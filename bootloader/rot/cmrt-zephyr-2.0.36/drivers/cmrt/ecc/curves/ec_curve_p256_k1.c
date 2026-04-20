/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#ifndef CRI_PKE_STANDALONE
#include <drivers/cmrt/crypto/pke_dpasl.h>
#else
#include "pke_dpasl.h"
#endif

const struct dpa_ecc_curve_struct CURVE_SECP256K1 = {
	.length = 8,
	.curve_is_Montgomery = FALSE,
	.curve_is_Edwards = FALSE,
	.spec_mod = SPEC_MOD_ENABLED,
	.ROM_mod = SPEC_MOD_IN_ROM,
	.curve = NIST_SECP256k1,
	.prime_field = NULL,
	.a = NULL,
	.b = NULL,
	.base_x = NULL,
	.base_y = NULL,
	.order = NULL,
	.misc = NULL,
	.blinding = (dpa_blinding)cmrt_pke_ec_blind_private_key
};
