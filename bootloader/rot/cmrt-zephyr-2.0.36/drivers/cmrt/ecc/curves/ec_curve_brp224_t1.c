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
	0x7ec8c0ff, 0x97da89f5, 0xb09f0757, 0x75d1d787, 0x2a183025, 0x26436686,
	0xd7c134aa
};
static const uint32_t ac[] = {
	0x7ec8c0fc, 0x97da89f5, 0xb09f0757, 0x75d1d787, 0x2a183025, 0x26436686,
	0xd7c134aa
};
static const uint32_t bx[] = {
	0x29b4d580, 0x8ac0c760, 0xcb49f892, 0xfe14762e, 0x96424e7f, 0xce25ff38,
	0x6ab1e344
};
static const uint32_t by[] = {
	0x1a46db4c, 0x1c6abd5f, 0x41c8cc0d, 0x7c0d4b1e, 0xd23f3f4d, 0x143e568c,
	0x374e9f5
};
static const uint32_t bc[] = {
	0x8a60888d, 0xb3bb64f1, 0x0da14c08, 0x0ced1ed2, 0xef271bf6, 0x4104cd7b,
	0x4b337d93
};
static const uint32_t ord[] = {
	0xa5a7939f, 0x6ddebca3, 0xd116bc4b, 0x75d0fb98, 0x2a183025, 0x26436686,
	0xd7c134aa
};

const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P224T1 = {
	.length = 7,
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
