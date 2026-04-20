/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file hc.h
 *
 * @brief Public APIs for the HC driver.
 */

#ifndef CMRT_HC_H
#define CMRT_HC_H

/**
 * @brief HC Interface
 * @defgroup hc_interface HC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <stddef.h>
#include <device.h>
#include <drivers/cmrt/hc_reg.h>
#include <drivers/cmrt/cshc_reg.h>
#include <drivers/cmrt/whc_reg.h>
#include <drivers/cmrt/hc2_reg.h>
#include <drivers/cmrt/kdc.h>

#ifdef __ZEPHYR__
#define CMRT_HC_HAS_SHAKE128 DT_PROP(DT_ALIAS(s3hc), has_shake128)
#define CMRT_HC_HAS_SHAKE256 DT_PROP(DT_ALIAS(s3hc), has_shake256)
#define CMRT_HC_SHAKE_HW_PADDING DT_PROP(DT_ALIAS(s3hc), shake_hw_padding)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_hc_context *cmrt_hc_t;

/*!
 * Hash algorithm identifier.
 */
typedef enum cmrt_hash_algo_e {
	CMRT_HASH_SHA224 = HC_HASH_ALGO_SHA_224,
	CMRT_HASH_SHA256 = HC_HASH_ALGO_SHA_256,
	CMRT_HASH_SHA384 = HC_HASH_ALGO_SHA_384,
	CMRT_HASH_SHA512 = HC_HASH_ALGO_SHA_512,
	CMRT_HASH_SHA512_224 = HC_HASH_ALGO_SHA_512_224,
	CMRT_HASH_SHA512_256 = HC_HASH_ALGO_SHA_512_256,
	CMRT_HASH_SHA3_224 = HC_HASH_ALGO_SHA3_224,
	CMRT_HASH_SHA3_256 = HC_HASH_ALGO_SHA3_256,
	CMRT_HASH_SHA3_384 = HC_HASH_ALGO_SHA3_384,
	CMRT_HASH_SHA3_512 = HC_HASH_ALGO_SHA3_512,
	CMRT_HASH_SHAKE128 = HC_HASH_ALGO_SHAKE128,
	CMRT_HASH_SHAKE256 = HC_HASH_ALGO_SHAKE256,
	CMRT_HASH_WHIRLPOOL = HC_HASH_ALGO_SHA_224
} cmrt_hash_algo_t;

/**
 * @brief Get hash size based on algo type.
 *
 * @param halgo cmrt_hash_algo_t hash algo type.
 * @param whirlpool For whirlpool hash core.
 * @param bsize Buffer size, used only for shake.
 * @return Hash size in bytes, 0 on unsupported algo.
 */
size_t cmrt_hc_hash_size(cmrt_hash_algo_t halgo, bool whirlpool, size_t bsize);

/**
 * @brief Open HC context for subsequent operations.
 *
 * Open and reserve a HC context and may block for a context to be available.
 *
 * @param name Hash core name, "s2hc", "cshc", "whc" or "s3hc" for
 *        SHA2 HC, Compact HC, Whirlpool HC, or SHA3 HC, respectively.
 *        NULL opens the first hash core regardless of its type.
 * @param flags CMRT_O_HWC_KEYED if HC gets key from KDC.
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_hc_t cmrt_hc_open(const char *name, uint32_t flags);

/**
 * @brief Open HC context for subsequent operations.
 *
 * Compatibility opens for each of the hash core instances. Only available
 * for CONFIG_CMRT_CSHC, CONFIG_CMRT_WHC, and CONFIG_CMRT_HC2, respectively.
 *
 * @param flags CMRT_O_HWC_KEYED if HC gets key from KDC.
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_hc_t cmrt_cshc_open(uint32_t flags);
__syscall cmrt_hc_t cmrt_whc_open(uint32_t flags);
__syscall cmrt_hc_t cmrt_hc2_open(uint32_t flags);

/**
 * @brief Close HC context.
 *
 * Close and free a previously opened HC context.
 *
 * @param context Pointer to the device.
 */
__syscall void cmrt_hc_close(cmrt_hc_t context);

/**
 * @brief Initialize KDC command for HC
 *
 * Use only if HC was opened with CMRT_O_HWC_KEYED.
 * Sets fields command0, command1, dest and key_size in cmrt_kdc_cmd_t.
 *
 * @param context Pointer to the device.
 * @param algo Hash algorithm.
 * @param keylen Length of the HMAC key.
 * @param[out] cmd KDC commnand structure filled in by function.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_hc_kdc_cmd(cmrt_hc_t context, cmrt_hash_algo_t algo, size_t keylen, cmrt_kdc_cmd_t *cmd);

/**
 * @brief Initialize hash context.
 *
 * @param context Pointer to the device.
 * @param algo Hash algorithm.
 * @param key Pointer to HMAC key or NULL if key comes via KDC.
 *        This must be 4-byte aligned.
 * @param keylen Length of HMAC key or zero if key comes via KDC.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_hc_init(cmrt_hc_t context, cmrt_hash_algo_t algo, const void *key, size_t keylen);

/**
 * @brief Update hash value.
 *
 * @param context Pointer to the device.
 * @param input Pointer to data to be hashed. This must be 4-byte aligned.
 * @param inlen Length of data to be hashed. This must be a multiple of 4.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_hc_update(cmrt_hc_t context, const void *input, size_t inlen);

/**
 * @brief Final hash value
 *
 * This function can be called many times until all output is consumed.
 * This applies to XOF functions like SHAKE128 and SHAKE256, in particular.
 * In that case, only the first call may have input data.
 *
 * @param context Pointer to the device.
 * @param input Pointer to data to be hashed. This must be 4-byte aligned.
 * @param inlen Length of data to be hashed. 0 is a valid value here.
 * @param output Pointer to hash. This must be 4-byte aligned.
 * @param outlen in: hash buffer length, out: length of hash
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_hc_final(cmrt_hc_t context, const void *input, size_t inlen, void *output, size_t *outlen);

#ifdef __cplusplus
}
#endif

#include <syscalls/hc.h>

#endif
/** @}*/
