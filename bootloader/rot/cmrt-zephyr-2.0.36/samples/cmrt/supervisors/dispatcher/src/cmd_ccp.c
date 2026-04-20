/*
 * Copyright (c) 2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <stdio.h>
#include <string.h>

#include <device.h>
#include <cri/cmrt/ccp.h>

#include "common.h"

/*
 * Examples for chacha20, Poly1305, and ChachaPoly usage
 */

typedef struct {
	u32_t op;
	u32_t mode;
	u32_t keylen;
	u32_t ivlen;
	u32_t aadlen;
	u32_t taglen;
	u32_t msglen;
	u8_t data[0];
} ccp_args_t;

static bool verify_inputs(const ccp_args_t *args);

static int do_ccp_operation(ccp_args_t * const args, u32_t in_used,
			    void * const output, u32_t * const out_used)
{
	printk("do_ccp_operation:\n");
	cri_ccp_t ccp = cri_ccp_open(0);
	if (!cri_is_valid(ccp)) {
		err("CCP context open failed\n");
		return -EIO;
	}

	printk("ccp operation: %s\n",
	       args->op == CIPHER_OP_ENCRYPT ? "encrypt" : "decrypt");

	const char * const key = args->data;
	const char * const iv = key + ((args->keylen + 3) & ~3);
	const char * const aad = iv + ((args->ivlen + 3) & ~3);
	const char * const tag_in = aad + ((args->aadlen + 3) & ~3);
	const char *msg = tag_in + ((args->taglen + 3) & ~3);

	DEBUG_HEXDUMP_VAR(key, args->keylen);
	DEBUG_HEXDUMP_VAR(iv, args->ivlen);
	DEBUG_HEXDUMP_VAR(aad, args->aadlen);
	DEBUG_HEXDUMP_VAR(tag_in, args->taglen);
	DEBUG_HEXDUMP_VAR(msg, args->msglen);

	int res = -EINVAL;
	const int block = args->mode == CCP_MODE_POLY ?
		POLY_BLOCK_BYTES : CHACHA_BLOCK_BYTES;
	int taglen = args->mode == CCP_MODE_CHACHA ? 0 : POLY_TAG_LENGTH_BYTES;

	res = cri_ccp_init(ccp, args->op, args->mode, key, args->keylen,
			   args->ivlen == 0 ? NULL : iv, args->ivlen, taglen);
	if (res != 0) {
		err("cri_ccp_init() failed %d\n", res);
		goto out;
	}

	if (args->mode == CCP_MODE_CHACHA_POLY_AEAD) {
		res = cri_ccp_final_aad(ccp, aad, args->aadlen);
		if (res != 0) {
			err("cri_ccp_final_aad() failed %d\n", res);
			goto out;
		}
	}

	u32_t len = args->msglen;
	char *out = output;
	alignas(4) u8_t out_block[CHACHA_BLOCK_BYTES] = {0};
	for (; len > block; len -= block) {
		if (args->mode == CCP_MODE_POLY) {
			res = cri_ccp_update_aad(ccp, msg, block);
		} else {
			res = cri_ccp_update(ccp, msg, block, out_block);
			memcpy(out, &out_block, block);
			out += block;
		}
		if (res != 0) {
			err("ccp update failed %d\n", res);
			goto out;
		}
		msg += block;
	}

	alignas(4) u8_t tag[POLY_TAG_LENGTH_BYTES] = {0};
	switch (args->mode) {
	case CCP_MODE_CHACHA:
		res = cri_ccp_final(ccp, msg, len, out_block);
		if (res != 0) {
			err("cri_ccp_final() failed %d\n", res);
			goto out;
		}
		memcpy(out, &out_block, len);
		*out_used = args->msglen;
		break;
	case CCP_MODE_CHACHA_POLY_AEAD:
		if (args->op == CIPHER_OP_DECRYPT) {
			memcpy(tag, tag_in, taglen);
		}
		res = cri_ccp_ae_final(
			ccp, msg, len, out_block, tag, &taglen);
		if (res != 0) {
			err("cri_ccp_ae_final() failed %d\n", res);
			goto out;
		}
		memcpy(out, &out_block, len);
		*out_used = args->msglen;
		if (args->op == CIPHER_OP_ENCRYPT) {
			memcpy(out + len, &tag, taglen);
			DEBUG_HEXDUMP_VAR(tag, taglen);
			*out_used += taglen;
		}
		res = cri_ccp_invalidate_key(ccp, 0);
		if (res != 0) {
			err("cri_ccp_invalidate_key() failed %d\n", res);
			goto out;
		}
		break;
	case CCP_MODE_POLY:
		res = cri_ccp_final_aad(ccp, msg, len);
		if (res != 0) {
			err("cri_ccp_final_aad() failed %d\n", res);
			goto out;
		}
		res = cri_ccp_ae_final(ccp, NULL, 0, NULL, out_block, &taglen);
		if (res != 0) {
			err("cri_ccp_ae_final() failed %d\n", res);
			goto out;
		}
		memcpy(out, &out_block, taglen);
		*out_used = taglen;
		break;
	default:
		goto out;
	}
	DEBUG_HEXDUMP_VAR(output, *out_used);
 out:
	cri_ccp_close(ccp);
	return res;
}

static int ccp_run(void *input, u32_t in_used,
		   void *output, u32_t *out_used, u32_t out_size)
{
	printk("ccp_run:\n");
	ccp_args_t *args = (ccp_args_t *) input;
	if (!verify_inputs(args)) {
		return -EINVAL;
	}
	return do_ccp_operation(args, in_used, output, out_used);
}

const cmd_t cmd_ccp = { CMDID_CCP, "CCP",
			 "Run ChachaPoly operations", ccp_run };

static bool verify_inputs(const ccp_args_t * const args)
{
	bool res = true;
	switch (args->mode) {
	case CCP_MODE_CHACHA:
		if ((args->taglen != 0) || (args->aadlen != 0)) {
			err("Invalid mode chacha input\n");
			res = false;
		}
		break;
	case CCP_MODE_POLY:
		if ((args->ivlen != 0) ||
		    (args->msglen == 0) ||
		    (args->op == CIPHER_OP_DECRYPT)) {
			err("Invalid mode poly input\n");
			res = false;
		}
		break;
	case CCP_MODE_CHACHA_POLY_AEAD:
		if ((args->op == CIPHER_OP_DECRYPT) &&
		    (args->taglen != POLY_TAG_LENGTH_BYTES)) {
			err("Invalid mode chachapoly input\n");
			res = false;
		}
		break;
	default:
		err("Invalid ccp mode %d\n", args->mode);
		res = false;
		break;
	}
	if ((args->op != CIPHER_OP_ENCRYPT) &&
	    (args->op != CIPHER_OP_DECRYPT)) {
		err("Invalid ccp operation %d\n", args->op);
		res = false;
	}
	if ((args->op == CIPHER_OP_ENCRYPT) && (args->taglen != 0)) {
		err("Tag length should be zero during encrypt\n");
		res = false;
	}
	return res;
}
