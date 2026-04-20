/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#ifndef CMRT_PKE_DPASL_H
#define CMRT_PKE_DPASL_H

#ifndef CRI_PKE_STANDALONE
#include <drivers/cmrt/pke4/pke4_reg.h>
#include <drivers/cmrt/pke4/pke4_driver.h>
#else
#include <pke4_reg.h>
#include <pke4_driver.h>
#endif

#ifndef CRI_PKE_STANDALONE
#define DPA_MAGIC_NUMBER 0x55AA55AAUL
#define word_t uint32_t
#endif

/**
 * \ingroup dpa_ecc_struct
 * \brief A function pointer to a blinding function that will split a scalar
 * as required by the relevant hardware implementation.
 */
typedef struct dpa_ecc_curve_struct dpa_ecc_curve;

#define TRUE 1
#define FALSE 0

typedef int (*dpa_blinding)(cmrt_pke_t pke, const dpa_ecc_curve *curve,
			    const uint8_t *private_key, uint8_t *key_share_1,
			    uint8_t *key_share_2);

int cmrt_pke_ec_blind_private_key(cmrt_pke_t context, const dpa_ecc_curve *curve,
				  const uint8_t *key, uint8_t *key_share0,
				  uint8_t *key_share1);

int cmrt_pke_xor_ec_blind_private_key(cmrt_pke_t context,
				      const dpa_ecc_curve *curve,
				      const uint8_t *private_key,
				      uint8_t *key_share0,
				      uint8_t *key_share1);

struct dpa_ecc_curve_struct {
	/* Number of word_t computer words required to
	 * represent a coordinate on the elliptic curve
	 */
	const size_t length;
	/* curve variables are in Montgomery form */
	const uint8_t curve_is_Montgomery;
	/* curve variables are in Montgomery form */
	const uint8_t curve_is_Edwards;
	/* PKE parameter MCG_SPEC_MOD */
	const MCG_SPEC_MOD spec_mod;
	/* PKE parameter MCG_ROM_MOD */
	const MCG_ROM_MOD ROM_mod;
	/* PKE parameter MCG_ROM_CURVES */
	const MCG_ROM_CURVES curve;
	/* prime field used for elliptic curve */
	const uint32_t *prime_field;
	/* order of elliptic curve */
	const uint32_t *order;
	/* parameter a */
	const uint32_t *a;
	/* parameter b */
	const uint32_t *b;
	/* base coordinate */
	const uint32_t *base_x;
	/* base coordinate */
	const uint32_t *base_y;
	/* misc parameter */
	const uint32_t *misc;
	/* Function for blinding key. */
	const dpa_blinding blinding;
};

#endif
