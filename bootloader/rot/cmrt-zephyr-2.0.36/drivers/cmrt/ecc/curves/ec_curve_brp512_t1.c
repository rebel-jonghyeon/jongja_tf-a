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
	0x583a48f3, 0x28aa6056, 0x2d82c685, 0x2881ff2f, 0xe6a380e6, 0xaecda12a,
	0x9bc66842, 0x7d4d9b00, 0x70330871, 0xd6639cca, 0xb3c9d20e, 0xcb308db3,
	0x33c9fc07, 0x3fd4e6ae, 0xdbe9c48b, 0xaadd9db8
};
static const uint32_t ac[] = {
	0x583a48f0, 0x28aa6056, 0x2d82c685, 0x2881ff2f, 0xe6a380e6, 0xaecda12a,
	0x9bc66842, 0x7d4d9b00, 0x70330871, 0xd6639cca, 0xb3c9d20e, 0xcb308db3,
	0x33c9fc07, 0x3fd4e6ae, 0xdbe9c48b, 0xaadd9db8
};
static const uint32_t bx[] = {
	0xfa9035da, 0x1baa2696, 0xe26f06b5, 0xf7a3f25f, 0xd6943a64, 0x99aa77a7,
	0x5cdb3ea4, 0x82ba5173, 0x39c0313d, 0x9db1758d, 0x58c56dde, 0xba858424,
	0xcbc2a6fe, 0xb9c1ba06, 0x12788717, 0x640ece5c
};
static const uint32_t by[] = {
	0x00f8b332, 0xe198b61e, 0x6dbb8bac, 0x306ecff9, 0xdf86a627, 0xd71df2da,
	0xbeef216b, 0xd9932184, 0xae03cee9, 0x1131159c, 0xb71634c0, 0xbb4e3019,
	0x6c84ace1, 0xa2c89237, 0x95f5af0f, 0x5b534bd5
};
static const uint32_t bc[] = {
	0x1867423e, 0x180ea257, 0x65763689, 0xc22553b4, 0xf2dae145, 0xf6450085,
	0x04976540, 0x2bcdfa23, 0xec3e36a6, 0x7897504b, 0xcb498152, 0x21f70c0b,
	0x6884eae3, 0x6e1890e4, 0x441cfab7, 0x7cbbbcf9
};
static const uint32_t ord[] = {
	0x9ca90069, 0xb5879682, 0x085ddadd, 0x1db1d381, 0x7fac1047, 0x41866119,
	0x4ca92619, 0x553e5c41, 0x70330870, 0xd6639cca, 0xb3c9d20e, 0xcb308db3,
	0x33c9fc07, 0x3fd4e6ae, 0xdbe9c48b, 0xaadd9db8
};

const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P512T1 = {
	.length = 16,
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
