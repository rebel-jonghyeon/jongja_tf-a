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
#include <drivers/cmrt/pke4/pke4_math.h>

#include "shake256.h"
#include "pke4_hash.h"
#else

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#include "pke4_math.h"
#endif
#include "pke4_random.h"

static int __pke_eddsa_sign1(cmrt_pke_t pke,
			     const struct dpa_ecc_curve_struct *curve,
			     const void *nonce,
			     const void *key_share0,
			     const void *key_share1,
			     void *sign_r)
{
	int ret = -EIO;

	uint32_t opcode = 0;

	if (!pke || !curve || !nonce || !key_share0 || !key_share1 || !sign_r) {
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

	if (curve->curve == CURVE_25519) {
		opcode = ED25519_SIGN_PHASE_1;
		memcpy(pke_addr(eddsaSign1_n0, curve, 0), nonce, 2 * curvelen);
	} else if (curve->curve == CURVE_448) {
		opcode = ED448_SIGN_PHASE_1;

		memset(pke_addr(eddsaSign1_n2, curve, 0), 0x00, curvelen);

		memcpy(pke_addr(eddsaSign1_n0, curve, 0), nonce, (2 * curvelen) + 2);

		uint32_t *ptr1 = pke_addr(eddsaSign1_magic, curve, 0);
		uint32_t *ptr2 = pke_addr(eddsaSign1_n2, curve, 0);
		ptr2[0] = ptr1[0];
	} else {
		ret = -EINVAL;
		goto err;
	}

	memcpy(pke_addr(eddsaSign1_s0, curve, 0), key_share0, curvelen);
	memcpy(pke_addr(eddsaSign1_s1, curve, 0), key_share1, curvelen);

	if ((curve->ROM_mod == SPEC_MOD_IN_ROM) && (curve->spec_mod == SPEC_MOD_ENABLED)) {
		cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(opcode, curve->spec_mod, curve->ROM_mod, curve->curve));
	} else {
		ret = -EINVAL;
	}

	cmrt_pke_response_t *const resp = &pke->response;
	if (curve->curve == CURVE_25519) {
		resp->copies_to_make = 1;
		resp->curve = curve;
		resp->bits = 0;
		resp->slot = out_eddsaSign1_rnd;
		resp->ret_param[0].bits = 0;
		resp->ret_param[0].rAddr = sign_r;
		resp->ret_param[0].pkeAddr = pke_addr(out_eddsaSign1_r, curve, 0);
	} else {
		resp->copies_to_make = 1;
		resp->curve = curve;
		resp->bits = 0;
		resp->slot = out_eddsaSign1_rnd;
		resp->copies_to_make = 1;
		resp->ret_param[0].bits = 114 * 8;
		resp->ret_param[0].rAddr = sign_r;
		resp->ret_param[0].pkeAddr = pke_addr(out_eddsaSign1_r, curve, 0);
	}

err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return ret;
}


/*!
 * @brief Generate EdDSA signature phase 1.
 *
 * Generate EdDSA signature.  The signature is typically the direct
 * concatenation of R || S.  This function returns the R component.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve ed25519/ed448.
 * @param nonce Pointer to nonce.
 * @param priv_key Pointer to private key.
 * @param sign_r buffer to receive signature R-part.
 * @retval Zero on success, -ERRNO on error.
 */
static int cmrt_pke_eddsa_sign_phase1(cmrt_pke_t pke,
				      cmrt_ecc_curve_t curve,
				      const void *nonce,
				      const void *priv_key,
				      void *sign_r)
{
	int ret = 0;

	uint8_t key_share0[56];
	uint8_t key_share1[56];
#ifndef CRI_PKE_STANDALONE
	uint32_t hash[29];
	uint32_t curvelen = cmrt_pke_get_curve_length(curve);

	if (0) {
#ifdef CONFIG_CMRT_PKE_ED25519_CURVE
	} else if (curve->curve == CURVE_25519) {
		/* decode the private key to scalar */
		if (get_hash(HC_HASH_ALGO_SHA_512, priv_key, curvelen, hash, 32) != 32) {
			ret = -EIO;
			goto err;
		}

		/* Only first 32 bytes are used from hash */
		/* decode scalar */
		uint32_t *p = hash;
		p[0] &= 0xfffffff8;
		p[7] &= 0x7fffffff;
		p[7] |= 0x40000000;
#endif
#ifdef CONFIG_CMRT_PKE_ED448_CURVE
	} else if (curve->curve == CURVE_448) {
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
#endif
	} else {
		return -EINVAL;
	}

	ret = cmrt_pke_blind_private_key(pke, curve, hash, key_share0, key_share1);
#else
	ret = cmrt_pke_blind_private_key(pke, curve, priv_key, key_share0, key_share1);
#endif
	if (ret) {
		goto err;
	}

	ret = __pke_eddsa_sign1(pke, curve, nonce, key_share0, key_share1, sign_r);
err:
	return ret;
}


/*!
 * @brief Generate EdDSA signature phase 2.
 *
 * Generate EdDSA signature on an Edwards curve (Ed25519 or Ed448).
 * The signature is typically the direct
 * concatenation of R || S.  This function returns the S component.
 *
 * @param context Pointer to the device.
 * @param curve Pointer to curve ed25519/ed448.
 * @param challenge Pointer to challenge
 * @param sign_s buffer to receive signature S-part.
 * @retval Zero on success, -ERRNO on error.
 */
static int
cmrt_pke_eddsa_sign_phase2(cmrt_pke_t pke,
			   const struct dpa_ecc_curve_struct *curve,
			   const void *challenge,
			   void *sign_s)
{
	int ret = -EIO;

	uint32_t opcode = 0;

	if (!pke || !curve || !challenge || !sign_s) {
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
#ifdef CONFIG_CMRT_PKE_32_BIT
	uint32_t length = curve->length;
	memset(pke_addr(eddsaSign2_blank, curve, 0), 0x00, length * sizeof(uint32_t));
#else /* 64-bit */
	uint32_t length = ((curve->length - 1) / 2) + 1;
	memset(pke_addr(eddsaSign2_blank, curve, 0), 0x00, length * sizeof(uint64_t));
#endif

	if (curve->curve == CURVE_25519) {
		opcode = ED25519_SIGN_PHASE_2;
		memcpy(pke_addr(eddsaSign2_c1, curve, 0), challenge, 2 * curvelen);
	} else if (curve->curve == CURVE_448) {
		opcode = ED448_SIGN_PHASE_2;
		memcpy(pke_addr(eddsaSign2_c1, curve, 0), challenge, (2 * curvelen) + 2);
	} else {
		ret = -EINVAL;
		goto err;
	}

	static const uint32_t cmds_cp[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(SET_MAND,      SLOT(eddsaSign2_c0)),
		SLOT_CMD(COPY,          SLOT(eddsaSign2_c1)),
		SLOT_CMD(SET_MAND,      SLOT(eddsaSign2_c1)),
		SLOT_CMD(COPY,          SLOT(eddsaSign2_c2)),
		SLOT_CMD(SET_MAND,      SLOT(eddsaSign2_c2)),
		SLOT_CMD(COPY,          SLOT(eddsaSign2_blank)),
		SLOT_CMD(SET_MAND,      SLOT(eddsaSign2_blank)),
		SLOT_CMD(COPY,          R_MAU_ZERO),
	};

	ret = cmrt_pke_mau_command_sequence(cmds_cp, sizeof(cmds_cp)/sizeof(uint32_t), length);
	if (ret) {
		goto err;
	}

	uint32_t cmd = MCG_PREPARE_COMMAND(opcode, curve->spec_mod,
					   curve->ROM_mod, curve->curve);
	ret = cmrt_pke_issue_mcg_command(pke, cmd);
	if (ret < 0) {
		goto err;
	}

	enum eddsaSign2 slotno = out_eddsaSign2_s_25519;
	if (curve->curve == CURVE_448) {
		/* memcpy used curvelen + ? */
		slotno = out_eddsaSign2_s_448;
		/* the ten most significant bits of the final octets
		 * are always zero.  since the last byte is not set by
		 * pke, it has to be cleared by sw.
		 */
		((uint8_t *) sign_s)[56] = 0;
	}
	cmrt_pke_response_t *const resp = &pke->response;
	resp->curve = curve;
	resp->bits = 0; /* might want to adjust this? */
	resp->copies_to_make = 1;
	resp->slot = out_ecdsaSign_rnd;
	resp->ret_param[0].bits = 0;
	resp->ret_param[0].rAddr = sign_s;
	resp->ret_param[0].pkeAddr = pke_addr(slotno, curve, 0);

	/* left here, no autosync either! */
err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return ret;
}

#ifndef CRI_PKE_STANDALONE
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

int z_impl_cmrt_pke_eddsa_sign(cmrt_pke_t context,
			       cmrt_ecc_curve_t curve,
			       const void *priv_key,
			       const void *message,
			       unsigned int msglen,
			       void *sign_r, void *sign_s)
{
	int ret = 0;
	uint32_t public_y[15];
	uint32_t nonce[29];
	uint32_t sign_nonce[15];
	uint32_t hash[29];
	uint32_t prefix[15];
	uint32_t outputlen;

	uint32_t curvelen = cmrt_pke_get_curve_length(curve);

	ret = pke_eddsa_keygen(context, curve, priv_key, public_y, prefix);
	if (ret) {
		goto err;
	}
	/* keygen function is not yet finished if async */
	if ((context->ddc.flags & CMRT_O_SYNC) == 0) {
		ret = cmrt_dd_sync(&context->ddc);
		if (ret != 0) {
			goto err;
		}
	}

	if (0) {
#ifdef CONFIG_CMRT_PKE_ED25519_CURVE
	} else if (curve->curve == CURVE_25519) {
		outputlen = curvelen;

		struct iov hashinv[] = {
			{ prefix, 32 },
			{ (void *)message, msglen }
		};
		if (get_hashv(HC_HASH_ALGO_SHA_512, hashinv, 2, nonce, 64) != 64) {
			ret = -EIO;
			goto err;
		};
#endif
#ifdef CONFIG_CMRT_PKE_ED448_CURVE
	} else if (curve->curve == CURVE_448) {
		outputlen = curvelen + 1;

		/* SHAKE256(dom4(F, C) || prefix || PH(M), 114)
		 * where F = 0, C is empty, so that
		 * dom4(F, C) = "SigEd448" || 0x00 || 0x00,
		 * i.e. 53 69 67 45 64 34 34 38 00 00
		 */
		shake_ctx_t shake_ctx;
		shake_ctx_t *ctx = cmrt_shake256_init(&shake_ctx);

		cmrt_shake256_update(ctx, SIGED448, sizeof(SIGED448));
		cmrt_shake256_update(ctx, prefix, 57);
		cmrt_shake256_update(ctx, message, msglen);
		cmrt_shake256_finish(ctx, nonce, 114);
#endif
	} else {
		ret = -EINVAL;
		goto err;
	}

	ret = cmrt_pke_eddsa_sign_phase1(context, curve, nonce, priv_key, sign_nonce);
	if (ret == 0) {
		ret = cmrt_pke_sync(context);
	}
	if (ret != 0) {
		goto err;
	}

	if (0) {
#ifdef CONFIG_CMRT_PKE_ED25519_CURVE
	} else if (curve->curve == CURVE_25519) {
		struct iov hashinv2[] = {
			{ sign_nonce, curvelen },
			{ public_y, curvelen},
			{ (void *)message, msglen }
		};
		if (get_hashv(HC_HASH_ALGO_SHA_512, hashinv2, 3, hash, 64) != 64) {
			ret = -EIO;
			goto err;
		};
#endif
#ifdef CONFIG_CMRT_PKE_ED448_CURVE
	} else if (curve->curve == CURVE_448) {
		/* SHAKE256(dom4(F, C) || R || A || PH(M), 114) */
		shake_ctx_t shake_ctx;
		shake_ctx_t *ctx = cmrt_shake256_init(&shake_ctx);

		cmrt_shake256_update(ctx, SIGED448, sizeof(SIGED448));
		cmrt_shake256_update(ctx, sign_nonce, 57);
		cmrt_shake256_update(ctx, public_y, 57);
		cmrt_shake256_update(ctx, message, msglen);
		cmrt_shake256_finish(ctx, hash, 114);
#endif
	} else {
		ret = -EINVAL;
		goto err;
	}

	ret = cmrt_pke_eddsa_sign_phase2(context, curve, hash, sign_s);
	ret = cmrt_dd_autosync(&context->ddc, ret);
	if (ret >= 0) {
		memcpy(sign_r, sign_nonce, outputlen);
	}

err:
	return ret;
}
#endif

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_eddsa_sign(cmrt_pke_t context, cmrt_ecc_curve_t curve,
	const void *priv_key, const void *message, unsigned int msglen,
	void *sign_r, void *sign_s)
{
	z_syscall_verify_pke_context(context);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(priv_key, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(message, msglen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(sign_r, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(sign_s, curvelen));

	return z_impl_cmrt_pke_eddsa_sign(context, pcurve, priv_key, message,
					  msglen, sign_r, sign_s);
}
#include <syscalls/cmrt_pke_eddsa_sign_mrsh.c>

#endif /* CONFIG_USERSPACE */
