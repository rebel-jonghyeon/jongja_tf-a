/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <errno.h>
#include <stdalign.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sys/byteorder.h>

#include <drivers/cmrt/hc.h>
#include <cmrt/shsig/xmss.h>
#include "xmss_int.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define ntohl(x) sys_be32_to_cpu(x)
#define htonl(x) sys_cpu_to_be32(x)
#define htons(x) ((uint16_t) ((((x) >> 8u) & 0xffu) | (((x) & 0xffu) << 8u)))
enum {
#ifdef CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES
	MAX_OTS_N = 64,
	MAX_OTS_LEN = 131,
#else
	MAX_OTS_N = 32,
	MAX_OTS_LEN = 67,
#endif
};

typedef struct __attribute__((__packed__)) {
	uint32_t layer;
	uint64_t tree;
	uint32_t type;		/* 0, 1, 2 */
	uint32_t ots;		/* ltree   padding */
	uint32_t chain;		/* height  height */
	uint32_t hash;		/* index   index */
	uint32_t keymask;
} xmss_ots_addr;

typedef xmss_ots_addr xmss_ltree_addr;
typedef xmss_ots_addr xmss_htree_addr;

typedef struct {
	xmss_ots_addr   ots;
	xmss_ltree_addr ltree;
	xmss_ltree_addr hash;
} xmss_addr;

static inline uint32_t index_length(int height, int layer)
{
	uint32_t len = (layer == 1) ? 4 : ((height * layer) + 7) / 8;
	return len;
}

static uint64_t decode_index(const void *data, uint32_t len)
{
	const uint8_t *p = data;
	uint64_t ret = 0;

	for (uint32_t i = 0; i < len; ++i) {
		ret |= ((uint64_t)p[i]) << (8u * (len - 1u - i));
	}

	return ret;
}

static void encode_index(void *data, uint32_t len, uint64_t idx)
{
	uint8_t *p = data;

	for (int i = len - 1; i >= 0; --i) {
		p[i] = idx & 0xffu;
		idx >>= 8u;
	}
}

static void sha2_256(cmrt_hc_t hc, int b, void *dig, const void *key, uint32_t klen, const void *msg, uint32_t mlen)
{
	alignas(4) uint8_t bs[32] = {0};
	bs[31] = b;

	int res = cmrt_hc_init(hc, HC_HASH_ALGO_SHA_256, NULL, 0);
	if (res) {
		LOG_ERR("Cannot init HC: %d\n", res);
	}
	res = cmrt_hc_update(hc, bs, sizeof(bs));
	if (res) {
		LOG_ERR("Cannot update bs: %d\n", res);
	}
	res = cmrt_hc_update(hc, key, klen);
	if (res) {
		LOG_ERR("Cannot update key: %d\n", res);
	}
	size_t dlen = 32u;
	res = cmrt_hc_final(hc, msg, mlen, dig, &dlen);
	if (res) {
		LOG_ERR("Cannot final hash: %d\n", res);
	}
}

static void sha2_256_f(cmrt_hc_t hc, void *dig, const void *key, const void *msg)
{
	sha2_256(hc, 0, dig, key, 32u, msg, 32u);
}

static void sha2_256_h(cmrt_hc_t hc, void *dig, const void *key, const void *msg)
{
	sha2_256(hc, 1, dig, key, 32u, msg, 32u * 2u);
}

static void sha2_256_h_msg(cmrt_hc_t hc, void *dig, const void *r, const void *root, uint64_t idx, const void *msg, uint32_t mlen)
{
	uint32_t key[3 * 8];

	(void)memset(key, 0, sizeof(key));
	(void)memcpy(key, r, 32u);
	(void)memcpy(key + 8u, root, 32u);
	encode_index(key + 16u, 32u, idx);
	sha2_256(hc, 2, dig, key, sizeof(key), msg, mlen);
}

static void sha2_256_prf(cmrt_hc_t hc, void *dig, const void *key, const void *addr)
{
	uint32_t msg[8];
	const uint32_t *a = addr;

	for (unsigned int i = 0; i < 8u; ++i) {
		msg[i] = htonl(a[i]);
	}
	sha2_256(hc, 3, dig, key, 32u, msg, sizeof(msg));
}

#ifdef CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES
static void sha2_512(cmrt_hc_t hc, int b, void *dig, const void *key, uint32_t klen, const void *msg, uint32_t mlen)
{
	alignas(4) uint8_t bs[64] = {0};
	bs[63] = b;
	int res = cmrt_hc_init(hc, HC_HASH_ALGO_SHA_512, NULL, 0);
	if (res) {
		LOG_ERR("Cannot init HC: %d\n", res);
	}
	res = cmrt_hc_update(hc, bs, sizeof(bs));
	if (res) {
		LOG_ERR("Cannot update bs: %d\n", res);
	}
	res = cmrt_hc_update(hc, key, klen);
	if (res) {
		LOG_ERR("Cannot update key: %d\n", res);
	}
	size_t dlen = 64u;
	res = cmrt_hc_final(hc, msg, mlen, dig, &dlen);
	if (res) {
		LOG_ERR("Cannot final hash: %d\n", res);
	}
}
static void sha2_512_f(cmrt_hc_t hc, void *dig, const void *key, const void *msg)
{
	sha2_512(hc, 0, dig, key, 64u, msg, 64u);
}

static void sha2_512_h(cmrt_hc_t hc, void *dig, const void *key, const void *msg)
{
	sha2_512(hc, 1, dig, key, 64u, msg, 64u * 2u);
}

static void sha2_512_h_msg(cmrt_hc_t hc, void *dig, const void *r, const void *root, uint64_t idx, const void *msg, uint32_t mlen)
{
	uint64_t key[3 * 8];

	(void)memset(key, 0, sizeof(key));
	(void)memcpy(key, r, 64u);
	(void)memcpy(key + 8u, root, 64u);
	encode_index(key + 16u, 64u, idx);
	sha2_512(hc, 2, dig, key, sizeof(key), msg, mlen);
}

static void sha2_512_prf(cmrt_hc_t hc, void *dig, const void *key, const void *addr)
{
	uint32_t msg[8];
	const uint32_t *a = addr;

	for (unsigned int i = 0; i < 8u; ++i) {
		msg[i] = htonl(a[i]);
	}
	sha2_512(hc, 3, dig, key, 64u, msg, sizeof(msg));
}

static void shake_128(cmrt_hc_t hc, int b, void *dig, const void *key, uint32_t klen, const void *msg, uint32_t mlen)
{
	alignas(4) uint8_t bs[32] = {0};
	bs[31] = b;
	int res = cmrt_hc_init(hc, HC_HASH_ALGO_SHAKE128, NULL, 0);
	if (res) {
		LOG_ERR("Cannot init HC: %d\n", res);
	}
	res = cmrt_hc_update(hc, bs, sizeof(bs));
	if (res) {
		LOG_ERR("Cannot update bs: %d\n", res);
	}
	res = cmrt_hc_update(hc, key, klen);
	if (res) {
		LOG_ERR("Cannot update key: %d\n", res);
	}
	size_t dlen = 32;
	res = cmrt_hc_final(hc, msg, mlen, dig, &dlen);
	if (res) {
		LOG_ERR("Cannot final hash: %d\n", res);
	}
}

static void shake_256_f(cmrt_hc_t hc, void *dig, const void *key, const void *msg)
{
	shake_128(hc, 0, dig, key, 32u, msg, 32u);
}

static void shake_256_h(cmrt_hc_t hc, void *dig, const void *key, const void *msg)
{
	shake_128(hc, 1, dig, key, 32u, msg, 32u * 2u);
}

static void shake_256_h_msg(cmrt_hc_t hc, void *dig, const void *r, const void *root, uint64_t idx, const void *msg, uint32_t mlen)
{
	uint32_t key[3 * 8];

	(void)memset(key, 0, sizeof(key));
	(void)memcpy(key, r, 32u);
	(void)memcpy(key + 8u, root, 32u);
	encode_index(key + 16u, 32u, idx);
	shake_128(hc, 2, dig, key, sizeof(key), msg, mlen);
}

static void shake_256_prf(cmrt_hc_t hc, void *dig, const void *key, const void *addr)
{
	uint32_t msg[8];
	const uint32_t *a = addr;

	for (unsigned int i = 0; i < 8u; ++i) {
		msg[i] = htonl(a[i]);
	}
	shake_128(hc, 3, dig, key, 32u, msg, sizeof(msg));
}

static void shake_256(cmrt_hc_t hc, int b, void *dig, const void *key, uint32_t klen, const void *msg, uint32_t mlen)
{
	alignas(4) uint8_t bs[64] = {0};
	bs[63] = b;
	int res = cmrt_hc_init(hc, HC_HASH_ALGO_SHAKE256, NULL, 0);
	if (res) {
		LOG_ERR("Cannot init HC: %d\n", res);
	}
	res = cmrt_hc_update(hc, bs, sizeof(bs));
	if (res) {
		LOG_ERR("Cannot update bs: %d\n", res);
	}
	res = cmrt_hc_update(hc, key, klen);
	if (res) {
		LOG_ERR("Cannot update key: %d\n", res);
	}
	size_t dlen = 64u;
	res = cmrt_hc_final(hc, msg, mlen, dig, &dlen);
	if (res) {
		LOG_ERR("Cannot final hash: %d\n", res);
	}
}

static void shake_512_f(cmrt_hc_t hc, void *dig, const void *key, const void *msg)
{
	shake_256(hc, 0, dig, key, 64u, msg, 64u);
}

static void shake_512_h(cmrt_hc_t hc, void *dig, const void *key, const void *msg)
{
	shake_256(hc, 1, dig, key, 64u, msg, 64u * 2u);
}

static void shake_512_h_msg(cmrt_hc_t hc, void *dig, const void *r, const void *root, uint64_t idx, const void *msg, uint32_t mlen)
{
	uint64_t key[3 * 8];

	(void)memset(key, 0, sizeof(key));
	(void)memcpy(key, r, 64u);
	(void)memcpy(key + 8u, root, 64u);
	encode_index(key + 16u, 64u, idx);
	shake_256(hc, 2, dig, key, sizeof(key), msg, mlen);
}

static void shake_512_prf(cmrt_hc_t hc, void *dig, const void *key, const void *addr)
{
	uint32_t msg[8];
	const uint32_t *a = addr;

	for (unsigned int i = 0; i < 8u; ++i) {
		msg[i] = htonl(a[i]);
	}
	shake_256(hc, 3, dig, key, 64u, msg, sizeof(msg));
}
#endif

cmrt_xmss_algorithm_type cmrt_xmss_get_type(const uint8_t *pk)
{
	if (pk != NULL) {
		uint32_t type = ntohl(*(uint32_t *)pk);
		if ((type >= XMSS_SHA2_10_256) &&
#ifdef CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES
		    (type <= XMSS_SHAKE_20_512))
#else
		    (type <= XMSS_SHA2_20_256))
#endif
		{
			return (cmrt_xmss_algorithm_type)type;
		}
	}
	return XMSS_RESERVED;
}

cmrt_hash_algo_t cmrt_xmss_get_hash_algo(cmrt_xmss_algorithm_type xmss_type)
{
	switch(xmss_type) {
	case XMSS_SHA2_10_256:
	case XMSS_SHA2_16_256:
	case XMSS_SHA2_20_256:
		return CMRT_HASH_SHA256;
#ifdef CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES
	case XMSS_SHA2_10_512:
	case XMSS_SHA2_16_512:
	case XMSS_SHA2_20_512:
		return CMRT_HASH_SHA512;
	case XMSS_SHAKE_10_256:
	case XMSS_SHAKE_16_256:
	case XMSS_SHAKE_20_256:
		return CMRT_HASH_SHAKE128;
	case XMSS_SHAKE_10_512:
	case XMSS_SHAKE_16_512:
	case XMSS_SHAKE_20_512:
#endif
	default:
		break;
	}
	/* there is no invalid cmrt_hash_algo_t */
	return CMRT_HASH_SHAKE256;
}

const cmrt_xmss_param_t *cmrt_xmss_load_param(cmrt_xmss_algorithm_type atype)
{
	static const cmrt_xmss_param_t xmss_parms[] = {
		{ XMSS_SHA2_10_256,  WOTSP_SHA2_256,  1u, 10u, 32u },
		{ XMSS_SHA2_16_256,  WOTSP_SHA2_256,  1u, 16u, 32u },
		{ XMSS_SHA2_20_256,  WOTSP_SHA2_256,  1u, 20u, 32u },
#ifdef CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES
		{ XMSS_SHA2_10_512,  WOTSP_SHA2_512,  1u, 10u, 64u },
		{ XMSS_SHA2_16_512,  WOTSP_SHA2_512,  1u, 16u, 64u },
		{ XMSS_SHA2_20_512,  WOTSP_SHA2_512,  1u, 20u, 64u },
		{ XMSS_SHAKE_10_256, WOTSP_SHAKE_256, 1u, 10u, 32u },
		{ XMSS_SHAKE_16_256, WOTSP_SHAKE_256, 1u, 16u, 32u },
		{ XMSS_SHAKE_20_256, WOTSP_SHAKE_256, 1u, 20u, 32u },
		{ XMSS_SHAKE_10_512, WOTSP_SHAKE_512, 1u, 10u, 64u },
		{ XMSS_SHAKE_16_512, WOTSP_SHAKE_512, 1u, 16u, 64u },
		{ XMSS_SHAKE_20_512, WOTSP_SHAKE_512, 1u, 20u, 64u }
#endif
	};
	for (unsigned int i = 0; i < sizeof(xmss_parms)/sizeof(cmrt_xmss_param_t); ++i) {
		const cmrt_xmss_param_t *p = &xmss_parms[i];
		if (p->atype == atype) {
			return p;
		}
	}
	return NULL;
}

const cmrt_xmss_ots_param_t *cmrt_xmss_load_ots_parm(cmrt_xmss_ots_type otstype)
{
	static const cmrt_xmss_ots_param_t parm_sha2_256 = {
		WOTSP_SHA2_256, 32, 16, 67, 64, 3,
		sha2_256_f, sha2_256_prf, sha2_256_h, sha2_256_h_msg
	};
#ifdef CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES
	static const cmrt_xmss_ots_param_t parm_sha2_512 = {
		WOTSP_SHA2_512, 64, 16, 131, 128, 3,
		sha2_512_f, sha2_512_prf, sha2_512_h, sha2_512_h_msg
	};
	static const cmrt_xmss_ots_param_t parm_shake_256 = {
		WOTSP_SHAKE_256, 32, 16, 67, 64, 3,
		shake_256_f, shake_256_prf, shake_256_h, shake_256_h_msg,
	};
	static const cmrt_xmss_ots_param_t parm_shake_512 = {
		WOTSP_SHAKE_512, 64, 16, 131, 128, 3,
		shake_512_f, shake_512_prf, shake_512_h, shake_512_h_msg,
	};
#endif
	switch (otstype) {
	case WOTSP_SHA2_256:
		return &parm_sha2_256;
#ifdef CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES
	case WOTSP_SHA2_512:
		return &parm_sha2_512;
	case WOTSP_SHAKE_256 :
		return &parm_shake_256;
	case WOTSP_SHAKE_512:
		return &parm_shake_512;
#endif
	default:
		return NULL;
	}
}

static void *chain(cmrt_hc_t hc, uint8_t *input, int index, int steps, const void *seed,
		   xmss_ots_addr *addr, const cmrt_xmss_ots_param_t *parm)
{
	uint8_t *tmp;
	alignas(4) uint8_t key[MAX_OTS_N];
	alignas(4) uint8_t bm[MAX_OTS_N];

	if (steps == 0) {
		return input;
	}
	if (index + steps > (parm->w - 1)) {
		return NULL;
	}
	tmp = chain(hc, input, index, steps - 1, seed, addr, parm);

	addr->hash = (uint32_t)index + (uint32_t)steps - 1u;
	addr->keymask = 0u;
	parm->prf(hc, key, seed, addr);
	addr->keymask = 1u;
	parm->prf(hc, bm, seed, addr);
	/* tmp xor bm */
	for (int i = 0; i < parm->n; ++i) {
		tmp[i] ^= bm[i];
	}
	parm->f(hc, tmp, key, tmp);

	return tmp;
}

static void base_w(const uint8_t *x, int w, int *basew, int out_len)
{
	int lgw = w == 4 ? 2 : 4;
	int in = 0;
	int out = 0;
	unsigned int total = 0u;
	int bits = 0;

	for (int consumed = 0; consumed < out_len; consumed++) {
		if (bits == 0) {
			total = x[in];
			in++;
			bits += 8;
		}
		bits -= lgw;
		basew[out] = (total >> bits) & (w - 1);
		out++;
	}
}

static void wots_verify(cmrt_hc_t hc, void *pk, const void *m, const void *sig,
			xmss_ots_addr *addr, const void *seed,
			cmrt_xmss_ots_type type, wdt_feed_func *wdt_feed)
{
	const cmrt_xmss_ots_param_t *parm = cmrt_xmss_load_ots_parm(type);
	int msg[MAX_OTS_LEN];
	alignas(4) uint16_t csum = 0u;
	int lgw = parm->w == 4 ? 2 : 4;
	const uint8_t *s = sig;
	uint8_t *k = pk;

	base_w(m, parm->w, msg, parm->len_1);
	for (int i = 0; i < parm->len_1; ++i) {
		csum += parm->w - 1 - msg[i];
	}

	csum <<= 8 - ((parm->len_2 * lgw) % 8);
	csum = htons(csum);
	base_w((const uint8_t *)&csum, parm->w, msg + parm->len_1, parm->len_2);

	for (int i = 0; i < parm->len; ++i) {
		addr->chain = i;
		(void)memcpy(k, s, parm->n);
		if (wdt_feed != NULL) {
			wdt_feed();
		}
		chain(hc, k, msg[i], parm->w - 1 - msg[i], seed, addr, parm);
		s += parm->n;
		k += parm->n;
	}
}

static void rand_hash(cmrt_hc_t hc, void *hash, const void *left, const void *right, const void *pub_seed, xmss_htree_addr *addr, const cmrt_xmss_ots_param_t *parm)
{
	alignas(4) uint8_t key[MAX_OTS_N];
	alignas(4) uint8_t bm0[MAX_OTS_N * 2];
	uint8_t *bm1 = &bm0[parm->n];

	addr->keymask = 0u;
	parm->prf(hc, key, pub_seed, addr);
	addr->keymask = 1u;
	parm->prf(hc, bm0, pub_seed, addr);
	addr->keymask = 2u;
	parm->prf(hc, bm1, pub_seed, addr);
	/* H(KEY, (LEFT XOR BM_0) || (RIGHT XOR BM_1)) */
	for (int i = 0; i < parm->n; ++i) {
		bm0[i] ^= ((uint8_t *)left)[i];
		bm1[i] ^= ((uint8_t *)right)[i];
	}
	parm->h(hc, hash, key, bm0);
}

static void l_tree(cmrt_hc_t hc, void *pk, const void *pub_seed, xmss_ltree_addr *addr, const cmrt_xmss_ots_param_t *parm)
{
	int len = parm->len;
	int n = parm->n;
	int i = 0;

#define PK(idx) (((uint8_t *)pk) + (idx) * parm->n)

	addr->chain = 0u; /* height */
	while (len > 1) {
		for (i = 0; i < len / 2; ++i) {
			addr->hash = i; /* index */
			rand_hash(hc, PK(i), PK(2 * i), PK(2 * i + 1), pub_seed, addr, parm);
		}
		if ((len % 2) == 1) {
			(void)memcpy(PK(len / 2), PK(len - 1), n);
			len = len / 2 + 1;
		} else {
			len = len / 2;
		}
		addr->chain += 1u; /* height */
	}

#undef PK
}

static void xmss_root_fromsig(cmrt_hc_t hc, void *node, uint32_t idx,
			      const void *sig, const void *auth_path,
			      const void *m, const void *pub_seed,
			      int height, xmss_ots_addr *addr,
			      const cmrt_xmss_ots_param_t *parm,
			      wdt_feed_func *wdt_feed)
{
	size_t n = parm->n;
	alignas(4) uint8_t pk[MAX_OTS_N * MAX_OTS_LEN];
	const uint8_t *auth = auth_path;
	uint8_t *hash = node;

	addr->type = 0u;
	addr->ots = idx;
	wots_verify(hc, pk, m, sig, addr, pub_seed, parm->type, wdt_feed);

	addr->type = 1u;
	addr->ots = idx; /* ltree */
	l_tree(hc, pk, pub_seed, addr, parm);
	(void)memcpy(hash, pk, n);

	addr->type = 2u;
	addr->hash = idx; /* index */

	for (int i = 0; i < height; ++i) {
		addr->chain = i; /* height */
		if ((idx >> i) % 2 == 0) {
			addr->hash /= 2u;
			rand_hash(hc, hash, hash, auth, pub_seed, addr, parm);
		} else {
			addr->hash = (addr->hash - 1u ) / 2u;
			rand_hash(hc, hash, auth, hash, pub_seed, addr, parm);
		}
		auth += n;
	}
}

int cmrt_xmss_verify_internal(cmrt_hc_t hc, const uint8_t *pk, const uint8_t *msg,
			      size_t mlen,  uint32_t height, uint32_t layer,
			      const cmrt_xmss_ots_param_t *parm, const uint8_t *sm,
			      wdt_feed_func *wdt_feed)
{
	/* sig = idx || r || ots-sig || auth || ...
	   pk = OID || root || pub_seed */
	const uint8_t *psm = sm;
	const uint8_t *r, *sig, *auth, *root, *pub_seed;
	const size_t n = parm->n;
	alignas(4) uint8_t m[MAX_OTS_N];
	alignas(4) uint8_t node[MAX_OTS_N];
	uint32_t idx_len = index_length(height, layer);
	uint32_t oid;
	uint64_t idx;
	int res;
	xmss_ots_addr addr;

	idx = decode_index(psm, idx_len);
	r = psm + idx_len;
	sig = r + n;
	auth = sig + n * parm->len;
	(void)memcpy(&oid, pk, sizeof(uint32_t));
	oid = ntohl(oid);
	root = pk + sizeof(uint32_t);
	pub_seed = root + n;

	parm->h_msg(hc, m, r, root, idx, msg, mlen);

	memset(&addr, 0, sizeof(addr));

	for (unsigned int i = 0; i < layer; ++i) {
		uint32_t leaf = (idx & ((1 << height) - 1));

		idx = idx >> height;
		addr.layer = i;
		addr.tree = idx;
		addr.ots = leaf;

		xmss_root_fromsig(hc, node, leaf, sig, auth, m, pub_seed,
				  height, &addr, parm, wdt_feed);
		(void)memcpy(m, node, n);

		sig += (height + parm->len) * n;
		auth += (height + parm->len) * n;
	}
	res = memcmp(node, root, n);

	return res == 0 ? 0 : -1;
}

int cmrt_xmss_verify(cmrt_hc_t hc, const uint8_t *pk, const uint8_t *digest,
		     size_t dlen, const uint8_t *sm, wdt_feed_func *wdt_feed)
{
	cmrt_xmss_algorithm_type xmss_type = cmrt_xmss_get_type(pk);
	if (xmss_type == XMSS_RESERVED) {
		return -EINVAL; /* wrong or unspported OID */
	}
	const cmrt_xmss_param_t *parm = cmrt_xmss_load_param(xmss_type);
	if ((parm == NULL) || (dlen > parm->hsize)) {
		return -EINVAL; /* unspported algo type or too big message */
	}
	const cmrt_xmss_ots_param_t *otsparm = cmrt_xmss_load_ots_parm(parm->otstype);
	if (otsparm == NULL) {
		return -EINVAL; /* unspported ots type */
	}
	return cmrt_xmss_verify_internal(hc, pk, digest, dlen, parm->height,
					 parm->layer, otsparm, sm, wdt_feed);
}
