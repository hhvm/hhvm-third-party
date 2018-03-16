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
rm "${SRC_EXT}"/{extlib,re,cmdliner,graph,cudf,dose,uutf,jsonm}.download