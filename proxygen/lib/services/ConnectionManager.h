// Copyright 2004-present Facebook.  All rights reserved.
#pragma once

#include "proxygen/lib/services/ManagedConnection.h"

#include <chrono>
#include <folly/Memory.h>
#include <thrift/lib/cpp/async/TAsyncTimeout.h>
#include <thrift/lib/cpp/async/TAsyncTimeoutSet.h>
#include <thrift/lib/cpp/async/TDelayedDestruction.h>
#include <thrift/lib/cpp/async/TEventBase.h>

namespace facebook { namespace proxygen {

/**
 * A ConnectionManager keeps track of ManagedConnections.
 */
class ConnectionManager: public apache::thrift::async::TDelayedDestruction {
 public:

  /**
   * Interface for an optional observer that's notified about
   * various events in a ConnectionManager
   */
  class Callback {
  public:
    virtual ~Callback() {}

    /**
     * Invoked when the number of connections managed by the
     * ConnectionManager changes from nonzero to zero.
     */
    virtual void onEmpty(const ConnectionManager& cm) = 0;

    /**
     * Invoked when a connection is added to the ConnectionManager.
     */
    virtual void onConnectionAdded(const ConnectionManager& cm) = 0;

    /**
     * Invoked when a connection is removed from the ConnectionManager.
     */
    virtual void onConnectionRemoved(const ConnectionManager& cm) = 0;
  };

  typedef std::unique_ptr<ConnectionManager, Destructor> UniquePtr;

  /**
   * Returns a new instance of ConnectionManager wrapped in a unique_ptr
   */
  template<typename... Args>
  static UniquePtr makeUnique(Args&&... args) {
    return folly::make_unique<ConnectionManager, Destructor>(
      std::forward<Args>(args)...);
  }

  /**
   * Constructor not to be used by itself.
   */
  ConnectionManager(apache::thrift::async::TEventBase* eventBase,
                    std::chrono::milliseconds timeout,
                    Callback* callback = nullptr);

  /**
   * Add a connection to the set of connections managed by this
   * ConnectionManager.
   *
   * @param connection     The connection to add.
   * @param timeout        Whether to immediately register this connection
   *                         for an idle timeout callback.
   */
  void addConnection(ManagedConnection* connection,
      bool timeout = false);

  /**
   * Schedule a timeout callback for a connection.
   */
  void scheduleTimeout(ManagedConnection* connection);

  /**
   * Remove a connection from this ConnectionManager and, if
   * applicable, cancel the pending timeout callback that the
   * ConnectionManager has scheduled for the connection.
   *
   * @note This method does NOT destroy the connection.
   */
  void removeConnection(ManagedConnection* connection);

  /* Begin gracefully shutting down connections in this ConnectionManager.
   * Notify all connections of pending shutdown, and after idleGrace,
   * begin closing idle connections.
   */
  void initiateGracefulShutdown(std::chrono::milliseconds idleGrace);

  /**
   * Destroy all connections Managed by this ConnectionManager, even
   * the ones that are busy.
   */
  void dropAllConnections();

  size_t getNumConnections() const { return conns_.size(); }

 private:
  class CloseIdleConnsCallback :
      public apache::thrift::async::TEventBase::LoopCallback,
      public apache::thrift::async::TAsyncTimeout {
   public:
    explicit CloseIdleConnsCallback(ConnectionManager* manager)
        : apache::thrift::async::TAsyncTimeout(manager->eventBase_),
          manager_(manager) {}

    void runLoopCallback() noexcept override {
      VLOG(3) << "Draining more conns from loop callback";
      manager_->drainAllConnections();
    }

    void timeoutExpired() noexcept override {
      VLOG(3) << "Idle grace expired";
      manager_->drainAllConnections();
    }

   private:
    ConnectionManager* manager_;
  };

  enum class ShutdownAction : uint8_t {
    /**
     * Drain part 1: inform remote that you will soon reject new requests.
     */
    DRAIN1 = 0,
    /**
     * Drain part 2: start rejecting new requests.
     */
    DRAIN2 = 1,
  };

  ~ConnectionManager() {}

  ConnectionManager(const ConnectionManager&) = delete;
  ConnectionManager& operator=(ConnectionManager&) = delete;

  /**
   * Destroy all connections managed by this ConnectionManager that
   * are currently idle, as determined by a call to each ManagedConnection's
   * isBusy() method.
   */
  void drainAllConnections();

  /** All connections */
  folly::CountedIntrusiveList<
    ManagedConnection,&ManagedConnection::listHook_> conns_;

  /** Connections that currently are registered for timeouts */
  apache::thrift::async::TAsyncTimeoutSet::UniquePtr connTimeouts_;

  /** Optional callback to notify of state changes */
  Callback* callback_;

  /** Event base in which we run */
  apache::thrift::async::TEventBase* eventBase_;

  /** Iterator to the next connection to shed; used by drainAllConnections() */
  folly::CountedIntrusiveList<
    ManagedConnection,&ManagedConnection::listHook_>::iterator idleIterator_;
  CloseIdleConnsCallback idleLoopCallback_;
  ShutdownAction action_{ShutdownAction::DRAIN1};
};

}} // facebook::proxygen
