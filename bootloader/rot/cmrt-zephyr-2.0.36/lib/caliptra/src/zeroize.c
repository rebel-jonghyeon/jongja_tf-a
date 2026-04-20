/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#include <cmrt/caliptra/flow.h>
#include "internal.h"

/* A bzero() that hopefully won't be optimized out. */
void zeroize(span buf)
{
	volatile unsigned char *p = (volatile unsigned char *)buf.p;
	size_t n = buf.n;
	while (n > 0u) {
		*p = (unsigned char)0U;
		--n;
		++p;
	}
}

void cmrt_caliptra_zeroize(void *p, size_t n)
{
	zeroize(span_from(p, n));
}

bool allzero(const span buf)
{
	/* Use word accesses if input is aligned, so it works for OTP
	 * too.
	 */
	size_t i = 0;
	if (IS_ALIGNED(buf.p, 4u)) {
		const uint32_t *wp = (const uint32_t *)buf.p;
		for (; i < buf.n / 4u; ++i) {
			if (wp[i] != 0u) {
				return false;
			}
		}
		i *= 4u; /* Convert to byte offset. */
	}
	/* Check the rest as bytes. */
	for (; i < buf.n; ++i) {
		if (buf.p[i] != 0u) {
			return false;
		}
	}
	return true;
}
