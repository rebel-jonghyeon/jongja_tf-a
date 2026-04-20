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
static int cmrt_pke_load_ecc_params(cmrt_ecc_curve_t curve)
{
	uint32_t curvelen = cmrt_pke_get_curve_length(curve);

	memcpy(pke_addr(eccPrivKeyGen_q, curve, 0), curve->order, curvelen);
	return 0;
}
#endif

static uint32_t cmrt_pke_make_private_key(cmrt_pke_t pke,
					  cmrt_ecc_curve_t curve,
					  void *private_key)
{
	int ret = 0;

	uint8_t valid = FALSE;

	uint32_t *key_slot = pke_addr(eccPrivKeyGen_k, curve, 0);

#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE) || \
	defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
	uint32_t *key_ptr;
#endif

	uint32_t curvelen = cmrt_pke_get_curve_length(curve);
#ifdef CONFIG_CMRT_PKE_32_BIT
	uint32_t length = curve->length;
#else /* 64-bit */
	uint32_t length = ((curve->length - 1) / 2) + 1;
#endif

	ISSUE_MAU_COMMAND(LOAD, SLOT(eccPrivKeyGen_q), length);
	ISSUE_MAU_COMMAND(INT_SUB, R_MAU_ONE, length);
	ISSUE_MAU_COMMAND(STORE, SLOT(eccPrivKeyGen_q), length);

	ret = cmrt_pke_wait();
	if (ret) {
		goto err;
	}

	while (valid == FALSE) {
#ifdef CONFIG_CMRT_PKE_CP_REVERSE_BYTES
		ret = cmrt_pke_get_true_random(private_key, curve->length * sizeof(uint32_t));
#else
		ret = cmrt_pke_get_true_random(private_key, curvelen);
#endif
		if (ret) {
			goto err;
		}

		int ret = COPY_TO_PKE(private_key, curvelen, key_slot, eccPrivKeyGen_rnd);
		if (ret) {
			goto err;
		}

		if (curve->curve == NIST_SECP521r1) {
#ifdef CONFIG_CMRT_PKE_32_BIT
			key_slot[length - 1] &= 0x1FF;
#else /* 64-bit */
			key_slot[length - 2] &= 0x1FF;
#endif
		}

		ISSUE_MAU_COMMAND(SET_MAND, SLOT(eccPrivKeyGen_q), length);
		ISSUE_MAU_COMMAND(COMPARE, SLOT(eccPrivKeyGen_k), length);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		int compare = MAU_GET_COMPARE_RESULT();
		if (compare == 1) {
			ISSUE_MAU_COMMAND(LOAD, SLOT(eccPrivKeyGen_k), length);
			ISSUE_MAU_COMMAND(INT_ADD, R_MAU_ONE, length);
			ISSUE_MAU_COMMAND(STORE, SLOT(eccPrivKeyGen_k), length);

			ret = cmrt_pke_wait();
			if (ret) {
				goto err;
			}

			valid = TRUE;
		}
	}

#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE) || \
	defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
	if ((curve->curve_is_Montgomery == TRUE) || (curve->curve_is_Edwards == TRUE)) {
		key_ptr = pke_addr(out_eccPrivKeyGen_k, curve, 0);

		if (curve->curve == CURVE_25519) {
			key_ptr[0] = key_ptr[0] & 0xFFFFFFF8;
			key_ptr[7] = key_ptr[7] & 0x7FFFFFFF;
			key_ptr[7] = key_ptr[7] | 0x40000000;
		} else if (curve->curve == CURVE_448) {
			key_ptr[0] = key_ptr[0] & 0xFFFFFFFC;
			key_ptr[13] = key_ptr[13] | 0x80000000;
		}
	}
#endif

	ret = COPY_FROM_PKE(pke_addr(out_eccPrivKeyGen_k, curve, 0), curvelen, (uint8_t *)private_key, out_eccPrivKeyGen_rnd);
err:
	return ret;
}


int cmrt_pke_ecc_private_keygen(cmrt_pke_t pke,
				cmrt_ecc_curve_t curve,
				void *private_key)
{
	int ret = -EIO;

	if (!pke || !curve || !private_key) {
		return -EINVAL;
	}

#ifndef CRI_PKE_STANDALONE
	cmrt_dd_t *dd = pke->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#endif

	if (IS_PKE_IDLE()) {
		goto err;
	}

#ifdef CONFIG_CMRT_PKE_32_BIT
	uint32_t length = curve->length;
#else /* 64-bit */
	uint32_t length = ((curve->length - 1) / 2) + 1;
#endif

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err;
	}

	if ((curve->ROM_mod == SPEC_MOD_IN_ROM) && (curve->spec_mod == SPEC_MOD_ENABLED)) {
		ISSUE_MCG_COMMAND(ECC_ROM_SETUP, curve->spec_mod, curve->ROM_mod, curve->curve);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		ISSUE_MAU_COMMAND(SET_MAND, SLOT(eccPrivKeyGen_q), length);
#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE) || \
	defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
		if ((curve->curve_is_Montgomery == TRUE) || (curve->curve_is_Edwards == TRUE)) {
			ISSUE_MAU_COMMAND(COPY, ROM_SLOT(eccMontRomSlot_q), length);
		} else {
			ISSUE_MAU_COMMAND(COPY, ROM_SLOT(eccRomSlot_q), length);
		}
#else
		ISSUE_MAU_COMMAND(COPY, ROM_SLOT(eccRomSlot_q), length);
#endif

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		ret = cmrt_pke_make_private_key(pke, curve, private_key);
		if (ret) {
			goto err;
		}
	} else {
#if defined(CONFIG_CMRT_PKE_BRAINPOOL_P192T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P224T1) || \
	defined(CONFIG_CMRT_PKE_BRAINPOOL_P256T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P320T1) || \
	defined(CONFIG_CMRT_PKE_BRAINPOOL_P384T1) || defined(CONFIG_CMRT_PKE_BRAINPOOL_P512T1)
#if defined(CONFIG_CMRT_PKE_X25519_CURVE) || defined(CONFIG_CMRT_PKE_X448_CURVE) || \
	defined(CONFIG_CMRT_PKE_ED25519_CURVE) || defined(CONFIG_CMRT_PKE_ED448_CURVE)
		if ((curve->curve_is_Montgomery == FALSE) && (curve->curve_is_Edwards == FALSE)) {
			ret = cmrt_pke_load_ecc_params(curve);
			if (ret) {
				goto err;
			}

			ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, length);

			ret = cmrt_pke_wait();
			if (ret) {
				goto err;
			}

			ret = cmrt_pke_make_private_key(pke, curve, private_key);
			if (ret) {
				goto err;
			}
		} else {
			ret = -EINVAL;
		}
#else
		ret = cmrt_pke_load_ecc_params(curve);
		if (ret) {
			goto err;
		}

		ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, length);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		ret = cmrt_pke_make_private_key(pke, curve, private_key);
		if (ret) {
			goto err;
		}
#endif
#else /* Montgomery curves */
		ret = -EINVAL;
		goto err;
#endif /* short Weierstrass curves not in PKE ROM */
	}

	static const uint32_t cmds_cp[] = {
		SLOT_CMD(SET_MAND,      SLOT(eccPrivKeyGen_q)),
		SLOT_CMD(COPY,          R_MAU_ZERO),
		SLOT_CMD(SET_MAND,      SLOT(eccPrivKeyGen_k)),
		SLOT_CMD(COPY,          R_MAU_ZERO),
		SLOT_CMD(SET_MAND,      SLOT(eccPrivKeyGen_rnd)),
		SLOT_CMD(COPY,          R_MAU_ZERO),
	};

	ret = cmrt_pke_mau_command_sequence(cmds_cp, sizeof(cmds_cp)/sizeof(uint32_t), length);
err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return ret;
}
