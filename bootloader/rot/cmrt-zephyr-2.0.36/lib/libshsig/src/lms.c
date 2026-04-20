/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>

#include <errno.h>
#include <stdbool.h>
#include <stdalign.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <tinycrypt/sha256.h>

#include <drivers/cmrt/cmrt.h>
#include <cmrt/shsig/lms.h>
#include <cmrt/shsig/lms_ots.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

static int lms_height(cmrt_lms_algorithm_type type)
{
	int h = -1;

	switch (type) {
	case LMS_SHA256_N32_H5:
		h = 5;
		break;
	case LMS_SHA256_N32_H10:
		h = 10;
		break;
	case LMS_SHA256_N32_H15:
		h = 15;
		break;
	case LMS_SHA256_N32_H20:
		h = 20;
		break;
	case LMS_SHA256_N32_H25:
		h = 25;
		break;
	default:
		break;
	}

	return h;
}

cmrt_lms_algorithm_type cmrt_lms_get_type(const uint8_t *pk, bool is_hss)
{
	if (pk != NULL) {
		uint32_t *ptype = (uint32_t *)pk;
		if (is_hss) {
			ptype++;
		}
		uint32_t type = ntohl(*ptype);
		if ((type >= LMS_SHA256_N32_H5) &&
		    (type <= LMS_SHA256_N32_H25)) {
			return (cmrt_lms_algorithm_type)type;
		}
	}
	return LMS_RESERVED;
}

int cmrt_lms_verify(cmrt_hc_t hc, const uint8_t *pk, const uint8_t *msg,
		    size_t mlen, const uint8_t *sig)
{
	if (!cmrt_is_valid(hc) || (sig == NULL) || (pk == NULL) ||
	    (msg == NULL)) {
		return -EINVAL;
	}

	/* pk = type || otstype || I || root_hash */
	uint32_t type, otstype, q;
	const uint8_t *I, *root_hash, *ots_sig, *path;
	const lmots_param *parm;
	size_t siglen;
	int h, node_num, nn;
	alignas(4) uint8_t Kc[32];
	alignas(4) uint8_t tmp[32];
	alignas(4) uint8_t inbuf[86];
	size_t inlen;
	size_t dlen;
	alignas(4) const uint16_t d_leaf = 0x8282;
	alignas(4) const uint16_t d_intr = 0x8383;

	I = pk;
	(void)memcpy(&type, I, sizeof(uint32_t));
	I += sizeof(uint32_t);
	(void)memcpy(&otstype, I, sizeof(uint32_t));
	I += sizeof(uint32_t);
	root_hash = I + (4u * sizeof(uint32_t));
	parm = lms_ots_parm(ntohl(otstype));
	if (parm == NULL) {
		return -1;
	}
	siglen = LMS_OTS_SIG_LEN(parm->p);

	/* sig = q || ots_signature || type || path x h */
	ots_sig = sig;
	(void)memcpy(&q, ots_sig, sizeof(uint32_t));
	q = ntohl(q);
	ots_sig += sizeof(uint32_t);

	if (memcmp(&otstype, ots_sig, sizeof(uint32_t)) != 0) {
		return -1;
	}
	if (memcmp(&type, ots_sig + siglen, sizeof(uint32_t)) != 0) {
		return -1;
	}
	path = ots_sig + siglen + sizeof(uint32_t);
	otstype = ntohl(otstype);
	type = ntohl(type);
	h = lms_height(type);
	if ((h < 0) || (q >= (1UL << h))) {
		return -1;
	}
	lms_ots_verify_hash(hc, Kc, I, q, ots_sig, msg, mlen);

	node_num = (1 << h) + q;
	nn = htonl(node_num);

	/* tmp = H(I || u32str(node_num) || u16str(D_LEAF) || Kc) */
	(void)memcpy(inbuf, I, 4u * sizeof(uint32_t));
	inlen = 4 * sizeof(uint32_t);
	(void)memcpy(inbuf + inlen, &nn, sizeof(uint32_t));
	inlen += sizeof(uint32_t);
	(void)memcpy(inbuf + inlen, &d_leaf, sizeof(uint16_t));
	inlen += sizeof(uint16_t);
	(void)memcpy(inbuf + inlen, Kc, sizeof(Kc));
	inlen += sizeof(Kc);
	int res = cmrt_hc_init(hc, HC_HASH_ALGO_SHA_256, 0, 0);
	if (res) {
		LOG_ERR("Cannot init HC: %d\n", res);
	}
	dlen = sizeof(tmp);
	res = cmrt_hc_final(hc, inbuf, inlen, tmp, &dlen);
	if (res) {
		LOG_ERR("Cannot final hash: %d\n", res);
	}

	for (int i = 0; node_num > 1; ++i) {
		nn = htonl(node_num / 2);

		(void)memcpy(inbuf, I, 4u * sizeof(uint32_t));
		inlen = 4 * sizeof(uint32_t);
		(void)memcpy(inbuf + inlen, &nn, sizeof(uint32_t));
		inlen += sizeof(uint32_t);
		(void)memcpy(inbuf + inlen, &d_intr, sizeof(uint16_t));
		inlen += sizeof(uint16_t);

		if ((node_num % 2) == 1) {
			/* H(I||u32str(node_num/2)||u16str(D_INTR)||path[i]||tmp) */
			(void)memcpy(inbuf + inlen, path, 32u);
			inlen += 32u;
			(void)memcpy(inbuf + inlen, tmp, sizeof(tmp));
			inlen += sizeof(tmp);
		} else {
			/* H(I||u32str(node_num/2)||u16str(D_INTR)||tmp||path[i]) */
			memcpy(inbuf + inlen, tmp, sizeof(tmp));
			inlen += sizeof(tmp);
			memcpy(inbuf + inlen, path, 32u);
			inlen += 32u;
		}

		res = cmrt_hc_init(hc, HC_HASH_ALGO_SHA_256, 0, 0);
		if (res) {
			LOG_ERR("Cannot init HC: %d\n", res);
		}
		dlen = sizeof(tmp);
		res = cmrt_hc_final(hc, inbuf, inlen, tmp, &dlen);
		if (res) {
			LOG_ERR("Cannot final hash: %d\n", res);
		}

		node_num = node_num / 2;
		path += 32u;
	}
	if (memcmp(tmp, root_hash, sizeof(tmp)) != 0) {
		return -1;
	}
	return 0;
}

static size_t lms_sig_len(const void *sig)
{
	/* q || ots_sig || type || path x h */
	uint32_t type, otstype;
	const uint8_t *s = sig;
	const lmots_param *parm;

	s += sizeof(uint32_t); /* skip q */
	/* type || C || 32 * p */
	(void)memcpy(&otstype, s, sizeof(uint32_t));
	otstype = ntohl(otstype);
	parm = lms_ots_parm(otstype);
	if (parm == NULL) {
		return 0u;
	}
	s += LMS_OTS_SIG_LEN(parm->p);
	(void)memcpy(&type, s, sizeof(uint32_t));
	type = ntohl(type);

	return LMS_SIG_LEN(parm->p, lms_height(type));
}

int cmrt_lms_hss_verify(cmrt_hc_t hc, const uint8_t *pk, const uint8_t *msg,
			size_t mlen, const uint8_t *sig)
{
	/* pk = level || type || otstype || I || root_hash
	   sig = n || n * (lms_sig || lms_pk) || lms_sig, where n = levels - 1 */
	int level, nspk;
	int ret = 0;
	size_t siglen;
	const uint8_t *p1;
	const uint8_t *s1;
	const uint8_t *key;

	(void)memcpy(&level, pk, sizeof(int));
	level = ntohl(level);
	(void)memcpy(&nspk, sig, sizeof(int));
	nspk = ntohl(nspk);

	if (nspk != level - 1) {
		return -1;
	}

	key = pk;
	key += sizeof(int); /* skip level */

	s1 = sig;
	s1 += sizeof(int); /* skip n */

	for (int i = 0; i < nspk; ++i) {
		siglen = lms_sig_len(s1);
		p1 = s1 + siglen;
		if (cmrt_lms_verify(hc, key, p1, LMS_PK_LEN, s1) != 0) {
			ret = -1;
		}
		s1 = p1 + LMS_PK_LEN;
		key = p1;
	}
	if (cmrt_lms_verify(hc, key, msg, mlen, s1) != 0) {
		ret = -1;
	}

	return ret;
}
