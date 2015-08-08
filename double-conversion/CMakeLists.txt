auto_sources(files "*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/src/double-conversion")
add_library(double-conversion STATIC ${files})
