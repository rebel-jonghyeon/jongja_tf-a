/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to perform HMAC SHA256 hashing
 * operations on the data received by SIC message.
 */

#include <cri/cmrt.h>
#include "crilog-user.h"
#include <stdalign.h>
#include "crisyscall-user.h"
#include <cri/cmrt/sic.h>
#include <cri/cmrt/hc.h>

enum {
	HASH_SIZE = 32,
	MAX_LENGTH = 64,
	BUFSIZE = 256
};

static int32_t hash_data(const cri_hc_t hc,
			 const uint8_t *input,
			 size_t inlen,
			 const uint8_t *key,
			 size_t keylen,
			 uint8_t *output,
			 size_t *outlen)
{
	int32_t ret = -1;
	if (cri_hc_init(hc, CRI_HASH_SHA256, key, keylen) != 0) {
		c_log("Cannot init hash\n");
	} else {
		if (cri_hc_final(hc,
				 input,
				 inlen,
				 output,
				 outlen) != 0) {
			c_log("Cannot final hash\n");
		} else {
			ret = 0;
		}
	}
	return ret;
}

static int32_t hash_message(const uint8_t *input,
			    size_t inlen,
			    const uint8_t *key,
			    size_t keylen,
			    uint8_t *output,
			    size_t *outlen)
{
	int32_t ret = -1;
	cri_hc_t hc = cri_hc_open(0);

	if (!cri_is_valid(hc)) {
		c_log("Cannot open hash\n");
		return ret;
	}

	/*
	 * RFC 2104: For SHA256 algorithm, if key length is larger
	 * than 512 bits, hash the key first, then use the
	 * digest as new key.
	 */

	if (keylen > (size_t)MAX_LENGTH) {
		static uint8_t alignas(4) hkey[MAX_LENGTH];
		size_t hkey_len = sizeof(hkey);

		ret = hash_data(hc, key, keylen, NULL, 0, hkey, &hkey_len);
		if (ret != 0) {
			c_log("Cannot hash the key\n");
			cri_hc_close(hc);
			return ret;
		}

		key = hkey;
		keylen = hkey_len;
	}
	ret = hash_data(hc, input, inlen, key, keylen, output, outlen);

	cri_hc_close(hc);

	return ret;
}

static size_t process_data(const uint8_t *input_data,
			   size_t input_size,
			   uint8_t *output_data,
			   size_t output_len)
{
	static alignas(4) const char long_secretkey[] =
		"secret key longer than 64 bytes will be "
		"hashed to make it fixed length of 64 bytes";

	if (hash_message(input_data,
			 input_size,
			 (const uint8_t *)long_secretkey,
			 sizeof(long_secretkey) - 1u,
			 output_data,
			 &output_len) < 0) {
		output_len = 0;
	}

	return output_len;
}

int main(void)
{
	c_log("Sample HMAC SHA256 hashing container starting...\n");

	const cri_sic_t sic = cri_sic_open(CRI_O_SYNC, CRI_UNIT_CONTAINER_SAMPLE);

	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}

	alignas(4) char input[BUFSIZE] = { 0 };
	size_t inlen = sizeof(input);
	uint32_t peer;

	while (cri_sic_read(sic, input, &inlen, &peer) == 0) {
		c_log("Received sic message from 0x%x\n", peer);
		alignas(4) char output[HASH_SIZE] = { 0 };

		size_t outlen = process_data((uint8_t *)input,
					     inlen,
					     (uint8_t *)output,
					     sizeof(output));

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
