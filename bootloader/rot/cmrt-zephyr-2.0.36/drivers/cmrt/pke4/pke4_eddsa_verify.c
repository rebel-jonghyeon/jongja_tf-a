/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#ifndef CRI_PKE_STANDALONE
#include <device.h>
#include <init.h>
#include <kernel.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>

#include <drivers/cmrt/crypto/pke_dpasl.h>
#include <drivers/cmrt/crypto/pke_common.h>

#include <drivers/cmrt/pke4/pke4_driver.h>

#include "shake256.h"
#include "pke4_hash.h"
#else

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#endif
#include "pke4_random.h"

static int __pke_eddsa_verify(cmrt_pke_t pke,
			      cmrt_ecc_curve_t curve,
			      const uint8_t *pub_y,
			      const uint8_t *hash,
			      const uint8_t *sign_r,
			      const uint8_t *sign_s,
			      uint8_t *rprime)
{
	int ret = -EIO;

	uint32_t opcode = 0;

	if (!pke || !curve || !pub_y || !hash || !sign_r || !sign_s) {
		return -EINVAL;
	}

	uint32_t *verf_r_ptr = pke_addr(eddsaVerf_r, curve, 0);
	uint32_t *verf_pyc_ptr = pke_addr(eddsaVerf_pyc, curve, 0);

#ifndef CRI_PKE_STANDALONE
	cmrt_dd_t *dd = pke->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#endif

	if (IS_PKE_IDLE()) {
		goto err;
	}

	uint32_t curvelen = cmrt_pke_get_curve_length(curve);
#ifdef CONFIG_CMRT_PKE_32_BIT
	uint32_t length = curve->length;
#else /* 64-bit */
	uint32_t length = ((curve->length - 1) / 2) + 1;
#endif

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err;
	}

	memcpy(verf_pyc_ptr, pub_y, curvelen);
	memcpy(verf_r_ptr, sign_r, curvelen);

	if (curve->curve == CURVE_25519) {
		opcode = ED25519_VERIFY;
		memcpy(pke_addr(eddsaVerf_gy, curve, 0), hash, 2 * curvelen);
	} else if (curve->curve == CURVE_448) {
		opcode = ED448_VERIFY;

		verf_pyc_ptr[curvelen / sizeof(uint32_t)] = (uint32_t) pub_y[56];
		verf_r_ptr[curvelen / sizeof(uint32_t)] = (uint32_t) sign_r[56];

		memcpy(pke_addr(eddsaVerf_gy, curve, 0), hash, (2 * curvelen) + 2);
	} else {
		ret = -EINVAL;
		goto err;
	}

	static const uint32_t cmds_cp[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(SET_MAND,      SLOT(eddsaVerf_c0)),
		SLOT_CMD(COPY,          SLOT(eddsaVerf_gy)),
		SLOT_CMD(SET_MAND,      SLOT(eddsaVerf_c1)),
		SLOT_CMD(COPY,          SLOT(eddsaVerf_gx)),
		SLOT_CMD(SET_MAND,      SLOT(eddsaVerf_c2)),
		SLOT_CMD(COPY,          SLOT(eddsaVerf_q)),
		SLOT_CMD(SET_MAND,      SLOT(eddsaVerf_rxs)),
		SLOT_CMD(COPY,          SLOT(eddsaVerf_s)),
	};

	ret = cmrt_pke_mau_command_sequence(cmds_cp, sizeof(cmds_cp)/sizeof(uint32_t), length);
	if (ret) {
		goto err;
	}

	memcpy(pke_addr(eddsaVerf_s, curve, 0), sign_s, curvelen);

	if ((curve->ROM_mod == SPEC_MOD_IN_ROM) && (curve->spec_mod == SPEC_MOD_ENABLED)) {
		cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(opcode, curve->spec_mod, curve->ROM_mod, curve->curve));
	} else {
		ret = -EINVAL;
	}

	cmrt_pke_response_t *const resp = &pke->response;

	if (rprime == NULL) {
		resp->copies_to_make = 0;
	} else {
		resp->curve = curve;
		resp->bits = 0;
		resp->copies_to_make = 1;
		resp->slot = out_eddsaVerf_rnd;
		resp->ret_param[0].bits = 0;
		resp->ret_param[0].rAddr = rprime;
		resp->ret_param[0].pkeAddr = pke_addr(out_eddsaVerf_r, curve, 0);
	}

err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return cmrt_dd_autosync(&pke->ddc, ret);
}

#ifdef CONFIG_CMRT_PKE_ED448_CURVE
/* F = 0, C is empty string, so that
 * dom4(F, C) = "SigEd448" || 0x00 || 0x00,
 * i.e. 53 69 67 45 64 34 34 38 00 00
 */
static const uint8_t SIGED448[] = {
	0x53, 0x69, 0x67, 0x45, 0x64,
	0x34, 0x34, 0x38, 0x00, 0x00,
};
#endif

#ifndef CRI_PKE_STANDALONE
int z_impl_cmrt_pke_eddsa_verify(cmrt_pke_t pke,
			  cmrt_ecc_curve_t curve,
			  const void *pub_y,
			  const void *message, unsigned int msglen,
			  const void *sign_r, const void *sign_s,
			  void *rprime)

{
	int ret = 0;
	uint8_t hash[114];
	uint32_t curvelen = cmrt_pke_get_curve_length(curve);

	if (0) {
#ifdef CONFIG_CMRT_PKE_ED25519_CURVE
	} else if (curve->curve == CURVE_25519) {
		struct iov hv[] = {
			{ (void *)sign_r, curvelen },
			{ (void *)pub_y, curvelen },
			{ (void *)message, msglen }
		};
		if (get_hashv(HC_HASH_ALGO_SHA_512, hv, 3, hash, 64) != 64) {
			ret = -ENXIO;
			goto err;
		}
#endif
#ifdef CONFIG_CMRT_PKE_ED448_CURVE
	} else if (curve->curve == CURVE_448) {
		/* SHAKE256(dom4(F, C) || R || A || PH(M), 114) */
		shake_ctx_t shake_ctx;
		shake_ctx_t *ctx = cmrt_shake256_init(&shake_ctx);

		cmrt_shake256_update(ctx, SIGED448, sizeof(SIGED448));
		cmrt_shake256_update(ctx, sign_r, 57);
		cmrt_shake256_update(ctx, pub_y, 57);
		cmrt_shake256_update(ctx, message, msglen);
		cmrt_shake256_finish(ctx, hash, 114);
#endif
	} else {
		ret = -EINVAL;
		goto err;
	}

	ret = __pke_eddsa_verify(pke, curve, pub_y, hash, sign_r, sign_s, rprime);
	if (ret != 0) {
		ret = -EINVAL;
	}
err:
	return ret;
}
#else
int z_impl_cmrt_pke_eddsa_verify(cmrt_pke_t pke,
			  cmrt_ecc_curve_t curve,
			  const void *pub_y,
			  const void *message, unsigned int msglen,
			  const void *sign_r, const void *sign_s,
			  void *rprime)

{
	int ret = -EINVAL;
	uint32_t curvelen = cmrt_pke_get_curve_length(curve);

	if (msglen == curvelen) {
		ret =  __pke_eddsa_verify(pke, curve, pub_y, message, sign_r, sign_s, rprime);
	}

	return ret;
}
#endif

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_eddsa_verify(cmrt_pke_t pke, cmrt_ecc_curve_t curve,
		const void *pub_y, const void *message, unsigned int msglen,
		const void *sign_r, const void *sign_s, void *rprime)
{
	z_syscall_verify_pke_context(pke);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(pub_y, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(message, msglen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(sign_r, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(sign_s, curvelen));

	if (rprime != NULL) {
		Z_OOPS(Z_SYSCALL_MEMORY_WRITE(rprime, curvelen));
	}
	return z_impl_cmrt_pke_eddsa_verify(pke, pcurve, pub_y, message, msglen,
					    sign_r, sign_s, rprime);
}
#include <syscalls/cmrt_pke_eddsa_verify_mrsh.c>

#endif /* CONFIG_USERSPACE */
