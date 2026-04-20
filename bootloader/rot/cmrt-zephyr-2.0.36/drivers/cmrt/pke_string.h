/*
 * Copyright (c) 2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file pke_string.h
 *
 * @brief Private API for PKE.
 */

#ifndef CRI_PKE_STRING_H
#define CRI_PKE_STRING_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief memcpy with zeroing tail
 * memcpy src to dst. zeroing tails up to 4-bytes.
 *
 * @param dst destination pointer
 * @param src source pointer
 * @param bytes size of @src
 */
void pke_memcpy(void *dst, const void *src, size_t bytes);

/**
 * @brief memcpy with swap endian and zeroing tail
 * swap endian of src to dst. zeroing tails up to 4-bytes.
 *
 * @param dst destination pointer
 * @param src source pointer
 * @param bytes size of @src
 * @param fill_zeros True if fill tail with zeros.
 */
void pke_swapcpy_ex(void *dst, const void *src, size_t bytes, bool fill_zeros);

static inline void pke_swapcpy(void *dst, const void *src, size_t bytes)
{
	pke_swapcpy_ex(dst, src, bytes, true);
}

#endif
