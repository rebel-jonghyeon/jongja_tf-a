/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#include <stdint.h>
#include "zeros.h"


/* https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogDeBruijn
 */
unsigned int clz32(uint32_t v)
{
	static const uint8_t lut[32] = {
		0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
		8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
	};

	v |= v >> 1; /* round down to one less than a power of 2 */
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;

	return 31 - lut[(uint32_t)(v * 0x07c4acddu) >> 27];
}
