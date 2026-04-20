#!/bin/bash

target_ip=${1}
b_path="${REBELH_TOP}/binaries/3rd_party"
key_path="${REBELH_TOP}/bootloader/rot/cmrt-zephyr-2.0.36/samples/cmrt/common"
s_path="${REBELH_TOP}/bootloader/rot/cmrt-zephyr-2.0.36/scripts"

${REBELH_TOP}/scripts/endian_swap.sh ${b_path}/${target_ip}.hex > ${b_path}/${target_ip}_change_endian.hex
xxd -r -p ${b_path}/${target_ip}_change_endian.hex > ${b_path}/${target_ip}_change_endian.bin
${REBELH_TOP}/scripts/gen-image-footer.py ${key_path}/prikey_ecdsa_p384.pem ${b_path}/${target_ip}_change_endian.bin \
    ${REBELH_TOP}/scripts/dummy_footer.json ${b_path}/${target_ip}_change_endian.bin.tmp
${REBELH_TOP}/scripts/gen-image-header.py ${b_path}/${target_ip}_change_endian.bin.tmp \
	${b_path}/${target_ip}_change_endian_sign.bin
xxd -e ${b_path}/${target_ip}_change_endian_sign.bin > ${b_path}/${target_ip}_change_endian_sign.hex
${s_path}/sboot_formatter.py ${b_path}/${target_ip}_change_endian_sign.hex
mv otp.hex ${b_path}/${target_ip}_change_endian_with_footer.hex
rm ${b_path}/${target_ip}_change_endian.bin.tmp

