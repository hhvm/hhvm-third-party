set(C_SOURCES)
auto_sources(files "*.c" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/mcrouter")
foreach (file ${files})
  if (${file} MATCHES "/(test|examples?)/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/mc_fbtrace_info.c$")
    list(REMOVE_ITEM files ${file})
  endif()

endforeach()
list(APPEND C_SOURCES ${files})

set(CXX_SOURCES)
auto_sources(files "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/mcrouter")
foreach (file ${files})
  if (${file} MATCHES "(/(test|examples?)/|Test.cpp$)")
    list(REMOVE_ITEM files ${file})
  endif()
endforeach()
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mcrouter/lib/network/McAsciiParser-gen.cpp
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/mcrouter/lib/network/McAsciiParser.rl
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/mcrouter/lib/network
  COMMAND ragel -G1 -o ${CMAKE_CURRENT_BINARY_DIR}/mcrouter/lib/network/McAsciiParser-gen.cpp ${CMAKE_CURRENT_SOURCE_DIR}/mcrouter/lib/network/McAsciiParser.rl
  COMMENT "Generating McAsciiParser-gen.cpp")
list(APPEND CXX_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/mcrouter/lib/network/McAsciiParser-gen.cpp")
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
WRITE_IMPL_FILE("${CMAKE_CURRENT_SOURCE_DIR}/mcrouter/lib/network/" "CaretSerializedMessage")
WRITE_IMPL_FILE("${CMAKE_CURRENT_SOURCE_DIR}/mcrouter/" "ServerOnRequest")

add_definitions(-DNO_LIB_GFLAGS)
add_definitions(-DLIBMC_FBTRACE_DISABLE)
add_definitions(-DHAVE_CONFIG_H)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/..")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
#include_directories("${HPHP_HOME}/third-party/mcrouter/mcrouter/lib/fbi")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
add_library(mcrouter STATIC ${C_SOURCES} ${CXX_SOURCES})
target_link_libraries(mcrouter folly hphp_thrift boost)
