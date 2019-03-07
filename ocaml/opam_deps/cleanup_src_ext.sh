#!/bin/bash
#
# Copyright (c) 2018-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.
#
set -e
SRC_EXT=$1
# opam does not gitignore .download but does gitignore .stamp
TARGET_DIR="cmdliner cppo cudf dose3 dune-local extlib mccs ocamlgraph"
TARGET_DIR="${TARGET_DIR} opam-file-format re result seq"
for dir in ${TARGET_DIR}; do
  rm -f "${SRC_EXT}/${dir}".download
  done
