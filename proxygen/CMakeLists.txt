set(CXX_SOURCES)
auto_sources(files "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/lib")
foreach (file ${files})
  if (${file} MATCHES "/(test|http)/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/lib/utils/(Null)?TraceEvent")
    list(REMOVE_ITEM files ${file})
  endif()
endforeach()
list(APPEND CXX_SOURCES ${files})
list(APPEND CXX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/external/http_parser/http_parser_cpp.cpp")

add_definitions(-DNO_LIB_GFLAGS)

find_package(Boost 1.48.0 COMPONENTS thread system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories("${HPHP_HOME}/third-party")
include_directories("${HPHP_HOME}/third-party/thrift/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
add_library(hphp_proxygen STATIC ${CXX_SOURCES})

add_dependencies(hphp_proxygen hphp_thrift)
target_link_libraries(hphp_proxygen hphp_thrift
                                    ${Boost_LIBRARIES}
                                    ${LIBGLOG_LIBRARY}
                                    ${LIBPTHREAD_LIBRARIES})
