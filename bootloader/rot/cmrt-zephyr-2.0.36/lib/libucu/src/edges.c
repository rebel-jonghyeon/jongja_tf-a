/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#include <cmrt/ucu/bitstat.h>
#include <stdint.h>
#include <stddef.h>


#if (USE_BUILTIN_CTZ > 0) && !defined(BUILTIN_CTZ)
#ifdef __GNUC__
/* Currently not constant time, nor very effective, unless support for
 * the instruction is present.
 */
#define BUILTIN_CTZ(X) __builtin_ctz(X)
#else
#error lacking definition for BUILTIN_CTZ()
#endif
#endif


int bits_edges_init(bits_edge_iter *it, const uint32_t *p, uint32_t n)
{
	int res = 0;
	if (it == NULL) {	/* no iterator given */
		res = -1;
	} else if (n > 0) {
		if (p != NULL) {
			uint32_t shifted = (p[0] & 1) | (p[0] << 1);
			*it = (bits_edge_iter){
				p, n, 0, shifted ^ p[0], 0xffffffffu
			};
		} else {	/* may not dereference null pointer */
			res = -1;
		}
	} else {		/* empty range never contains edges */
		*it = (bits_edge_iter){ NULL, 0, 0, 0, 0 };
	}
	return res;
}


/* Count trailing zeros.  A few alternate implementations are given.
 *
 * The builtin should be chosen if, and only if there is support for
 * the instruction.  The trivial shifting and tresting against 0 has a
 * runtime dependent on the data and should not be used unless space
 * is very contrived.
 *
 * For explanation on the default implementation, see
 * "Using de Bruijn Sequences to Index a 1 in a Computer Word",
 * Leiserson, Charles E. et al, MIT, 1998.
 * and (also contains a similar div/mod37 based implementation with
 * one less instruction (but a div):
 * https://graphics.stanford.edu/~seander/
 * bithacks.html#ZerosOnRightMultLookup
 */
static unsigned ctz(uint32_t x)
{
#if USE_BUILTIN_CTZ > 0
	return BUILTIN_CTZ(x);
#else
	static const uint8_t lut[32] = {
		0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
		31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
	};
	return lut[((x & -x) * 0x77cb531u) >> 27];
#endif
}


static void advance(bits_edge_iter *it)
{
	uint32_t i = it->i;
	const uint32_t *p = it->p;
	uint32_t last = p[i / 32];
	i += 32;
	uint32_t x = p[i / 32];
	uint32_t shifted = (last >> 31) | (x << 1);
	it->edges = x ^ shifted;
	if (i + 32 > it->n) {
		it->mask = (1u << (it->n - i)) - 1;
	} else {
		it->mask = 0xffffffffu;
	}
	it->i = i;
}


int bits_edges_next(bits_edge_iter *it)
{
	while (it->i < it->n) {
		uint32_t masked = it->edges & it->mask;
		if (masked != 0) {
			unsigned index = ctz(masked); /* next return value */
			it->mask &= ~(1u << index);   /* masked out */
			return it->i + index; /* next match */
		}
		advance(it);
	}
	return 0;
}


static inline uint32_t min(uint32_t a, uint32_t b) { return (a < b) ? a : b; }


int bits_runlens(bits_edge_iter *it, uint32_t *bins, size_t nbins)
{
	unsigned i, last = 0, count = 0, nbits = it->n;
	while ((i = bits_edges_next(it)) > 0) {
		bins[min(i - last, nbins) - 1] += 1;
		++count;
		last = i;
	}
	if (last < nbits) {
		bins[min(nbits - last, nbins) - 1] += 1;
		++count;
	}
	return count;
}
