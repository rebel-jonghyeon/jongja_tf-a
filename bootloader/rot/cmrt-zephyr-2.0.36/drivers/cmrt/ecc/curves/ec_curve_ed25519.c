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

const struct dpa_ecc_curve_struct EDWARDS_CURVE_ED25519 = {
	.length = 8,
	.curve_is_Montgomery = FALSE,
	.curve_is_Edwards = TRUE,
	.spec_mod = SPEC_MOD_ENABLED,
	.ROM_mod = SPEC_MOD_IN_ROM,
	.curve = CURVE_25519,
	.prime_field = NULL,
	.order = NULL,
	.a = NULL,
	.b = NULL,
	.base_x = NULL,
	.base_y = NULL,
	.misc = NULL,
	.blinding = (dpa_blinding)cmrt_pke_ec_blind_private_key
};
