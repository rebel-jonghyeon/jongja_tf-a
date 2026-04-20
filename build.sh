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

# Default Freq and Data Rate
BUS_FREQ=${BUS_FREQ:-1600}
DCL_FREQ=${DCL_FREQ:-1800}

HBM_DATA_RATE=${HBM_DATA_RATE:-9200}
UCIE_DATA_RATE=${UCIE_DATA_RATE:-12000}

source ./source_rebel_h.sh
source ./source_directories.sh

source scripts/build_common.sh
source scripts/build_bootrom.sh
source scripts/build_cmrt.sh
source scripts/build_tf-a.sh
source scripts/build_cp0.sh
source scripts/build_cp1.sh
source scripts/build_cm.sh

# Parse arguments
while [[ "$#" -gt 0 ]]; do
	case $1 in
		-h|--help)		print_help;	exit 0;;
		-c|--clean)		clean_all;	exit 0;;
		-p|--platform)	PLATFORM="${2}";	shift;;
		-m|--mode)		MODE="${2}";		shift;;
		-n|--nchannel)	NCHANNEL="${2}";	shift;;
		-s|--sign)		SIGN="${2}";		shift;;
		-g|--gpt)		USE_GPT="${2}";		shift;;
		--cmrt)			CMRT_BUILD="${2}";	shift;;
		-dcl|--dcluster)
			if [[ "${2:0:1}" == "-" || -z "${2}" ]]; then
				DCLUSTER="yes";
			else
				DCLUSTER="$2";	shift;
			fi;;
		-cl|--chiplet)
			if [[ "${2:0:1}" == "-" || -z "${2}" ]]; then
				CHIPLET_COUNT="4";
			elif [ "$2" -lt 1 ] || [ "$2" -gt 4 ]; then
				echo "Invalid chiplet count $2. Only 1,2,3,4 are supported"
				exit 1;
			else
				CHIPLET_COUNT="$2";	shift;
			fi;;

		-t|--test)
			if [[ "${2:0:1}" == "-" || -z "${2}" ]]; then
				TEST="all";
			else
				TEST="${2}";	shift;
			fi;;
		# PCIe related options
		-pu|--pcie)						USE_PCIE="${2}";				shift;;
		-pl|--PCIE_PHY_SRAM_LOAD)		PCIE_PHY_SRAM_LOAD="${2}";		shift;;
		-ps|--PCIE_TARGET_SPEED)		PCIE_TARGET_SPEED="${2}";		shift;;
		-pn|--PCIE_TARGET_NUM_LANES)	PCIE_TARGET_NUM_LANES="${2}";	shift;;
		-pi|--PCIE_IATU_NUM_REGION)		PCIE_IATU_NUM_REGION="${2}";	shift;;

		# Freq related options
		--bus_freq)		BUS_FREQ="${2}";	shift;;
		--dcl_freq)		DCL_FREQ="${2}";	shift;;

		# HBM test options
		-ht|--hbmtest)		HBM_TEST="${2}";		shift;;
		-hdr|--hbm_rate)	HBM_DATA_RATE="${2}";	shift;;

		# UCIe related options
		-udr|--ucie_rate)	UCIE_DATA_RATE="${2}";		shift;;
		--ucie_fw_bin)		UCIE_FW_BIN_PATH="${2}";	shift;;
		-evt|--evt_ver)		EVT_VER="${2}";				shift;;

		# Release Note
		--note)		BUILD_NOTE="${2}";		shift;;
		--rel_msg)	REL_MSG="${2}";			shift;;

		# Log Hash
		--loghash)	LOG_HASH_ENABLE="1";	;;
		--) shift;;
		*)	COMMAND="${1}";;
	esac
	shift
done

if [ "$USE_PCIE" == "0" ]; then
	PCIE_PHY_SRAM_LOAD="0";
fi

if [[ ! "$BUS_FREQ" =~ ^(1600|800)$ ]]; then
	echo "Available BUS frequency is 1600 and 800"
	exit 0
fi

if [[ ! "$DCL_FREQ" =~ ^(1800|1700|1600|1500|1400|1200|1000)$ ]]; then
	echo "Available DCL frequency is 1800, 1700, 1600, 1500, 1400, 1200 and 1000"
	exit 0
fi

if [[ ! "$HBM_DATA_RATE" =~ ^(4800|6400|8000|9200|9600)$ ]]; then
	echo "Available HBM data rate is 4800, 6400, 8000, 9200 and 9600"
	exit 0
fi

if [[ ! "$UCIE_DATA_RATE" =~ ^(16000|12000|8000|4000)$ ]]; then
	echo "Available UCIe Data Rate is 16000, 12000, 8000 and 4000"
	exit 0
fi

if  [ "$EVT_VER" == "" ]; then
	echo "Select EVT version \"-evt\" for UCIe FW"
	exit 0
else
	if [[ ! "$EVT_VER" =~ ^(0|1)$ ]]; then
		echo "Available EVT_VER is 0 and 1"
		exit 0
	fi
fi

if [ "$EVT_VER" == '1' ] && [ "${DCL_FREQ}" == '1800' ]; then
	DCL_FREQ=1700
fi

if [ "$COMMAND" = "clean" ]; then
	echo
	echo -e "----------------------------------------"
	echo -e "\t[Clean]"
	echo -e "----------------------------------------"
	echo
	clean_all
	exit 0
fi

# Set default options
COMMAND=${COMMAND:-all}
PLATFORM=${PLATFORM:-zebu}
MODE=${MODE:-debug}
NCHANNEL=${NCHANNEL:-ch16}
SIGN=${SIGN:-1}
TEST=${TEST:-all}
USE_GPT=${USE_GPT:-1}
USE_PCIE=${USE_PCIE:-1}
HBM_TEST=${HBM_TEST:-0}
CMRT_BUILD=${CMRT_BUILD:-0}
DCLUSTER=${DCLUSTER:-yes}
CHIPLET_COUNT=${CHIPLET_COUNT:-4}
PCIE_PHY_SRAM_LOAD=${PCIE_PHY_SRAM_LOAD:-1}

EVT_VER=${EVT_VER:-0}

UCIE_FW_BIN_PATH=${UCIE_FW_BIN_PATH:-""}
# Default UCIE FW path for chip revision
if [ "${UCIE_FW_BIN_PATH}" == "" ]; then
	if [ "${EVT_VER}" == "1" ]; then
		UCIE_FW_BIN_PATH=${REBELH_TOP}/binaries/3rd_party/ucie/evt1/fw_pls_shape_ovr_ab862.bin
	else
		UCIE_FW_BIN_PATH=${REBELH_TOP}/binaries/3rd_party/ucie/evt0/master_rt_9264e.bin
	fi
fi

fmt="   | %-25s| %-25s| %-25s|\n"

if [ "$LOG_HASH_ENABLE" == "1" ]; then
	echo
	echo -e "----------------------------------------"
	echo -e "\t[Log Hash Encoding]"
	echo -e "----------------------------------------"

	ENCODER_CMD="python3 scripts/log_hash/log_hash_encoder.py"

	if [ -n "$REL_MSG" ]; then
		ENCODER_CMD="$ENCODER_CMD --rel_msg \"$REL_MSG\""
	fi

	echo "Running: $ENCODER_CMD"
	eval $ENCODER_CMD

	if [ $? -ne 0 ]; then
		echo "Error: Log hash encoding failed"
		exit 1
	fi

	HASH_DIR="${PWD}_hash"
	if [ ! -d "$HASH_DIR" ]; then
		echo "Error: _hash directory was not created"
		exit 1
	fi

	cd "$HASH_DIR"
	echo "Build path switched to _hash directory: $(pwd)"

fi

echo
echo "-------------------------------------------------------------------------------------"
echo "COMPILER_PATH_CMAKE  = ${COMPILER_PATH_CMAKE}"
echo "COMPILER_PATH_ARM64  = ${COMPILER_PATH_ARM64}"
echo "COMPILER_PATH_ARM32  = ${COMPILER_PATH_ARM32}"
echo "COMPILER_PATH_ZEPHYR = ${COMPILER_PATH_ZEPHYR_RISCV}"
echo "-------------------------------------------------------------------------------------"
echo "Current working directory: `pwd`"
echo "-------------------------------------------------------------------------------------"
echo "Build options:"
echo "====================================================================================="
printf "${fmt}" "Command" "Platform" "MODE"
printf "${fmt}" "NCHANNEL" "SIGN" "Test"
printf "${fmt}" "USE_GPT" "HBM_TEST" "PCIE_PHY_SRAM_LOAD"
printf "${fmt}" "PCIE_TARGET_SPEED" "PCIE_TARGET_NUM_LANES" "PCIE_IATU_NUM_REGION"
printf "${fmt}" "USE_PCIE" "LOG_HASH_ENABLE"
printf "${fmt}" "EVT VER" "DCLUSTER" "CHIPLET_COUNT"
printf "${fmt}" "BUS FREQ (MHz)" "DCL FREQ (MHz)"
printf "${fmt}" "HBM Data Rate (Mbps)" "UCIe Data Rate (MT/s)"
echo "-------------------------------------------------------------------------------------"
printf "${fmt}" "${COMMAND}" "${PLATFORM}" "${MODE}"
printf "${fmt}" "${NCHANNEL}" "${SIGN}" "${TEST}"
printf "${fmt}" "${USE_GPT}" "${HBM_TEST}" "${PCIE_PHY_SRAM_LOAD}"
printf "${fmt}" "${PCIE_TARGET_SPEED:--}" "${PCIE_TARGET_NUM_LANES:--}" "${PCIE_IATU_NUM_REGION:--}"
printf "${fmt}" "${USE_PCIE}" "${LOG_HASH_ENABLE}"
printf "${fmt}" "EVT${EVT_VER}" "${DCLUSTER}" "${CHIPLET_COUNT}"
printf "${fmt}" "${BUS_FREQ}" "${DCL_FREQ}"
printf "${fmt}" "${HBM_DATA_RATE}" "${UCIE_DATA_RATE}"
echo "====================================================================================="

echo ""
echo "UCIe FW: ${UCIE_FW_BIN_PATH}"

echo
echo -e "----------------------------------------"
echo -e "\t[Clean] ${COMMAND}"
echo -e "----------------------------------------"
echo
eval "clean_${COMMAND}"

echo
echo -e "----------------------------------------"
echo -e "\t[Build] ${COMMAND}"
echo -e "----------------------------------------"
echo
eval "build_${COMMAND}"

echo
echo -e "----------------------------------------"
echo -e "\t[Transhex] ${COMMAND}"
echo -e "----------------------------------------"
echo
eval "transhex_${COMMAND}"

echo
echo -e "----------------------------------------"
echo -e "\t[Sign] ${COMMAND}"
echo -e "----------------------------------------"
echo
if [ $SIGN = 1 ]; then
	eval "sign_${COMMAND}"
fi

echo
echo -e "----------------------------------------"
echo -e "\t[Doxygen] ${COMMAND}"
echo -e "----------------------------------------"
echo
eval "doxygen_${COMMAND}"

echo
echo -e "----------------------------------------"
echo -e "\t[Done] ${COMMAND}"
echo -e "----------------------------------------"
echo
echo "Images are in '${BINARY_TOP}' directory"
echo

if [ "${USE_GPT}" == "1" ]; then
	if generate_gpt && generate_t32_flash && generate_dediprog_bin; then
		exit 0
	else
		echo "Error: GPT flash image generation failed"
		exit 1
	fi
fi

