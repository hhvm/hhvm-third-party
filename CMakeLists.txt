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

include(HPHPSetup)
include(FollySetup)

add_definitions("-DHHVM")

set(THIRD_PARTY_MODULES)
set(THIRD_PARTY_HEADERS)

list(APPEND THIRD_PARTY_MODULES
  pcre
  fastlz
  libafdt
  libmbfl
  libsqlite3
  timelib
  lz4
  double-conversion
  folly
  libzip)
if(ENABLE_FASTCGI)
  list(APPEND THIRD_PARTY_MODULES proxygen)
  list(APPEND THIRD_PARTY_MODULES thrift)
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
  elseif(MODULE STREQUAL double-conversion)
    TP_INSTALL_HEADERS(double-conversion double-conversion/src double-conversion)
  else()
    TP_INSTALL_HEADERS(${MODULE} ${MODULE} ${MODULE})
  endif()
endforeach()
