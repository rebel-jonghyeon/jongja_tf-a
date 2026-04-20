/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file pke4_ecc_driver.h
 *
 * @brief Functions for ECC operations.
 */

#ifndef CMRT_PKE4_ECC_DRIVER_H
#define CMRT_PKE4_ECC_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

cmrt_ecc_curve_t cmrt_pke_get_curve(uint32_t curve);

int cmrt_pke_ecc_pairwise_consistency_check(cmrt_ecc_curve_t curve,
					    const uint32_t asset_type,
					    const uint8_t *private_key,
					    const uint8_t *public_key_x,
					    const uint8_t *public_key_y);

#ifdef __cplusplus
}
#endif
#endif
