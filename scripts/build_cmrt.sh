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

source_cmrt() {
	source ./source_rebel_h.sh
	source ./source_directories.sh

	cd ${BOOTLOADER_CMRT}
		source sourceme-env-setup
		source cmrt-zephyr-env.sh
		cd ${REBELH_TOP}
}

_clean_cmrt() {
	# Check CMRT variables
	if [ -n ${CMRT_SDK_BASE} ]; then
		source_cmrt
	fi

	cd ${BOOTLOADER_CMRT_SAMPLE}
		cmd=`make pristine RELEASE_BUILD=1`
		if [ $? -ne 0 ]; then exit 1; fi
		cd ${REBELH_TOP}

	if [ -n ${BINARY_BOOTLOADER_ROT} ]; then
		rm ${BINARY_BOOTLOADER_ROT}/* 2>/dev/null
	fi
	if [ -n ${BINARY_CONTAINER_ROT} ]; then
		rm ${BINARY_CONTAINER_ROT}/blank/* 2>/dev/null
	fi
	if [ -n ${BINARY_CONTAINER_ROT} ]; then
		rm ${BINARY_CONTAINER_ROT}/tested/* 2>/dev/null
	fi
	if [ -n ${BINARY_CONTAINER_ROT} ]; then
		rm ${BINARY_CONTAINER_ROT}/provisioned/* 2>/dev/null
	fi
	if [ -n ${BINARY_ZEPHYR_ROT} ]; then
		rm ${BINARY_ZEPHYR_ROT}/* 2>/dev/null
	fi
	if [ -n ${BINARY_XIP_ROT} ]; then
		rm ${BINARY_XIP_ROT}/* 2>/dev/null
	fi
}
clean_cmrt() {
	${REBELH_TOP}/scripts/build_cmrt.sh _clean_cmrt
}

_build_sboot_s() {
	# Check CMRT variables
	if [ -n ${CMRT_SDK_BASE} ]; then
		source_cmrt
	fi

	cd ${BOOTLOADER_SBOOT_S}
		cmd=`make RELEASE_BUILD=1`
		if [ $? -ne 0 ]; then exit 1; fi

		cp -r build/sboot*	${BINARY_BOOTLOADER_ROT}
		cp -r build/otp*	${BINARY_BOOTLOADER_ROT}
		cd ${REBELH_TOP}
}
build_sboot_s() {
	_build_sboot_s
}

_build_tboot_s() {
	# Check CMRT variables
	if [ -n ${CMRT_SDK_BASE} ]; then
		source_cmrt
	fi

	cd ${BOOTLOADER_TBOOT_S}
		if [ ${TEST} == 'all' ] ; then
			cmd=`make RELEASE_BUILD=2`
		else
			cmd=`make RELEASE_BUILD=1`
		fi
		if [ $? -ne 0 ]; then exit 1; fi

		cp -r build/mw\.*		${BINARY_ZEPHYR_ROT}
		cp -r build/os.img*		${BINARY_ZEPHYR_ROT}
		cp -r build/flash_os*	${BINARY_ZEPHYR_ROT}
		cd ${REBELH_TOP}
}
build_tboot_s() {
	_build_tboot_s
}

_build_blank_cont() {
	# Check CMRT variables
	if [ -n ${CMRT_SDK_BASE} ]; then
		source_cmrt
	fi

	cd "${BOOTLOADER_CONTAINER}/blank"
		cmd=`make RELEASE_BUILD=1`
		if [ $? -ne 0 ]; then exit 1; fi

		cp -r build/blank\.* ${BINARY_CONTAINER_ROT}/blank/
		cd ${REBELH_TOP}
}
build_blank_cont() {
	_build_blank_cont
}

_build_tested_cont() {
	# Check CMRT variables
	if [ -n ${CMRT_SDK_BASE} ]; then
		source_cmrt
	fi

	cd "${BOOTLOADER_CONTAINER}/tested"
		cmd=`make RELEASE_BUILD=1`
		if [ $? -ne 0 ]; then exit 1; fi

		cp -r build/tested\.* ${BINARY_CONTAINER_ROT}/tested/
		cd ${REBELH_TOP}
}
build_tested_cont() {
	_build_tested_cont
}

_build_provisioned_cont() {
	# Check CMRT variables
	if [ -n ${CMRT_SDK_BASE} ]; then
		source_cmrt
	fi

	cd "${BOOTLOADER_CONTAINER}/provisioned"
		cmd=`make RELEASE_BUILD=1`
		if [ $? -ne 0 ]; then exit 1; fi

		cp -r build/provisioned\.* ${BINARY_CONTAINER_ROT}/provisioned/
		cd ${REBELH_TOP}
}
build_provisioned_cont() {
	_build_provisioned_cont
}

_build_cmrt_xip() {
	cd ${BINARY_XIP_ROT}
		SBOOT_S0_IMG=./../BootLoader_ROT/otp0.hex
		SBOOT_S1_IMG=./../BootLoader_ROT/otp1.hex
		TBOOT_S_IMG=./../Zephyr_ROT/flash_os1.hex
		if [ -e "${SBOOT_S0_IMG}" ] && [ -e "${SBOOT_S1_IMG}" ] && [ -e "${TBOOT_S_IMG}" ] ; then
			echo "generate XIP sboot_s & tboot_s flash img"

			cat ${SBOOT_S0_IMG} | fold -w 2 > xip_sboot_tboot_s.hex
			cat ${SBOOT_S1_IMG} | fold -w 2 >> xip_sboot_tboot_s.hex
			#16384 bytes filled

			#offset 0x10000 starts from 65,537th line (starting from 1st line)
			tail -n +16385 ${TBOOT_S_IMG} >> xip_sboot_tboot_s.hex
		else
			echo "Sboot_s or Tboot_s img is missing! can't generate XIP img."
		fi
		cd ${REBELH_TOP}
}
build_cmrt_xip() {
	_build_cmrt_xip
}

_build_cmrt() {
	# Check CMRT variables
	if [ -n ${CMRT_SDK_BASE} ]; then
		source_cmrt
	fi

	build_sboot_s
	build_tboot_s
	build_blank_cont
	build_tested_cont
	build_provisioned_cont
	build_cmrt_xip
}
build_cmrt() {
	_build_cmrt
}

transhex_cmrt() {
	echo "TODO: transhex_cmrt"
}

sign_cmrt() {
	echo "TODO: sign_cmrt"
}

doxygen_cmrt() {
	echo "TODO: doxygen_cmrt"
}

if [ -n "${1}" ] && [ "${1:0:1}" == "_" ]; then
	eval "${1}"
fi
