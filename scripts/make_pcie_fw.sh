#!/bin/bash

b_path="../binaries/3rd_party"
key_path="../bootloader/rot/cmrt-zephyr-2.0.36/samples/cmrt/common"
s_path="../bootloader/rot/cmrt-zephyr-2.0.36/scripts"

./endian_swap.sh ${b_path}/dwc_pcie5_phy.hex > ${b_path}/dwc_pcie5_phy_change_endian.hex
xxd -r -p ${b_path}/dwc_pcie5_phy_change_endian.hex > ${b_path}/dwc_pcie5_phy_change_endian.bin
./gen-image-footer.py ${key_path}/prikey_ecdsa_p384.pem ${b_path}/dwc_pcie5_phy_change_endian.bin \
    ./dummy_footer.json ${b_path}/dwc_pcie5_phy_change_endian.bin.tmp
./gen-image-header.py ${b_path}/dwc_pcie5_phy_change_endian.bin.tmp ${b_path}/dwc_pcie5_phy_change_endian_sign.bin
xxd -e ${b_path}/dwc_pcie5_phy_change_endian_sign.bin > ${b_path}/dwc_pcie5_phy_change_endian_sign.hex
${s_path}/sboot_formatter.py ${b_path}/dwc_pcie5_phy_change_endian_sign.hex
mv otp.hex ${b_path}/dwc_pcie5_phy_change_endian_with_footer.hex
rm ${b_path}/dwc_pcie5_phy_change_endian.bin.tmp
