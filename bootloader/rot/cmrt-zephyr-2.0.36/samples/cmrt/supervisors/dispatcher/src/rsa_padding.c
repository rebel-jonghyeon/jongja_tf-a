/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <string.h>
#include <stdalign.h>
#include <cri/cmrt.h>
#include "cri/cmrt/hc.h"
#include "cri/cmrt/tmc.h"

#include "libpad.h"


enum {
	SHA_MAX_OUTPUT = 512 / 8, /* sha512 */
	RSA_MAX_KEY_SIZE = 8192
};


static int trng_generate(void *dst, uint32_t len)
{
	int res;

	cri_tmc_t tmc = cri_tmc_open(CRI_O_SYNC);
	if (!cri_is_valid(tmc)) {
		return -1;
	}

	res = cri_tmc_generate(tmc, dst, len >= 32 ? 32 : len);
	if (res != 0) {
		goto out;
	}

#define __do_reseed(_size) do {			\
	dst += 32; \
	res = cri_tmc_reseed(tmc, dst, (_size)); \
	if (res != 0) { \
		goto out; \
	} \
} while (0)

	uint32_t a = len >> 5;
	uint32_t b = len % 32;

	for (uint32_t i = 0; i + 1 < a; ++i) {
		__do_reseed(32);
	}
	if (a && b) {
		__do_reseed(b);
	}

out:
	cri_tmc_close(tmc);
	return res;
}


static const struct hashinfo {
	uint16_t algo;
	uint8_t len;
} s_hash_algos[] = {
	{ HC_HASH_ALGO_SHA_224, 224 / 8 }, /* 0, complicates */
	{ HC_HASH_ALGO_SHA_256, 256 / 8 },
	{ HC_HASH_ALGO_SHA_384, 384 / 8 },
	{ HC_HASH_ALGO_SHA_512, 512 / 8 },
	{ HC_HASH_ALGO_SHA_512_224, 224 / 8 },
	{ HC_HASH_ALGO_SHA_512_256, 256 / 8 },
	{ HC_HASH_ALGO_SHA3_224, 224 / 8 },
	{ HC_HASH_ALGO_SHA3_256, 256 / 8 },
	{ HC_HASH_ALGO_SHA3_384, 384 / 8 },
	{ HC_HASH_ALGO_SHA3_512, 512 / 8 },
	{ 0 }
};


static int get_hash_algo(uint16_t halgo, uint16_t hlen)
{
	if (!halgo && hlen == 28)
		return HC_HASH_ALGO_SHA_224;
	for (struct hashinfo const *p = s_hash_algos + 1; p->len; ++p) {
		if (!halgo && hlen == p->len) {
			return p->algo;
		}
		if (halgo == p->algo) {
			if (hlen == p->len)
				return halgo;
			return -1; /* invalid length specified */
		}
	}
	return -1; /* invalid value */
}


/*!
 * Digest length for algorithm.
 * @param algo HC algorithm identifier
 * @return digest length in bytes or 0 if unknown
 */
static uint32_t get_hash_len(uint32_t algo)
{
	for (struct hashinfo const *p = s_hash_algos; p->len; ++p) {
		if (p->algo == algo)
			return p->len;
	}
	return 0;
}


#define SHA_BUF_SIZE 64

static uint8_t __shab[SHA_BUF_SIZE];
static uint32_t __shab_offs;
static uint32_t __shalen;
static cri_hc_t __shahandle;


static int sha_init(uint32_t algo)
{
	cri_hc_t hc = cri_hc_open(0);
	if (!cri_is_valid(hc)) {
		return -1;
	}

	if (cri_hc_init(hc, algo, NULL, 0) != 0) {
		cri_hc_close(hc);
		return -1;
	}
	__shahandle = hc;

	memset(__shab, 0, sizeof(__shab));
	__shab_offs = 0;
	__shalen = get_hash_len(algo);

	return 0;
}

static int sha_update(const void *data, uint32_t len)
{
	uint32_t offs = 0;

	while (len && __shab_offs + len >= SHA_BUF_SIZE) {
		/* copy is less than or equal to len */
		uint32_t copy = SHA_BUF_SIZE - __shab_offs;

		memcpy(__shab + __shab_offs, data + offs, copy);
		offs += copy;
		len -= copy;

		if (cri_hc_update(__shahandle, __shab, SHA_BUF_SIZE) != 0) {
			cri_hc_close(__shahandle);
			return -1;
		}

		__shab_offs = 0;
	}

	if (len) {
		memcpy(__shab + __shab_offs, data + offs, len);
		__shab_offs += len;
	}

	return 0;
}

static int sha_final(void *dst)
{
	int ret = -1;
	uint8_t *data = NULL;
	uint32_t len = 0;
	uint32_t hashlen = __shalen;
	uint8_t buf[SHA_MAX_OUTPUT];

	if (__shab_offs) {
		if (cri_hc_update(__shahandle, __shab, __shab_offs & ~3UL) != 0) {
			goto out;
		}
		data = __shab + (__shab_offs & ~3UL);
		len = __shab_offs & 3UL;
	}

	ret = cri_hc_final(__shahandle, data, len, buf, &hashlen);
	if (ret == 0) {
		memcpy(dst, buf, __shalen);
	}

out:
	cri_hc_close(__shahandle);
	return ret;
}

#define htonl(x) \
	((((uint32_t)(x) & 0xff000000) >> 24) | \
	(((uint32_t)(x) & 0x00ff0000) >> 8) | \
	(((uint32_t)(x) & 0x0000ff00) << 8) | \
	(((uint32_t)(x) & 0x000000ff) << 24))

static const uint8_t *
mgf1(const uint8_t *seed, uint32_t slen, uint32_t masklen, uint32_t halgo)
{
	/* An extra SHA_MAX_OUTPUT in case the masklen is not divisible by hlen. */
	static uint8_t mgf_output_buf[RSA_MAX_KEY_SIZE / 8 + SHA_MAX_OUTPUT];

	uint32_t len = 0;
	uint8_t *output;

	if (masklen > sizeof(mgf_output_buf))
		return NULL;

	memset(mgf_output_buf, 0, sizeof(mgf_output_buf));
	output = mgf_output_buf;

	/* According to pkcs-1v2-1, section A.2.3, page 43,
	 * the maskGenAlgorithm is recommended to be the same
	 * as hashAlgorithm. The default is SHA1.
	 */
	uint32_t hlen = get_hash_len(halgo);
	for (uint32_t i = 0; len < masklen; ++i) {
		uint32_t pad = htonl(i);

		if (sha_init(halgo) ||
				sha_update(seed, slen) ||
				sha_update(&pad, 4)) {
			return NULL;
		}

		if (sha_final(output + len))
			return NULL;
		len += hlen;
	}

	return mgf_output_buf;
}

static int do_quick_hash(void *dst, uint32_t hcid, const void *data, uint32_t len)
{
	if (sha_init(hcid) ||
			sha_update(data, len) ||
			sha_final(dst))
		return -1;

	return 0;
}


int cri_oaep_enc(const struct cri_oaep_params *params,
		 const void *message, uint32_t mlen,
		 void *dst)
{
	const uint32_t bytes = params->bits / 8;
	if (params->hlen > SHA_MAX_OUTPUT
	    || mlen > bytes - 2 * params->hlen - 2) {
		return -1;
	}
	memset(dst, 0, bytes);

	uint8_t *seed, *db;
	uint32_t dblen, hlen;

	hlen = params->hlen;
	int halgo = get_hash_algo(params->halgo, (uint16_t)hlen);
	if (halgo < 0)
		return halgo;

	dblen = bytes - hlen - 1;
	db = (uint8_t *)dst + 1 + hlen;

	if (do_quick_hash(db, halgo, params->label, params->llen) != 0) {
		return -1;
	}

	seed = (uint8_t *)dst + 1;
	if (trng_generate(seed, hlen) != 0)
		return -1;

	db[dblen - mlen - 1] = 0x01;
	memcpy(&db[dblen - mlen], message, mlen);

	const uint8_t *mask = mgf1(seed, hlen, dblen, halgo);

	if (!mask)
		return -1;

	for (uint32_t i = 0; i < dblen; ++i) {
		db[i] ^= mask[i];
	}
	mask = mgf1(db, dblen, hlen, halgo);
	for (uint32_t i = 0; i < hlen; ++i) {
		seed[i] ^= mask[i];
	}

	return 0;
}

int cri_oaep_dec(const struct cri_oaep_params *params, const void *em, void *message)
{
	const uint32_t bytes = params->bits / 8;
	uint32_t mlen = bytes;
	if (params->hlen > SHA_MAX_OUTPUT || bytes < 2u * params->hlen + 2) {
		return -1;
	}

	uint8_t *db, *seed;
	uint32_t dblen, hlen = params->hlen;

	int halgo = get_hash_algo(params->halgo, (uint16_t)hlen);
	if (halgo < 0)
		return halgo;
	dblen = bytes - hlen - 1;
	seed = (uint8_t *)em + 1;
	db = (uint8_t *)em + 1 + hlen;

	const uint8_t *mask = mgf1(db, dblen, hlen, halgo);

	for (uint32_t i = 0; i < hlen; ++i) {
		seed[i] ^= mask[i];
	}
	mask = mgf1(seed, hlen, dblen, halgo);
	for (uint32_t i = 0; i < dblen; ++i) {
		db[i] ^= mask[i];
	}

	uint8_t lh[SHA_MAX_OUTPUT];

	if (do_quick_hash(lh, halgo, params->label, params->llen) != 0) {
		return -1;
	}

	/* verify.
	 * The first byte should be zero.
	 * The padding in db between [hlen, dblen-mlen-2] must be zeros.
	 * The db[dblen-mlen-1] is 1.
	 * And the rest is message.
	 */

	/* timing side-channel attack */

	/* good is either 1 or 0 */
	uint32_t good = (seed[-1] == 0);
	uint32_t mstart = 0; /* message start index */
	uint32_t found_one = 0;
	uint32_t tlen; /* tail length, i.e. the real message length */

	for (uint32_t i = hlen; i < dblen; ++i) {
		uint32_t e0 = (db[i] == 0);
		uint32_t e1 = (db[i] == 1);

		mstart = (!found_one && e1) ? (i + 1) : mstart;
		found_one |= e1;
		good &= (found_one | e0);
	}

	good &= found_one;
	tlen = dblen - mstart;
	good &= (mlen >= tlen);

	/* Then compare the hash */
	uint8_t cmp = 0;

	for (uint32_t i = 0; i < hlen; ++i) {
		cmp |= lh[i] ^ db[i];
	}
	good &= (cmp == 0);

	uint8_t *src = db + mstart;
	uint8_t *to = message;
	/* msg_mask is either 0 or -1.
	 * It should be 0 if everything is good.
	 * Otherwise it is -1.
	 */
	uint32_t msg_mask = good - 1;

	/* In any case fill mlen bytes. */
	for (uint32_t i = 0; i < mlen; ++i) {
		uint32_t eq = i ^ tlen;

		eq = ~eq & (eq - 1);
		eq = 0 - (eq >> 31);
		/* eq is either -1 or 0 */

		/* If mlen is less than tlen, src is wrapped around.
		 * Otherwise src is not changed.
		 */
		src -= dblen & eq;
		/* If everything is good, copy from `src` to `to`,
		 * otherwise fill some broken data to `to`.
		 * Note that msg_mask is initialized to 0 if it is good.
		 * So it remains 0 here.
		 * The work here keeps the same memory access pattern
		 * no matter the verification is successful or not.
		 */
		msg_mask &= msg_mask ^ eq;
		to[i] = (msg_mask & to[i]) | (~msg_mask & src[i]);
	}

	return good ? tlen : (uint32_t)-1;
}

/* MPrime is buffer for PSS. The first 8 bytes are padding.
 * The reset is preserved for hash and salt, len of which depends
 * on input params.
 *
 * The longest hash (SHA512) is 64 bytes.
 *
 * The upper limit of slen is bits/8-h-2, which is 4096/8-28-2=482 bytes.
 * But it takes half kilo without much benefit. The typical salt length
 * is the length of hash (hlen), hence  we define max salt length to be
 * SHA512_OUTPUT_SIZE.
 */
#define PSS_SALT_LEN_MAX SHA_MAX_OUTPUT

int cri_pss_enc(const struct cri_pss_params *params,
		const void *message, size_t mlen,
		void *dst)
{
	const uint32_t embits = params->bits - 1; /* was embits */
	const uint32_t emlen = params->bits / 8; /* was params->emlen; */
	const uint32_t hlen = params->hlen;
	const uint32_t slen = params->slen;
	const int halgo = get_hash_algo(params->halgo, hlen);

	if (halgo < 0 || slen > PSS_SALT_LEN_MAX || emlen < hlen + slen + 2) {
		return -1;
	}

	/* The padding1 is 8 bytes of zero */
	alignas(4) uint8_t ps[(8+64+PSS_SALT_LEN_MAX)] = { 0 };

	uint8_t *mhash = ps + 8;
	uint8_t *salt = mhash + hlen;

	if (params->flags & CRI_PSS_PREHASHED) {
		if (mlen != hlen) {
			return -1;
		}
		memcpy(mhash, message, mlen);
	} else if (do_quick_hash(mhash, halgo, message, mlen) < 0) {
		return -1;
	}

	/* slen may be zero */
	if (slen && trng_generate(salt, slen) != 0) {
		return -1;
	}

	const uint32_t pslen = emlen - slen - hlen - 2;
	const uint32_t dblen = pslen + 1 + slen;
	uint8_t *db = dst;
	uint8_t *h = dst + dblen;

	memset(dst, 0, pslen);

	/* DB = PS || 0x01 || salt */
	db[pslen] = 0x01;
	if (slen) {
		memcpy(&db[pslen + 1], salt, slen);
	}

	if (do_quick_hash(h, halgo, ps, 8 + hlen + slen)) {
		return -1;
	}

	const uint8_t *mask = mgf1(h, hlen, dblen, halgo);

	for (uint32_t i = 0; i < dblen; ++i) {
		db[i] ^= mask[i];
	}

	db[emlen - 1] = 0xbc;

	/* Set the leftmost 8emLen - emBits bits of the leftmost octet
	 * in maskedDB to zero.
	 */
	int octets = (8 * emlen - embits) / 8;
	int bits = (8 * emlen - embits) % 8;
	memset(db, 0, octets);
	db[octets] &= (1u << (8 - bits)) - 1;

	return 0;
}


int cri_pss_verify(const struct cri_pss_params *params, const void *message, size_t mlen, void *pem)
{
	uint8_t *em = pem;
	const uint32_t embits = params->bits; /* was embits */
	const uint32_t emlen = embits / 8; /* params->emlen; */
	const uint32_t hlen = params->hlen;
	const uint32_t slen = params->slen;
	const int halgo = get_hash_algo(params->halgo, hlen);

	if (halgo < 0 || slen > PSS_SALT_LEN_MAX || emlen < hlen + slen + 2) {
		return -1;
	}
	if (em[emlen - 1] != 0xbc) {
		return -1;
	}

	const uint32_t pslen = emlen - slen - hlen - 2;
	const uint32_t dblen = pslen + 1 + slen;
	uint8_t *db = em;

	/* Check the leftmost 8emLen - emBits bits of the leftmost octet
	 * in DB value.
	 */
	int octets = (8 * emlen - embits) / 8;
	int bits = (8 * emlen - embits) % 8;

	for (int i = 0; i < octets; ++i) {
		if (db[i] != 0) {
			return -1;
		}
	}

	if (bits) {
		uint8_t x = (1u << (8 - bits)) - 1;
		if ((db[octets] & x) != db[octets]) {
			return -1;
		}
	}

	const uint8_t *em_hash = em + dblen;
	const uint8_t *mask = mgf1(em_hash, hlen, dblen, halgo);

	for (uint32_t i = 0; i < dblen; ++i) {
		db[i] ^= mask[i];
	}

	/* Again, set leftmost 8emLen - emBits bits of the leftmost octet
	 * of DB to zero.
	 */
	memset(db, 0, octets);
	db[octets] &= (1u << (8 - bits)) - 1;

	/* The emLen - hLen - sLen - 2 leftmost octets of DB must be zero.
	 * The emLen - hLen - sLen - 1 char must be 0x01.
	 */
#if 0
	/* Although RFC 8017 requires PS field to be all zeros, the PSS
	 * encoding and verification in openssl doesn't follow it. Somehow
	 * openssl sets MSB 1bit in the generated signature. We chose to
	 * follow openssl due the the fact that it is de-facto standard in
	 * industry.
	 *
	 * Note that this choice may not conform to FIPS.
	 */
	for (uint32_t i = 0; i < pslen; ++i) {
		if (db[i] != 0) {
			return -1;
		}
	}
#endif
	if (db[pslen] != 0x01) {
		return -1;
	}

	alignas(4) uint8_t ps[(8+64+PSS_SALT_LEN_MAX)] = { 0 };

	uint8_t *em_salt = &db[pslen + 1];
	uint8_t *mhash = ps + 8;
	uint8_t *salt = mhash + hlen;

	if (slen) {
		memcpy(salt, em_salt, slen);
	}

	if (params->flags & CRI_PSS_PREHASHED) {
		if (mlen != hlen) {
			return -1;
		}
		memcpy(mhash, message, mlen);
	} else if (do_quick_hash(mhash, halgo, message, mlen)) {
		return -1;
	}

	uint8_t hprime[SHA_MAX_OUTPUT];

	if (do_quick_hash(hprime, halgo, ps, 8 + hlen + slen)) {
		return -1;
	}

	for (uint32_t i = 0; i < hlen; ++i) {
		if (hprime[i] != em_hash[i]) {
			return -1;
		}
	}

	return 0;
}
