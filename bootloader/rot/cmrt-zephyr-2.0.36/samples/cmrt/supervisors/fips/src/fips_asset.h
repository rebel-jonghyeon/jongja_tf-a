/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>

#include <cri/cmrt/sic.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>
#include <cri/cmrt/pke.h>
#include <cri/cmrt.h>


#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"

#define TEST_MAGIC(m) (((uint32_t *) (m))[0] != 0xF1951402)
#define TEST_VER_MINOR(m) (((uint16_t *) (m))[2] != 0x0000)
#define TEST_VER_MAJOR(m) (((uint16_t *) (m))[3] != 0x0001)

#define GET_ASSET_TYPE(m) (m & 0xff)
#define GET_ASSET_OWNER(m) ((m >> 8) & 0xff)
#define GET_ASSET_INTERNAL_FLAG(m) ((m >> 16) & 1)

#define GET_ASSET_TYPE_FROM_ASSET(m) ((((uint32_t *) (m))[2]) & 0xff)
#define GET_ASSET_OWNER_FROM_ASSET(m) (((((uint32_t *) (m))[2]) >> 8) & 0xff)
#define GET_ASSET_INTERNAL_FLAG_FROM_ASSET(m) (((((uint32_t *) (m))[2]) >> 16) & 1)

#define SET_ASSET_TYPE_IN_ASSET(m, type) \
	((((uint32_t *) (m))[2]) = ((((uint32_t *) (m))[2]) & 0xffffff00) ^ (type & 0xff))
#define SET_ASSET_TYPE_OWNER(x, y, z) (((uint32_t *) (x))[2] = ((y) << 8) ^ (z))
#define SET_ASSET_INTERNAL_FLAG_IN_ASSET(m, flag) \
	((((uint32_t *) (m))[2]) = ((((uint32_t *) (m))[2]) & 0xfffeffff) ^ ((flag & 1) << 16))

#define SET_FIPS_HEADER(x, y, z) do { \
		((uint32_t *) (x))[0] = 0xF1951402; \
		((uint16_t *) (x))[2] = 0x0000; \
		((uint16_t *) (x))[3] = 0x0001; \
		SET_ASSET_TYPE_OWNER(x, y, z); \
	} while (0);

#define SET_FIPS_KDF_HEADER_LENGTH(x, y) ((uint32_t *)x)[3] = (y)
#define GET_FIPS_KDF_KEY(x) (uint8_t *)&(((uint32_t *)x)[4])

#define GET_HEADER_SIZE() (3 * sizeof(uint32_t))

#define SET_FIPS_EC_HEADER(x, y, z, n) do { \
		SET_FIPS_HEADER((x), (y), (z)); \
		/* curve type*/ \
		((uint32_t *) (x))[3] = (n); \
	} while (0);

#define GET_SECRET_KEY_LENGTH_FROM_ASSET(x) (((uint32_t *) (x))[3])
#define SET_SECRET_KEY_LENGTH_IN_ASSET(x, y) (((uint32_t *) (x))[3] = (y))
#define GET_SECRET_KEY_FROM_ASSET(x) ((uint8_t *)&(((uint32_t *) (x))[4]))

#define CURVE_LENGTH(x) cri_pke_get_curve_length(x)

#define P224_LENGTH (7 * sizeof(uint32_t))
#define P256_LENGTH (8 * sizeof(uint32_t))
#define P384_LENGTH (12 * sizeof(uint32_t))
#define P521_LENGTH (17 * sizeof(uint32_t))

#define GET_EC_CURVE_TYPE(x) (((uint32_t *) (x))[0])
#define GET_EC_ASSET_CURVE_TYPE(x) (((uint32_t *) (x))[3])

#define GET_ECDH_PUBLIC_KEY_ASSET_SIZE(x) (CURVE_LENGTH(x) + (4 * sizeof(uint32_t)))
#define GET_ECDH_KEYPAIR_ASSET_SIZE(x) ((2 * CURVE_LENGTH(x)) + (4 * sizeof(uint32_t)))
#define GET_ECDSA_PUBLIC_KEY_ASSET_SIZE(x) ((2 * CURVE_LENGTH(x)) + (4 * sizeof(uint32_t)))
#define GET_ECDSA_KEYPAIR_ASSET_SIZE(x) ((3 * CURVE_LENGTH(x)) + (4 * sizeof(uint32_t)))

#define GET_ECDSA_PUBLIC_KEY_X_FROM_ASSET(x) ((x) + (4 * sizeof(uint32_t)))
#define GET_ECDSA_PUBLIC_KEY_Y_FROM_ASSET(x, y) ((x) + (4 * sizeof(uint32_t)) + (1 * CURVE_LENGTH(y)))
#define GET_ECDSA_PRIVATE_KEY_FROM_ASSET(x, y) ((x) + (4 * sizeof(uint32_t)) + (2 * CURVE_LENGTH(y)))

#define GET_ECDH_PUBLIC_KEY_FROM_ASSET(x) ((x) + (4 * sizeof(uint32_t)))
#define GET_ECDH_PRIVATE_KEY_FROM_ASSET(x, y) ((x) + (4 * sizeof(uint32_t)) + (1 * CURVE_LENGTH(y)))

#define GET_SHARED_SECRET_SIZE(x) (x + sizeof(uint32_t))
#define GET_SHARED_SECRET_ASSET_SIZE(x) (x + (4 * sizeof(uint32_t)))
#define GET_SHARED_SECRET(x) ((x) + sizeof(uint32_t))
#define GET_SHARED_SECRET_FROM_ASSET(x) ((x) + (4 * sizeof(uint32_t)))
#define SET_SHARED_SECRET_LENGTH(x, y) ((uint32_t *) (x))[3] = y

typedef enum {
	FIPS_INVALID,
	FIPS_RSA,
	FIPS_RSA_PF,
	FIPS_RSA_CRT
} rsa_key_types;

#define GET_RSA_KEY_TYPE_FROM_ASSET(x, y, z) fips_get_rsa_type(((uint32_t *) (x))[3], &(y), &(z))

/* NB: 0x01000100 is 2^16+1 as a little-endian 32-bit value*/
#define SET_FIPS_RSA_HEADER(x, y, z, n) do { \
		SET_FIPS_HEADER((x), (y), (z)); \
		/* key type */ \
		((uint32_t *) (x))[3] = (n); \
		/* public key length */ \
		((uint32_t *) (x))[4] = 4; \
		/* public key */ \
		((uint32_t *) (x))[5] = 0x01000100; \
	} while (0);

extern const uint32_t rsa_element_lengths[3];
extern const uint32_t rsa_crt_element_lengths[3];

#define GET_RSA_HEADER_SIZE() (4 * sizeof(uint32_t))

#define GET_RSA_KEY_LENGTH(x) rsa_element_lengths[(x) - FIPS_RSA_2K]
#define GET_RSA_BIT_LENGTH(x) (8 * rsa_element_lengths[(x) - FIPS_RSA_2K])

#define GET_RSA_PF_KEY_LENGTH(x) rsa_element_lengths[(x) - FIPS_RSA_PF_2K]
#define GET_RSA_PF_BIT_LENGTH(x) (8 * rsa_element_lengths[(x) - FIPS_RSA_PF_2K])

#define GET_RSA_CRT_KEY_LENGTH(x) rsa_crt_element_lengths[(x) - FIPS_RSA_CRT_2K]
#define GET_RSA_CRT_BIT_LENGTH(x) (16 * rsa_crt_element_lengths[(x) - FIPS_RSA_CRT_2K])

#define GET_RSA_PUBLIC_EXPONENT_FROM_ASSET(x) ((x) + (5 * sizeof(uint32_t)))
#define GET_RSA_PUBLIC_MODULUS_FROM_ASSET(x) ((x) + (6 * sizeof(uint32_t)))

#define GET_RSA_PRIVATE_EXPONENT_FROM_ASSET(x, y) ((x) + (6 * sizeof(uint32_t))) \
	+ GET_RSA_KEY_LENGTH(y)
#define GET_RSA_ASSET_SIZE(x) ((6 * sizeof(uint32_t)) + (2 * GET_RSA_KEY_LENGTH(x)))

#define GET_RSA_PF_PRIVATE_EXPONENT_FROM_ASSET(x, y) ((x) + (6 * sizeof(uint32_t))) \
	+ GET_RSA_PF_KEY_LENGTH(y)
#define GET_RSA_PF_PRIVATE_P_FROM_ASSET(x, y) ((x) + (6 * sizeof(uint32_t))) \
	+ (2 * GET_RSA_PF_KEY_LENGTH(y))
#define GET_RSA_PF_PRIVATE_Q_FROM_ASSET(x, y) ((x) + (6 * sizeof(uint32_t))) \
	+ (2 * GET_RSA_PF_KEY_LENGTH(y)) + GET_RSA_PF_KEY_LENGTH(y)/2
#define GET_RSA_PF_ASSET_SIZE(x) ((6 * sizeof(uint32_t)) + (3 * GET_RSA_PF_KEY_LENGTH(x)))

#define GET_RSA_CRT_PRIVATE_P_FROM_ASSET(x, y) ((x) + (6 * sizeof(uint32_t))) \
	+ (2 * GET_RSA_CRT_KEY_LENGTH(y))
#define GET_RSA_CRT_PRIVATE_Q_FROM_ASSET(x, y) ((x) + (6 * sizeof(uint32_t))) \
	+ (3 * GET_RSA_CRT_KEY_LENGTH(y))
#define GET_RSA_CRT_PRIVATE_DP_FROM_ASSET(x, y) ((x) + (6 * sizeof(uint32_t))) \
	+ (4 * GET_RSA_CRT_KEY_LENGTH(y))
#define GET_RSA_CRT_PRIVATE_DQ_FROM_ASSET(x, y) ((x) + (6 * sizeof(uint32_t))) \
	+ (5 * GET_RSA_CRT_KEY_LENGTH(y))
#define GET_RSA_CRT_PRIVATE_IQ_FROM_ASSET(x, y) ((x) + (6 * sizeof(uint32_t))) \
	+ (6 * GET_RSA_CRT_KEY_LENGTH(y))
#define GET_RSA_CRT_ASSET_SIZE(x) ((6 * sizeof(uint32_t)) + (7 * GET_RSA_CRT_KEY_LENGTH(x)))

#define GET_RSA_PUBLIC_KEY_ASSET_SIZE(x) ((6 * sizeof(uint32_t)) + (GET_RSA_KEY_LENGTH(x)))
#define GET_RSA_PF_PUBLIC_KEY_ASSET_SIZE(x) ((6 * sizeof(uint32_t)) + (GET_RSA_PF_KEY_LENGTH(x)))
#define GET_RSA_CRT_PUBLIC_KEY_ASSET_SIZE(x) ((6 * sizeof(uint32_t)) + (2 * GET_RSA_CRT_KEY_LENGTH(x)))

#define GET_MAX_ASSET_SIZE() GET_RSA_CRT_ASSET_SIZE(FIPS_RSA_CRT_4K)

int32_t fips_delete_asset(fips_state_t *state,
		teec_abi_invokecommand_t *h,
		fips_asset_location location);

int32_t fips_read_asset_from_teefs(fips_state_t *state,
		fips_asset_identifier *source_asset,
		uint32_t size,
		uint8_t *asset,
		uint32_t *asset_length);

int32_t fips_read_asset_of_type_from_teefs(fips_state_t *state,
		fips_asset_identifier *source_asset,
		uint32_t size,
		uint8_t *asset,
		uint32_t *asset_length,
		uint8_t asset_type);

int32_t fips_read_asset_from_shared_memory(fips_state_t *state,
		teec_abi_invokecommand_t *h,
		uint32_t index,
		uint8_t *asset,
		uint32_t *asset_length);

int32_t fips_write_asset_to_teefs(fips_state_t *state,
		fips_asset_identifier *destination_asset,
		uint32_t size,
		uint8_t *asset,
		uint32_t asset_length);

int32_t fips_check_valid_asset_size(fips_asset *asset,
		fips_asset_type type,
		size_t checksize);

void fips_get_rsa_type(uint32_t type,
		uint8_t *rsa_type,
		uint8_t *fips_rsa_type);

cri_ecc_curve_t cri_pke_get_fips_curve_from_asset(fips_asset *asset);

cri_ecc_curve_t cri_pke_get_fips_curve(fips_curves type);
