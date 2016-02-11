#!/bin/sh

GPERF=$(which gperf)

if [ -z "$GPERF" ]; then
  echo "gperf required for generating files" >&2
  exit 1
fi

mkdir -p gen/proxygen/lib/http
src/proxygen/lib/http/gen_HTTPCommonHeaders.h.sh src/proxygen/lib/http/HTTPCommonHeaders.txt src gen/proxygen/lib/http
src/proxygen/lib/http/gen_HTTPCommonHeaders.cpp.sh src/proxygen/lib/http/HTTPCommonHeaders.txt src gen/proxygen/lib/http "$GPERF"
