add_library(googletest STATIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src/googletest/src/gtest-all.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/googletest/src/gtest_main.cc"
  )
target_include_directories(googletest PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src/googletest")
target_include_directories(googletest PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src/googletest/include")
