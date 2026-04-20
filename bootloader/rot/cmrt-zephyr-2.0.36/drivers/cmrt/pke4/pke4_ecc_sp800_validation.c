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

int cmrt_sp800_public_key_validation(cmrt_pke_t pke,
				     cmrt_ecc_curve_t curve,
				     uint8_t *pub_x,
				     uint8_t *pub_y)
{
	int ret = -EIO;

	uint32_t order[66];
	uint32_t *dummy = order;

	if (!pke || !curve || !pub_x || !pub_y) {
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
		ret = COPY_TO_PKE(pub_x, curvelen, pke_addr(eccOnCurve_px, curve, 0), eccOnCurve_rnd);
		if (ret) {
			goto err;
		}

		ret = COPY_TO_PKE(pub_y, curvelen, pke_addr(eccOnCurve_py, curve, 0), eccOnCurve_rnd);
		if (ret) {
			goto err;
		}

		ISSUE_MCG_COMMAND(ECC_ONCURVE, curve->spec_mod, curve->ROM_mod, curve->curve);

		/* this will cause an error if x, y are not in [0, p-1], and the point-at-infinity
		 * has no numerical representation.
		 */
		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		ISSUE_MCG_COMMAND(ECC_ROM_SETUP, curve->spec_mod, curve->ROM_mod, curve->curve);

		ret = cmrt_pke_wait();
		if (ret) {
			goto err;
		}

		ISSUE_MAU_COMMAND(SET_SPECIAL_PARAMS, curve->curve, length);

		/* Get group order */
		static const uint32_t cmds_get_order[] = {
			SLOT_CMD(SET_MAND,      SLOT(out_eccTest_q)),
			SLOT_CMD(COPY,          ROM_SLOT(eccRomSlot_q)),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_get_order, sizeof(cmds_get_order)/sizeof(uint32_t), length);
		if (ret) {
			goto err;
		}

		ret = COPY_FROM_PKE(pke_addr(out_eccTest_q, curve, 0), curvelen, (uint8_t *)order, out_eccTest_rnd);
		if (ret) {
			goto err;
		}

		/* Check order of the curve. NB: this should fail as generating the point-at-infinity is not
		 * supported in the PKE.
		 */
		ret = cmrt_pke_ecdh(pke, curve, order, pub_x, dummy);
		if (ret) {
			/* Found point-at-infinity */
			cmrt_pke_flush(pke);
			ret = 0;
		} else {
			/* Test failed */
			ret = -EIO;
			goto err;
		}
	} else {
		ret = -EINVAL;
	}
err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	cmrt_pke_close(pke);
	return ret;
}
