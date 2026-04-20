/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include "common.h"

#ifdef CONFIG_CMRT_RSA

#include <stdalign.h>
#include <stdio.h>
#include <string.h>

#include <device.h>
#include <cri/cmrt/pke.h>
#include <cri/cmrt/hc.h>
#include "internals.h"
#include "crypto/rsa_common.h"
#include <libpad.h>


/* short-hand function names */
#define rsaep cri_pke_rsa_public_key_primitive

/*
 * This basic example shows how to use RSA calculations.
 *
 */

typedef struct {
	u32_t mode;
	u32_t alg;
	u32_t nlen;
	u32_t elen;
	u32_t dlen;
	u32_t saltvallen;
	u32_t slen;
	u32_t plen;
	u32_t qlen;
	u32_t dplen;
	u32_t dqlen;
	u32_t iqlen;
	u32_t msglen;
	u8_t data[0];
} rsa_args_t;

enum {
	RSA_MAX_KEY_BITS = 8192,
	SCRATCH_WORDS = (RSA_CRT_SCRATCH_SIZE(RSA_MAX_KEY_BITS))/4
};

/*!
 * Specify if using a constant size independent of key size for all
 * scratch buffers.  The static buffer is always maxed out: behaviour
 * is more constant, and this is required by some coding standards.
 *
 * The static size may prevent some operations from succeeding with
 * smaller key sizes, where they would otherwise succeed, however, as
 * stack is exhausted.
 *
 * The dynamic buffer is allocated using alloca() and not as a VLA.
 *
 * Regardless of allocation strategy, the buffer is immediately filled
 * with zeros to force a hit on any stack guard pages.
 */
#if RSA_CONSTANT_SCRATCH_SIZE > 0
#define DEFSCRATCH(B) uint32_t scratch[SCRATCH_WORDS] = { 0 } \
		uint32_t scratch_size = SCRATCH_WORDS * 4;
#else
#define DEFSCRATCH(B) \
	uint32_t scratch_size = RSA_CRT_SCRATCH_SIZE(B);	\
	uint32_t *scratch = alloca(scratch_size); \
	memset(scratch, 0, scratch_size)
#endif

/* Private primitive.  Select function according to if key has CRT
 * components or not.
 */
static int rsadp(cri_pke_t pke, const struct cri_rsa_key *key,
		 const uint32_t *in, uint32_t *out)
{
#ifdef CONFIG_CMRT_RSA_CRT
	if (key->q) {
		printk("do cri_pke_rsa_crt_primitive\n");
		DEFSCRATCH(key->bits);
		/* CRT primitive is synchronous does and not need sync() */
		return cri_pke_rsa_crt_primitive(pke, key, in, out,
						 scratch, scratch_size);
	}
#endif
	printk("do cri_pke_rsa_private_key_primitive\n");
	int ret = cri_pke_rsa_private_key_primitive(pke, key->bits,
						 key->n, key->e, key->d,
						 in, out);
	return ret;
}

static int do_rsa_sign(rsa_args_t *args,
		    u32_t in_used,
		    void *output,
		    u32_t *out_used)
{
	printk("do_rsa_sign:\n");

	u8_t *n = args->data;
	u8_t *e = n + ((args->nlen + 3) & ~3);
	u8_t *d = e + ((args->elen + 3) & ~3);
	u8_t *salt_val = d + ((args->dlen + 3) & ~3);
	u8_t *s = salt_val + ((args->saltvallen + 3) & ~3);
	u8_t *p = s + ((args->slen + 3) & ~3);
	u8_t *q = p + ((args->plen + 3) & ~3);
	u8_t *dp = q + ((args->qlen + 3) & ~3);
	u8_t *dq = dp + ((args->dplen + 3) & ~3);
	u8_t *iq = dq + ((args->dqlen + 3) & ~3);
	u8_t *msg = iq + ((args->iqlen + 3) & ~3);
	HEXDUMP_VAR(n, args->nlen);
	HEXDUMP_VAR(e, args->elen);
	HEXDUMP_VAR(d, args->dlen);
	HEXDUMP_VAR(salt_val, args->saltvallen);
	HEXDUMP_VAR(p, args->plen);
	HEXDUMP_VAR(q, args->qlen);
	HEXDUMP_VAR(dp, args->dplen);
	HEXDUMP_VAR(dq, args->dqlen);
	HEXDUMP_VAR(iq, args->iqlen);
	HEXDUMP_VAR(msg, args->msglen);

	/* Open and initialize RSA. */
	cri_pke_t pke = cri_pke_open(0);
	if (!cri_is_valid(pke)) {
		err("Cannot open %s!\n", CONFIG_CRI_PKE_NAME);
		return -EIO;
	}
	/*!
	* RSA (CRT) key.  Accepted key sizes depend on exact system
	* specifications, but typically accepted are 2048, 3072, and 4096.
	* The members can be optional according to routine;
	* - public keys have n and e
	* - private keys have n, and either (d, e), or (e, p, q, dp, dq, iq);
	* or, all of the elements
	*/
	cri_reverse(n, n, args->nlen);
	cri_reverse(e, e, args->elen);
	struct cri_rsa_key key = {
		.bits = args->nlen * 8, /**< bits in key data */
		.flags = 0, 		/**< flags, keep at 0 */
		.n = (uint32_t *)n, 	/**< public modulus, bits/8 bytes */
		.e = (uint32_t *)e, 	/**< public exponent, bits/8 bytes */
		.d = NULL, 		/**< private exponent, bits/8 bytes */
		.p = NULL, 		/**< crt prime 1, bits/16 bytes */
		.q = NULL, 		/**< crt prime 2, bits/16 bytes */
		.dp = NULL,		/**< crt exponent 1, bits/16 bytes */
		.dq = NULL,		/**< crt exponent 2, bits/16 bytes */
		.iq = NULL		/**< crt coefficient, bits/16 bytes */
	};
	if (args->dplen == 0) {
		cri_reverse(d, d, args->dlen);
		key.d = (uint32_t *)d;
	} else { /* crt */
		cri_reverse(p, p, args->plen);
		cri_reverse(q, q, args->qlen);
		cri_reverse(dp, dp, args->dplen);
		cri_reverse(dq, dq, args->dqlen);
		cri_reverse(iq, iq, args->iqlen);
		key.p = (uint32_t *)p;
		key.q = (uint32_t *)q;
		key.dp = (uint32_t *)dp;
		key.dq = (uint32_t *)dq;
		key.iq = (uint32_t *)iq;
	}
	int ret = -1;
	*out_used = 0;
	struct cri_pss_params params = {
		.bits = args->nlen * 8,		/*!< length of key in bits */
		.hlen = args->msglen,		/*!< hash output in bytes */
		.flags = CRI_PSS_PREHASHED,	/*!< hash flags */
		.halgo = args->alg,		/*!< hash algorithm used */
		.slen = args->saltvallen	/*!< salt length in bytes, maximum 64 */
	};
	uint32_t padbuf[RSA_MAX_KEY_BITS/32] = { 0 };
	uint32_t sigbuf[RSA_MAX_KEY_BITS/32] = { 0 };
	printk("do cri_pss_enc:\n");
	if (cri_pss_enc(&params, msg, params.hlen, padbuf) >= 0) {
		cri_reverse(padbuf, padbuf, params.bits / 8);
		if (rsadp(pke, &key, padbuf, sigbuf) >= 0) {
			cri_reverse(sigbuf, sigbuf, params.bits / 8);
			hexdump_var("Core out", sigbuf, params.bits / 8);
			memcpy(output, &sigbuf, params.bits / 8);
			*out_used = params.bits / 8;
			ret = 0;
		}
		cri_pke_close(pke);
	}
	return ret;
}

static int do_rsa_verify(rsa_args_t *args,
		    u32_t in_used,
		    void *output,
		    u32_t *out_used)
{
	printk("do_rsa_verify:\n");

	u8_t *n = args->data;
	u8_t *e = n + ((args->nlen + 3) & ~3);
	u8_t *d = e + ((args->elen + 3) & ~3);
	u8_t *salt_val = d + ((args->dlen + 3) & ~3);
	u8_t *s = salt_val + ((args->saltvallen + 3) & ~3);
	u8_t *p = s + ((args->slen + 3) & ~3);
	u8_t *q = p + ((args->plen + 3) & ~3);
	u8_t *dp = q + ((args->qlen + 3) & ~3);
	u8_t *dq = dp + ((args->dplen + 3) & ~3);
	u8_t *iq = dq + ((args->dqlen + 3) & ~3);
	u8_t *msg = iq + ((args->iqlen + 3) & ~3);
	HEXDUMP_VAR(n, args->nlen);
	HEXDUMP_VAR(e, args->elen);
	HEXDUMP_VAR(s, args->slen);
	HEXDUMP_VAR(salt_val, args->saltvallen);
	HEXDUMP_VAR(msg, args->msglen);

	u32_t *result = output;
	result[0] = 0x1; /* FAIL */
	*out_used = 1;
	/* Open and initialize RSA. */
	cri_pke_t pke = cri_pke_open(0);
	if (!cri_is_valid(pke)) {
		err("Cannot open %s!\n", CONFIG_CRI_PKE_NAME);
		return -EIO;
	}
	/* Verify RSA signature. */
	printk("cri_pss_verify:\n");
	int ret = -1;
	struct cri_pss_params params = {
		.bits = args->nlen * 8,		/*!< length of key in bits */
		.hlen = args->msglen,		/*!< hash output in bytes */
		.flags = CRI_PSS_PREHASHED,	/*!< hash flags */
		.halgo = args->alg,		/*!< hash algorithm used */
		.slen = args->saltvallen	/*!< salt length in bytes, maximum 64 */
	};
	cri_reverse(n, n, args->nlen);
	cri_reverse(e, e, args->elen);
	cri_reverse(s, s, args->slen);
	uint32_t outbuf[RSA_MAX_KEY_BITS/32] = { 0 };
	if (rsaep(pke, params.bits,
		  (uint32_t *)n,
		  (uint32_t *)e,
		  (uint32_t *)s, outbuf) >= 0
	    && cri_pke_sync(pke) >= 0) {
		cri_reverse(outbuf, outbuf, params.bits / 8);
		ret = cri_pss_verify(&params, msg, params.hlen, outbuf);
		printk("cri_pss_verify_ret: %d\n", ret);
	}
	if (ret >= 0)
		result[0] = 0x0; /* PASS */
	/* If pke sync fails with EINVAL, verify result is FAIL
	   but it is not an error */
	if (ret == -EINVAL)
		ret = 0;
	printk("Core out: %d\n", result[0]);

	/* Close RSA when done. */
	if (cri_is_valid(pke))
		cri_pke_close(pke);
	return 0;
}

static int rsa_run(void *input, u32_t in_used,
		   void *output, u32_t *out_used, u32_t out_size)
{
#ifdef CONFIG_SV_PERF_MEAS
	u32_t cycles;

	plog_reset();
#endif
	int ret = 0;
	printk("rsa_run:\n");
	rsa_args_t *args = (rsa_args_t *) input;
	printk("mode: %u\n", args->mode);
	printk("alg: %d\n", args->alg);
#ifdef CONFIG_SV_PERF_MEAS
	plog_set_ref();
#endif

	if (args->mode == 0) {
		ret = do_rsa_sign(args, in_used, output, out_used);
#ifdef CONFIG_SV_PERF_MEAS
		cycles = plog_get_cycles();
		plog("RSA,%d-Sign-%d,%u,%u", args->alg, args->nlen * 8, args->mode, cycles);
#endif
		return ret;
	}
	if (args->mode == 1) {
		ret = do_rsa_verify(args, in_used, output, out_used);
#ifdef CONFIG_SV_PERF_MEAS
		cycles = plog_get_cycles();
		plog("RSA,%d-Verify-%d,%u,%u", args->alg, args->nlen * 8, args->mode, cycles);
#endif
		return ret;
	}
	return -EINVAL;
}

#else

static int rsa_run(void *input, u32_t in_used,
		     void *output, u32_t *out_used, u32_t out_size)
{
	printk("RSA not supported for this target\n");
	return -EINVAL;
}

#endif

const cmd_t cmd_rsa = { CMDID_RSA, "RSA",
			  "Compute RSA over input data", rsa_run };
