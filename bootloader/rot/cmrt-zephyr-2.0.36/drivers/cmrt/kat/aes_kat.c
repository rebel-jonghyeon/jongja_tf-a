/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <init.h>
#include <drivers/cmrt/aes.h>
#include <drivers/cmrt/eac.h>
#include <drivers/cmrt/sic.h>
#include "aes_kat.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);


typedef struct {
	cmrt_aes_operation_t operation;
	cmrt_aes_mode_t cipher;
	const uint8_t *key;
	size_t keylen;
	const uint8_t *iv;
	size_t ivlen;
	const uint8_t *aad;
	size_t aadlen;
	const uint8_t *tag;
	size_t taglen;
	const uint8_t *input;
	size_t inlen;
	const uint8_t *output;
	size_t outlen;
} aes_kat_t;

#define INIT_AES_SIZED_KAT_T(operation, cipher, key, keylen, input, inlen, iv, ivlen, aad, aadlen, tag, taglen, output, outlen)			\
	{						\
		(operation),				\
		(cipher),				\
		(key),					\
		(keylen),				\
		(iv),					\
		(ivlen),				\
		(aad),					\
		(aadlen),				\
		(tag),					\
		(taglen),				\
		(input),				\
		(inlen),				\
		(output),				\
		(outlen)				\
	}

#define INIT_NOCHAINING_AES_KAT_T(operation, cipher, key, input, output) \
	INIT_AES_SIZED_KAT_T((operation), (cipher), (key), sizeof(key), (input), sizeof(input), NULL, 0, NULL, 0, NULL, 0, (output), sizeof(output))

#define INIT_IV_AES_KAT_T(operation, cipher, key, input, iv, output) \
	INIT_AES_SIZED_KAT_T((operation), (cipher), (key), sizeof(key), (input), sizeof(input), (iv), sizeof(iv), NULL, 0, NULL, 0, (output), sizeof(output))

#define INIT_AES_KAT_T(operation, cipher, key, input, iv, aad, tag, output) \
	INIT_AES_SIZED_KAT_T((operation), (cipher), (key), sizeof(key), (input), sizeof(input), (iv), sizeof(iv), (aad), sizeof(aad), (tag), sizeof(tag), (output), sizeof(output))

#if defined(CONFIG_CMRT_FIPS_140_MODE) && !defined(CONFIG_CMRT_ASIL_B_MODE)
static const uint8_t key0_128[] = {
	0x14, 0x3a, 0xe8, 0xed, 0x65, 0x55,
	0xab, 0xa9, 0x61, 0x10, 0xab, 0x58,
	0x89, 0x3a, 0x8a, 0xe1
};
static const uint8_t key0_256[] = {
	0x14, 0x3a, 0xe8, 0xed, 0x65, 0x55,
	0xab, 0xa9, 0x61, 0x10, 0xab, 0x58,
	0x89, 0x3a, 0x8a, 0xe1, 0x6c, 0x00,
	0x2b, 0x68, 0x24, 0x83, 0xe0, 0xca,
	0xbc, 0xc7, 0x31, 0xc2, 0x53, 0xbe,
	0x56, 0x74
};
static const uint8_t input0[] = {
	0xe2, 0x34, 0xcd, 0xca, 0x26, 0x06,
	0xb8, 0x1f, 0x29, 0x40, 0x8d, 0x5f,
	0x6d, 0xa2, 0x12, 0x06
};

static const uint8_t input1[] = {
	0xf3, 0x44, 0x81, 0xec, 0x3c, 0xc6,
	0x27, 0xba, 0xcd, 0x5d, 0xc3, 0xfb,
	0x08, 0xf2, 0x73, 0xe6
};

static const uint8_t input2[] = {
	0xff, 0x4f, 0x83, 0x91, 0xa6, 0xa4,
	0x0c, 0xa5, 0xb2, 0x5d, 0x23, 0xbe,
	0xdd, 0x44, 0xa5, 0x97
};

static const uint8_t input3[] = {
	0x08, 0xa4, 0xe2, 0xef, 0xec, 0x8a,
	0x8e, 0x33, 0x12, 0xca, 0x74, 0x60,
	0xb9, 0x04, 0x0b, 0xbf
};

static const uint8_t iv0_16[] = {
	0x13, 0x23, 0x7c, 0x49, 0x07, 0x4a,
	0x3d, 0xa0, 0x78, 0xdc, 0x1d, 0x82,
	0x8b, 0xb7, 0x8c, 0x6f
};

static const uint8_t iv0_12[] = {
	0x13, 0x23, 0x7c, 0x49, 0x07, 0x4a,
	0x3d, 0xa0, 0x78, 0xdc, 0x1d, 0x82,
	0x8b, 0xb7, 0x8c, 0x6f
};

static const uint8_t aad0[] = {
	0x71, 0xb5, 0xc0, 0x8a, 0x19, 0x93,
	0xe1, 0x36, 0x2e, 0x4d, 0x0c, 0xe9,
	0xb2, 0x2b, 0x78, 0xd5
};

/* AES CBC vectors */
/* res = AES.new(key0_128, AES.MODE_CBC, iv=iv0_16).encrypt(input0) */
static const uint8_t res_cbc_enc_128[] = { 0x8e, 0x84, 0xbc, 0x64, 0x50, 0xa0, 0x6f, 0x8a, 0xe0, 0x36, 0xdc, 0xdd, 0xa3, 0x49, 0xa1, 0x05 };
/* res = AES.new(key0_128, AES.MODE_CBC, iv=iv0_16).decrypt(input0) */
static const uint8_t res_cbc_dec_128[] = { 0x1b, 0xd4, 0x62, 0x84, 0x8e, 0x99, 0x81, 0x8c, 0x6b, 0x35, 0x29, 0xa2, 0xf7, 0x66, 0x8f, 0xa0 };
/* AES GCM vectors */
/* res, tag = AES.new(key0_256, AES.MODE_GCM, nonce=iv0_12, mac_len=16).update(aad0).encrypt_and_digest(input0) */
static const uint8_t res_gcm_enc_256[] = { 0x8e, 0xc3, 0xa5, 0x91, 0x42, 0x2c, 0xd2, 0x33, 0x84, 0xa0, 0x76, 0x61, 0xee, 0x19, 0xca, 0xbd };
static const uint8_t tag_gcm_enc_256[] = { 0x3d, 0xe5, 0xed, 0x9b, 0x7e, 0x1c, 0x43, 0x02, 0x2a, 0x83, 0xb0, 0xf4, 0x2f, 0xd3, 0xf4, 0xc0 };
static const uint8_t res_gcm_dec_256[] = { 0x64, 0x53, 0x8a, 0xb4, 0x88, 0xa0, 0xe4, 0x1f, 0xbf, 0x2a, 0x8f, 0x5e, 0x3a, 0xbf, 0xd3, 0x04 };
static const uint8_t tag_gcm_dec_256[] = { 0x54, 0x16, 0x1c, 0xea, 0xe1, 0x11, 0x72, 0x0a, 0x1e, 0xf4, 0x96, 0xea, 0xf5, 0x42, 0x2e, 0xdb };
/* AES CTR vectors */
/* res = AES.new(key0_256, AES.MODE_CTR, nonce=iv0_16[0:12], initial_value=iv0_16[12:16]).encrypt(input0) */
static const uint8_t res_ctr_enc_256[] = { 0x1c, 0x26, 0x3a, 0xb0, 0x5a, 0x2f, 0x04, 0x47, 0x9a, 0xa0, 0x13, 0x66, 0x64, 0x77, 0xcf, 0xfd };
/* res = AES.new(key0_256, AES.MODE_CTR, nonce=iv0_16[0:12], initial_value=iv0_16[12:16]).decrypt(input1) */
static const uint8_t res_ctr_dec_256[] = { 0x0d, 0x56, 0x76, 0x96, 0x40, 0xef, 0x9b, 0xe2, 0x7e, 0xbd, 0x5d, 0xc2, 0x01, 0x27, 0xae, 0x1d };
/* AES CFB128 vectors */
/* res = AES.new(key0_256, AES.MODE_CFB, iv=iv0_16, segment_size=128).encrypt(input0) */
static const uint8_t res_cfb_enc_256[] = { 0x1c, 0x26, 0x3a, 0xb0, 0x5a, 0x2f, 0x04, 0x47, 0x9a, 0xa0, 0x13, 0x66, 0x64, 0x77, 0xcf, 0xfd };
/* res = AES.new(key0_256, AES.MODE_CFB, iv=iv0_16, segment_size=128).decrypt(input2) */
static const uint8_t res_cfb_dec_256[] = { 0x01, 0x5d, 0x74, 0xeb, 0xda, 0x8d, 0xb0, 0xfd, 0x01, 0xbd, 0xbd, 0x87, 0xd4, 0x91, 0x78, 0x6c };

static const aes_kat_t aes_kat_vectors[] = {
	INIT_IV_AES_KAT_T(CMRT_AES_ENCRYPT, CMRT_AES_CBC, key0_128, input0, iv0_16, res_cbc_enc_128),
	INIT_IV_AES_KAT_T(CMRT_AES_DECRYPT, CMRT_AES_CBC, key0_128, input0, iv0_16, res_cbc_dec_128),
	INIT_IV_AES_KAT_T(CMRT_AES_ENCRYPT, CMRT_AES_CTR, key0_256, input0, iv0_16, res_ctr_enc_256),
	INIT_IV_AES_KAT_T(CMRT_AES_DECRYPT, CMRT_AES_CTR, key0_256, input1, iv0_16, res_ctr_dec_256),
	INIT_IV_AES_KAT_T(CMRT_AES_ENCRYPT, CMRT_AES_CFB, key0_256, input0, iv0_16, res_cfb_enc_256),
	INIT_IV_AES_KAT_T(CMRT_AES_DECRYPT, CMRT_AES_CFB, key0_256, input2, iv0_16, res_cfb_dec_256),
	INIT_AES_KAT_T(CMRT_AES_ENCRYPT, CMRT_AES_GCM, key0_256, input0, iv0_12, aad0, tag_gcm_enc_256, res_gcm_enc_256),
	INIT_AES_KAT_T(CMRT_AES_DECRYPT, CMRT_AES_GCM, key0_256, input3, iv0_12, aad0, tag_gcm_dec_256, res_gcm_dec_256)
};
#endif /* CONFIG_CMRT_FIPS_140_MODE */

#ifdef CONFIG_CMRT_ASIL_B_MODE
/* AES Core Vectors */
static const uint8_t key0[] = {
	0x2d, 0xc4, 0x77, 0xac, 0x10, 0xd6, 0xc0, 0x7b,
	0x3f, 0xe0, 0x08, 0xf6, 0x36, 0x03, 0x77, 0x33,
	0x37, 0x40, 0xd8, 0xa2, 0xfd, 0x15, 0xbb, 0xe6,
	0xda, 0x49, 0xed, 0x89, 0x03, 0xc6, 0x28, 0xba
};
static const uint8_t input0[] = {
	0x57, 0x8c, 0x86, 0x70, 0x0b, 0xf9, 0x62, 0x8f,
	0xc8, 0xd3, 0x8f, 0x97, 0x48, 0xf0, 0xcd, 0xeb,
	0xc8, 0x86, 0x0d, 0x93, 0x87, 0x55, 0x89, 0x97,
	0x03, 0x29, 0xdc, 0xcd, 0x4d, 0xa1, 0x00, 0xc3
};
static const uint8_t iv0[] = {
	0x19, 0x51, 0x28, 0x24, 0xb7, 0x57, 0x06, 0x63,
	0x1e, 0x83, 0x9d, 0x00
};
static const uint8_t aad0[] = {
	0x2b, 0x2b, 0xa8, 0x3f, 0xc8, 0x3a, 0x69, 0x5a,
	0x04, 0xfe
};
/* python: output0_aes_gcm, tag0_aes_gcm = AES.new(key0), AES.MODE_GCM, nonce=(iv0), mac_len=16).update(aad0).encrypt_and_digest(input0) */
static const uint8_t tag0_aes_gcm[] = {
	0xd2, 0x84, 0x51, 0xd8, 0xc4, 0x4e, 0x36, 0xfd,
	0x65, 0x76, 0x59, 0x7b, 0x23, 0x6c, 0xda, 0x80
};
static const uint8_t output0_aes_gcm[] = {
	0x7a, 0xec, 0x97, 0xeb, 0x39, 0x4e, 0x89, 0xdc,
	0xc5, 0xc5, 0x1c, 0x1b, 0xce, 0x31, 0x7e, 0xba,
	0xf8, 0x3e, 0x4d, 0x66, 0x22, 0xde, 0x0c, 0xc9,
	0xe2, 0x90, 0x12, 0x9d, 0x59, 0x34, 0xa4, 0xa7
};
/* python: output1_aes_ecb = AES.new(input0), AES.MODE_ECB).encrypt(key0) */
static const uint8_t output1_aes_ecb[] = {
	0x6d, 0x4d, 0x10, 0xaf, 0x5b, 0xda, 0x7b, 0x40,
	0xac, 0x38, 0x5e, 0x0b, 0x6f, 0x27, 0x07, 0x77,
	0xb1, 0xe5, 0xb1, 0x29, 0x43, 0x55, 0x0f, 0x82,
	0xc4, 0x80, 0xc1, 0xc3, 0xf4, 0xe9, 0xe0, 0x01
};

/* Populate AES KAT array */
static const aes_kat_t aes_kat_vectors[] = {
	INIT_AES_KAT_T(CMRT_AES_ENCRYPT, CMRT_AES_GCM, key0, input0, iv0, aad0, tag0_aes_gcm, output0_aes_gcm),
	INIT_AES_KAT_T(CMRT_AES_DECRYPT, CMRT_AES_GCM, key0, output0_aes_gcm, iv0, aad0, tag0_aes_gcm, input0),
	INIT_NOCHAINING_AES_KAT_T(CMRT_AES_ENCRYPT, CMRT_AES_ECB, input0, key0, output1_aes_ecb),
	INIT_NOCHAINING_AES_KAT_T(CMRT_AES_DECRYPT, CMRT_AES_ECB, input0, output1_aes_ecb, key0)
};
#endif  /* CONFIG_CMRT_ASIL_B_MODE */

#define AES_KAT_VECTORS_COUNT (sizeof(aes_kat_vectors) / sizeof(aes_kat_vectors[0]))

#define MAX_OUTPUT_BYTES (64 * 4)
#define MAX_TAG_BYTES (64)

static int init_aes(cmrt_aes_t aes, const aes_kat_t *kat)
{
	/* Initialize the aes core context */
	int rc = cmrt_aes_init(aes,
			       kat->operation,
			       kat->cipher,
			       kat->key,
			       kat->keylen,
			       kat->iv,
			       kat->ivlen,
			       kat->taglen);

	if ((rc == 0) && (kat->aad != NULL)) {
		rc = cmrt_aes_final_aad(aes, kat->aad, kat->aadlen);
	}

	return rc;
}

/* Perform aes operation
 * Returns true if a tag or output mismatch is detected else returns false */
static bool do_aes(cmrt_aes_t aes, const aes_kat_t *kat)
{
	uint8_t output[MAX_OUTPUT_BYTES];
	uint8_t tag[MAX_TAG_BYTES];
	int rc = 0;
	uint32_t size_w = (kat->inlen + AES_BLOCK_BYTES - 1u) / AES_BLOCK_BYTES;
	unsigned i = 0;

	if (size_w > 1) { /* run a single update for non-final */
		rc = cmrt_aes_update(aes,
				     kat->input,
				     (size_w - 1) * AES_BLOCK_BYTES,
				     output);
		if (rc != 0) {
			cmrt_eac_kat_error(CORE_ID_AES, -EXDEV, rc);
		}
		i = (size_w - 1) * AES_BLOCK_BYTES;
	}

	unsigned nin = kat->inlen - i;

	/* non-zero taglen implies authenticated encryption */
	if (kat->taglen != 0u) {
		size_t taglen = kat->taglen;
		if (CMRT_AES_ENCRYPT == kat->operation) {
			rc = cmrt_aes_ae_final(aes,
					       &kat->input[i],
					       nin,
					       &output[i],
					       tag,
					       &taglen);
			if (memcmp(kat->tag, tag, kat->taglen) != 0) {
				return true;
			}
		} else { /* decrypt */
			rc = cmrt_aes_ae_final(aes,
					       &kat->input[i],
					       nin,
					       &output[i],
					       (void *)kat->tag,
					       &taglen);
		}
		if (taglen != kat->taglen) {
			return true;
		}
	} else {
		rc = cmrt_aes_final(aes, &kat->input[i], nin, &output[i]);
	}

	if (rc != 0) {
		cmrt_eac_kat_error(CORE_ID_AES, -EXDEV, rc);
		return true;
	}

	return (memcmp(kat->output, output, kat->inlen) != 0);
}

static int aes_run_kat(cmrt_aes_t aes, const aes_kat_t *kat)
{
	/* Init the aes core context */
	int rc = init_aes(aes, kat);

	/* Check whether there is an error */
	if (rc == 0) {
		if (do_aes(aes, kat) != 0) {
			rc = -EFAULT;
		} else {
			cmrt_dd_flush((cmrt_dd_context_t *)aes);
		}
	}

	return rc;
}

void aes_open_kat(cmrt_dd_context_t *context)
{
	LOG_INF("Running AES KAT vectors");

	cmrt_aes_t aes = (cmrt_aes_t)context;

	/* Run the aes kats and expect output vector match */
	for (uint32_t i = 0; i < AES_KAT_VECTORS_COUNT; i++) {
		int rc = aes_run_kat(aes, &aes_kat_vectors[i]);
		if (rc != 0) {
			cmrt_eac_kat_error(CORE_ID_AES, -EXDEV, rc);
		}
	}
}

int aes_init_kat(const struct device *dev)
{
	ARG_UNUSED(dev);
#ifdef CONFIG_CMRT_FIPS_140_MODE
	/* Only run in mission and in fips mode. */
	uint32_t state = sys_read32((mm_reg_t)(CMRT_SIC_BASE + R_DEVICE_LIFECYCLE));
	uint32_t fips = sys_read32((mm_reg_t)(CMRT_SIC_BASE + R_FIPS_MODE));
	if (state != DLC_MISSION || (fips & FIPS_MODE_ENTER_FLAG) == 0) {
		return 0;
	}
#endif
#if defined(CONFIG_CMRT_FIPS_140_MODE) || (defined(CONFIG_CMRT_ASIL_B_MODE) && !defined(CONFIG_SUPERVISOR_MODE))
	cmrt_aes_t aes = cmrt_aes_open(CMRT_O_HWC_FORCE_KAT);
	if (!cmrt_dd_valid(aes)) {
		cmrt_eac_kat_error(CORE_ID_AES, -EXDEV, -ENODEV);
	}
	cmrt_aes_close(aes);
#endif
	return 0;
}
