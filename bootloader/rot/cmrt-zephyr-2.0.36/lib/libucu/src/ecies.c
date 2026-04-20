/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdalign.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/aes.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/util.h>
#include <cmrt/ucu/ecies.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);


#define AES128_KEY_BYTES 16
#define AES256_KEY_BYTES 32

typedef struct cmrt_ecies_context {
	cmrt_pke_t pke;
	cmrt_hc_t hc;
	cmrt_aes_t aes;
	cmrt_ecies_mode_t mode;
	cmrt_ecies_operation_t operation;
} cmrt_ecies_context_t;

#define ECIES_CONTEXTS 1 /* only one active at a time */
static cmrt_ecies_context_t contexts[ECIES_CONTEXTS];

cmrt_ecies_t cmrt_ecies_open(uint32_t flags)
{
	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		LOG_ERR("Cannot open PKE!\n");
		return CMRT_INVALID_HANDLE;
	}

	cmrt_hc_t hc = CMRT_INVALID_HANDLE;
	if (flags & CMRT_ECIES_O_USE_HC2) {
#ifdef CONFIG_CMRT_HC2
		hc = cmrt_hc2_open(0);
#endif
	} else {
		hc = cmrt_hc_open("s3hc", 0);
		/* Try to open sha3 core first but if it's not present
		   use first HC */
		if (!cmrt_is_valid(hc)) {
			hc = cmrt_hc_open(NULL, 0);
		}
	}

	if (!cmrt_is_valid(hc)) {
		LOG_ERR("Cannot open HC!\n");
		cmrt_pke_close(pke);
		return CMRT_INVALID_HANDLE;
	}
	cmrt_aes_t aes = cmrt_aes_open(0);
	if (!cmrt_is_valid(aes)) {
		LOG_ERR("Cannot open AES!\n");
		cmrt_hc_close(hc);
		cmrt_pke_close(pke);
		return CMRT_INVALID_HANDLE;
	}
	contexts[0].pke = pke;
	contexts[0].hc  = hc;
	contexts[0].aes = aes;
	return &contexts[0];
}

static int increment_counter(uint8_t *c)
{
	int i;
	for (i = 3; i >= 0; i--) {
		if (++c[i]) {
			return 0;
		}
	}
	/* counter overruns */
	return -1;
}

/* ISO/IEC 18033-2:2006 */
static int cmrt_kdf1(cmrt_hc_t hc, cmrt_hash_algo_t hashalgo, uint32_t *shared,
		     size_t sharedlen, uint32_t *keyout, size_t keylen)
{
	int rc = 0;
	uint32_t hashlen;
	switch (hashalgo) {
	case CMRT_HASH_SHA256:
		hashlen = SHA256_BYTES;
		break;
	case CMRT_HASH_SHA384:
		hashlen = SHA384_BYTES;
		break;
	case CMRT_HASH_SHA512:
		hashlen = SHA512_BYTES;
		break;
	case CMRT_HASH_SHA3_256:
		hashlen = SHA3_256_BYTES;
		break;
	case CMRT_HASH_SHA3_384:
		hashlen = SHA3_384_BYTES;
		break;
	case CMRT_HASH_SHA3_512:
		hashlen = SHA3_512_BYTES;
		break;
	default:
		rc = -EINVAL;
		goto out;
	}

	uint32_t counter = 0;
	uint32_t hash[SHA512_WORDS];
	uint32_t rounds = (keylen + hashlen - 1) / hashlen;
	uint32_t start = 0;
	size_t outlen = sizeof(hash);
	size_t cpylen;
	size_t aligned_sharedlen = (sharedlen + 3) & -4;
	for (uint32_t i = 0; i < rounds; ++i) {
		rc = cmrt_hc_init(hc, hashalgo, NULL, 0);
		if (rc) {
			LOG_ERR("cmrt_hc_init: %d\n", rc);
			goto out;
		}
		rc = cmrt_hc_update(hc, shared, aligned_sharedlen);
		if (rc) {
			LOG_ERR("cmrt_hc_update shared: %d\n", rc);
			goto out;
		}
		rc = cmrt_hc_update(hc, &counter, 4);
		if (rc) {
			LOG_ERR("cmrt_hc_update counter: %d\n", rc);
			goto out;
		}
		rc = cmrt_hc_final(hc, NULL, 0, hash, &outlen);
		if (rc || (outlen == 0)) {
			LOG_ERR("hash_final_int: %d outlen:%d\n", rc, outlen);
			goto out;
		}
		start = i * (hashlen/sizeof(uint32_t));
		cpylen = keylen - i * hashlen;
		if (cpylen > outlen) {
			cpylen = outlen;
		}
		memcpy(&keyout[start], hash, cpylen);

		if (increment_counter((uint8_t *)&counter) < 0) {
			rc = -EINVAL;
			goto out;
		}
	}

out:
	return rc;
}

int cmrt_ecies_init(cmrt_ecies_t ecies, cmrt_ecies_mode_t mode,
		   cmrt_ecies_operation_t operation, const void *priv,
		   size_t privlen, const void *peerx, size_t peerxlen,
		   void *pubxout, size_t pubxoutlen)
{
	int rc = -EINVAL;
	if (!peerx || !pubxout) {
		goto out;
	}

	cmrt_ecc_curve_t curve;
	cmrt_hash_algo_t hashalgo;
	size_t k_aes_len;
	size_t k_mac_len;
	switch (mode) {
	case CMRT_ECIES_P256_KDF1_SHA256_AES128_HMAC_SHA256:
		curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P256);
		hashalgo = CMRT_HASH_SHA256;
		k_aes_len = AES128_KEY_BYTES;
		k_mac_len = SHA256_BYTES;
		break;
	case CMRT_ECIES_P384_KDF1_SHA384_AES128_HMAC_SHA384:
		curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P384);
		hashalgo = CMRT_HASH_SHA384;
		k_aes_len = AES128_KEY_BYTES;
		k_mac_len = SHA384_BYTES;
		break;
	case CMRT_ECIES_P521_KDF1_SHA512_AES256_HMAC_SHA512:
		curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P521);
		hashalgo = CMRT_HASH_SHA512;
		k_aes_len = AES256_KEY_BYTES;
		k_mac_len = SHA512_BYTES;
		break;
	case CMRT_ECIES_P256_KDF1_SHA3_256_AES128_HMAC_SHA3_256:
		curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P256);
		hashalgo = CMRT_HASH_SHA3_256;
		k_aes_len = AES128_KEY_BYTES;
		k_mac_len = SHA3_256_BYTES;
		break;
	case CMRT_ECIES_P384_KDF1_SHA3_384_AES128_HMAC_SHA3_384:
		curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P384);
		hashalgo = CMRT_HASH_SHA3_384;
		k_aes_len = AES128_KEY_BYTES;
		k_mac_len = SHA3_384_BYTES;
		break;
	case CMRT_ECIES_P521_KDF1_SHA3_512_AES256_HMAC_SHA3_512:
		curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P521);
		hashalgo = CMRT_HASH_SHA3_512;
		k_aes_len = AES256_KEY_BYTES;
		k_mac_len = SHA3_512_BYTES;
		break;
	default:
		goto out;
	}
	size_t curvelen = cmrt_pke_get_curve_length(curve);
	if (curvelen != peerxlen) {
		goto out;
	}

	ecies->mode = mode;
	ecies->operation = operation;

	enum { MAX_DERIVED_KEY_BYTES = AES256_KEY_BYTES + SHA3_512_BYTES };
	uint32_t ephemeral_priv[MAX_EC_CURVE_LENGTH_W] = { 0 };
	uint32_t ephemeral_pubx[MAX_EC_CURVE_LENGTH_W] = { 0 };
	uint32_t ephemeral_puby[MAX_EC_CURVE_LENGTH_W] = { 0 };
	uint32_t shared[MAX_EC_CURVE_LENGTH_W] = { 0 };
	uint32_t aes_operation;
	uint32_t key[MAX_DERIVED_KEY_BYTES/sizeof(uint32_t)];
	if (operation == CMRT_ECIES_ENCRYPT) {
		if (priv != NULL) {
			goto out;
		}
		/* generate ephemeral private key */
		if (cmrt_get_random(ephemeral_priv, curvelen) < 0) {
			rc = -ENXIO;
			goto out;
		}
		aes_operation = CIPHER_OP_ENCRYPT;
	} else {
		if ((priv == NULL) || (curvelen != privlen)) {
			goto out;
		}
		memcpy(ephemeral_priv, priv, privlen);
		aes_operation = CIPHER_OP_DECRYPT;
	}
	/* generate ephemeral public key */
	rc = cmrt_pke_ecdsa_keygen(ecies->pke, curve, ephemeral_priv,
				  ephemeral_pubx, ephemeral_puby);
	if (rc) {
		LOG_ERR("cmrt_pke_ecdsa_keygen failed %d\n", rc);
		goto out;
	}

	/* generate shared key from ephemeral private key and peer public key */
	rc = cmrt_pke_ecdh(ecies->pke, curve, ephemeral_priv, peerx, shared);
	if (rc) {
		LOG_ERR("cmrt_pke_ecdh failed %d\n", rc);
		goto out;
	}

	rc = cmrt_kdf1(ecies->hc, hashalgo, shared, curvelen, key,
		      k_aes_len + k_mac_len);
	if (rc) {
		LOG_ERR("cmrt_kdf1 failed %d\n", rc);
		goto out;
	}
	const uint32_t aes_iv[4] = { 0 };
	rc = cmrt_aes_init(ecies->aes, aes_operation, AES_CBC, &key[0],
			  k_aes_len, &aes_iv[0], sizeof(aes_iv), 0);
	if (rc) {
		LOG_ERR("cmrt_aes_init failed %d\n", rc);
		goto out;
	}
	rc = cmrt_hc_init(ecies->hc, hashalgo,
			 &key[k_aes_len/sizeof(uint32_t)], k_mac_len);
	if (rc) {
		LOG_ERR("cmrt_hc_init failed %d\n", rc);
		goto out;
	}
	memcpy(pubxout, ephemeral_pubx, pubxoutlen);

out:
	return rc;

}

int cmrt_ecies_update(cmrt_ecies_t ecies, const void *input, size_t inputlen,
		     void *output)
{
	int rc = 0;
	if ((inputlen & (AES_BLOCK_BYTES - 1)) != 0) {
		LOG_ERR("cmrt_aes_update inputlen %u\n", inputlen);
		rc = -EINVAL;
		goto err;
	}
	if (ecies->operation == CMRT_ECIES_DECRYPT) {
		rc = cmrt_hc_update(ecies->hc, input, inputlen);
		if (rc) {
			LOG_ERR("cmrt_hc_update failed %d inputlen:%d\n",
				rc, inputlen);
			goto err;
		}
	}
	rc = cmrt_aes_update(ecies->aes, input, inputlen, output);
	if (rc) {
		LOG_ERR("cmrt_aes_update failed %d\n", rc);
		goto err;
	}
	if (ecies->operation == CMRT_ECIES_ENCRYPT) {
		rc = cmrt_hc_update(ecies->hc, output, inputlen);
		if (rc) {
			LOG_ERR("cmrt_hc_update failed %d inputlen:%d\n",
				rc, inputlen);
			goto err;
		}
	}
err:
	return rc;
}

int cmrt_ecies_final(cmrt_ecies_t ecies, const void *input, size_t inputlen,
		    const void *sharedinfo, size_t sharedinfolen, void *output,
		    void *tag, size_t taglen)
{
	int rc = 0;
	const uint8_t *cipher = input;
	if (ecies->operation == CMRT_ECIES_ENCRYPT) {
		rc = cmrt_aes_final(ecies->aes, input, inputlen, output);
		if (rc) {
			LOG_ERR("cmrt_aes_final failed %d\n", rc);
			goto err;
		}
		cipher = output;
	}
	alignas(4) uint8_t tmpword[4] = { 0 };
	size_t ilenhc = inputlen;
	if (sharedinfo && sharedinfolen) {
		if (cipher) {
			size_t n = ilenhc & ~3u;
			size_t clen = ilenhc - n;
			rc = cmrt_hc_update(ecies->hc, cipher, n);
			if (rc) {
				LOG_ERR("cmrt_ecies_update: %d\n", rc);
				goto err;
			}
			cipher += n;
			if (clen) {
				memcpy(&tmpword[0], cipher, clen);
			}
			size_t slen = sharedinfolen;
			size_t clenrest = 4 - clen;
			while (slen >= 4) {
				memcpy(&tmpword[clen], sharedinfo, clenrest);
				slen -= clenrest;
				sharedinfo = (const char *)sharedinfo + clenrest;
				if (slen > 4) {
					rc = cmrt_hc_update(ecies->hc, tmpword, 4);
					if (rc) {
						LOG_ERR("cmrt_ecies_update: %d\n", rc);
						goto err;
					}
					memcpy(&tmpword[clen], sharedinfo, clen);
					slen -= clen;
					sharedinfo = (const char *)sharedinfo + clen;
				} else {
					break;
				}
			}
			cipher = tmpword;
			ilenhc = slen;
		} else {
			cipher = sharedinfo;
			ilenhc = sharedinfolen;
		}
	}

	rc = cmrt_hc_final(ecies->hc, cipher, ilenhc, tag, &taglen);
	if (rc) {
		LOG_ERR("cmrt_hc_final failed %d ilenhc:%d\n", rc, ilenhc);
		goto err;
	}
	if (ecies->operation == CMRT_ECIES_DECRYPT) {
		rc = cmrt_aes_final(ecies->aes, input, inputlen, output);
		if (rc) {
			LOG_ERR("cmrt_aes_final failed %d\n", rc);
			goto err;
		}
	}
err:
	return rc;
}

void cmrt_ecies_close(cmrt_ecies_t ecies)
{
	if (cmrt_is_valid(ecies->aes)) {
		cmrt_aes_close(ecies->aes);
		ecies->aes = CMRT_INVALID_HANDLE;
	}
	if (cmrt_is_valid(ecies->hc)) {
		cmrt_hc_close(ecies->hc);
		ecies->hc = CMRT_INVALID_HANDLE;
	}
	if (cmrt_is_valid(ecies->pke)) {
		cmrt_pke_close(ecies->pke);
		ecies->pke = CMRT_INVALID_HANDLE;
	}
}
