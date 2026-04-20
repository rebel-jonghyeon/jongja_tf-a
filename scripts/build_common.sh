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

print_help() {
	echo ""
	echo "Welcome to REBEL-H build system"
	echo ""
	echo "Usage: ./build.sh <command> [-h | --help] [-c | --clean] [-p | --platform] [-m | --mode] \
[-n | --nchannel] [-s | --sign] [-t | --test]"
	echo ""
	echo "These are list of commands"
	echo "   all            : build all images   (by default)"
	echo "   bootrom        : build bootrom  for fboot"
	echo "   tf-a           : build tf-a     for bl1/bl2/bl31"
	echo "   cp0            : build freertos for ca73 blk_cp0"
	echo "   cp1            : build freertos for ca73 blk_cp1"
	echo "   cm             : build freertos for cm7"
	echo "   cmrt           : build all cmrt for rot"
	echo "   clean          : clean all binaries (same as -c option)"
	echo ""
	echo "Build options"
	echo "   -h, --help     : print help"
	echo "   -c, --clean    : clean all binaries (same as './build.sh clean)"
	echo "   -p, --platform : select target platform"
	echo "                    -p zebu          : build images for zebu platform   (by default)"
	echo "                    -p silicon       : build images for real silicon"
	echo "   -m, --mode     : select build mode"
	echo "                    -m debug         : build images for debug mode   (-g)   (by default)"
	echo "                    -m release       : build images for release mode (-O2)"
	echo "   -n, --nchannel : select hbm channel"
	echo "                    -n ch1           : hbm 1 channel"
	echo "                    -n ch16          : hbm 16 channel   (by default)"
	echo "   -s, --sign     : select signing image"
	echo "                    -s 0             : Not Sign Image   (by default)"
	echo "                    -s 1             : Sign Image "
	echo "   -t, --test     : add test functions"
	echo "                    -t               : add all tests related to 'command'"
	echo "                    -t all           : add all tests related to 'command'"
	echo "                    -t none          : no test (by default)"
	echo "   -g, --gpt      : use GPT addressing"
	echo "                    -g 1             : boot from GPT (by default)"
	echo "                    -g 0             : boot from preloading"
	echo "   -dcl, --dcluster : build with dcluster"
	echo "                    -dcl             : for image with dcluster"
	echo "                    -dcl yes         : for image with dcluster"
	echo "                    -dcl no          : for image without dcluster (default)"
	echo ""
	echo "These are driver specific options for DRAM and PCIe"
	echo ""
	echo "PCIe related options"
	echo "   -ps, --PCIE_TARGET_SPEED     : set PCIe target speed (1 ~ 5)"
	echo "   -pn, --PCIE_TARGET_NUM_LANES : set PCIe lane number (1 ~ 16)"
	echo "   -pi, --PCIE_IATU_NUM_REGION  : set PCIe iATU region number (1 ~ 64)"
	echo "   -pl, --PCIE_PHY_SRAM_LOAD    : set PCIe phy sram loaded from bootrom (1), default 0"
	echo "UCIe related options"
	echo " 	 -evt,--EVT_VER				  : select EVT ver for UCIE"
	echo ""
	echo "e.g."
	echo "./build.sh      <- Build all images for ZEBU with debug mode"
	echo "./build.sh -h   <- Print help"
	echo "./build.sh -c   <- Clean all"
	echo "./build.sh -n ch16   <- HBM 16ch"
	echo "./build.sh boot -p silicon -m release   <- Build bootrom for silicon with release mode"
	echo "./build.sh cmrt -p silicon -m release   <- Build all cmrt for silicon with release mode"
	echo ""
}

clean_all() {
	clean_bootrom
	clean_tf-a
if [ "${CMRT_BUILD}" == "1" ]; then
	clean_cmrt
fi
	clean_cp0
	clean_cp1
	clean_cm
}

build_all() {
	build_bootrom
	build_tf-a
if [ "${CMRT_BUILD}" == "1" ]; then
	build_cmrt
fi
	build_cp0
	build_cp1
	build_cm
}

transhex_all() {
	transhex_bootrom
	transhex_tf-a
if [ "${CMRT_BUILD}" == "1" ]; then
	transhex_cmrt
fi
	transhex_cp0
	transhex_cp1
	transhex_cm
}

sign_all() {
	sign_bootrom
	sign_tf-a
if [ "${CMRT_BUILD}" == "1" ]; then
	sign_cmrt
fi
	sign_cp0
	sign_cp1
	sign_cm
}

doxygen_all() {
	doxygen_bootrom
	doxygen_tf-a
if [ "${CMRT_BUILD}" == "1" ]; then
	doxygen_cmrt
fi
	doxygen_cp0
	doxygen_cp1
	doxygen_cm
}

sign_pcie() {
	source ${REBELH_TOP}/scripts/make_signed_fw.sh dwc_pcie5_phy
}

sign_ucie() {
if [ "${UCIE_FW_BIN_PATH}" != "" ]; then
	./scripts/bin2hex.pl ${UCIE_FW_BIN_PATH} ./binaries/3rd_party/ucie.hex
fi
	source ${REBELH_TOP}/scripts/make_signed_fw.sh ucie
	cp ${REBELH_TOP}/binaries/3rd_party/ucie_change_endian.bin ${REBELH_TOP}/binaries/ucie_phy_pre_load.bin
}

generate_gpt() {
	sign_pcie
	sign_ucie
	echo "Generate flash gpt image"
	if [ "${PCIE_PHY_SRAM_LOAD}" -ne 0 ]; then
		python3 ${REBELH_TOP}/scripts/gen_gpt_flash.py ${SIGN} ${USE_GPT} ${PLATFORM} ${PCIE_PHY_SRAM_LOAD} || return 1
	else
		python3 ${REBELH_TOP}/scripts/gen_gpt_flash.py ${SIGN} ${USE_GPT} ${PLATFORM} || return 1
	fi
}

generate_t32_flash() {
	echo "Generate flash gpt image"
	python3 ${REBELH_TOP}/scripts/convert_flash_hex_for_t32.py || return 1
}

generate_dediprog_bin() {
	echo "Generate Dediprog binary image"
	python3 ${REBELH_TOP}/scripts/convert_flash_hex_to_bin.py \
		${REBELH_TOP}/binaries/flash_gpt.hex \
		${REBELH_TOP}/binaries/flash_gpt.bin || return 1
	python3 ${REBELH_TOP}/scripts/conv_endian.py \
		${REBELH_TOP}/binaries/flash_gpt.bin \
		${REBELH_TOP}/binaries/flash_gpt_dp.bin || return 1
}
