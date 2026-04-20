/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include <errno.h>
#include <hexutil.h>

#include <cri/cmrt/teedev_dmac.h>
#include <cri/cmrt/sac.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/hc.h>
#include <cri/cmrt/aes.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>
#include <cri/cmrt.h>
#include <cri/cmrt/pke.h>

#include "cmvp_sw.h"
#include "cri_utils.h"
#include "cri_crypto.h"

uint32_t swap32(uint32_t x)
{
	x = (x << 16) ^ (x >> 16);
	x = ((x & 0x00ff00ff) << 8) ^ ((x >> 8) & 0x00ff00ff);
	return x;
}

void reverse_words(const void *in, const size_t length, void *out)
{
	const uint32_t *iptr = in;
	uint32_t *optr = out;

	for (size_t i = 0; i < length; i++) {
		optr[i] = swap32(iptr[length - 1 - i]);
	}
}

void reverse_endian_words(const void *in, const size_t length, void *out)
{
	const uint32_t *iptr = in;
	uint32_t *optr = out;

	for (size_t i = 0; i < length; i++) {
		optr[i] = swap32(iptr[i]);
	}
}

int32_t fips_write_to_shared_memory(const uint8_t *buffer,
		uint32_t buffer_length,
		teec_abi_invokecommand_t *h,
		uint32_t index)
{
	int32_t status = 0;

	if (buffer_length > h->params[index].memref.size) {
		dprintk("The shared memory buffer is not large enough: %d -> %d\n",
				buffer_length, h->params[index].memref.size);
		status = -ENOSPC;
		goto out;
	}

	memcpy((uint8_t *) (h->params[index].memref.offset + SAC_MEMORY_BASE), buffer, buffer_length);
	h->params[index].memref.size = buffer_length;
	dprintk("Wrote %d bytes to shared memory\n", buffer_length);

out:
	return status;
}

int32_t fips_read_from_shared_memory(teec_abi_invokecommand_t *h,
		uint32_t index,
		uint8_t *buffer,
		uint32_t *buffer_length)
{
	int32_t status = 0;

	if (h->params[index].memref.size > *buffer_length) {
		dprintk("The internal memory is not large enough: %d -> %d\n",
				h->params[index].memref.size, *buffer_length);
		status = -ENOSPC;
		goto out;
	}

	*buffer_length = h->params[index].memref.size;
	memcpy(buffer, (uint8_t *) (h->params[index].memref.offset + SAC_MEMORY_BASE), *buffer_length);
	dhexdump("Read from shared memory", buffer, *buffer_length);

out:
	return status;
}

int32_t fips_hash(uint8_t *input,
		uint32_t input_length,
		fips_hash_algorithm hash_algorithm,
		uint8_t *digest,
		uint32_t *digest_length)
{
	int32_t status;

	hash_work_struct sha;

	switch (hash_algorithm) {
	case FIPS_HASH_SHA224:
		sha.hashtype = HC_HASH_ALGO_SHA_224;
		sha.hashlen = 28;
		break;
	case FIPS_HASH_SHA256:
		sha.hashtype = HC_HASH_ALGO_SHA_256;
		sha.hashlen = 32;
		break;
	case FIPS_HASH_SHA384:
		sha.hashtype = HC_HASH_ALGO_SHA_384;
		sha.hashlen = 48;
		break;
	case FIPS_HASH_SHA512:
		sha.hashtype = HC_HASH_ALGO_SHA_512;
		sha.hashlen = 64;
		break;
	case FIPS_HASH_SHA512_224:
		sha.hashtype = HC_HASH_ALGO_SHA_512_224;
		sha.hashlen = 28;
		break;
	case FIPS_HASH_SHA512_256:
		sha.hashtype = HC_HASH_ALGO_SHA_512_256;
		sha.hashlen = 32;
		break;
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
	case FIPS_HASH_SHA3_224:
		sha.hashtype = HC_HASH_ALGO_SHA3_224;
		sha.hashlen = 28;
		break;
	case FIPS_HASH_SHA3_256:
		sha.hashtype = HC_HASH_ALGO_SHA3_256;
		sha.hashlen = 32;
		break;
	case FIPS_HASH_SHA3_384:
		sha.hashtype = HC_HASH_ALGO_SHA3_384;
		sha.hashlen = 48;
		break;
	case FIPS_HASH_SHA3_512:
		sha.hashtype = HC_HASH_ALGO_SHA3_512;
		sha.hashlen = 64;
		break;
#endif
	default:
		status = -EINVAL;
		goto out;
	}

	*digest_length = sha.hashlen;
	status = cri_hash(&sha, input, input_length, digest, *digest_length, FIPS_HC_1);

out:
	return status;
}

#ifdef CONFIG_DEBUG
const char *fips_command_str(fips_command cmd)
{
#define A(X) { X, #X }
	static const struct {
		uint32_t cmdcode;
		const char *name;
	} cmdcodes[] = {
		A(FIPS_SERVICE_INVALID_COMMAND),
		A(FIPS_SERVICE_LOGIN_FINAL),
		A(FIPS_SERVICE_CREATE_USER),
		A(FIPS_SERVICE_DELETE_USER),
		A(FIPS_SERVICE_GEN_SYMM_KEY),
		A(FIPS_SERVICE_DERIVE_SYMM_KEY),
		A(FIPS_SERVICE_DERIVE_SYMM_KEY_TWO_STEP),
		A(FIPS_SERVICE_GEN_EC_KEYPAIR),
		A(FIPS_SERVICE_GEN_RSA_KEYPAIR),
		A(FIPS_SERVICE_IMPORT_KEY),
		A(FIPS_SERVICE_EXPORT_KEY),
		A(FIPS_SERVICE_EXPORT_KEY_KTC),
		A(FIPS_SERVICE_AES_ECB),
		A(FIPS_SERVICE_AES_GCM_INIT),
		A(FIPS_SERVICE_AES_GCM_AAD_UPDATE),
		A(FIPS_SERVICE_AES_GCM_UPDATE),
		A(FIPS_SERVICE_AES_GCM_ENCRYPT_FINAL),
		A(FIPS_SERVICE_AES_GCM_DECRYPT_FINAL),
		A(FIPS_SERVICE_AES_CBC_INIT),
		A(FIPS_SERVICE_AES_CBC_UPDATE),
		A(FIPS_SERVICE_AES_CBC_FINAL),
		A(FIPS_SERVICE_AES_CTR_INIT),
		A(FIPS_SERVICE_AES_CTR_UPDATE),
		A(FIPS_SERVICE_AES_CTR_FINAL),
		A(FIPS_SERVICE_AES_CFB128_INIT),
		A(FIPS_SERVICE_AES_CFB128_UPDATE),
		A(FIPS_SERVICE_AES_CFB128_FINAL),
		A(FIPS_SERVICE_ECDSA_SIGN),
		A(FIPS_SERVICE_ECDSA_VERIFY),
		A(FIPS_SERVICE_ECDSA_PK_TEST),
		A(FIPS_SERVICE_ECDH),
		A(FIPS_SERVICE_RSA_SIGN),
		A(FIPS_SERVICE_RSA_VERIFY),
		A(FIPS_SERVICE_MAC_GEN_INIT),
		A(FIPS_SERVICE_MAC_GEN_FINAL),
		A(FIPS_SERVICE_MAC_VERIFY_INIT),
		A(FIPS_SERVICE_MAC_VERIFY_FINAL),
		A(FIPS_SERVICE_MAC_UPDATE),
		A(FIPS_SERVICE_HASH_INIT),
		A(FIPS_SERVICE_HASH_UPDATE),
		A(FIPS_SERVICE_HASH_FINAL),
		A(FIPS_SERVICE_GET_TRNG),
		A(FIPS_SERVICE_LIST_ASSETS),
		A(FIPS_SERVICE_MOVE_ASSET),
		A(FIPS_DELETE_DYNAMIC_ASSET),
		A(FIPS_DELETE_STATIC_ASSET),
		A(FIPS_SERVICE_ZEROIZE),
		A(FIPS_SERVICE_SELF_TEST),
		A(FIPS_SERVICE_RESET),
		A(FIPS_SERVICE_SHOW_STATUS),
		A(FIPS_SERVICE_DRBG),
		A(FIPS_SERVICE_GEN_KYBER_KEM_KEYPAIR),
		A(FIPS_SERVICE_GEN_DILITHIUM_KEYPAIR),
		A(FIPS_SERVICE_DILITHIUM_SIGN),
		A(FIPS_SERVICE_DILITHIUM_VERIFY),
		A(FIPS_SERVICE_GEN_KYBER_KEM_KEYPAIR),
		A(FIPS_SERVICE_KYBER_KEM_ENC),
		A(FIPS_SERVICE_KYBER_KEM_DEC),
		A(FIPS_SERVICE_LMS_VERIFY),
		A(FIPS_SERVICE_HSS_VERIFY),
		A(FIPS_SERVICE_XMSS_VERIFY),
		A(FIPS_SERVICE_XMSSMT_VERIFY)
	};
#undef A
	enum { k_num_cmdcodes = sizeof(cmdcodes) / sizeof(cmdcodes[0]) };
	for (uint32_t i = 0; i < k_num_cmdcodes; ++i) {
		if (cmdcodes[i].cmdcode == cmd)
			return cmdcodes[i].name;
	}
	return "UNKNOWN_COMMAND";
}

const char *fips_asset_type_str(fips_asset_type type)
{
#define A(X) { X, #X }
	static const struct {
		uint32_t asset_type;
		const char *name;
	} asset_types[] = {
		A(FIPS_TYPE_AES),
		A(FIPS_TYPE_HMAC_SHA224),
		A(FIPS_TYPE_HMAC_SHA256),
		A(FIPS_TYPE_HMAC_SHA384),
		A(FIPS_TYPE_HMAC_SHA512),
		A(FIPS_TYPE_RSA_PUBLIC_KEY),
		A(FIPS_TYPE_RSA_KEYPAIR),
		A(FIPS_TYPE_RSA_PF_KEYPAIR),
		A(FIPS_TYPE_RSA_CRT_KEYPAIR),
		A(FIPS_TYPE_ECDSA_PUBLIC_KEY),
		A(FIPS_TYPE_ECDSA_KEYPAIR),
		A(FIPS_TYPE_ECDH_PUBLIC_KEY),
		A(FIPS_TYPE_ECDH_KEYPAIR),
		A(FIPS_TYPE_SHARED_SECRET),
		A(FIPS_TYPE_AES_GCM_ENCRYPT),
		A(FIPS_TYPE_AES_GCM_DECRYPT),
		A(FIPS_TYPE_WRAP_KEY),
		A(FIPS_TYPE_SECRET),
		A(FIPS_TYPE_HMAC_SHA3_224),
		A(FIPS_TYPE_HMAC_SHA3_256),
		A(FIPS_TYPE_HMAC_SHA3_384),
		A(FIPS_TYPE_HMAC_SHA3_512),
		A(FIPS_TYPE_DILITHIUM_PUBLIC_KEY),
		A(FIPS_TYPE_DILITHIUM_KEYPAIR),
		A(FIPS_TYPE_KYBER_ENCAP_KEY),
		A(FIPS_TYPE_KYBER_KEYPAIR)
	};
#undef A
	enum { k_num_asset_types = sizeof(asset_types) / sizeof(asset_types[0]) };
	for (uint32_t i = 0; i < k_num_asset_types; ++i) {
		if (asset_types[i].asset_type == type)
			return asset_types[i].name;
	}
	return "UNKNOWN_ASSET_TYPE";
}
#endif

int cmrt_pke_rsa_ctx_init(struct cmrt_rsa_ctx *ctx, size_t bit_length, void *buf)
{
	static const uint32_t E = 0x00010001;
	uint32_t bytes_len = bit_length / 8;
	memset(buf, 0, 9 * bytes_len + sizeof(uint32_t));
	ctx->key.bits = bit_length;
	ctx->key.e = (uint8_t *)&E;
	ctx->key.elength = 4;
	ctx->key.flags = 0;

	ctx->key.n = buf;
	ctx->key.d = ctx->key.n + bytes_len;

	ctx->key.p = ctx->key.d + bytes_len;
	ctx->key.q = ctx->key.p + bytes_len;
	ctx->key.dp = ctx->key.q + bytes_len;
	ctx->key.dq = ctx->key.dp + bytes_len;
	ctx->key.iq = ctx->key.dq + bytes_len;
	ctx->key.mask = ctx->key.iq + bytes_len;

	ctx->signature = ctx->key.mask + sizeof(uint32_t);
	ctx->message = ctx->signature + bytes_len;

	return 0;
}

int cri_rsa_pub(cmrt_pke_t pke, struct cmrt_rsa_ctx *ctx)
{
	return cmrt_pke_rsa_public_key_primitive(pke, ctx->key.bits,
				ctx->key.n, ctx->key.e, ctx->signature, ctx->message);
}
