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
	0x3107ec53, 0x87470013, 0x901d1a71, 0xacd3a729, 0x7fb71123, 0x12b1da19,
	0xed5456b4, 0x152f7109, 0x50e641df, 0x0f5d6f7e, 0xa3386d28, 0x8cb91e82
};
static const uint32_t ac[] = {
	0x3107ec50, 0x87470013, 0x901d1a71, 0xacd3a729, 0x7fb71123, 0x12b1da19,
	0xed5456b4, 0x152f7109, 0x50e641df, 0x0f5d6f7e, 0xa3386d28, 0x8cb91e82
};
static const uint32_t bx[] = {
	0x418808cc, 0xd8d0aa2f, 0x946a5f54, 0xc4ff191b, 0x462aabff, 0x2476fecd,
	0xebd65317, 0x9b80ab12, 0x35f72a81, 0xf2afcd72, 0x2db9a306, 0x18de98b0
};
static const uint32_t by[] = {
	0x9e582928, 0x2675bf5b, 0x4dc2b291, 0x46940858, 0xa208ccfe, 0x3b88f2b6,
	0x5b7a1fca, 0x747f9347, 0x755ad336, 0xa114afd2, 0x62d30651, 0x25ab0569
};
static const uint32_t bc[] = {
	0x33b471ee, 0xed70355a, 0x3b88805c, 0x2074aa26, 0x756dce1d, 0x4b1abd11,
	0x8ccdc64e, 0x4b9346ed, 0x47910f8c, 0xd826dba6, 0xa7bda81b, 0x7f519ead
};
static const uint32_t ord[] = {
	0xe9046565, 0x3b883202, 0x6b7fc310, 0xcf3ab6af, 0xac0425a7, 0x1f166e6c,
	0xed5456b3, 0x152f7109, 0x50e641df, 0x0f5d6f7e, 0xa3386d28, 0x8cb91e82
};

const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P384T1 = {
	.length = 12,
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
	.blinding = (dpa_blinding)cmrt_pke_ec_blind_private_key,
};
