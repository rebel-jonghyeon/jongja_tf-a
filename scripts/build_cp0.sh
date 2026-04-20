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

clean_cp0() {
	cd ${FREERTOS_TOP}
		rm -r ./build
		cd ${REBELH_TOP}

	if [ -n ${BINARY_FREERTOS_CP} ]; then
		rm -r ${BINARY_FREERTOS_CP}/*
	fi
}

build_cp0() {
	clean_cp0

	cd ${FREERTOS_TOP}
		${COMPILER_PATH_CMAKE} -DBUILD_TARGET=cp0 -B ./build -S .	\
			-DPLATFORM=${PLATFORM} -DMODE=${MODE} -DTEST=${TEST}	\
			-DCHIPLET_COUNT=${CHIPLET_COUNT} \
			-DBUILD_NOTE="${BUILD_NOTE}"	\
			-DEVT_VER=${EVT_VER}
		if [ $? -ne 0 ]; then exit 1; fi

		${COMPILER_PATH_CMAKE} --build ./build
		if [ $? -ne 0 ]; then exit 1; fi

		cp -f ./build/[fF]*	${BINARY_FREERTOS_CP}

		cd ${REBELH_TOP}
}

transhex_cp0() {
	${REBELH_TOP}/scripts/transhex.sh cp0 ${NCHANNEL}
}

sign_cp0() {
	${REBELH_TOP}/scripts/sign_image.sh \
		${BINARY_FREERTOS_CP}/freertos_kernel.bin \
		${BINARY_FREERTOS_CP}/freertos_kernel.sign
}

doxygen_cp0() {
	echo "TODO: doxygen_cp0"
}
