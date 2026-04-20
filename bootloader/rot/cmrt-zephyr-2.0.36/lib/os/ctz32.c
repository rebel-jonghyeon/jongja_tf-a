/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#include <stdint.h>
#include "zeros.h"


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
unsigned int ctz32(uint32_t x)
{
	static const uint8_t lut[32] = {
		0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
		31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
	};
	return lut[((x & -x) * 0x77cb531u) >> 27];
}
