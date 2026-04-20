/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file ccp.h
 *
 * @brief Public APIs for the CCP driver.
 */

#ifndef CRI_CCP_H
#define CRI_CCP_H

/**
 * @brief ChaChaPoly (CCP) Interface
 * @defgroup ccp_interface CCP Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <stddef.h>
#include <ccp_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_ccp_t;
#else
typedef struct cmrt_ccp_context *cri_ccp_t;
#endif

/**
 * @brief Open ChaChaPoly context for subsequent operations.
 *
 * Open and reserve an CCP context. May block for a context to be available.
 *
 * @return Context handle on success or NULL on error.
 */
cri_ccp_t cri_ccp_open(uint32_t flags);

/**
 * @brief Close ChaChaPoly context, reverse of open.
 *
 * Close and free a previously opened CCP context.
 *
 * @param dev Pointer to the device.
 */
void cri_ccp_close(cri_ccp_t dev);

/**
 * @brief Initialize ChaChaPoly context.
 *
 * @param dev Pointer to the device.
 * @param operation Cipher operation, CIPHER_OP_ENCRYPT or CIPHER_OP_DECRYPT.
 * @param mode Cipher algorithm, one of ccp_mode_op.
 * @param key Pointer to chacha key. Must be 32-bit aligned.
 * @param keylen Length of chacha key in bytes
 * @param iv Pointer to iv. Must be 32-bit aligned.
 * @param ivlen Length of iv in bytes, must be CCP_IV_LEN if used.
 * @param taglen Length of tag in bytes, must be POLY_TAG_LENGTH_BYTES if used.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ccp_init(cri_ccp_t dev, int operation, int mode, const void *key,
		 size_t keylen, const void *iv, size_t ivlen, size_t taglen);

/**
 * @brief Update ChaChaPoly operation.
 *
 * @param dev Pointer to the device.
 * @param input Pointer to input PT/CT data. This must be 4-byte aligned.
 * @param inlen Length of input PT/CT data. This must be a multiple of 16.
 * @param output Pointer to output data. This must be 4-byte aligned.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ccp_update(cri_ccp_t dev, const void *input,
		   size_t inlen, void *output);

/**
 * @brief Update aad data for authenticated ChaChaPoly operation.
 *
 * @param dev Pointer to the device.
 * @param aad Pointer to input AA data. This must be 4-byte aligned.
 * @param aadlen Length of input AA data. This must be a multiple of 4.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ccp_update_aad(cri_ccp_t dev, const void *aad, size_t aadlen);

/**
 * @brief Final aad data for authenticated ChaChaPoly operation.
 *
 * @param dev Pointer to the device.
 * @param aad Pointer to input AA data. This must be 4-byte aligned.
 * @param aadlen Length of input AA data. This must be a multiple of 4.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ccp_final_aad(cri_ccp_t dev, const void *aad, size_t aadlen);

/**
 * @brief Finalize ChaChaPoly operation.
 *
 * @param dev Pointer to the device.
 * @param input Pointer to input PT/CT data. This must be 4-byte aligned.
 * @param inlen Length of input PT/CT data. The length has no restrictions but
 *                 the datain and dataout buffer sizes must be multiples of 4.
 * @param output Pointer to output data. This must be 4-byte aligned.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ccp_final(cri_ccp_t dev, const void *input,
		  unsigned int inlen, void *output);

/**
 * @brief Finalize authenticated ChaChaPoly operation.
 *
 * @param dev Pointer to the device.
 * @param input Pointer to input PT/CT data. This must be 4-byte aligned.
 * @param inlen Length of input PT/CT data. The length has no restrictions but
 *        the datain and dataout buffer sizes must be multiples of 4.
 * @param output Pointer to output data. This must be 4-byte aligned.
 * @param tag Pointer to tag This must be 4-byte aligned.
 * @param taglen Length of tag buffer. This must be a multiple of 4.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ccp_ae_final(cri_ccp_t dev, const void *input,
		     size_t inlen, void *output, void *tag, size_t *taglen);

/**
 * @brief Invalidate key for ChaChaPoly operation.
 *
 * @param dev Pointer to the device.
 * @param flags Flags for special options, default 0.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ccp_invalidate_key(cri_ccp_t dev, uint32_t flags);

#ifdef __cplusplus
}
#endif

#endif
 /** @}*/
