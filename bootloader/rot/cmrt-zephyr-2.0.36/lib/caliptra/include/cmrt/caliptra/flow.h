/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#ifndef CMRT_CALIPTRA_FLOW_H
#define CMRT_CALIPTRA_FLOW_H

#include <cmrt/caliptra/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Key names used in ECC key derivation. */
#define CMRT_KP_INFO_IDevID "IDevID Key Pair"
#define CMRT_KP_INFO_LDevID "LDevID Key Pair"
#define CMRT_KP_INFO_AliasFMC "AliasFMC Key Pair"
#define CMRT_KP_INFO_AliasRT "AliasRT Key Pair"

/**
 * Derive the UDS hash from the obfuscated seed.
 *
 * @param uds_seed obfuscated UDS seed
 * @param uds_hash the UDS hash
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_derive_uds_hash(const cmrt_caliptra_uds_t *uds_seed,
				  cmrt_caliptra_digest_t *uds_hash);

/**
 * Deobfuscate field entropy in-place.
 *
 * @param field_entropy the obfuscated field entropy value
 * @param slot_index index of the field entropy slot
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_deobfuscate_field_entropy(cmrt_caliptra_field_entropy_t *field_entropy, int slot_index);

/**
 * Derive an secp384r1 EC keypair deterministically.
 *
 * priv := HMAC_SHA2_384(input, keyname)
 * pub := [priv]*G (on the P-384 curve)
 *
 * @param input the input key for the underlying HMAC operation
 * @param input_len length of @a input
 * @param keyname key name used in the underlying HMAC operation
 * @param keyname_len length of @a keyname
 * @param[out] priv location for the private key
 * @param[out] pub location for the public key
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_ecckpdf(const void *input, size_t input_len,
			  const char *keyname, size_t keyname_len,
			  cmrt_caliptra_privkey_t *priv, cmrt_caliptra_pubkey_t *pub);

/**
 * Calculate SHA2-384.
 *
 * @param msg data to hash
 * @param msg_len length of @a msg
 * @param out location for the digest
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_hash(const void *msg, size_t msg_len, cmrt_caliptra_digest_t *out);

/**
 * Calculate HMAC-SHA2-384.
 *
 * @param key HMAC key
 * @param key_len length of @a key
 * @param msg data to MAC
 * @param msg_len length of @a msg
 * @param out location for the HMAC digest
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_hmac(const void *key, size_t key_len, const void *msg, size_t msg_len, cmrt_caliptra_digest_t *out);

/**
 * Clear memory securely.
 *
 * Used instead of memset(p, 0, n); which may be optimized away.
 *
 * @param p buffer to clear
 * @param n length of the buffer
 */
void cmrt_caliptra_zeroize(void *p, size_t n);

/**
 * Get device information required for the Caliptra boot flow.
 *
 * @param[out] info device information structure
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_get_deviceinfo(cmrt_caliptra_deviceinfo_t *info);

#ifdef __cplusplus
}
#endif
#endif
