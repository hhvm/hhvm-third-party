cmake_minimum_required(VERSION 2.8.0)

set(MVFST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Needed for fcntl w/ F_SETPIPE_SZ
add_definitions("-D_GNU_SOURCE")

add_definitions(-DNO_LIB_GFLAGS)

# Main mvfst library files
auto_sources(files "*.cpp" "RECURSE" "${MVFST_DIR}/quic")
auto_sources(hfiles "*.h" "RECURSE" "${MVFST_DIR}/quic")
HHVM_REMOVE_MATCHES_FROM_LISTS(files hfiles MATCHES "/test/" "/samples/")

add_library(mvfst STATIC ${files} ${hfiles})
auto_source_group(mvfst "${MVFST_DIR}" ${files} ${hfiles})
include_directories("${TP_DIR}/fizz/src" "${MVFST_DIR}")

add_dependencies(mvfst libsodiumMaybeBuild)
target_include_directories(mvfst PUBLIC "${LIBSODIUM_INCLUDE_DIRS}")
target_link_libraries(mvfst folly boost fizz libsodium)
