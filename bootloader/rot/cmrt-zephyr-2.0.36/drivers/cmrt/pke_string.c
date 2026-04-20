/*
 * Copyright (c) 2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "pke_string.h"

static void zerotail(void *dst, size_t bytes)
{
	if (((uintptr_t)dst & 3U) == 0u) {
		uint32_t *d = (uint32_t *)((char *)dst + ((bytes + 3u) & ~3U) - 4);
		d[0] = 0;
	}
}

void pke_memcpy(void *dst, const void *src, size_t bytes)
{
	zerotail(dst, bytes);
	(void)memcpy(dst, src, bytes);
}

#define well_aligned(p1, p2, bytes, align) \
	((((uintptr_t)(p1) | (uintptr_t)(p2) | (uintptr_t)(bytes)) & \
	  ((align) - 1u)) == 0u)

void pke_swapcpy_ex(void *dst, const void *src, size_t bytes, bool fill_zeros)
{
	if (fill_zeros) {
		zerotail(dst, bytes);
	}

	if (well_aligned(dst, src, bytes, 4u)) {
		uint32_t *d = (uint32_t *)dst;
		const uint32_t *s = (const uint32_t *)((const char *)src + bytes);
		while (bytes != 0u) {
			*(d++) = __builtin_bswap32(*(--s));
			bytes -= 4u;
		}
	} else if (well_aligned(dst, src, bytes, 2u)) {
		uint16_t *d = (uint16_t *)dst;
		const uint16_t *s = (const uint16_t *)((const char *)src + bytes);
		while (bytes != 0u) {
			*(d++) = __builtin_bswap16(*(--s));
			bytes -= 2u;
		}
	} else {
		char *d = dst;
		const char *s = src;

		s += bytes;
		while (bytes-- != 0u) {
			*(d++) = *(--s);
		}
	}
}
