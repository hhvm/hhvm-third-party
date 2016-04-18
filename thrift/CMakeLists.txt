set(THRIFT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/thrift")

set(CXX_SOURCES)

auto_sources(files "*.cpp" "RECURSE" "${THRIFT_DIR}")

HHVM_REMOVE_MATCHES_FROM_LISTS(files MATCHES
  "/perf/"
  "/test/"
  "/tests/"
  "/lib/d/"
  "/lib/node/"
  "/lib/cpp2/(security|async|server)/"
  "/lib/py/"
  "/lib/php/"
  "/tutorial/"
  "/example/"
  "Test.cpp"
  "/neutronium/"
  "/kerberos/"
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

list(APPEND CXX_SOURCES ${files})

auto_sources(files "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/gen")
list(APPEND CXX_SOURCES ${files})

find_package(Boost 1.48.0 COMPONENTS thread system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories("${HPHP_HOME}/third-party")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/gen")
add_library(hphp_thrift STATIC ${CXX_SOURCES})

target_link_libraries(hphp_thrift wangle ${Boost_LIBRARIES}
                                         ${LIBGLOG_LIBRARY}
                                         ${LIBPTHREAD_LIBRARIES})
