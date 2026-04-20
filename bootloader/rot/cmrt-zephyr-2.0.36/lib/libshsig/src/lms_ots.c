/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <stdalign.h>
#include <stdint.h>
#include <string.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/hc.h>

#include <cmrt/shsig/lms_ots.h>
#include <tinycrypt/sha256.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

const lmots_param *lms_ots_parm(lmots_algorithm_type type)
{
	static const lmots_param parm1 = {
		LMOTS_SHA256_N32_W1, 32, 1, 265, 7, 8516
	};
	static const lmots_param parm2 = {
		LMOTS_SHA256_N32_W2, 32, 2, 133, 6, 4292
	};
	static const lmots_param parm4 = {
		LMOTS_SHA256_N32_W4, 32, 4, 67, 4, 2180
	};
	static const lmots_param parm8 = {
		LMOTS_SHA256_N32_W8, 32, 8, 34, 0, 1124
	};
	switch (type) {
	case LMOTS_SHA256_N32_W1:
		return &parm1;
	case LMOTS_SHA256_N32_W2:
		return &parm2;
	case LMOTS_SHA256_N32_W4:
		return &parm4;
	case LMOTS_SHA256_N32_W8:
		return &parm8;
	default:
		LOG_ERR("unknown OTS type: %d\n", type);
		return NULL;
	}
}

/* TODO: it can be made faster. */
static uint32_t coef(const void *s, uint32_t i, uint32_t w)
{
	const uint8_t *p = s;
	size_t offs = (i * w) / 8;
	uint32_t ret = (1U << w) - 1;
	alignas(4) uint8_t c;

	p += offs;
	c = p[0] >> (w * (~i & (8u / w - 1u)));
	ret &= c;

	return ret;
}

/* 4.4 */
static uint16_t lms_ots_checksum(const void *s, const lmots_param *parm)
{
	alignas(4) uint16_t sum = 0;
	alignas(4) uint32_t w = parm->w;
	int e = (1 << w) - 1;
	uint32_t b = (parm->n * 8u) / w;

	for (uint32_t i = 0; i < b; ++i) {
		sum = sum + e - coef(s, i, w);
	}

	return sum << parm->ls;
}

/* q in little-endian */
void lms_ots_verify_hash(cmrt_hc_t hc, void *hash, const void *I,
			 uint32_t q, const void *sig, const void *msg, uint32_t mlen)
{
	enum { INBUF_SIZE = 56 };
	const uint8_t *C, *y;
	uint32_t type;
	const lmots_param *parm;
	alignas(4) uint8_t Q[32 + 2];
	alignas(4) uint8_t inbuf[INBUF_SIZE];
	size_t inlen, dlen, flen;
	alignas(4) uint16_t d_mesg = 0x8181u;
	alignas(4) uint16_t d_pblc = 0x8080u;
	int w;
	int res;
	struct tc_sha256_state_struct s;

	q = htonl(q);

	/* get type, C from sig */
	(void)memcpy(&type, sig, 4u);
	type = ntohl(type);
	parm = lms_ots_parm(type);
	if (parm == NULL) {
		LOG_ERR("Wrong OTS type 0x%x\n", (unsigned int)type);
		return;
	}
	w = parm->w;
	C = sig;
	C += 4u;
	y = C + 32u;

	/* I || q || D_PBLC || y */
	(void)tc_sha256_init(&s);
	(void)tc_sha256_update(&s, I, 16u);
	(void)tc_sha256_update(&s, (const uint8_t *)&q, 4u);
	(void)tc_sha256_update(&s, (const uint8_t *)&d_pblc, 2u);


	/* Q = H(I || u32str(q) || u16str(D_MESG) || C || message) */
	res = cmrt_hc_init(hc, HC_HASH_ALGO_SHA_256, 0, 0);
	if (res) {
		LOG_ERR("Cannot init HC: %d\n", res);
	}
	(void)memcpy(inbuf, I, 16u);
	inlen = 16u;
	(void)memcpy(inbuf + inlen, &q, 4u);
	inlen += 4u;
	(void)memcpy(inbuf + inlen, &d_mesg, 2u);
	inlen += 2u;
	(void)memcpy(inbuf + inlen, C, 32u);
	inlen += 32u;

	const uint8_t *pmsg = (const uint8_t *)msg;
	for (;;) {
		flen = INBUF_SIZE - inlen;
		if (mlen > flen) {
			/* Align update to 56 */
			(void)memcpy(inbuf + inlen, pmsg, flen);
			inlen += flen;
			pmsg += flen;
			mlen -= flen;
			res = cmrt_hc_update(hc, inbuf, inlen);
			if (res) {
				LOG_ERR("Cannot update hash: %d\n", res);
			}
			inlen = 0u;
		} else {
			(void)memcpy(inbuf + inlen, pmsg, mlen);
			inlen += mlen;
			mlen = 0u;
			dlen = 32u;
			res = cmrt_hc_final(hc, inbuf, inlen, Q, &dlen);
			if (res) {
				LOG_ERR("Cannot final hash: %d\n", res);
			}
			inlen = 0;
			break;
		}
	}
	/* attach lms_ots_checksum to Q */
	alignas(4) uint16_t cksum = lms_ots_checksum(Q, parm);
	cksum = htons(cksum);
	(void)memcpy(Q + 32u, &cksum, 2u);

	for (int i = 0; i < parm->p; ++i) {
		alignas(4) uint8_t tmp[32];
		alignas(4) uint8_t a = coef(Q, i, w);
		alignas(4) uint8_t j;
		alignas(4) uint16_t ni = i;

		ni = htons(ni);
		(void)memcpy(tmp, y, 32u);

		for (j = a; j < (1u << w) - 1u; ++j) {
			res = cmrt_hc_init(hc, HC_HASH_ALGO_SHA_256, 0, 0);
			if (res) {
				LOG_ERR("Cannot init HC: %d\n", res);
			}
			(void)memcpy(inbuf, I, 16u);
			inlen = 16u;
			(void)memcpy(inbuf + inlen, &q, 4u);
			inlen += 4u;
			(void)memcpy(inbuf + inlen, &ni, 2u);
			inlen += 2u;
			(void)memcpy(inbuf + inlen, &j, 1u);
			inlen += 1u;
			(void)memcpy(inbuf + inlen, tmp, 32u);
			inlen += 32u;

			dlen = sizeof(tmp);
			res = cmrt_hc_final(hc, inbuf, inlen, tmp, &dlen);
			if (res) {
				LOG_ERR("Cannot final hash: %d\n", res);
			}
		}
		/* z[i] = tmp */
		(void)tc_sha256_update(&s, tmp, 32u);
		y += 32u;
	}
	(void)tc_sha256_final(hash, &s);
}

/* 4.6 */
int lms_ots_verify(cmrt_hc_t hc, const void *sig, const void *pk,
		   const void *msg, uint32_t mlen)
{
	/* get parm, I, q, K from pk */
	const uint8_t *p = pk;
	const uint8_t *K, *I;
	uint32_t type, q;
	alignas(4) uint8_t Kc[32];

	(void)memcpy(&type, p, 4u);
	p += 4u;
	I = p;
	p += 16u;
	(void)memcpy(&q, p, 4u); /* keep it in big endian */
	q = ntohl(q);
	p += 4u;
	K = p;

	/* get type, C from sig */
	if (memcmp(&type, sig, 4u) != 0) {
		LOG_ERR("wrong type\n");
		return -1;
	}

	lms_ots_verify_hash(hc, Kc, I, q, sig, msg, mlen);

	if (memcmp(K, Kc, 32u) != 0) {
		LOG_ERR("wrong K\n");
		return -1;
	}
	return 0;
}
