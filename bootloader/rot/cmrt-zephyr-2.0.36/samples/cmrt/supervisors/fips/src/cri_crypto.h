/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CRI_CRYPTO_H
#define CRI_CRYPTO_H

#include <stdint.h>
#include <stddef.h>

#include <cri/cmrt/pke.h>
#include <cri/cmrt.h>

#include "fips.h"


int32_t init_tmc_with_otp_config();
int32_t cri_get_randomness(uint8_t *buffer, size_t size);

int32_t cri_ecdh(cri_ecc_curve_t curve,
		const uint8_t *priv_key,
		const uint8_t *public_key,
		uint8_t *secret);

int32_t cri_ecdsa_sign(const uint32_t pke_curve, uint8_t *priv_key,
		uint8_t *digest, uint32_t digest_len, uint8_t *r, uint8_t *s);

int32_t cri_full_ecdsa_public_key_validation(cri_ecc_curve_t curve,
		uint8_t *public_key_x,
		uint8_t *public_key_y);

int32_t rsa_pairwise_consistency_check(const uint32_t *n,
		const uint32_t *d,
		uint32_t bit_length,
		uint32_t *work_buffer);

int32_t cri_ecdsa_verify(cri_ecc_curve_t curve, uint8_t *r, uint8_t *s,
		uint8_t *public_key_x, uint8_t *public_key_y, uint8_t *digest, uint32_t digest_len,
		uint8_t *rp);

int32_t cri_hash(hash_work_struct *sha, uint8_t *in_dataarray,
		size_t inlen, uint8_t *out_hash, size_t outlen, const fips_hc_id hc_id);

int32_t cri_mac_gen(hash_work_struct *sha, uint8_t *in_dataarray,
		size_t inlen, uint8_t *key, size_t keylen, uint8_t *out_hash,
		size_t outlen);

int32_t sp800_108_kdf(uint8_t *derived_key,
		uint32_t derived_key_length,
		uint8_t *salt,
		uint32_t salt_length,
		uint8_t *z,
		uint32_t z_length,
		uint8_t *fixed_info,
		uint32_t fixed_info_length,
		uint8_t *work_area);

int32_t kdf_component_extraction_expansion(uint8_t *derived_key,
		uint32_t derived_key_length,
		uint8_t *salt,
		uint32_t salt_length,
		uint8_t *z,
		uint32_t z_length,
		uint8_t *label,
		uint32_t label_length,
		uint8_t *component,
		uint32_t component_length,
		uint8_t *work_area);

bool run_all_kats(void);

#endif
