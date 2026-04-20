/*
 * Copyright (c) 2017-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file mpu.h
 *
 * @brief Public APIs for the MPU driver.
 */

#ifndef CRI_MPU_H
#define CRI_MPU_H

/**
 * @brief MPU Interface
 * @defgroup mpu_interface MPU Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <mpu_reg.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get number of free MPU rules.
 *
 * Get number of free MPU rules.
 *
 * @return Number of free rules.
 */
int cri_mpu_free_rules(void);

/**
 * @brief Set MPU rule.
 *
 * Set MPU rule for given index.
 *
 * @param index Rule index.
 * @param address End address for the rule.
 * @param privilege Privilege for the rule, e.g. MPU_PRIVILEGE_M.
 * @param bits Mode and other attributes for the rule, e.g. MPU_MODE_WRITABLE.
 * @return Zero on success, -ERRNO on error.
 */
int cri_mpu_set_rule(uint32_t index, uint32_t address, uint32_t privilege, uint32_t bits);

/**
 * @brief Get MPU rule.
 *
 * Get MPU rule for given index.
 *
 * @param index Rule index.
 * @param address End address for the rule.
 * @param privilege Privilege for the rule.
 * @param bits Mode and other attributes for the rule.
 * @return Zero on success, -ERRNO on error.
 */
int cri_mpu_get_rule(uint32_t index, uint32_t *address, uint32_t *privilege, uint32_t *bits);

/**
 * @brief Get next free rule index.
 *
 * Get next free rule index for given privilege. Note that we assume that
 * MPU is correctly set up, i.e. there are first rules for M, then for S,
 * and finally preliminary rules for U.
 *
 * @param privilege Privilege for the rule.
 * @param address End address for the rule.
 * @return Rule index on success, -ERRNO on error.
 */
int cri_mpu_next_free(uint32_t privilege, uint32_t *address);

/**
 * @brief Check if there is access to given address with given parameters.
 *
 * Check if there is access to given address with given parameters.
 *
 * @param address Start address to check.
 * @param size End address to check.
 * @param privilege Privilege for the rule.
 * @param bits Mode and other attributes for the rule.
 * @return true for access OK or false for no access.
 */
bool cri_mpu_has_access(uint32_t address, uint32_t size, uint32_t privilege, uint32_t bits);

#ifdef __cplusplus
}
#endif

#endif
 /** @}*/
