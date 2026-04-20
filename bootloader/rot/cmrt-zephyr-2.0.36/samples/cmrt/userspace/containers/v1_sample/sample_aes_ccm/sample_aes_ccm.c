/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample Container that verifies AES CCM operation
 *        by SIC message using Unified API.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdalign.h>

#include "crisyscall-user.h"
#include "crilog-user.h"
#include <cri/cmrt.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/aes.h>


static int do_aes_ccm(uint32_t operation, uint32_t cipher,
		const uint8_t *key, uint32_t keylen,
		const uint8_t *iv, uint32_t ivlen,
		const uint8_t *aad, uint32_t aadlen,
		const uint8_t *pt, uint32_t ptlen,
		const uint8_t *ct, uint32_t ctlen,
		uint8_t *tag, uint32_t taglen)
{
	alignas(4) static uint32_t output[1024/4];
	alignas(4) static uint32_t b0[16/4];
	alignas(4) static uint32_t bn[32/4]; /* we know bn needs 32 bytes */
	alignas(4) static uint32_t tag2[16/4];

	uint32_t tag2len = taglen;
	uint32_t bnlen = 0;
	cri_aes_t aes;
	int ret;

	c_log("do_aes_ccm:\n");

	/* Prepare b0 and bn */
	ret = cri_aes_ccm_encode_nonce(b0,
				       sizeof(b0),
				       iv,
				       ivlen,
				       ptlen,
				       taglen,
				       1);

	c_log("b0 encode: %d\n", ret);
	if (ret < 0) {
		return ret;
	}

	ret = cri_aes_ccm_encode_aad(bn, sizeof(bn), aad, aadlen);
	c_log("bn encode: %d\n", ret);
	if (ret < 0) {
		return ret;
	}
	bnlen = ret;
	ret = 0;

	/* Open and initialize AES. */
	aes = cri_aes_open(0);
	if (!cri_is_valid(aes)) {
		c_error("Cannot open AES!\n");
		return -ENOENT;
	}

	c_log("cri_aes_init: %08x\n", (uint32_t)aes);
	ret = cri_aes_init(aes, operation, cipher,
			       key, keylen,
			       b0, sizeof(b0),
			       taglen);
	if (ret) {
		c_error("AES init failed %d\n", ret);
		goto out;
	}

	ret = cri_aes_final_aad(aes, bn, bnlen);
	if (ret) {
		c_error("AES AAD failed %d\n", ret);
		goto out;
	}

	c_log("cri_aes_aes_final\n");
	if (operation == CRI_AES_ENCRYPT) {
		ret = cri_aes_ae_final(aes, pt, ptlen, output, tag2, &tag2len);
		if (ret) {
			c_error("AES final enc failed %d\n", ret);
			goto out;
		}
		if (taglen != tag2len) {
			c_error("enc taglen mismatch %d %d\n", taglen, tag2len);
			goto out;
		}
		if (memcmp(tag2, tag, taglen) != 0) {
			c_error("enc tag mismatchd\n");
			goto out;
		}
	} else {
		ret = cri_aes_ae_final(aes, ct, ctlen, output, tag, &tag2len);
		if (ret) {
			c_error("AES final dec failed %d\n", ret);
			goto out;
		}
		if (memcmp(output, pt, ptlen) != 0) {
			c_error("dec tag mismatch\n");
			goto out;
		}
	}
	c_log("****************************\n");
	c_log("* AES CCM Mode: %x Success *\n", operation);
	c_log("****************************\n");

out:
	/* Close AES when done. */
	c_log("cri_aes_close: %08x\n", (uint32_t)aes);
	cri_aes_close(aes);
	return ret;
}


#define BUFSIZE 256

static int process_data(char *input_data, size_t input_size)
{
	(void)input_size;
	c_log("Note: input data not used\n");

	alignas(4) static uint8_t key[] = {
		0xd0, 0xf4, 0xb2, 0x45, 0x9b, 0x6e, 0x02, 0xef,
		0xa9, 0x1a, 0x77, 0x7b, 0x45, 0x3f, 0xd3, 0x4e,
	};
	alignas(4) static uint8_t iv[] = {
		0x14, 0xbd, 0xac, 0x62, 0xf4, 0xe6, 0xdc, 0x48,
		0xc4, 0x73, 0x0b, 0xb4
	};
	alignas(4) static uint8_t pt[] = {
		0x5d, 0x91, 0x5f, 0x17, 0x6c, 0x55, 0x8c, 0xeb,
		0xcd, 0x0c, 0xf5, 0x74, 0x46, 0xa5, 0xc4, 0x85,
	};
	alignas(4) static uint8_t ct[] = {
		0x9a, 0xf1, 0xc8, 0x49, 0x14, 0xd4, 0x86, 0x4d,
		0xf0, 0x37, 0x64, 0x2b, 0xf2, 0x52, 0x05, 0x5c,
	};
	alignas(4) static uint8_t aad[] = {
		0x7b, 0x18, 0x0c, 0x98, 0xc5, 0x38, 0x93, 0x34,
		0x01, 0x23, 0x49, 0xa9, 0xd9, 0x44, 0x51, 0x8a,
	};
	alignas(4) static uint8_t tag[] = {
		0xd1, 0xaf, 0x00, 0x05, 0xca, 0x44, 0x12, 0xda,
		0x27, 0xe9, 0x8b, 0x75, 0x39, 0x05, 0x61, 0x9c,
	};

	int res = do_aes_ccm(CRI_AES_ENCRYPT, CRI_AES_CCM,
				key, sizeof(key),
				iv,  sizeof(iv),
				aad, sizeof(aad),
				pt, sizeof(pt),
				ct, sizeof(ct),
				tag, sizeof(tag));

	if (res == 0) {
		res = do_aes_ccm(CRI_AES_DECRYPT, CRI_AES_CCM,
					key, sizeof(key),
					iv,  sizeof(iv),
					aad, sizeof(aad),
					pt, sizeof(pt),
					ct, sizeof(ct),
					tag, sizeof(tag));
	}

	return snprintf(input_data, BUFSIZE,
			(res ? "failed: res %d\n" : "OK\n"), res);
}

int main(void)
{
	c_log("Sample (aes ccm) container starting...\n");

	const cri_sic_t sic = cri_sic_open(0, CRI_UNIT_CONTAINER_SAMPLE);
	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}

	static char buf[BUFSIZE];
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
