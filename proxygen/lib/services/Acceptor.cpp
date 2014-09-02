// Copyright 2004-present Facebook.  All rights reserved.
#include "proxygen/lib/services/Acceptor.h"

#include "proxygen/lib/services/ManagedConnection.h"
#include "proxygen/lib/utils/Time.h"
#include "stubs/glog/portability.h"

#include <boost/cast.hpp>
#include <fcntl.h>
#include <folly/ScopeGuard.h>
#include <fstream>
#include <gflags/gflags.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thrift/lib/cpp/async/TAsyncSocket.h>
#include <thrift/lib/cpp/async/TEventBase.h>
#include <unistd.h>

using apache::thrift::async::TAsyncServerSocket;
using apache::thrift::async::TAsyncSocket;
using apache::thrift::async::TAsyncTimeoutSet;
using apache::thrift::async::TEventBase;
using apache::thrift::transport::TSocketAddress;
using apache::thrift::transport::TTransportException;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::filebuf;
using std::ifstream;
using std::ios;
using std::shared_ptr;
using std::string;

namespace facebook { namespace proxygen {

DEFINE_int32(shutdown_idle_grace_ms, 5000, "milliseconds to wait before "
             "closing idle conns");

static const std::string empty_string;

Acceptor::Acceptor(const AcceptorConfiguration& accConfig) :
  accConfig_(accConfig),
  socketOptions_(accConfig.getSocketOptions()) {
}

void
Acceptor::init(TAsyncServerSocket* serverSocket,
               TEventBase* eventBase) {
  CHECK_NULL(this->base_);

  base_ = eventBase;
  state_ = State::kRunning;
  downstreamConnectionManager_ = ConnectionManager::makeUnique(
    eventBase, accConfig_.connectionIdleTimeout, this);
  transactionTimeouts_.reset(new TAsyncTimeoutSet(
      eventBase, accConfig_.transactionIdleTimeout));

  serverSocket->addAcceptCallback(this, eventBase);
  // SO_KEEPALIVE is the only setting that is inherited by accepted
  // connections so only apply this setting
  for (const auto& option: socketOptions_) {
    if (option.first.level == SOL_SOCKET &&
        option.first.optname == SO_KEEPALIVE && option.second == 1) {
      serverSocket->setKeepAliveEnabled(true);
      break;
    }
  }
}

Acceptor::~Acceptor(void) {
}

void
Acceptor::drainAllConnections() {
  if (downstreamConnectionManager_) {
    downstreamConnectionManager_->initiateGracefulShutdown(
      std::chrono::milliseconds(FLAGS_shutdown_idle_grace_ms));
  }
}

bool Acceptor::canAccept(const TSocketAddress& address) {
  return true;
}

void
Acceptor::connectionAccepted(
    int fd, const TSocketAddress& clientAddr) noexcept {
  if (!canAccept(clientAddr)) {
    close(fd);
    return;
  }
  auto acceptTime = getCurrentTime();
  for (const auto& opt: socketOptions_) {
    opt.first.apply(fd, opt.second);
  }
  TransportInfo tinfo;
  tinfo.acceptTime = acceptTime;
  TAsyncSocket::UniquePtr sock(new TAsyncSocket(base_, fd));
  connectionReady(std::move(sock), clientAddr, empty_string, tinfo);
}

void
Acceptor::connectionReady(
    TAsyncSocket::UniquePtr sock,
    const TSocketAddress& clientAddr,
    const string& nextProtocolName,
    TransportInfo& tinfo) {
  // Limit the number of reads from the socket per poll loop iteration,
  // both to keep memory usage under control and to prevent one fast-
  // writing client from starving other connections.
  sock->setMaxReadsPerEvent(16);
  tinfo.initWithSocket(sock.get());
  onNewConnection(std::move(sock), &clientAddr, nextProtocolName, tinfo);
}

void
Acceptor::acceptError(const std::exception& ex) noexcept {
  // An error occurred.
  // The most likely error is out of FDs.  TAsyncServerSocket will back off
  // briefly if we are out of FDs, then continue accepting later.
  // Just log a message here.
  LOG(ERROR) << "error accepting on acceptor socket: " << ex.what();
}

void
Acceptor::acceptStopped() noexcept {
  VLOG(3) << "Acceptor " << this << " acceptStopped()";
  // Drain the open client connections
  drainAllConnections();

  // If we haven't yet finished draining, begin doing so by marking ourselves
  // as in the draining state. We must be sure to hit checkDrained() here, as
  // if we're completely idle, we can should consider ourself drained
  // immediately (as there is no outstanding work to complete to cause us to
  // re-evaluate this).
  if (state_ != State::kDone) {
    state_ = State::kDraining;
    checkDrained();
  }
}

void
Acceptor::onEmpty(const ConnectionManager& cm) {
  VLOG(3) << "Acceptor=" << this << " onEmpty()";
  if (state_ == State::kDraining) {
    checkDrained();
  }
}

void
Acceptor::checkDrained() {
  CHECK(state_ == State::kDraining);
  if (forceShutdownInProgress_ ||
      (downstreamConnectionManager_->getNumConnections() != 0)) {
    return;
  }

  VLOG(2) << "All connections drained from Acceptor=" << this << " in thread "
          << base_;

  downstreamConnectionManager_.reset();

  state_ = State::kDone;

  onConnectionsDrained();
}

milliseconds
Acceptor::getConnTimeout() const {
  return accConfig_.connectionIdleTimeout;
}

void Acceptor::addConnection(ManagedConnection* conn) {
  // Add the socket to the timeout manager so that it can be cleaned
  // up after being left idle for a long time.
  downstreamConnectionManager_->addConnection(conn, true);
}

void
Acceptor::forceStop() {
  base_->runInEventBaseThread([&] { dropAllConnections(); });
}

void
Acceptor::dropAllConnections() {
  if (downstreamConnectionManager_) {
    LOG(INFO) << "Dropping all connections from Acceptor=" << this <<
      " in thread " << base_;
    assert(base_->isInEventBaseThread());
    forceShutdownInProgress_ = true;
    downstreamConnectionManager_->dropAllConnections();
    CHECK(downstreamConnectionManager_->getNumConnections() == 0);
    downstreamConnectionManager_.reset();
  }

  state_ = State::kDone;
  onConnectionsDrained();
}

}} // facebook::proxygen
