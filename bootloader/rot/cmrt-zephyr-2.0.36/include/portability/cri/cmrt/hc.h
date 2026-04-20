/*
 * Copyright (c) 2017-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file hc.h
 *
 * @brief Public APIs for the HC driver.
 */

#ifndef CRI_HC_H
#define CRI_HC_H

/**
 * @brief HC Interface
 * @defgroup hc_interface HC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <stddef.h>
#include <hc_reg.h>
#include <cshc_reg.h>
#include <whc_reg.h>
#include <hc2_reg.h>
#include <cri/cmrt/kdc.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_hc_t;
#else
typedef struct cmrt_hc_context *cri_hc_t;
#endif


/*!
 * Hash algorithm identifier.
 */
typedef enum cri_hash_algo_e {
	CRI_HASH_SHA224 = HC_HASH_ALGO_SHA_224,
	CRI_HASH_SHA256 = HC_HASH_ALGO_SHA_256,
	CRI_HASH_SHA384 = HC_HASH_ALGO_SHA_384,
	CRI_HASH_SHA512 = HC_HASH_ALGO_SHA_512,
	CRI_HASH_SHA512_224 = HC_HASH_ALGO_SHA_512_224,
	CRI_HASH_SHA512_256 = HC_HASH_ALGO_SHA_512_256,
	CRI_HASH_SHA3_224 = HC_HASH_ALGO_SHA3_224,
	CRI_HASH_SHA3_256 = HC_HASH_ALGO_SHA3_256,
	CRI_HASH_SHA3_384 = HC_HASH_ALGO_SHA3_384,
	CRI_HASH_SHA3_512 = HC_HASH_ALGO_SHA3_512,
	CRI_HASH_SHAKE128 = HC_HASH_ALGO_SHAKE128,
	CRI_HASH_SHAKE256 = HC_HASH_ALGO_SHAKE256,

	CRI_HASH_WHIRLPOOL = HC_HASH_ALGO_SHA_224
} cri_hash_algo_t;

/**
 * @brief Open HC context for subsequent operations.
 *
 * Open and reserve a HC context and may block for a context to be available.
 *
 * @param name Hash core name, for example CONFIG_CRI_WHC_NAME.
 * @param flags CRI_O_HWC_KEYED if HC gets key from KDC.
 * @return Context handle on success or NULL on error.
 */
cri_hc_t cri_hc_open(uint32_t flags);
cri_hc_t cri_cshc_open(uint32_t flags);
cri_hc_t cri_whc_open(uint32_t flags);
cri_hc_t cri_hc2_open(uint32_t flags);
cri_hc_t cri_hc_open_by_name(const char *name, uint32_t flags);

/**
 * @brief Close HC context.
 *
 * Close and free a previously opened HC context.
 *
 * @param context Pointer to the device.
 */
void cri_hc_close(cri_hc_t context);

/**
 * @brief Initialize KDC command for HC
 *
 * Use only if HC was opened with CRI_O_HWC_KEYED.
 * Sets fields command0, command1, dest and key_size in kdc_cmd_t.
 *
 * @param context Pointer to the device.
 * @param algo Hash algorithm.
 * @param keylen Length of the HMAC key.
 * @param keylen Length of the HMAC key.
 * @return Zero on success, -ERRNO on error.
 */
int cri_hc_kdc_cmd(cri_hc_t context, cri_hash_algo_t algo, size_t keylen, kdc_cmd_t *cmd);

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
int cri_hc_init(cri_hc_t context, cri_hash_algo_t algo, const void *key, size_t keylen);

/**
 * @brief Update hash value.
 *
 * @param context Pointer to the device.
 * @param input Pointer to data to be hashed. This must be 4-byte aligned.
 * @param inlen Length of data to be hashed. This must be a multiple of 4.
 * @return Zero on success, -ERRNO on error.
 */
int cri_hc_update(cri_hc_t context, const void *input, size_t inlen);

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
int cri_hc_final(cri_hc_t context, const void *input, size_t inlen, void *output, size_t *outlen);

/**
 * @brief Flush the hash core.
 *
 * Issues a FLUSH command to hash core without releasing the context.
 *
 * Note that this does not change whether the core was opened in
 * CRI_O_HWC_KEYED mode: if that is the case then the key can still be
 * only set via KDC and the hardware core will not be locked after
 * this call either.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_hc_flush(cri_hc_t context);

#ifdef __cplusplus
}
#endif

#endif
 /** @}*/
