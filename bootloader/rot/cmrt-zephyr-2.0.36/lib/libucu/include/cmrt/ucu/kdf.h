/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file kdf.h
 *
 * @brief Public APIs for the KDF driver.
 */

#ifndef CMRT_KDF_H
#define CMRT_KDF_H

#include <stdint.h>
#include <stddef.h>

#include <drivers/cmrt/hc.h>

/* TODO: Comment based on ecies.h. Please review. */
/**
 * @brief Key Derivation
 * @defgroup kdf_interface KDF Interface
 * @ingroup kdf_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief HKDF extract with HMAC-SHA256 as per RFC-5869.
 *
 * Generates a pseudorandom key of 32 bytes using an  optional public salt
 * value and some arbitrary keying material. The output of this function is
 * intended to used as the input PRK of the HKDF expand function.
 *
 * @param hc Device context handle to an open hash core.
 * @param salt Pointer to optional salt value. Can be NULL.
 *             Must be 4-byte aligned.
 * @param saltlen Length of salt in bytes. Must be 0 if salt is NULL.
 * @param ikm Pointer to input keying material. Must be 4-bytes aligned.
 * @param ikmlen Length of ikm in bytes.
 * @param prk Pointer to output buffer. The function outputs exactly 32 bytes.
 *            Must be 4-bytes aligned.
 * @return Zero on success, -ERRNO on error.
 */
int hkdf_extract(cmrt_hc_t hc, const void *salt, size_t saltlen, const void *ikm,
		size_t ikmlen, void *prk);

/**
 * @brief HKDF expand with HMAC-SHA256 as per RFC-5869.
 *
 * Derives a cryptographic key of a specified length from a pseudorandom key.
 *
 * @param hc Device context handle to an open hash core.
 * @param prk Pointer to an input pseudorandom key at least 32 bytes long.
 *            Must be 4-bytes aligned.
 * @param prklen Length of prk in bytes.
 * @param info Pointer to application specific information to be included in key
 *             derivation. Can be NULL. Must be 4-byte aligned.
 * @param infolen Length of info in bytes. Can be 0.
 * @param l Length of output keying material in bytes. Cannot be 0.
 * @param okm Pointer to output buffer. Must be 4-bytes aligned.
 * @return Zero on success, -ERRNO on error.
 */
int hkdf_expand(cmrt_hc_t hc, const void *prk, size_t prklen, const void *info,
		size_t infolen, size_t l, void *okm);

/**
 * @brief HKDF extract and then expand with HMAC-SHA256 as per RFC-5869.
 *
 * Derives a cryptographic key of a speicified length using a pseudorandom key
 * obtained from the input ikm and salt using the HKDF extract function.
 * It is the same as calling the extract function to obtain a prk, and then
 * calling the expand function with the prk.
 *
 * @param hc Device context handle to an open hash core.
 * @param salt Pointer to optional salt value. Can be NULL.
 *             Must be 4-byte aligned.
 * @param saltlen Length of salt in bytes. Must be 0 if salt is NULL.
 * @param ikm Pointer to input keying material. Must be 4-bytes aligned.
 * @param ikmlen Length of ikm in bytes.
 * @param info Pointer to application specific information to be included in key
 *             derivation. Can be NULL. Must be 4-byte aligned.
 * @param infolen Length of info in bytes. Can be 0.
 * @param l Length of output keying material in bytes. Cannot be 0.
 * @param okm Pointer to output buffer. Must be 4-bytes aligned.
 * @return Zero on success, -ERRNO on error.
 */
int hkdf_extract_expand(cmrt_hc_t hc, const void *salt, size_t saltlen,
		const void *ikm, size_t ikmlen, const void *info, size_t infolen,
		size_t l, void *okm);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
