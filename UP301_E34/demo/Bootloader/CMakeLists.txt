cmake_minimum_required(VERSION 3.19.0)

# Detect if running on Windows/Linux
if(WIN32)
    message(STATUS "Running on Windows")
    set(EXE_SUFFIX ".exe")
	set(PATH_SEP ";")
elseif(UNIX)
    message(STATUS "Running on Linux/Unix")
    set(EXE_SUFFIX "")
	set(PATH_SEP ":")
else()
    message(STATUS "Unknown system")
endif()

# Default
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C/C++ standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#==========================================================================================
# Function updating `settings.json` for SDK/Zephyr
function(settings_json_replace_value KEY NEW_VALUE)
    set(SETTINGS_JSON "${CMAKE_SOURCE_DIR}/.vscode/settings.json")

    # Read contents
    file(READ "${SETTINGS_JSON}" CONTENTS)

    # Substitute the key value
    string(REGEX REPLACE
        "\"${KEY}\": \"[^\"]*\""
        "\"${KEY}\": \"${NEW_VALUE}\""
        NEW_CONTENTS
        "${CONTENTS}"
    )

    # Write back
    file(WRITE "${SETTINGS_JSON}" "${NEW_CONTENTS}")
endfunction()

# Set directories
set(CODEBASE_E34_DIR 	${CMAKE_SOURCE_DIR}/../..)
set(UPT_ENV_DIR 		${CODEBASE_E34_DIR}/../..)
set(FREEDOM_METAL_DIR 	${CODEBASE_E34_DIR}/freedom-metal)

# Change gdb and openocd tcl paths in `settings.json` file between SDK and Zephyr env
file(REAL_PATH "${UPT_ENV_DIR}" UPT_ENV_DIR_REAL)
get_filename_component(DIR_NAME "${UPT_ENV_DIR_REAL}" NAME)
if(DIR_NAME STREQUAL "hal") # Zephyr path
	set(NEW_DBG_PATH "\${workspaceFolder}/../../../../../../xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64/bin/riscv-none-elf-gdb")
	settings_json_replace_value("myDbgCmd_linux" "${NEW_DBG_PATH}")

	set(NEW_OPENOCD_TCL_PATH "\${workspaceFolder}/../../../../../../Misc/scripts/tcl")
	settings_json_replace_value("myOpenOcdTclScriptDir" "${NEW_OPENOCD_TCL_PATH}")
else() # SDK path
	set(NEW_DBG_PATH "\${workspaceFolder}/../../../../xpack-riscv-none-elf-gcc-14.2.0-3-linux-x64/bin/riscv-none-elf-gdb")
	settings_json_replace_value("myDbgCmd_linux" "${NEW_DBG_PATH}")

	set(NEW_OPENOCD_TCL_PATH "\${workspaceFolder}/../../../../Misc/scripts/tcl")
	settings_json_replace_value("myOpenOcdTclScriptDir" "${NEW_OPENOCD_TCL_PATH}")
endif()

message(STATUS "Project path: ${CMAKE_SOURCE_DIR}")
message(STATUS "Metal source path: ${CODEBASE_E34_DIR}")
message(STATUS "Core Metal source path: ${FREEDOM_METAL_DIR}")

#==========================================================================================
# Get all project name
get_filename_component(PROJECT_LIST_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)
file(GLOB PARENT_SUBDIRS RELATIVE ${PROJECT_LIST_DIR} ${PROJECT_LIST_DIR}/*)
set(FOLDER_NAMES "")
foreach(item ${PARENT_SUBDIRS})
    if(IS_DIRECTORY "${PROJECT_LIST_DIR}/${item}")
        list(APPEND PROJECT_LIST_NAMES ${item})
    endif()
endforeach()
string(REPLACE ";" " " PROJECT_LIST_NAMES "${PROJECT_LIST_NAMES}")
message(STATUS "List all projects in SDK: ${PROJECT_LIST_NAMES}")

# Get Project & Filename
get_filename_component(SOURCE_FOLDER_NAME ${CMAKE_SOURCE_DIR} NAME)
message(STATUS "Project name: ${SOURCE_FOLDER_NAME}")

# [User Project Configurable]
set(UPT_PROJECT "${SOURCE_FOLDER_NAME}" CACHE STRING "Select demo project")
set_property(CACHE UPT_PROJECT PROPERTY STRINGS ${PROJECT_LIST_NAMES})

# [User E21 Project Configurable]
set(E21_PROJECT "E21_Testchip" CACHE STRING "Select E21 project")

# [User BSP Configurable]
set(BOARD_NAME "UP301_EVB" CACHE STRING "Select target board")
set_property(CACHE BOARD_NAME PROPERTY STRINGS UP301_EVB UP201_EVB Trina-pi Panta-pi)
set(SERIAL_BAUD "921600" CACHE STRING "Select serial port baudrate")
set_property(CACHE SERIAL_BAUD PROPERTY STRINGS 921600 3M 6M 12M)
message(STATUS "Target board name: ${BOARD_NAME}")
message(STATUS "Debug Serial port baudrate: ${SERIAL_BAUD}")

# Project name
project(${UPT_PROJECT} C CXX ASM)

# Save project name to file
file(WRITE ${CMAKE_BINARY_DIR}/cmake_project_name.txt "${UPT_PROJECT}")

#==========================================================================================
# [User Library Configurable Options]
option(USE_LVGL				"Enable LVGL graphics support" 	OFF)
option(USE_CMDER			"Enable Upbeat debug feature" 	OFF)
option(USE_CMSIS_DSP		"Enable CMSIS DSP support"		OFF)
option(USE_CMSIS_NN			"Enable CMSIS NN support" 		OFF)
option(USE_LITERT			"Enable LiteRT support" 		OFF)
option(USE_MICROROS			"Enable MICROROS support" 		OFF)

# Option to select which Metal static libraries to use
set(USE_METAL_STATIC_LIBS "NONE" CACHE STRING "Select static libraries source")
set_property(CACHE USE_METAL_STATIC_LIBS PROPERTY STRINGS
	"NONE"		# Compile sources directly
	"INTERNAL"	# Build from internal sources
	"EXTERNAL"	# Use prebuilt libraries
)

# [User Unit_test Configurable Options]
option(INCLUDE_TESTS_IN_MAIN	"Include test functions in main executable" OFF)

# [User Gcc/Env Relative Configurable Options]
#option(USE_Def_Toolchain_Path	"Enable Default Toolchain Path" ON)
option(USE_Build_Debug		"Enable Build Debug" ON)
option(USE_Build_Release	"Enable Build Release" OFF)

# [User General Configurable Options]
option(USE_PRINT_LOG		"Enable LOG" ON)
option(USE_AUTO_WDT_KICK	"Enable AUTO WDT KICK" ON)
option(USE_LOAD_SRAM_CODE	"Enable LOAD_SRAM_CODE support" OFF)
option(USE_LOAD_E21_CODE	"Enable LOAD_E21_CODE support" 	OFF)
option(USE_FETCH_E21_CODE	"Enable FETCH_E21_CODE support"	OFF)

# Show OS support
if(UPT_PROJECT STREQUAL "FreeRTOS_Example" OR UPT_PROJECT STREQUAL "BTtask")
	set(USE_FREERTOS ON)
	message(STATUS "FreeRTOS is enabled")
else()
	set(USE_FREERTOS OFF)
	message(STATUS "FreeRTOS is disabled")
endif()

# Show library support
if(USE_LVGL STREQUAL "ON")
	message(STATUS "LVGL Library is enabled")
else()
	message(STATUS "LVGL Library is disabled")
endif()

if(USE_CMDER STREQUAL "ON")
	message(STATUS "CMDER Library is enabled")
else()
	message(STATUS "CMDER Library is disabled")
endif()

if(USE_CMSIS_DSP STREQUAL "ON")
	message(STATUS "USE_CMSIS_DSP Library is enabled")
else()
	message(STATUS "USE_CMSIS_DSP Library is disabled")
endif()

if(USE_CMSIS_NN STREQUAL "ON")
	message(STATUS "USE_CMSIS_NN Library is enabled")
else()
	message(STATUS "USE_CMSIS_NN Library is disabled")
endif()

if(USE_LITERT STREQUAL "ON")
	message(STATUS "USE_LITERT Library is enabled")
else()
	message(STATUS "USE_LITERT Library is disabled")
endif()

if(USE_MICROROS STREQUAL "ON")
	message(STATUS "USE_MICROROS Library is enabled")
else()
	message(STATUS "USE_MICROROS Library is disabled")
endif()

# Show feature support
if(USE_LOAD_SRAM_CODE STREQUAL "ON")
	message(STATUS "LOAD_SRAM_CODE is enabled")
else()
	message(STATUS "LOAD_SRAM_CODE is disabled")
endif()

if(USE_LOAD_E21_CODE STREQUAL "ON")
	message(STATUS "LOAD_E21_CODE is enabled")
else()
	message(STATUS "LOAD_E21_CODE is disabled")
endif()

if(USE_FETCH_E21_CODE STREQUAL "ON")
	message(STATUS "FETCH_E21_CODE is enabled")
else()
	message(STATUS "FETCH_E21_CODE is disabled")
endif()

#==========================================================================================
# Search paths included
set(FREERTOS_DIR 		${CODEBASE_E34_DIR}/FreeRTOS-metal)
set(LVGL_DIR 			${CODEBASE_E34_DIR}/lvgl)
set(CMDER_DIR 			${CODEBASE_E34_DIR}/UPCmder-metal)
set(CMSIS_DSP_DIR 		${CODEBASE_E34_DIR}/CMSIS_dsp_metal)
set(CMSIS_NN_DIR        ${CODEBASE_E34_DIR}/CMSIS_NN-metal)
set(LITERT_DIR 		    ${CODEBASE_E34_DIR}/LiteRT)
set(MICROROS_DIR 		${CODEBASE_E34_DIR}/microros)
set(BOOTLOADER_DIR 		${CODEBASE_E34_DIR}/mcuboot)

# Include headers from the include/ folder
set(INCLUDE_DIRS
	${CODEBASE_E34_DIR}/bsp
	${CMAKE_SOURCE_DIR}/include
	${FREEDOM_METAL_DIR}
	${FREEDOM_METAL_DIR}/metal/drivers
	${FREEDOM_METAL_DIR}/metal/pufs/include
	${FREEDOM_METAL_DIR}/metal/sdmmc/include
	${FREEDOM_METAL_DIR}/metal/nema_dc/include
)

if(USE_FREERTOS STREQUAL "ON" )
    list(APPEND INCLUDE_DIRS
        ${FREERTOS_DIR}/include
        ${FREERTOS_DIR}/FreeRTOS-Kernel
        ${FREERTOS_DIR}/FreeRTOS-Kernel/include
        ${FREERTOS_DIR}/FreeRTOS-Kernel/portable/GCC/RISC-V
        ${FREERTOS_DIR}/FreeRTOS-Kernel/portable/GCC/RISC-V/chip_specific_extensions/RV32I_CLINT_no_extensions
    )
endif()

if(USE_LVGL STREQUAL "ON" )
	list(APPEND INCLUDE_DIRS ${LVGL_DIR})
endif()

if(USE_CMDER STREQUAL "ON" )
	list(APPEND INCLUDE_DIRS ${CMDER_DIR}/include)
endif()

if(USE_CMSIS_DSP STREQUAL "ON" )
	list(APPEND INCLUDE_DIRS ${CMSIS_DSP_DIR}/Include)
endif()

if(USE_CMSIS_NN STREQUAL "ON" )
	list(APPEND INCLUDE_DIRS 
		${CMSIS_NN_DIR}/Include
		${CMSIS_NN_DIR}/TestCases
		)
endif()

if(USE_LITERT STREQUAL "ON" )
	list(APPEND INCLUDE_DIRS
	 	${LITERT_DIR}  
		${LITERT_DIR}/tensorflow
		${LITERT_DIR}/third_party/ruy
		${LITERT_DIR}/third_party/kissfft
		${LITERT_DIR}/third_party/gemmlowp
		${LITERT_DIR}/third_party/eyalroz_printf/src
		${LITERT_DIR}/third_party/flatbuffers/include
		${CMSIS_NN_DIR}
		)
endif()

if(USE_MICROROS STREQUAL "ON" )
	list(APPEND INCLUDE_DIRS ${MICROROS_DIR})
endif()

if(UPT_PROJECT STREQUAL "Bootloader" OR USE_Build_Release STREQUAL "ON")
	list(APPEND INCLUDE_DIRS 
		${BOOTLOADER_DIR}/bootutil/include
		${BOOTLOADER_DIR}/common/include
		${BOOTLOADER_DIR}/ext/mbedtls/3rdparty/everest/include
		${BOOTLOADER_DIR}/ext/mbedtls/3rdparty/everest/include/everest
		${BOOTLOADER_DIR}/ext/mbedtls/3rdparty/everest/include/everest/kremlib
		${BOOTLOADER_DIR}/ext/mbedtls/include
		${BOOTLOADER_DIR}/ext/mbedtls/library
	)
endif()

#==========================================================================================
# Search all source files
if(USE_METAL_STATIC_LIBS STREQUAL "NONE")
	file(GLOB_RECURSE METAL_SOURCES
		"src/*.cpp" "src/*.c" "src/*.s" "src/*.S" "src/*.cc"
		"${CODEBASE_E34_DIR}/bsp/*.cpp" "${CODEBASE_E34_DIR}/bsp/*.c" "${CODEBASE_E34_DIR}/bsp/*.S"
		"${FREEDOM_METAL_DIR}/src/*.cpp" "${FREEDOM_METAL_DIR}/src/*.c" "${FREEDOM_METAL_DIR}/src/*.S"
	)
	list(APPEND SOURCES ${METAL_SOURCES})
else() # INTERNAL || EXTERNAL
	file(GLOB_RECURSE METAL_SOURCES
		"src/*.cpp" "src/*.c" "src/*.s" "src/*.S" "src/*.cc"
		"${CODEBASE_E34_DIR}/bsp/*.cpp"
		"${CODEBASE_E34_DIR}/bsp/*.c"
		"${CODEBASE_E34_DIR}/bsp/*.S"
		"${FREEDOM_METAL_DIR}/src/gloss/*.cpp"
		"${FREEDOM_METAL_DIR}/src/gloss/*.c"
		"${FREEDOM_METAL_DIR}/src/gloss/*.S"
	)
	list(APPEND SOURCES ${METAL_SOURCES})

	file(GLOB METAL_ROOT_SOURCES
		"${FREEDOM_METAL_DIR}/src/*.cpp"
		"${FREEDOM_METAL_DIR}/src/*.c"
		"${FREEDOM_METAL_DIR}/src/*.S"
	)
	list(APPEND SOURCES ${METAL_ROOT_SOURCES})
endif()
	
if(USE_FREERTOS STREQUAL "ON" )
	file(GLOB_RECURSE FREERTOS_SOURCES
		"${FREERTOS_DIR}/FreeRTOS-Kernel/*.cpp"
		"${FREERTOS_DIR}/FreeRTOS-Kernel/*.c"
		"${FREERTOS_DIR}/FreeRTOS-Kernel/*.S"
	)
	list(APPEND SOURCES ${FREERTOS_SOURCES})
	add_compile_options(
		-fdebug-prefix-map=${FREERTOS_DIR}=${CMAKE_SOURCE_DIR}/
	)
endif()

if(USE_LVGL STREQUAL "ON" )
	file(GLOB_RECURSE LVGL_SOURCES
		"${LVGL_DIR}/src/*.cpp"
		"${LVGL_DIR}/src/*.c"
		"${LVGL_DIR}/src/*.S"
	)
	list(APPEND SOURCES ${LVGL_SOURCES})
	add_compile_options(
		-fdebug-prefix-map=${LVGL_DIR}=${CMAKE_SOURCE_DIR}/
	)
endif()

if(USE_CMSIS_DSP STREQUAL "ON" )
	file(GLOB_RECURSE CMSIS_DSP_SOURCES
		"${CMSIS_DSP_DIR}/src/*.cpp"
		"${CMSIS_DSP_DIR}/src/*.c"
		"${CMSIS_DSP_DIR}/src/*.S"
	)
	list(APPEND SOURCES ${CMSIS_DSP_SOURCES})
	add_compile_options(
		-fdebug-prefix-map=${CMSIS_DSP_DIR}=${CMAKE_SOURCE_DIR}/
	)
endif()

if(USE_CMSIS_NN STREQUAL "ON" )
	file(GLOB_RECURSE CMSIS_NN_SOURCES
		"${CMSIS_NN_DIR}/src/*.cpp"
		"${CMSIS_NN_DIR}/src/*.c"
		"${CMSIS_NN_DIR}/src/*.S"
	)
	list(APPEND SOURCES ${CMSIS_NN_SOURCES})
	add_compile_options(
		-fdebug-prefix-map=${CMSIS_NN_DIR}=${CMAKE_SOURCE_DIR}/
	)
endif()

if(USE_LITERT STREQUAL "ON" )
	file(GLOB_RECURSE LITERT_SOURCES
		"${LITERT_DIR}/**/*.c"
		"${LITERT_DIR}/**/*.cc"
	)
	list(APPEND SOURCES ${LITERT_SOURCES})
	add_compile_options(
		-fdebug-prefix-map=${LITERT_DIR}=${CMAKE_SOURCE_DIR}/
	)
endif()

if(USE_CMDER STREQUAL "ON" )
	file(GLOB_RECURSE CMDER_SOURCES
		"${CMDER_DIR}/src/*.cpp"
		"${CMDER_DIR}/src/*.c"
		"${CMDER_DIR}/src/*.S"
	)
	list(APPEND SOURCES ${CMDER_SOURCES})
	add_compile_options(
		-fdebug-prefix-map=${CMDER_DIR}=${CMAKE_SOURCE_DIR}/
	)
endif()

if(UPT_PROJECT STREQUAL "Bootloader" OR USE_Build_Release STREQUAL "ON")
	file(GLOB_RECURSE BOOT_SOURCES
		"${BOOTLOADER_DIR}/*.cpp"
		"${BOOTLOADER_DIR}/*.c"
		"${BOOTLOADER_DIR}/*.S"
	)
	list(APPEND SOURCES ${BOOT_SOURCES})
	add_compile_options(
		-fdebug-prefix-map=${BOOTLOADER_DIR}=${CMAKE_SOURCE_DIR}/
	)
endif()

#==========================================================================================
# Compiler options
set(CMAKE_C_FLAGS	"-march=rv32imafc_zicsr_zifencei -mabi=ilp32f -mcmodel=medlow -ffunction-sections -fdata-sections -u _printf_float" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS	"-march=rv32imafc_zicsr_zifencei -mabi=ilp32f -mcmodel=medlow -ffunction-sections -fdata-sections -u _printf_float" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS	"-march=rv32imafc_zicsr_zifencei -mabi=ilp32f -mcmodel=medlow -ffunction-sections -fdata-sections -u _printf_float -fno-exceptions -fno-rtti -fno-use-cxa-atexit" CACHE STRING "" FORCE)
set(EXE_LINKER_FLAGS
	"-march=rv32imafc_zicsr_zifencei \
	-mabi=ilp32f \
	-mcmodel=medlow \
	--specs=nano.specs \
	-fcommon \
	-nostartfiles \
	-nostdlib \
	-Wl,--gc-sections \
	-Wl,--start-group \
	-lstdc++ -lc -lgcc -lm " 
	CACHE STRING "" FORCE)

# Add Custom Libraries	
if(USE_MICROROS STREQUAL "ON" )
	set(EXE_LINKER_FLAGS "${EXE_LINKER_FLAGS} -L${MICROROS_DIR} -lmicroros")
endif()

# Final linker flags
set(EXE_LINKER_FLAGS "${EXE_LINKER_FLAGS} -Wl,--end-group -Xlinker -u -Xlinker _printf_float ")

#==========================================================================================
# Set linker script
if(USE_Build_Debug STREQUAL "ON" )
	if(UPT_PROJECT STREQUAL "Bootloader")
		set(DEBUG_LDS_FILE "${CMAKE_SOURCE_DIR}/project_file/metal.default_load_sram_2.lds" CACHE FILEPATH "Path to debug linker script (.lds)")
	elseif(UPT_PROJECT STREQUAL "BTtask" OR UPT_PROJECT STREQUAL "FreeRTOS_Example")
		set(DEBUG_LDS_FILE "${CMAKE_SOURCE_DIR}/project_file/metal.freertos.lds" CACHE FILEPATH "Path to debug linker script (.lds)")
	else()
		set(DEBUG_LDS_FILE "${CMAKE_SOURCE_DIR}/project_file/metal.default.lds" CACHE FILEPATH "Path to debug linker script (.lds)")
	endif()
endif()

if(USE_Build_Release STREQUAL "ON" )
	if(UPT_PROJECT STREQUAL "Bootloader")
		set(RELEASE_LDS_FILE "${CMAKE_SOURCE_DIR}/project_file/metal.default_load_sram_2.lds" CACHE FILEPATH "Path to debug linker script (.lds)")
	elseif(UPT_PROJECT STREQUAL "BTtask" OR UPT_PROJECT STREQUAL "FreeRTOS_Example")
		set(RELEASE_LDS_FILE "${CMAKE_SOURCE_DIR}/project_file/metal.freertos_no_header.lds" CACHE FILEPATH "Path to debug linker script (.lds)")
	else()
		set(RELEASE_LDS_FILE "${CMAKE_SOURCE_DIR}/project_file/metal.default_no_header.lds" CACHE FILEPATH "Path to release linker script (.lds)")
	endif()	
endif()

#==========================================================================================
# Global definition flags
if(UPT_PROJECT STREQUAL "Bootloader")
	list(APPEND DEFINE_FLAGS 
		"ROM_CODE"
		"BOOTLOADER"
		"JTAG_UART_EN"
		"LOAD_SRAM_CODE"
		"BAREMETAL"
		"MTIME_RATE_HZ_DEF=32768" 
		"NONE_DP"
		"MMC_ENABLED" 
		"FSL_FEATURE_USDHC_HAS_SDR50_MODE" 
		"LV_LVGL_H_INCLUDE_SIMPLE" 
		"UP301_MEM_ACCESS_ISSUE"
	)
else()
	if (USE_LOAD_SRAM_CODE STREQUAL "ON")
		list(APPEND DEFINE_FLAGS
			"LOAD_SRAM_CODE"
		)
	endif()

	list(APPEND DEFINE_FLAGS
		"MTIME_RATE_HZ_DEF=32768" 
		"NONE_DP"
		"MMC_ENABLED" 
		"FSL_FEATURE_USDHC_HAS_SDR50_MODE" 
		"LV_LVGL_H_INCLUDE_SIMPLE" 
		"UP301_MEM_ACCESS_ISSUE"
	)
endif()

# Load E21 code support
if(USE_LOAD_E21_CODE STREQUAL "ON")
	if(USE_FETCH_E21_CODE STREQUAL "ON")
		set(CODEBASE_E21_DIR 	${CODEBASE_E34_DIR}/../UP301_E21)
		set(E21_CODE_LOCAL 		${CMAKE_SOURCE_DIR}/include/upt_up301_e21.h)
		set(E21_CODE_EXTERNAL	${CODEBASE_E21_DIR}/header/${E21_PROJECT}/upt_up301_e21.h)

		# Clean E21 cache
		message(STATUS "Cleaning E21 cache...")
		execute_process(
			COMMAND ${CMAKE_COMMAND} -E rm -rf build/CMakeCache.txt
			WORKING_DIRECTORY ${CODEBASE_E21_DIR}/demo/${E21_PROJECT}
		)

		# Configure E21 code
		message(STATUS "Configuring E21 code...")
		execute_process(
			COMMAND cmake --preset=riscv-debug
			WORKING_DIRECTORY ${CODEBASE_E21_DIR}/demo/${E21_PROJECT}
			RESULT_VARIABLE result
			ERROR_VARIABLE err
		)
		if(NOT result EQUAL 0)
			message(FATAL_ERROR "Configuring E21 code failed in project: ${E21_PROJECT}. ${err}")
		endif()

		# Build E21 code
		message(STATUS "Building E21 code...")
		execute_process(
			COMMAND cmake --build --preset=riscv-debug-build
			WORKING_DIRECTORY ${CODEBASE_E21_DIR}/demo/${E21_PROJECT}
			RESULT_VARIABLE result
			ERROR_VARIABLE err
		)
		if(NOT result EQUAL 0)
			message(FATAL_ERROR "Building E21 code failed in project: ${E21_PROJECT}. ${err}")
		endif()

		# Check if the local e21 code already exists
		if(EXISTS ${E21_CODE_LOCAL})
			# Compare between headers
			message(STATUS "Local E21 header exists")
			execute_process(
				COMMAND ${CMAKE_COMMAND} -E compare_files ${E21_CODE_LOCAL} ${E21_CODE_EXTERNAL}
				RESULT_VARIABLE result
			)
			# Copy the external header if they are different
			if(result EQUAL 1)
				message(STATUS "E21 headers differ. Copying external header...")
				file(COPY ${E21_CODE_EXTERNAL} DESTINATION ${CMAKE_SOURCE_DIR}/include)
			else()
				message(STATUS "Local E21 header is up-to-date")
			endif()
		else()
			# Copy the external header
			message(STATUS "Local E21 header does not exist. Copying external header...")
			file(COPY ${E21_CODE_EXTERNAL} DESTINATION ${CMAKE_SOURCE_DIR}/include)
		endif()
	endif()

	list(APPEND DEFINE_FLAGS
		"LOAD_E21_CODE"
	)
endif()

# LiteRT with CMSIS_NN kernel
if (UPT_PROJECT STREQUAL "LITERT_Example")
	list(APPEND DEFINE_FLAGS 
	"CMSIS_NN"
	)
endif()


# FreeRTOS definition flags
if(UPT_PROJECT STREQUAL "FreeRTOS_Example" OR UPT_PROJECT STREQUAL "BTtask")
	list(APPEND DEFINE_FLAGS
		"WAIT_MS=1000"
		"__ASSEMBLY__"
		"__riscv_fdiv"
	)
endif()
	
if(BOARD_NAME STREQUAL "UP301_EVB")
	list(APPEND DEFINE_FLAGS "PMIC_TPS65023")
elseif(BOARD_NAME STREQUAL "UP201_EVB")
	list(APPEND DEFINE_FLAGS "PMIC_TPS65023")
elseif(BOARD_NAME STREQUAL "Trina-pi")
	list(APPEND DEFINE_FLAGS "PMIC_TPS628604")
elseif(BOARD_NAME STREQUAL "Panta-pi")
	list(APPEND DEFINE_FLAGS "PMIC_TPS628604")
endif()

if(SERIAL_BAUD STREQUAL "921600")
	list(APPEND DEFINE_FLAGS "STDOUT_BAUD_921600")
elseif(SERIAL_BAUD STREQUAL "3M")
	list(APPEND DEFINE_FLAGS "STDOUT_BAUD_3000000")
elseif(SERIAL_BAUD STREQUAL "6M")
	list(APPEND DEFINE_FLAGS "STDOUT_BAUD_6000000")
elseif(SERIAL_BAUD STREQUAL "12M")
	list(APPEND DEFINE_FLAGS "STDOUT_BAUD_12000000")
endif()
	
if(USE_PRINT_LOG STREQUAL "ON" )
	list(APPEND DEFINE_FLAGS "UP_DEBUG" "UP_LOG_LEVEL=5")
endif()

if(USE_AUTO_WDT_KICK STREQUAL "ON" )
	list(APPEND DEFINE_FLAGS "WDT_ISR_ALWAYS_KICK")
endif()

list(APPEND DEFINE_DEBUG_FLAGS 		${DEFINE_FLAGS})
list(APPEND DEFINE_RELEASE_FLAGS	${DEFINE_FLAGS})

# Additional release flags
if(USE_Build_Release STREQUAL "ON")
	if(UPT_PROJECT STREQUAL "Bootloader")
		list(APPEND DEFINE_RELEASE_FLAGS "MP_BOOT")
	endif()

	list(APPEND DEFINE_RELEASE_FLAGS "BUILD_RELEASE")
endif()

#==========================================================================================
# Find path restrictions
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

file(MAKE_DIRECTORY 		"${CMAKE_CURRENT_BINARY_DIR}/Debug")
file(MAKE_DIRECTORY 		"${CMAKE_CURRENT_BINARY_DIR}/Release")
set(MAKE_DIRECTORY_DEBUG 	"${CMAKE_CURRENT_BINARY_DIR}/Debug")
set(MAKE_DIRECTORY_RELEASE 	"${CMAKE_CURRENT_BINARY_DIR}/Release")

#==========================================================================================
# Function to create a static library
function(make_lib LIB_NAME LIB_DIR)
    # Gather all source files (.S, .c, .cpp) in the library directory
    file(GLOB LIB_SRC
        "${LIB_DIR}/*.S"
        "${LIB_DIR}/*.c"
        "${LIB_DIR}/*.cpp"
    )

    # Create a static library
    add_library(${LIB_NAME} STATIC ${LIB_SRC})

    # Set compile definitions and options
	target_compile_definitions(${LIB_NAME} PUBLIC ${DEFINE_FLAGS})
	target_compile_options(${LIB_NAME} PUBLIC -O0 -g -Wall)

    # Set include directories
    target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DIRS})

    # Set output directory for static libraries
    set_target_properties(${LIB_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )
endfunction()

# Build libraries if `USE_METAL_STATIC_LIBS` is not NONE
if(NOT USE_METAL_STATIC_LIBS STREQUAL "NONE")
	set(LIBRARIES)
    set(LIB_NAMES
		drivers
		nema_dc
		pufs
		sdmmc
	)

	foreach(LIB_NAME ${LIB_NAMES})
		if(USE_METAL_STATIC_LIBS STREQUAL "INTERNAL")
			# Make lib from internal sources (.c)
			make_lib(${LIB_NAME} ${FREEDOM_METAL_DIR}/src/${LIB_NAME})
			list(APPEND LIBRARIES "${CMAKE_BINARY_DIR}/lib/lib${LIB_NAME}.a")
		else()
			# Link lib from external sources (.a)
			if(UPT_PROJECT STREQUAL "Bootloader")
				list(APPEND LIBRARIES "${FREEDOM_METAL_DIR}/lib_sdk/bootloader/lib${LIB_NAME}.a")
			else()
				list(APPEND LIBRARIES "${FREEDOM_METAL_DIR}/lib_sdk/app/lib${LIB_NAME}.a")
			endif()
		endif()
	endforeach()
endif()

#==========================================================================================
# Generate execution files
# Debug target
if(USE_Build_Debug STREQUAL "ON" )
	add_executable(${PROJECT_NAME}_Debug ${SOURCES})
	target_compile_definitions(${PROJECT_NAME}_Debug PRIVATE ${DEFINE_DEBUG_FLAGS})
	target_compile_options(${PROJECT_NAME}_Debug PRIVATE -O0 -g -Wall)
	target_link_options(${PROJECT_NAME}_Debug PRIVATE -T${DEBUG_LDS_FILE})
	target_link_libraries(${PROJECT_NAME}_Debug PRIVATE "${EXE_LINKER_FLAGS} -Wl,-Map=${MAKE_DIRECTORY_DEBUG}/${UPT_PROJECT}_Debug.map")
	target_link_libraries(${PROJECT_NAME}_Debug PRIVATE ${LIBRARIES})
	target_include_directories(${PROJECT_NAME}_Debug PRIVATE ${INCLUDE_DIRS})
endif()

# Release target
if(USE_Build_Release STREQUAL "ON" )
	add_executable(${PROJECT_NAME}_Release ${SOURCES})
	target_compile_definitions(${PROJECT_NAME}_Release PRIVATE ${DEFINE_RELEASE_FLAGS})
	target_compile_options(${PROJECT_NAME}_Release PRIVATE -O0 -g)
	target_link_options(${PROJECT_NAME}_Release PRIVATE -T${RELEASE_LDS_FILE})
	target_link_libraries(${PROJECT_NAME}_Release PRIVATE "${EXE_LINKER_FLAGS} -Wl,-Map=${MAKE_DIRECTORY_RELEASE}/${UPT_PROJECT}_Debug.map")
	target_link_libraries(${PROJECT_NAME}_Release PRIVATE ${LIBRARIES})
	target_include_directories(${PROJECT_NAME}_Release PRIVATE ${INCLUDE_DIRS})
endif()

#Pre-build Step
add_custom_command(
	OUTPUT ${CMAKE_BINARY_DIR}/pre_build.done
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/pre_build.cmake
	COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/pre_build.done
	COMMENT "Running pre-build script with CMake"
)
add_custom_target(prebuild_step
    DEPENDS ${CMAKE_BINARY_DIR}/pre_build.done
)

#Post-build Step
add_custom_command(
	OUTPUT ${CMAKE_BINARY_DIR}/post_build.done
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/post_build.cmake
	COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/post_build.done
	COMMENT "Running post-build script with CMake"
)
add_custom_target(postbuild_step
	DEPENDS ${CMAKE_BINARY_DIR}/post_build.done
)

# Debug target
if(USE_Build_Debug STREQUAL "ON" )
	# Post-build commands for Debug target
	add_custom_command(TARGET ${PROJECT_NAME}_Debug POST_BUILD
		COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target postbuild_step
		COMMAND ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-objcopy -O binary ${MAKE_DIRECTORY_DEBUG}/${PROJECT_NAME}_Debug.elf ${MAKE_DIRECTORY_DEBUG}/${PROJECT_NAME}_Debug.bin
		COMMAND ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-objcopy -O ihex ${MAKE_DIRECTORY_DEBUG}/${PROJECT_NAME}_Debug.elf ${MAKE_DIRECTORY_DEBUG}/${PROJECT_NAME}_Debug.hex
		COMMAND ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-objdump --source --all-headers --demangle --line-numbers --wide ${MAKE_DIRECTORY_DEBUG}/${PROJECT_NAME}_Debug.elf > ${MAKE_DIRECTORY_DEBUG}/${PROJECT_NAME}_Debug.lst
		COMMAND ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-size --format=berkeley ${MAKE_DIRECTORY_DEBUG}/${PROJECT_NAME}_Debug.elf
		COMMENT "Generating bin, hex, lst and size for Debug build"
	)

	# .elf
	set_target_properties(${PROJECT_NAME}_Debug PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${MAKE_DIRECTORY_DEBUG}
		OUTPUT_NAME "${PROJECT_NAME}_Debug"
		SUFFIX ".elf"
	)

	# dependencies
	add_dependencies(${PROJECT_NAME}_Debug prebuild_step)
endif()

# Release target
if(USE_Build_Release STREQUAL "ON" )
	# Post-build commands for Release target
	add_custom_command(TARGET ${PROJECT_NAME}_Release POST_BUILD
		COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target postbuild_step
		COMMAND ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-objcopy -O binary ${MAKE_DIRECTORY_RELEASE}/${PROJECT_NAME}_Release.elf ${MAKE_DIRECTORY_RELEASE}/${PROJECT_NAME}_Release.bin
		COMMAND ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-objcopy -O ihex ${MAKE_DIRECTORY_RELEASE}/${PROJECT_NAME}_Release.elf ${MAKE_DIRECTORY_RELEASE}/${PROJECT_NAME}_Release.hex
		COMMAND ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-objdump --source --all-headers --demangle --line-numbers --wide ${MAKE_DIRECTORY_RELEASE}/${PROJECT_NAME}_Release.elf > ${MAKE_DIRECTORY_RELEASE}/${PROJECT_NAME}_Release.lst
		COMMAND ${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}-size --format=berkeley ${MAKE_DIRECTORY_RELEASE}/${PROJECT_NAME}_Release.elf
		COMMENT "Generating bin, hex, lst and size for Release build"
	)

	# .elf
	set_target_properties(${PROJECT_NAME}_Release PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${MAKE_DIRECTORY_RELEASE}
		OUTPUT_NAME "${PROJECT_NAME}_Release"
		SUFFIX ".elf"
	)

	# dependencies
	add_dependencies(${PROJECT_NAME}_Release prebuild_step)
endif()

#==========================================================================================
# Link and debug path
set(TOP_SOURCE_DIRS "${CMAKE_SOURCE_DIR}/../../../UP301_E34")
set(LINK_DEST_ROOT "${CMAKE_BINARY_DIR}/UP301_E34")

foreach(SRC_DIR IN LISTS INCLUDE_DIRS SOURCES)
  # Get relative path of TOP_SOURCE_DIRS 
  file(RELATIVE_PATH REL_PATH "${TOP_SOURCE_DIRS}" "${SRC_DIR}")

  # symlink path
  set(SYMLINK_DEST "${LINK_DEST_ROOT}/${REL_PATH}")

  get_filename_component(SYMLINK_DEST_PARENT "${SYMLINK_DEST}" DIRECTORY)
  file(MAKE_DIRECTORY "${SYMLINK_DEST_PARENT}")

  # Establish symlink
  if(NOT EXISTS "${SYMLINK_DEST}")
    message(STATUS "Linking dir: ${SRC_DIR} ${SYMLINK_DEST}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${SRC_DIR}" "${SYMLINK_DEST}")
  endif()
endforeach()

file(MAKE_DIRECTORY 		"${CMAKE_BINARY_DIR}/linkext")
set(LINK_CODEBASE_E34_DIR	&{CMAKE_BINARY_DIR}/linkext)
add_compile_options(
	"-fdebug-prefix-map=${CODEBASE_E34_DIR}=${LINK_CODEBASE_E34_DIR}"
)
message(STATUS "Link debug source path: ${LINK_CODEBASE_E34_DIR}")

#==========================================================================================
# For Doxygen
set(PROJECT_NAME_FOR_DOXYGEN 	"UP301/UP201 series")
set(DOXYGEN_OUTPUT_DIR		"${CODEBASE_E34_DIR}/Document")
set(DOXYGEN_EXECUTABLE_DEFAULT 	"c:/Program Files/doxygen/bin/doxygen${EXE_SUFFIX}")
set(DOXYGEN_EXECUTABLE "${DOXYGEN_EXECUTABLE_DEFAULT}" CACHE FILEPATH "Path to the Doxygen executable")
set(PLANTUML_JAR_PATH_DEFAULT 	"c:/Data/myProgram/PlantUML/plantuml-1.2023.4.jar")
set(PLANTUML_JAR_PATH "${PLANTUML_JAR_PATH_DEFAULT}" CACHE FILEPATH "Path to PlantUML jar file")

if(NOT EXISTS "${DOXYGEN_EXECUTABLE}")
    message(WARNING "Doxygen executable not found at: ${DOXYGEN_EXECUTABLE}")
endif()

if(NOT EXISTS "${PLANTUML_JAR_PATH}")
    message(WARNING "PlantUML jar not found at: ${PLANTUML_JAR_PATH}")
endif()

# Generate temp Doxyfile.in
file(WRITE ${CMAKE_BINARY_DIR}/Doxyfile.in
	"PROJECT_NAME          \"= ${PROJECT_NAME_FOR_DOXYGEN}\"
	INPUT                  = ${CODEBASE_E34_DIR}
	OUTPUT_DIRECTORY       = ${DOXYGEN_OUTPUT_DIR}
	FULL_PATH_NAMES        = NO
	WARN_IF_UNDOCUMENTED   = NO
	RECURSIVE              = YES
	GENERATE_LATEX         = NO
	PLANTUML_JAR_PATH      = ${PLANTUML_JAR_PATH}
")

# Generate Doxyfile
configure_file(${CMAKE_BINARY_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)

# CMake custom target: doxygen
add_custom_target(gen_doxygen
	COMMAND "${DOXYGEN_EXECUTABLE}" "${CMAKE_BINARY_DIR}/Doxyfile"
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Generating documentation with Doxygen"
	VERBATIM
)

#==========================================================================================
# Make Project Clean
add_custom_target(extra_clean
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/CMakeFiles/*
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/Debug/*
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/Release/*
  COMMENT "Extra cleaning..."
)

#==========================================================================================
# Openocd Programming Flash
set(OPENOCD_EXECUTABLE "openocd${EXE_SUFFIX}")
set(OPENOCD_FOLDER_NAME "riscv-openocd-upbeat-20240919")

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    # On Windows: use bundled OpenOCD
    set(OPENOCD_PATH "${UPT_ENV_DIR}/${OPENOCD_FOLDER_NAME}/bin/${OPENOCD_EXECUTABLE}" CACHE FILEPATH "Path to OpenOCD")
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    # On Linux: use system-installed OpenOCD
    set(OPENOCD_PATH "openocd" CACHE FILEPATH "Path to OpenOCD")
else()
    # On unsupported systems: stop configuration
    message(FATAL_ERROR "Unsupported host platform: ${CMAKE_HOST_SYSTEM_NAME}")
endif()

# Custom target: flash program using OpenOCD
add_custom_target(flash_program
    COMMAND ${CMAKE_COMMAND} -E env pwd
    COMMAND "${OPENOCD_PATH}"
            -f ../../../bsp/${BOARD_NAME}/openocd.cfg
            -c "program ./Debug/${PROJECT_NAME}_Debug.elf verify reset exit"
    COMMENT "Flashing debug project using OpenOCD"
    VERBATIM
)