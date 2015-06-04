cmake_minimum_required(VERSION 2.8.0)
include(ExternalProject)
ExternalProject_Add(
  webscalesqlclient
  SOURCE_DIR webscalesql-5.6/
  CMAKE_ARGS
  -DWITHOUT_SERVER=TRUE
  -DDISABLE_SHARED=TRUE
  -DCMAKE_C_FLAGS=-Wno-maybe-uninitialized ${CMAKE_C_FLAGS}
  -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
  -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
  -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
  BUILD_COMMAND $(MAKE) -C libmysql
  PREFIX build
  BUILD_IN_SOURCE true
  INSTALL_COMMAND ""
)
