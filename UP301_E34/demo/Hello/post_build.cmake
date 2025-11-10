# pre_build.cmake
message(STATUS "Running pre-build from pre_build.cmake")

# Cross Compiler
message(STATUS "Compiler = ${CMAKE_C_COMPILER}")

# PreBuild log
file(WRITE "${CMAKE_BINARY_DIR}/pre_build_log.txt" "Pre-build steps done.\n")