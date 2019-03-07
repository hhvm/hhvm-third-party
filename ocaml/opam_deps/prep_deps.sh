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

TARGETS="cmdliner cppo cudf dose3 dune-local extlib ocamlgraph mccs re"
TARGETS="$TARGETS opam-file-format result seq"

# clean deps
for dir in $TARGETS; do
    rm -rf "${SRC_EXT}/${dir}"
done

# transfer
cp -r "${OPAM_DEPS}/cmdliner" "${SRC_EXT}/cmdliner"
cp -r "${OPAM_DEPS}/cppo" "${SRC_EXT}/cppo"
cp -r "${OPAM_DEPS}/cudf" "${SRC_EXT}/cudf"
cp -r "${OPAM_DEPS}/dose" "${SRC_EXT}/dose3"
cp -r "${OPAM_DEPS}/dune" "${SRC_EXT}/dune-local"
cp -r "${OPAM_DEPS}/ocaml-extlib" "${SRC_EXT}/extlib"
cp -r "${OPAM_DEPS}/ocamlgraph" "${SRC_EXT}/ocamlgraph"
cp -r "${OPAM_DEPS}/ocaml-mccs" "${SRC_EXT}/mccs"
cp -r "${OPAM_DEPS}/ocaml-re" "${SRC_EXT}/re"
cp -r "${OPAM_DEPS}/opam-file-format" "${SRC_EXT}/opam-file-format"
cp -r "${OPAM_DEPS}/result" "${SRC_EXT}/result"
cp -r "${OPAM_DEPS}/seq" "${SRC_EXT}/seq"

# patch repos
pushd "${SRC_EXT}"

for dir in $TARGETS; do
    if [ -d "patches/${dir}.common" ]; then
        cd "${dir}"
        for p in ../patches/"${dir}.common"/*.patch; do
            patch -p1 < $p
        done
        cd ..
    fi
    if [ -d "patches/${dir}" ]; then
        cd "${dir}"
        for p in ../patches/"${dir}"/*.patch; do
            patch -p1 < $p
        done
        cd ..
    fi
    if [ "${dir}" != "dune-local" ] ; then
        for i in $(find "$dir" -name jbuild); do
            sed -e "s/name \+runtest/name disabled-runtest/g" $i > $i.tmp
            mv $i.tmp $i
        done
        for j in $(find . -regextype sed -regex "\(./dune-${dir}\|./dune-${dir}-.*\)"); do
            cp "$j" "${dir}$(echo "$(basename $j)" | sed -e "s/dune-${dir}//" -e "s|-|/|g")/dune"
            echo "(lang dune 1.0)" > "${dir}/dune-project"
            echo "(name ${dir})" >> "${dir}/dune-project"
            touch "${dir}/${dir}.opam"
        done
    fi
    touch "${dir}.stamp" "${dir}.download"
done
popd

# patch ocamlgraph
ocamllex "${SRC_EXT}/ocamlgraph/src/dot_lexer.mll"
ocamllex "${SRC_EXT}/ocamlgraph/src/gml.mll"
ocamlyacc "${SRC_EXT}/ocamlgraph/src/dot_parser.mly"
echo 'let version = "1.8.*+dev"' > "${SRC_EXT}/ocamlgraph/src/version.ml"
echo 'let date = "Thu Mar 7 11:59:42 CEST 2019"' >> "${SRC_EXT}/ocamlgraph/src/version.ml"
