#!/bin/bash

if [ ! $# -eq 2 ]; then
    echo "Usage : sign_image.sh $INPUT $OUTPUT"
    exit 1
fi

# Load environment variables
source ./source_directories.sh

in_image=$1
out_image=$2

# Check multiple of 4
python3 $REBELH_TOP/scripts/gen-image-multiple4.py $in_image

python3 $REBELH_TOP/scripts/gen-image-footer.py \
        $BOOTLOADER_CMRT_SAMPLE/common/prikey_ecdsa_p384.pem \
        ${in_image} \
        $REBELH_TOP/scripts/dummy_footer.json \
        ${in_image}.tmp

python3 $REBELH_TOP/scripts/gen-image-header.py \
        ${in_image}.tmp \
        ${out_image}

rm -f ${in_image}.tmp

