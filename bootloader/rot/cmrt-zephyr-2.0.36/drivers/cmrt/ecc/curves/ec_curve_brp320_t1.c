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
	0xf1b32e27, 0xfcd412b1, 0x7893ec28, 0x4f92b9ec, 0xf6f40def, 0xf98fcfa6,
	0xd201e065, 0xe13c785e, 0x36bc4fb7, 0xd35e4720
};
static const uint32_t ac[] = {
	0xf1b32e24, 0xfcd412b1, 0x7893ec28, 0x4f92b9ec, 0xf6f40def, 0xf98fcfa6,
	0xd201e065, 0xe13c785e, 0x36bc4fb7, 0xd35e4720
};
static const uint32_t bx[] = {
	0xa21bed52, 0x3357f624, 0xcc136fff, 0x7ee07868, 0x6c4f09cb, 0x3408ab10,
	0x90010f81, 0x4d3e7d49, 0x01afc6fb, 0x925be9fb
};
static const uint32_t by[] = {
	0x5fb0d2c3, 0x1b9bc045, 0x9d1ee71b, 0x42a5a098, 0xa0b077ad, 0xee084e58,
	0x7abb30eb, 0x6671dbef, 0x27483ebf, 0x63ba3a7a
};
static const uint32_t bc[] = {
	0x22340353, 0xb5b4fef4, 0xb8a547ce, 0x80aaf77f, 0x7ed27c67, 0x64c19f2,
	0xdb782013, 0x60b3d147, 0x38eb1ed5, 0xa7f561e0
};
static const uint32_t ord[] = {
	0x44c59311, 0x8691555b, 0xee8658e9, 0x2d482ec7, 0xb68f12a3, 0xf98fcfa5,
	0xd201e065, 0xe13c785e, 0x36bc4fb7, 0xd35e4720
};

const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P320T1 = {
	.length = 10,
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
