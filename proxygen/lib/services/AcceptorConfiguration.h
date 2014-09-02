// Copyright 2004-present Facebook.  All rights reserved.
#pragma once

#include "proxygen/lib/utils/SocketOptions.h"

#include <boost/optional.hpp>
#include <chrono>
#include <fcntl.h>
#include <folly/String.h>
#include <list>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <thrift/lib/cpp/async/TAsyncSocket.h>
#include <thrift/lib/cpp/transport/TSSLSocket.h>
#include <thrift/lib/cpp/transport/TSocketAddress.h>
#include <zlib.h>

namespace facebook { namespace proxygen {

/**
 * Configuration for a single Acceptor.
 *
 * This configures not only accept behavior, but also some types of SSL
 * behavior that may make sense to configure on a per-VIP basis (e.g. which
 * cert(s) we use, etc).
 */
struct AcceptorConfiguration {
  /**
   * Set/get the socket options to apply on all downstream connections.
   */
  void setSocketOptions(
    const apache::thrift::async::TAsyncSocket::OptionMap& opts) {
    socketOptions_ = filterIPSocketOptions(opts, bindAddress.getFamily());
  }
  apache::thrift::async::TAsyncSocket::OptionMap&
  getSocketOptions() {
    return socketOptions_;
  }
  const apache::thrift::async::TAsyncSocket::OptionMap&
  getSocketOptions() const {
    return socketOptions_;
  }

  /**
   * The name of this acceptor; used for stats/reporting purposes.
   */
  std::string name;

  /**
   * Determines if the VIP should accept traffic from only internal or
   * external clients. Internal VIPs have different behavior
   * (e.g. Via headers, etc).
   */
  bool internal{false};

  /**
   * The depth of the accept queue backlog.
   */
  uint32_t acceptBacklog{1024};

  /**
   * The number of milliseconds a connection can be idle before we close it.
   */
  std::chrono::milliseconds connectionIdleTimeout{600000};

  /**
   * The number of milliseconds a transaction can be idle before we close it.
   */
  std::chrono::milliseconds transactionIdleTimeout{600000};

  /**
   * The address to bind to.
   */
  apache::thrift::transport::TSocketAddress bindAddress;

  /**
   * Determines if the Acceptor does strict checking when loading the ssl
   * contexts.
   */
  bool strictSSL{true};

  /**
   * The compression level to use for SPDY headers with responses from
   * this Acceptor.
   */
  int spdyCompressionLevel{Z_NO_COMPRESSION};

  /**
   * The name of the protocol to use on non-TLS connections.
   */
  std::string plaintextProtocol;

 private:
  apache::thrift::async::TAsyncSocket::OptionMap socketOptions_;
};

}} // facebook::proxygen
