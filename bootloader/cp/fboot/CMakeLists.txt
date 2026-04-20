#
# Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
#
# PROPRIETARY/CONFIDENTIAL
#
# This software is the confidential and proprietary information of
# Samsung Electronics Co., Ltd. ("Confidential Information").
# You shall not disclose such Confidential Information and shall use it only
# in accordance with the terms of the license agreement you entered into with
# Samsung Electronics Co., Ltd. ("SAMSUNG").
#
# SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
# THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
# NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
# LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
# ITS DERIVATIVES.
#

cmake_minimum_required(VERSION 3.15)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_HOME_DIRECTORY}/toolchain.cmake)
set(CMAKE_ROOT_DIR ${CMAKE_SOURCE_DIR}/../../..)
set(BAREMETAL_TARGET "TARGET_CA73" CACHE STRING "Baremetal code target architecture")

project(
	CP_Bootloader
	VERSION 0.0
	DESCRIPTION "CMake for CP Bootloaders"
	LANGUAGES C ASM)

message(STATUS "Compiler")
message(STATUS " - ID       \t: ${CMAKE_C_COMPILER_ID}")
message(STATUS " - Version  \t: ${CMAKE_C_COMPILER_VERSION}")
message(STATUS " - Path     \t: ${CMAKE_C_COMPILER}")

set(BUILD_TYPE DEBUG)

option(ZEBU "Build with ZEBU option" OFF)
if ("${PLATFORM}" STREQUAL "zebu")
	add_compile_options(-DZEBU)
endif()
if ("${PLATFORM}" STREQUAL "zebu_poc")
	add_compile_options(-DZEBU)
	add_compile_options(-DZEBU_POC)
endif()

if (${USE_GPT} EQUAL 0)
	add_compile_options(-DSBOOT_N_PRELOAD)
endif()

set(BOOTLOADER_COMMON_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}/include
	${CMAKE_CURRENT_LIST_DIR}/include/arm64
	${CMAKE_ROOT_DIR}/common/arch/arm64
	${CMAKE_ROOT_DIR}/common
	${CMAKE_ROOT_DIR}
)

add_subdirectory(aarch64)

add_subdirectory(${CMAKE_ROOT_DIR}/drivers ${CMAKE_HOME_DIRECTORY}/build/drivers)

set(TESTT ${CMAKE_HOME_DIRECTORY}/tools)

# Generate build info(git head + whoami + date) as build.h
add_custom_target(build_h_target ALL
				COMMAND /bin/bash ${TESTT}/build_string.sh
				WORKING_DIRECTORY ${TESTT}
				COMMENT "Generating build.h")


if ("${TEST}" STREQUAL "all")
	message("[Test] fboot ${TEST}")
	# TODOL Add test code for fboot
endif()

set(FBOOT_INCLUDE
	${CMAKE_CURRENT_LIST_DIR}/include
	${CMAKE_CURRENT_LIST_DIR}/include/arm64
)

add_library(lib STATIC
	string/memchr.c
	string/memcmp.c
	string/memcpy.c
	string/memmove.c
	string/memscan.c
	string/memset.c
	string/strcat.c
	string/strchr.c
	string/strcmp.c
	string/strcoll.c
	string/strcpy.c
	string/strerror.c
	string/strlcat.c
	string/strlcpy.c
	string/strlen.c
	string/strncat.c
	string/strncmp.c
	string/strncpy.c
	string/strnlen.c
	string/strpbrk.c
	string/strrchr.c
	string/strspn.c
	string/strstr.c
	string/strtok.c
	string/strxfrm.c
	printf.c
)

target_link_libraries(lib
	PUBLIC
	uart
)

target_include_directories(lib
	PUBLIC
	${BOOTLOADER_COMMON_INCLUDES}
)

add_executable(fboot_n main.c dma.c)

add_dependencies(fboot_n build_h_target)

target_link_libraries(fboot_n
	PUBLIC
	lib
	aarch64
	dwc_ssi
)

target_include_directories(fboot_n
	PUBLIC
	include
	include/arm64
	${BOOTLOADER_COMMON_INCLUDES}
)

target_link_options(fboot_n PRIVATE "-T${CMAKE_SOURCE_DIR}/fboot.lds")

add_custom_command(TARGET fboot_n POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O binary fboot_n fboot_n.bin
	COMMAND ${CMAKE_OBJDUMP} -d 	fboot_n > fboot_n.dump
	COMMAND ${CMAKE_OBJDUMP} -d -S	fboot_n > fboot_n.with_source.dump
)
