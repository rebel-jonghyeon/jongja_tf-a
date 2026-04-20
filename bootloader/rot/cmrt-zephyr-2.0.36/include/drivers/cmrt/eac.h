/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file eac.h
 *
 * @brief Public APIs for the EAC driver.
 */

#ifndef CMRT_EAC_H
#define CMRT_EAC_H

/**
 * @brief EAC Interface
 * @defgroup eac_interface EAC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <stdbool.h>
#include <toolchain.h>
#include <drivers/cmrt/eac_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set internal software error register.
 *
 * Internal error register R_INTERNAL_SW_ERR_INFO is used to show possible
 * errors to HLOS. Bits 23:16 show core id, bits 31:24 show core error.
 * The register is actually in SIC but EAC API is better suited for this.
 *
 * @param core_id HW core number.
 * @param core_error error status.
 */
void cmrt_eac_set_core_error(uint8_t core_id, uint8_t core_error);

/**
 * @brief Set internal software error register.
 *
 * Internal error register R_INTERNAL_SW_ERR_INFO is used to show possible
 * errors to HLOS. Bits 7:0 show major error, bits 15:8 show minor error.
 * The register is actually in SIC but EAC API is better suited for this.
 *
 * @param major Major error code.
 * @param minor Minor error code.
 */
void cmrt_eac_set_internal_error(int major, int minor);

/**
 * @brief Set boot status register for additional error info.
 *
 * Internal error register R_SW_BOOT_STATUS is used to show possible
 * errors to HLOS. Bits 31:24 show CPU mcause, bits 23:16 show NMI error.
 * The register is actually in SIC but EAC API is better suited for this.
 *
 * @param mcause CPU mcause value.
 * @param nmi NMI error code.
 */
void cmrt_eac_set_boot_status(uint8_t mcause, uint8_t nmi);

/**
 * Halt CMRT.
 *
 * Disable interrupts and set internal error register (see @ref
 * cmrt_eac_set_internal_error) before halting.
 * Again registers used may be in SIC or in EAC.
 *
 * Raises a safety alarm in ASIL_B mode.
 *
 * @param core_id HW core number.
 * @param major Major error code.
 * @param minor Minor error code.
 */
void cmrt_eac_halt(uint32_t core_id, int major, int minor) FUNC_NORETURN;

/**
 * Reboot CMRT.
 *
 * Disable interrupts and start reboot.
 */
void cmrt_eac_reboot(void) FUNC_NORETURN;

/**
 * Reset CMRT.
 *
 * Disable interrupts and start boot up. Reset is lighter than reboot
 * and does not clear all registers. Sboot can check the retained registers
 * at boot up.
 */
void cmrt_eac_reset(void) FUNC_NORETURN;

/**
 * Uses SIC and EAC registers to indicate an eSW KAT failure,
 * disables interrupts and halts CMRT by reporting eSW alarm.
 *
 * @param core_id Core ID reporting the KAT error.
 * @param major Major error code.
 * @param minor Minor error code.
 */
void cmrt_eac_kat_error(uint32_t core_id, int major, int minor) FUNC_NORETURN;

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
