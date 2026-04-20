/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef LIBPERSO_PERSO_H
#define LIBPERSO_PERSO_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Set SW_BOOT_STATUS register to tell HLOS that perso is running.
 *
 * @param bits Bits to set.
 * @param mask Bits to clear.
 */
void cri_set_boot_status(uint32_t bits, uint32_t mask);

/**
 * Set SCRATCH_0 register to tell HLOS the run result of the perso.
 *
 * @param status Run status.
 */
#define cri_set_perso_status(status) cri_write_reg(CMRT_SIC_BASE, R_SCRATCH_0, (status))

/**
 * Enable or disable debug mode.
 *
 * @param new New debug mode.
 * @param old Old debug mode.
 * @return Zero on success, ERRNO on error.
 */
int cri_set_debug_mode(bool new, bool *old);

/**
 * Burn DGOK.
 *
 * @return Zero on success, ERRNO on error.
 */
int cri_burn_dgok(void);

/**
 * Initialize OEC version.
 *
 * If OEC version is 0 then it is changed to 1, otherwise do nothing.
 *
 * @return Zero on success, ERRNO on error.
 */
int cri_init_oec_version(void);

/**
 * Get index of the lifecycle.
 *
 * Can be used to verify lifecycle value validity.
 *
 * @param value Lifecycle value.
 * @return Index value or negative on error.
 */
int cri_lifecycle_to_index(uint32_t value);

/**
 * Get lifecycle value at given index.
 *
 * @param index Lifecycle index.
 * @return Lifecycle value or -1 for invalid index.
 */
uint32_t cri_index_to_lifecycle(int index);

/**
 * Set lifecycle to OTP.
 *
 * @param value Lifecycle value.
 * @return Zero on success, ERRNO on error.
 */
int cri_set_lifecycle(uint32_t value);

#endif
