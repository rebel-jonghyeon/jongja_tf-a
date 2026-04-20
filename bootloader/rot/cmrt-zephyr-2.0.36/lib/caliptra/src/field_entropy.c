/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdalign.h>
#include <cmrt/caliptra/flow.h>
#include "internal.h"

/* Deobfuscate field_entropy in-place. */
int cmrt_caliptra_deobfuscate_field_entropy(cmrt_caliptra_field_entropy_t *field_entropy, int slot_index)
{
	/* SHA2-384(“Field Entropy Derivation Constant”)[0:15] */
	alignas(4) static const uint8_t path[] = {
		0xea, 0xb0, 0x56, 0xfc, 0x5d, 0xed, 0xed, 0x8a,
		0x2f, 0x3c, 0x7c, 0x6f, 0x70, 0x95, 0x15, 0x74,
	};
	/* SHA2-384(“Field Entropy AES-CBC IV”)[0:15] */
	alignas(4) uint8_t iv[] = {
		0x82, 0x66, 0x86, 0xae, 0x2b, 0x8e, 0xf5, 0x85,
		0x9e, 0x35, 0x1a, 0x62, 0x60, 0x1f, 0x79, 0xa0,
	};
	/* Perturb the IV with index of the field entropy slot. */
	iv[0] ^= (uint8_t)slot_index;

	return deobfuscate(SPAN(*field_entropy), SPAN(iv), SPAN(path), SPAN(*field_entropy));
}
