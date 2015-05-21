set(PROXYGEN_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/proxygen/lib")
set(PROXYGEN_EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/proxygen/external")

set(CXX_SOURCES)
auto_sources(files "*.cpp" "RECURSE" "${PROXYGEN_LIB_DIR}")
foreach (file ${files})
  if (${file} MATCHES "/test/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/lib/utils/(Null)?TraceEvent")
    list(REMOVE_ITEM files ${file})
  endif()
endforeach()
list(APPEND CXX_SOURCES ${files})
list(APPEND CXX_SOURCES "${PROXYGEN_EXTERNAL_DIR}/http_parser/http_parser_cpp.cpp")
list(APPEND CXX_SOURCES "${PROXYGEN_LIB_DIR}/http/HTTPCommonHeaders.cpp")
list(APPEND CXX_SOURCES "${PROXYGEN_LIB_DIR}/http/HTTPCommonHeaders.h")

add_custom_command(
  OUTPUT ${PROXYGEN_LIB_DIR}/http/HTTPCommonHeaders.h
  COMMAND HEADERS_LIST=${PROXYGEN_LIB_DIR}/http/HTTPCommonHeaders.txt FBCODE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/.. INSTALL_DIR=${PROXYGEN_LIB_DIR}/http ${PROXYGEN_LIB_DIR}/http/gen_HTTPCommonHeaders.h.sh
)
add_custom_command(
  OUTPUT ${PROXYGEN_LIB_DIR}/http/HTTPCommonHeaders.cpp
  COMMAND HEADERS_LIST=${PROXYGEN_LIB_DIR}/http/HTTPCommonHeaders.txt FBCODE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/.. INSTALL_DIR=${PROXYGEN_LIB_DIR}/http ${PROXYGEN_LIB_DIR}/http/gen_HTTPCommonHeaders.cpp.sh
)

add_definitions(-DNO_LIB_GFLAGS)

find_package(Boost 1.48.0 COMPONENTS thread system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories("${HPHP_HOME}/third-party")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
add_library(hphp_proxygen STATIC ${CXX_SOURCES})
target_link_libraries(hphp_proxygen ${Boost_LIBRARIES}
                                    ${LIBGLOG_LIBRARY}
                                    ${LIBPTHREAD_LIBRARIES})
