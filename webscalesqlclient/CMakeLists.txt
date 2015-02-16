cmake_minimum_required(VERSION 2.8.0)
include(ExternalProject)
ExternalProject_Add(
  webscalesqlclient
  SOURCE_DIR webscalesql-5.6/
  CMAKE_ARGS -DWITHOUT_SERVER=TRUE -DDISABLE_SHARED=TRUE
  BUILD_COMMAND $(MAKE) -C libmysql
  PREFIX build
  BUILD_IN_SOURCE true
  INSTALL_COMMAND ""
)
