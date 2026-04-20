/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */

#ifndef CRI_PKE_KAT_H
#define CRI_PKE_KAT_H

#include <device.h>
#include <drivers/cmrt/eac.h>
#include <drivers/cmrt/cmrt.h>
#include <sic_reg.h>
#include <string.h>
#include <errno.h>

#define BASE_KAT_TIMEOUT 0x8000UL

typedef struct ecdh_kat {
	uint8_t k[28];
	uint8_t Qx[28];
	uint8_t Sx[28];
} ecdh_kat_t;

typedef struct ecdsa_kat {
	uint8_t k[32];
	uint8_t Qx[32];
	uint8_t Qy[32];
	uint8_t no[64];
	uint8_t hs[32];
	uint8_t r[32];
	uint8_t s[32];
} ecdsa_kat_t;

typedef struct rsa_kat {
#ifdef CONFIG_CRI_FIPS_140_MODE
	uint32_t bit_length;
	uint8_t n[256];
	uint8_t d[256];
	uint8_t m[256];
#else
	uint32_t n[64];
	uint32_t d[64];
#endif
} rsa_kat_t;

/**
 * Runs PKE ECDH kat tests
 *
 * @param dev Pointer to the device.
 * @param flags CRI_O_HWC_FORCE_KAT executes KAT test unconditionally.
 * @retval 1 when all KATs successfully ran
 *         0 when tests were skipped
 *         When some test fails device halts.
 */
uint32_t ecdh_run_kat(struct device *dev, uint32_t flags);

/**
 * Runs PKE ECDSA kat tests
 *
 * @param dev Pointer to the device.
 * @param flags CRI_O_HWC_FORCE_KAT executes KAT test unconditionally.
 * @retval 1 when all KATs successfully ran
 *         0 when tests were skipped
 *         When some test fails device halts.
 */
uint32_t ecdsa_run_kat(struct device *dev, uint32_t flags);

/**
 * Runs PKE RSA kat tests
 *
 * @retval 1 when all KATs successfully ran
 *         0 when tests were skipped
 *         When some test fails device halts.
 */
uint32_t rsa_run_kat(void);

#endif
