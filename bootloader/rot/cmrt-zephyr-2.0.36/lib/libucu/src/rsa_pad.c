/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <string.h>
#include <stdalign.h>
#include <zephyr.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/tmc.h>
#include <drivers/cmrt/util.h>
#include <cmrt/ucu/rsa_pad.h>


enum {
	SHA_MAX_OUTPUT = 512 / 8, /* sha512 */
	SHA_BUF_SIZE = SHA_MAX_OUTPUT,
	/* The upper limit of slen is bits/8-h-2, which is
	 * 4096/8-28-2=482 bytes.  But it takes half kilo without much
	 * benefit. The typical salt length is the length of hash
	 * (hlen), hence we define max salt length to be
	 * SHA512_OUTPUT_SIZE.
	 */
	PSS_SALT_LEN_MAX = SHA_MAX_OUTPUT,

	MGFBUFSIZE = SHA_MAX_OUTPUT
};


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
	if (!halgo && (hlen == 28u)) {
		return HC_HASH_ALGO_SHA_224;
	}
	for (struct hashinfo const *p = s_hash_algos + 1; p->len; ++p) {
		if (!halgo && (hlen == p->len)) {
			return p->algo;
		}
		if (halgo == p->algo) {
			if (hlen == p->len) {
				return halgo;
			}
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
		if (p->algo == algo) {
			return p->len;
		}
	}
	return 0;
}


/*!
 * Hash state.  Rearranges for input data so that full length buffers
 * are supplied to the driver even if the message itself will not be
 * fully aligned.
 */
struct sha_state {
	cmrt_hc_t hc;
	uint32_t len;
	uint32_t offset;
	uint8_t buffer[SHA_BUF_SIZE];
};


static int sha_init(cmrt_hc_t hc, struct sha_state *sha, uint32_t algo)
{
	if (!cmrt_is_valid(hc)) {
		return -1;
	}
	if (cmrt_hc_init(hc, (cmrt_hash_algo_t)algo, NULL, 0) != 0) {
		return -1;
	}
	memset(sha, 0, sizeof(*sha));
	sha->hc = hc;
	return sha->len = get_hash_len(algo);
}

static int sha_update(struct sha_state *sha, const void *vdata, uint32_t len)
{
	uint32_t offs = 0;
	const uint8_t *data = vdata;

	while ((len > 0u) && (sha->offset + len >= SHA_BUF_SIZE)) {
		/* copy is less than or equal to len */
		uint32_t copy = SHA_BUF_SIZE - sha->offset;

		memcpy(&sha->buffer[sha->offset], &data[offs], copy);
		offs += copy;
		len -= copy;

		if (cmrt_hc_update(sha->hc, sha->buffer, SHA_BUF_SIZE) != 0) {
			return -1;
		}

		sha->offset = 0;
	}

	if (len > 0u) {
		memcpy(sha->buffer + sha->offset, data + offs, len);
		sha->offset += len;
	}

	return 0;
}

static int sha_final(struct sha_state *sha, void *dst)
{
	uint8_t *data = sha->buffer;
	uint32_t len = sha->offset;
	size_t hashlen = sha->len;
	void *pout = dst;
	uint32_t buffer[(SHA_BUF_SIZE + 3) / 4];

	if (((uintptr_t)pout % 4) != 0) {
		pout = buffer;
	}

	int ret = cmrt_hc_final(sha->hc, data, len, pout, &hashlen);
	if ((ret >= 0) && (pout != dst)) {
		memcpy(dst, pout, hashlen);
	}
	memset(sha, 0, sizeof(*sha));
	return ret;
}

static int hash(cmrt_hc_t hc,
		void *dst, uint32_t algo, const void *data, uint32_t len)
{
	struct sha_state sha;

	if (sha_init(hc, &sha, algo) < 0
	    || sha_update(&sha, data, len) < 0
	    || sha_final(&sha, dst) < 0) {
		return -1;
	}

	return 0;
}


static inline uint32_t htonl(uint32_t x)
{
	return (((uint32_t)(x) & 0xff000000u) >> 24) |
		(((uint32_t)(x) & 0x00ff0000u) >> 8) |
		(((uint32_t)(x) & 0x0000ff00u) << 8) |
		(((uint32_t)(x) & 0x000000ffu) << 24);
}

static uint32_t min(uint32_t a, uint32_t b) { return (a < b) ? a : b; }

/*!
 * Structure for MGF1 state.
 */
struct mgf1 {
	cmrt_hc_t hc;
	uint32_t algo;
	uint8_t hlen;	/**< hash length */
	uint8_t offset; /**< offset in this buffer for retrieval */
	uint32_t pad;
	const uint8_t *seed;
	uint32_t nseed;
	uint8_t buffer[MGFBUFSIZE];
};

static int mgf1next(struct mgf1 *mgf)
{
	struct sha_state sha;
	int res = sha_init(mgf->hc, &sha, mgf->algo);
	if (res >= 0) {
		res = sha_update(&sha, mgf->seed, mgf->nseed);
	}
	if (res >= 0) {
		uint32_t pad = htonl(mgf->pad);
		res = sha_update(&sha, &pad, 4);
	}
	if (res >= 0) {
		res = sha_final(&sha, mgf->buffer);
	}
	if (res >= 0) {
		mgf->offset = 0;
		mgf->pad++;
	}
	return res;
}

/*!
 * Initialize mgf1.
 * @param[out] mgf mask generator to initialize
 * @param hc hash core to use; must remain open during all use
 * @param algo hash algorithm
 * @param seed seed for MGF
 * @param nseed seed length
 * @return non-negative for errors
 */
static int mgf1init(struct mgf1 *mgf, cmrt_hc_t hc, uint32_t algo,
		    const uint8_t *seed, uint32_t nseed)
{
	int res = -1;
	size_t hlen = get_hash_len(algo);
	if ((mgf != NULL) && cmrt_is_valid(hc) && (hlen > 0)) {
		mgf->hc = hc;
		mgf->algo = algo;
		mgf->hlen = hlen;
		mgf->offset = 0;
		mgf->pad = 0;
		mgf->seed = seed;
		mgf->nseed = nseed;
		res = mgf1next(mgf);
	}
	return res;
}

/*!
 * Copy a XOR-masked byte stream.
 * @param pout output (may be either \a a or \a b)
 * @param a first input
 * @param b second input
 * @param n number of bytes
 * @return n
 */
static size_t
xorcopy(uint8_t *pout, const uint8_t *a, const uint8_t *b, size_t n)
{
	if ((((uintptr_t)pout | (uintptr_t)a | (uintptr_t)b) & 3u) == 0u) {
		uint32_t *p32 = (uint32_t *)pout;
		const uint32_t *a32 = (const uint32_t *)a;
		const uint32_t *b32 = (const uint32_t *)b;
		size_t i;
		for (i = 0; i + 4 <= n; i += 4) {
			p32[i/4] = a32[i/4] ^ b32[i/4];
		}
		n -= i;
		pout += i;
		a += i;
		b += i;
	}
	for (unsigned i = 0; i < n; ++i) {
		pout[i] = a[i] ^ b[i];
	}
	return n;
}

/*!
*  Apply MGF1 mask to buffer (inplace)
 * @param mgf mask generator initialized with mgf1init()
 * @param obuf masked output buffer
 * @param ibuf input buffer
 * @param nbuf length of buffer in bytes
 * @return negative number of bytes left unprocessed, 0 for success
 */
static int
mgf1f(struct mgf1 *mgf, uint8_t *obuf, uint8_t *ibuf, size_t nbuf)
{
	while (nbuf > 0) {
		if (mgf->offset == mgf->hlen) {
			if (mgf1next(mgf) < 0) {
				break;
			}
		}
		size_t n = min(nbuf, mgf->hlen - mgf->offset);
		(void)xorcopy(obuf, mgf->buffer + mgf->offset, ibuf, n);
		nbuf -= n;
		obuf += n;
		ibuf += n;
		mgf->offset += n;
	}
	return -(int)nbuf;
}

static uint8_t mgf1byte(struct mgf1 *mgf)
{
	if (mgf->offset == mgf->hlen) {
		if (mgf1next(mgf) < 0) {
			return 0;
		}
	}
	return mgf->buffer[mgf->offset++];
}

/*!
 * Mask buffer with MGF1.
 * @param buffer buffer to be xor'ed with MGF1
 * @param hc open handle to hash core to utilize
 * @param seed seed used to initialize the mask
 * @param slen length of \a seed in bytes
 * @param masklen length of \a buffer to mask in bytes
 * @param halgo hash algorithm identifier
 */
static int
mgf1mask(uint8_t *buffer, cmrt_hc_t hc, const uint8_t *seed, uint32_t slen,
	 uint32_t masklen, uint32_t halgo)
{
	struct mgf1 mgf;
	int res = mgf1init(&mgf, hc, halgo, seed, slen);
	if (res >= 0) {
		res  = mgf1f(&mgf, buffer, buffer, masklen);
	}
	return res;
}


int cmrt_oaep_enc(cmrt_hc_t hc,
		  const struct cmrt_oaep_params *params,
		  const void *message, uint32_t mlen,
		  void *dst)
{
	const uint32_t bytes = params->bits / 8u;
	if (!cmrt_is_valid(hc)
	    || (params->hlen > SHA_MAX_OUTPUT)
	    || mlen > (bytes - 2u * params->hlen - 2u)) {
		return -1;
	}
	memset(dst, 0, bytes);

	uint8_t *seed, *db;

	uint32_t hlen = params->hlen;
	int halgo = get_hash_algo(params->halgo, (uint16_t)hlen);
	if (halgo < 0)
		return halgo;

	uint32_t dblen = bytes - hlen - 1u;
	db = (uint8_t *)dst + 1 + hlen;

	if (hash(hc, db, halgo, params->label, params->llen) < 0) {
		return -1;
	}

	seed = (uint8_t *)dst + 1;
	if (cmrt_get_random(seed, hlen) < 0) {
		return -1;
	}

	db[dblen - mlen - 1u] = 0x01;
	memcpy(&db[dblen - mlen], message, mlen);

	/* The size is non-constant */
	int res = mgf1mask(db, hc, seed, hlen, dblen, halgo);
	if (res >= 0) {
		res = mgf1mask(seed, hc, db, dblen, hlen, halgo);
	}

	return res;
}


int cmrt_oaep_dec(cmrt_hc_t hc,
		  const struct cmrt_oaep_params *params,
		  const void *emv, void *message)
{
	const uint8_t *em = emv;
	const uint32_t bytes = params->bits / 8;
	uint32_t mlen = bytes;
	if (!cmrt_is_valid(hc)) {
		return -1;
	}
	if ((params->hlen > SHA_MAX_OUTPUT)
	    || (bytes < (2u * params->hlen + 2))) {
		return -1;
	}

	uint32_t hlen = params->hlen;

	int halgo = get_hash_algo(params->halgo, (uint16_t)hlen);
	if (halgo < 0) {
		return halgo;
	}
	uint32_t dblen = bytes - hlen - 1;
	alignas(4) uint8_t seed[SHA_MAX_OUTPUT];
	const uint8_t *db = em + 1 + hlen;

	memcpy(seed, em + 1, hlen);
	if (mgf1mask(seed, hc, db, dblen, hlen, halgo) < 0) {
		return -1;
	}

	uint8_t lh[SHA_MAX_OUTPUT];

	if (hash(hc, lh, halgo, params->label, params->llen) != 0) {
		return -1;
	}

	struct mgf1 mgf;
	if (mgf1init(&mgf, hc, halgo, seed, hlen) < 0) {
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
	uint32_t good = (em[0] == 0);

	/* compare the hash initially as always in one buffer */
	uint8_t cmp = 0;

	for (uint32_t i = 0; i < hlen; ++i) {
		cmp |= lh[i] ^ db[i] ^ mgf.buffer[i];
	}
	good &= (cmp == 0);
	if (mgf1next(&mgf) < 0) {
		return -1;
	}

	uint32_t mstart = 0; /* message start index */
	uint32_t found_one = 0;
	uint32_t tlen; /* tail length, i.e. the real message length */
	uint8_t *to = message;

	for (uint32_t i = hlen; i < dblen; ++i) {
		uint8_t x = db[i] ^ mgf1byte(&mgf);
		uint32_t e0 = (x == 0);
		uint32_t e1 = (x == 1);

		*to = x;
		to += found_one;
		mstart = (!found_one && e1) ? (i + 1) : mstart;
		found_one |= e1;
		good &= (found_one | e0);
	}

	good &= found_one;
	tlen = dblen - mstart;
	good &= (mlen >= tlen);

	return good ? tlen : (uint32_t)-1;
}


int cmrt_pss_enc(cmrt_hc_t hc,
		 const struct cmrt_pss_params *params,
		 const void *message, size_t mlen,
		 void *dst)
{
	const uint32_t embits = params->bits - 1; /* was embits */
	const uint32_t emlen = params->bits / 8; /* was params->emlen; */
	const uint32_t hlen = params->hlen;
	const uint32_t slen = params->slen;
	const int halgo = get_hash_algo(params->halgo, hlen);

	if (!cmrt_is_valid(hc)) {
		return -1;
	}
	if ((halgo < 0) || (slen > PSS_SALT_LEN_MAX) || (emlen < (hlen + slen + 2))) {
		return -1;
	}

	/* The padding1 is 8 bytes of zero */
	alignas(4) uint8_t ps[(8+64+PSS_SALT_LEN_MAX)] = { 0 };

	uint8_t *mhash = ps + 8;
	uint8_t *salt = mhash + hlen;

	if (params->flags & CMRT_PSS_PREHASHED) {
		if (mlen != hlen) {
			return -1;
		}
		memcpy(mhash, message, mlen);
	} else if (hash(hc, mhash, halgo, message, mlen) < 0) {
		return -1;
	}

	/* slen may be zero */
	if ((slen > 0) && (cmrt_get_random(salt, slen) < 0)) {
		return -1;
	}

	const uint32_t pslen = emlen - slen - hlen - 2;
	const uint32_t dblen = pslen + 1 + slen;
	uint8_t *db = dst;
	uint8_t *h = db + dblen;

	memset(dst, 0, pslen);

	/* DB = PS || 0x01 || salt */
	db[pslen] = 0x01;
	if (slen > 0u) {
		memcpy(&db[pslen + 1], salt, slen);
	}

	if (hash(hc, h, halgo, ps, 8 + hlen + slen) < 0) {
		return -1;
	}

	int res = -1;
	if (mgf1mask(db, hc, h, hlen, dblen, halgo) >= 0) {
		db[emlen - 1] = 0xbc;
		/* Set the leftmost 8emLen - emBits bits of the
		 * leftmost octet in maskedDB to zero.
		 */
		unsigned int octets = (8u * emlen - embits) / 8u;
		unsigned int bits = (8u * emlen - embits) % 8u;
		memset(db, 0, octets);
		db[octets] &= (1u << (8u - bits)) - 1u;
		res = 0;
	}

	return res;
}


int cmrt_pss_verify(cmrt_hc_t hc,
		    const struct cmrt_pss_params *params,
		    const void *message, size_t mlen, void *pem)
{
	uint8_t *em = pem;
	const uint32_t embits = params->bits; /* was embits */
	const uint32_t emlen = embits / 8u; /* params->emlen; */
	const uint32_t hlen = params->hlen;
	const uint32_t slen = params->slen;
	const int halgo = get_hash_algo(params->halgo, hlen);

	if (!cmrt_is_valid(hc)) {
		return -1;
	}
	if ((halgo < 0) || (slen > PSS_SALT_LEN_MAX) ||
	    emlen < hlen + slen + 2u) {
		return -1;
	}
	if (em[emlen - 1u] != 0xbcu) {
		return -1;
	}

	const uint32_t pslen = emlen - slen - hlen - 2u;
	const uint32_t dblen = pslen + 1u + slen;
	uint8_t *db = em;

	/* Check the leftmost 8emLen - emBits bits of the leftmost octet
	 * in DB value.
	 */
	unsigned int octets = (8u * emlen - embits) / 8u;
	unsigned int bits = (8u * emlen - embits) % 8u;

	for (unsigned int i = 0; i < octets; ++i) {
		if (db[i] != 0) {
			return -1;
		}
	}

	if (bits > 0u) {
		uint8_t x = (1u << (8 - bits)) - 1;
		if ((db[octets] & x) != db[octets]) {
			return -1;
		}
	}

	const uint8_t *em_hash = em + dblen;
	if (mgf1mask(db, hc, em_hash, hlen, dblen, halgo) < 0) {
		return -1;
	}

	/* Again, set leftmost 8emLen - emBits bits of the leftmost octet
	 * of DB to zero.
	 */
	memset(db, 0, octets);
	db[octets] &= (1u << (8 - bits)) - 1u;

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

	alignas(4) uint8_t ps[8 + 64 + PSS_SALT_LEN_MAX] = { 0 };

	uint8_t *em_salt = &db[pslen + 1];
	uint8_t *mhash = ps + 8;
	uint8_t *salt = mhash + hlen;

	if (slen > 0u) {
		memcpy(salt, em_salt, slen);
	}

	if ((params->flags & CMRT_PSS_PREHASHED) != 0) {
		if (mlen != hlen) {
			return -1;
		}
		memcpy(mhash, message, mlen);
	} else if (hash(hc, mhash, halgo, message, mlen) < 0) {
		return -1;
	} else {
		/* empty */
	}

	alignas(4) uint8_t hprime[SHA_MAX_OUTPUT];

	if (hash(hc, hprime, halgo, ps, 8u + hlen + slen) < 0) {
		return -1;
	}

	for (uint32_t i = 0; i < hlen; ++i) {
		if (hprime[i] != em_hash[i]) {
			return -1;
		}
	}

	return 0;
}
