# Phase 1 - see if they have a built-in version of ocamlc which is 'good enough'
find_program(OCAML NAMES ocaml ocaml)
find_program(OCAMLC NAMES ocamlc.opt ocamlc)
find_program(OCAMLOPT NAMES ocamlopt.opt ocamlopt)
find_program(OCAMLBUILD NAMES ocamlbuild.native ocamlbuild)

set(OCAMLC_FOUND FALSE)

if (OCAMLC)
  # We found a local version of ocamlc - check the version.
  message(STATUS "Found ocamlc: ${OCAMLC}")
  execute_process(COMMAND "${OCAMLC}" -version
    OUTPUT_VARIABLE OCAMLC_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  message(STATUS "Got ocaml version ${OCAMLC_VERSION}")
  if ("${OCAMLC_VERSION}" VERSION_LESS "4.03")
    message(STATUS "System version of ocaml is too old")
  else()
    set(OCAMLC_FOUND TRUE)
  endif()
endif()

if (NOT OCAMLC_FOUND)
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
    COMMAND /bin/bash -c 'PATH="${OCAML_PREFIX}/bin:$ENV{PATH}" \$\(MAKE\) -f configure.make
        OCAML_NATIVE=true
        OCAMLBUILD_BINDIR=${OCAML_PREFIX}/bin
        OCAMLBUILD_LIBDIR=${OCAML_PREFIX}/lib'
    COMMAND /bin/bash -c 'PATH="${OCAML_PREFIX}/bin:$ENV{PATH}" \$\(MAKE\)'
    COMMAND \$\(MAKE\) install CHECK_IF_PREINSTALLED=false
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/ocamlbuild"
    DEPENDS ${OCAMLC}
    COMMENT "Compiling ocamlbuild")

  add_custom_command(
    OUTPUT ${OPAM}
    COMMAND /bin/bash -c 'PATH="${OCAML_PREFIX}/bin:$ENV{PATH}" ./configure --prefix="${OCAML_PREFIX}"'
    # BEGIN PATCHING extlib
    # This allows us to skip directly modifying opam's Makefile or opam's src_ext Makefile
    COMMAND ${CMAKE_COMMAND} -E ARGS remove_directory src_ext/extlib
    COMMAND ${CMAKE_COMMAND} -E ARGS remove_directory src_ext/re
    COMMAND ${CMAKE_COMMAND} -E ARGS remove_directory src_ext/cmdliner
    COMMAND ${CMAKE_COMMAND} -E ARGS remove_directory src_ext/graph
    COMMAND ${CMAKE_COMMAND} -E ARGS remove_directory src_ext/cudf
    COMMAND ${CMAKE_COMMAND} -E ARGS remove_directory src_ext/dose
    COMMAND ${CMAKE_COMMAND} -E ARGS remove_directory src_ext/uutf
    COMMAND ${CMAKE_COMMAND} -E ARGS remove_directory src_ext/jsonm
    COMMAND ${CMAKE_COMMAND} -E ARGS copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps/ocaml-extlib/extlib" src_ext/extlib
    COMMAND ${CMAKE_COMMAND} -E ARGS copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps/ocaml-re" src_ext/re
    COMMAND ${CMAKE_COMMAND} -E ARGS copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps/cmdliner" src_ext/cmdliner
    # patch cmdliner
    COMMAND /bin/bash -c 'cd src_ext/cmdliner && for p in ../patches/cmdliner/*.patch\; do patch -p1 < $$p\; done\;'
    COMMAND ${CMAKE_COMMAND} -E ARGS copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps/ocamlgraph" src_ext/graph
    # patch ocamlgraph
    COMMAND /bin/bash -c 'PATH="${OCAML_PREFIX}/bin:$ENV{PATH}" ocamllex src_ext/graph/src/dot_lexer.mll'
    COMMAND /bin/bash -c 'PATH="${OCAML_PREFIX}/bin:$ENV{PATH}" ocamllex src_ext/graph/src/gml.mll'
    COMMAND /bin/bash -c 'PATH="${OCAML_PREFIX}/bin:$ENV{PATH}" ocamlyacc src_ext/graph/src/dot_parser.mly'
    COMMAND /bin/bash -c '/bin/echo let version = \\"1.8.4+dev\\" > src_ext/graph/src/version.ml'
    COMMAND /bin/bash -c '/bin/echo let date = \\"Fri Apr 4 14:45:42 CEST 2014\\" >> src_ext/graph/src/version.ml'
    COMMAND ${CMAKE_COMMAND} -E ARGS copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps/cudf" src_ext/cudf
    COMMAND ${CMAKE_COMMAND} -E ARGS copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps/dose" src_ext/dose
    COMMAND /bin/bash -c 'cd src_ext/dose && for p in ../patches/dose/*.patch\; do patch -p1 < $$p\; done\;'
    COMMAND ${CMAKE_COMMAND} -E ARGS copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps/uutf" src_ext/uutf
    COMMAND ${CMAKE_COMMAND} -E ARGS copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/opam_deps/jsonm" src_ext/jsonm
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/extlib.download
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/extlib.stamp
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/re.download
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/re.stamp
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/cmdliner.download
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/cmdliner.stamp
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/graph.download
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/graph.stamp
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/cudf.download
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/cudf.stamp
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/dose.download
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/dose.stamp
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/uutf.download
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/uutf.stamp
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/jsonm.download
    COMMAND ${CMAKE_COMMAND} -E ARGS touch src_ext/jsonm.stamp
    # END PATCHING extlib
    COMMAND /bin/bash -c 'PATH="${OCAML_PREFIX}/bin:$ENV{PATH}" \$\(MAKE\) -j1 lib-ext' # -j1 to pacify opam
    COMMAND /bin/bash -c 'PATH="${OCAML_PREFIX}/bin:$ENV{PATH}" \$\(MAKE\) -j1'
    COMMAND \$\(MAKE\) install
    # Clean up submodule repo, ok because .stamp are gitignored
    COMMAND ${CMAKE_COMMAND} -E ARGS remove src_ext/extlib.download src_ext/re.download src_ext/cmdliner.download src_ext/graph.download src_ext/cudf.download src_ext/dose.download src_ext/uutf.download src_ext/jsonm.download
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/opam"
    DEPENDS ${OCAMLBUILD}
    COMMENT "Compiling opam")

  set(OCAMLC_FOUND TRUE)
endif()

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
