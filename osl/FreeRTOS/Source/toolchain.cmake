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

# References of Compiler Options
# https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
# https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
# https://gcc.gnu.org/onlinedocs/gcc/AArch64-Options.html
# https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html

if(BUILD_TARGET STREQUAL cp0)
	set(CMAKE_C_COMPILER		$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-gcc)
	set(CMAKE_CXX_COMPILER		$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-gcc)
	set(CMAKE_ASM_COMPILER		$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-gcc)
	set(CMAKE_LINKER			$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-ld)
	set(CMAKE_NM				$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-nm)
	set(CMAKE_OBJCOPY			$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-objcopy)
	set(CMAKE_OBJDUMP			$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-objdump)
	set(LINKER_SCRIPT			${CMAKE_HOME_DIRECTORY}/FreeRTOS.ld)

	# GCC Flags
	# '-mcpu=name'           : Specifies the name of the target ARM processor.
	# '-mabi=name'           : Generate code for the specified data model.
	# '-nostartfiles'        : Do not use the standard system startup files when linking.
	# '-lc -lgcc -lm'        : C libraries. (<=> -nolibc, -nostdlib)
	# '-Werror'              : Make all warnings into errors.
	# '-Wall'                : Note that some warning flags are not implied by '-Wall'.
	# '-D name=definition'   : The contents of definition are tokenized and processed
	#     as if they appeared during translation phase three in a ‘#define’ directive.
	# '-Xlinker option'      : Pass option as an option to the linker
	#     '-M=<mapfile>' or '-Map=<mapfile>' : Print a link map to the file <mapfile>
	set(CMAKE_C_FLAGS			"-march=armv8-a+crypto -mcpu=cortex-a73 -mabi=lp64 -nostartfiles -lc -lgcc -lm \
								-Werror \
								-Wall \
								-Wno-unused-parameter \
								-Wno-unused-but-set-variable \
								-Wno-unused-function \
								-D__RUN_RTOS=1 -D__TARGET_CP=0")
	set(CMAKE_EXE_LINKER_FLAGS	"-T ${LINKER_SCRIPT} -nostartfiles -Xlinker -Map=FreeRTOS.map")

	#For FreeRTOS main CMakeLists.txt
	set(FREERTOS_PORT			"GCC_ARM_CA73" CACHE STRING "FreeRTOS port name")
	set(ARCH					"CA73")
	if (MODE STREQUAL debug)
		# '-O2'                    : Better performance & Worse compilation time.
		#     It does not involve a space-speed tradeoff.
		#     This flag increases both compilation time and the performance of the generated code.
		# '-fno-inline-functions'  : Prevent '-finline-functions'.
		#     Optimization flags, such as -O2 and -O3, include the '-finline-functions' flag.
		#     '-finline-functions' can remove function labels, making debugging more difficult.
		set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -g -O2 -fno-inline-functions")
	elseif (MODE STREQUAL release)
		# '-O3' : Optimize more than '-O2' flag.
		#     Improve the performance of loops, such as cache optimization.
		# '-s'  : Remove all symbol table and relocation information from the executable.
		set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -s -O3 -finline-functions")
	endif()

	if (${TEST} STREQUAL all)
		set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -D__TEST=1")
	endif()
	# '-falign-labels=n'     : Align all branch targets to a power-of-two boundary.
	# '-fno-reorder-functions' : Prevent '-freorder-functions'.
	#     Optimization flags, such as -O2 and -O3, include the '-freorder-functions' flag.
	#     '-freorder-functions' can change address of functions, especially the entrypoint.
	# '-fno-strict-aliasing' : Prevent '-fstrict-aliasing' flag.
	#     '-fstrict-aliasing' flag allow the compiler to assume the strictest aliasing rules
	#     applicable to the language being compiled.
	# '-fno-tree-vectorize'  : Prevent '-ftree-vectorize' flag.
	#     '-ftree-vectorize' flag enables '-ftree-loop-vectorize' and '-ftree-slp-vectorize'.
	#     '-ftree-loop-vectorize' : Combine repeated instructions into vector instructions.
	#     '-ftree-slp-vectorize'  : Combine similar independent instructions into vector instructions.
	# '-mstrict-align'       : Allow generating memory accesses that may not be aligned
	#     on a natural object boundary as described in the architecture specification.
	set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -falign-labels=32 \
							-fno-reorder-functions -fno-strict-aliasing -fno-tree-vectorize -mstrict-align")
elseif(BUILD_TARGET STREQUAL cp1)
	set(CMAKE_C_COMPILER		$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-gcc)
	set(CMAKE_CXX_COMPILER		$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-gcc)
	set(CMAKE_ASM_COMPILER		$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-gcc)
	set(CMAKE_LINKER			$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-ld)
	set(CMAKE_NM				$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-nm)
	set(CMAKE_OBJCOPY			$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-objcopy)
	set(CMAKE_OBJDUMP			$ENV{COMPILER_PATH_ARM64}/aarch64-none-elf-objdump)
	set(LINKER_SCRIPT			${CMAKE_HOME_DIRECTORY}/FreeRTOS_CP1.ld)

	set(CMAKE_C_FLAGS			"-march=armv8-a+crypto -mcpu=cortex-a73 -mabi=lp64 -nostartfiles -lc -lgcc -lm \
								-Werror \
								-Wall \
								-Wno-unused-parameter \
								-Wno-unused-but-set-variable \
								-Wno-unused-function \
								-D__RUN_RTOS=1 -D__TARGET_CP=1")
	set(CMAKE_EXE_LINKER_FLAGS	"-T ${LINKER_SCRIPT} -nostartfiles -Xlinker -Map=FreeRTOS.map")

	set(FREERTOS_PORT			"GCC_ARM_CA73" CACHE STRING "FreeRTOS port name")
	set(ARCH					"CA73")
	if (MODE STREQUAL debug)
		set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -g -O2 -fno-inline-functions")
	elseif (MODE STREQUAL release)
		set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -s -O3 -finline-functions")
	endif()
	set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -falign-labels=32 \
							-fno-reorder-functions -fno-strict-aliasing -fno-tree-vectorize -mstrict-align")
elseif(BUILD_TARGET STREQUAL cm)
	set(CMAKE_C_COMPILER		$ENV{COMPILER_PATH_ARM32}/arm-none-eabi-gcc)
	set(CMAKE_CXX_COMPILER		$ENV{COMPILER_PATH_ARM32}/arm-none-eabi-gcc)
	set(CMAKE_ASM_COMPILER		$ENV{COMPILER_PATH_ARM32}/arm-none-eabi-gcc)
	set(CMAKE_LINKER			$ENV{COMPILER_PATH_ARM32}/arm-none-eabi-ld)
	set(CMAKE_NM				$ENV{COMPILER_PATH_ARM32}/arm-none-eabi-gcc-nm)
	set(CMAKE_OBJCOPY			$ENV{COMPILER_PATH_ARM32}/arm-none-eabi-objcopy)
	set(CMAKE_OBJDUMP			$ENV{COMPILER_PATH_ARM32}/arm-none-eabi-objdump)
	set(LINKER_SCRIPT			${CMAKE_HOME_DIRECTORY}/FreeRTOS_CM7.ld)

	# Flags
	set(CMAKE_C_FLAGS			"-mthumb -march=armv7e-m -mtune=cortex-m7 -Werror -Wall -mfpu=fpv5-d16 -mfloat-abi=hard -D__TARGET_PCIE=1 -D__RUN_RTOS=1")
	set(CMAKE_ASM_FLAGS			"-mthumb -march=armv7e-m -mtune=cortex-m7 -Werror -Wall -mfpu=fpv5-d16 -mfloat-abi=hard -D__TARGET_PCIE=1 -D__RUN_RTOS=1")
	set(CMAKE_EXE_LINKER_FLAGS	"-T ${LINKER_SCRIPT} -nostartfiles -Xlinker -Map=FreeRTOS_CM7.map")

	#For FreeRTOS main CMakeLists.txt
	set(FREERTOS_PORT			"GCC_ARM_CM7" CACHE STRING "FreeRTOS port name")
    set(ARCH					"CM7")
	if (MODE STREQUAL debug)
		set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -g")
	elseif (MODE STREQUAL release)
		set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -fno-reorder-functions -s -O2")
	endif()
	if ("${TEST}" STREQUAL "all")
		set(CMAKE_C_FLAGS	"${CMAKE_C_FLAGS} -D__TEST=1")
	endif()
endif()
