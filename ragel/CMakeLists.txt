include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/aapl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/ragel)

file(GLOB_RECURSE AAPLP_HEADER_FILES "src/aapl/*.h")
file(GLOB_RECURSE HEADER_FILES "src/ragel/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/ragel/*.cpp")

add_executable(ragel ${AAPLP_HEADER_FILES} ${HEADER_FILES} ${SOURCE_FILES})
auto_source_group("Ragel" ${CMAKE_CURRENT_SOURCE_DIR} ${AAPLP_HEADER_FILES} ${HEADER_FILES} ${SOURCE_FILES})
