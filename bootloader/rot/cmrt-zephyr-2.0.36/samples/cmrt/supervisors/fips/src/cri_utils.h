/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CRI_UTILS_H
#define CRI_UTILS_H

#include <stdint.h>
#include <stddef.h>
#include <cri/cmrt/fips/fips_types.h>
#include <cri/cmrt/pke.h>
#include <drivers/cmrt/pke.h>

#define CHECK_COMMAND(x) do { \
	if (((uint32_t *) workcontext)[0] != 0x00000000) { \
		dprintk("Working context is not empty, cleaning now\n"); \
		status = -EPERM; \
		goto out; \
	} \
	((uint32_t *) workcontext)[0] = (x); \
} while (0);

#define ALIGN_32_BIT_POINTER(x) (((uint32_t)(x) + 3) & 0xFFFFFFFC)

#define GET_32_BIT_WORD(x, y, z) do { \
	memcpy(&(x), (y) + offset, 4 * sizeof(uint8_t)); \
	(x) = swap32((x)); \
	offset += 4 * sizeof(uint8_t); \
} while (0);

#ifndef BIT2WORD
#define BIT2WORD(bits) ((bits) / 32)
#endif
#ifndef BIT2BYTE
#define BIT2BYTE(bits) ((bits) / 8)
#endif

#define _RSA_CONCAT(a, b) a##b

#define DCLR_CTX(bits) _RSA_CONCAT(_rsa_context_, bits)
#define RSA_CTX_SIZE(bits) sizeof(struct DCLR_CTX(bits))

#define DCLR_KEY_CTX(bits) _RSA_CONCAT(aux_cmrt_rsa_key_, bits)
#define DCLR_RSA_CTX(bits) _RSA_CONCAT(aux_cmrt_rsa_ctx_, bits)

#define DEF_KEY_CTX(bits) \
struct DCLR_KEY_CTX(bits) { \
	uint8_t n[BIT2BYTE(bits)]; /**< public key modulus */ \
	uint8_t e[BIT2BYTE(bits)]; /**< public key exponent */ \
	uint32_t elength; /**< byte length of e */ \
	uint8_t d[BIT2BYTE(bits)]; /**< private exponent, if required */ \
	uint8_t p[BIT2BYTE(bits)/8+8]; /**< private key (CRT) prime */ \
	uint8_t q[BIT2BYTE(bits)/8+8]; /**< private key (CRT) prime */ \
	uint8_t dp[BIT2BYTE(bits)/8+8]; /**< private key dp = d mod p-1 */ \
	uint8_t dq[BIT2BYTE(bits)/8+8]; /**< private key dq = d mod q-1 */ \
	uint8_t iq[BIT2BYTE(bits)/8+8]; /**< private key iq = q^-1 mod p */ \
	uint8_t mask[8]; /**< mask used to blind key */ \
};

DEF_KEY_CTX(1024);
DEF_KEY_CTX(2048);
DEF_KEY_CTX(3072);
DEF_KEY_CTX(4096);
DEF_KEY_CTX(8192);

#define DEF_CMRT_RSA_CTX(bits) \
struct DCLR_RSA_CTX(bits) { \
	struct DCLR_KEY_CTX(bits) key; \
	uint8_t signature[BIT2BYTE(bits)]; \
	uint8_t message[BIT2BYTE(bits)]; \
};

DEF_CMRT_RSA_CTX(1024);
DEF_CMRT_RSA_CTX(2048);
DEF_CMRT_RSA_CTX(3072);
DEF_CMRT_RSA_CTX(4096);
DEF_CMRT_RSA_CTX(8192);

uint32_t swap32(uint32_t x);

/* note length is in 32-bit words */
void reverse_endian_words(const void *in, const size_t length, void *out);

/* note length is in 32-bit words */
void reverse_words(const void *in, const size_t length, void *out);

int32_t fips_write_to_shared_memory(const uint8_t *buffer,
		uint32_t buffer_length,
		teec_abi_invokecommand_t *h,
		uint32_t index);

int32_t fips_read_from_shared_memory(teec_abi_invokecommand_t *h,
		uint32_t index,
		uint8_t *buffer,
		uint32_t *buffer_length);

int32_t fips_hash(uint8_t *input,
		uint32_t input_length,
		fips_hash_algorithm hash_algorithm,
		uint8_t *digest,
		uint32_t *digest_length);

#ifdef CONFIG_DEBUG
const char *fips_command_str(fips_command cmd);
const char *fips_asset_type_str(fips_asset_type type);
#endif

int cmrt_pke_rsa_ctx_init(struct cmrt_rsa_ctx *ctx, size_t bit_length, void *buf);
int cri_rsa_pub(cmrt_pke_t pke, struct cmrt_rsa_ctx *ctx);
#endif
