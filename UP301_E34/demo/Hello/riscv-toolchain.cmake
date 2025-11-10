# riscv-toolchain.cmake
message(STATUS ">>> [Toolchain] Loaded riscv-toolchain.cmake")

# [Set toolchain]
# Default path
file(REAL_PATH "${CMAKE_SOURCE_DIR}/../../../.." UPT_ENV_DIR)

# Zephyr path
get_filename_component(DIR_NAME "${UPT_ENV_DIR}" NAME)
if(DIR_NAME STREQUAL "hal")
	file(REAL_PATH "${CMAKE_SOURCE_DIR}/../../../../../.." UPT_ENV_DIR)
endif()

if(WIN32)
	set(CMAKE_TOOLCHAIN "xpack-riscv-none-elf-gcc-14.2.0-3-win32-x64" CACHE STRING "Select GCC toolchain")
	set(TOOLCHAIN_PREFIX riscv-none-elf)
elseif(UNIX)
	set(CMAKE_TOOLCHAIN "xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64" CACHE STRING "Select GCC toolchain")
	set(TOOLCHAIN_PREFIX riscv-none-elf)
else()
	set(CMAKE_TOOLCHAIN "xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64" CACHE STRING "Select GCC toolchain")
	set(TOOLCHAIN_PREFIX riscv-none-elf)
endif()
set(TOOLCHAIN_PATH "${UPT_ENV_DIR}/${CMAKE_TOOLCHAIN}/bin" CACHE FILEPATH "Path to Toolchain compiler")
set(ENV{PATH} "${TOOLCHAIN_PATH}${PATH_SEP}$ENV{PATH}")

message(STATUS "Toolchain path: ${TOOLCHAIN_PATH}")

set(GCC_PATH "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-gcc${EXE_SUFFIX}" CACHE FILEPATH "Path to GCC compiler")
set(ASM_PATH "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-gcc${EXE_SUFFIX}" CACHE FILEPATH "Path to ASM compiler")
set(GXX_PATH "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-g++${EXE_SUFFIX}" CACHE FILEPATH "Path to G++ compiler")	


# Compiler
# Cross compiler setting
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv32)
set(CMAKE_C_COMPILER ${GCC_PATH})
set(CMAKE_ASM_COMPILER ${ASM_PATH})
set(CMAKE_CXX_COMPILER ${GXX_PATH})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

message(STATUS "ASM Compiler: ${CMAKE_ASM_COMPILER}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")

# Find path restrictions
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

message(STATUS ">>> Using toolchain from: ${TOOLCHAIN_PATH}")