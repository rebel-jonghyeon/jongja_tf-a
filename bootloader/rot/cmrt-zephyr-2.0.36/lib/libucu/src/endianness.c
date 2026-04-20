/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stddef.h>
#include <sys/byteorder.h>
#include <cmrt/ucu/endianness.h>


uint32_t *cmrt_endian_swap(uint32_t *s, uint32_t words)
{
	if ((words == 0u) || ((words % 2u) != 0u)) {
		/* Must have even number of words to swap. */
		return NULL;
	}
	for (int i = 0, j = words - 1; i < j; i++, j--) {
		uint32_t tmp = s[i];
		s[i] = __bswap_32(s[j]);
		s[j] = __bswap_32(tmp);
	}
	return s;
}
