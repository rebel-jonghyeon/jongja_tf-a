/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef FIPS_TYPES_CMRT_H
#define FIPS_TYPES_CMRT_H

#include <stdint.h>
#include <stddef.h>
#include <cmrt/tee_client_abi.h>

typedef struct {
	uint32_t location;
	uint32_t asset_name_length;
	uint8_t asset_name[64];
} fips_asset_identifier;

typedef enum {
	FIPS_ASSET_DYNAMIC = 0x01,
	FIPS_ASSET_STATIC
} fips_asset_location;

typedef enum {
	FIPS_OWNER_ANONYMOUS = 0,
	FIPS_OWNER_CRYPTO_OFFICER,
	FIPS_OWNER_USER_0,
	FIPS_OWNER_USER_1,
	FIPS_OWNER_USER_2,
	FIPS_OWNER_USER_3,
	FIPS_OWNER_USER_4,
	FIPS_OWNER_USER_5,
	FIPS_OWNER_ALL = 0xFF
} fips_owner_user;

typedef struct {
	uint32_t magic;
	uint16_t ver_minor;
	uint16_t ver_major;
	uint32_t metadata;
	void *asset_data;
} fips_asset;

typedef enum {
	FIPS_EXTERNAL_ASSET = 0,
	FIPS_INTERNAL_ASSET
} fips_asset_creation_status;

typedef struct {
	size_t size;
	uint8_t *key;
} fips_aes_key;

typedef struct {
	size_t size;
	uint8_t *key;
} fips_hmac_key;

typedef struct {
	size_t exponent_size;
	uint8_t *n;
	uint8_t *e;
} fips_rsa_public_key_components;

typedef struct {
	uint32_t key_type;
	fips_rsa_public_key_components public_key;
} fips_rsa_public_key;

typedef struct {
	uint8_t *d;
} fips_rsa_private_key_components;

typedef struct {
	uint8_t *d;
	uint8_t *p;
	uint8_t *q;
} fips_rsa_pf_private_key_components;

typedef struct {
	uint8_t *p;
	uint8_t *q;
	uint8_t *dp;
	uint8_t *dq;
	uint8_t *iq;
} fips_rsa_crt_private_key_components;

typedef struct {
	uint32_t key_type;
	fips_rsa_public_key_components public_key;
	fips_rsa_private_key_components private_key;
} fips_rsa_keypair;

typedef struct {
	uint32_t key_type;
	fips_rsa_public_key_components public_key;
	fips_rsa_crt_private_key_components private_key;
} fips_rsa_crt_keypair;

typedef enum {
	FIPS_ECC_NIST_P224 = 0x01,
	FIPS_ECC_NIST_P256,
	FIPS_ECC_NIST_P384,
	FIPS_ECC_NIST_P521
} fips_curves;

typedef struct {
	uint8_t *x;
	uint8_t *y;
} fips_ecdsa_public_key_components;

typedef struct {
	uint32_t curve_type;
	fips_ecdsa_public_key_components public_key;
} fips_ecdsa_public_key;

typedef struct {
	uint32_t curve_type;
	fips_ecdsa_public_key_components public_key;
	uint8_t *private_key;
} fips_ecdsa_keypair;

typedef struct {
	uint32_t curve_type;
	uint8_t *x;
} fips_ecdh_public_key;

typedef struct {
	uint32_t curve_type;
	uint8_t *x;
	uint8_t *d;
} fips_ecdh_keypair;

typedef struct {
	size_t size;
	uint8_t *shared_secret;
} fips_shared_secret;

typedef struct {
	size_t size;
	uint8_t *secret;
} fips_secret_data;

typedef struct {
	uint32_t asset_name_length;
	uint8_t asset_name[64];
} fips_asset_list_t;

typedef enum {
	FIPS_KDF_FIXED_INFO_NONE,
	FIPS_KDF_FIXED_INFO_COMPONENTS,
	FIPS_KDF_FIXED_INFO_DATA
} fips_fixed_info_type;

typedef struct {
	uint32_t label_size;
	uint8_t *label;
	uint32_t context_size;
	uint8_t *context;
} fips_fixed_info_components;

typedef struct {
	uint32_t data_size;
	uint8_t *data;
} fips_fixed_info_data;

typedef struct {
	uint32_t fixed_info_type;
	uint32_t output_bit_length;
	uint32_t output_key_length;
	uint32_t salt_size;
	uint8_t *salt;
} fips_other_info;

typedef enum {
	FIPS_RSA_2K = 1,
	FIPS_RSA_3K,
	FIPS_RSA_4K,
	FIPS_RSA_PF_2K,
	FIPS_RSA_PF_3K,
	FIPS_RSA_PF_4K,
	FIPS_RSA_CRT_2K,
	FIPS_RSA_CRT_3K,
	FIPS_RSA_CRT_4K
} fips_rsa_key_type;

typedef enum {
	FIPS_HASH_INVALID = 0,
	FIPS_HASH_SHA224,
	FIPS_HASH_SHA256,
	FIPS_HASH_SHA384,
	FIPS_HASH_SHA512,
	FIPS_HASH_SHA512_224,
	FIPS_HASH_SHA512_256,
	FIPS_HASH_SHA3_224,
	FIPS_HASH_SHA3_256,
	FIPS_HASH_SHA3_384,
	FIPS_HASH_SHA3_512,
	FIPS_HASH_NONE
} fips_hash_algorithm;

enum {
	FIPS_CIPHER_INVALID_DIRECTION = 0,
	FIPS_CIPHER_ENCRYPT,
	FIPS_CIPHER_DECRYPT
};

enum {
	FIPS_ROLE_INVALID_PK = 0,
	FIPS_ROLE_ECDSA_P256_PK
};

typedef struct {
	uint32_t public_key_type;
	uint8_t *public_key;
} fips_role_public_key;

typedef enum {
	FIPS_ZEROIZE_DYNAMIC = 0,
	FIPS_ZEROIZE_STATIC,
	FIPS_ZEROIZE_ALL,
} fips_zeroize_mode;

typedef enum {
	FIPS_TYPE_AES = 0x1,
	FIPS_TYPE_HMAC_SHA224,
	FIPS_TYPE_HMAC_SHA256,
	FIPS_TYPE_HMAC_SHA384,
	FIPS_TYPE_HMAC_SHA512,
	FIPS_TYPE_RSA_PUBLIC_KEY,
	FIPS_TYPE_RSA_KEYPAIR,
	FIPS_TYPE_RSA_PF_KEYPAIR,
	FIPS_TYPE_RSA_CRT_KEYPAIR,
	FIPS_TYPE_ECDSA_PUBLIC_KEY,
	FIPS_TYPE_ECDSA_KEYPAIR,
	FIPS_TYPE_ECDH_PUBLIC_KEY,
	FIPS_TYPE_ECDH_KEYPAIR,
	FIPS_TYPE_SHARED_SECRET,
	FIPS_TYPE_AES_GCM_ENCRYPT,
	FIPS_TYPE_AES_GCM_DECRYPT,
	FIPS_TYPE_WRAP_KEY,
	FIPS_TYPE_SECRET,
	FIPS_TYPE_HMAC_SHA3_224,
	FIPS_TYPE_HMAC_SHA3_256,
	FIPS_TYPE_HMAC_SHA3_384,
	FIPS_TYPE_HMAC_SHA3_512,
	FIPS_TYPE_DILITHIUM_PUBLIC_KEY,
	FIPS_TYPE_DILITHIUM_KEYPAIR,
	FIPS_TYPE_KYBER_ENCAP_KEY,
	FIPS_TYPE_KYBER_KEYPAIR,

	FIPS_TYPE_NUM
} fips_asset_type;

extern uint8_t asset_overhead[FIPS_TYPE_NUM];

typedef enum {
	FIPS_SERVICE_INVALID_COMMAND = 0,
	FIPS_SERVICE_LOGIN_FINAL,
	FIPS_SERVICE_CREATE_USER,
	FIPS_SERVICE_DELETE_USER,
	FIPS_SERVICE_GEN_SYMM_KEY,
	FIPS_SERVICE_DERIVE_SYMM_KEY,
	FIPS_SERVICE_DERIVE_SYMM_KEY_TWO_STEP,
	FIPS_SERVICE_GEN_EC_KEYPAIR,
	FIPS_SERVICE_GEN_RSA_KEYPAIR,
	FIPS_SERVICE_IMPORT_KEY,
	FIPS_SERVICE_EXPORT_KEY,
	FIPS_SERVICE_EXPORT_KEY_KTC,
	FIPS_SERVICE_AES_ECB,
	FIPS_SERVICE_AES_GCM_INIT,
	FIPS_SERVICE_AES_GCM_AAD_UPDATE,
	FIPS_SERVICE_AES_GCM_UPDATE,
	FIPS_SERVICE_AES_GCM_ENCRYPT_FINAL,
	FIPS_SERVICE_AES_GCM_DECRYPT_FINAL,
	FIPS_SERVICE_AES_CBC_INIT,
	FIPS_SERVICE_AES_CBC_UPDATE,
	FIPS_SERVICE_AES_CBC_FINAL,
	FIPS_SERVICE_AES_CTR_INIT,
	FIPS_SERVICE_AES_CTR_UPDATE,
	FIPS_SERVICE_AES_CTR_FINAL,
	FIPS_SERVICE_AES_CFB128_INIT,
	FIPS_SERVICE_AES_CFB128_UPDATE,
	FIPS_SERVICE_AES_CFB128_FINAL,
	FIPS_SERVICE_ECDSA_SIGN,
	FIPS_SERVICE_ECDSA_VERIFY,
	FIPS_SERVICE_ECDSA_PK_TEST,
	FIPS_SERVICE_ECDH,
	FIPS_SERVICE_RSA_SIGN,
	FIPS_SERVICE_RSA_VERIFY,
	FIPS_SERVICE_MAC_GEN_INIT,
	FIPS_SERVICE_MAC_GEN_FINAL,
	FIPS_SERVICE_MAC_VERIFY_INIT,
	FIPS_SERVICE_MAC_VERIFY_FINAL,
	FIPS_SERVICE_MAC_UPDATE,
	FIPS_SERVICE_HASH_INIT,
	FIPS_SERVICE_HASH_UPDATE,
	FIPS_SERVICE_HASH_FINAL,
	FIPS_SERVICE_GET_TRNG,
	FIPS_SERVICE_LIST_ASSETS,
	FIPS_SERVICE_MOVE_ASSET,
	FIPS_DELETE_DYNAMIC_ASSET,
	FIPS_DELETE_STATIC_ASSET,
	FIPS_SERVICE_ZEROIZE,
	FIPS_SERVICE_SELF_TEST,
	FIPS_SERVICE_RESET,
	FIPS_SERVICE_SHOW_STATUS,
	FIPS_SERVICE_DRBG,
	FIPS_SERVICE_GEN_DILITHIUM_KEYPAIR,
	FIPS_SERVICE_DILITHIUM_SIGN,
	FIPS_SERVICE_DILITHIUM_VERIFY,
	FIPS_SERVICE_GEN_KYBER_KEM_KEYPAIR,
	FIPS_SERVICE_KYBER_KEM_ENC,
	FIPS_SERVICE_KYBER_KEM_DEC,
	FIPS_SERVICE_LMS_VERIFY,
	FIPS_SERVICE_HSS_VERIFY,
	FIPS_SERVICE_XMSS_VERIFY,
	FIPS_SERVICE_XMSSMT_VERIFY,

	NUMBER_OF_SERVICES
} fips_command;

typedef enum {
	FIPS_HC_1 = 1,
	FIPS_HC_2 = 2,
	FIPS_HC_NONE = 3
} fips_hc_id;

#define FIPS_SERVICE_LOGIN_INIT 100

typedef enum {
	FIPS_DILITHIUM_LEVEL_2 = 2,
	FIPS_DILITHIUM_LEVEL_3 = 3,
	FIPS_DILITHIUM_LEVEL_5 = 5
} fips_dilithium_level;

typedef struct {
	uint8_t *pk;
} fips_dilithium_public_key_components;

typedef struct {
	uint32_t k;
	fips_dilithium_public_key_components public_key;
} fips_dilithium_public_key;

typedef struct {
	uint8_t *sk;
} fips_dilithium_secret_key_components;

typedef struct {
	uint32_t k;
	fips_dilithium_public_key_components public_key;
	fips_dilithium_secret_key_components secret_key;
} fips_dilithium_keypair;

typedef enum {
	FIPS_KYBER_LEVEL_2 = 2,
	FIPS_KYBER_LEVEL_3 = 3,
	FIPS_KYBER_LEVEL_4 = 4
} fips_kyber_level;

typedef struct {
	uint8_t *ek;
} fips_kyber_encap_key_components;

typedef struct {
	uint32_t k;
	fips_kyber_encap_key_components encap_key;
} fips_kyber_encap_key;

typedef struct {
	uint8_t *dk;
} fips_kyber_decap_key_components;

typedef struct {
	uint32_t k;
	fips_kyber_encap_key_components encap_key;
	fips_kyber_decap_key_components decap_key;
} fips_kyber_keypair;

#endif
