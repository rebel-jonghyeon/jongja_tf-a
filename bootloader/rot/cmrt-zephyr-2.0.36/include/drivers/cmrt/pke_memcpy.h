/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


/**
 * @file pke_memcpy.h
 *
 * @brief Public APIs for the memory copy procedures used by PKE driver.
 */

#ifndef CMRT_PKE_MEMCPY_H
#define CMRT_PKE_MEMCPY_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Size of random ordering array
 */
#define PKE_CP_ORDER_SIZE    0x20

/**
 * @brief Copy big number into PKE
 *
 * Copy a big number into PKE. Uses defines to control endianness and
 * security features. Note that the numbers inside the PKE are
 * required to be little-endian 32-bit big numbers.
 *
 * @param in Pointer to the input.
 * @param length Byte length of input.
 * @param out Pointer to the output.
 * @param slot If a random order is selected, a slot for pseudo random values.
 * @retval Zero on success, -ERRNO on error.
 */
int copy_to_pke(const uint8_t * in,
		const size_t length,
#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
		uint32_t * out,
		const int8_t slot);
#else
		uint32_t *out);
#endif

/**
 * @brief Copy big number into PKE
 *
 * Copy a big number from PKE. Uses defines to control endianness.
 * Note that the numbers inside the PKE are required to be
 * little-endian 32-bit big numbers.
 *
 * @param in Pointer to the input.
 * @param length Byte length of input.
 * @param out Pointer to the output.
 * @param slot If a random order is selected, a slot for pseudo random values.
 * @retval Zero on success, -ERRNO on error.
 */
int copy_from_pke(uint32_t * in,
		  const size_t length,
#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
		  uint8_t * out,
		  const int8_t slot);
#else
		  uint8_t *out);
#endif

#ifdef CONFIG_CMRT_PKE_CP_RANDOM_ORDER
#define PKE_CP_NO_RANDOM_ORDER -2
#define COPY_TO_PKE(a, b, c, d) copy_to_pke((a), (b), (c), (d))
#define COPY_FROM_PKE(a, b, c, d) copy_from_pke((a), (b), (c), (d))
#else
#define COPY_TO_PKE(a, b, c, d) copy_to_pke((a), (b), (c))
#define COPY_FROM_PKE(a, b, c, d) copy_from_pke((a), (b), (c))
#endif

#ifdef __cplusplus
}
#endif
#endif
