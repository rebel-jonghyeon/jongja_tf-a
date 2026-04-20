/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>
#include <cri/cmrt/ecies.h>

#include "common.h"

/*
  * This basic example shows how to use ECIES operations.
 *
 * It handles one data block, whose size is limited by available SAC memory
 * size. It pushes almost all of the data with cri_ecies_update() call. The
 * trailing non-word size data, if any, is pushed with cri_ecies_final() call.
 * It is possible to support data larger than SAC memory size. For that
 * cri_ecies_update() is to be called multiple times. A minimum of 16 bytes must
 * be pushed with cri_ecies_update() in each call. cri_ecies_update() can only
 * handle data in multiple of word sizes. Input and output buffer address must
 * always be word aligned.
 */

enum { AES_BLOCK_BYTES = 16 };

typedef enum {
	/* Close devices and reset context. */
	ECIES_CMD_CLOSE = 0,
	/* Set up encryption operation. */
	ECIES_CMD_ENCRYPT_INIT = 1,
	/* Feed block aligned size PT and receive CT */
	ECIES_CMD_ENCRYPT_UPDATE = 2,
	/* Feed the rest of PT and optional shared info,
	 * receive CT and tag. */
	ECIES_CMD_ENCRYPT_FINAL = 3,
	/* Set up decryption operation. */
	ECIES_CMD_DECRYPT_INIT = 4,
	/* Feed block aligned size CT and receive PT */
	ECIES_CMD_DECRYPT_UPDATE = 5,
	/* Feed the rest of CT, tag and optional shared info,
	 * receive PT and verification result. */
	ECIES_CMD_DECRYPT_FINAL = 6,
} ecies_cmd_t;

typedef struct {
	ecies_cmd_t cmd;
	uint32_t hc_id;
	cri_ecies_mode_t mode;
	size_t textlen;
	size_t sharedinfolen;
	size_t taglen;
	uint8_t data[0];
} ecies_args_t;

typedef struct {
	cri_ecies_t ecies;
	size_t curvelen;
	size_t hashlen;
} ecies_context_t;
static ecies_context_t context = { CRI_INVALID_HANDLE, 0, 0 };

#define ROUNDUP(n, align) (((n) + align - 1) & (~(align - 1)))

static void ecies_close(void)
{
	if (cri_is_valid(context.ecies)) {
		cri_ecies_close(context.ecies);
	}
	memset(&context, 0, sizeof(context));
	context.ecies = CRI_INVALID_HANDLE;
}

static int ecies_open(uint32_t hc_id, cri_ecies_mode_t mode)
{
	switch (mode) {
	case CRI_ECIES_P256_KDF1_SHA256_AES128_HMAC_SHA256:
		context.hashlen = 32;
		context.curvelen = 32;
		break;
	case CRI_ECIES_P384_KDF1_SHA384_AES128_HMAC_SHA384:
		context.hashlen = 48;
		context.curvelen = 48;
		break;
	case CRI_ECIES_P521_KDF1_SHA512_AES256_HMAC_SHA512:
		context.hashlen = 64;
		context.curvelen = 66;
		break;
	default:
		err("Invalid mode: %u\n", mode);
		return -EINVAL;
	}

	uint32_t oflags = (hc_id == 2) ? CRI_ECIES_O_USE_HC2 : 0;
	context.ecies = cri_ecies_open(oflags);
	if (!cri_is_valid(context.ecies)) {
		err("Cannot open ECIES\n");
		memset(&context, 0, sizeof(context));
		return -EBUSY;
	}

	return 0;
}

static int ecies_run(void *input, uint32_t in_used, void *output, uint32_t *out_used,
		     uint32_t out_size)
{
	int rc = 0;
	*out_used = 0;
	printk("ecies_run:\n");

	ecies_args_t *args = (ecies_args_t *) input;
	printk("cmd: %u\n", args->cmd);

	if (out_size < sizeof(ecies_args_t)) {
		err("output buffer too small\n");
		return -ENOSPC;
	}
	ecies_args_t *argsout = (ecies_args_t *) output;
	argsout->cmd = args->cmd;
	argsout->textlen = 0;

	switch (args->cmd) {
	case ECIES_CMD_CLOSE:
		ecies_close();
		break;
	case ECIES_CMD_ENCRYPT_INIT: {
		printk("encrypt init hc%u mode:%u\n", args->hc_id, args->mode);
		ecies_close();
		rc = ecies_open(args->hc_id, args->mode);
		if (rc) {
			break;
		}
		/* peerpubx in, pub_key out */
		rc = cri_ecies_init(context.ecies, args->mode,
				    CRI_ECIES_ENCRYPT, NULL, context.curvelen,
				    args->data, context.curvelen, argsout->data,
				    context.curvelen);
		if (rc == 0) {
			argsout->textlen = context.curvelen;
		}
		break;
	}
	case ECIES_CMD_ENCRYPT_UPDATE:
		printk("encrypt update %u:\n", args->textlen);
		rc = cri_ecies_update(context.ecies, args->data, args->textlen,
				      argsout->data);
		if (rc == 0) {
			argsout->textlen = args->textlen;
		}
		break;
	case ECIES_CMD_ENCRYPT_FINAL: {
		argsout->taglen = context.hashlen;
		printk("encrypt final text:%u sharedinfo:%u, tag:%u\n",
		       args->textlen, args->sharedinfolen, argsout->taglen);
		size_t textlen_aligned = ROUNDUP(args->textlen, 4);
		rc = cri_ecies_final(context.ecies, args->data, args->textlen,
				     args->data + textlen_aligned,
				     args->sharedinfolen,
				     argsout->data + argsout->taglen,
				     argsout->data,
				     argsout->taglen);
		if (rc == 0) {
			argsout->textlen = textlen_aligned;
			*out_used += argsout->taglen;
		}
		break;
	}
	case ECIES_CMD_DECRYPT_INIT: {
		printk("decrypt init hc%u mode:%u\n", args->hc_id, args->mode);
		ecies_close();
		rc = ecies_open(args->hc_id, args->mode);
		if (rc) {
			break;
		}
		if (context.curvelen != args->textlen) {
			printk("wrong private key length: %u != %u\n",
			       args->textlen, context.curvelen);
			break;
		}
		/* peerpriv, epubkey in, pub_key out */
		rc = cri_ecies_init(context.ecies, args->mode,
				    CRI_ECIES_DECRYPT,
				    args->data, context.curvelen,
				    args->data + context.curvelen,
				    context.curvelen, argsout->data,
				    context.curvelen);
		if (rc == 0) {
			argsout->textlen = context.curvelen;
		}
		break;
	}
	case ECIES_CMD_DECRYPT_UPDATE:
		printk("decrypt update %u:\n", args->textlen);
		rc = cri_ecies_update(context.ecies, args->data, args->textlen,
				      argsout->data);
		if (rc == 0) {
			argsout->textlen = args->textlen;
		}
		break;
	case ECIES_CMD_DECRYPT_FINAL: {
		argsout->taglen = context.hashlen;
		printk("decrypt final text:%u sharedinfo:%u tag:%u\n",
		       args->textlen, args->sharedinfolen, argsout->taglen);
		rc = cri_ecies_final(context.ecies, args->data, args->textlen,
				     args->data + args->textlen,
				     args->sharedinfolen,
				     argsout->data + argsout->taglen,
				     argsout->data, argsout->taglen);
		if (rc == 0) {
			argsout->textlen = args->textlen;
			*out_used += argsout->taglen;
		}

		break;
	}
	default:
		return -EINVAL;
		break;
	}
	if (rc) {
		info("ECIES operation %u failed\n", args->cmd);
		ecies_close();
	} else {
		info("ECIES operation %u done\n", args->cmd);
		*out_used += sizeof(*argsout) + ROUNDUP(argsout->textlen, 4);
	}
	return rc;
}

const cmd_t cmd_ecies = { CMDID_ECIES, "ECIES", "ECIES operations", ecies_run };
