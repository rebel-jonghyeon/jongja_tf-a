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

clean_tf-a() {
	cd ${BOOTLOADER_TF_A}
		make distclean > /dev/null
		cd ${REBELH_TOP}

	if [ -n ${BINARY_BOOTLOADER_TF_A} ]; then
		rm -r ${BINARY_BOOTLOADER_TF_A}/bl*.*
	fi
}

build_tf-a() {
	if [ ${PLATFORM} == "zebu" ] || [ ${PLATFORM} == "zebu_poc" ]; then
		ZEBU=1
	else
		ZEBU=0
	fi
	if [ ${MODE} == "debug" ]; then
		DEBUG=1
	else
		DEBUG=0
	fi
	if [ ${DCLUSTER} == "yes" ]; then
		DCL_CNT=2
	else
		DCL_CNT=0
	fi

	cd ${BOOTLOADER_TF_A}
		make PLAT=rebel_h W=0 DEBUG=${DEBUG} ZEBU=${ZEBU} ZEBU_POC=${ZEBU_POC} DCL_CNT=${DCL_CNT} \
			USE_GPT=${USE_GPT} NCHANNEL=${NCHANNEL} \
			PCIE_PHY_SRAM_LOAD=${PCIE_PHY_SRAM_LOAD} EVT_VER=${EVT_VER} \
			CHIPLET_COUNT=${CHIPLET_COUNT} \
			BUS_FREQ=${BUS_FREQ} DCL_FREQ=${DCL_FREQ} \
			HBM_DATA_RATE=${HBM_DATA_RATE} UCIE_DATA_RATE=${UCIE_DATA_RATE} \
			HBM_TEST=${HBM_TEST} CP=0 CROSS_COMPILE=${COMPILER_PATH_ARM64}/aarch64-none-elf- -j$(nproc) all
		if [ $? -ne 0 ]; then exit 1; fi

		cp ./build/rebel_h/*/bl*.bin ./build/rebel_h/*/bl*/bl*.{dump,elf,map} ${BINARY_BOOTLOADER_TF_A}

		cd ${REBELH_TOP}
}

transhex_tf-a() {
	${REBELH_TOP}/scripts/transhex.sh tf-a ${NCHANNEL}
}

sign_tf-a() {
	if [ ${SIGN} = 1 ]; then
		${REBELH_TOP}/scripts/sign_image.sh \
			${BINARY_BOOTLOADER_TF_A}/bl1.bin \
			${BINARY_BOOTLOADER_TF_A}/bl1.sign

		${REBELH_TOP}/scripts/sign_image.sh \
			${BINARY_BOOTLOADER_TF_A}/bl2.bin \
			${BINARY_BOOTLOADER_TF_A}/bl2.sign

		${REBELH_TOP}/scripts/sign_image.sh \
			${BINARY_BOOTLOADER_TF_A}/bl31.bin \
			${BINARY_BOOTLOADER_TF_A}/bl31.sign
	fi
}

doxygen_tf-a() {
	echo "TODO: doxygen_tf-a"
}
