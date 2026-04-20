/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file ecies.h
 *
 * @brief Public APIs for the ECIES driver.
 */

#ifndef CRI_ECIES_H
#define CRI_ECIES_H

#include <stdint.h>
#include <stddef.h>
#include <cri/cmrt.h>

/**
 * @brief ECIES Interface
 * @defgroup ecies_interface ECIES Interface
 * @ingroup ecies_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_ecies_t;
#else
typedef struct cmrt_ecies_context *cri_ecies_t;
#endif

typedef enum cri_ecies_mode_e {
	/** EC: NIST P-256,
	   KDF1 HASH: SHA256
	   AES-CBC: AES-CBC-128
	   HMAC: HMAC-SHA256 */
	CRI_ECIES_P256_KDF1_SHA256_AES128_HMAC_SHA256,
	/** EC: NIST P-384
	   KDF1 HASH: SHA384
	   AES-CBC: AES-CBC-128
	   HMAC: HMAC-SHA384 */
	CRI_ECIES_P384_KDF1_SHA384_AES128_HMAC_SHA384,
	/** EC: NIST P-521
	   KDF1 HASH: SHA512
	   AES-CBC: AES-CBC-256
	   HMAC: HMAC-SHA512 */
	CRI_ECIES_P521_KDF1_SHA512_AES256_HMAC_SHA512
} cri_ecies_mode_t;

typedef enum cri_ecies_operation_e {
	CRI_ECIES_ENCRYPT,
	CRI_ECIES_DECRYPT
} cri_ecies_operation_t;

/**
 * In systems with multiple hash cores, secondary HC will be used
 */
#define CRI_ECIES_O_USE_HC2          (0x1 << 16)


/**
 * @brief Open ECIES context for subsequent operations.
 *
 * Open and reserve a ECIES context (PKE, HC, AES cores).
 * May block for a context to be available.
 *
 * @param flags CRI_ECIES_O_USE_HC2 to use HC2 for hash operations.
 * @return Context handle on success, CRI_INVALID_HANDLE on error.
 */
cri_ecies_t cri_ecies_open(uint32_t flags);

/**
 * @brief Initialize ECIES context.
 *
 * @param ecies Device context handle.
 * @param mode A cri_ecies_mode_t enumeration that selects the ECIES
 *             mode of operation and the suite of cryptographic primitives
 *             to be used.
 * @param operation A cri_ecies_operation_t enumeration that selects whether the
 *                  current session is encryption or decryption.
 * @param priv Pointer to a constant buffer that contains the private key for
 *             the ECIES operation.
 * @param privlen A size_t value that specifies the length of the priv buffer
 *                in bytes.
 * @param peerx Pointer to constant buffer that contains the peer's x-component.
 * @param peerxlen Length of the peerx buffer in bytes.
 * @param pubxout Buffer that receives the public key x-component.
 * @param pubxoutlen Length of pubxout buffer.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ecies_init(cri_ecies_t ecies,
		   cri_ecies_mode_t mode,
		   cri_ecies_operation_t operation,
		   const void *priv,
		   size_t privlen,
		   const void *peerx,
		   size_t peerxlen,
		   void *pubxout,
		   size_t pubxoutlen);

/**
 * @brief Update ECIES operation.
 *
 * @param ecies Device context handle.
 * @param input Pointer to constant buffer that holds the input data for the
 *              operation.
 * @param inputlen Length in bytes of the input buffer. This must be a multiple
 *                 of 128 bits or 16 bytes.
 * @param output Pointer to buffer that receives the output from the AES
 *               operation. It is assumed that the output buffer is the same
 *               size or larger than the input buffer.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ecies_update(cri_ecies_t ecies,
		     const void *input,
		     size_t inputlen,
		     void *output);

/**
 * @brief Finalize ECIES operation.
 *
 * @param ecies Device context handle.
 * @param input Pointer to constant buffer that holds the input data for the
 *              operation.
 * @param inputlen Length in bytes of the input buffer.
 * @param sharedinfo Pointer to a constant buffer that holds the shared
 *                   information.
 * @param sharedinfolen Length in bytes of the sharedinfo buffer.
 * @param output Pointer to a buffer that receives the output from the AES
 *               operation. It is assumed that the output buffer is the same
 *               size or larger than the input buffer.
 * @param tag Pointer to a buffer that receives the HMAC digest tag.
 * @param taglen Length in bytes of the tag buffer.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ecies_final(cri_ecies_t ecies,
		    const void *input,
		    size_t inputlen,
		    const void *sharedinfo,
		    size_t sharedinfolen,
		    void *output,
		    void *tag,
		    size_t taglen);

/**
 * @brief Close ECIES context, reverse of open.
 *
 * Close and free previously opened ECIES context.
 *
 * @param ecies Device context handle.
 */
void cri_ecies_close(cri_ecies_t ecies);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
