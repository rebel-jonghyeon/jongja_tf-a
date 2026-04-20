/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample Container that verifies AES XTS operation
 *        by SIC message using Unified API.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "crisyscall-user.h"
#include <cri/cmrt.h>
#include "crilog-user.h"
#include <cri/cmrt/sic.h>
#include <cri/cmrt/aes.h>


static int do_aes_xts(uint32_t operation, uint32_t cipher,
		const uint8_t *key, const uint32_t keylen,
		const uint8_t *iv, const uint32_t ivlen,
		const uint8_t *msg, const uint32_t msglen,
		const uint8_t *expected, uint32_t expectedlen)
{
	uint8_t output[1024];

	c_log("do_aes_xts:\n");
	/* Open and initialize AES. */
	cri_aes_t aes = cri_aes_open(0);
	if (!cri_is_valid(aes)) {
		c_error("Cannot open AES!\n");
		return -ENOENT;
	}

	c_log("cri_aes_init:\n");
	int ret = cri_aes_init(aes, operation, cipher,
			       key, keylen,
			       iv, ivlen,
			       0);
	if (ret) {
		c_error("AES init failed %d\n", ret);
		goto out;
	}
	c_log("cri_aes_final: %d\n", msglen);
	ret = cri_aes_final(aes, msg, msglen, output);
	if (ret) {
		c_error("AES final failed %d\n", ret);
		goto out;
	}
	c_log("Core out:\n");
	hexdump(output, msglen);

	if (memcmp(output, expected, expectedlen)) {
		c_log("AES XTS %x Operation Failed\n", operation);
		c_log("AES XTS Expected Cipher HEX\n");
		hexdump((uint8_t *)expected, expectedlen);
		ret = 1;
	} else {
		c_log("****************************\n");
		c_log("* AES XTS Mode: %x Success *\n", operation);
		c_log("****************************\n");
	}

out:
	/* Close AES when done. */
	cri_aes_close(aes);
	return ret;
}



#define BUFSIZE 256

static int process_data(char *input_data, size_t input_size)
{
	(void)input_size;
	c_log("Note: input data not used\n");

	static const uint8_t key[] = {
		0xc8, 0x7b, 0x33, 0xc6, 0xb4, 0x41, 0xc0, 0x33,
		0xd2, 0x75, 0x0b, 0x9d, 0xaa, 0xcc, 0x1f, 0x7f,
		0x6f, 0x3a, 0x12, 0x37, 0x81, 0xd0, 0x3c, 0xb8,
		0xf7, 0xb9, 0xe7, 0xc6, 0xeb, 0x1c, 0xd9, 0x33,
	};
	static const uint8_t iv[] = {
		0x96, 0x85, 0x03, 0x7a, 0x42, 0x21, 0xa3, 0x74,
		0xe5, 0x23, 0x53, 0xfb, 0xe1, 0xf6, 0x33, 0x52,
	};
	static uint8_t pt[] = {
		0x89, 0x23, 0x30, 0x68, 0x80, 0x98, 0x6d, 0xd2,
		0x64, 0x69, 0xca, 0xcb, 0x98, 0x94, 0x94, 0x93,
		0xab, 0x17, 0xe7, 0x04, 0xfc, 0xaa, 0x81, 0xc3,
		0x1f, 0x10, 0x62, 0x4b, 0x1a, 0x43, 0xfc, 0x81,
	};
	static const uint8_t ct[] = {
		0xc4, 0x24, 0x2b, 0x19, 0xb2, 0xc2, 0x19, 0x76,
		0x09, 0x8f, 0xa5, 0x8e, 0xd4, 0xa3, 0x88, 0xd6,
		0x7c, 0xb1, 0x3c, 0x11, 0x44, 0xc7, 0x7a, 0xa2,
		0x6a, 0xbe, 0x55, 0xc7, 0x16, 0x43, 0xf9, 0xda,
	};

	int res = do_aes_xts(CRI_AES_ENCRYPT, CRI_AES_XTS,
				key, sizeof(key),
				iv,  AES_BLOCK_BYTES,
				pt, sizeof(pt), ct, sizeof(ct));

	res += do_aes_xts(CRI_AES_DECRYPT, CRI_AES_XTS,
				key, sizeof(key),
				iv,  AES_BLOCK_BYTES,
				ct, sizeof(ct), pt, sizeof(pt));
	return snprintf(input_data, BUFSIZE,
			(res ? "failed: res %d\n" : "OK\n"), res);
}

int main(void)
{
	c_log("Sample (aes xts) container starting...\n");

	const cri_sic_t sic = cri_sic_open(0, CRI_UNIT_CONTAINER_SAMPLE);
	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}

	char buf[BUFSIZE];
	uint32_t peer;
	size_t msglen = sizeof(buf);
	int ret = cri_sic_read(sic, buf, &msglen, &peer);
	if (ret) {
		c_log("cri_sic_read() returned %d\n", ret);
		goto out;
	}
	while (true) {
		const int fout = cri_wait(1, &sic, CRI_SECONDS(30));
		if ((fout > 0) && (fout & 1)) {
			ret = cri_sic_sync(sic);
			if (ret) {
				c_log("cri_sic_sync() returned %d\n", ret);
				break;
			}
			c_log("Received sic message from 0x%x\n", peer);
			msglen = process_data(buf, msglen);

			c_log("Sending sic message to 0x%x\n", peer);
			ret = cri_sic_write(sic, buf, msglen, peer);
			if (ret) {
				c_log("cri_sic_write() returned %d\n", ret);
				break;
			}
			msglen = sizeof(buf);
			ret = cri_sic_read(sic, buf, &msglen, &peer);
			if (ret) {
				c_log("cri_sic_read() returned %d\n", ret);
				break;
			}
		}
		else if (fout < 0) {
			c_log("cri_wait() returned %d\n", fout);
			break;
		}
		else {
			c_log("No sic messages in 30 seconds...\n");
		}
	}
out:
	cri_sic_close(sic);
	c_log("Sample container exiting.\n");
	return 1;
}
