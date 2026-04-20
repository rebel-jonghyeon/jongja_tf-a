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

clean_cm() {
	cd ${FREERTOS_TOP}
		rm -r ./build
		cd ${REBELH_TOP}

	if [ -n ${BINARY_FREERTOS_PCIE} ]; then
		rm -r ${BINARY_FREERTOS_PCIE}/*
	fi
}

build_cm() {
	clean_cm

	cd ${FREERTOS_TOP}
		if [ "$USE_PCIE" != "0" ]; then
			PCIE_OPTION="-DPCIE_TARGET_SPEED=${PCIE_TARGET_SPEED}	\
				-DPCIE_TARGET_NUM_LANES=${PCIE_TARGET_NUM_LANES}	\
				-DPCIE_IATU_NUM_REGION=${PCIE_IATU_NUM_REGION}		\
				-DPCIE_PHY_SRAM_LOAD=${PCIE_PHY_SRAM_LOAD}"
		fi

		${COMPILER_PATH_CMAKE} -DBUILD_TARGET=cm -B ./build -S .	\
		-DPLATFORM=${PLATFORM} -DMODE=${MODE} -DTEST=${TEST}		\
		-DCHIPLET_COUNT=${CHIPLET_COUNT}							\
		-DUSE_PCIE=${USE_PCIE} $PCIE_OPTION

		if [ $? -ne 0 ]; then exit 1; fi

		${COMPILER_PATH_CMAKE} --build ./build
		if [ $? -ne 0 ]; then exit 1; fi

		cp -f ./build/[fF]*	${BINARY_FREERTOS_PCIE}

		cd ${REBELH_TOP}
}

transhex_cm() {
	${REBELH_TOP}/scripts/transhex.sh cm ${NCHANNEL}
}

sign_cm() {
	${REBELH_TOP}/scripts/sign_image.sh \
		${BINARY_FREERTOS_PCIE}/freertos_kernel.bin \
		${BINARY_FREERTOS_PCIE}/freertos_kernel.sign
}

doxygen_cm() {
	echo "TODO: doxygen_cm"
}
