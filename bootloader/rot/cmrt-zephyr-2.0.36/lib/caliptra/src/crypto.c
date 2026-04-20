/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/aes.h>
#include <errno.h>
#include <cmrt/caliptra/types.h>
#include <cmrt/caliptra/flow.h>
#include "internal.h"

int sha384(const span data, span out)
{
	cmrt_hc_t hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	int res = -EIO;
	if (cmrt_is_valid(hc)) {
		res = cmrt_hc_init(hc, CMRT_HASH_SHA384, NULL, 0);
		if (res == 0) {
			res = cmrt_hc_final(hc, data.p, data.n, (uint8_t *)out.p, &out.n);
		}
		cmrt_hc_close(hc);
	}
	return res;
}

int hmac384(const span key, const span data, span out)
{
	cmrt_hc_t hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	int res = -EIO;
	if (cmrt_is_valid(hc)) {
		res = cmrt_hc_init(hc, CMRT_HASH_SHA384, key.p, key.n);
		if (res == 0) {
			res = cmrt_hc_final(hc, data.p, data.n, (uint8_t *)out.p, &out.n);
		}
		cmrt_hc_close(hc);
	}
	return res;
}

int cmrt_caliptra_hash(const void *msg, size_t msg_len, cmrt_caliptra_digest_t *out)
{
	return sha384(span_from(msg, msg_len), SPAN(*out));
}

int cmrt_caliptra_hmac(const void *key, size_t key_len,
		       const void *msg, size_t msg_len, cmrt_caliptra_digest_t *out)
{
	return hmac384(span_from(key, key_len), span_from(msg, msg_len), SPAN(*out));
}

int p384_genpub(const span priv, span pubx, span puby)
{
	int res = -EIO;
	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (cmrt_is_valid(pke)) {
		cmrt_ecc_curve_t curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P384);
		if (curve != NULL) {
			res = cmrt_pke_ecdsa_keygen(pke, curve, priv.p,
						    (void *)pubx.p, (void *)puby.p);
			if (res == 0) {
				res = cmrt_pke_sync(pke);
			}
		}
		cmrt_pke_close(pke);
	}
	return res;
}

int p384_sign(const span priv, const span digest, span sigr, span sigs)
{
	int res = -EIO;
	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (cmrt_is_valid(pke)) {
		cmrt_ecc_curve_t curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P384);
		if (curve != NULL) {
			res = cmrt_pke_ecdsa_sign_hash(pke, curve, priv.p,
						       digest.p, digest.n,
						       (void *)sigr.p, (void *)sigs.p);
			if (res == 0) {
				res = cmrt_pke_sync(pke);
			}
		}
		cmrt_pke_close(pke);
	}
	return res;
}

int ecckpdf(const span input, const span keyname,
			   cmrt_caliptra_privkey_t *priv, cmrt_caliptra_pubkey_t *pub)
{
	int res = -EIO;
	res = hmac384(input, keyname, SPAN(*priv));
	if (res == 0) {
		res = p384_genpub(SPAN(*priv), SPAN(pub->x), SPAN(pub->y));
	}
	return res;
}

int cmrt_caliptra_ecckpdf(const void *input, size_t input_len,
			  const char *keyname, size_t keyname_len,
			  cmrt_caliptra_privkey_t *priv, cmrt_caliptra_pubkey_t *pub)
{
	return ecckpdf(span_from(input, input_len), span_from(keyname, keyname_len), priv, pub);
}

/* Deobfuscate @a data using AES-256-CBC with a key derived from DGOK
 * using the given diversification path. Write the result to @a out.
 */
int deobfuscate(const span data, const span iv, const span diversify_path, span out)
{
	int res = 0;
	cmrt_aes_t aes = CMRT_INVALID_HANDLE;
	cmrt_kdc_t kdc = CMRT_INVALID_HANDLE;

	aes = cmrt_aes_open(CMRT_O_HWC_KEYED | CMRT_O_SYNC);
	if (!cmrt_is_valid(aes)) {
		res = -EIO;
	}
	if (res == 0) {
		kdc = cmrt_kdc_open(CMRT_O_SYNC);
		if (!cmrt_is_valid(kdc)) {
			res = -EIO;
		}
	}

	if (res == 0) {
		cmrt_kdc_cmd_t cmd = {
			.base_key_id = KEY_ID_DGOK,
			.diversify_len = diversify_path.n,
		};
		(void)memcpy(cmd.diversify_path, diversify_path.p, sizeof(cmd.diversify_path));
		res = cmrt_aes_kdc_cmd(aes, CMRT_AES_DECRYPT,
				       CMRT_AES_CBC, 256UL/8UL, 0, &cmd);
		if (res == 0) {
			res = cmrt_kdc_derive_key(kdc, &cmd);
		}
	}
	if (res == 0) {
		res = cmrt_aes_init(aes, CMRT_AES_DECRYPT, CMRT_AES_CBC,
				    NULL, 0, iv.p, iv.n, 0);
	}
	if (res == 0) {
		res = cmrt_aes_final(aes, data.p, data.n, (void *)out.p);
	}
	cmrt_kdc_close(kdc);
	cmrt_aes_close(aes);
	return res;
}
