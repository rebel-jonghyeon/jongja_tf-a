/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef FBOOT_LIFECYCLE_H
#define FBOOT_LIFECYCLE_H

#include <stdint.h>

/**
 * @brief Run handler for the given lifecycle.
 *
 * @param lc The lifecycle value.
 * @return 0 on success, -ERRNO on error, -ENOENT on unknown lifecycle.
 */
int run_lifecycle_op(uint32_t lc);

/**
 * @brief Setup perso root.
 *
 * Perso root is set using the supplied @p root struct. If @p root is NULL,
 * perso root is cleared.
 *
 * @param root Root ID and permissions.
 */
void set_perso_root(const cmrt_omc_root_t *root);

/**
 * @brief Setup root's HW security context.
 *
 * Setup permission registers in FMC, KDC, KTC and OMC.
 *
 * @param omc OTP management core context.
 * @param root Root's permissions.
 * @param valid True to set current root as valid.
 */
void set_root_permissions(cmrt_omc_t omc, const cmrt_omc_root_perm_t *root, bool valid);

/**
 * @brief Setup root's derive path.
 *
 * Derive path is set to root id + the silo byte. It is the basis for all
 * key derivations using the KDC.
 *
 * @param id Root ID.
 * @param silo Silo mode, values are 0 for no caveat and 1 for silo caveat.
 */
void set_derive_path(const cmrt_omc_root_id_t *id, uint8_t silo);

/**
 * @brief Setup and verify boot bypass.
 *
 * Calculates SHA256 over all X and R MPU segments.
 * Requires CONFIG_CMRT_PMU=y.
 *
 * @param setup True to update the value to check when resuming.
 * @return Zero on success, -ERRNO on error.
 */
int fboot_verify_bb(bool setup);

/**
 * @brief Initialize the security monitor.
 *
 * Cache OTP root table and version words, initialize data store.
 *
 * @param omc OMC driver handle.
 */
void fboot_init_sm(cmrt_omc_t omc);

#endif
