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
add_definitions(-DBOOTLOADER=1)

set(CMAKE_ASM_COMPILER		$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-gcc)
set(CMAKE_C_COMPILER		$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-gcc)
set(CMAKE_CXX_COMPILER		$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-gcc)
set(CMAKE_LINKER			$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-ld)
set(CMAKE_NM				$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-nm)
set(CMAKE_OBJCOPY			$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-objcopy)
set(CMAKE_OBJDUMP			$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-objdump)
set(CMAKE_SIZE				$ENV{COMPILER_PATH_ARM64}aarch64-none-elf-size)

set(CMAKE_ASM_FLAGS			"-march=armv8-a")
set(CMAKE_C_FLAGS			"-march=armv8-a -mcpu=cortex-a73 -nostdlib -nostdinc -fno-builtin -mstrict-align -D__TARGET_BOOTROM=1 -O2")
set(CMAKE_CXX_FLAGS			"-march=armv8-a -mcpu=cortex-a73")
set(CMAKE_EXE_LINKER_FLAGS	"-nostartfiles -specs=nosys.specs")
set(ARCH					"CA73")

if (MODE STREQUAL debug)
	set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -g")
elseif (MODE STREQUAL release)
	set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -s")
endif()
