set(FOLLY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/folly")

# Ensure that we are either getting malloc functions
# like malloc_usable_size() from either malloc.h
# or stdlib.h. Default is stdlib.h
INCLUDE(CheckCXXSourceCompiles)
CHECK_CXX_SOURCE_COMPILES("#include <folly/Malloc.h>
int main() {
  return 0;
}" FOLLY_MALLOC)
if (NOT FOLLY_MALLOC)
  add_definitions("-DFOLLY_HAVE_MALLOC_H=1")
endif()

if (NOT EXISTS "${FOLLY_DIR}/Portability.h")
  message(FATAL_ERROR "${FOLLY_DIR}/Portability.h missing, did you forget to "
                      "run `git submodule update --init --recursive`?")
endif()

add_definitions(-DNO_LIB_GFLAGS)

# Generated files from folly/build/generate_*.py
auto_sources(genfiles "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}/gen")

# Main folly library files
auto_sources(files "*.cpp" "RECURSE" "${FOLLY_DIR}")
auto_sources(cfiles "*.c" "RECURSE" "${FOLLY_DIR}")

# No need for tests, Benchmarks, Utils, or most experimental stuff
foreach (file ${files})
  if (${file} MATCHES "/test/")
    list(REMOVE_ITEM files ${file})
  endif()
endforeach()
list(REMOVE_ITEM files
  ${FOLLY_DIR}/Benchmark.cpp
  ${FOLLY_DIR}/build/GenerateFingerprintTables.cpp
  ${FOLLY_DIR}/detail/Clock.cpp
  ${FOLLY_DIR}/detail/FunctionalExcept.cpp
  ${FOLLY_DIR}/experimental/File.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionTracer.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionTracerBenchmark.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionTracerLib.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/ExceptionTracerTest.cpp
  ${FOLLY_DIR}/experimental/exception_tracer/StackTrace.cpp
  ${FOLLY_DIR}/experimental/io/AsyncIO.cpp
  ${FOLLY_DIR}/experimental/io/HugePageUtil.cpp
  ${FOLLY_DIR}/experimental/io/IOBufQueue.cpp
  ${FOLLY_DIR}/experimental/SingletonStackTrace.cpp
  ${FOLLY_DIR}/experimental/symbolizer/StackTrace.cpp
  ${FOLLY_DIR}/experimental/symbolizer/ElfCache.cpp
  ${FOLLY_DIR}/experimental/symbolizer/ElfUtil.cpp
  ${FOLLY_DIR}/experimental/symbolizer/SignalHandler.cpp
  ${FOLLY_DIR}/wangle/bootstrap/BootstrapTest.cpp
  ${FOLLY_DIR}/wangle/codec/CodecTest.cpp
  ${FOLLY_DIR}/wangle/service/ServiceTest.cpp
  )

# Remove non-portable items
if (NOT LINUX)
  list(REMOVE_ITEM files
    ${FOLLY_DIR}/experimental/symbolizer/Symbolizer.cpp
    ${FOLLY_DIR}/experimental/symbolizer/Dwarf.cpp
    ${FOLLY_DIR}/experimental/symbolizer/Elf.cpp
    )
endif()

# Subprocess requires flatmap from boost 1.48
# and some other folly pieces we're not including yet
# For now, that's not actually a requirement, so skip it
list(REMOVE_ITEM files ${FOLLY_DIR}/Subprocess.cpp)

# io/Compression requires snappy library
# Don't add dep until we need it
list(REMOVE_ITEM files ${FOLLY_DIR}/io/Compression.cpp)

add_library(folly STATIC ${files} ${genfiles} ${cfiles} )

find_package(Boost 1.48.0 COMPONENTS system program_options filesystem regex
             REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

find_package(Glog REQUIRED)
include_directories(${LIBGLOG_INCLUDE_DIR})

find_package(PThread REQUIRED)
include_directories(${LIBPTHREAD_INCLUDE_DIRS})

target_link_libraries(folly ${Boost_LIBRARIES}
                            ${LIBGLOG_LIBRARY}
                            ${LIBPTHREAD_LIBRARIES})

if (JEMALLOC_ENABLED)
  target_link_libraries(folly ${JEMALLOC_LIB})
endif()

# For some reason we aren't making a folly-config.h and this is in there.
# Please fix properly!
add_definitions("-DFOLLY_VERSION=\"0.1\"")
