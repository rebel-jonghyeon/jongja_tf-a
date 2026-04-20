/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
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

int cmrt_pke_ecc_pairwise_consistency_check(cmrt_pke_t pke,
					    cmrt_ecc_curve_t curve,
					    const uint8_t *private_key,
					    const uint8_t *pub_x,
					    const uint8_t *pub_y)
{
	int ret = -EIO;

	uint32_t generator[66];
	uint32_t secret[66];

	if (!pke || !curve || !private_key || !pub_x) {
		return -EINVAL;
	}

#ifndef CRI_PKE_STANDALONE
	cmrt_dd_t *dd = pke->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#endif

	if ((curve->curve != NIST_SECP192r1) &&
	    (curve->curve != NIST_SECP224r1) &&
	    (curve->curve != NIST_SECP256r1) &&
	    (curve->curve != NIST_SECP384r1) &&
	    (curve->curve != NIST_SECP521r1)) {
		ret = -EINVAL;
		goto err;
	}

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

	if ((curve->ROM_mod == SPEC_MOD_IN_ROM) && (curve->spec_mod == SPEC_MOD_ENABLED)) {
		ISSUE_MCG_COMMAND(ECC_ROM_SETUP, curve->spec_mod, curve->ROM_mod, curve->curve);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		ISSUE_MAU_COMMAND(SET_SPECIAL_PARAMS, curve->curve, length);

		/* NB: gx is in Montgomery form */
		static const uint32_t cmds_get_generator[] = {
			SLOT_CMD(SET_MAND,      ROM_SLOT(eccRomSlot_gx)),
			SLOT_CMD(MONT_MUL,      R_MAU_ONE),
			SLOT_CMD(CANON,         0),
			SLOT_CMD(STORE,         SLOT(out_eccTest_gx)),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_get_generator, sizeof(cmds_get_generator)/sizeof(uint32_t), length);
		if (ret) {
			goto err;
		}

		ret = COPY_FROM_PKE(pke_addr(out_eccPrivKeyGen_gx, curve, 0), curvelen, (uint8_t *)generator, out_eccPrivKeyGen_rnd);
		if (ret) {
			goto err;
		}

		ret = cmrt_pke_ecdh(pke, curve, private_key, generator, secret);
		if (ret) {
			goto err;
		}

		if (memcmp(secret, pub_x, cmrt_pke_get_curve_length(curve)) != 0) {
			ret = -EIO;
			goto err;
		}

		if (pub_y != NULL) {
			ret = COPY_TO_PKE(pub_x, curvelen, pke_addr(eccOnCurve_px, curve, 0), eccOnCurve_rnd);
			if (ret) {
				goto err;
			}

			ret = COPY_TO_PKE(pub_y, curvelen, pke_addr(eccOnCurve_py, curve, 0), eccOnCurve_rnd);
			if (ret) {
				goto err;
			}

			ISSUE_MCG_COMMAND(ECC_ONCURVE, curve->spec_mod, curve->ROM_mod, curve->curve);

			ret = cmrt_pke_wait();
			if (ret) {
				goto err;
			}
		}
	} else {
		ret = -EINVAL;
	}
err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return ret;
}
