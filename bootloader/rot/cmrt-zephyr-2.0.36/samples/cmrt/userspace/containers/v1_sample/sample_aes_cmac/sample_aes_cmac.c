/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to generate AES-CMAC of the data received
 *        by SIC message.
 */


#include <errno.h>
#include <stdalign.h>
#include <stdio.h>
#include "crilog-user.h"
#include "crisyscall-user.h"
#include <cri/cmrt.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/aes.h>

#define BUFSIZE 256


static int32_t do_aes_cmac(cri_aes_operation_t operation, cri_aes_mode_t cipher, const uint8_t *input,
			    size_t inlen,  uint8_t *output, size_t outlen,
			    const uint8_t *key,
			    size_t keylen)
{
	cri_aes_t aes;
	int ret  = 0;

	/* Open and initialize AES. */
	aes = cri_aes_open(0);
	if (!cri_is_valid(aes)) {
		c_error("Cannot open AES!\n");
		return -ENOENT;
	}

	c_log("cri_aes_init: %08x\n", (uint32_t)aes);
	ret = cri_aes_init(aes, operation, cipher,
			       key, keylen, NULL, 0, 16);
	if (ret != 0) {
		c_error("AES init failed %d\n", ret);
		goto out;
	}
	for (; inlen > AES_BLOCK_BYTES; inlen -= AES_BLOCK_BYTES) {
		c_log("multiple updates(%u)...\n", inlen);
		ret = cri_aes_update_aad(aes, input, AES_BLOCK_BYTES);
		input += AES_BLOCK_BYTES;
		if (ret != 0)
			goto out;
	}
	if (inlen) {
		c_log("last update(%u)...\n", inlen);
		ret = cri_aes_final_aad(aes, input, inlen);
		c_log("aad = %d\n", ret);
		if (ret != 0)
			goto out;
	}
	if (ret >= 0) {
		c_log("cri_aes_ae_final(0)...\n");
		ret = cri_aes_ae_final(aes, NULL, 0, NULL, output, &outlen);
		c_log("final(%u) = %d, outlen = %u\n", inlen, ret, outlen);
	}

	if (ret) {
		c_error("AES final failed %d\n", ret);
		goto out;
	}

	ret = outlen;

	c_log("****************************\n");
	c_log("* AES CMAC Success *\n");
	c_log("****************************\n");

	hexdump(output, outlen);

out:
	/* Close AES when done. */
	c_log("cri_aes_close: %08x\n", (uint32_t)aes);
	cri_aes_close(aes);
	return ret;
}

static size_t process_data(const uint8_t *input_data,
			   size_t input_size,  uint8_t *output_data, size_t output_len)
{
	int res = 0;
	alignas(4)  static  uint8_t mysecretkey[] = {
		0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
	};

	res = do_aes_cmac(CRI_AES_ENCRYPT, CRI_AES_CMAC, input_data,  input_size, output_data, output_len, mysecretkey, sizeof(mysecretkey));

	return res;
}

int main(void)
{
	c_log("Sample (AES-CMAC) unified container starting...\n");

	const cri_sic_t sic = cri_sic_open(CRI_O_SYNC, CRI_UNIT_CONTAINER_SAMPLE);

	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}

	char buf[BUFSIZE];
	char mac[32];
	size_t msglen = sizeof(buf);
	size_t taglen = 16;
	uint32_t peer;
	int  ret = 0;

	while (cri_sic_read(sic, buf, &msglen, &peer) == 0) {
		c_log("Received sic message from 0x%x\n", peer);

		/* AES-CMAC using unified apis.*/

		taglen = process_data((uint8_t *)buf, msglen, (uint8_t *)mac, taglen);
		c_log("Sending sic message to 0x%x\n", peer);
		ret = cri_sic_write(sic, mac, taglen, peer);
		if (ret) {
			c_log("cri_sic_write() returned %d\n", ret);
			break;
		}
		else {
			msglen = sizeof(buf);
		}
	}
	cri_sic_close(sic);
	c_log("Sample container exiting.\n");
	return 0;

}
