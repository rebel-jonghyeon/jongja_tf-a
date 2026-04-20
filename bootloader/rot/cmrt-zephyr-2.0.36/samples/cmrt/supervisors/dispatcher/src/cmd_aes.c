/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <stdio.h>
#include <string.h>

#include <device.h>
#include <cri/cmrt/aes.h>
#include <hexutil.h>

#include "common.h"

/*
 * This basic example shows how to use AES calculations.
 *
 * It handles one data block, whose size is limited by available SAC memory
 * size. It pushes almost all of the data with cri_aes_update() call. The
 * trailing non-word size data, if any, is pushed with cri_aes_final() call.
 * It is possible to support data larger than SAC memory size. For that
 * cri_aes_update() is to be called multiple times. A minimum of 4 bytes must
 * be pushed with cri_aes_update() in each call. cri_aes_update() can only
 * handle data in multiple of word sizes. Input and output buffer address must
 * always be word aligned.
 */

typedef struct {
	u32_t algorithm;
	u32_t operation;
	u8_t *key;
	u32_t keylen;
	u8_t *iv;
	u32_t ivlen;
	u8_t *aad;
	u32_t aadlen;
	u8_t *tag;
	u32_t taglen;
	u8_t *msg;
	u32_t msglen;
} input_args_t;

static int do_aes(input_args_t *args,
		  u32_t in_used,
		  void *output,
		  u32_t *out_used,
		  u32_t out_size)
{
	printk("do_aes:\n");
	/* Open and initialize AES. */
	cri_aes_t aes = cri_aes_open(0);
	if (!cri_is_valid(aes)) {
		err("Cannot open %s!\n", CONFIG_CRI_AES_NAME);
		return -ENOENT;
	}

	printk("cri_aes_init:\n");
	if (args->ivlen == 0) {
		args->iv = NULL;
	}

	int ret = cri_aes_init(aes, args->operation, args->algorithm,
			       args->key, args->keylen,
			       args->iv, args->ivlen,
			       args->taglen);
	if (ret) {
		err("AES init failed %d\n", ret);
		goto out;
	}

	/*
	 * Push most of the data.
	 * _update() can only handle data that is well aligned
	 * (address to word boundary and size to block boundary.)
	 */
	printk("cri_aes_update: %d\n", in_used & ~15);
	ret = cri_aes_update(aes, args->msg, in_used & ~15, output);
	if (ret) {
		err("AES update failed %d\n", ret);
		goto out;
	}
	/*
	 * Push any remaining data and retrieve PT/CT.
	 * It is OK if data size is not a multiple of word size (4).
	 */
	printk("cri_aes_final: %d\n", in_used & 15);
	ret = cri_aes_final(aes, (char *)(args->msg) + (in_used & ~15),
			    in_used & 15, output + (in_used & ~15));
	if (ret) {
		err("AES final failed %d\n", ret);
		goto out;
	}
	printk("Core out:\n");
	hexdump(output, args->msglen);
	*out_used = args->msglen;

out:
	/* Close AES when done. */
	cri_aes_close(aes);
	return ret;
}

static int do_aes_xts(input_args_t *args,
		      u32_t in_used,
		      void *output,
		      u32_t *out_used,
		      u32_t out_size)
{
	printk("do_aes_xts:\n");

	if ((args->keylen != 32) && (args->keylen != 64)) {
		printk("Invalid key length %d\n", args->keylen);
		return false;
	}
	if (args->ivlen != AES_BLOCK_BYTES) {
		printk("invalid XTS iv (tweak) length %d\n", args->ivlen);
		return false;
	}

	/* Open and initialize AES. */
	cri_aes_t aes = cri_aes_open(0);
	if (!cri_is_valid(aes)) {
		err("Cannot open %s!\n", CONFIG_CRI_AES_NAME);
		return -ENOENT;
	}

	printk("cri_aes_init:\n");
	int ret = cri_aes_init(aes, args->operation, args->algorithm,
			       args->key, args->keylen,
			       args->iv, args->ivlen,
			       args->taglen);
	if (ret) {
		err("AES init failed %d\n", ret);
		goto out;
	}

	/* Final must be called with at least AES_BLOCK_BYTES or 0 */
	u32_t in_final = (in_used % AES_BLOCK_BYTES) == 0 ? 0 :
		AES_BLOCK_BYTES + (in_used % AES_BLOCK_BYTES);

	if (in_used > in_final) {
		printk("cri_aes_update: %d\n", in_used - in_final);
		ret = cri_aes_update(aes, args->msg,
				     in_used - in_final, output);
		if (ret) {
			err("AES update failed %d\n", ret);
			goto out;
		}
		*out_used = in_used - in_final;
	}

	printk("cri_aes_final: %d\n", in_final);
	ret = cri_aes_final(aes, (char *)(args->msg) + *out_used,
			    in_final, output + *out_used);
	if (ret) {
		err("AES final failed %d\n", ret);
		goto out;
	}
	*out_used += in_final;

	printk("Core out:\n");
	hexdump(output, *out_used);

out:
	/* Close AES when done. */
	cri_aes_close(aes);
	return ret;
}

static int do_aes_gcm(input_args_t *args,
		      u32_t in_used,
		      void *output,
		      u32_t *out_used,
		      u32_t out_size)
{
	printk("do_aes_gcm:\n");
	if ((args->algorithm == CRI_AES_GCM) && (args->ivlen != 12)) {
		printk("invalid iv length for aes-gcm: %u\n", args->ivlen);
		return -1;
	}
	/* Open and initialize AES. */
	cri_aes_t aes = cri_aes_open(0);
	if (!cri_is_valid(aes)) {
		err("Cannot open %s!\n", CONFIG_CRI_AES_NAME);
		return -ENOENT;
	}

	printk("cri_aes_init:\n");
	if (args->ivlen == 0) {
		args->iv = NULL;
	}
	if (args->algorithm == CRI_AES_CMAC) {
		/*
		 * In case of AES CMAC, input tag is empty and
		 * it is always calculated with full length of 16 bytes.
		 */
		args->taglen = 16;
	}
	int ret = cri_aes_init(aes, args->operation, args->algorithm,
			       args->key, args->keylen,
			       args->iv, args->ivlen,
			       args->taglen);
	if (ret) {
		err("AES init failed %d\n", ret);
		goto out;
	}

	printk("cri_aes_final_aad: %d\n", args->aadlen);
	ret = cri_aes_final_aad(aes, args->aad, args->aadlen);
	if (ret) {
		err("cri_aes_final_aad failed %d\n", ret);
		goto out;
	}
	/*
	 * Push any remaining data and retrieve PT/CT.
	 * It is OK if data size is not a multiple of word size (4).
	 */
	printk("cri_aes_ae_final: %d\n", args->msglen);
	ret = cri_aes_ae_final(aes, args->msg, args->msglen, output,
			       args->tag, &args->taglen);
	if (ret) {
		err("cri_aes_ae_final failed %d\n", ret);
		goto out;
	}
	printk("Core out:\n");
	if (args->algorithm == CRI_AES_CMAC) {
		hexdump(args->tag, args->taglen);
		memcpy(output, args->tag, args->taglen);
		*out_used = args->taglen;
	} else {
		hexdump(output, args->msglen);
		if (args->operation == CRI_AES_ENCRYPT) {
			printk("Tag:\n");
			hexdump(args->tag, args->taglen);
			memcpy((u8_t *)(output + args->msglen), args->tag, args->taglen);
			*out_used = args->msglen + args->taglen;
		} else {
			*out_used = args->msglen;
		}
	}

out:
	/* Close AES when done. */
	cri_aes_close(aes);
	return ret;
}


static int do_aes_ccm(input_args_t *args,
		      u32_t in_used,
		      void *output,
		      u32_t *out_used,
		      u32_t out_size)
{
	printk("do_aes_ccm:\n");
	/* Open and initialize AES. */
	cri_aes_t aes = cri_aes_open(0);
	if (!cri_is_valid(aes)) {
		err("Cannot open %s!\n", CONFIG_CRI_AES_NAME);
		return -ENOENT;
	}

	printk("cri_aes_init:\n");
	if (args->ivlen == 0) {
		args->iv = NULL;
	}
	bool has_aad = (args->aadlen > 0);
	static u32_t b0[16];
	static u32_t bn[256];
	u32_t bnlen = 0;
	/* Prepare b0 and bn */
	int ret = cri_aes_ccm_encode_nonce(b0, sizeof(b0),
					   args->iv,
					   args->ivlen,
					   args->msglen,
					   args->taglen,
					   has_aad);

	info("b0 encode: %d\n", ret);
	if (ret < 0) {
		goto out;
	}
	ret = cri_aes_ccm_encode_aad(bn, sizeof(bn), args->aad, args->aadlen);
	if (ret < 0) {
		err("cri_aes_ccm_encode_aad failed %d\n", ret);
		goto out;
	}
	bnlen = ret;
	ret = cri_aes_init(aes, args->operation, args->algorithm,
			   args->key, args->keylen,
			   b0, sizeof(b0),
			   args->taglen);
	if (ret) {
		err("AES init failed %d\n", ret);
		goto out;
	}

	ret = cri_aes_final_aad(aes, bn, bnlen);
	if (ret) {
		err("cri_aes_final_aad failed %d\n", ret);
		goto out;
	}
	/*
	 * Push any remaining data and retrieve PT/CT.
	 * It is OK if data size is not a multiple of word size (4).
	 */
	ret = cri_aes_ae_final(aes, args->msg, args->msglen, output,
			       args->tag, &args->taglen);
	if (ret) {
		err("cri_aes_ae_final failed %d\n", ret);
		goto out;
	}
	printk("Core out:\n");
	hexdump(output, args->msglen);
	if (args->operation == CRI_AES_ENCRYPT) {
		printk("Tag:\n");
		hexdump(args->tag, args->taglen);
		memcpy((u8_t *)(output + args->msglen), args->tag, args->taglen);
		*out_used = args->msglen + args->taglen;
	} else {
		*out_used = args->msglen;
	}

out:
	/* Close AES when done. */
	cri_aes_close(aes);
	return ret;
}

typedef struct {
	u32_t algorithm;
	u32_t encrypt;
	u32_t keylen;
	u32_t ivlen;
	u32_t aadlen;
	u32_t taglen;
	u32_t msglen;
	u8_t data[0];
} aes_args_t;

#ifdef CONFIG_SV_PERF_MEAS
static const char *aes_mode_names[] = {
		"ECB",
		"CBC",
		"CFB",
		"CTR",
		"GCM",
		"CCM",
		"XTS",
		"CMAC"
};

static const char *aes_operation_names[] = {
		"ENCRYPTION",
		"DECRYPTION"
};
#endif

static int aes_run(void *input, u32_t in_used,
		   void *output, u32_t *out_used, u32_t out_size)
{
#ifdef CONFIG_SV_PERF_MEAS
	u32_t cycles;
	plog_reset();
	plog_set_ref();
#endif
	int ret;

	printk("aes_run:\n");
	aes_args_t *c = (aes_args_t *) input;

	char *key_offset = c->data;
	char *iv_offset = key_offset + ((c->keylen + 3) & ~3);
	char *aad_offset = iv_offset + ((c->ivlen + 3) & ~3);
	char *tag_offset = aad_offset + ((c->aadlen + 3) & ~3);
	char *msg_offset = tag_offset;
	if (c->encrypt == CRI_AES_DECRYPT) {
		msg_offset = tag_offset + ((c->taglen + 3) & ~3);
	}

	input_args_t input_args = {
		 .algorithm = c->algorithm,
		 .operation = c->encrypt,
		 .key = key_offset,
		 .keylen = c->keylen,
		 .iv = iv_offset,
		 .ivlen = c->ivlen,
		 .aad = aad_offset,
		 .aadlen = c->aadlen,
		 .tag = tag_offset,
		 .taglen = c->taglen,
		 .msg = msg_offset,
		 .msglen = c->msglen
	};

	printk("algorithm: %d\n", c->algorithm);
	printk("operation: %d\n", c->encrypt);
	printk("key: %d\n", c->keylen);
	hexdump(input_args.key, c->keylen);
	printk("iv: %d\n", c->ivlen);
	hexdump(input_args.iv, c->ivlen);
	printk("aad: %d\n", c->aadlen);
	hexdump(input_args.aad, c->aadlen);
	printk("tag: %d\n", c->taglen);
	hexdump(input_args.tag, c->taglen);
	printk("msg: %d\n", c->msglen);
	hexdump(input_args.msg, c->msglen);
	printk("in_used: %d\n", in_used);

	if (c->algorithm == CRI_AES_GCM || c->algorithm == CRI_AES_CMAC) {
		ret = do_aes_gcm(&input_args,
				 c->msglen,
				 output,
				 out_used,
				 out_size);
	} else if (c->algorithm == CRI_AES_CCM) {
		ret = do_aes_ccm(&input_args,
				 c->msglen,
				 output,
				 out_used,
				 out_size);
	} else if (c->algorithm == CRI_AES_XTS) {
		ret = do_aes_xts(&input_args,
				 c->msglen,
				 output,
				 out_used,
				 out_size);
	} else {
		ret = do_aes(&input_args,
			     c->msglen,
			     output,
			     out_used,
			     out_size);
	}

#ifdef CONFIG_SV_PERF_MEAS
	cycles = plog_get_cycles();
	plog("AES,AES-%s,%s,%d,%d,%u", aes_mode_names[c->algorithm],
		aes_operation_names[c->encrypt], c->msglen, c->keylen * 8, cycles);
#endif
	return ret;
}

const cmd_t cmd_aes = { CMDID_AES, "AES",
			"Compute AES over input data", aes_run };
