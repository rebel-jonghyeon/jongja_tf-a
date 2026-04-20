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

	memcpy(pke_addr(ecdhShared_b, curve, 0), curve->b, curvelen);
	memcpy(pke_addr(ecdhShared_q, curve, 0), curve->order, curvelen);
	memcpy(pke_addr(ecdhShared_p, curve, 0), curve->prime_field, curvelen);
	memcpy(pke_addr(ecdhShared_a, curve, 0), curve->a, curvelen);
	return 0;
}
#endif

static int __pke_ecdh_eph(cmrt_pke_t pke,
			  cmrt_ecc_curve_t curve,
			  uint32_t opcode,
			  const void *key_share0,
			  const void *key_share1,
			  const void *peer_key,
			  void *shared_secret)
{
	int ret = -EIO;

	if (!pke || !curve || !key_share0 || !key_share1 || !peer_key || !shared_secret) {
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

#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE)
	if (curve->curve_is_Montgomery == TRUE) {
		memcpy(pke_addr(eccKeyGen_s0, curve, 0), key_share0, curvelen);
		memcpy(pke_addr(ecdhShared_s1, curve, 0), key_share1, curvelen);
	} else {
		ret = COPY_TO_PKE(key_share0, curvelen, pke_addr(eccKeyGen_s0, curve, 0), ecdhShared_rnd);
		if (ret) {
			goto err;
		}

		ret = COPY_TO_PKE(key_share1, curvelen, pke_addr(ecdhShared_s1, curve, 0), ecdhShared_rnd);
		if (ret) {
			goto err;
		}
	}
#else
	ret = COPY_TO_PKE(key_share0, curvelen, pke_addr(eccKeyGen_s0, curve, 0), eccKeyGen_rnd);
	if (ret) {
		goto err;
	}

	ret = COPY_TO_PKE(key_share1, curvelen, pke_addr(eccKeyGen_s1, curve, 0), eccKeyGen_rnd);
	if (ret) {
		goto err;
	}
#endif

#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE)
	if (curve->curve_is_Montgomery == TRUE) {
		memcpy(pke_addr(ecdhMont_gx, curve, 0), peer_key, curvelen);
	} else {
		ret = COPY_TO_PKE(peer_key, curvelen, pke_addr(ecdhShared_px, curve, 0), ecdhShared_rnd);
		if (ret) {
			goto err;
		}
	}
#else
	ret = COPY_TO_PKE(peer_key, curvelen, pke_addr(ecdhShared_px, curve, 0), ecdhShared_rnd);
	if (ret) {
		goto err;
	}
#endif

	if ((curve->ROM_mod == SPEC_MOD_IN_ROM) && (curve->spec_mod == SPEC_MOD_ENABLED)) {
		cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(opcode, curve->spec_mod, curve->ROM_mod, curve->curve));
	} else {
#if defined(CONFIG_CMRT_PKE_BRAINPOOL_P192T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P224T1) || \
	defined(CONFIG_CMRT_PKE_BRAINPOOL_P256T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P320T1) || \
	defined(CONFIG_CMRT_PKE_BRAINPOOL_P384T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P512T1)
#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE)
#ifdef CONFIG_CMRT_PKE_32_BIT
		uint32_t length = curve->length;
#else /* 64-bit */
		uint32_t length = ((curve->length - 1) / 2) + 1;
#endif

		if (curve->curve_is_Montgomery == FALSE) {
			ret = cmrt_pke_load_ecc_params(curve);
			if (ret) {
				goto err;
			}

			cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(PKE_ECDH_SHARED_OPCODE, curve->spec_mod, curve->ROM_mod, length));
		} else {
			ret = -EINVAL;
		}
#else
#ifdef CONFIG_CMRT_PKE_32_BIT
		uint32_t length = curve->length;
#else /* 64-bit */
		uint32_t length = ((curve->length - 1) / 2) + 1;
#endif

		ret = cmrt_pke_load_ecc_params(curve);
		if (ret) {
			goto err;
		}

		cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(PKE_ECDH_SHARED_OPCODE, curve->spec_mod, curve->ROM_mod, length));
#endif
#else /* Montgomery curves */
		ret = -EINVAL;
#endif /* short Weierstrass curves not in PKE ROM */
	}

	cmrt_pke_response_t *const resp = &pke->response;
	resp->curve = curve;
	resp->bits = 0;
	resp->copies_to_make = 1;
	resp->slot = out_ecdhShared_rnd;
	resp->ret_param[0].bits = 0;
	resp->ret_param[0].rAddr = shared_secret;
#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE)
	if (curve->curve_is_Montgomery == TRUE) {
		resp->ret_param[0].pkeAddr = pke_addr(out_ecdhMont_px, curve, 0);
	} else {
		resp->ret_param[0].pkeAddr = pke_addr(out_ecdhShared_sx, curve, 0);
	}
#else
	resp->ret_param[0].pkeAddr = pke_addr(out_ecdhShared_sx, curve, 0);
#endif
err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return cmrt_dd_autosync(&pke->ddc, ret);
}

int z_impl_cmrt_pke_ecdh(cmrt_pke_t pke,
		  cmrt_ecc_curve_t curve,
		  const void *priv_key,
		  const void *peer_key,
		  void *shared_secret)
{
	int ret = 0;

	uint32_t opcode = 0;

	uint8_t key_share0[68];
	uint8_t key_share1[68];

#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE)
	if (curve->curve_is_Montgomery == TRUE) {
		uint32_t key[14];
		uint32_t curvelen = cmrt_pke_get_curve_length(curve);

		memcpy(key, priv_key, curvelen);

		if (curve->curve == CURVE_25519) {
			key[0] = key[0] & 0xFFFFFFF8;
			key[7] = key[7] & 0x7FFFFFFF;
			key[7] = key[7] | 0x40000000;
		} else if (curve->curve == CURVE_448) {
			key[0] = key[0] & 0xFFFFFFFC;
			key[13] = key[13] | 0x80000000;
		}

		ret = cmrt_pke_blind_private_key(pke, curve, key, key_share0, key_share1);
		opcode = ECDH_MONTGOMERY_SHARED_EPH;
	} else {
		ret = cmrt_pke_blind_private_key(pke, curve, priv_key, key_share0, key_share1);
		opcode = PKE_ECDH_SHARED_OPCODE;
	}
#else
	ret = cmrt_pke_blind_private_key(pke, curve, priv_key, key_share0, key_share1);
	opcode = PKE_ECDH_SHARED_OPCODE;
#endif
	if (ret == 0) {
		ret = __pke_ecdh_eph(pke, curve, opcode,
				     key_share0, key_share1, peer_key,
				     shared_secret);
	}
	return ret;
}

#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE)
int z_impl_cmrt_pke_rfc7748(cmrt_pke_t pke,
		     cmrt_ecc_curve_t curve,
		     const void *priv_key, const void *pub_x,
		     void *shared_secret)
{
	return cmrt_pke_ecdh(pke, curve, priv_key, pub_x, shared_secret);
}
#endif

int cmrt_pke_ecdh_extended(cmrt_pke_t pke,
			   cmrt_ecc_curve_t curve,
			   const void *priv_key_share1,
			   const void *priv_key_share2,
			   const void *peer_key,
			   void *shared_secret)
{
	uint32_t opcode = 0;

#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE)
	if (curve->curve_is_Montgomery == FALSE) {
		opcode = PKE_ECDH_SHARED_OPCODE;
	} else {
		opcode = ECDH_MONTGOMERY_SHARED_EPH;
	}
#else
	opcode = PKE_ECDH_SHARED_OPCODE;
#endif

	return __pke_ecdh_eph(pke, curve, opcode, priv_key_share1, priv_key_share2, peer_key, shared_secret);
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_ecdh(cmrt_pke_t pke, cmrt_ecc_curve_t curve,
		const void *priv_key, const void *peer_key, void *shared_secret)
{
	z_syscall_verify_pke_context(pke);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(priv_key, curvelen));

	Z_OOPS(Z_SYSCALL_MEMORY_READ(peer_key, curvelen));

	Z_OOPS(Z_SYSCALL_MEMORY_READ(shared_secret, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(shared_secret, curvelen));

	return z_impl_cmrt_pke_ecdh(pke, pcurve, priv_key, peer_key, shared_secret);
}
#include <syscalls/cmrt_pke_ecdh_mrsh.c>

static inline int z_vrfy_cmrt_pke_rfc7748(cmrt_pke_t pke, cmrt_ecc_curve_t curve,
		const void *priv_key, const void *pub_x, void *shared_secret)
{
	z_syscall_verify_pke_context(pke);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(priv_key, curvelen));

	Z_OOPS(Z_SYSCALL_MEMORY_READ(pub_x, curvelen));

	Z_OOPS(Z_SYSCALL_MEMORY_READ(shared_secret, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(shared_secret, curvelen));

	return z_impl_cmrt_pke_rfc7748(pke, pcurve, priv_key, pub_x, shared_secret);
}
#include <syscalls/cmrt_pke_rfc7748_mrsh.c>

#endif /* CONFIG_USERSPACE */
