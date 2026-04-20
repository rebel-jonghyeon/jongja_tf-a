/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CRI_SW_KDF_KAT_H
#define CRI_SW_KDF_KAT_H

#include <device.h>
#include <cri/cmrt/eac.h>
#include <sic_reg.h>
#include <string.h>
#include <errno.h>

typedef struct {
	const uint8_t *z;
	const uint32_t z_length;
	const uint8_t *salt;
	const uint32_t salt_length;
	const uint8_t *fixed_info;
	const uint32_t fixed_info_length;
	const uint8_t *output;
	const uint32_t output_length;
} kdf_one_step_kat_t;

typedef struct {
	const uint8_t *z;
	const uint32_t z_length;
	const uint8_t *salt;
	const uint32_t salt_length;
	const uint8_t *label;
	const uint32_t label_length;
	const uint8_t *context;
	const uint32_t context_length;
	const uint32_t length;
	const uint8_t *output;
	const uint32_t output_length;
} kdf_two_step_kat_t;

/**
 * Runs one-step KDF sp800_108 and 800_56C kat
 *
 * @retval 1 when all KATs successfully ran
 *         0 when tests were skipped
 *         When some test fails device halts.
 */
uint32_t sw_one_step_kdf_run_kat(void);

/**
 * Runs two-step KDF 800_56C kat
 *
 * @retval 1 when all KATs successfully ran
 *         0 when tests were skipped
 *         When some test fails device halts.
 */
uint32_t sw_two_step_kdf_run_kat(void);

#endif
