/*
 * Copyright (c) 2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file pmu.h
 *
 * @brief Public APIs for the PMU support in the SIC driver.
 */

#ifndef CRI_PMU_H
#define CRI_PMU_H

/**
 * @brief PMU Interface
 * @defgroup pmu_interface PMU Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Allow or disallow entering low power mode.
 *
 * Called from the main application to make it possible to enter low
 * power mode when the idle thread runs next.
 *
 * @param allowed True to enter low power mode.
 * @return Zero on success, -ERRNO on error.
 */
int cri_pmu_low_power(bool allowed);

/**
 * @brief Set idle mode from where HLOS can command low power mode.
 *
 * Typically called from the idle thread after cri_pmu_low_power(true) has
 * been called. Prepares CMRT to enter low power mode. This function can be
 * called from the application thread, too. In that case after calling
 * cri_pmu_to_idle() the application thread must execute the WFI instruction
 * as the final step to let the HLOS know CMRT can be put to sleep.
 */
void cri_pmu_to_idle(void);

/**
 * @brief Continue execution after WFI returned.
 *
 * Typically called from the idle thread after cri_pmu_to_idle() has been
 * called and the WFI instruction returned before HLOS put CMRT to sleep.
 * Restores CMRT into normal state of operation.
 */
void cri_pmu_from_idle(void);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
