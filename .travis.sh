#!/bin/sh
set -e
hhvm --version

cd /var/source/util

hh_client
FILE=../third_party_notices.txt
PRE_HASH="$(sha256sum $FILE)"
hhvm make-notices.hh > $FILE
POST_HASH="$(sha256sum $FILE)"

if [ "$PRE_HASH" != "$POST_HASH" ]; then
  echo "third_party_notices.txt differs - please regenerate"
  exit 1
fi
