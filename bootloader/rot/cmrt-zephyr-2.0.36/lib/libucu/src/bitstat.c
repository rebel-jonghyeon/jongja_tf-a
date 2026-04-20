/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#include <cmrt/ucu/bitstat.h>
#include <stdint.h>
#include <stddef.h>


#if (USE_BUILTIN_POPCOUNT > 0) && !defined(BUILTIN_POPCOUNT)
#ifdef __GNUC__
/* Currently not constant time, nor very effective, unless support for
 * the instruction is present.
 */
#define BUILTIN_POPCOUNT(X) __builtin_popcount(X)
#else
#error lacking definition of BUILTIN_POPCOUNT()
#endif
#endif


/* Generally an instruction or intrinsic.  With he RISC-V
 * bit-manipulation extension the instruction is cpop.  A
 * constant-time implementation is supplied if not.
 */
static inline unsigned popcount(unsigned x)
{
#if USE_BUILTIN_POPCOUNT > 0
	return BUILTIN_POPCOUNT(x);
#else
	x -= ((x >> 1) & 0x55555555u);
	x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
	x = (x + (x >> 4)) & 0x0F0F0F0Fu;
	x += (x >> 8);
	x += (x >> 16);
	return x & 0x0000003Fu;
#endif
}


uint32_t bitstat_ones32(const uint32_t *p, uint32_t n)
{
	uint32_t total = 0;
	for (unsigned i = 0; i < n; i += 32) {
		total += popcount(*p++);
	}
	return total;
}


/* Population count of a set of /bits/. The input must be fully aligned.
 * The last word of data must be adjusted into the smallest bits (i.e.,
 * a little-endian format is expected).
 */
uint32_t bitstat_ones(const uint32_t *p, uint32_t n)
{
	uint32_t total = 0;
	uint32_t mask = -1;
	for (unsigned i = 0; i < n; i += 32) {
		if (i + 32 > n) {
			mask = (1u << (n - i)) - 1;
		}
		total += popcount(*p++ & mask);
	}
	return total;
}


/* Count changes within a bitstring.  Some rules;
 * - initial value is not a change
 * - last value is not counted either
 * Some notes:
 * - expects (x >> 31) to be a sign bit comparison, if that is faster
 */
static uint32_t edgecount(const uint32_t *p, size_t n)
{
	uint32_t total = 0;
	uint32_t last = -(p[0] & 1); /* copy lowest bit */
	uint32_t mask = -1;
	for (unsigned i = 0; i < n; i += 32) {
		uint32_t x = *p++;
		uint32_t shifted = (last >> 31) | (x << 1);
		uint32_t changes = x ^ shifted;
		if (i + 32 > n) {
			mask = (1u << (n - i)) - 1;
		}
		total += popcount(changes & mask);
		last = x;
	}

	return total;
}


uint32_t bitstat_runs(const uint32_t *p, uint32_t n)
{
	uint32_t res = 0;
	if (n > 0) {
		res = 1 + edgecount(p, n);
	}
	return res;
}


uint32_t bitstat_matches32(const uint32_t *x, const uint32_t *y, uint32_t n)
{
	uint32_t total = 0;
	for (unsigned i = 0; i < n; i += 32) {
		total += popcount(*x++ ^ *y++);
	}
	return n - total;
}


uint32_t bitstat_matches(const uint32_t *x, const uint32_t *y, uint32_t n)
{
	uint32_t total = 0;
	uint32_t mask = -1;
	for (unsigned i = 0; i < n; i += 32) {
		if (i + 32 > n) {
			mask = (1u << (n - i)) - 1;
		}
		total += popcount((*x++ ^ *y++) & mask);
	}
	return n - total;
}


uint32_t bitstat_shifted_matches(const uint32_t *x,
				 const uint32_t *y, uint32_t n,
				 uint32_t shift)
{
	y += shift / 32;
	shift %= 32;
	if (shift == 0) {
		return bitstat_matches(x, y, n);
	}
	uint32_t total = 0;
	uint32_t mask = -1;
	for (unsigned i = 0; i < n; i += 32) {
		if (i + 32 > n) {
			mask = (1u << (n - i)) - 1;
		}
		uint32_t other = (y[0] >> shift) | (y[1] << (32 - shift));
		total += popcount((*x++ ^ other) & mask);
		++y;
	}
	return n - total;
}
