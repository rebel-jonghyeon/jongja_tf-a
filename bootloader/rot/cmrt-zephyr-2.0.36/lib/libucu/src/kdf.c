/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdalign.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/hc.h>
#include <cmrt/ucu/kdf.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

/* RFC2104. hc must be already open. Will not close it on exit even if fails. */
static int hc_init_hmac_sha256(cmrt_hc_t hc, const void *key, size_t keylen)
{
#define BLOCKLEN 64
	int rc;
	alignas(4) uint8_t _key[BLOCKLEN] = {0};
	size_t outlen;

	if (keylen > BLOCKLEN) {
		rc = cmrt_hc_init(hc, CMRT_HASH_SHA256, 0, 0);
		if (rc) { goto out; }

		outlen = SHA256_BYTES;
		rc = cmrt_hc_final(hc, key, keylen, _key, &outlen);
		if (rc) { goto out; }
	} else {
		memcpy(_key, key, keylen);
	}

	/* NOTE: Remaining bytes in _key are already padded with 0. */
	rc = cmrt_hc_init(hc, CMRT_HASH_SHA256, _key, BLOCKLEN);

out:
	return rc;
#undef BLOCKLEN
}

int hkdf_extract(cmrt_hc_t hc, const void *salt, size_t saltlen, const void *ikm,
		size_t ikmlen, void *prk)
{
	int rc;
	rc = hc_init_hmac_sha256(hc, salt, saltlen);
	if (!rc) {
		size_t outlen = SHA256_BYTES;
		rc = cmrt_hc_final(hc, ikm, ikmlen, prk, &outlen);
	}

	return rc;
}

int hkdf_expand(cmrt_hc_t hc, const void *prk, size_t prklen, const void *info,
		size_t infolen, size_t l, void *okm)
{
	int rc;
	uint8_t *_okm = (uint8_t *) okm;

	/* mandated by RFC5869 except !l check */
	if (prklen < SHA256_BYTES || !l || l > 255*SHA256_BYTES) { return -EINVAL; }
	if (!infolen) { info = NULL; }

	l = (l+(SHA256_BYTES-1)) & (~(SHA256_BYTES-1)); /* align up to SHA256_BYTES */
	uint8_t *okm_end = _okm+l;

	size_t info_updatelen = infolen & ~(3UL);
	size_t info_remaining = infolen & 3UL;
	/* NOTE: infolen and info_* can be 0. */

	alignas(4) uint8_t tmp[4] = {0}; /* to store remaining info (if any) | b */
	if (info) {
		memcpy(tmp, (uint8_t*)info+info_updatelen, info_remaining);
	}

	/* unrolled first iteration, okm[0..SHA_BYTES) = HMAC(PRK, info|0x01) */
	rc = hc_init_hmac_sha256(hc, prk, prklen);
	if (rc) { goto out; }

	if (info) {
		rc = cmrt_hc_update(hc, info, info_updatelen);
		if (rc) { goto out; }
	}

	tmp[info_remaining] = 0x01;
	size_t outlen = SHA256_BYTES;
	rc = cmrt_hc_final(hc, tmp, info_remaining + 1, _okm, &outlen);
	if (rc) { goto out; }
	_okm += SHA256_BYTES;

	for (uint8_t t = 2;
		_okm < okm_end; _okm += SHA256_BYTES, ++t) {

		rc = hc_init_hmac_sha256(hc, prk, prklen);
		if (rc) { goto out; }

		/* for remaining iterations, T(n) is always SHA256_BYTES long. */
		rc = cmrt_hc_update(hc, _okm-SHA256_BYTES, SHA256_BYTES);
		if (rc) { goto out; }

		if (info) {
			rc = cmrt_hc_update(hc, info, info_updatelen);
			if (rc) { goto out; }
		}

		tmp[info_remaining] = t;
		outlen = SHA256_BYTES;
		rc = cmrt_hc_final(hc, tmp, info_remaining + 1, _okm, &outlen);
		if (rc) { goto out; }
	}

out:
	return rc;
}

int hkdf_extract_expand(cmrt_hc_t hc, const void *salt, size_t saltlen,
		const void *ikm, size_t ikmlen, const void *info, size_t infolen,
		size_t l, void *okm)
{
	int rc;
	alignas(4) uint8_t prk[SHA256_BYTES];

	rc = hkdf_extract(hc, salt, saltlen, ikm, ikmlen, prk);
	if (!rc) {
		rc = hkdf_expand(hc, prk, sizeof(prk), info, infolen, l, okm);
	}

	return rc;
}
