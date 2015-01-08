# Require gawk because of use of strtonum which wasn't used before
FIND_PROGRAM(AWK_EXECUTABLE NAMES gawk)

IF(NOT AWK_EXECUTABLE)
  MESSAGE(FATAL_ERROR "HHVM requires gawk for libmbfl")
ENDIF()

SET(mbfl_files mbfilter.c mbfl_string.c mbfl_language.c mbfl_encoding.c mbfl_convert.c
mbfl_ident.c mbfl_memory_device.c mbfl_allocators.c mbfl_filter_output.c
mbfilter_pass.c mbfilter_wchar.c mbfilter_8bit.c)

add_library(mbfl STATIC ${mbfl_files} ${mbfl_filters_files} ${mbfl_nls_files})

# Generate eaw_table.h
add_custom_target(
  eaw_table
  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/mk_eaw_tbl.awk" "${CMAKE_CURRENT_SOURCE_DIR}/EastAsianWidth.txt"
  COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/generate-eaw-table.sh ${AWK_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR} 
)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/eaw_table.h")
add_dependencies(mbfl eaw_table)
