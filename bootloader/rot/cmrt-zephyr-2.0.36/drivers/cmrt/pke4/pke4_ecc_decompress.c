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

	memcpy(pke_addr(eccKeyGen_b, curve, 0), curve->b, curvelen);
	memcpy(pke_addr(eccKeyGen_p, curve, 0), curve->prime_field, curvelen);
	memcpy(pke_addr(eccKeyGen_a, curve, 0), curve->a, curvelen);
	return 0;
}
#endif

static int __pke_ecc_decompress(cmrt_pke_t pke,
				cmrt_ecc_curve_t curve,
				const void *pub_x,
				void *pub_y,
				int sy)
{
	int ret = -EIO;

	if (!pke || !curve || !pub_x || !pub_y) {
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
	uint32_t *sign_of_y = pke_addr(eccDecompress_sy, curve, 0);

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err;
	}

	ret = COPY_TO_PKE(pub_x, curvelen, pke_addr(eccDecompress_px, curve, 0), eccDecompress_rnd);
	if (ret) {
		goto err;
	}
	sign_of_y[0] = sy;

	if ((curve->ROM_mod == SPEC_MOD_IN_ROM) && (curve->spec_mod == SPEC_MOD_ENABLED)) {
		cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(ECC_DECOMPRESS, curve->spec_mod, curve->ROM_mod, curve->curve));
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

		cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(ECC_DECOMPRESS, curve->spec_mod, curve->ROM_mod, length));
#else
		ret = -EINVAL;
#endif
	}

	cmrt_pke_response_t *const resp = &pke->response;
	resp->curve = curve;
	resp->bits = 0;
	resp->copies_to_make = 1;
	resp->slot = out_eccDecompress_rnd;
	resp->ret_param[0].bits = 0;
	resp->ret_param[0].rAddr = pub_y;
	resp->ret_param[0].pkeAddr = pke_addr(out_eccDecompress_py, curve, 0);

err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return ret;
}

int cmrt_pke_ecc_decompress(cmrt_pke_t pke,
			    cmrt_ecc_curve_t curve,
			    const void *pub_x,
			    void *pub_y,
			    int sy)
{
	int ret = __pke_ecc_decompress(pke, curve, pub_x, pub_y, sy);
	return cmrt_dd_autosync(&pke->ddc, ret);
}
