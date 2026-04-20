/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample Container that verifies ECIES operation
 *        by SIC message using Unified API.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <cri/cmrt.h>
#include "crilog-user.h"
#include "crisyscall-user.h"
#include <cri/cmrt/sic.h>
#include <cri/cmrt/ecies.h>

#define BUFSIZE	1024
#define MAX_TEXT_SIZE 100
#define AES_BLOCK_BYTES 16
#define MAX_HASH_SIZE 64
#define MAX_KEY_SIZE 68

typedef struct {
	uint32_t flags;
	size_t curvelen;
	size_t hashlen;
	cri_ecies_mode_t mode;
	cri_ecies_operation_t operation;
	const void *peerpriv;
	const void *peerpubx;
	void *pubkey;
	const void *sharedinfo;
	size_t sharedinfolen;
	void *tag;
} ecies_context_t;

static uint32_t encrypted_tag[MAX_HASH_SIZE/4];
static uint32_t decrypted_tag[MAX_HASH_SIZE/4];
static uint32_t pub_key[MAX_KEY_SIZE/4];
static uint32_t pub_key_dec[MAX_KEY_SIZE/4];

static int do_ecies(const ecies_context_t *context, const void *msg, size_t msglen,\
		void *result, size_t *presultlen)
{
	int rc = 0;
	uint8_t *output = result;

	cri_ecies_t ecies = cri_ecies_open(context->flags);
	if (!cri_is_valid(ecies)) {
		c_log("Cannot open ECIES\n");
		rc = -EBUSY;
		goto out;
	}
	rc = cri_ecies_init(ecies, context->mode, context->operation, context->peerpriv,
				context->curvelen, context->peerpubx, context->curvelen, context->pubkey,
				context->curvelen);
	if (rc) {
		c_log("cri_ecies_init failed %d\n", rc);
		goto out;
	}

	size_t len = msglen;
	const void *input = msg;
	for (; len > AES_BLOCK_BYTES; len -= AES_BLOCK_BYTES) {
		rc = cri_ecies_update(ecies, input, AES_BLOCK_BYTES, output);
		if (rc) {
			c_log("cri_ecies_update: %d\n", rc);
			goto out;
		}
		input += AES_BLOCK_BYTES;
		output += AES_BLOCK_BYTES;
	}
	uint8_t lastblock[AES_BLOCK_BYTES] = { 0 };
	if (context->operation == CRI_ECIES_ENCRYPT) {
		len = AES_BLOCK_BYTES;
	}
	memcpy(lastblock, input, len);
	rc = cri_ecies_final(ecies, lastblock, len, context->sharedinfo, context->sharedinfolen,
				 output, context->tag, context->hashlen);
	if (rc) {
		c_log("cri_ecies_final failed %d\n", rc);
		goto out;
	}
	*presultlen = (msglen + AES_BLOCK_BYTES - 1) & -AES_BLOCK_BYTES;

out:
	/* Close ECIES when done. */
	cri_ecies_close(ecies);
	return rc;
}

static int process_data(char *input_data, size_t input_size)
{
	(void)input_size;
	c_log("Note: input data not used\n");
	char ct[MAX_TEXT_SIZE];
	char pt[96] = "This is a plain text that needs to be at least one full and one partial 256b block size.";
	size_t ct_length = 0;
	size_t pt_length = 0;
	static const uint8_t priv[68] = {
		0x00, 0x9a, 0x90, 0x28, 0x8b, 0xb6, 0x1d, 0xfd,
		0x1d, 0x02, 0x75, 0x18, 0xb4, 0xcd, 0xc6, 0xac,
		0xb8, 0xa6, 0x32, 0xa3, 0x21, 0xc9, 0xe7, 0xa9,
		0x5c, 0xba, 0x2f, 0x95, 0x4c, 0x4b, 0x1c, 0x9c,
		0x31, 0x13, 0x6b, 0x97, 0xb6, 0x49, 0x06, 0x72,
		0xe9, 0x2b, 0x6a, 0x96, 0x3f, 0x80, 0x03, 0xd8,
		0x37, 0x21, 0x62, 0xf9, 0x30, 0x25, 0xc2, 0x3d,
		0xd8, 0xe7, 0x55, 0xba, 0xb3, 0x6b, 0xe9, 0x9b,
		0x65, 0xe4
	};

	static const uint8_t peerpubx[68] = {
		0x00, 0xf3, 0x84, 0xfd, 0xa7, 0x76, 0x11, 0x8c,
		0xa0, 0xee, 0x19, 0x79, 0x54, 0xd9, 0x09, 0xbf,
		0x7e, 0x2a, 0x37, 0xd3, 0xec, 0x41, 0x56, 0x5a,
		0x1f, 0x8a, 0x2f, 0x3d, 0x02, 0x02, 0x62, 0x17,
		0x7d, 0xe7, 0x57, 0x74, 0xef, 0x02, 0xe8, 0x2f,
		0x67, 0x7c, 0x37, 0xff, 0x6e, 0xc5, 0x4e, 0x11,
		0x83, 0x9f, 0x6f, 0xf0, 0x89, 0xa8, 0x59, 0x30,
		0xaa, 0x9c, 0xf6, 0x9f, 0x22, 0x85, 0x02, 0x56,
		0x25, 0x7a
	};
	static const uint8_t sharedinfo[] = {
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
	};

	ecies_context_t enc_context = {
		.flags = 0,
		.mode = CRI_ECIES_P521_KDF1_SHA512_AES256_HMAC_SHA512,
		.curvelen = 66,
		.hashlen = 64,
		.operation = CRI_ECIES_ENCRYPT,
		.peerpubx = peerpubx,
		.pubkey = pub_key,
		.sharedinfo = sharedinfo,
		.sharedinfolen = sizeof(sharedinfo),
		.tag = encrypted_tag
	};

	ecies_context_t dec_context = {
		.flags = 0,
		.mode = CRI_ECIES_P521_KDF1_SHA512_AES256_HMAC_SHA512,
		.curvelen = 66,
		.hashlen = 64,
		.operation = CRI_ECIES_DECRYPT,
		.peerpriv = priv,
		.peerpubx = enc_context.pubkey,
		.pubkey = pub_key_dec,
		.sharedinfo = sharedinfo,
		.sharedinfolen = sizeof(sharedinfo),
		.tag = decrypted_tag
	};
	c_log("Plain Text:\n%s\n", pt);
	int res = do_ecies(&enc_context, pt, sizeof(pt), ct, &ct_length);

	if (res) {goto out; }
	c_log("Cipher Text:\n");
	hexdump(ct, ct_length);

	res += do_ecies(&dec_context, ct, ct_length, pt, &pt_length);
	if (res) {goto out; }
	c_log("Decrypted cipher text:\n%s\n", pt);

	if (memcmp(enc_context.tag, dec_context.tag, sizeof(encrypted_tag))) {
		c_log("TAG comparison failed.\n");
		c_log("Enc Tag:\n");
		hexdump(enc_context.tag, sizeof(*enc_context.tag));
		c_log("Dec Tag:\n");
		hexdump(dec_context.tag, sizeof(*dec_context.tag));
	}
	else {
		c_log("****************************\n");
		c_log("*       ECIES Success      *\n");
		c_log("****************************\n");
	}
out:
	return snprintf(input_data, BUFSIZE,
			(res ? "failed: res %d\n" : "OK\n"), res);
}

int main(void)
{
	c_log("Sample (ECIES) container starting...\n");

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
