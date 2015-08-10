add_library(fastlz STATIC fastlz.c fastlz.h)
auto_source_group("fastlz" "${CMAKE_CURRENT_SOURCE_DIR}" fastlz.c fastlz.h)
