#!/bin/bash

# $1 must be the path to hphp/hack
set -e

OPAM_VERSION="2.0.3"
OPAM_PKG="opam-full-${OPAM_VERSION}.tar.gz"

if ! [ -f "${OPAM_PKG}" ]; then
    if [ -f "$1/facebook/${OPAM_PKG}" ]; then
        cp "$1/facebook/${OPAM_PKG}" .
    else
        wget "https://github.com/ocaml/opam/releases/download/${OPAM_VERSION}/${OPAM_PKG}"
    fi
fi
# TODO: add the signature check once the file is available from github

rm -rf opam
tar xzf "${OPAM_PKG}"
mv "opam-full-${OPAM_VERSION}" opam
