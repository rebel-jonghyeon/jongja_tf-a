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

clean_bootrom() {
	cd ${BOOTLOADER_BOOTROM}
		rm -r ./build > /dev/null
		cd ${REBELH_TOP}

	if [ -n ${BINARY_BOOTLOADER_BOOTROM} ]; then
		rm -r ${BINARY_BOOTLOADER_BOOTROM}/*boot*
	fi
}

build_bootrom() {
	cd ${BOOTLOADER_BOOTROM}
		${COMPILER_PATH_CMAKE} -B ./build -S .	\
			-DPLATFORM=${PLATFORM} -DUSE_GPT=${USE_GPT}
		if [ $? -ne 0 ]; then exit 1; fi

		${COMPILER_PATH_CMAKE} --build ./build
		if [ $? -ne 0 ]; then exit 1; fi

		cp -f ./build/*_n* ${BINARY_BOOTLOADER_BOOTROM}

		cd ${REBELH_TOP}

	${REBELH_TOP}/scripts/transhex.sh boot ${NCHANNEL}
}

transhex_bootrom() {
	${REBELH_TOP}/scripts/transhex.sh boot ${NCHANNEL}
}

sign_bootrom() {
	echo "TODO: sign_bootrom"
}

doxygen_bootrom() {
	echo "TODO: doxygen_bootrom"
}
