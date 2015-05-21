set(THRIFT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/thrift")

set(CXX_SOURCES)

auto_sources(files "*.cpp" "RECURSE" "${THRIFT_DIR}")

foreach (file ${files})
  if (${file} MATCHES "/perf/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/test/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/tests/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/cpp2/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/lib/d/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/lib/node/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/lib/py/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/lib/php/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/tutorial/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/example/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "Test.cpp")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/neutronium/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/protocol/")
    list(REMOVE_ITEM files ${file})
  endif()
endforeach()

list(REMOVE_ITEM files
  ${THRIFT_DIR}/lib/cpp/transport/HDFS.cpp
  ${THRIFT_DIR}/lib/cpp/transport/THDFSFileTransport.cpp
  ${THRIFT_DIR}/lib/cpp/transport/THeaderTransport.cpp
  ${THRIFT_DIR}/lib/cpp/transport/TMemPagedTransport.cpp
  ${THRIFT_DIR}/lib/cpp/transport/TMemPagedFactory.cpp
  ${THRIFT_DIR}/lib/cpp/transport/THeader.cpp
  ${THRIFT_DIR}/lib/cpp/protocol/TSimpleJSONProtocol.cpp
  ${THRIFT_DIR}/lib/cpp/concurrency/NumaThreadManager.cpp
)

list(APPEND CXX_SOURCES ${files})

add_definitions(-DNO_LIB_GFLAGS)

find_package(Boost 1.48.0 COMPONENTS thread system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories("${HPHP_HOME}/third-party")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_library(hphp_thrift STATIC ${CXX_SOURCES})

target_link_libraries(hphp_thrift ${Boost_LIBRARIES}
                                  ${LIBGLOG_LIBRARY}
                                  ${LIBPTHREAD_LIBRARIES})
