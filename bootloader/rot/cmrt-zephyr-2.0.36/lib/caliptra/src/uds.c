/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */

#include <errno.h>
#include <drivers/cmrt/util.h>
#include <cmrt/caliptra/types.h>
#include <cmrt/caliptra/flow.h>
#include <cmrt/ucu/span.h>
#include "internal.h"

int cmrt_caliptra_derive_uds_hash(const cmrt_caliptra_uds_t *uds_seed,
				  cmrt_caliptra_digest_t *uds_hash)
{
	/* SHA2-384(“UDS Derivation Constant”)[0:15] */
	alignas(4) static const uint8_t path[] = {
		0x9b, 0x27, 0x3d, 0x41, 0xf0, 0xba, 0x28, 0xf7,
		0xc7, 0x25, 0xcc, 0x4e, 0x41, 0x18, 0x10, 0x89,
	};
	/*  SHA2-384(“UDS AES-CBC IV”)[0:15] */
	alignas(4) static const uint8_t iv[] = {
		0x55, 0xde, 0x45, 0xfb, 0x2a, 0x7e, 0xa1, 0x06,
		0x23, 0x30, 0x10, 0x6f, 0x74, 0xb2, 0xf2, 0x1d,
	};
	/* UDS := Deobfuscate(UDS_Seed) */
	cmrt_caliptra_digest_t uds;
	int res = deobfuscate(SPAN(*uds_seed), SPAN(iv), SPAN(path), SPAN(uds));

	/* Clear UDS seed from memory. Doing it now allows uds_seed
	 * and uds_hash to be the same buffer.
	 */
	zeroize(SPAN(*uds_seed));
	if (res == 0) {
		/* UDS_Hash :=  SHA384(UDS) */
		res = sha384(SPAN(uds), SPAN(*uds_hash));
	}
	/* Clear UDS. */
	zeroize(SPAN(uds));
	return res;
}
