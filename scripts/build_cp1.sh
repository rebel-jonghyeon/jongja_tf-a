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

clean_cp1() {
	# BL31_CP1
	cd ${BOOTLOADER_TF_A}
		make distclean > /dev/null
		cd ${REBELH_TOP}

	# FreeRTOS_CP1
	cd ${FREERTOS_TOP}
		rm -r ./build
		cd ${REBELH_TOP}

	if [ -n ${BINARY_FREERTOS_CP1} ]; then
		rm -r ${BINARY_FREERTOS_CP1}/*
	fi
}

build_cp1() {
	clean_cp1

	# BL31_CP1
	if [ ${PLATFORM} == "zebu" ]; then
		ZEBU=1
	else
		ZEBU=0
	fi
	if [ ${PLATFORM} == "zebu_poc" ]; then
		ZEBU=1
		ZEBU_POC=1
	else
		ZEBU=0
		ZEBU_POC=0
	fi
	if [ ${MODE} == "debug" ]; then
		DEBUG=1
	else
		DEBUG=0
	fi

	cd ${BOOTLOADER_TF_A}
		make PLAT=rebel_h W=0 DEBUG=${DEBUG} ZEBU=${ZEBU} ZEBU_POC=${ZEBU_POC} USE_GPT=${USE_GPT} CP=1 \
			EVT_VER=${EVT_VER} \
			CROSS_COMPILE=${COMPILER_PATH_ARM64}/aarch64-none-elf- -j$(nproc) all
		if [ $? -ne 0 ]; then exit 1; fi

		cp ./build/rebel_h/*/bl31.bin ./build/rebel_h/*/bl31*/bl31*.{dump,elf,map} ${BINARY_FREERTOS_CP1}

		cd ${REBELH_TOP}

	# FreeRTOS_CP1
	cd ${FREERTOS_TOP}
		${COMPILER_PATH_CMAKE} -DBUILD_TARGET=cp1 -B ./build -S .	\
			-DPLATFORM=${PLATFORM} -DMODE=${MODE} \
			-DCHIPLET_COUNT=${CHIPLET_COUNT}
		if [ $? -ne 0 ]; then exit 1; fi

		${COMPILER_PATH_CMAKE} --build ./build
		if [ $? -ne 0 ]; then exit 1; fi

		cp -f ./build/[fF]*	${BINARY_FREERTOS_CP1}

		cd ${REBELH_TOP}
}

transhex_cp1() {
	${REBELH_TOP}/scripts/transhex.sh cp1 ${NCHANNEL}
}

sign_cp1() {
	# BL31_CP1
	$REBELH_TOP/scripts/sign_image.sh \
		${BINARY_FREERTOS_CP1}/bl31.bin \
		${BINARY_FREERTOS_CP1}/cp1_bl31.sign

	# FreeRTOS_CP1
	${REBELH_TOP}/scripts/sign_image.sh \
		${BINARY_FREERTOS_CP1}/freertos_kernel.bin \
		${BINARY_FREERTOS_CP1}/freertos_kernel.sign
}

doxygen_cp1() {
	echo "TODO: doxygen_cp1"
}
