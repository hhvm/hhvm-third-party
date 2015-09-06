set(CXX_SOURCES)
set(HEADER_SOURCES)
auto_sources(files "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/lib")
auto_sources(hfiles "*.h" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/lib")
HHVM_REMOVE_MATCHES_FROM_LISTS(files hfiles
  MATCHES "/test/" "/lib/utils/(Null)?TraceEvent")
list(APPEND CXX_SOURCES ${files})
list(APPEND HEADER_SOURCES ${hfiles})
list(APPEND CXX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/external/http_parser/http_parser_cpp.cpp")
list(APPEND CXX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lib/http/HTTPCommonHeaders.cpp")
list(APPEND CXX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lib/http/HTTPCommonHeaders.h")

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lib/http/HTTPCommonHeaders.h
  COMMAND HEADERS_LIST=${CMAKE_CURRENT_SOURCE_DIR}/lib/http/HTTPCommonHeaders.txt FBCODE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/.. INSTALL_DIR=${CMAKE_CURRENT_SOURCE_DIR}/lib/http ${CMAKE_CURRENT_SOURCE_DIR}/lib/http/gen_HTTPCommonHeaders.h.sh
)
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lib/http/HTTPCommonHeaders.cpp
  COMMAND HEADERS_LIST=${CMAKE_CURRENT_SOURCE_DIR}/lib/http/HTTPCommonHeaders.txt FBCODE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/.. INSTALL_DIR=${CMAKE_CURRENT_SOURCE_DIR}/lib/http ${CMAKE_CURRENT_SOURCE_DIR}/lib/http/gen_HTTPCommonHeaders.cpp.sh
)

add_definitions(-DNO_LIB_GFLAGS)

find_package(Boost 1.48.0 COMPONENTS thread system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories("${HPHP_HOME}/third-party")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
add_library(hphp_proxygen STATIC ${CXX_SOURCES} ${HEADER_SOURCES})
auto_source_group("hphp_proxygen" "${CMAKE_CURRENT_SOURCE_DIR}/src/proxygen"
  ${CXX_SOURCES} ${HEADER_SOURCES})
target_link_libraries(hphp_proxygen wangle ${Boost_LIBRARIES}
                                           ${LIBGLOG_LIBRARY}
                                           ${LIBPTHREAD_LIBRARIES})
