/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>
#include <cri/cmrt/pke.h>

#include "common.h"

/*
 * FFDH example allowing a client to interactively perform DH shared
 * secret derivation with CMRT.
 */

#define FFDH_MAX_LENGTH 4096
#define BITS2WORDS(b) ((b) / 32)

/*
 * Note that the term "key" is used maybe slightly incorrectly related
 * to DH; a better choice would be "private value" and "public value".
 */

typedef u32_t ffdh_key_t[BITS2WORDS(FFDH_MAX_LENGTH)];

typedef struct {
	u32_t size;
	u32_t P[BITS2WORDS(FFDH_MAX_LENGTH)];
	u32_t Q[BITS2WORDS(FFDH_MAX_LENGTH)];
	u32_t G[BITS2WORDS(FFDH_MAX_LENGTH)];
} ffdh_params_t;

typedef enum {
	/* Reset the session. */
	FFDH_CMD_RESET = 0,
	/* Set group parameters. */
	FFDH_CMD_SET_PARAMS = 1,
	/* Generate group parameters and return them to the peer. */
	FFDH_CMD_GEN_PARAMS = 2,
	/* Set the peer's public key. */
	FFDH_CMD_SET_PEER_PUB = 3,
	/* Generate a keypair for CMRT and return the public key. */
	FFDH_CMD_GEN_OUR_KEY = 4,
	/* Perform DH and return the shared secret. */
	FFDH_CMD_CALC_SHARED = 5,
} ffdh_cmd_t;

typedef struct {
	ffdh_cmd_t cmd;
	u32_t modsize;
	ffdh_params_t params;
	ffdh_key_t key;
} ffdh_args_t;

typedef struct {
	bool have_params;
	bool have_peer_pub;
	bool have_our_key;
	u32_t modsize;
	ffdh_params_t params;
	ffdh_key_t peer_pub;
	ffdh_key_t our_priv;
	ffdh_key_t our_pub;
	ffdh_key_t shared_secret;
} ffdh_session_t;

static ffdh_session_t sess;

static bool suported_size(u32_t size)
{
	switch (size) {
	case 1024:
	case 2048:
	case 3072:
	case 4096:
		return true;
	default:
		return false;
	}
}

static int ffdh(cri_pke_t pke, const ffdh_args_t *args, ffdh_args_t *argsout)
{
	int ret = 0;
	switch (args->cmd) {
	case FFDH_CMD_RESET:
		memset(&sess, 0, sizeof(sess));
		break;
	case FFDH_CMD_SET_PARAMS: {
		u32_t ks = args->modsize;
		if (!suported_size(ks)) {
			err("unsupported DH group size: %u\n", ks);
			return -EINVAL;
		}
		size_t n = ks / 8;
		sess.modsize = n;
		memcpy(sess.params.P, args->params.P, n);
		memcpy(sess.params.Q, args->params.Q, n);
		memcpy(sess.params.G, args->params.G, n);
		ret = cri_pke_ffdh_verify(pke,
					  n, sess.params.P,
					  n, sess.params.Q,
					  n, sess.params.G);
		if (ret >= 0) {
			sess.have_params = true;
			memcpy(argsout->params.P, sess.params.P, n);
			memcpy(argsout->params.Q, sess.params.Q, n);
			memcpy(argsout->params.G, sess.params.G, n);
		}
		break;
	}
	case FFDH_CMD_GEN_PARAMS: {
		u32_t ks = args->modsize;
		if (!suported_size(ks)) {
			err("unsupported group size for DH param generation\n");
			return -EINVAL;
		}
		memset(&sess, 0, sizeof(sess));
		ret = cri_pke_ffdh_parmgen(pke, ks, ks / 4,
					   sess.params.P,
					   sess.params.Q,
					   sess.params.G);
		if (ret != 0) {
			err("DH param generation failed: %d\n", ret);
			return ret;
		}
		size_t n = ks / 8;
		ret = cri_pke_ffdh_verify(pke,
					  n, sess.params.P,
					  n, sess.params.Q,
					  n, sess.params.G);
		if (ret < 0) {
			err("failed to verify DH parameters: %d\n", ret);
			return ret;
		}
		sess.modsize = n;
		sess.have_params = true;
		memcpy(argsout->params.P, sess.params.P, n);
		memcpy(argsout->params.Q, sess.params.Q, n);
		memcpy(argsout->params.G, sess.params.G, n);
		break;
	}
	case FFDH_CMD_SET_PEER_PUB:
		memcpy(sess.peer_pub, args->key, sess.modsize);
		argsout->modsize = sess.modsize * 8;
		sess.have_peer_pub = true;
		break;
	case FFDH_CMD_GEN_OUR_KEY: {
		if (!sess.have_params) {
			err("DH group params must be set first\n");
			return -EINVAL;
		}
		ret = cri_pke_ffdh_keygen(pke, sess.modsize, sess.params.Q, sess.our_priv);
		if (ret < 0) {
			err("FFDH key generation failed: %d\n", ret);
			break;
		}
		/* Calculate our public key. */
		ret = cri_pke_ffdh(pke, sess.modsize,
				   sess.params.P, sess.params.Q,
				   sess.params.G,
				   sess.our_priv, NULL, sess.our_pub, NULL);
		if (ret < 0) {
			err("failed to generate public key: %d\n", ret);
		} else {
			argsout->modsize = sess.modsize * 8;
			memcpy(argsout->key, sess.our_pub, sess.modsize);
			sess.have_our_key = true;
		}
		break;
	}
	case FFDH_CMD_CALC_SHARED:
		if (!sess.have_params) {
			err("DH group params must be set first\n");
			return -EINVAL;
		}
		if (!sess.have_peer_pub) {
			err("peer public key is not set\n");
			return -EINVAL;
		}
		if (!sess.have_our_key) {
			err("our key is not set\n");
			return -EINVAL;
		}
		/* Calculate our public key. */
		ret = cri_pke_ffdh(pke, sess.modsize,
				   sess.params.P, sess.params.Q, sess.params.G,
				   sess.our_priv,
				   sess.peer_pub, NULL, sess.shared_secret);
		if (ret < 0) {
			err("failed to derive shared secret: %d\n", ret);
		} else {
			argsout->modsize = sess.modsize * 8;
			memcpy(argsout->key, sess.shared_secret, sess.modsize);
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}

static int ffdh_run(void *input, u32_t in_used,
		    void *output, u32_t *out_used, u32_t out_size)
{
	const ffdh_args_t *args = (ffdh_args_t *)input;
	ffdh_args_t *out = (ffdh_args_t *)output;

	if (out_size < sizeof(ffdh_args_t)) {
		err("output buffer too small\n");
		return -ENOSPC;
	}
	*out = *args;

	info("FFDH cmd: %u\n", args->cmd);

	cri_pke_t pke = cri_pke_open(0);
	int ret = ffdh(pke, args, out);
	cri_pke_close(pke);
	info("FFDH operation %s\n", (ret >= 0) ? "done" : "failed");
	cri_pke_close(pke);
	if (ret >= 0) {
		*out_used = sizeof(ffdh_args_t);
	}
	return ret;
}

const cmd_t cmd_ffdh = { CMDID_FFDH, "FFDH", "FFDH operations", ffdh_run };
