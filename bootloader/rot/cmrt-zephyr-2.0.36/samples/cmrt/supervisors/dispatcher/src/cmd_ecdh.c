/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <stdio.h>
#include <string.h>
#include <device.h>
#include <cri/cmrt/pke.h>

#include "common.h"

/*
 * The following example shows how to perform a basic ECDH operation.
 */

typedef struct {
	u32_t mode;
	u32_t curve;
	u32_t curve_len;
	u8_t data[0];
} ecdh_args_t;

enum { MAX_KEY_SIZE = 68 };

static int sync(cri_pke_t pke, int res)
{
	if (res >= 0) {
		res = cri_pke_sync(pke);
	}
	return res;
}

static int do_ecdh_operation(ecdh_args_t *args,
			     u32_t in_used,
			     void *output,
			     u32_t *out_used)
{
	printk("do_ecdh_operation:\n");
	/*************************/
#ifdef CONFIG_SV_PERF_MEAS
	u32_t cycles;

	plog_reset();
	plog_set_ref();
#endif

	const u32_t key_size = args->curve_len;
	u8_t *priv_key = args->data;
	HEXDUMP_VAR(priv_key, key_size);

	/* Open and initialize */
	cri_pke_t pke = cri_pke_open(CRI_O_SYNC);
	int ret = cri_is_valid(pke);
	if (!ret) {
		err("Cannot open %s!\n", CONFIG_CRI_PKE_NAME);
		return -EIO;
	}

	printk("cri_pke_get_curve: 0x%x\n", args->curve);
	cri_ecc_curve_t curve = cri_pke_get_curve(args->curve);
	if (curve == NULL) {
		err("Failed to obtain a curve: %u\n", args->curve);
		ret = -ENOENT;
		goto out;
	}

	alignas(4) u8_t key[MAX_KEY_SIZE] = {0};

	switch (args->mode) {
	case 0: {
		u8_t *peer_key = priv_key + ((key_size + 3) & ~3);
		HEXDUMP_VAR(peer_key, key_size);
		if (args->curve == CRI_ECC_CURVE_448 ||
		    args->curve == CRI_ECC_CURVE_25519){
			printk("cri_pke_rfc7748:\n");
#ifdef CONFIG_SV_PERF_MEAS
			plog_set_ref();
#endif
			ret = cri_pke_rfc7748(pke, curve, priv_key,
					      peer_key, key);
			ret = sync(pke, ret);
#ifdef CONFIG_SV_PERF_MEAS
			cycles = plog_get_cycles();
			plog("PKE_cri_pke_rfc7748,0x%x,%d,%u", args->curve, key_size*8, cycles);
#endif

		} else {
			printk("cri_pke_ecdh:\n");
#ifdef CONFIG_SV_PERF_MEAS
			plog_set_ref();
#endif
			ret = cri_pke_ecdh(pke, curve, priv_key, peer_key, key);
			ret = sync(pke, ret);
#ifdef CONFIG_SV_PERF_MEAS
			cycles = plog_get_cycles();
			plog("PKE_cri_pke_ecdh,0x%x,%d,%u", args->curve, key_size*8, cycles);
#endif
		}
		break;
	}
	case 1: {
		if (args->curve == CRI_ECC_CURVE_448 ||
		    args->curve == CRI_ECC_CURVE_25519) {
			printk("cri_pke_rfc7748_keygen:\n");
#ifdef CONFIG_SV_PERF_MEAS
			plog_set_ref();
#endif
			ret = cri_pke_rfc7748_keygen(pke, curve, priv_key, key);
			ret = sync(pke, ret);
#ifdef CONFIG_SV_PERF_MEAS
			cycles = plog_get_cycles();
			plog("PKE_cri_pke_ecdh_rfc7748_keygen,0x%x,%d,%u",
			     args->curve, key_size*8, cycles);
#endif
		} else {
			printk("cri_pke_ecdh_keygen:\n");
#ifdef CONFIG_SV_PERF_MEAS
			plog_set_ref();
#endif
			ret = cri_pke_ecdh_keygen(pke, curve, priv_key, key);
			ret = sync(pke, ret);
#ifdef CONFIG_SV_PERF_MEAS
			cycles = plog_get_cycles();
			plog("PKE_cri_pke_ecdh_keygen,0x%x,%d,%u", args->curve, key_size*8, cycles);
#endif
		}
		break;
	}
	default: {
		err("Unsupported ECDH mode: %d\n", args->mode);
		ret = -ENOENT;
		goto out;
	}
	}

	if (ret) {
		err("Cri pke ecdh operation failed: %d\n", ret);
		ret = -ENOENT;
		goto out;
	}

	hexdump_var("secret", key, key_size);
	memcpy(output, &key, key_size);
	*out_used = key_size;

 out:
	/* Close always */
	cri_pke_close(pke);
	return ret;
}

static int ecdh_run(void *input, u32_t in_used,
		    void *output, u32_t *out_used, u32_t out_size)
{
	printk("ecdh_run:\n");
	ecdh_args_t *args = (ecdh_args_t *) input;
	return do_ecdh_operation(args, in_used, output, out_used);
}

const cmd_t cmd_ecdh = { CMDID_ECDH, "ECDH",
			 "Run ECDH key exchange operations", ecdh_run };
