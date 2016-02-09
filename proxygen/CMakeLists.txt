set(CXX_SOURCES)
auto_sources(files "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/lib")
foreach (file ${files})
  if (${file} MATCHES "/test/")
    list(REMOVE_ITEM files ${file})
  endif()
  if (${file} MATCHES "/lib/utils/(Null)?TraceEvent")
    list(REMOVE_ITEM files ${file})
  endif()
endforeach()
list(APPEND CXX_SOURCES ${files})
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
if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
endif()
add_library(hphp_proxygen STATIC ${CXX_SOURCES})
target_link_libraries(hphp_proxygen wangle ${Boost_LIBRARIES}
                                           ${LIBGLOG_LIBRARY}
                                           ${LIBPTHREAD_LIBRARIES})
