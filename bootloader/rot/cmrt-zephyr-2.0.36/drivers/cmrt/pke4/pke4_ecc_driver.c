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

#ifdef CONFIG_CMRT_PKE_NIST_P192
extern const struct dpa_ecc_curve_struct NIST_CURVE_P192;
#endif
#ifdef CONFIG_CMRT_PKE_NIST_P224
extern const struct dpa_ecc_curve_struct NIST_CURVE_P224;
#endif
#ifdef CONFIG_CMRT_PKE_NIST_P256
extern const struct dpa_ecc_curve_struct NIST_CURVE_P256;
#endif
#ifdef CONFIG_CMRT_PKE_SECP256K1
extern const struct dpa_ecc_curve_struct CURVE_SECP256K1;
#endif
#ifdef CONFIG_CMRT_PKE_NIST_P384
extern const struct dpa_ecc_curve_struct NIST_CURVE_P384;
#endif
#ifdef CONFIG_CMRT_PKE_NIST_P521
extern const struct dpa_ecc_curve_struct NIST_CURVE_P521;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P192R1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P192R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P224R1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P224R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P256R1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P256R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P320R1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P320R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P384R1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P384R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P512R1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P512R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P192T1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P192T1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P224T1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P224T1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P256T1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P256T1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P320T1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P320T1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P384T1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P384T1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P512T1
extern const struct dpa_ecc_curve_struct BRAINPOOL_CURVE_P512T1;
#endif
#ifdef CONFIG_CMRT_PKE_FRP256_CURVE
extern const struct dpa_ecc_curve_struct FRP_CURVE_P256;
#endif
#ifdef CONFIG_CMRT_PKE_X25519_CURVE
extern const struct dpa_ecc_curve_struct MONTGOMERY_CURVE_P25519;
#endif
#ifdef CONFIG_CMRT_PKE_ED25519_CURVE
extern const struct dpa_ecc_curve_struct EDWARDS_CURVE_ED25519;
#endif
#ifdef CONFIG_CMRT_PKE_X448_CURVE
extern const struct dpa_ecc_curve_struct MONTGOMERY_CURVE_P448;
#endif
#ifdef CONFIG_CMRT_PKE_ED448_CURVE
extern const struct dpa_ecc_curve_struct EDWARDS_CURVE_ED448;
#endif
#ifdef CONFIG_CMRT_PKE_SM2_CURVE
extern const struct dpa_ecc_curve_struct PRC_SM2_CURVE_P256;
#endif

cmrt_ecc_curve_t z_impl_cmrt_pke_get_curve(uint32_t curve)
{
	switch (curve) {
#ifdef CONFIG_CMRT_PKE_NIST_P192
	case CMRT_ECC_CURVE_NIST_P192:
		return &NIST_CURVE_P192;
#endif
#ifdef CONFIG_CMRT_PKE_NIST_P224
	case CMRT_ECC_CURVE_NIST_P224:
		return &NIST_CURVE_P224;
#endif
#ifdef CONFIG_CMRT_PKE_NIST_P256
	case CMRT_ECC_CURVE_NIST_P256:
		return &NIST_CURVE_P256;
#endif
#ifdef CONFIG_CMRT_PKE_NIST_P384
	case CMRT_ECC_CURVE_NIST_P384:
		return &NIST_CURVE_P384;
#endif
#ifdef CONFIG_CMRT_PKE_NIST_P521
	case CMRT_ECC_CURVE_NIST_P521:
		return &NIST_CURVE_P521;
#endif
#ifdef CONFIG_CMRT_PKE_SECP256K1
	case CMRT_ECC_CURVE_SECP256K1:
		return &CURVE_SECP256K1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P192R1
	case CMRT_ECC_CURVE_BRAINPOOL_P192R1:
		return &BRAINPOOL_CURVE_P192R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P224R1
	case CMRT_ECC_CURVE_BRAINPOOL_P224R1:
		return &BRAINPOOL_CURVE_P224R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P256R1
	case CMRT_ECC_CURVE_BRAINPOOL_P256R1:
		return &BRAINPOOL_CURVE_P256R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P320R1
	case CMRT_ECC_CURVE_BRAINPOOL_P320R1:
		return &BRAINPOOL_CURVE_P320R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P384R1
	case CMRT_ECC_CURVE_BRAINPOOL_P384R1:
		return &BRAINPOOL_CURVE_P384R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P512R1
	case CMRT_ECC_CURVE_BRAINPOOL_P512R1:
		return &BRAINPOOL_CURVE_P512R1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P192T1
	case CMRT_ECC_CURVE_BRAINPOOL_P192T1:
		return &BRAINPOOL_CURVE_P192T1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P224T1
	case CMRT_ECC_CURVE_BRAINPOOL_P224T1:
		return &BRAINPOOL_CURVE_P224T1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P256T1
	case CMRT_ECC_CURVE_BRAINPOOL_P256T1:
		return &BRAINPOOL_CURVE_P256T1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P320T1
	case CMRT_ECC_CURVE_BRAINPOOL_P320T1:
		return &BRAINPOOL_CURVE_P320T1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P384T1
	case CMRT_ECC_CURVE_BRAINPOOL_P384T1:
		return &BRAINPOOL_CURVE_P384T1;
#endif
#ifdef CONFIG_CMRT_PKE_BRAINPOOL_P512T1
	case CMRT_ECC_CURVE_BRAINPOOL_P512T1:
		return &BRAINPOOL_CURVE_P512T1;
#endif
#ifdef CONFIG_CMRT_PKE_FRP256_CURVE
	case CMRT_ECC_CURVE_ANSSI_FRP256V1:
		return &FRP_CURVE_P256;
#endif
#ifdef CONFIG_CMRT_PKE_X25519_CURVE
	case CMRT_ECC_CURVE_25519:
		return &MONTGOMERY_CURVE_P25519;
#endif
#ifdef CONFIG_CMRT_PKE_ED25519_CURVE
	case CMRT_ECC_CURVE_ED25519:
		return &EDWARDS_CURVE_ED25519;
#endif
#ifdef CONFIG_CMRT_PKE_ED448_CURVE
	case CMRT_ECC_CURVE_ED448:
		return &EDWARDS_CURVE_ED448;
#endif
#ifdef CONFIG_CMRT_PKE_X448_CURVE
	case CMRT_ECC_CURVE_448:
		return &MONTGOMERY_CURVE_P448;
#endif
#ifdef CONFIG_CMRT_PKE_SM2_CURVE
	case CMRT_ECC_CURVE_SM2:
		return &PRC_SM2_CURVE_P256;
#endif
	default:
		return NULL;
	}
	return NULL;
}

uint32_t z_impl_cmrt_pke_get_curve_length(cmrt_ecc_curve_t curve)
{
	if (cmrt_pke_verify_curve(curve) == NULL) {
		return 0;
	}
#ifdef CONFIG_CMRT_PKE_NIST_P521
	if (curve == &NIST_CURVE_P521) {
		return 66;
	}
#endif
	return curve->length * sizeof(uint32_t);
}


#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline cmrt_ecc_curve_t z_vrfy_cmrt_pke_get_curve(uint32_t curve)
{
	/* In user mode the cmrt_ecc_curve_t is not a real curve pointer, but
	 * uses the curve id masquerading as a matching typed pointer to keep
	 * the api fully compatible. The returned curve is looked up by the
	 * passed in argument used as an integer parameter into
	 * the supervisor-side cmrt_pke_get_curve(). */

	if (z_impl_cmrt_pke_get_curve(curve) != NULL) {
		return (cmrt_ecc_curve_t)curve;
	}
	return NULL;
}
#include <syscalls/cmrt_pke_get_curve_mrsh.c>

static inline uint32_t z_vrfy_cmrt_pke_get_curve_length(cmrt_ecc_curve_t curve)
{
	cmrt_ecc_curve_t pcurve = cmrt_pke_verify_user_curve(curve);
	return z_impl_cmrt_pke_get_curve_length(pcurve);
}
#include <syscalls/cmrt_pke_get_curve_length_mrsh.c>

#endif /* CONFIG_USERSPACE */
