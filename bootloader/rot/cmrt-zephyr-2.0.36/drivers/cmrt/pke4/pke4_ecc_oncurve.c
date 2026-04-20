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

	memcpy(pke_addr(eccKeyGen_b, curve, 0), curve->b, curvelen);
	memcpy(pke_addr(eccKeyGen_p, curve, 0), curve->prime_field, curvelen);
	memcpy(pke_addr(eccKeyGen_a, curve, 0), curve->a, curvelen);
	return 0;
}
#endif

static int __pke_validate_ecc_key(cmrt_pke_t pke,
				  cmrt_ecc_curve_t curve,
				  uint32_t opcode,
				  const void *pub_x,
				  const void *pub_y)
{
	int ret = -EIO;

	if (!pke || !curve || !pub_x) {
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

	ret = COPY_TO_PKE(pub_x, curvelen, pke_addr(eccOnCurve_px, curve, 0), eccOnCurve_rnd);
	if (ret) {
		goto err;
	}

	if (pub_y != NULL) {
		ret = COPY_TO_PKE(pub_y, curvelen, pke_addr(eccOnCurve_py, curve, 0), eccOnCurve_rnd);
		if (ret) {
			goto err;
		}
	}

	if ((curve->ROM_mod == SPEC_MOD_IN_ROM) && (curve->spec_mod == SPEC_MOD_ENABLED)) {
		ISSUE_MCG_COMMAND(opcode, curve->spec_mod, curve->ROM_mod, curve->curve);
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

		ISSUE_MCG_COMMAND(opcode, curve->spec_mod, curve->ROM_mod, length);
#else
		ret = -EINVAL;
#endif
	}

err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
	ret = cmrt_dd_autosync(&pke->ddc, ret);
#endif
	return ret;
}

int z_impl_cmrt_pke_validate_ecc_xy_key(cmrt_pke_t context,
				 cmrt_ecc_curve_t curve,
				 const void *pub_x,
				 const void *pub_y)
{
	return __pke_validate_ecc_key(context, curve, ECC_ONCURVE, pub_x, pub_y);
}

int cmrt_pke_validate_ecc_x_key(cmrt_pke_t context,
				cmrt_ecc_curve_t curve,
				const void *pub_x)
{
	return __pke_validate_ecc_key(context, curve, ECC_ONCURVE_XONLY, pub_x, NULL);
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_validate_ecc_xy_key(cmrt_pke_t context, cmrt_ecc_curve_t curve,
		const void *pub_x, const void *pub_y)
{
	z_syscall_verify_pke_context(context);

	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	uint32_t curvelen = cmrt_pke_get_curve_length(pcurve);

	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(pub_x, curvelen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(pub_y, curvelen));

	return z_impl_cmrt_pke_validate_ecc_xy_key(context, pcurve, pub_x, pub_y);

}
#include <syscalls/cmrt_pke_validate_ecc_xy_key_mrsh.c>

#endif /* CONFIG_USERSPACE */
