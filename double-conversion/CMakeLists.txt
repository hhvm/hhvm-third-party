auto_sources(CXX_SOURCES "*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/src/double-conversion")
auto_sources(HEADER_SOURCES "*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/double-conversion")
add_library(double-conversion STATIC ${CXX_SOURCES} ${HEADER_SOURCES})
auto_source_group("double-conversion"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/double-conversion"
  ${CXX_SOURCES} ${HEADER_SOURCES}
)
