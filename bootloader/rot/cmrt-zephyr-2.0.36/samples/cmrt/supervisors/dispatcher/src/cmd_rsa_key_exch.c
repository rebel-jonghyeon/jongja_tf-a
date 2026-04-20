/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifdef CONFIG_CMRT_RSA

#include <stdalign.h>
#include <stdio.h>
#include <string.h>
#include <device.h>
#include <cri/cmrt/pke.h>
#include <cri/cmrt/hc.h>
#include <libpad.h>
#include <teefs.h>
#include <crypto/rsa_common.h>

#include "internals.h"

#endif /* CONFIG_CMRT_RSA */

#include "common.h"

#ifdef CONFIG_CMRT_RSA

/* short-hand function names */
#define rsaep cri_pke_rsa_public_key_primitive

#define TEEFS_MP "" /* mount point */
#define TEEFS_MPLEN (sizeof(TEEFS_MP) - 1)

/*
 * This basic example shows how to use RSA key exchange.
 * Private key is first loaded to teefs before using it.
 *
 * NOTE: Instead of using private key directly, it is recommended
 * to run it trough key derivation function before using it.
 * That way the private key would not be exposed to someone
 * listening the traffic.
*/

typedef struct {
	uint32_t cmd; /* cmd: 0 for key loading */
	uint32_t nlen;
	uint32_t elen;
	uint32_t dlen;
	uint32_t plen;
	uint32_t qlen;
	uint32_t dplen;
	uint32_t dqlen;
	uint32_t iqlen;
	uint8_t data[0];
} rsa_key_t;

typedef struct {
	uint32_t cmd; /* cmd: 1 for rsa key exchange */
	uint32_t msglen;
	uint8_t data[0];
} rsa_key_exch_t;

enum {
	RSA_MAX_KEY_BITS = 8192,
	RSA_MAX_KEY_BYTES = RSA_MAX_KEY_BITS / 8,
	SALT_VAL_LEN = 64,
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

static int load_rsa_key(uint8_t **n, uint8_t **e, uint8_t **d,
			uint8_t **p, uint8_t **q, uint8_t **dp, uint8_t **dq, uint8_t **iq,
			size_t *keylen, size_t *plen)
{
	printk("do load_rsa_key:\n");
	static const uint8_t name[] = "priv_key.bin";
	static uint32_t buffer[4 + (RSA_MAX_KEY_BYTES * 3) / 4] = {0};
	printk("do teefs_open:\n");
	int fd = teefs_open(name, sizeof(name) - 1, 0);
	if (fd < 0) {
		printk("teefs_open failed: %d\n", fd);
		return fd;
	}
	printk("do teefs_read:\n");
	size_t datalen = teefs_stat(fd);
	int res = teefs_read(fd, buffer, &datalen);
	rsa_key_t *key = (rsa_key_t *)buffer;
	if (res < 0) {
		printk("teefs_read failed: %d\n", res);
		return res;
	}
	*n = (uint8_t *)key->data;
	*e = *n + ROUND_UP(key->nlen, 4);
	*d = *e + ROUND_UP(key->elen, 4);
	*p = *d + ROUND_UP(key->dlen, 4);
	*q = *p + ROUND_UP(key->plen, 4);
	*dp = *q + ROUND_UP(key->qlen, 4);
	*dq = *dp + ROUND_UP(key->dplen, 4);
	*iq = *dq + ROUND_UP(key->dqlen, 4);

	HEXDUMP_VAR(*n, key->nlen);
	HEXDUMP_VAR(*e, key->elen);
	HEXDUMP_VAR(*d, key->dlen);
	HEXDUMP_VAR(*p, key->plen);
	HEXDUMP_VAR(*q, key->qlen);
	HEXDUMP_VAR(*dp, key->dplen);
	HEXDUMP_VAR(*dq, key->dqlen);
	HEXDUMP_VAR(*iq, key->iqlen);

	*keylen = key->nlen;
	*plen = key->plen;
	printk("do teefs_close:\n");
	teefs_close(fd);
	return 0;
}

static int store_rsa_key(rsa_key_t *key,
			 void *output,
			 uint32_t *out_used)
{
	printk("do store_rsa_key:\n");
	if (key->nlen > RSA_MAX_KEY_BYTES ||
	    key->elen > RSA_MAX_KEY_BYTES ||
	    key->dlen > RSA_MAX_KEY_BYTES) {
		printk("Invalid key size. Check n, e, d params.\n");
		printk("Maximum key size is: %d bits\n", RSA_MAX_KEY_BITS);
		return -EINVAL;
	}
	static const uint8_t name[] = "priv_key.bin";
	size_t datalen = sizeof(rsa_key_t) +
			 ROUND_UP(key->nlen, 4) +
			 ROUND_UP(key->elen, 4) +
			 ROUND_UP(key->dlen, 4) +
			 ROUND_UP(key->plen, 4) +
			 ROUND_UP(key->qlen, 4) +
			 ROUND_UP(key->dplen, 4) +
			 ROUND_UP(key->dqlen, 4) +
			 ROUND_UP(key->iqlen, 4);
	int res = teefs_gc(TEEFS_MP, TEEFS_MPLEN);
	if (res < 0) {
		printk("teefs_gc failed: %d\n", res);
		return res;
	}
	printk("do teefs_open:\n");
	int fd = teefs_open(name, sizeof(name) - 1, TEEFS_FLAG_CREATE);
	if (fd < 0) {
		printk("teefs_open failed: %d\n", fd);
		return fd;
	}
	res = teefs_truncate(fd, 0);
	if (res < 0) {
		printk("teefs_truncate failed: %d\n", res);
		return res;
	}
	res = teefs_write(fd, key, datalen);
	if (res < 0) {
		printk("teefs_write failed: %d\n", res);
		return res;
	}
	printk("do teefs_close:\n");
	teefs_close(fd);
	/* return public key (n, e) */
	memcpy(output, (uint8_t *)key->data, key->nlen + key->elen);
	*out_used = key->nlen + key->elen;
	return 0;
}

static int sign_hash(cri_pke_t *pke,
		     const struct cri_rsa_key *key,
		     void *inbuf,
		     void *outbuf,
		     void *output,
		     uint32_t *out_used,
		     size_t *hash_size)
{
	struct cri_pss_params pss = {
		.bits = key->bits,	    /*!< length of key in bits */
		.hlen = *hash_size,	    /*!< hash output in bytes */
		.flags = CRI_PSS_PREHASHED, /*!< hash flags */
		.halgo = CRI_HASH_SHA256,   /*!< hash algorithm used */
		.slen = SALT_VAL_LEN,       /*!< salt length in bytes, maximum 64 */
	};
	uint32_t padbuf[RSA_MAX_KEY_BITS/32] = { 0 };

	printk("Sign hash:\n");
	if (cri_pss_enc(&pss, inbuf, pss.hlen, padbuf) >= 0) {
		cri_reverse(padbuf, padbuf, pss.bits / 8);
		printk("do rsadp:\n");
		if (rsadp(*pke, key, padbuf, outbuf) >= 0) {
			printk("do cri_reverse:\n");
			cri_reverse(output, outbuf, pss.bits / 8);
			hexdump_var("Core out", output, pss.bits / 8);
			*out_used = pss.bits / 8;
			return 0;
		}
	} else {
		printk("cri_pss_enc failed\n");
	}
	return -1;
}

static int hash(void *inbuf, void *outbuf, size_t *input_size, size_t *hash_size)
{
	hexdump_var("Hash in", inbuf, *input_size);
	cri_hc_t hc = CRI_INVALID_HANDLE;
	hc = cri_hc_open(0);
	int res = cri_hc_init(hc, HC_HASH_ALGO_SHA_256, 0, 0);
	res = cri_hc_final(hc, inbuf, *input_size, outbuf, hash_size);
	hexdump_var("Hash out", outbuf, *hash_size);
	memcpy(inbuf, outbuf, *hash_size);
	cri_hc_close(hc);
	return 0;
}

static int rsa_key_exch(void *input, uint32_t in_used,
			void *output, uint32_t *out_used, uint32_t out_size)
{
	printk("rsa_key_exch:\n");
	*out_used = 0;
	int res = -1;

	uint8_t *n = NULL;
	uint8_t *e = NULL;
	uint8_t *d = NULL;

	uint8_t *p = NULL;
	uint8_t *q = NULL;
	uint8_t *dp = NULL;
	uint8_t *dq = NULL;
	uint8_t *iq = NULL;

	rsa_key_t *sel = (rsa_key_t *) input;
	if (sel->cmd == 0) {
		rsa_key_t *args = (rsa_key_t *) input;
		return store_rsa_key(args, output, out_used);
	} else {
		size_t keylen = 0;
		size_t plen = 0;
		rsa_key_exch_t *args = (rsa_key_exch_t *) input;
		load_rsa_key(&n, &e, &d, &p, &q, &dp, &dq, &iq, &keylen, &plen);
		uint8_t *msg = args->data;
		hexdump_var("Encrypted random data", msg, args->msglen);

		/*
		* RSA (CRT) key.  Accepted key sizes depend on exact system
		* specifications, but typically accepted are 2048, 3072
		* and 4096.
		* The members can be optional according to routine;
		* - public keys have n and e
		* - private keys have n, and either (d, e), or
		*   (e, p, q, dp, dq, iq), or all of the elements
		*/
		struct cri_rsa_key key = {
			.bits = keylen * 8, /* bits in key data */
			.flags = 0,	    /* flags, keep at 0 */
			.n = (uint32_t *)n, /* public modulus, bits/8 bytes */
			.e = (uint32_t *)e, /* public exponent, bits/8 bytes */
			.d = NULL,          /* private exponent, bits/8 bytes */
			.p = NULL,	    /* crt prime 1, bits/16 bytes */
			.q = NULL,	    /* crt prime 2, bits/16 bytes */
			.dp = NULL,	    /* crt exponent 1, bits/16 bytes */
			.dq = NULL,	    /* crt exponent 2, bits/16 bytes */
			.iq = NULL	    /* crt coefficient, bits/16 bytes */
		};
		if (plen == 0) {
			key.d = (uint32_t *)d;
		} else { /* crt */
			key.p = (uint32_t *)p;
			key.q = (uint32_t *)q;
			key.dp = (uint32_t *)dp;
			key.dq = (uint32_t *)dq;
			key.iq = (uint32_t *)iq;
		}

		struct cri_oaep_params oaep = {
			.bits = keylen * 8, /* bits in key, 1024,2048,4096,8192 */
			.hlen = 32,	    /* hash algorithm output length in bytes */
			.halgo = 0,	    /* hash core (HC) algorithm identifier to override */
			.label = NULL,	    /* octet string of label */
			.llen = 0	    /* length of label in bytes */
		};

		uint32_t inbuf[RSA_MAX_KEY_BITS/32] = { 0 };
		uint32_t outbuf[RSA_MAX_KEY_BITS/32] = { 0 };

		printk("Load private key:\n");
		cri_pke_t pke = cri_pke_open(0);
		if (cri_is_valid(pke)) {
			cri_reverse(inbuf, msg, keylen);
			if (rsadp(pke, &key, inbuf, outbuf) >= 0) {
				printk("Decrypt random data:\n");
				cri_reverse(outbuf, outbuf, keylen);
				res = cri_oaep_dec(&oaep, outbuf, output);
				if (res >= 0 && output && (size_t)res <= (keylen)) {
					hexdump_var("Encrypted data", output, res);
					printk("Hash encrypted random data and public key:\n");
					memcpy(inbuf, output, res);
					memcpy(((uint8_t *)inbuf) + res, n, keylen);
					memcpy(((uint8_t *)inbuf) + res + keylen, e, keylen);
					size_t input_size = res + keylen + keylen;
					size_t hash_size = oaep.hlen;
					res = hash(&inbuf, &outbuf, &input_size, &hash_size);
					res = sign_hash(&pke, &key, &inbuf, &outbuf, output, out_used, &hash_size);
				}
			}
			cri_pke_close(pke);
		}
	}
	return res;
}

#else

static int rsa_key_exch(void *input, u32_t in_used,
			void *output, u32_t *out_used, u32_t out_size)
{
	printk("RSA not supported for this target\n");
	return -EINVAL;
}

#endif

const cmd_t cmd_rsa_key_exch = { CMDID_RSA_KEY_EXCH, "RSA_KEY_EXCH",
				"Verify host key using RSA key exchange protocol", rsa_key_exch };
