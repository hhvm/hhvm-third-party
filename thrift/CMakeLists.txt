set(THRIFT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/thrift")

set(CXX_SOURCES)
set(HEADER_SOURCES)
auto_sources(files "*.cpp" "RECURSE" "${THRIFT_DIR}")
auto_sources(hfiles "*.h" "RECURSE" "${THRIFT_DIR}")
HHVM_REMOVE_MATCHES_FROM_LISTS(files hfiles MATCHES
  "/perf/" "/test/" "/tests/"
  "/cpp2/" "/lib/d/" "/lib/node/"
  "/lib/py/" "/lib/php/" "/tutorial/"
  "/example/" "Test.cpp" "/neutronium/"
  "/protocol/"
)

list(REMOVE_ITEM files
  ${THRIFT_DIR}/contrib/thrift_dump.cpp
  ${THRIFT_DIR}/lib/cpp/transport/HDFS.cpp
  ${THRIFT_DIR}/lib/cpp/transport/THDFSFileTransport.cpp
  ${THRIFT_DIR}/lib/cpp/transport/THeaderTransport.cpp
  ${THRIFT_DIR}/lib/cpp/transport/TMemPagedTransport.cpp
  ${THRIFT_DIR}/lib/cpp/transport/TMemPagedFactory.cpp
  ${THRIFT_DIR}/lib/cpp/transport/THeader.cpp
  ${THRIFT_DIR}/lib/cpp/protocol/TSimpleJSONProtocol.cpp
  ${THRIFT_DIR}/lib/cpp/concurrency/NumaThreadManager.cpp
  ${THRIFT_DIR}/lib/cpp/util/TThreadedServerCreator.cpp
  ${THRIFT_DIR}/lib/cpp/util/TNonblockingServerCreator.cpp
)

list(REMOVE_ITEM hfiles
  ${THRIFT_DIR}/lib/cpp/transport/HDFS.h
  ${THRIFT_DIR}/lib/cpp/transport/THDFSFileTransport.h
  ${THRIFT_DIR}/lib/cpp/transport/THeaderTransport.h
  ${THRIFT_DIR}/lib/cpp/transport/TMemPagedTransport.h
  ${THRIFT_DIR}/lib/cpp/transport/TMemPagedFactory.h
  ${THRIFT_DIR}/lib/cpp/transport/THeader.h
  ${THRIFT_DIR}/lib/cpp/protocol/TSimpleJSONProtocol.h
  ${THRIFT_DIR}/lib/cpp/concurrency/NumaThreadManager.h
  ${THRIFT_DIR}/lib/cpp/util/TThreadedServerCreator.h
  ${THRIFT_DIR}/lib/cpp/util/TNonblockingServerCreator.h
)

list(APPEND CXX_SOURCES ${files})
list(APPEND HEADER_SOURCES ${hfiles})

add_definitions(-DNO_LIB_GFLAGS)

find_package(Boost 1.48.0 COMPONENTS thread system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories("${HPHP_HOME}/third-party")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_library(hphp_thrift STATIC ${CXX_SOURCES} ${HEADER_SOURCES})
auto_source_group("hphp_thrift" "${THRIFT_DIR}/lib/cpp"
  ${CXX_SOURCES} ${HEADER_SOURCES})
target_link_libraries(hphp_thrift wangle ${Boost_LIBRARIES}
                                         ${LIBGLOG_LIBRARY}
                                         ${LIBPTHREAD_LIBRARIES})
