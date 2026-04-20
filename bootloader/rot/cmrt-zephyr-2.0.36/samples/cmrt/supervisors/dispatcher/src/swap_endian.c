/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 *
 * Byte-string reversal routines.  The implementation assumes that
 * a word-wise copy is always faster than accessing the memory
 * byte-wise.  Lacking any special byte-reordering instructions,
 * copying and reversing words is not guaranteed to be faster, making
 * the word-wise tests and functions useless!
 */


#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "internals.h"


/*!
 * Swap byte order in 32-bit word.  __builtin_bswap32() does always
 * result in an external function call (loaded masks cannot be used
 * regardless of optimization level), the function is available on
 * gcc, but this is in no way guaranteed, nor is the presence
 * testable.
 *
 * @param x input word
 * @return byte-swapped x
 */
#if 0
#define swap32(uint32_t x) __builtin_bswap32(x)
#else
static uint32_t swap32(uint32_t x)
{
	x = (x << 16) ^ (x >> 16);
	x = ((x & 0x00ff00ff) << 8) ^ ((x >> 8) & 0x00ff00ff);
	return x;
}
#endif


static void inplace_rev32(uint32_t *p, size_t n)
{
	unsigned int i = 0, j = n - 1;
	for (; i < j; ++i, --j) {
		uint32_t c = swap32(p[i]);
		p[i] = swap32(p[j]);
		p[j] = c;
	}
	if (i == j) {
		p[i] = swap32(p[i]);
	}
}


static void inplace_reverse(void *pv, size_t n)
{
	if ((((uintptr_t)pv | n) & 3) == 0) {
		inplace_rev32(pv, n / 4);
	} else {
		char *p = pv;
		for (unsigned int i = 0, j = n - 1; i < j; ++i, --j) {
			char c = p[i];
			p[i] = p[j];
			p[j] = c;
		}
	}
}


static void revcpy32(uint32_t *pa, const uint32_t *pb, size_t n)
{
	for (unsigned int i = 0; n; ++i) {
		pa[i] = swap32(pb[--n]);
	}
}


static inline bool overlap(const void *pa, const void *pb, size_t n)
{
	return (size_t)((char *)pa - (char *)pb) < n;
}


/*!
 * Copy data reversing input.  The data in pin, pin+1, ..., pin+n-1
 * will be written out to pout+n-1, pout+n-2, ... pout.  We streamline
 * the case of being word-aligned: this case is expected with most
 * data arguments.
 *
 * Overlapping ranges are allowed (which will cause the input to be
 * garbled), including inplace-reversal (which is generally faster.)
 */
int cri_reverse(void *pvout, const void *pvin, size_t n)
{
	if (pvout == pvin) {
		inplace_reverse(pvout, n);
	} else if (overlap(pvout, pvin, n)) {
		memmove(pvout, pvin, n);
		inplace_reverse(pvout, n);
	} else if ((((uintptr_t)pvout | (uintptr_t)pvin | n) & 3) == 0) {
		revcpy32(pvout, pvin, n / 4);
	} else {
		const char *pin = pvin;
		char *pout = pvout;
		while (n) {
			*pout++ = pin[--n];
		}
	}
	return 0;
}
