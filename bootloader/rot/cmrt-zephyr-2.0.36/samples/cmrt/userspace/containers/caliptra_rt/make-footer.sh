#!/bin/sh

# Copyright (c) 2023 Cryptography Research, Inc. (CRI).
# A license or authorization from CRI is needed to use this file

set -eu

caliptra_uds_len=$((384/8))

# Note: the -4 in end0/1 is there because addresses are inclusive.
if test "$CONFIG_CMRT_OMC_ESW_RSVD_FIRST" = y
then
	reserved_area_size=$((CONFIG_CMRT_OMC_ESW_RSVD_WORDS * 4))
	# Allow access to reserved words.
	start0=0
	end0=$((reserved_area_size - 4))
	perms0="rw"
	# Allow access from field entropy to end of OTP.
	start1=$((reserved_area_size + SBOOT_IMG_LEN + caliptra_uds_len))
	end1=$((OTP_SIZE - OTP_ESW + reserved_area_size - 4))
	perms1="rw"
else
	# Allow access from field entropy to end of OTP, including reserved words.
	start0=$((SBOOT_IMG_LEN + caliptra_uds_len))
	end0=$((OTP_SIZE - OTP_ESW - 4))
	perms0="rw"
	start1=0
	end1=0
	perms1=""
fi

cat <<EOD
{
    "container_format_version": 1,
    "entity": {
	"caveats": [ 1 ],
	"SCID": "c0ffbeef"
    },
    "container_version": 1,
    "permissions": {
	"write_otp_slots": [ 0 ],
	"write_otp_keys": [ ],
	"establish_roots": [ ],
	"obliterate_roots": [ ],
	"use_special_keys": [ ],
	"use_otp_keys": [ 1 ],
	"use_keydests": [ ],
	"write_feature_block": [ ],
	"access_otp": [
	    { "lo": ${start0}, "hi": ${end0}, "perms": "${perms0}"},
	    { "lo": ${start1}, "hi": ${end1}, "perms": "${perms1}"}
	],
	"software_permissions": [26, 31 ]
    }
}
EOD
