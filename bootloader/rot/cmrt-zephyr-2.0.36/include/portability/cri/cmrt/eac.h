/*
 * Copyright (c) 2018-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file eac.h
 *
 * @brief Public APIs for the EAC driver.
 */

#ifndef CRI_EAC_H
#define CRI_EAC_H

/**
 * @brief EAC Interface
 * @defgroup eac_interface EAC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <stdbool.h>
#include <eac_reg.h>
#include <toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get last NMI error.
 *
 * Typically called at boot.
 *
 * @param clear Clear after reading.
 * @return R_HW_ERROR_INFO0 or 0.
 */
uint32_t cri_eac_last_nmi_error(bool clear);

/**
 * @brief Get last fatal error.
 *
 * Typically called at boot.
 *
 * @param clear Clear after reading.
 * @return R_HW_ERROR_INFO1 or 0.
 */
uint32_t cri_eac_last_fatal_error(bool clear);

/**
 * @brief Set internal software error register.
 *
 * Internal error register R_INTERNAL_SW_ERR_INFO is used to show possible
 * errors to HLOS. Bits 7:0 show major error, bits 15:8 show minor error.
 * The register is actually in SIC but EAC API is better suited for this.
 *
 * @param dev Pointer to the device.
 * @param core_id HW core number.
 * @param major Major error code.
 * @param minor Minor error code.
 * @return R_HW_ERROR_INFO1 or 0.
 */
void cri_eac_set_internal_error(uint32_t core_id, int major, int minor);

/**
 * Halt CMRT.
 *
 * Disable interrupts and set internal error register (see @ref
 * cri_aec_set_internal_error) before halting.
 * Again registers used may be in SIC or in EAC.
 *
 * Raises a safety alarm in ASIL_B mode.
 *
 * @param core_id HW core number.
 * @param major Major error code.
 * @param minor Minor error code.
 */
void cri_eac_halt(uint32_t core_id, int major, int minor) FUNC_NORETURN;

/**
 * Reboot CMRT.
 *
 * Disable interrupts and start reboot.
 */
void cri_eac_reboot(void) FUNC_NORETURN;

/**
 * Uses SIC and EAC registers to indicate an eSW KAT failure,
 * disables interrupts and halts CMRT by reporting eSW alarm.
 *
 * @param core_id Core ID reporting the KAT error.
 * @param major Major error code.
 * @param minor Minor error code.
 */
void cri_eac_kat_error(uint32_t core_id, int major, int minor) FUNC_NORETURN;

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
