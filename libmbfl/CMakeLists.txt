cmake_minimum_required(VERSION 2.6)
project(libmbfl C CXX)

include(CheckIncludeFiles)
include(CheckFunctionExists)

MACRO(MBFL_CHECK_INCLUDE include_file)
	string(REGEX REPLACE "[./]"
	         "_" _include_var ${include_file})
	string(TOUPPER "HAVE_${_include_var}" _include_var)

	CHECK_INCLUDE_FILES("${include_file}" ${_include_var})
	IF(NOT ${_include_var})
		message(STATUS "Checking for ${include_file} - failed")
	ENDIF()
ENDMACRO()

MBFL_CHECK_INCLUDE("stdio.h")
MBFL_CHECK_INCLUDE("stdlib.h")
MBFL_CHECK_INCLUDE("stddef.h")
MBFL_CHECK_INCLUDE("assert.h")
MBFL_CHECK_INCLUDE("memory.h")
MBFL_CHECK_INCLUDE("strings.h")
MBFL_CHECK_INCLUDE("string.h")


CHECK_FUNCTION_EXISTS("strcasecmp" HAVE_STRCASECMP)
CHECK_FUNCTION_EXISTS("strchr" HAVE_STRCHR)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_definitions(-DHAVE_CONFIG_H=1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mbfl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/nls)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/filters)

add_subdirectory(nls)
add_subdirectory(filters)
add_subdirectory(mbfl)