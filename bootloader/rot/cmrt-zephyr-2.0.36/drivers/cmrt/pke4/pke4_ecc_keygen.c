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
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>

#include <drivers/cmrt/crypto/pke_dpasl.h>
#include <drivers/cmrt/crypto/pke_common.h>
#include <drivers/cmrt/pke4/pke4_driver.h>

#include "shake256.h"
#include "pke_string.h"
#include "pke4_hash.h"
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
static int cmrt_pke_load_ecc_params(cmrt_ecc_curve_t curve)
{
	uint32_t curvelen = cmrt_pke_get_curve_length(curve);

	memcpy(pke_addr(eccKeyGen_b, curve, 0), curve->b, curvelen);
	memcpy(pke_addr(eccKeyGen_gx, curve, 0), curve->base_x, curvelen);
	memcpy(pke_addr(eccKeyGen_gy, curve, 0), curve->base_y, curvelen);
	memcpy(pke_addr(eccKeyGen_q, curve, 0), curve->order, curvelen);
	memcpy(pke_addr(eccKeyGen_p, curve, 0), curve->prime_field, curvelen);
	memcpy(pke_addr(eccKeyGen_a, curve, 0), curve->a, curvelen);
	return 0;
}
#endif

static int __pke_ecc_keygen(cmrt_pke_t pke,
			    const struct dpa_ecc_curve_struct *curve,
			    const uint32_t opcode,
			    const void *key_share0,
			    const void *key_share1,
			    void *public_x,
			    void *public_y)
{
	int ret = -EIO;

	if (!pke || !curve || !key_share0 || !key_share1 || !public_x) {
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

#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE) || \
		defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
	if ((curve->curve_is_Montgomery == TRUE) || (curve->curve_is_Edwards == TRUE)) {
		memcpy(pke_addr(eccKeyGen_s0, curve, 0), key_share0, curvelen);
		memcpy(pke_addr(eccKeyGen_s1, curve, 0), key_share1, curvelen);
	} else {
		ret = COPY_TO_PKE(key_share0, curvelen, pke_addr(eccKeyGen_s0, curve, 0), eccKeyGen_rnd);
		if (ret) {
			goto err;
		}

		ret = COPY_TO_PKE(key_share1, curvelen, pke_addr(eccKeyGen_s1, curve, 0), eccKeyGen_rnd);
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

	if ((curve->ROM_mod == SPEC_MOD_IN_ROM) && (curve->spec_mod == SPEC_MOD_ENABLED)) {
		cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(opcode, curve->spec_mod, curve->ROM_mod, curve->curve));
	} else {
#if defined(CONFIG_CMRT_PKE_BRAINPOOL_P192T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P224T1) || \
	defined(CONFIG_CMRT_PKE_BRAINPOOL_P256T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P320T1) || \
	defined(CONFIG_CMRT_PKE_BRAINPOOL_P384T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P512T1)
#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE) || \
	defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
#ifdef CONFIG_CMRT_PKE_32_BIT
		uint32_t length = curve->length;
#else /* 64-bit */
		uint32_t length = ((curve->length - 1) / 2) + 1;
#endif
		if ((curve->curve_is_Montgomery == FALSE) && (curve->curve_is_Edwards == FALSE)) {
			ret = cmrt_pke_load_ecc_params(curve);
			if (ret) {
				goto err;
			}

			cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(opcode, curve->spec_mod, curve->ROM_mod, length));
		} else {
			ret = -EINVAL;
		}
#else /* Montgomery curves */
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
#endif
#else
		ret = -EINVAL;
#endif /* short Weierstrass curves not in PKE ROM */
	}

	cmrt_pke_response_t *const resp = &pke->response;
	resp->curve = curve;
	resp->bits = 0;
	resp->copies_to_make = 1;
	resp->slot = out_eccKeyGen_rnd;
	resp->ret_param[0].bits = 0;
	resp->ret_param[0].rAddr = public_x;
#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE) || \
	defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
	if (curve->curve_is_Montgomery == TRUE) {
		resp->ret_param[0].pkeAddr = pke_addr(out_ecdhMont_px, curve, 0);
	} else if (curve->curve_is_Edwards == TRUE) {
		resp->ret_param[0].pkeAddr = pke_addr(out_eddsaKeyGen_pyc, curve, 0);

#ifdef CONFIG_CMRT_PKE_ED448_CURVE
		if (curve->curve == CURVE_448) {
			resp->copies_to_make = 2;
			resp->ret_param[1].bits = 8;
			resp->ret_param[1].rAddr = ((uint8_t *)public_x) + 56;
			resp->ret_param[1].pkeAddr = pke_addr(out_eddsaKeyGen_pyc + 1, curve, 0);
		}
#endif
	} else {
		resp->ret_param[0].pkeAddr = pke_addr(out_eccKeyGen_px, curve, 0);
	}
#else
	resp->ret_param[0].pkeAddr = pke_addr(out_eccKeyGen_px, curve, 0);
#endif
	if (public_y != NULL) {
		resp->copies_to_make = 2;
		resp->ret_param[1].bits = 0;
		resp->ret_param[1].rAddr = public_y;
		resp->ret_param[1].pkeAddr = pke_addr(out_eccKeyGen_py, curve, 0);
	}
err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return cmrt_dd_autosync(&pke->ddc, ret);
}

static int pke_ecc_keygen_extended(cmrt_pke_t pke,
				   cmrt_ecc_curve_t curve,
				   uint32_t opcode,
				   const void *priv_key_share1,
				   const void *priv_key_share2,
				   void *pub_x,
				   void *pub_y)
{
	return __pke_ecc_keygen(pke, curve, opcode, priv_key_share1, priv_key_share2, pub_x, pub_y);
}

static int pke_ecc_keygen(cmrt_pke_t pke,
			  cmrt_ecc_curve_t curve,
			  uint32_t opcode,
			  const void *priv_key,
			  void *pub_x,
			  void *pub_y)
{
	uint8_t key_share0[68];
	uint8_t key_share1[68];

	int ret = cmrt_pke_blind_private_key(pke, curve, priv_key, key_share0, key_share1);
	if (ret == 0) {
		ret = __pke_ecc_keygen(pke, curve, opcode, key_share0, key_share1, pub_x, pub_y);
	}
	return ret;
}

int cmrt_pke_ecdh_keygen_extended(cmrt_pke_t pke,
				  cmrt_ecc_curve_t curve,
				  const void *priv_key_share1,
				  const void *priv_key_share2,
				  void *pub_x)
{
	uint32_t opcode = 0;

#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE)
	if (curve->curve_is_Montgomery == FALSE) {
		opcode = PKE_ECDH_KEYGEN_OPCODE;
	} else {
		opcode = ECDH_MONTGOMERY_KEYGEN_EPH;
	}
#else
	opcode = PKE_ECDH_KEYGEN_OPCODE;
#endif

	return pke_ecc_keygen_extended(pke, curve, opcode, priv_key_share1, priv_key_share2, pub_x, NULL);
}

int z_impl_cmrt_pke_ecdh_keygen(cmrt_pke_t pke,
			 cmrt_ecc_curve_t curve,
			 const void *priv_key,
			 void *pub_x)
{
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

		return pke_ecc_keygen(pke, curve, ECDH_MONTGOMERY_KEYGEN_EPH, key, pub_x, NULL);
	}
#endif

	return pke_ecc_keygen(pke, curve, PKE_ECDH_KEYGEN_OPCODE, priv_key, pub_x, NULL);
}

#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE)
int z_impl_cmrt_pke_rfc7748_keygen(cmrt_pke_t pke,
			    cmrt_ecc_curve_t curve,
			    const void *priv_key,
			    void *pub_x)
{
	return cmrt_pke_ecdh_keygen(pke, curve, priv_key, pub_x);
}
#endif

int cmrt_pke_ecdsa_keygen_extended(cmrt_pke_t pke,
				   cmrt_ecc_curve_t curve,
				   const void *priv_key_share1,
				   const void *priv_key_share2,
				   void *pub_x, void *pub_y)
{
	uint32_t opcode = ECDSA_KEYGEN;

#ifdef CONFIG_CMRT_PKE_SM2_CURVE
	if (curve->curve == SM2_CURVE) {
		opcode = SM2DSA_KEYGEN;
	}
#endif

	return pke_ecc_keygen_extended(pke, curve, opcode, priv_key_share1, priv_key_share2, pub_x, pub_y);
}

int z_impl_cmrt_pke_ecdsa_keygen(cmrt_pke_t pke,
			  cmrt_ecc_curve_t curve,
			  const void *priv_key,
			  void *pub_x, void *pub_y)
{
	uint32_t opcode = ECDSA_KEYGEN;

#ifdef CONFIG_CMRT_PKE_SM2_CURVE
	if (curve->curve == SM2_CURVE) {
		opcode = SM2DSA_KEYGEN;
	}
#endif

	return pke_ecc_keygen(pke, curve, opcode, priv_key, pub_x, pub_y);
}

#if defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
int cmrt_pke_eddsa_keygen_extended(cmrt_pke_t pke,
				   cmrt_ecc_curve_t curve,
				   const void *priv_key_share1,
				   const void *priv_key_share2,
				   void *pub_x)
{
	uint32_t opcode = 0;

	if (0) {
#ifdef CONFIG_CMRT_PKE_ED25519_CURVE
	} else if (curve->curve == CURVE_25519) {
		opcode = ED25519_KEYGEN;
#endif
#ifdef CONFIG_CMRT_PKE_ED448_CURVE
	} else if (curve->curve == CURVE_448) {
		opcode = ED448_KEYGEN;
#endif
	} else {
		return -EINVAL;
	}

	return pke_ecc_keygen_extended(pke, curve, opcode, priv_key_share1, priv_key_share2, pub_x, NULL);
}

int cmrt_pke_ecc_x_keygen(cmrt_pke_t pke,
			  cmrt_ecc_curve_t curve,
			  const void *priv_key,
			  void *pub_x)
{
	return cmrt_pke_ecdh_keygen(pke, curve, priv_key, pub_x);
}

int cmrt_pke_ecc_x_keygen_extended(cmrt_pke_t pke,
				   cmrt_ecc_curve_t curve,
				   const void *priv_key_share1,
				   const void *priv_key_share2,
				   void *pub_x)
{
	return cmrt_pke_ecdh_keygen_extended(pke, curve, priv_key_share1, priv_key_share2, pub_x);
}

int cmrt_pke_ecc_xy_keygen(cmrt_pke_t pke,
			   cmrt_ecc_curve_t curve,
			   const void *priv_key,
			   void *pub_x, void *pub_y)
{
	return cmrt_pke_ecdsa_keygen(pke, curve, priv_key, pub_x, pub_y);
}

int cmrt_pke_ecc_xy_keygen_extended(cmrt_pke_t pke,
				    cmrt_ecc_curve_t curve,
				    const void *priv_key_share1,
				    const void *priv_key_share2,
				    void *pub_x, void *pub_y)
{
	return cmrt_pke_ecdsa_keygen_extended(pke, curve, priv_key_share1, priv_key_share2, pub_x, pub_y);
}

#ifndef CRI_PKE_STANDALONE
int pke_eddsa_keygen(cmrt_pke_t pke,
		     cmrt_ecc_curve_t curve,
		     const void *priv_key,
		     void *pub_x,
		     void *prefix)
#else
int pke_eddsa_keygen(cmrt_pke_t pke,
		     cmrt_ecc_curve_t curve,
		     const void *priv_key,
		     void *pub_x)
#endif
{
	uint32_t opcode = 0;
	uint32_t ret = -EINVAL;
#ifndef CRI_PKE_STANDALONE
	uint32_t hash[29];
	uint32_t curvelen = cmrt_pke_get_curve_length(curve);
#endif

	if (0) {
#ifdef CONFIG_CMRT_PKE_ED25519_CURVE
	} else if (curve->curve == CURVE_25519) {
#ifndef CRI_PKE_STANDALONE
		/* decode the private key to scalar */
		if (get_hash(HC_HASH_ALGO_SHA_512, priv_key, curvelen, hash, 64) != 64) {
			ret = -EIO;
			goto err;
		}

		/* Only first 32 bytes are used from hash */
		/* decode scalar */
		uint32_t *p = hash;
		p[0] &= 0xfffffff8;
		p[7] &= 0x7fffffff;
		p[7] |= 0x40000000;

		/* Second 32 bytes are prefix for nonce */
		if (prefix != NULL) {
			(void)memcpy(prefix, &hash[8], 32);
		}
#endif
		opcode = ED25519_KEYGEN;
#endif
#ifdef CONFIG_CMRT_PKE_ED448_CURVE
	} else if (curve->curve == CURVE_448) {
#ifndef CRI_PKE_STANDALONE
		/* Hash the 57-byte private key using SHAKE256(x, 114)
		 * to a 114-octet large buffer, denoted h.
		 * Only the lower 57 bytes are used.
		 */
		shake_ctx_t shake_ctx;
		shake_ctx_t *shake = cmrt_shake256_init(&shake_ctx);

		cmrt_shake256_update(shake, priv_key, 57);
		cmrt_shake256_finish(shake, hash, 114);

		/* Prune the buffer:
		 * The two least significant bits of the first octet are cleared.
		 */
		uint8_t *ptr = (uint8_t *) hash;
		ptr[0] &= 0xfcu;
		/* all eight bits the last octet are cleared. */
		ptr[57 - 1] = 0;
		/* the highest bit of the second to last octet is set */
		ptr[57 - 2] |= 0x80u;

		if (prefix != NULL) {
			(void)memcpy(prefix, &ptr[57], 57);
		}
#endif
		opcode = ED448_KEYGEN;
#endif
	} else {
		ret = -EINVAL;
		goto err;
	}

#ifndef CRI_PKE_STANDALONE
	ret = pke_ecc_keygen(pke, curve, opcode, hash, pub_x, NULL);
#else
	ret = pke_ecc_keygen(pke, curve, opcode, priv_key, pub_x, NULL);
#endif

err:
	return ret;
}

int z_impl_cmrt_pke_eddsa_keygen(cmrt_pke_t pke,
			  cmrt_ecc_curve_t curve,
			  const void *priv_key,
			  void *pub_x)
{
#ifndef CRI_PKE_STANDALONE
	return pke_eddsa_keygen(pke, curve, priv_key, pub_x, NULL);
#else
	return pke_eddsa_keygen(pke, curve, priv_key, pub_x);
#endif
}
#endif

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_ecdsa_keygen(cmrt_pke_t pke, cmrt_ecc_curve_t curve,
		const void *priv_key, void *pub_x, void *pub_y)

{
	z_syscall_verify_pke_context(pke);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(priv_key, curvelen));

	Z_OOPS(Z_SYSCALL_MEMORY_READ(pub_x, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(pub_x, curvelen));

	Z_OOPS(Z_SYSCALL_MEMORY_READ(pub_y, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(pub_y, curvelen));

	return z_impl_cmrt_pke_ecdsa_keygen(pke, pcurve, priv_key, pub_x, pub_y);

}
#include <syscalls/cmrt_pke_ecdsa_keygen_mrsh.c>

static inline int z_vrfy_cmrt_pke_ecdh_keygen(cmrt_pke_t pke, cmrt_ecc_curve_t curve,
		const void *priv_key, void *pub_x)

{
	z_syscall_verify_pke_context(pke);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(priv_key, curvelen));

	Z_OOPS(Z_SYSCALL_MEMORY_READ(pub_x, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(pub_x, curvelen));

	return z_impl_cmrt_pke_ecdh_keygen(pke, pcurve, priv_key, pub_x);

}
#include <syscalls/cmrt_pke_ecdh_keygen_mrsh.c>

static inline int z_vrfy_cmrt_pke_rfc7748_keygen(cmrt_pke_t pke, cmrt_ecc_curve_t curve,
		const void *priv_key, void *pub_x)
{
	z_syscall_verify_pke_context(pke);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(priv_key, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(pub_x, curvelen));

	return z_impl_cmrt_pke_rfc7748_keygen(pke, pcurve, priv_key, pub_x);
}
#include <syscalls/cmrt_pke_rfc7748_keygen_mrsh.c>

static inline int z_vrfy_cmrt_pke_eddsa_keygen(cmrt_pke_t pke, cmrt_ecc_curve_t curve,
		const void *priv_key, void *pub_x)
{
	z_syscall_verify_pke_context(pke);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(priv_key, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(pub_x, curvelen));

	return z_impl_cmrt_pke_eddsa_keygen(pke, pcurve, priv_key, pub_x);
}
#include <syscalls/cmrt_pke_eddsa_keygen_mrsh.c>


#endif /* CONFIG_USERSPACE */
