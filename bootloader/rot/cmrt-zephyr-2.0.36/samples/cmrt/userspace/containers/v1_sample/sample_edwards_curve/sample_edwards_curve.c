/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file sample_edwards_curve.c
 * @brief Sample container to perform operations on Edwards curves.
 */

#include <stdalign.h>
#include <string.h>
#include <stdint.h>

#include "crisyscall-user.h"
#include <cri/cmrt/pke.h>
#include <cri/cmrt.h>
#include <cri/cmrt/sic.h>
#include "crisyscall-user.h"
#include "crilog-user.h"

static int test_rfc7748(int curveid, const void *key_priv, const void *key_priv2)
{
	/* 448 needs 56 bytes, 25519 needs 32 bytes */
	alignas(4) static uint8_t pubx[56];
	alignas(4) static uint8_t puby[56];
	alignas(4) static uint8_t shared1[56];
	alignas(4) static uint8_t shared2[56];

	cri_pke_t pke;
	cri_ecc_curve_t curve;
	int ret = -1;

	pke = cri_pke_open(0);
	if (!cri_is_valid(pke)) {
		c_error("Failed to open pke\n");
		return -1;
	}

	curve = cri_pke_get_curve(curveid);
	if (!curve) {
		c_error("Failed to obtain a curve\n");
		goto out;
	}

	ret = cri_pke_rfc7748_keygen(pke, curve, key_priv, pubx);
	if (ret) {
		c_error("cri_pke_rfc7748_keygen failed\n");
		goto out;
	}

	ret = cri_pke_sync(pke);
	if (ret) {
		c_error("Failed to sync keygen\n");
		goto out;
	}

	ret = cri_pke_rfc7748_keygen(pke, curve, key_priv2, puby);
	if (ret) {
		c_error("cri_pke_rfc7748_keygen failed\n");
		goto out;
	}

	ret = cri_pke_sync(pke);
	if (ret) {
		c_error("Failed to sync keygen\n");
		goto out;
	}

	ret = cri_pke_rfc7748(pke, curve, key_priv, puby, shared1);
	if (ret) {
		c_error("cri_pke_rfc7748 failed\n");
		goto out;
	}

	ret = cri_pke_sync(pke);
	if (ret) {
		c_error("Failed to sync rfc7748\n");
		goto out;
	}

	ret = cri_pke_rfc7748(pke, curve, key_priv2, pubx, shared2);
	if (ret) {
		c_error("cri_pke_rfc7748 failed\n");
		goto out;
	}

	ret = cri_pke_sync(pke);
	if (ret) {
		c_error("Failed to sync rfc7748\n");
		goto out;
	}

	if (memcmp(shared1, shared2, sizeof(shared1)) != 0) {
		ret = -1;
		c_error("ECDH shared key mismatch\n");
	}

out:
	cri_pke_close(pke);
	return ret;
}

static int test_eddsa(int curveid,
		size_t curvesize,
		const void *msg,
		const void *priv,
		const void *expected_pub)
{
	/* 448 needs 57 bytes, 25519 needs 32 bytes */
	alignas(4) static uint8_t pubx[57];
	alignas(4) static uint8_t sign_r[57];
	alignas(4) static uint8_t sign_s[57];
	alignas(4) static uint8_t comp_r[57];

	int ret = -1;
	cri_ecc_curve_t curve;
	cri_pke_t pke;

	pke = cri_pke_open(0);
	if (!cri_is_valid(pke)) {
		c_error("failed to open pke\n");
		return -1;
	}

	curve = cri_pke_get_curve(curveid);
	if (!curve) {
		c_error("Failed to obtain a curve\n");
		goto out;
	}

	ret = cri_pke_eddsa_keygen(pke, curve, priv, pubx);
	if (ret) {
		c_error("cri_pke_eddsa_keygen failed\n");
		goto out;
	}
	ret = cri_pke_sync(pke);
	if (ret) {
		c_error("keygen sync failed\n");
		goto out;
	}

	if (memcmp(pubx, expected_pub, curvesize) != 0) {
		c_error("wrong pubx\n");
		ret = -1;
		goto out;
	}

	ret = cri_pke_eddsa_sign(pke, curve, priv, msg, 0,
				     sign_r, sign_s);
	if (ret) {
		c_error("cri_pke_eddsa_sign failed\n");
		goto out;
	}
	ret = cri_pke_sync(pke);
	if (ret) {
		c_error("sign sync failed\n");
		goto out;
	}

	ret = cri_pke_eddsa_verify(pke, curve, pubx, msg, 0,
				   sign_r, sign_s, comp_r);
	if (ret) {
		c_error("cri_pke_eddsa_verify failed\n");
		goto out;
	}
	ret = cri_pke_sync(pke);
	if (ret) {
		c_error("verify sync failed\n");
	}


out:
	cri_pke_close(pke);
	return ret;
}

static int test_ed448(void)
{
	/* test vector from
	 * https://datatracker.ietf.org/doc/html/rfc8032#section-7.4
	 */
	alignas(4) static const uint8_t priv[57] = {
		0x6c, 0x82, 0xa5, 0x62, 0xcb, 0x80, 0x8d, 0x10,
		0xd6, 0x32, 0xbe, 0x89, 0xc8, 0x51, 0x3e, 0xbf,
		0x6c, 0x92, 0x9f, 0x34, 0xdd, 0xfa, 0x8c, 0x9f,
		0x63, 0xc9, 0x96, 0x0e, 0xf6, 0xe3, 0x48, 0xa3,
		0x52, 0x8c, 0x8a, 0x3f, 0xcc, 0x2f, 0x04, 0x4e,
		0x39, 0xa3, 0xfc, 0x5b, 0x94, 0x49, 0x2f, 0x8f,
		0x03, 0x2e, 0x75, 0x49, 0xa2, 0x00, 0x98, 0xf9,
		0x5b
	};
	alignas(4) static const uint8_t expected_pub[57] = {
		0x5f, 0xd7, 0x44, 0x9b, 0x59, 0xb4, 0x61, 0xfd,
		0x2c, 0xe7, 0x87, 0xec, 0x61, 0x6a, 0xd4, 0x6a,
		0x1d, 0xa1, 0x34, 0x24, 0x85, 0xa7, 0x0e, 0x1f,
		0x8a, 0x0e, 0xa7, 0x5d, 0x80, 0xe9, 0x67, 0x78,
		0xed, 0xf1, 0x24, 0x76, 0x9b, 0x46, 0xc7, 0x06,
		0x1b, 0xd6, 0x78, 0x3d, 0xf1, 0xe5, 0x0f, 0x6c,
		0xd1, 0xfa, 0x1a, 0xbe, 0xaf, 0xe8, 0x25, 0x61,
		0x80
	};
	/* test vector from
	 * https://datatracker.ietf.org/doc/html/rfc7748#section-6.2
	 */
	alignas(4) static const uint8_t key_priv[56] = {
		0x9a, 0x8f, 0x49, 0x25, 0xd1, 0x51, 0x9f,
		0x57, 0x75, 0xcf, 0x46, 0xb0, 0x4b, 0x58,
		0x00, 0xd4, 0xee, 0x9e, 0xe8, 0xba, 0xe8,
		0xbc, 0x55, 0x65, 0xd4, 0x98, 0xc2, 0x8d,
		0xd9, 0xc9, 0xba, 0xf5, 0x74, 0xa9, 0x41,
		0x97, 0x44, 0x89, 0x73, 0x91, 0x00, 0x63,
		0x82, 0xa6, 0xf1, 0x27, 0xab, 0x1d, 0x9a,
		0xc2, 0xd8, 0xc0, 0xa5, 0x98, 0x72, 0x6b,
	};
	alignas(4) static const uint8_t key_priv2[56] = {
		0x1c, 0x30, 0x6a, 0x7a, 0xc2, 0xa0, 0xe2,
		0xe0, 0x99, 0x0b, 0x29, 0x44, 0x70, 0xcb,
		0xa3, 0x39, 0xe6, 0x45, 0x37, 0x72, 0xb0,
		0x75, 0x81, 0x1d, 0x8f, 0xad, 0x0d, 0x1d,
		0x69, 0x27, 0xc1, 0x20, 0xbb, 0x5e, 0xe8,
		0x97, 0x2b, 0x0d, 0x3e, 0x21, 0x37, 0x4c,
		0x9c, 0x92, 0x1b, 0x09, 0xd1, 0xb0, 0x36,
		0x6f, 0x10, 0xb6, 0x51, 0x73, 0x99, 0x2d,
	};

	int ret = test_eddsa(CRI_ECC_CURVE_ED448, 57, "", priv, expected_pub);

	if (ret) {
		return ret;
	}

	return test_rfc7748(CRI_ECC_CURVE_448, key_priv, key_priv2);
}

static int test_ed25519(void)
{
	/* test vector from
	 * https://datatracker.ietf.org/doc/html/rfc8032#section-7.1
	 */
	alignas(4) static const uint8_t priv[32] = {
		0x9d, 0x61, 0xb1, 0x9d, 0xef, 0xfd, 0x5a, 0x60,
		0xba, 0x84, 0x4a, 0xf4, 0x92, 0xec, 0x2c, 0xc4,
		0x44, 0x49, 0xc5, 0x69, 0x7b, 0x32, 0x69, 0x19,
		0x70, 0x3b, 0xac, 0x03, 0x1c, 0xae, 0x7f, 0x60,
	};
	alignas(4) static const uint8_t expected_pub[32] = {
		0xd7, 0x5a, 0x98, 0x01, 0x82, 0xb1, 0x0a, 0xb7,
		0xd5, 0x4b, 0xfe, 0xd3, 0xc9, 0x64, 0x07, 0x3a,
		0x0e, 0xe1, 0x72, 0xf3, 0xda, 0xa6, 0x23, 0x25,
		0xaf, 0x02, 0x1a, 0x68, 0xf7, 0x07, 0x51, 0x1a,
	};
	/* test vector from
	 * https://datatracker.ietf.org/doc/html/rfc7748#section-6.1
	 */
	static const uint8_t key_priv[] = {
		0x77, 0x07, 0x6d, 0x0a, 0x73, 0x18, 0xa5, 0x7d,
		0x3c, 0x16, 0xc1, 0x72, 0x51, 0xb2, 0x66, 0x45,
		0xdf, 0x4c, 0x2f, 0x87, 0xeb, 0xc0, 0x99, 0x2a,
		0xb1, 0x77, 0xfb, 0xa5, 0x1d, 0xb9, 0x2c, 0x2a
	};
	static const uint8_t key_priv2[] = {
		0x5d, 0xab, 0x08, 0x7e, 0x62, 0x4a, 0x8a, 0x4b,
		0x79, 0xe1, 0x7f, 0x8b, 0x83, 0x80, 0x0e, 0xe6,
		0x6f, 0x3b, 0xb1, 0x29, 0x26, 0x18, 0xb6, 0xfd,
		0x1c, 0x2f, 0x8b, 0x27, 0xff, 0x88, 0xe0, 0xeb
	};

	int ret = test_eddsa(CRI_ECC_CURVE_ED25519, 32, "", priv, expected_pub);

	if (ret) {
		return ret;
	}
	return test_rfc7748(CRI_ECC_CURVE_25519, key_priv, key_priv2);
}

static size_t process_data(const uint8_t *input_data,
		size_t input_size,
		uint8_t *output_data)
{
	(void)input_data;
	(void)input_size;

	int ret = test_ed448();

	if (ret == 0) {
		ret = test_ed25519();
	}

	memcpy(output_data, &ret, 4);
	return 4;
}

enum {
	BUFSIZE = 256
};

int main(void)
{
	c_log("Sample edwards_curve container starting...\n");

	const cri_sic_t sic = cri_sic_open(CRI_O_SYNC, CRI_UNIT_CONTAINER_SAMPLE);

	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}

	alignas(4) char input[BUFSIZE] = { 0 };
	size_t inlen = sizeof(input);
	alignas(4) char output[BUFSIZE] = { 0 };
	uint32_t peer;

	while (cri_sic_read(sic, input, &inlen, &peer) == 0) {
		c_log("Received sic message from 0x%x\n", peer);

		size_t outlen = process_data((uint8_t *)input, inlen, (uint8_t *)output);

		c_log("Sending sic message to 0x%x", peer);

		int32_t ret = cri_sic_write(sic, output, outlen, peer);
		if (ret != 0) {
			c_log("cri_sic_write() returned %d\n", ret);
		} else {
			inlen = sizeof(input);
		}
	}

	cri_sic_close(sic);
	c_log("Sample container exiting.\n");
	return 0;
}
