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
#include "pke_internal.h"


static inline int wait(cmrt_pke_t pke)
{
	int ret = cmrt_pke_wait();
	(void)cmrt_pke_irqs(); /* clear any irqs */
	return ret;
}


int cmrt_pke_ec_blind_private_key(cmrt_pke_t pke,
				  const dpa_ecc_curve *curve,
				  const uint8_t *key,
				  uint8_t *key_share0,
				  uint8_t *key_share1)
{
	int ret = -EIO;

	if (!pke || !curve || !key || !key_share0 || !key_share1) {
		return -EINVAL;
	}

#ifndef CRI_PKE_STANDALONE
	cmrt_dd_t *dd = pke->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#endif

	if (IS_PKE_IDLE()) {
		goto err_unlock;
	}

	uint32_t curvelen = cmrt_pke_get_curve_length(curve);
#ifdef CONFIG_CMRT_PKE_32_BIT
	uint32_t length = curve->length;
#else /* 64-bit */
	uint32_t length = ((curve->length - 1) / 2) + 1;
#endif

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err_unlock;
	}
	(void)wait(pke); /* clear the interrupt before issue */

#if defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
	if (curve->curve_is_Edwards == TRUE) {
		memcpy(pke_addr(eccKeyGen_s0, curve, 0), key, curvelen);
	} else {
		ret = COPY_TO_PKE(key, curvelen, pke_addr(eccKeyGen_s0, curve, 0), CMRT_PKE_NO_SLOT);
		if (ret) {
			goto err_unlock;
		}
	}
#else
	ret = COPY_TO_PKE(key, curvelen, pke_addr(eccKeyGen_s0, curve, 0), CMRT_PKE_NO_SLOT);
	if (ret) {
		goto err_unlock;
	}
#endif
	/* Make sure the length of private key is in range. */
	if (curve->curve == NIST_SECP521r1) {
		uint32_t *sk = pke_addr(eccKeyGen_s0, curve, 0);
		sk[16] &= 0x000001ffu;
	}

	if ((curve->ROM_mod == SPEC_MOD_IN_ROM) && (curve->spec_mod == SPEC_MOD_ENABLED)) {
		ISSUE_MCG_COMMAND(EC_BLIND_PRIVATE_KEY, curve->spec_mod, curve->ROM_mod, curve->curve);
	} else {
		memcpy(pke_addr(eccKeyGen_q, curve, 0), curve->order, curvelen);

		ISSUE_MCG_COMMAND(EC_BLIND_PRIVATE_KEY, curve->spec_mod, curve->ROM_mod, length);
	}

	ret = wait(pke);
	if (ret) {
		goto err;
	}

#if defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
	if (curve->curve_is_Edwards == TRUE) {
		memcpy(key_share0, pke_addr(eccKeyGen_s0, curve, 0), curvelen);
		memcpy(key_share1, pke_addr(eccKeyGen_s1, curve, 0), curvelen);

	} else {
		ret = COPY_FROM_PKE(pke_addr(eccKeyGen_s0, curve, 0), curvelen, key_share0, CMRT_PKE_NO_SLOT);
		if (ret) {
			goto err;
		}

		ret = COPY_FROM_PKE(pke_addr(eccKeyGen_s1, curve, 0), curvelen, key_share1, CMRT_PKE_NO_SLOT);
		if (ret) {
			goto err;
		}
	}
#else
	ret = COPY_FROM_PKE(pke_addr(eccKeyGen_s0, curve, 0), curvelen, key_share0, CMRT_PKE_NO_SLOT);
	if (ret) {
		goto err;
	}

	ret = COPY_FROM_PKE(pke_addr(eccKeyGen_s1, curve, 0), curvelen, key_share1, CMRT_PKE_NO_SLOT);
	if (ret) {
		goto err;
	}
#endif

err:
err_unlock:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return ret;
}

int cmrt_pke_xor_ec_blind_private_key(cmrt_pke_t context, const dpa_ecc_curve *curve,
				      const uint8_t *private_key, uint8_t *key_share0,
				      uint8_t *key_share1)
{
	if (!context || !curve || !private_key || !key_share0 || !key_share1) {
		return -EINVAL;
	}

	uint32_t curvelen = cmrt_pke_get_curve_length(curve);

	if (cmrt_pke_get_pseudo_random(key_share0, curvelen, CMRT_PKE_NO_SLOT, 0) != 0) {
		return -ENXIO;
	}

	for (uint32_t i = 0; i < curvelen; i++) {
		key_share1[i] = key_share0[i] ^ private_key[i];
	}
	return 0;
}

int cmrt_pke_blind_private_key(cmrt_pke_t context,
			       cmrt_ecc_curve_t curve,
			       const void *key, void *share1, void *share2)
{
	if (curve == NULL) {
		return -EINVAL;
	}

	if (curve->blinding == NULL) {
		return 0;
	}

	return curve->blinding(context, curve, key, share1, share2);
}
