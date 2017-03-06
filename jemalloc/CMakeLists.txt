include(ExternalProject)

find_program(AUTOCONF autoconf)
if (NOT AUTOCONF)
  MESSAGE(FATAL_ERROR "autoconf not found")
endif()

ExternalProject_Add(
  jemalloc_sub
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
  CONFIGURE_COMMAND ${AUTOCONF}
    COMMAND ./configure --prefix=${CMAKE_CURRENT_BINARY_DIR}
  BUILD_COMMAND $(MAKE) all
  BUILD_IN_SOURCE 1
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
  INSTALL_COMMAND $(MAKE) install_bin install_include install_lib
)

add_library(jemalloc INTERFACE)
add_dependencies(jemalloc jemalloc_sub)
target_include_directories(jemalloc INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/include)
target_link_libraries(jemalloc INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/lib/libjemalloc.a pthread)
