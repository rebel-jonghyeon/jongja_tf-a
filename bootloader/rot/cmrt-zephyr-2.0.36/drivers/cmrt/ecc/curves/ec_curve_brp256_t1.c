/*
 * Copyright 2013-2022 Cryptography Research, Inc. All rights reserved.
 *
 * Unauthorized use (including, without limitation, distribution and copying)
 * is strictly prohibited. All use requires, and is subject to, explicit
 * written authorization and nondisclosure agreements with Cryptography
 * Research.
 */

#include <stdint.h>
#include <stdlib.h>

#ifndef CRI_PKE_STANDALONE
#include <drivers/cmrt/crypto/pke_dpasl.h>
#else
#include "pke_dpasl.h"
#endif

static const uint32_t pf[] = {
	0x1f6e5377, 0x2013481d, 0xd5262028, 0x6e3bf623, 0x9d838d72, 0x3e660a90,
	0xa1eea9bc, 0xa9fb57db
};
static const uint32_t ac[] = {
	0x1f6e5374, 0x2013481d, 0xd5262028, 0x6e3bf623, 0x9d838d72, 0x3e660a90,
	0xa1eea9bc, 0xa9fb57db
};
static const uint32_t bx[] = {
	0x2e1305f4, 0x79a19156, 0x7aafbc2b, 0xafa142c4, 0x3a656149, 0x732213b2,
	0xc1cfe7b7, 0xa3e8eb3c
};
static const uint32_t by[] = {
	0x5b25c9be, 0x1dabe8f3, 0x39d02700, 0x69bcb6de, 0x4644417e, 0x7f7b22e1,
	0x3439c56d, 0x2d996c82
};
static const uint32_t bc[] = {
	0xfee92b04, 0x6ae58101, 0xaf2f4925, 0xbf93ebc4, 0x3d0b76b7, 0xfe66a773,
	0x30d84ea4, 0x662c61c4
};
static const uint32_t ord[] = {
	0x974856a7, 0x901e0e82, 0xb561a6f7, 0x8c397aa3, 0x9d838d71, 0x3e660a90,
	0xa1eea9bc, 0xa9fb57db
};

const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P256T1 = {
	.length = 8,
	.curve_is_Montgomery = FALSE,
	.curve_is_Edwards = FALSE,
	.spec_mod = SPEC_MOD_DISABLED,
	.ROM_mod = SPEC_MOD_NOT_ROM,
	.curve = NOT_ROM,
	.prime_field = pf,
	.a = ac,
	.b = bc,
	.base_x = bx,
	.base_y = by,
	.order = ord,
	.misc = NULL,
	.blinding = (dpa_blinding)cmrt_pke_ec_blind_private_key
};
