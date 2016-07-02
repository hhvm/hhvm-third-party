set(FOLLY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/folly")

# Needed for fcntl w/ F_SETPIPE_SZ
add_definitions("-D_GNU_SOURCE")

# Ensure that we are either getting malloc functions
# like malloc_usable_size() from either malloc.h
# or stdlib.h. Default is stdlib.h
INCLUDE(CheckCXXSourceCompiles)
CHECK_CXX_SOURCE_COMPILES("#include <malloc.h>
int main() {
  return 0;
}" FOLLY_MALLOC)
if (FOLLY_MALLOC)
  add_definitions("-DFOLLY_HAVE_MALLOC_H=1")
else()
  add_definitions("-DFOLLY_HAVE_MALLOC_H=0")
endif()

if (NOT EXISTS "${FOLLY_DIR}/Portability.h")
  message(FATAL_ERROR "${FOLLY_DIR}/Portability.h missing, did you forget to "
                      "run `git submodule update --init --recursive`?")
endif()

# Generated files from folly/build/generate_*.py
auto_sources(genfiles "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/gen")

# Main folly library files
auto_sources(files "*.cpp" "RECURSE" "${FOLLY_DIR}")
auto_sources(cfiles "*.c" "RECURSE" "${FOLLY_DIR}")
auto_sources(hfiles "*.h" "RECURSE" "${FOLLY_DIR}")

# No need for tests, Benchmarks, Utils, or most experimental stuff
HHVM_REMOVE_MATCHES_FROM_LISTS(files cfiles hfiles MATCHES "/test/" "Test.cpp$" "/futures/exercises/")
list(REMOVE_ITEM files
  ${FOLLY_DIR}/Benchmark.cpp
  ${FOLLY_DIR}/SingletonStackTrace.cpp
  ${FOLLY_DIR}/build/GenerateFingerprintTables.cpp
  ${FOLLY_DIR}/experimental/DynamicParser.cpp
  ${FOLLY_DIR}/experimental/JSONSchemaTester.cpp
  ${FOLLY_DIR}/experimental/RCUUtils.cpp
  ${FOLLY_DIR}/experimental/ProgramOptions.cpp
  ${FOLLY_DIR}/experimental/Select64.cpp
  ${FOLLY_DIR}/experimental/TestUtil.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionCounterLib.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionStackTraceLib.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionTracer.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionTracerBenchmark.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionTracerLib.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/StackTrace.cpp
  ${FOLLY_DIR}/experimental/io/AsyncIO.cpp
  ${FOLLY_DIR}/experimental/io/HugePageUtil.cpp
  ${FOLLY_DIR}/experimental/symbolizer/StackTrace.cpp
  ${FOLLY_DIR}/experimental/symbolizer/ElfCache.cpp
  ${FOLLY_DIR}/experimental/symbolizer/ElfUtil.cpp
  ${FOLLY_DIR}/experimental/symbolizer/SignalHandler.cpp
  ${FOLLY_DIR}/init/Init.cpp
  # io/Compression requires snappy library
  # Don't add dep until we need it
  ${FOLLY_DIR}/io/Compression.cpp
)
list(REMOVE_ITEM hfiles
  ${FOLLY_DIR}/Benchmark.h
  ${FOLLY_DIR}/experimental/DynamicParser.h
  ${FOLLY_DIR}/experimental/DynamicParser-inl.h
  ${FOLLY_DIR}/experimental/RCUUtils.h
  ${FOLLY_DIR}/experimental/ProgramOptions.h
  ${FOLLY_DIR}/experimental/TestUtil.h
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionAbi.h
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionCounterLib.h
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionTracer.h
  ${FOLLY_DIR}/experimental/exception_tracer/StackTrace.h
  ${FOLLY_DIR}/experimental/io/AsyncIO.h
  ${FOLLY_DIR}/experimental/symbolizer/StackTrace.h
  ${FOLLY_DIR}/experimental/symbolizer/ElfCache.h
  ${FOLLY_DIR}/experimental/symbolizer/SignalHandler.h
  ${FOLLY_DIR}/init/Init.h
  # io/Compression requires snappy library
  # Don't add dep until we need it
  ${FOLLY_DIR}/io/Compression.h
)

CHECK_CXX_SOURCE_COMPILES("#include <bits/functexcept.h>
int main() {
  return 0;
}" FOLLY_FUNCTEXCEPT)
if (FOLLY_FUNCTEXCEPT)
  list(REMOVE_ITEM files ${FOLLY_DIR}/detail/FunctionalExcept.cpp)
  list(REMOVE_ITEM hfiles ${FOLLY_DIR}/detail/FunctionalExcept.h)
endif()

if (LINUX)
  list(REMOVE_ITEM files ${FOLLY_DIR}/detail/Clock.cpp)
  list(REMOVE_ITEM hfiles ${FOLLY_DIR}/detail/Clock.h)
else()
  # Remove non-portable items
  list(REMOVE_ITEM files
    ${FOLLY_DIR}/experimental/symbolizer/Dwarf.cpp
    ${FOLLY_DIR}/experimental/symbolizer/Elf.cpp
    ${FOLLY_DIR}/experimental/symbolizer/LineReader.cpp
    ${FOLLY_DIR}/experimental/symbolizer/Symbolizer.cpp
  )
  list(REMOVE_ITEM hfiles
    ${FOLLY_DIR}/experimental/symbolizer/Dwarf.h
    ${FOLLY_DIR}/experimental/symbolizer/Elf.h
    ${FOLLY_DIR}/experimental/symbolizer/Elf-inl.h
    ${FOLLY_DIR}/experimental/symbolizer/LineReader.h
    ${FOLLY_DIR}/experimental/symbolizer/Symbolizer.h
  )

  if (WINDOWS)
    list(REMOVE_ITEM files ${FOLLY_DIR}/Subprocess.cpp)
    list(REMOVE_ITEM hfiles ${FOLLY_DIR}/Subprocess.h)
  endif()
endif()

add_library(folly STATIC ${files} ${genfiles} ${cfiles} ${hfiles})
auto_source_group(folly ${FOLLY_DIR} ${files} ${genfiles} ${cfiles} ${hfiles})

find_package(Boost 1.51.0 COMPONENTS system program_options filesystem regex
             context REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

find_package(Glog REQUIRED)
include_directories(${LIBGLOG_INCLUDE_DIR})

find_package(PThread REQUIRED)
include_directories(${LIBPTHREAD_INCLUDE_DIRS})

target_link_libraries(folly ${Boost_LIBRARIES}
                            ${LIBGLOG_LIBRARY}
                            ${LIBPTHREAD_LIBRARIES})

if (DOUBLE_CONVERSION_LIBRARY)
  target_link_libraries(folly ${DOUBLE_CONVERSION_LIBRARY})
else()
  target_link_libraries(folly double-conversion)
endif()

if (JEMALLOC_ENABLED)
  target_link_libraries(folly ${JEMALLOC_LIB})
endif()

# For some reason we aren't making a folly-config.h and this is in there.
# Please fix properly!
add_definitions("-DFOLLY_VERSION=\"0.1\"")
