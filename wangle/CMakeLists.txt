cmake_minimum_required(VERSION 2.8.0)

set(WANGLE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/wangle")
set(FOLLY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../folly/src/folly")

# Needed for fcntl w/ F_SETPIPE_SZ
add_definitions("-D_GNU_SOURCE")

add_definitions(-DNO_LIB_GFLAGS)

# Ensure that we are either getting malloc functions
# like malloc_usable_size() from either malloc.h
# or stdlib.h. Default is stdlib.h
INCLUDE(CheckCXXSourceCompiles)
CHECK_CXX_SOURCE_COMPILES("#include <malloc.h>
int main() {
  return 0;
}" FOLLY_MALLOC)
if (FOLLY_MALLOC)
  add_definitions("-DFOLLY_HAVE_MALLOC_H=1")
else()
  add_definitions("-DFOLLY_HAVE_MALLOC_H=0")
endif()

# Main wangle library files
auto_sources(files "*.cpp" "RECURSE" "${WANGLE_DIR}")

# No need for tests, Benchmarks, Utils, or most experimental stuff
foreach (file ${files})
  if (${file} MATCHES "/test/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "Test.cpp$")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/example/")
    list(REMOVE_ITEM files ${file})
  endif()
endforeach()

list(REMOVE_ITEM files
  ${WANGLE_DIR}/bootstrap/ServerBootstrap.cpp
  ${WANGLE_DIR}/channel/FileRegion.cpp
)

add_library(wangle STATIC ${files})

find_package(Boost 1.51.0 COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
link_directories(${OPENSSL_LIBRARIES})

include_directories(${FOLLY_DIR})

target_link_libraries(wangle folly ${Boost_LIBRARIES}
                                   ${OPENSSL_LIBRARIES})
