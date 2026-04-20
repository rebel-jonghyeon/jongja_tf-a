/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <stdio.h>
#include <string.h>

#include <device.h>
#include <cri/cmrt/pke.h>
#include <cri/cmrt/hc.h>

#include "common.h"


/*
 * This basic example shows how to use ECDSA calculations.
 *
 * Key and signature parameters are big endian numbers and size of those
 * must match the size of the curve (i.e. 384 bits for P-384 and so on).
 * When input parameters are serialized, padding may need to be added so
 * all parameters are addressed from word-aligned locations. This is
 * particularly important with P521 curve since key size is 521 bits,
 * meaning 65 bytes plus one bit. If hash len is longer than key len,
 * the bytes beyond the key len are ignored.
 *
 * Following example handles one data block, whose size is limited by available
 * SAC memory size. It pushes almost all of the data with cri_ecdsa_update()
 * call. The trailing non-word size data, if any, is pushed with
 * cri_ecdsa_final() call. It is possible to support data larger than SAC
 * memory size. For that cri_ecdsa_update() is to be called multiple times.
 * A minimum of 4 bytes must be pushed with cri_ecdsa_update() in each call.
 * cri_ecdsa_update() can only handle data in multiple of word sizes.
 * Input and output buffer address must always be word aligned.
 */

typedef struct {
	u32_t mode;
	u32_t curve;
	u32_t algorithm;
	u32_t keylen;
	u32_t siglen;
	u32_t msglen;
	u8_t data[0];
} ecdsa_args_t;

enum { MAX_SIG_LEN = 68 };

static int do_ecdsa_sign(ecdsa_args_t *args,
			 u32_t in_used,
			 void *output,
			 u32_t *out_used)
{
	printk("do_ecdsa_sign:\n");
#ifdef CONFIG_SV_PERF_MEAS
	u32_t cycles;
#endif
	u8_t *priv_key = args->data;
	u8_t *msg      = priv_key + ((args->keylen + 3) & ~3);

	HEXDUMP_VAR(priv_key, args->keylen);
	HEXDUMP_VAR(msg, args->msglen);

	/* Open and initialize PKE */
	cri_pke_t pke = cri_pke_open(0);
	if (!cri_is_valid(pke)) {
		err("Cannot open %s!\n", CONFIG_CRI_PKE_NAME);
		return -EIO;
	}
	printk("cri_pke_get_curve: 0x%x\n", args->curve);
	cri_ecc_curve_t curve = cri_pke_get_curve(args->curve);
	int ret;
	if (!curve) {
		err("Failed to obtain a curve: %d\n", args->curve);
		ret = -ENOENT;
		goto out;
	}
	alignas(4) u8_t sig_r_out[MAX_SIG_LEN] = {0};
	alignas(4) u8_t sig_s_out[MAX_SIG_LEN] = {0};
	if (args->curve == CRI_ECC_CURVE_ED448 ||
	    args->curve == CRI_ECC_CURVE_ED25519) {
		printk("cri_pke_eddsa_sign:\n");
#ifdef CONFIG_SV_PERF_MEAS
		plog_set_ref();
#endif
		ret = cri_pke_eddsa_sign(pke, curve, priv_key,
					 msg, args->msglen,
					 &sig_r_out, &sig_s_out);
#ifdef CONFIG_SV_PERF_MEAS
		cycles = plog_get_cycles();
		plog("PKE_cri_pke_eddsa_sign,0x%x,%d,%u", args->curve, args->keylen * 8, cycles);
#endif
	} else {
		printk("cri_pke_ecdsa_sign:\n");
#ifdef CONFIG_SV_PERF_MEAS
		plog_set_ref();
#endif
		ret = cri_pke_ecdsa_sign_hash(pke, curve, priv_key,
					      msg, args->msglen,
					      &sig_r_out, &sig_s_out);
#ifdef CONFIG_SV_PERF_MEAS
		cycles = plog_get_cycles();
		plog("PKE_cri_pke_ecdsa_sign_hash,0x%x,%d,%u",
		     args->curve, args->keylen * 8, cycles);
#endif
	}
	if (ret) {
		err("ecdsa/eddsa sign failed: %d\n", ret);
		ret = -ENOENT;
		goto out;
	}
	ret = cri_pke_sync(pke);
	printk("Core out:\n");
	HEXDUMP_VAR(sig_r_out, args->siglen);
	HEXDUMP_VAR(sig_s_out, args->siglen);
	memcpy(output, &sig_r_out, args->siglen);
	memcpy(output + args->siglen, &sig_s_out, args->siglen);
	*out_used = args->siglen*2;
 out:
	/* Close PKE when done */
	if (cri_is_valid(pke))
		cri_pke_close(pke);
	return ret;
}

static int do_ecdsa_verify(ecdsa_args_t *args,
			   u32_t in_used,
			   void *output,
			   u32_t *out_used)
{
	printk("do_ecdsa_verify:\n");
#ifdef CONFIG_SV_PERF_MEAS
	u32_t cycles;
#endif
	u8_t *pub_x = args->data;
	u8_t *pub_y = pub_x + ((args->keylen + 3) & ~3);
	u8_t *sig_r = pub_y + ((args->keylen + 3) & ~3);
	u8_t *sig_s = sig_r + ((args->siglen + 3) & ~3);
	u8_t *msg   = sig_s + ((args->siglen + 3) & ~3);

	HEXDUMP_VAR(pub_x, args->keylen);
	HEXDUMP_VAR(pub_y, args->keylen);
	HEXDUMP_VAR(sig_r, args->siglen);
	HEXDUMP_VAR(sig_s, args->siglen);
	HEXDUMP_VAR(msg, args->msglen);

	u32_t *result = output;
	result[0] = 0x1; /* FAIL */
	*out_used = 1;

	/* Open and initialize PKE */
	cri_pke_t pke = cri_pke_open(0);
	if (!cri_is_valid(pke)) {
		err("Cannot open %s!\n", CONFIG_CRI_PKE_NAME);
		return -EIO;
	}
	printk("cri_pke_get_curve: %d\n", args->curve);
	cri_ecc_curve_t curve = cri_pke_get_curve(args->curve);
	int ret;
	if (!curve) {
		err("Failed to obtain a curve: %d\n", args->curve);
		ret = -ENOENT;
		goto out;
	}
	const bool eddsa_curve =
		args->curve == CRI_ECC_CURVE_ED448 ||
		args->curve == CRI_ECC_CURVE_ED25519;

	/* Verify ECDSA signature */
	if (eddsa_curve) {
		printk("cri_pke_eddsa_verify:\n");
#ifdef CONFIG_SV_PERF_MEAS
		plog_set_ref();
#endif
		ret = cri_pke_eddsa_verify(pke, curve, pub_x, msg, args->msglen,
					   sig_r, sig_s, NULL);
#ifdef CONFIG_SV_PERF_MEAS
		cycles = plog_get_cycles();
		plog("PKE_cri_pke_eddsa_verify,0x%x,%d,%u", args->curve, args->keylen * 8, cycles);
#endif
	} else {
		printk("cri_pke_ecdsa_verify:\n");
#ifdef CONFIG_SV_PERF_MEAS
		plog_set_ref();
#endif
		ret = cri_pke_ecdsa_verify_hash(pke, curve, pub_x, pub_y,
						msg, args->msglen,
						sig_r, sig_s, NULL);
#ifdef CONFIG_SV_PERF_MEAS
		cycles = plog_get_cycles();
		plog("PKE_cri_pke_ecdsa_verify_hash,0x%x,%d,%u",
		     args->curve, args->keylen * 8, cycles);
#endif
	}
	if (ret) {
		err("ecdsa/eddsa verify failed: %d\n", ret);
		ret = -ENOENT;
		goto out;
	}
	ret = cri_pke_sync(pke);
	if (ret == 0) {
		result[0] = 0x0; /* PASS */
	}
	ret = 0; /* verify failure is not an error */
	printk("Core out: %d\n", result[0]);
 out:
	/* Close PKE when done */
	if (cri_is_valid(pke))
		cri_pke_close(pke);
	return ret;
}

static int do_ecdsa_keygen(ecdsa_args_t *args, u32_t in_used,
			   void *output, u32_t *out_used)
{
	printk("do_ecdsa_keygen:\n");
#ifdef CONFIG_SV_PERF_MEAS
	u32_t cycles;
#endif
	hexdump_var("priv_key", args->data, args->keylen);

	/* Open and initialize PKE */
	cri_pke_t pke = cri_pke_open(0);
	if (!cri_is_valid(pke)) {
		err("Cannot open %s!\n", CONFIG_CRI_PKE_NAME);
		return -EIO;
	}
	printk("cri_pke_get_curve: 0x%x\n", args->curve);
	cri_ecc_curve_t curve = cri_pke_get_curve(args->curve);
	const bool eddsa_curve =
		args->curve == CRI_ECC_CURVE_ED448 ||
		args->curve == CRI_ECC_CURVE_ED25519;
	int ret;
	if (!curve) {
		err("Failed to obtain a curve: %d\n", args->curve);
		ret = -ENOENT;
		goto out;
	}
	alignas(4) u8_t pub_x_out[MAX_SIG_LEN] = {0};
	alignas(4) u8_t pub_y_out[MAX_SIG_LEN] = {0};
	if (eddsa_curve) {
		printk("cri_pke_eddsa_keygen:\n");
#ifdef CONFIG_SV_PERF_MEAS
		plog_set_ref();
#endif
		ret = cri_pke_eddsa_keygen(
			pke, curve, args->data, &pub_x_out);
#ifdef CONFIG_SV_PERF_MEAS
		cycles = plog_get_cycles();
		plog("PKE_cri_pke_eddsa_keygen,0x%x,%d,%u", args->curve, args->keylen * 8, cycles);
#endif
	} else {
		printk("cri_pke_ecdsa_keygen:\n");
#ifdef CONFIG_SV_PERF_MEAS
		plog_set_ref();
#endif
		ret = cri_pke_ecdsa_keygen(
			pke, curve, args->data, &pub_x_out, &pub_y_out);
#ifdef CONFIG_SV_PERF_MEAS
		cycles = plog_get_cycles();
		plog("PKE_cri_pke_ecdsa_keygen,0x%x,%d,%u", args->curve, args->keylen * 8, cycles);
#endif
	}
	if (ret) {
		err("ecdsa/eddsa keygen failed: %d\n", ret);
		ret = -ENOENT;
		goto out;
	}
	ret = cri_pke_sync(pke);
	printk("Core out:\n");
	HEXDUMP_VAR(pub_x_out, args->keylen);
	memcpy(output, &pub_x_out, args->keylen);
	*out_used = args->keylen;
	if (!eddsa_curve) {
		HEXDUMP_VAR(pub_y_out, args->keylen);
		memcpy(output + args->keylen, &pub_y_out, args->keylen);
		*out_used = args->keylen*2;
	}
 out:
	/* Close PKE when done */
	if (cri_is_valid(pke))
		cri_pke_close(pke);
	return ret;
}

static int ecdsa_run(void *input, u32_t in_used,
		     void *output, u32_t *out_used, u32_t out_size)
{
	printk("ecdsa_run:\n");
#ifdef CONFIG_SV_PERF_MEAS
	plog_reset();
#endif

	ecdsa_args_t *args = (ecdsa_args_t *) input;
	int ret;
	switch (args->mode) {
	case 0:
		ret = do_ecdsa_sign(args, in_used, output, out_used);
		break;
	case 1:
		ret = do_ecdsa_verify(args, in_used, output, out_used);
		break;
	case 2:
		ret = do_ecdsa_keygen(args, in_used, output, out_used);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}

const cmd_t cmd_ecdsa = { CMDID_ECDSA, "ECDSA",
			  "Compute ECDSA over input data", ecdsa_run };
