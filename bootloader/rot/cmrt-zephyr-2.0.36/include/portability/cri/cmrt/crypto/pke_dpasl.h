/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#ifndef CMRT_PKE_DPASL_H
#define CMRT_PKE_DPASL_H
#if (CONFIG_CMRT_PKE_VERSION == 0x020000)
#include <cri/cmrt/pke2/pke_reg.h>
#include <cri/cmrt/rsa/pke2/dpa-resist/dpa.h>
#include <cri/cmrt/rsa/pke2/mau/mau_types.h>
#else
#include <cri/cmrt/pke.h>
#include <cri/cmrt/pke3/pke3_reg.h>
#include <cri/cmrt/rsa/pke3/dpa-resist/dpa.h>
#include <cri/cmrt/rsa/pke3/mau/mau_types.h>
#endif

#define DPA_MAGIC_NUMBER 0x55AA55AAUL
#define word_t uint32_t

/**
 * \ingroup dpa_ecc_struct
 * \brief A function pointer to a blinding function that will split a scalar
 * as required by the relevant hardware implementation.
 */

typedef struct dpa_ecc_curve_struct dpa_ecc_curve;

#if (CONFIG_CMRT_PKE_VERSION >= 0x030000)
struct device;
typedef int (*dpa_blinding)(cri_pke_t pke, const dpa_ecc_curve *curve,
    const word_t *private_key, word_t *key_share_1, word_t *key_share_2);

int dpa_mcg_ec_blind_private_key(cri_pke_t context, const dpa_ecc_curve *curve,
				 const word_t *key, word_t *key_share0,
				 word_t *key_share1);

int dpa_xor_ec_blind_private_key(cri_pke_t context,
				 const dpa_ecc_curve *curve,
				 const word_t *private_key,
				 word_t *key_share0,
				 word_t *key_share1);

struct dpa_ecc_curve_struct {
    /* For integrity checking if required */
    const word_t magic_header;
    /* Number of word_t computer words required to
     * represent a coordinate on the elliptic curve
     */
    const size_t length;
    /* uses x-only arithmetic */
    const uint32_t ecdh_is_xonly;
    /* curve variables are in Montgomery form */
    const uint32_t curve_is_Montgomery;
    /* PKE parameter MCG_SPEC_MOD */
    const MCG_SPEC_MOD spec_mod;
    /* PKE parameter MCG_ROM_MOD */
    const MCG_ROM_MOD ROM_mod;
    /* PKE parameter MCG_ROM_CURVES */
    const MCG_ROM_CURVES special_curves;
    /* prime field used for elliptic curve */
    const word_t *prime_field;
    /* order of elliptic curve */
    const word_t *order;
    /* parameter a */
    const word_t *a;
    /* parameter b */
    const word_t *b;
    /* base coordinate */
    const word_t *base_x;
    /* base coordinate */
    const word_t *base_y;
    /* misc parameter */
    const word_t *misc;
    /* Function for blinding key. */
    const dpa_blinding blinding;
    /* For integrity checking if required */
    const word_t magic_footer;
};
#else
struct dpa_ecc_curve_struct {
	/* For integrity checking if required */
	const word_t magic_header;
	/* Number of word_t computer words required to
	 * represent a coordinate on the elliptic curve
	 */
	const size_t length;
	/* Set to TRUE if (x,z) coordinates are used for ECDH public keys */
	const uint32_t ecdh_is_xonly;
	/* Curve parameter number for selecting the elliptic curve that the
	 * PK-engine will use
	 */
	const unsigned int CurveParam;
	/* x-coordinate of the base point used in ECDSA/ECDH */
	const word_t *base_x;
	/* y-coordinate of the base point used in ECDSA/ECDH */
	const word_t *base_y;
	/* An elliptic curve parameter. For examples, in short Weierstrass
	 * of the form y^2=x^3-ax+b.
	 */
	const word_t *b;
	/* The order of the group formed by the points on the elliptic
	 * curve.
	 */
	const word_t *order;
	/* The prime field used by the group formed by the points on the
	 * elliptic curve.
	 */
	const word_t *p;
	/* Function pointer to a preprocessing step. */
	const void *preprocess;
	/* Function for blinding key. */
	const void *blinding;
	/* For integrity checking if required */
	const word_t magic_footer;
};
#endif
#endif
