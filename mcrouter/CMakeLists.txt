set(CXX_SOURCES)
auto_sources(files "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/mcrouter")
foreach (file ${files})
  if (${file} MATCHES "(/(test)/|Test.cpp$)")
    list(REMOVE_ITEM files ${file})
  endif()
endforeach()
list(APPEND CXX_SOURCES ${files})

add_definitions(-DNO_LIB_GFLAGS)
add_definitions(-DLIBMC_FBTRACE_DISABLE)
add_definitions(-DHAVE_CONFIG_H)

find_package(Boost 1.48.0 COMPONENTS context regex system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories("${HPHP_HOME}/third-party")
include_directories("${HPHP_HOME}/third-party/mcrouter/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
add_library(mcrouter STATIC ${CXX_SOURCES})

target_link_libraries(mcrouter ${Boost_LIBRARIES})
