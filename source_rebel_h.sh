#!/bin/bash
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

HOST_NAME=$(hostname)
if [[ "$HOST_NAME" =~ ^vwp* ]]; then
	# VWP environment
	export COMPILER_PATH_CMAKE="${COMPILER_PATH_CMAKE:-/user/travemul/ZEBU/REBEL_H/common/cmake/cmake-3.27.2-linux-x86_64/bin/cmake}"
	export COMPILER_PATH_ARM64="${COMPILER_PATH_ARM64:-/user/travemul/ZEBU/REBEL_H/common/aarch64-none-elf/bin}"
	export COMPILER_PATH_ARM32="${COMPILER_PATH_ARM32:-/user/travemul/ZEBU/REBEL_H/common/arm-none-eabi/bin}"
	export COMPILER_PATH_ZEPHYR_RISCV="${COMPILER_PATH_ZEPHYR_RISCV:-/user/travemul/ZEBU/REBEL_H/common/sdk}"
	# VWP bin directory (temporally used)
	export PATH="${PATH}:/user/travemul/ZEBU/REBEL_H/common/bin"
else
	# Client environment
	export COMPILER_PATH_CMAKE=cmake
	export COMPILER_PATH_ARM64="${COMPILER_PATH_ARM64:-/tools/arm-gnu-toolchain-13.2.Rel1-x86_64-aarch64-none-elf/bin}"
	export COMPILER_PATH_ARM32="${COMPILER_PATH_ARM32:-/tools/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin}"
	export COMPILER_PATH_ZEPHYR_RISCV="${COMPILER_PATH_ZEPHYR_RISCV:-/opt/cmrt/sdk}"
fi
