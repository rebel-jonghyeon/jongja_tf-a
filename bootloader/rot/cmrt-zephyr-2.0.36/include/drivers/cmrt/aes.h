/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file aes.h
 *
 * @brief Public APIs for the AES driver.
 */

#ifndef CMRT_AES_H
#define CMRT_AES_H

/**
 * @brief AES Interface
 * @defgroup aes_interface AES Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <stddef.h>
#include <device.h>
#include <drivers/cmrt/aes_reg.h>
#include <drivers/cmrt/kdc.h>

#ifdef __ZEPHYR__
#define CMRT_AES_HAS_CMAC DT_PROP(DT_NODELABEL(aes), has_cmac)
#define CMRT_AES_HAS_XTS DT_PROP(DT_NODELABEL(aes), has_xts)
#define CMRT_AES_HAS_CCM DT_PROP(DT_NODELABEL(aes), has_ccm)
#define CMRT_AES_HAS_192 DT_PROP(DT_NODELABEL(aes), has_192)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_aes_context *cmrt_aes_t;

typedef enum cmrt_aes_operation_e {
	CMRT_AES_ENCRYPT = AES_ENCRYPT,
	CMRT_AES_DECRYPT = AES_DECRYPT
} cmrt_aes_operation_t;


/*!
 * AES operation mode.  The block cipher mode is selected with the parameter.
 */
typedef enum cmrt_aes_mode_e {
	CMRT_AES_ECB = AES_ECB, /**< codebook mode */
	CMRT_AES_CBC = AES_CBC, /**< cryptographic block  */
	CMRT_AES_CFB = AES_CFB, /**< feedback mode */
	CMRT_AES_CTR = AES_CTR, /**< counter mode */
	CMRT_AES_GCM = AES_GCM, /**< Galois/counter mode */
	CMRT_AES_CCM = AES_CCM,
	CMRT_AES_XTS = AES_XTS,
	CMRT_AES_CMAC = AES_CMAC /**< AES-CMAC mode */
} cmrt_aes_mode_t;

/**
 * @brief Open AES context for subsequent operations.
 *
 * Open and reserve an AES context. May block for a context to be available.
 *
 * @param flags CMRT_O_HWC_KEYED if AES gets key from KDC.
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_aes_t cmrt_aes_open(uint32_t flags);

/**
 * @brief Close AES context, reverse of open.
 *
 * Close and free a previously opened AES context.
 *
 * @param context Pointer to the device.
 */
__syscall void cmrt_aes_close(cmrt_aes_t context);

/**
 * @brief Initialize KDC command structure for AES.
 *
 * Use only if AES was opened with CMRT_O_HWC_KEYED.
 * Sets fields command0, command1, dest and key_size in cmrt_kdc_cmd_t.
 *
 * @param context Pointer to the device.
 * @param operation Cipher operation, AES_ENCRYPT or AES_DECRYPT
 * @param mode Cipher mode, AES_ECB, AES_CBC, etc.
 * @param keylen Length of AES key in bytes
 * @param taglen Length of tag in bytes.
 * @param[out] cmd KDC commnand structure filled in by function
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_aes_kdc_cmd(cmrt_aes_t context, cmrt_aes_operation_t operation, cmrt_aes_mode_t mode, size_t keylen, size_t taglen, cmrt_kdc_cmd_t *cmd);

/**
 * @brief Load a key into AES using KDC.
 *
 * This is a convenience function to derive keys with KDC, taking
 * mode-specific caveats into consideration.  In most modes, it just
 * calls cmrt_kdc_derive_key().
 *
 * In AES-XTS-256 mode this will use cmrt_kdc_derive_key() twice to
 * deliver 512 bits of key material to the AES core, taking the
 * following into account:
 *
 * - It makes sure that the KDC retains the lock on the AES core
 * between the two derivations.
 *
 * - Inverts the first byte of the diversify path in the first
 * derivation to ensure that the two subkeys are different (which is a
 * requirement of XTS mode).  NOTE: this is an arbitrary choice by
 * this function so that the caller doesn't have to specify two
 * distinct diversification paths!  If more control is needed, key
 * derivations should be performed manually.
 *
 * @param context AES context
 * @param kdc KDC context
 * @param cmd A KDC command structure (filled with diversify path and
 * by cmrt_aes_kdc_cmd())
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_aes_load_kdc_key(cmrt_aes_t context, cmrt_kdc_t kdc, cmrt_kdc_cmd_t *cmd);

/**
 * @brief Initialize AES context.
 *
 * Note: XTS mode uses two keys internally, and in that case the @p
 * key parameter should point to a buffer containing these two keys
 * concatenated as Key1 || Key2 (where Key1 is the encryption key and
 * Key2 is the tweak key).
 *
 * @param context Pointer to the device.
 * @param operation Cipher operation, AES_ENCRYPT or AES_DECRYPT
 * @param mode Cipher mode, AES_ECB, AES_CBC, etc.
 * @param key Pointer to AES key. Must be 32-bit aligned.
 * @param keylen Length of AES key in bytes
 * @param iv Pointer to iv. Must be 32-bit aligned.
 * @param ivlen Length of iv in bytes.
 * @param taglen Length of tag in bytes.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_aes_init(cmrt_aes_t context, cmrt_aes_operation_t operation, cmrt_aes_mode_t mode, const void *key, size_t keylen, const void *iv, size_t ivlen, size_t taglen);

/**
 * @brief Set the offset of the starting block in the data unit in XTS
 * mode.
 *
 * This allows encryption/decryption starting at an offset of the data
 * unit. The value must be a multiple of the block size and not be
 * larger than 2^24.
 *
 * This function must be called after cmrt_aes_init() and before any
 * cipher operation takes place. The user is also responsible for
 * supplying the corresponding data (starting from that given offset)
 * in the subsequent cmrt_aes_update() and cmrt_aes_final() calls.
 *
 * @param context Pointer to the device.
 * @param offset The offset, must be a multiple of the AES
 * block size.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_aes_xts_set_offset(cmrt_aes_t context, uint32_t offset);

/**
 * @brief Update aes operation.
 *
 * @param context Pointer to the device.
 * @param input Pointer to input data. This must be 4-byte aligned.
 * @param inlen Length of input data. This must be a multiple of 16.
 * @param output Pointer to output data. This must be 4-byte aligned.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_aes_update(cmrt_aes_t context, const void *input, size_t inlen, void *output);

/**
 * @brief Update aad data for authenticated AES operation.
 *
 * @param context Pointer to the device.
 * @param aad Pointer to input data. This must be 4-byte aligned.
 * @param aadlen Length of input data.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_aes_update_aad(cmrt_aes_t context, const void *aad, size_t aadlen);

/**
 * @brief Final aad data for authenticated AES operation.
 *
 * @param context Pointer to the device.
 * @param aad Pointer to input data. This must be 4-byte aligned.
 * @param aadlen Length of input data. This must be a multiple of 4.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_aes_final_aad(cmrt_aes_t context, const void *aad, size_t aadlen);

/**
 * @brief Finalize AES operation.
 *
 * If the mode is #CMRT_AES_XTS then the length must be either 0 or
 * larger than the AES block size. In other words, the input must
 * contain at least one full block, if the last one is not full.
 *
 * In other modes the length has no restrictions but the input and
 * output buffer sizes must be multiples of 4.
 *
 * @param context Pointer to the device.
 * @param input Pointer to input data. This must be 4-byte aligned.
 * @param inlen Length of input data.
 * @param output Pointer to output data. This must be 4-byte aligned.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_aes_final(cmrt_aes_t context, const void *input, size_t inlen, void *output);

/**
 * @brief Finalize authenticated AES operation.
 *
 * @param context Pointer to the device.
 * @param input Pointer to input data. This must be 4-byte aligned.
 * @param inlen Length of input data. The length has no restrictions but
 *        the datain and dataout buffer sizes must be multiples of 4.
 * @param output Pointer to output data. This must be 4-byte aligned.
 * @param[out] tag buffer This must be 4-byte aligned and sufficient
 * to hold the tag (as specified on cmrt_aes_init().)
 * @param[in,out] taglen length of tag buffer, returns actual length
 * of tag in bytes
 * @return Zero on success, -ERRNO on error.
 * @note on tag mismatch on decryption the output area will be
 * zeroed. Any memory passed in previously through cmrt_aes_update()
 * will still remain decrypted.
 */
__syscall int cmrt_aes_ae_final(cmrt_aes_t context, const void *input, size_t inlen, void *output, void *tag, size_t *taglen);

/**
 * @brief Construct nonce block for AES CCM
 *
 * AES CCM encoded nonce with respect to rfc3610. The encoded nonce is later
 * fed to cmrt_aes_init as iv.
 *
 * @param buf Pointer to the encoded buffer as output. Must be 32bit aligned.
 * @param buflen Size of buf in bytes.
 * @param nonce Pointer to nonce.
 * @param noncelen Length of nonce in bytes. Must be between 7-13.
 * @param ptlen Length of message.
 * @param taglen Length of tag. Supported lengths are 4, 6, 8, 12, 14, 16.
 * @param hasaad Indicates if AAD is expected. 1 for having AAD, otherwise 0.
 * @return Size of encoded buf in bytes. -1 on error.
 */
__syscall int cmrt_aes_ccm_encode_nonce(void *buf, size_t buflen, const void *nonce, size_t noncelen, size_t ptlen, size_t taglen, int hasaad);

/**
 * @brief Construct AAD block for AES CCM.
 *
 * AES CCM encoded AAD with respect to rfc3610. The encoded AAD is later
 * fed to cmrt_aes_final_aad as aad.
 *
 * @param buf Pointer to the encoded buffer as output. Must be 32bit aligned.
 * @param buflen Size of buf in bytes.
 * @param aad Pointer to AAD.
 * @param aadlen Length of AAD in bytes. Must be less than 2^32 bytes.
 * @return Size of encoded buf in bytes. -1 on error.
 */
__syscall int cmrt_aes_ccm_encode_aad(void *buf, size_t buflen, const void *aad, size_t aadlen);

#ifdef __cplusplus
}
#endif

#include <syscalls/aes.h>

#endif
/** @}*/
