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
	0xe1a86297, 0x8fce476d, 0x93d18db7, 0xa7a34630, 0x932a36cd, 0xc302f41d
};
static const uint32_t ac[] = {
	0xe1a86294, 0x8fce476d, 0x93d18db7, 0xa7a34630, 0x932a36cd, 0xc302f41d
};
static const uint32_t bx[] = {
	0xf4618129, 0x2c446af6, 0xbbf43fa7, 0x282e1fe7, 0x82f63c30, 0x3ae9e58c
};
static const uint32_t by[] = {
	0x7ccc01c9, 0xb7e5b3de, 0x449d0084, 0x902ab5ca, 0x67c2223a, 0x097e2c56
};
static const uint32_t bc[] = {
	0x27897b79, 0xfb68542e, 0x3b35bec2, 0x68f9deb4, 0xec78681e, 0x13d56ffa
};
static const uint32_t ord[] = {
	0x9ac4acc1, 0x5be8f102, 0x9e9e916b, 0xa7a3462f, 0x932a36cd, 0xc302f41d
};

const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P192T1 = {
	.length = 6,
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
