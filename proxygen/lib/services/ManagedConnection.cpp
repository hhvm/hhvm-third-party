// Copyright 2004-present Facebook.  All rights reserved.
#include "proxygen/lib/services/ManagedConnection.h"

#include "proxygen/lib/services/ConnectionManager.h"

namespace proxygen {

ManagedConnection::ManagedConnection()
  : connectionManager_(nullptr) {
}

ManagedConnection::~ManagedConnection() {
  if (connectionManager_) {
    connectionManager_->removeConnection(this);
  }
}

void
ManagedConnection::resetTimeout() {
  if (connectionManager_) {
    connectionManager_->scheduleTimeout(this);
  }
}

////////////////////// Globals /////////////////////

std::ostream&
operator<<(std::ostream& os, const ManagedConnection& conn) {
  conn.describe(os);
  return os;
}

} // proxygen
