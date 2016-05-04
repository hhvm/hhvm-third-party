include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/aapl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/ragel)

file(GLOB_RECURSE AAPLP_HEADER_FILES "src/aapl/*.h")
file(GLOB_RECURSE HEADER_FILES "src/ragel/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/ragel/*.cpp")

if(CMAKE_VERSION VERSION_LESS "2.8.12")
    function(add_compile_options)
        add_definitions(${ARGN})
    endfunction(add_compile_options)
endif()

add_compile_options(-Wno-overloaded-virtual -Wno-narrowing -Wno-init-self -Wno-unused-but-set-variable)
add_executable(ragel ${AAPLP_HEADER_FILES} ${HEADER_FILES} ${SOURCE_FILES})
auto_source_group("Ragel" ${CMAKE_CURRENT_SOURCE_DIR} ${AAPLP_HEADER_FILES} ${HEADER_FILES} ${SOURCE_FILES})
