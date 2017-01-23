set(ZSTD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/lib")

set(C_SOURCES)
auto_sources(files "*.c" "RECURSE" "${ZSTD_DIR}")
list(APPEND C_SOURCES ${files})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_library(zstd STATIC ${C_SOURCES})
