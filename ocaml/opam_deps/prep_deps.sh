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
PREFIX=$1
OPAM_DEPS=$2
SRC_EXT=$3
PATH="${PREFIX}/bin:$PATH"
# clean deps
rm -rf "${SRC_EXT}"/{extlib,re,cmdliner,graph,cudf,dose,uutf,jsonm} 
# transfer
cp -r "${OPAM_DEPS}/ocaml-extlib/extlib" "${SRC_EXT}/extlib"
cp -r "${OPAM_DEPS}/ocaml-re" "${SRC_EXT}/re"
cp -r "${OPAM_DEPS}/cmdliner" "${SRC_EXT}/cmdliner"
cp -r "${OPAM_DEPS}/ocamlgraph" "${SRC_EXT}/graph"
cp -r "${OPAM_DEPS}/cudf" "${SRC_EXT}/cudf"
cp -r "${OPAM_DEPS}/dose" "${SRC_EXT}/dose"
cp -r "${OPAM_DEPS}/uutf" "${SRC_EXT}/uutf"
cp -r "${OPAM_DEPS}/jsonm" "${SRC_EXT}/jsonm"
# patch cmdliner
(cd "${SRC_EXT}/cmdliner" && for p in ../patches/cmdliner/*.patch; do patch -p1 < $p; done)
# patch ocamlgraph
ocamllex "${SRC_EXT}/graph/src/dot_lexer.mll"
ocamllex "${SRC_EXT}/graph/src/gml.mll"
ocamlyacc "${SRC_EXT}/graph/src/dot_parser.mly"
echo 'let version = "1.8.4+dev"' > "${SRC_EXT}/graph/src/version.ml"
echo 'let date = "Fri Apr 4 14:45:42 CEST 2014"' >> "${SRC_EXT}/graph/src/version.ml"
# patch dose
(cd "${SRC_EXT}/dose" && for p in ../patches/dose/*.patch; do patch -p1 < $p; done)
# finish
touch "${SRC_EXT}"/{extlib,re,cmdliner,graph,cudf,dose,uutf,jsonm}.{download,stamp}
