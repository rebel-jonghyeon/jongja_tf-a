/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file omc.h
 *
 * @brief Public APIs for the OMC driver.
 */

#ifndef CMRT_OMC_H
#define CMRT_OMC_H

/**
 * @brief OMC Interface
 * @defgroup omc_interface OMC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stddef.h>
#include <stdint.h>
#include <device.h>

#ifdef __ZEPHYR__
#define CMRT_OTP_BASE DT_REG_ADDR(DT_NODELABEL(otp))
#define CMRT_OTP_SIZE DT_REG_SIZE(DT_NODELABEL(otp))
#define CMRT_OTP_LAYOUT_VERSION DT_PROP(DT_NODELABEL(omc), layout_version)
#define CMRT_OTP_NUM_KEYSPLITS DT_PROP(DT_NODELABEL(omc), num_keysplits)
#define CMRT_OTP_NUM_ROOTS DT_PROP(DT_NODELABEL(omc), num_roots)
#endif

#include <drivers/cmrt/omc_reg.h>
#include <drivers/cmrt/otp_off.h>
#ifdef CONFIG_CMRT_OMC_EMULATED_OTP
#include <drivers/cmrt/oec_reg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_omc_context *cmrt_omc_t;

/**
 * @brief Get pointer to OTP layout.
 *
 * @param offset Offset from the start of OTP.
 * @return Pointer to OTP base address + offset.
 */
static inline void *cmrt_otp_layout(uint32_t offset)
{
	return (void *)(uintptr_t)(CMRT_OTP_BASE + offset);
}

/**
 * @brief Get offset to the start of the OTP ESW area.
 *
 * The ESW area begins after the HW managed OTP area.
 * Typically, it has the reserved words in the beginning.
 *
 * @return Offset to the start of OTP ESW area after the reserved words.
 */
uint32_t cmrt_otp_esw_start(void);

/**
 * @brief Open OMC context for subsequent operations.
 *
 * Open and reserve an OMC context. May block for a context to be available.
 *
 * When using emulated OTP, @ref CMRT_O_OTP_COMMIT flag can be specified,
 * then OMC driver reserves HC and AES contexts. @ref cmrt_omc_close
 * then auto commits OTP contents and releases HC and AES contexts.
 * This flag is NOP if CONFIG_CMRT_OMC_EMULATED_OTP is not set.
 *
 * @param flags CMRT_O_OTP_COMMIT for autocommit, see above.
 *              CMRT_O_SYNC to autosync all operations, if not set one must call
 *              cmrt_omc_sync explicitly for most API calls.
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_omc_t cmrt_omc_open(uint32_t flags);

/**
 * @brief Close OMC context, reverse of open.
 *
 * Close and free previously opened OMC context.
 *
 * When using emulated OTP, if @ref CMRT_O_OTP_COMMIT flag is specified in @ref
 * cmrt_omc_open, then OTP contents are auto committed and HC and AES contexts
 * are released.
 *
 * @param context Pointer to the device.
 */
__syscall void cmrt_omc_close(cmrt_omc_t context);

/**
 * @brief Read data from OTP.
 *
 * Reading DGOK or keysplits is not allowed.
 * Do not call cmrt_omc_sync, reading is synchronous.
 * In case of uncorrectable ECC error -EIO is returned.
 *
 * @param context Pointer to the device.
 * @param offset Offset from the beginning of OTP, see otp_off.h for values.
 * @param buffer Pointer to buffer to copy the data from OTP.
 * @param buflen Buffer size must be word aligned and correct for the offset.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_omc_read(cmrt_omc_t context, uint32_t offset, void *buffer, size_t buflen);

/**
 * @brief Write data to OTP.
 *
 * Writing DGOK, or status or key obliterate words is not allowed.
 * Caller must call cmrt_omc_sync to wait for completion, or CMRT_O_SYNC
 * must be set in cmrt_omc_open.
 *
 * @param context Pointer to the device.
 * @param offset Offset from the beginning of OTP, see otp_off.h for values.
 * @param buffer Pointer to buffer to copy the data from OTP.
 * @param buflen Buffer size must be word aligned and correct for the offset.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_omc_write(cmrt_omc_t context, uint32_t offset, const void *buffer, size_t buflen);

/**
 * @brief Obliterate an OTP asset.
 *
 * Only DGOK, keysplits, roots and perso root can be obliterated.
 * To obliterating perso root offset must be OTP_STATUS_WORD_OFFSET.
 * Caller must call cmrt_omc_sync to wait for completion, or CMRT_O_SYNC
 * must be set in cmrt_omc_open.
 *
 * @param context Pointer to the device.
 * @param offset Offset from the beginning of OTP, see otp_off.h for values.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_omc_obliterate(cmrt_omc_t context, uint32_t offset);

/**
 * @brief Reshadow OTP
 *
 * Requests OMC to reparse OTP assets and update certain SIC registers,
 * DEVICE_LIFECYCLE register for example. Caller must call cmrt_omc_sync to
 * wait for completion, or CMRT_O_SYNC must be set in cmrt_omc_open.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_omc_reshadow(cmrt_omc_t context);

/**
 * @brief Get OMC command result.
 *
 * Get OMC result after interrupt, or wait until it finishes.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_omc_sync(cmrt_omc_t context);

/**
 * @brief Set up OMC privilege registers.
 *
 * This must be done in machine mode and is typically handled in the
 * security monitor.
 *
 * @param context Pointer to the device.
 * @param perm Caller must fill fields properly, see omc_reg.h.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_omc_permissions(cmrt_omc_t context, const omc_perm_t *perm);

/**
 * @brief Read OEC controlled data.
 *
 * This function is a NOP if CONFIG_CMRT_OMC_EMULATED_OTP is not set.
 * See oec_reg.h for address values. Caller must call cmrt_omc_sync to
 * wait for completion, or CMRT_O_SYNC must be set in cmrt_omc_open.
 *
 * @param context Pointer to the device.
 * @param address Requested data address.
 * @param buffer Output buffer for data.
 * @param buflen Buffer size in bytes.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_oec_read(cmrt_omc_t context, uint32_t address, void *buffer, size_t buflen);

/**
 * @brief Write OEC controlled data.
 *
 * This function is a NOP if CONFIG_CMRT_OMC_EMULATED_OTP is not set.
 * See oec_reg.h for address values. Caller must call cmrt_omc_sync to
 * wait for completion, or CMRT_O_SYNC must be set in cmrt_omc_open.
 *
 * @param context Pointer to the device.
 * @param address Requested data address.
 * @param buffer Output buffer for data.
 * @param buflen Buffer size in bytes.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_oec_write(cmrt_omc_t context, uint32_t address, const void *buffer, size_t buflen);

/**
 * @brief Commit changes to the OTP.
 *
 * This function is a NOP if CONFIG_CMRT_OMC_EMULATED_OTP is not set.
 * When using emulated OTP one must call this function to commit
 * written changes to the OTP. Caller must call cmrt_omc_sync to
 * wait for completion, or CMRT_O_SYNC must be set in cmrt_omc_open.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_oec_commit(cmrt_omc_t context);

#ifdef __cplusplus
}
#endif

#include <syscalls/omc.h>

#endif
/** @}*/
