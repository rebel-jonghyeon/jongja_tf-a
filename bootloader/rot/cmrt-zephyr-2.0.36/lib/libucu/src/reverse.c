/*
 * Copyright (c) 2017-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 *
 * Byte-string reversal routines.  The implementation assumes that
 * a word-wise copy is always faster than accessing the memory
 * byte-wise.  Lacking any special byte-reordering instructions,
 * copying and reversing words is not guaranteed to be faster, making
 * the word-wise tests and functions useless!
 */


#include <cmrt/ucu/endianness.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


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
static uint32_t swap32(uint32_t x)
{
	return ((((x) >> 24) & 0xffu) |
		(((x) >> 8) & 0xff00u) |
		(((x) & 0xff00u) << 8) |
		(((x) & 0xffu) << 24));
}


static void inplace_rev32(uint32_t *p, size_t n)
{
	unsigned int i = 0u, j = n - 1u;
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
	if ((((uintptr_t)pv | n) & 3u) == 0u) {
		inplace_rev32(pv, n / 4u);
	} else {
		char *p = pv;
		for (unsigned int i = 0, j = n - 1u; i < j; ++i, --j) {
			char c = p[i];
			p[i] = p[j];
			p[j] = c;
		}
	}
}


static void revcpy32(uint32_t *pa, const uint32_t *pb, size_t n)
{
	for (unsigned int i = 0u; n != 0u; ++i) {
		pa[i] = swap32(pb[--n]);
	}
}


static inline bool overlap(const void *pa, const void *pb, size_t n)
{
	if (pa < pb) {
		const void *p = pa;
		pa = pb;
		pb = p;
	}
	return (size_t)((const char *)pa - (const char *)pb) < n;
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
int cmrt_reverse(void *pvout, const void *pvin, size_t n)
{
	int res = 0;
	if (n == 0) {
		/* nothing to do */
	} else if ((pvout == NULL) || (pvin == NULL)) {
		res = -1;
	} else if (pvout == pvin) {
		inplace_reverse(pvout, n);
	} else if (overlap(pvout, pvin, n)) {
		memmove(pvout, pvin, n);
		inplace_reverse(pvout, n);
	} else if ((((uintptr_t)pvout | (uintptr_t)pvin | n) & 3u) == 0u) {
		revcpy32(pvout, pvin, n / 4u);
	} else {
		const char *pin = pvin;
		char *pout = pvout;
		while (n != 0u) {
			*pout++ = pin[--n];
		}
	}
	return res;
}
