# When updating:
# - verify the gpg signature (foo.tar.gz.asc) against key
#   C13466B7E169A085188632165CB4A9347B3B09DC
# - generate the sha256 with `openssl dgst -sha256 foo.tar.gz`
#
# We separately store the sha256 to be sure we're getting the exact same
# build, not just any tarball.
#
# This also avoids the need to depend on gpg in the installation.

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  set(RUST_URL "https://static.rust-lang.org/dist/rust-1.36.0-x86_64-unknown-linux-gnu.tar.gz")
  set(RUST_SHA256 "15e592ec52f14a0586dcebc87a957e472c4544e07359314f6354e2b8bd284c55")
elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
  set(RUST_URL "https://static.rust-lang.org/dist/rust-1.36.0-x86_64-apple-darwin.tar.gz")
  set(RUST_SHA256 "91f151ec7e24f5b0645948d439fc25172ec4012f0584dd16c3fb1acb709aa325")
else()
  message(FATAL_ERROR "HHVM does not support this operating system")
endif()

set(RUST_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/rust-opt")

function(download_and_extract OUT_DIR_VARIABLE URL SHA256)
  message(STATUS "Fetching ${URL}...")
  get_filename_component(TARBALL "${URL}" NAME)
  string(REPLACE ".tar.gz" "" DIR "${TARBALL}")
  set(TARBALL "${CMAKE_CURRENT_BINARY_DIR}/${TARBALL}")
  file(DOWNLOAD "${URL}" "${TARBALL}" EXPECTED_HASH "SHA256=${SHA256}")
  message(STATUS "... extracting ${DIR}/")
  execute_process(
    COMMAND "tar" "zxf" "${TARBALL}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  )
  message(STATUS "... extracted ${DIR}/")
  set(${OUT_DIR_VARIABLE} "${CMAKE_CURRENT_BINARY_DIR}/${DIR}" PARENT_SCOPE)
endfunction()

download_and_extract(RUST_DIR "${RUST_URL}" "${RUST_SHA256}")
execute_process(
  COMMAND "${RUST_DIR}/install.sh" "--prefix=${RUST_PREFIX}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

set(RUSTC_EXECUTABLE "${RUST_PREFIX}/bin/rustc" CACHE FILEPATH "rustc executable")
set(CARGO_EXECUTABLE "${RUST_PREFIX}/bin/cargo" CACHE FILEPATH "cargo executable")
