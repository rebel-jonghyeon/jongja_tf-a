cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_HOME_DIRECTORY}/toolchain.cmake)

project(REBEL_H C ASM)

if ("${PLATFORM}" STREQUAL "zebu")
	add_compile_options(-DZEBU)
endif()
if ("${PLATFORM}" STREQUAL "zebu_poc")
	add_compile_options(-DZEBU)
	add_compile_options(-DZEBU_POC)
endif()

add_compile_options(-DCHIPLET_COUNT=${CHIPLET_COUNT})

if ("${USE_PCIE}" STREQUAL "1")
	add_compile_options(-DUSE_PCIE)
endif()

if ("${EVT_VER}" STREQUAL "1")
	add_compile_options(-DEVT_VER)
endif()

# User is responsible to set two mandatory options:
# FREERTOS_CONFIG_FILE_DIRECTORY
# FREERTOS_PORT
#
# User can choose which heap implementation to use (either the implementations
# included with FreeRTOS [1..5] or a custom implementation ) by providing the
# option FREERTOS_HEAP. If the option is not set, the cmake will default to
# using heap_4.c.

# Heap number or absolute path to custom heap implementation provided by user
set(FREERTOS_HEAP "4" CACHE STRING "FreeRTOS heap model number. 1 .. 5. Or absolute path to custom heap source file")

if(NOT FREERTOS_PORT)
	message(FATAL_ERROR " FREERTOS_PORT is not set. Please specify it from top-level CMake file (example):\n"
		"  set(FREERTOS_PORT GCC_ARM_CM4F CACHE STRING \"\")\n"
		" or from CMake command line option:\n"
		"  -DFREERTOS_PORT=GCC_ARM_CM4F\n"
		" \n"
		" Available port options:\n"
		" GCC_ARM_CA73                     - Compiller: GCC           Target: ARM Cortex-A73\n"
		" GCC_ARM_CM7                      - Compiller: GCC           Target: ARM Cortex-M7")
endif()

# Absolute path to FreeRTOS config file directory
if(${FREERTOS_PORT} STREQUAL "GCC_ARM_CA73")
	set(FREERTOS_CONFIG_FILE_DIRECTORY "${CMAKE_HOME_DIRECTORY}/../Config/REBEL-H/CA73/" CACHE STRING "Absolute path to the directory with FreeRTOSConfig.h")
elseif(${FREERTOS_PORT} STREQUAL "GCC_ARM_CM7")
	set(FREERTOS_CONFIG_FILE_DIRECTORY "${CMAKE_HOME_DIRECTORY}/../Config/REBEL-H/CM7/" CACHE STRING "Absolute path to the directory with FreeRTOSConfig.h")
endif()

if(NOT FREERTOS_CONFIG_FILE_DIRECTORY)
	message(FATAL_ERROR " FreeRTOSConfig.h file directory not specified. Please specify absolute path to it from top-level CMake file:\n"
		"  set(FREERTOS_CONFIG_FILE_DIRECTORY <absolute path to FreeRTOSConfig.h directory> CACHE STRING \"\")\n"
		" or from CMake command line option:\n"
		"  -DFREERTOS_CONFIG_FILE_DIRECTORY='/absolute_path/to/FreeRTOSConfig.h/directory'")
elseif(NOT EXISTS ${FREERTOS_CONFIG_FILE_DIRECTORY}/FreeRTOSConfig.h)
	message(FATAL_ERROR " FreeRTOSConfig.h file not found in the directory specified (${FREERTOS_CONFIG_FILE_DIRECTORY})\n"
		" Please specify absolute path to it from top-level CMake file:\n"
		"  set(FREERTOS_CONFIG_FILE_DIRECTORY <absolute path to FreeRTOSConfig.h directory> CACHE STRING \"\")\n"
		" or from CMake command line option:\n"
		"  -DFREERTOS_CONFIG_FILE_DIRECTORY='/absolute_path/to/FreeRTOSConfig.h/directory'")
endif()
set(CMAKE_ROOT_DIR ${CMAKE_SOURCE_DIR}/../../..)
set(FREERTOS_COMMON_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}/include
	${CMAKE_ROOT_DIR}/common
	${CMAKE_ROOT_DIR}/common/arch
	${FREERTOS_CONFIG_FILE_DIRECTORY}
	$<$<STREQUAL:${FREERTOS_PORT},GCC_ARM_CA73>:${CMAKE_CURRENT_LIST_DIR}/portable/GCC/ARM_CA73>
	$<$<STREQUAL:${FREERTOS_PORT},GCC_ARM_CM7>:${CMAKE_CURRENT_LIST_DIR}/portable/GCC/ARM_CM7/r1p2>

	$<$<STREQUAL:${FREERTOS_PORT},GCC_ARM_CA73>:${CMAKE_ROOT_DIR}/common/arch/arm64>
	$<$<STREQUAL:${FREERTOS_PORT},GCC_ARM_CM7>:${CMAKE_ROOT_DIR}/common/arch/arm>

	$<$<STREQUAL:${FREERTOS_PORT},GCC_ARM_CM7>:${CMAKE_CURRENT_LIST_DIR}/../CMSIS/CMSIS/Core/Include>

	${CMAKE_CURRENT_LIST_DIR}/gloss
	${CMAKE_CURRENT_LIST_DIR}/services/cli_service
)

add_subdirectory(${CMAKE_ROOT_DIR}/lib/unity ./build/unity)
add_subdirectory(${CMAKE_ROOT_DIR}/lib/interrupt_test_helper ./build/interrupt_test_helper)
add_subdirectory(${CMAKE_ROOT_DIR}/common ./build/common)
add_subdirectory(${CMAKE_ROOT_DIR}/drivers ./build/drivers)
add_subdirectory(${CMAKE_ROOT_DIR}/tests ./build/tests)

if(${FREERTOS_PORT} STREQUAL "GCC_ARM_CA73")
	add_library(freertos_kernel_config
		STATIC
		FreeRTOS_tick_config.c
	)
	target_link_libraries(freertos_kernel_config
		PUBLIC
		intc
		generic_timer
		dw_apb_timer
	)
	target_include_directories(freertos_kernel_config
		PUBLIC
		${FREERTOS_COMMON_INCLUDES}
	)
endif()

add_subdirectory(portable)
add_subdirectory(gloss)
if (NOT BUILD_TARGET STREQUAL cp1)
	add_subdirectory(services)
endif()

add_library(freertos_kernel
	STATIC
	croutine.c
	event_groups.c
	list.c
	queue.c
	stream_buffer.c
	tasks.c
	timers.c
	# If FREERTOS_HEAP is digit between 1 .. 5 - it is heap number, otherwise - it is path to custom heap source file
	$<IF:$<BOOL:$<FILTER:${FREERTOS_HEAP},EXCLUDE,^[1-5]$>>,${FREERTOS_HEAP},portable/MemMang/heap_${FREERTOS_HEAP}.c>
)
target_include_directories(freertos_kernel
	PUBLIC
	${CMAKE_SOURCE_DIR}/services/replay_service/include
	${FREERTOS_COMMON_INCLUDES}
	${CMAKE_ROOT_DIR}/tests/pvt_con
)
target_link_libraries(freertos_kernel
	common
	$<$<STREQUAL:${FREERTOS_PORT},GCC_ARM_CA73>:intc>
	assert
)

if(${FREERTOS_PORT} STREQUAL "GCC_ARM_CA73")
	if (BUILD_TARGET STREQUAL cp0)
		add_executable(freertos_kernel.elf main.c)
	else()
		add_executable(freertos_kernel.elf main_cp1.c)
	endif()
elseif(${FREERTOS_PORT} STREQUAL "GCC_ARM_CM7")
	add_executable(freertos_kernel.elf main_cm7.c)
endif()

target_link_libraries(freertos_kernel.elf
	freertos_kernel
	freertos_kernel_port
	freedom_metal
	${DD_LISTS}
	${SVC_LIST}
	${TEST_LISTS}
)

if(${FREERTOS_PORT} STREQUAL "GCC_ARM_CA73")
	target_link_libraries(freertos_kernel.elf
		freertos_arch
		freertos_kernel_config
		smp
		smccc
	)
endif()

add_custom_command(
	TARGET freertos_kernel.elf
	POST_BUILD
	COMMAND ${CMAKE_OBJCOPY}
	ARGS -O binary freertos_kernel.elf freertos_kernel.bin
	COMMAND ${CMAKE_OBJDUMP}
	ARGS -ldS freertos_kernel.elf > freertos_kernel.lst
	COMMAND ${CMAKE_READELF}
	ARGS -a freertos_kernel.elf > freertos_kernel.readelf
)
