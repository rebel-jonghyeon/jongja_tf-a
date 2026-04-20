#include <stdalign.h>
#include <drivers/cmrt/cmrt.h>
#include <logging/log.h>

#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/aes.h>

LOG_MODULE_DECLARE(test_crypto, CONFIG_CMRT_LOG_LEVEL);

#define TEST_FAIL (0xff)
static int test_hc_sha384(void)
{
	alignas(4) static const uint8_t hc_input[] = {
		0x37, 0x40, 0xd8, 0xa2, 0xfd, 0x15, 0xbb, 0xe6,
		0xda, 0x49, 0xed, 0x89, 0x03, 0xc6, 0x28, 0xba,
		0x57, 0x8c, 0x86, 0x70, 0x0b, 0xf9, 0x62, 0x8f,
		0xc8, 0xd3, 0x8f, 0x97, 0x48, 0xf0, 0xcd, 0xeb
	};
	static const uint8_t expected_hc_sha384_output[] = {
		0x9c, 0x71, 0x28, 0xa6, 0xa9, 0x06, 0xaa, 0xee,
		0x5f, 0x08, 0x1e, 0xb3, 0xd0, 0x3c, 0xbd, 0x37,
		0xa3, 0x09, 0x74, 0xa3, 0xf3, 0x5c, 0xea, 0x3d,
		0x5c, 0xca, 0x67, 0xe3, 0x46, 0xcb, 0xea, 0x43,
		0xa6, 0xbf, 0x9c, 0xe4, 0xf7, 0x46, 0xbb, 0x72,
		0x00, 0xdb, 0x24, 0xd1, 0x4c, 0xe6, 0xdf, 0xe4
	};
	alignas(4) uint8_t hc_output[64] = { 0, };
	int output_len = SHA384_BYTES;
	int res = 0;

	cmrt_hc_t hc = cmrt_hc_open(NULL, CMRT_O_SYNC);

	if (!cmrt_is_valid(hc)) {
		LOG_INF("cmrt_hc_open fail");
		return -ENODEV;
	}
	res = cmrt_hc_init(hc, HC_HASH_ALGO_SHA_384, NULL, 0);

	if (res != 0) {
		LOG_INF("cmrt_hc_init failed, %d", res);
		cmrt_hc_close(hc);
		return res;
	}

	res = cmrt_hc_final(hc, hc_input, sizeof(hc_input), hc_output, &output_len);
	if (res != 0) {
		LOG_INF("cmrt_hc_final failed, %d", res);
		cmrt_hc_close(hc);
		return res;
	}

	if (memcmp(hc_output, expected_hc_sha384_output, SHA384_BYTES) == 0) {
		LOG_INF("hc sha384 test passed");
	} else {
		LOG_INF("hc sha384 test failed");
		res = TEST_FAIL;
	}

	cmrt_hc_close(hc);

	return res;
}

#define P384_KEY_LEN	(48)
static int test_ecdsa_p384(void)
{
	cmrt_ecc_curve_t curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P384);
	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);

	if (!cmrt_is_valid(pke)) {
		LOG_INF("cmrt_pke_open fail");
		return -ENODEV;
	}

	int res = 0;
	uint8_t private_key[P384_KEY_LEN] = { 0, };

	res = cmrt_pke_ecc_private_keygen(pke, curve, private_key);
	if (res != 0) {
		LOG_INF("cmrt_pke_ecc_private_keygen failed, %d", res);
		cmrt_pke_close(pke);
		return res;
	}

	uint8_t public_key_x[P384_KEY_LEN] = { 0, };
	uint8_t public_key_y[P384_KEY_LEN] = { 0, };

	res = cmrt_pke_ecc_xy_keygen(pke, curve, private_key, public_key_x, public_key_y);
	if (res != 0) {
		LOG_INF("cmrt_pke_ecc_xy_keygen failed, %d", res);
		cmrt_pke_close(pke);
		return res;
	}

	alignas(4) static const uint8_t hc_input[] = {
		0xaa, 0x93, 0x9f, 0x6d, 0xfd, 0x15, 0xa1, 0xe6,
		0x11, 0xbc, 0xa0, 0xcc, 0x03, 0x4c, 0x28, 0x8a,
		0x57, 0xf1, 0x86, 0xef, 0x4a, 0x74, 0x92, 0x53,
		0xc8, 0xd3, 0x7f, 0x97, 0x48, 0xf0, 0x13, 0x23
	};
	alignas(4) uint8_t hc_output[64] = { 0, };
	int output_len = SHA384_BYTES;

	cmrt_hc_t hc = cmrt_hc_open(NULL, CMRT_O_SYNC);

	if (!cmrt_is_valid(hc)) {
		LOG_INF("cmrt_hc_open fail");
		return -ENODEV;
	}
	res = cmrt_hc_init(hc, HC_HASH_ALGO_SHA_384, NULL, 0);

	if (res != 0) {
		LOG_INF("cmrt_hc_init failed, %d", res);
		cmrt_hc_close(hc);
		cmrt_pke_close(pke);
		return res;
	}

	res = cmrt_hc_final(hc, hc_input, sizeof(hc_input), hc_output, &output_len);
	if (res != 0) {
		LOG_INF("cmrt_hc_final failed, %d", res);
		cmrt_hc_close(hc);
		cmrt_pke_close(pke);
		return res;
	}

	cmrt_hc_close(hc);

	uint8_t signature_r[P384_KEY_LEN] = { 0, };
	uint8_t signature_s[P384_KEY_LEN] = { 0, };

	res = cmrt_pke_ecdsa_sign_hash(pke, curve, private_key, hc_output, output_len,
								   signature_r, signature_s);
	if (res != 0) {
		LOG_INF("cmrt_pke_ecdsa_sign_hash failed, %d", res);
		cmrt_pke_close(pke);
		return res;
	}

	res = cmrt_pke_ecdsa_verify_hash(pke, curve, public_key_x, public_key_y, hc_output,
									 output_len, signature_r, signature_s, NULL);
	if (res != 0) {
		LOG_INF("cmrt_pke_ecdsa_verify_hash failed, %d", res);
		res = TEST_FAIL;
	} else {
		LOG_INF("cmrt_pke_ecdsa_verify_hash passed");
	}

	cmrt_pke_close(pke);

	return res;
}

static int test_ecdh_p384(void)
{
	cmrt_ecc_curve_t curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P384);
	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);

	if (!cmrt_is_valid(pke)) {
		LOG_INF("cmrt_pke_open fail");
		return -ENODEV;
	}

	int res = 0;
	uint8_t private_key_a[P384_KEY_LEN] = { 0, };
	uint8_t private_key_b[P384_KEY_LEN] = { 0, };

	res = cmrt_pke_ecc_private_keygen(pke, curve, private_key_a);
	if (res != 0) {
		LOG_INF("cmrt_pke_ecc_private_keygen for A failed, %d", res);
		cmrt_pke_close(pke);
		return res;
	}

	res = cmrt_pke_ecc_private_keygen(pke, curve, private_key_b);
	if (res != 0) {
		LOG_INF("cmrt_pke_ecc_private_keygen for B failed, %d", res);
		cmrt_pke_close(pke);
		return res;
	}

	uint8_t public_key_x_a[P384_KEY_LEN] = { 0, };
	uint8_t public_key_x_b[P384_KEY_LEN] = { 0, };

	res = cmrt_pke_ecdh_keygen(pke, curve, private_key_a, public_key_x_a);
	if (res != 0) {
		LOG_INF("cmrt_pke_ecdh_keygen for A failed, %d", res);
		cmrt_pke_close(pke);
		return res;
	}

	res = cmrt_pke_ecdh_keygen(pke, curve, private_key_b, public_key_x_b);
	if (res != 0) {
		LOG_INF("cmrt_pke_ecdh_keygen for B failed, %d", res);
		cmrt_pke_close(pke);
		return res;
	}

	uint8_t shared_secret_a[P384_KEY_LEN] = { 0, };
	uint8_t shared_secret_b[P384_KEY_LEN] = { 0, };

	res = cmrt_pke_ecdh(pke, curve, private_key_a, public_key_x_b, shared_secret_a);
	if (res != 0) {
		LOG_INF("cmrt_pke_ecdh for A failed, %d", res);
		cmrt_pke_close(pke);
		return res;
	}
	res = cmrt_pke_ecdh(pke, curve, private_key_b, public_key_x_a, shared_secret_b);
	if (res != 0) {
		LOG_INF("cmrt_pke_ecdh for B failed, %d", res);
		cmrt_pke_close(pke);
		return res;
	}

	if (memcmp(shared_secret_a, shared_secret_b, P384_KEY_LEN) == 0) {
		LOG_INF("ecdh-p384 key exchagne passed");
	} else {
		LOG_INF("ecdh-p384 key exchagne failed");
		res = TEST_FAIL;
	}

	cmrt_pke_close(pke);

	return res;
}

#define MAX_OUTPUT_BYTES	(64 * 4)
#define MAX_TAG_BYTES		(64)
#define TAG_SIZE_16B		(16)
static bool do_aes(cmrt_aes_t aes, size_t inlen, const uint8_t *input,
				   size_t *taglen, uint8_t *tag, cmrt_aes_operation_t operation,
				   uint8_t *output)
{
	int res = 0;
	uint32_t size_w = (inlen + AES_BLOCK_BYTES - 1u) / AES_BLOCK_BYTES;
	uint32_t i = 0;

	if (size_w > 1) { /* run a single update for non-final */
		res = cmrt_aes_update(aes, input, (size_w - 1) * AES_BLOCK_BYTES, output);
	    if (res != 0) {
			return -EXDEV;
		}
		i = (size_w - 1) * AES_BLOCK_BYTES;
	}

	uint32_t nin = inlen - i;

	/* non-zero taglen implies authenticated encryption */
	if (taglen != 0u) {
		if (operation == CMRT_AES_ENCRYPT) {
			res = cmrt_aes_ae_final(aes, &input[i], nin, &output[i], tag, taglen);
		} else { /* decrypt */
			res = cmrt_aes_ae_final(aes, &input[i], nin, &output[i], tag, taglen);
		}
	} else {
		res = cmrt_aes_final(aes, &input[i], nin, &output[i]);
	}

	return res;
}

static int test_aes_256_gcm(void)
{
	const uint8_t key[] = {
		0x14, 0x3a, 0xe8, 0xed, 0x65, 0x55,
		0xab, 0xa9, 0x61, 0x10, 0xab, 0x58,
		0x89, 0x3a, 0x8a, 0xe1, 0x6c, 0x00,
		0x2b, 0x68, 0x24, 0x83, 0xe0, 0xca,
		0xbc, 0xc7, 0x31, 0xc2, 0x53, 0xbe,
		0x56, 0x74
	};
	const uint8_t input[] = {
		0xe2, 0x34, 0xcd, 0xca, 0x26, 0x06,
		0xb8, 0x1f, 0x29, 0x40, 0x8d, 0x5f,
		0x6d, 0xa2, 0x12, 0x06
	};
	const uint8_t iv[] = {
		0x13, 0x23, 0x7c, 0x49, 0x07, 0x4a,
		0x3d, 0xa0, 0x78, 0xdc, 0x1d, 0x82,
		0x8b, 0xb7, 0x8c, 0x6f
	};
	const uint8_t aad[] = {
		0x71, 0xb5, 0xc0, 0x8a, 0x19, 0x93,
		0xe1, 0x36, 0x2e, 0x4d, 0x0c, 0xe9,
		0xb2, 0x2b, 0x78, 0xd5
	};
	uint8_t tag_gcm[TAG_SIZE_16B] = { 0, };
	uint8_t enc_output[sizeof(input)] = { 0, };
	uint8_t dec_output[sizeof(input)] = { 0, };

	int res = 0;
	cmrt_aes_t aes = cmrt_aes_open(CMRT_O_SYNC);

	if (!cmrt_is_valid(aes)) {
		LOG_INF("cmrt_aes_open failed");
		return -ENODEV;
	}
	size_t tag_len = sizeof(tag_gcm);

	res = cmrt_aes_init(aes, CMRT_AES_ENCRYPT, CMRT_AES_GCM, key, sizeof(key),
						iv, sizeof(iv), tag_len);
	if (res != 0) {
		LOG_INF("cmrt_aes_init failed, %d", res);
		cmrt_aes_close(aes);
		return res;
	}

	res = cmrt_aes_final_aad(aes, aad, sizeof(aad));
	if (res != 0) {
		LOG_INF("cmrt_aes_final_aad failed, %d", res);
		cmrt_aes_close(aes);
		return res;
	}

	res = do_aes(aes, sizeof(input), input, &tag_len, tag_gcm, CMRT_AES_ENCRYPT, enc_output);
	if (res != 0) {
		LOG_INF("aes-gcm encryption failed");
	} else {
		LOG_INF("aes-gcm encryption done");
	}
	cmrt_aes_close(aes);

	aes = cmrt_aes_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(aes)) {
		LOG_INF("cmrt_aes_open failed");
		return -ENODEV;
	}

	res = cmrt_aes_init(aes, CMRT_AES_DECRYPT, CMRT_AES_GCM, key, sizeof(key),
						iv, sizeof(iv), tag_len);
	if (res != 0) {
		LOG_INF("cmrt_aes_init failed, %d", res);
		cmrt_aes_close(aes);
		return res;
	}

	res = cmrt_aes_final_aad(aes, aad, sizeof(aad));
	if (res != 0) {
		LOG_INF("cmrt_aes_final_aad failed, %d", res);
		cmrt_aes_close(aes);
		return res;
	}

	res = do_aes(aes, sizeof(enc_output), enc_output, &tag_len, tag_gcm,
				 CMRT_AES_DECRYPT, dec_output);
	if (res != 0) {
		LOG_INF("aes-gcm decryption failed");
	} else {
		LOG_INF("aes-gcm decryption done");
	}

	if (memcmp(input, dec_output, sizeof(input)) == 0) {
		LOG_INF("aes-gcm encryption/decryption passed");
	} else {
		LOG_INF("aes-gcm encryption/decryption failed");
		res = TEST_FAIL;
	}

	cmrt_aes_close(aes);

	return res;
}

static int test_aes_256_xts(void)
{
	static const uint8_t key0_key1_512[] = {
		0x14, 0x3a, 0xe8, 0xed, 0x65, 0x55,
		0xab, 0xa9, 0x61, 0x10, 0xab, 0x58,
		0x89, 0x3a, 0x8a, 0xe1, 0x6c, 0x00,
		0x2b, 0x68, 0x24, 0x83, 0xe0, 0xca,
		0xbc, 0xc7, 0x31, 0xc2, 0x53, 0xbe,
		0x56, 0x74,
		0xc7, 0xbc, 0x13, 0xed, 0xae, 0x5f,
		0xf1, 0xaa, 0x54, 0x47, 0x98, 0x00,
		0x69, 0x8a, 0x17, 0x5e, 0xf1, 0x10,
		0x14, 0x7c, 0xe2, 0x83, 0xe0, 0xa2,
		0x97, 0xc7, 0x9e, 0x4c, 0x51, 0x1e,
		0x50, 0x9a,
	};
	const uint8_t input[] = {
		0xe2, 0x34, 0xcd, 0xca, 0x26, 0x06,
		0xb8, 0x1f, 0x29, 0x40, 0x8d, 0x5f,
		0x6d, 0xa2, 0x12, 0x06
	};
	uint8_t enc_output[sizeof(input)] = { 0, };
	uint8_t dec_output[sizeof(input)] = { 0, };
	const uint8_t iv[] = {
		0x13, 0x23, 0x7c, 0x49, 0x07, 0x4a,
		0x3d, 0xa0, 0x78, 0xdc, 0x1d, 0x82,
		0x8b, 0xb7, 0x8c, 0x6f
	};
	int res = 0;
	cmrt_aes_t aes = cmrt_aes_open(CMRT_O_SYNC);

	if (!cmrt_is_valid(aes)) {
		LOG_INF("cmrt_aes_open fail");
		return -ENODEV;
	}

	res = cmrt_aes_init(aes, CMRT_AES_ENCRYPT, CMRT_AES_XTS, key0_key1_512, sizeof(key0_key1_512),
						iv, sizeof(iv), 0);
	if (res != 0) {
		LOG_INF("cmrt_aes_init failed, %d", res);
		cmrt_aes_close(aes);
		return res;
	}

	res = do_aes(aes, sizeof(input), input, NULL, NULL, CMRT_AES_ENCRYPT, enc_output);
	if (res != 0) {
		LOG_INF("aes-xts encryption failed");
	} else {
		LOG_INF("aes-xts encryption done");
	}

	cmrt_aes_close(aes);

	aes = cmrt_aes_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(aes)) {
		LOG_INF("cmrt_aes_open fail");
		return -ENODEV;
	}
	res = cmrt_aes_init(aes, CMRT_AES_DECRYPT, CMRT_AES_XTS, key0_key1_512, sizeof(key0_key1_512),
						iv, sizeof(iv), 0);
	if (res != 0) {
		LOG_INF("cmrt_aes_init failed, %d", res);
		cmrt_aes_close(aes);
		return res;
	}

	res = do_aes(aes, sizeof(enc_output), enc_output, NULL, NULL, CMRT_AES_DECRYPT, dec_output);
	if (res != 0) {
		LOG_INF("aes-xts decryption failed");
	} else {
		LOG_INF("aes-xts decryption done");
	}

	if (memcmp(input, dec_output, sizeof(input)) == 0) {
		LOG_INF("aes-xts encryption/decryption passed");
	} else {
		LOG_INF("aes-xts encryption/decryption failed");
		res = TEST_FAIL;
	}

	cmrt_aes_close(aes);

	return res;
}

void test_crypto_hc_ec(void *p1, void *p2, void *p3)
{
	test_hc_sha384();
	test_ecdsa_p384();
	test_ecdh_p384();
}

void test_crypto_aes(void *p1, void *p2, void *p3)
{
	test_aes_256_gcm();
	test_aes_256_xts();
}
