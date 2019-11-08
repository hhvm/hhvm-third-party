include(HHVMRustVersion)
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
