/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <device.h>
#include <kernel.h>
#include <cri/cmrt/pke.h>
#include <string.h>
#include <errno.h>
#include <kernel_structs.h>
#include <cri/cmrt/hc.h>
#include <cri/cmrt.h>
#include <cmrt/ucu/rsa_pad.h>

#include <cri/cmrt/fips/fips_types.h>

#include <cmrt/ucu/endianness.h>
#include <cmrt/ucu/rsa_pad.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"
#include "cri_crypto.h"

#include "pke_kat_vectors.h"


static int pke_rsa_pub(cmrt_pke_t pke, const struct cmrt_rsa_key *key,
		       const char *signature, char *message)
{
	return cmrt_pke_rsa_public_key_primitive(pke, key->bits,
						 key->n, key->e,
						 signature,
						 message);
}

static bool run_rsa(const rsa_kat_t *kat)
{
	int32_t status = 0;

	uint32_t byte_length = kat->bit_length / 8;
	struct cmrt_pss_params pss;
	uint8_t *pss_message = workcontext;
	uint8_t *signature = pss_message + byte_length;
	struct cmrt_rsa_ctx *r_ctx =
		(struct cmrt_rsa_ctx *)(signature + byte_length);
	cmrt_pke_t pke = CMRT_INVALID_HANDLE;
	cmrt_hc_t hc = CMRT_INVALID_HANDLE;

	status = cmrt_pke_rsa_ctx_init(r_ctx, kat->bit_length,
				       (uint32_t *)(r_ctx + sizeof(struct cmrt_rsa_ctx)));

	if (status) {
		dprintk("Failed RSA init %d\n", status);
		status = -EIO;
		goto out;
	}

	pss.bits = kat->bit_length;
	pss.hlen = 32;
	pss.flags = 0;
	pss.halgo = CMRT_HASH_SHA256;
	pss.slen = 10;

	hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	if (!cmrt_is_valid(hc)) {
		dprintk("HC opening failed\n");
		status = -EBUSY;
		goto out;
	}
	status = cmrt_pss_enc(hc, &pss, kat->m, sizeof(kat->m), pss_message);
	if (status) {
		dprintk("PSS ENC failed %d\n", status);
		goto out;
	}

	reverse_words(kat->n, byte_length / 4, r_ctx->key.n);
	reverse_words(kat->d, byte_length / 4, r_ctx->key.d);
	reverse_words(pss_message, byte_length / 4, r_ctx->message);

	pke = cmrt_pke_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(pke)) {
		dprintk("Failed to open %s\n", CONFIG_CRI_PKE_NAME);
		status = -EIO;
		goto out;
	}

	status = cmrt_pke_rsa_sign(pke, r_ctx);

	if (status) {
		goto out;
	}

	reverse_words(r_ctx->signature, byte_length / 4, signature);

	memset(r_ctx->message, 0, byte_length);

	status = pke_rsa_pub(pke, &r_ctx->key,
			     r_ctx->signature, r_ctx->message);
	if (status) {
		goto out;
	}

	reverse_words(r_ctx->message, byte_length / 4, pss_message);

	status = cmrt_pss_verify(hc, &pss, kat->m, sizeof(kat->m), pss_message);
	if (status) {
		dprintk("PSS verify failed\n");
		status = -EINVAL;
		goto out;
	}

out:
	if (cmrt_is_valid(pke)) {
		cmrt_pke_close(pke);
	}
	if (cmrt_is_valid(hc)) {
		cmrt_hc_close(hc);
	}
	destroy_workcontext(0);
	if (status) {
		return false;
	} else {
		return true;
	}
}

uint32_t rsa_run_kat(void)
{
	/* Run the sw kdf kats and expect output vector match */
	for (uint32_t i = 0; i < RSA_KAT_VECTORS_COUNT; ++i) {
		if (!run_rsa(&rsa_kat_vectors[i])) {
			cmrt_eac_kat_error(CORE_ID_PKE, -EXDEV, -EFAULT);
		}
	}
	return 1;
}
