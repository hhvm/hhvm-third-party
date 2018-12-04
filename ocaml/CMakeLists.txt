# Either we couldn't find a reasonable version of ocamlc or it was too old.
message(STATUS "Building ocaml from third-party")

set(OCAML_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/build")
set(OCAML "${OCAML_PREFIX}/bin/ocaml")
set(OCAMLC "${OCAML_PREFIX}/bin/ocamlc.opt")
set(OCAMLOPT "${OCAML_PREFIX}/bin/ocamlopt.opt")
set(OCAMLBUILD "${OCAML_PREFIX}/bin/ocamlbuild.native")
set(OPAM "${OCAML_PREFIX}/bin/opam")

# TODO: what about dependencies so we rebuild ocaml when it changes?
# NOTE: The weirdness building world.opt twice is because (at least on arm64)
# ocaml (4.03) seems to have parallel build dependency problems.
add_custom_command(
  OUTPUT ${OCAML} ${OCAMLC} ${OCAMLOPT}
  COMMAND ./configure -prefix "${OCAML_PREFIX}" -no-graph
  COMMAND \$\(MAKE\) -k world.opt || true
  COMMAND \$\(MAKE\) -j1 world.opt
  COMMAND \$\(MAKE\) install
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src"
  COMMENT "Compiling ocaml")

add_custom_command(
  OUTPUT ${OCAMLBUILD}
  # Hack up the path before building ocamlbuild.
  # (OCamlBuild doesn't understand how to override its build tools properly -
  # they call "ocamlc -where" directly from configure.make)
  # This would be better as 'cmake -E env' but that's only available in cmake 3.1+
  COMMAND /bin/bash -c "\
    PATH='${OCAML_PREFIX}/bin:$ENV{PATH}' \
    \$\(MAKE\) -f configure.make \
    OCAML_NATIVE=true \
    'OCAMLBUILD_BINDIR=${OCAML_PREFIX}/bin' \
    'OCAMLBUILD_LIBDIR=${OCAML_PREFIX}/lib' \
    'OCAMLBUILD_MANDIR=${OCAML_PREFIX}/share/man' \
  "
  COMMAND /bin/bash -c "\
    PATH='${OCAML_PREFIX}/bin:$ENV{PATH}' \
    \$\(MAKE\) \
  "
  COMMAND \$\(MAKE\) install CHECK_IF_PREINSTALLED=false
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/ocamlbuild"
  DEPENDS ${OCAMLC}
  COMMENT "Compiling ocamlbuild")

add_custom_command(
  OUTPUT ${OPAM}
  COMMAND /bin/bash -c "\
    PATH='${OCAML_PREFIX}/bin:$ENV{PATH}'\
    ./configure \
    --prefix='${OCAML_PREFIX}' \
  "
  # prep source tree to skip the %.download and %.stamp Makefile rules of lib-ext
  COMMAND
    "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps/prep_deps.sh"
    "${OCAML_PREFIX}"
    "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps" ./src_ext
  COMMAND /bin/bash -c "\
    PATH='${OCAML_PREFIX}/bin:$ENV{PATH}' \
    \$\(MAKE\) -j1 lib-ext \
  "
  COMMAND /bin/bash -c "\
    PATH='${OCAML_PREFIX}/bin:$ENV{PATH}' \
    \$\(MAKE\) -j1 \
  "
  COMMAND \$\(MAKE\) install
  # ensure clean git status
  COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps/cleanup_src_ext.sh" ./src_ext
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/opam"
  DEPENDS ${OCAMLBUILD}
  COMMENT "Compiling opam")

set(OCAMLC_FOUND TRUE)

add_custom_target(ocaml
  DEPENDS ${OCAMLC} ${OCAMLOPT} ${OCAMLBUILD} ${OPAM})

set(OCAML_EXECUTABLE ${OCAML} CACHE FILEPATH "path to ocaml" FORCE)
mark_as_advanced(OCAML_EXECUTABLE)
set(OCAMLC_EXECUTABLE ${OCAMLC} CACHE FILEPATH "path to ocamlc" FORCE)
mark_as_advanced(OCAMLC_EXECUTABLE)
set(OCAMLOPT_EXECUTABLE ${OCAMLOPT} CACHE FILEPATH "path to ocamlopt" FORCE)
mark_as_advanced(OCAMLOPT_EXECUTABLE)
set(OCAMLBUILD_EXECUTABLE ${OCAMLBUILD} CACHE FILEPATH "path to ocamlbuild" FORCE)
mark_as_advanced(OCAMLBUILD_EXECUTABLE)
set(OPAM_EXECUTABLE ${OPAM} CACHE FILEPATH "path to opam" FORCE)
mark_as_advanced(OPAM_EXECUTABLE)
