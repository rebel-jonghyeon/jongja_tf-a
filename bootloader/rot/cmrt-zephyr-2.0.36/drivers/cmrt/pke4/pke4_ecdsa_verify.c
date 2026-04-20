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
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>

#include <drivers/cmrt/crypto/pke_dpasl.h>
#include <drivers/cmrt/crypto/pke_common.h>

#include <drivers/cmrt/pke4/pke4_driver.h>
#else

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#endif
#include "pke4_random.h"

#if defined(CONFIG_CMRT_PKE_BRAINPOOL_P192T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P224T1) || \
	defined(CONFIG_CMRT_PKE_BRAINPOOL_P256T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P320T1) || \
	defined(CONFIG_CMRT_PKE_BRAINPOOL_P384T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P512T1)
static uint32_t cmrt_pke_load_ecc_params(cmrt_ecc_curve_t curve)
{
	uint32_t curvelen = cmrt_pke_get_curve_length(curve);

	memcpy(pke_addr(ecdsaVerf_b, curve, 0), curve->b, curvelen);
	memcpy(pke_addr(ecdsaVerf_gx, curve, 0), curve->base_x, curvelen);
	memcpy(pke_addr(ecdsaVerf_gy, curve, 0), curve->base_y, curvelen);
	memcpy(pke_addr(ecdsaVerf_q, curve, 0), curve->order, curvelen);
	memcpy(pke_addr(ecdsaVerf_p, curve, 0), curve->prime_field, curvelen);
	memcpy(pke_addr(ecdsaVerf_a, curve, 0), curve->a, curvelen);
	return 0;
}
#endif

static int __pke_ecdsa_verify(cmrt_pke_t pke,
			      cmrt_ecc_curve_t curve,
			      const void *pub_x,
			      const void *pub_y,
			      const void *hash,
			      const uint32_t hash_len,
			      const void *r,
			      const void *s,
			      void *rprime)
{
	int ret = -EIO;

	uint32_t opcode = 0;

	if (!pke || !curve || !pub_x || !pub_y || !hash || !r || !s) {
		return -EINVAL;
	}

#ifndef CRI_PKE_STANDALONE
	cmrt_dd_t *dd = pke->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#endif

	if (IS_PKE_IDLE()) {
		goto err;
	}

	uint32_t curvelen = cmrt_pke_get_curve_length(curve);

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err;
	}

	ret = COPY_TO_PKE(pub_x, curvelen, pke_addr(ecdsaVerf_Px, curve, 0), ecdsaVerf_rnd);
	if (ret) {
		goto err;
	}

	ret = COPY_TO_PKE(pub_y, curvelen, pke_addr(ecdsaVerf_Py, curve, 0), ecdsaVerf_rnd);
	if (ret) {
		goto err;
	}

	if (hash_len >= curvelen) {
		ret = COPY_TO_PKE(hash, curvelen, pke_addr(ecdsaSign_h, curve, 0), ecdsaSign_rnd);
	} else {
		ret = COPY_TO_PKE(hash, hash_len, pke_addr(ecdsaSign_h, curve, 0), ecdsaSign_rnd);
	}
	if (ret) {
		goto err;
	}

	ret = COPY_TO_PKE(r, curvelen, pke_addr(ecdsaVerf_r, curve, 0), ecdsaVerf_rnd);
	if (ret) {
		goto err;
	}

	ret = COPY_TO_PKE(s, curvelen, pke_addr(ecdsaVerf_s, curve, 0), ecdsaVerf_rnd);
	if (ret) {
		goto err;
	}

#ifdef CONFIG_CMRT_PKE_SM2_CURVE
	if (curve->curve == SM2_CURVE) {
		opcode = SM2DSA_VERIFY;
	} else {
		opcode = ECDSA_VERIFY;
	}
#else
	opcode = ECDSA_VERIFY;
#endif

	if ((curve->ROM_mod == SPEC_MOD_IN_ROM) && (curve->spec_mod == SPEC_MOD_ENABLED)) {
		cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(opcode, curve->spec_mod, curve->ROM_mod, curve->curve));
	} else {
#if defined(CONFIG_CMRT_PKE_BRAINPOOL_P192T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P224T1) || \
	defined(CONFIG_CMRT_PKE_BRAINPOOL_P256T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P320T1) || \
	defined(CONFIG_CMRT_PKE_BRAINPOOL_P384T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P512T1)
#ifdef CONFIG_CMRT_PKE_32_BIT
		uint32_t length = curve->length;
#else /* 64-bit */
		uint32_t length = ((curve->length - 1) / 2) + 1;
#endif
		ret = cmrt_pke_load_ecc_params(curve);
		if (ret) {
			goto err;
		}

		cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(opcode, curve->spec_mod, curve->ROM_mod, length));
#else
		ret = -EINVAL;
#endif /* short Weierstrass curves not in PKE ROM */
	}

	cmrt_pke_response_t *const resp = &pke->response;

	if (rprime == NULL) {
		resp->copies_to_make = 0;
	} else {
		resp->curve = curve;
		resp->bits = 0;
		resp->copies_to_make = 1;
		resp->slot = out_ecdsaVerf_rnd;
		resp->ret_param[0].bits = 0;
		resp->ret_param[0].rAddr = rprime;
		resp->ret_param[0].pkeAddr = pke_addr(out_ecdsaVerf_r, curve, 0);
	}

err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return ret;
}

int z_impl_cmrt_pke_ecdsa_verify_hash(cmrt_pke_t pke,
			       cmrt_ecc_curve_t curve,
			       const void *pub_x, const void *pub_y,
			       const void *digest, unsigned int digest_len,
			       const void *sign_r, const void *sign_s,
			       void *rprime)
{
	int ret = __pke_ecdsa_verify(pke, curve, pub_x, pub_y, digest, digest_len, sign_r, sign_s, rprime);
	return cmrt_dd_autosync(&pke->ddc, ret);
}

int z_impl_cmrt_pke_ecdsa_verify(cmrt_pke_t pke,
			  cmrt_ecc_curve_t curve,
			  const void *pub_x,
			  const void *pub_y,
			  const void *digest,
			  const void *sign_r,
			  const void *sign_s,
			  void *rprime)
{
	uint32_t curvelen = cmrt_pke_get_curve_length(curve);
	return cmrt_pke_ecdsa_verify_hash(pke, curve, pub_x, pub_y, digest,
					  curvelen, sign_r, sign_s, rprime);
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_ecdsa_verify(cmrt_pke_t pke, cmrt_ecc_curve_t curve,
		const void *pub_x, const void *pub_y, const void *digest,
		const void *sign_r, const void *sign_s, void *rprime)
{
	z_syscall_verify_pke_context(pke);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(pub_x, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(pub_y, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(digest, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(sign_r, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(sign_s, curvelen));

	if (rprime != NULL) {
		Z_OOPS(Z_SYSCALL_MEMORY_READ(rprime, curvelen));
		Z_OOPS(Z_SYSCALL_MEMORY_WRITE(rprime, curvelen));
	}

	return z_impl_cmrt_pke_ecdsa_verify(pke, pcurve, pub_x, pub_y, digest,
					    sign_r, sign_s, rprime);
}
#include <syscalls/cmrt_pke_ecdsa_verify_mrsh.c>

static inline int z_vrfy_cmrt_pke_ecdsa_verify_hash(cmrt_pke_t pke,
		cmrt_ecc_curve_t curve,
		const void *pub_x, const void *pub_y,
		const void *digest, unsigned int digest_len,
		const void *sign_r, const void *sign_s,
		void *rprime)
{
	z_syscall_verify_pke_context(pke);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(pub_x, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(pub_y, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(digest, digest_len));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(sign_r, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(sign_s, curvelen));

	if (rprime != NULL) {
		Z_OOPS(Z_SYSCALL_MEMORY_WRITE(rprime, curvelen));
	}

	return z_impl_cmrt_pke_ecdsa_verify_hash(pke, pcurve, pub_x, pub_y,
						 digest, digest_len, sign_r,
						 sign_s, rprime);
}
#include <syscalls/cmrt_pke_ecdsa_verify_hash_mrsh.c>

#endif /* CONFIG_USERSPACE */
