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

set(C_SOURCES)
auto_sources(files "*.c" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/mcrouter")
foreach (file ${files})
  if (${file} MATCHES "/(test|examples)/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/mc_fbtrace_info.c$")
    list(REMOVE_ITEM files ${file})
  endif()
endforeach()
# ascii_client.c is generated from lib/mc/ascii_client.rl using ragel
list(APPEND C_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ascii_client.c")
list(APPEND C_SOURCES ${files})

set(CXX_SOURCES)
auto_sources(files "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/mcrouter")
foreach (file ${files})
  if (${file} MATCHES "(/(test|examples)/|Test.cpp$)")
    list(REMOVE_ITEM files ${file})
  endif()
endforeach()
# McAsciiParser-gen.cpp is generated from mcrouter/lib/network/McAsciiParser.rl
# using ragel
# So ran the command found in mcrouter/Makefile.am manually and put the file
# here -- this avoids linking errors
list(APPEND CXX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/McAsciiParser-gen.cpp")
list(APPEND CXX_SOURCES ${files})

# We need to make sure several files are the same
macro(WRITE_IMPL_FILE dirName sourceName)
  # These were previously symlinks, causing issues when trying to
  # install the headers, so, if it's either a symlink, or it doesn't
  # exist, create it.
  if (IS_SYMLINK "${dirName}/${sourceName}.h")
    file(REMOVE "${dirName}/${sourceName}.h")
  endif()
  if (NOT EXISTS "${dirName}/${sourceName}.h")
    file(WRITE "${dirName}/${sourceName}.h" "#include \"${sourceName}Impl.h\"")
  endif()
endmacro()
WRITE_IMPL_FILE("${CMAKE_CURRENT_SOURCE_DIR}/mcrouter/lib/network/" "CaretReplyConverter")
WRITE_IMPL_FILE("${CMAKE_CURRENT_SOURCE_DIR}/mcrouter/lib/network/" "CaretSerializedMessage")
WRITE_IMPL_FILE("${CMAKE_CURRENT_SOURCE_DIR}/mcrouter/" "ServerOnRequest")

add_definitions(-DNO_LIB_GFLAGS)
add_definitions(-DLIBMC_FBTRACE_DISABLE)
add_definitions(-DHAVE_CONFIG_H)

find_package(Boost 1.51.0 COMPONENTS context regex system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories("${HPHP_HOME}/third-party")
include_directories("${HPHP_HOME}/third-party/mcrouter/")
#include_directories("${HPHP_HOME}/third-party/mcrouter/mcrouter/lib/fbi")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
add_library(mcrouter STATIC ${C_SOURCES} ${CXX_SOURCES})
target_link_libraries(mcrouter folly ${Boost_LIBRARIES})
