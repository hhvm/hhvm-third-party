message(STATUS "Building opam from third-party")

set(OPAM_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/build")
set(OPAM "${OPAM_PREFIX}/bin/opam")
set(OPAM_INSTALLER "${OPAM_PREFIX}/bin/opam-installer")

include("${CMAKE_CURRENT_LIST_DIR}/../ocaml/CMakeLists.txt")

macro(fetch FILE URL HASH)
  if (NOT EXISTS "${FILE}")
    message(STATUS "Downloading ${URL}")
    file(DOWNLOAD "${URL}" "${FILE}" EXPECTED_HASH ${HASH})
  endif()
endmacro(fetch)

set(CMDLINER "${CMAKE_CURRENT_LIST_DIR}/src/src_ext/cmdliner-0.9.7.tbz")
fetch(
  "${CMDLINER}"
  http://erratique.ch/software/cmdliner/releases/cmdliner-0.9.7.tbz
  SHA256=9c19893cffb5d3c3469ee0cce85e3eeeba17d309b33b9ace31aba06f68f0bf7a
)

set(CUDF "${CMAKE_CURRENT_LIST_DIR}/src/src_ext/cudf-0.7.tar.gz")
fetch(
  "${CUDF}"
  https://gforge.inria.fr/frs/download.php/file/33593/cudf-0.7.tar.gz
  SHA256=92c8a9ed730bbac73f3513abab41127d966c9b9202ab2aaffcd02358c030a701
)

set(DOSE3 "${CMAKE_CURRENT_LIST_DIR}/src/src_ext/dose3-3.3.tar.gz")
fetch(
  "${DOSE3}"
  https://gforge.inria.fr/frs/download.php/file/34277/dose3-3.3.tar.gz
  SHA256=8dc4dae9b1a81bb3a42abb283df785ba3eb00ade29b13875821c69f03e00680e
)

set(EXTLIB "${CMAKE_CURRENT_LIST_DIR}/src/src_ext/extlib-1.5.3.tar.gz")
fetch(
  "${EXTLIB}"
  http://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/ocaml-extlib/extlib-1.5.3.tar.gz
  SHA256=c095eef4202a8614ff1474d4c08c50c32d6ca82d1015387785cf03d5913ec021
)

set(JSONM "${CMAKE_CURRENT_LIST_DIR}/src/src_ext/jsonm-0.9.1.tbz")
fetch(
  "${JSONM}"
  http://erratique.ch/software/jsonm/releases/jsonm-0.9.1.tbz
  SHA256=3fd4dca045d82332da847e65e981d8b504883571d299a3f7e71447d46bc65f73
)

set(OCAMLGRAPH "${CMAKE_CURRENT_LIST_DIR}/src/src_ext/ocamlgraph-1.8.5.tar.gz")
fetch(
  "${OCAMLGRAPH}"
  http://ocamlgraph.lri.fr/download/ocamlgraph-1.8.5.tar.gz
  SHA256=d167466435a155c779d5ec25b2db83ad851feb42ebc37dca8ffa345ddaefb82f
)

set(OCAML_RE "${CMAKE_CURRENT_LIST_DIR}/src/src_ext/ocaml-re-1.2.0.tar.gz")
fetch(
  "${OCAML_RE}"
  https://github.com/ocaml/ocaml-re/archive/ocaml-re-1.2.0.tar.gz
  SHA256=a34dd9d6136731436a963bbab5c4bbb16e5d4e21b3b851d34887a3dec451999f
)

set(UUTF "${CMAKE_CURRENT_LIST_DIR}/src/src_ext/uutf-0.9.3.tbz")
fetch(
  "${UUTF}"
  http://erratique.ch/software/uutf/releases/uutf-0.9.3.tbz
  SHA256=1f364f89b1179e5182a4d3ad8975f57389d45548735d19054845e06a27107877
)

add_custom_target(opam_src_ext
  DEPENDS "${CMDLINER}" "${CUDF}" "${DOSE3}" "${EXTLIB}" "${JSONM}"
    "${OCAMLGRAPH}" "${OCAML_RE}" "${UUTF}")

add_custom_command(
  OUTPUT ${OPAM} ${OPAM_INSTALLER}
  DEPENDS ocaml opam_src_ext
  COMMAND ./configure -prefix "${OPAM_PREFIX}"
    OCAML="${OCAML_EXECUTABLE}"
    OCAMLC="${OCAMLC_EXECUTABLE}"
    OCAMLCDOTOPT="${OCAMLC_EXECUTABLE}"
    OCAMLOPT="${OCAMLOPT_EXECUTABLE}"
    OCAMLOPTDOTOPT="${OCAMLOPT_EXECUTABLE}"
    OCAMLDEP="${OCAMLDEP_EXECUTABLE}"
    OCAMLDOC="${OCAMLDOC_EXECUTABLE}"
    OCAMLLEX="${OCAMLLEX_EXECUTABLE}"
    OCAMLLEXDOTOPT="${OCAMLLEX_EXECUTABLE}"
    OCAMLYACC="${OCAMLYACC_EXECUTABLE}"
    OCAMLMKLIB="${OCAMLMKLIB_EXECUTABLE}"
    OCAMLMKTOP="${OCAMLMKTOP_EXECUTABLE}"
    OCAMLBUILD="${OCAMLBUILD_EXECUTABLE}"
    OCAMLFIND="no"
  COMMAND \$\(MAKE\) lib-ext
  # Makefile.config.in is missing OCAMLMKTOP so we have to set it here too
  COMMAND \$\(MAKE\) opam opam-installer OCAMLMKTOP="${OCAMLMKTOP_EXECUTABLE}"
  COMMAND \$\(MAKE\) install
  # src_ext/jsonm and src_ext/uutf are missing from .gitignore, so clean them up
  # (see https://github.com/ocaml/opam/pull/3065)
  COMMAND rm -rf
    "${CMAKE_CURRENT_LIST_DIR}/src/src_ext/jsonm"
    "${CMAKE_CURRENT_LIST_DIR}/src/src_ext/uutf"
  WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/src"
  COMMENT "Compiling opam")

add_custom_target(opam
  DEPENDS ${OPAM} ${OPAM_INSTALLER})

set(OPAM_EXECUTABLE ${OPAM} CACHE FILEPATH "path to opam" FORCE)
mark_as_advanced(OPAM_EXECUTABLE)
set(OPAM_INSTALLER_EXECUTABLE ${OPAM_INSTALLER} CACHE FILEPATH "path to opam-installer" FORCE)
mark_as_advanced(OPAM_INSTALLER_EXECUTABLE)
