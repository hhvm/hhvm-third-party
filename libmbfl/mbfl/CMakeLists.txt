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
execute_process(
  COMMAND ${AWK_EXECUTABLE} -v TABLE_NAME=mbfl_eaw_table -f mk_eaw_tbl.awk EastAsianWidth.txt
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/mbfl/eaw_table.h
)
