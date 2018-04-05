#
#   +----------------------------------------------------------------------+
#   | HipHop for PHP                                                       |
#   +----------------------------------------------------------------------+
#   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
#   | Copyright (c) 1997-2010 The PHP Group                                |
#   +----------------------------------------------------------------------+
#   | This source file is subject to version 3.01 of the PHP license,      |
#   | that is bundled with this package in the file LICENSE, and is        |
#   | available through the world-wide-web at the following url:           |
#   | http://www.php.net/license/3_01.txt                                  |
#   | If you did not receive a copy of the PHP license and are unable to   |
#   | obtain it through the world-wide-web, please send a note to          |
#   | license@php.net so we can mail you a copy immediately.               |
#   +----------------------------------------------------------------------+
#

set(EXTRA_INCLUDE_PATHS)
set(THIRD_PARTY_MODULES)
set(THIRD_PARTY_HEADERS)


list(APPEND THIRD_PARTY_MODULES libmbfl)
list(APPEND EXTRA_INCLUDE_PATHS
  "${TP_DIR}/libmbfl"
  "${TP_DIR}/libmbfl/mbfl"
  "${TP_DIR}/libmbfl/filters"
)

list(APPEND THIRD_PARTY_MODULES timelib)
list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/timelib")

list(APPEND THIRD_PARTY_MODULES folly)
list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/folly/src")

# Fatal is a header-only library, so there's nothing to build.
list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/fatal")

list(APPEND THIRD_PARTY_MODULES wangle)
list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/wangle/src")

list(APPEND THIRD_PARTY_MODULES brotli)
list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/brotli/src")

if(ENABLE_FASTCGI)
  list(APPEND THIRD_PARTY_MODULES proxygen)
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/proxygen/src")

  list(APPEND THIRD_PARTY_MODULES thrift)
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/thrift/src")

  list(APPEND THIRD_PARTY_MODULES zstd)
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/zstd/src/lib")
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/zstd/src/lib/dictBuilder")
endif()

if (NOT MSVC)
  list(APPEND THIRD_PARTY_MODULES libafdt)
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/libafdt/src/src")
endif()

if(ENABLE_ASYNC_MYSQL)
  find_package(RE2)
  if(NOT RE2_LIBRARY)
    message(STATUS "Building RE2 from third-party")
    list(APPEND THIRD_PARTY_MODULES re2)
  endif()
  list(APPEND THIRD_PARTY_MODULES squangle)
  list(APPEND THIRD_PARTY_MODULES webscalesqlclient)
endif()

if (ENABLE_MCROUTER)
  # Ragel is only used at build time to generate some files for MCRouter.
  list(APPEND THIRD_PARTY_MODULES ragel)

  list(APPEND THIRD_PARTY_MODULES mcrouter)
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/mcrouter/src")
endif()

# Add bundled fastlz if the system one will not be used
if(NOT FASTLZ_LIBRARY)
  list(APPEND THIRD_PARTY_MODULES fastlz)
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/fastlz/src")
endif()

# Add bundled libsqlite3 if the system one will not be used
if(NOT LIBSQLITE3_LIBRARY)
  list(APPEND THIRD_PARTY_MODULES libsqlite3)
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/libsqlite3")
endif()

# Add bundled lz4 if the system one will not be used
if(NOT LZ4_FOUND)
  list(APPEND THIRD_PARTY_MODULES lz4)
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/lz4/src/lib")
endif()

# Add bundled double-conversion if the system one will not be used
if(NOT DOUBLE_CONVERSION_FOUND)
  list(APPEND THIRD_PARTY_MODULES double-conversion)
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/double-conversion")
endif()

# Add bundled PCRE if the system one will not be used
find_package(PCRE)
if(NOT PCRE_LIBRARY)
  list(APPEND THIRD_PARTY_MODULES pcre)
  # Disable building a few parts of PCRE by default that we don't
  # actually use.
  set(PCRE_BUILD_PCRECPP OFF CACHE BOOL "Build the PCRE C++ library (pcrecpp).")
  set(PCRE_BUILD_PCREGREP OFF CACHE BOOL "Build pcregrep")
  set(PCRE_BUILD_TESTS OFF CACHE BOOL "Build the tests")
endif()

# Add bundled libzip if the system one will not be used
if(NOT LIBZIP_LIBRARY)
  list(APPEND THIRD_PARTY_MODULES libzip)
  list(APPEND EXTRA_INCLUDE_PATHS
    "${CMAKE_CURRENT_BINARY_DIR}/libzip/src/lib"
    "${TP_DIR}/libzip/src/lib"
  )
endif()

list(APPEND THIRD_PARTY_MODULES ocaml)

# Add bundled XED library if XED is enabled and the specified XED library
# is either not found or incompatible.
if(NOT DISABLE_XED AND NOT LibXed_FOUND)
  list(APPEND THIRD_PARTY_MODULES xed)
  list(APPEND EXTRA_INCLUDE_PATHS "${TP_DIR}/xed/xed/build/include/xed")
endif()

function(TP_INSTALL_HEADERS TARGET SRCDIR DEST)
  file(GLOB_RECURSE files "${SRCDIR}/*.h")
  install(
    CODE "INCLUDE(\"${HPHP_HOME}/CMake/HPHPFunctions.cmake\")
      HHVM_INSTALL_HEADERS(${TARGET}
      \"${CMAKE_CURRENT_SOURCE_DIR}/${SRCDIR}\"
      \"\${CMAKE_INSTALL_PREFIX}/include/hphp/third-party/${DEST}\"
      ${files})"
    COMPONENT dev)
endfunction()

foreach(MODULE ${THIRD_PARTY_MODULES})
  add_subdirectory(${MODULE})
  # Install headers here, rather than in the individual submodules, so that we
  # can easily control the destination. Put them in include/hphp/third-party.
  if(MODULE STREQUAL folly)
    TP_INSTALL_HEADERS(folly folly/src/folly folly)
  else()
    TP_INSTALL_HEADERS(${MODULE} ${MODULE} ${MODULE})
  endif()
endforeach()

if(NOT PCRE_LIBRARY)
  target_include_directories(pcre PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/pcre")
  target_compile_definitions(pcre PUBLIC "PCRE_STATIC=1")
endif()

set(THIRD_PARTY_INCLUDE_PATHS ${EXTRA_INCLUDE_PATHS} CACHE INTERNAL "" FORCE)

# boost checks
find_package(Boost 1.51.0 COMPONENTS context filesystem program_options regex system thread REQUIRED)
add_library(boost INTERFACE)
target_include_directories(boost INTERFACE ${Boost_INCLUDE_DIRS})
target_link_libraries(boost INTERFACE ${Boost_LIBRARIES})
