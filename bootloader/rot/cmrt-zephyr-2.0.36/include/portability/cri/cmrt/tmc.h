/*
 * Copyright (c) 2018-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file tmc.h
 *
 * @brief Public APIs for the TMC driver.
 */

#ifndef CRI_TMC_H
#define CRI_TMC_H

/**
 * @brief TMC Interface
 * @defgroup tmc_interface TMC Interface
 * @ingroup io_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <tmc_reg.h>

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_tmc_t;
#else
typedef struct cmrt_tmc_context *cri_tmc_t;
#endif

/**
 * @brief Open TMC for subsequent operations.
 *
 * Open and reserve TMC context. May block for it to be available.
 *
 * @param flags Zero to call cri_ufc_sync after an operation,
 *              CRI_O_SYNC to autosync all operations.
 * @return Context handle on success or NULL on error.
 */
cri_tmc_t cri_tmc_open(uint32_t flags);

/**
 * @brief Open TMC for KDC.
 *
 * Open and initialize TMC for KDC. KDC will then take over TMC.
 * Software shall call @ref cri_tmc_close after KDC's job is finished.
 *
 * @return Context handle on success or NULL on error.
 */
cri_tmc_t cri_tmc_open_kdc(void);

/**
 * @brief Close TMC, reverse of open.
 *
 * Close and free previously opened TMC.
 *
 * @param context Pointer to the device.
 */
void cri_tmc_close(cri_tmc_t context);

/**
 * @brief Reseed TMC.
 *
 * Reseed TMC. Also gives out random data like generate below.
 * TMC has an internal entropy source where it gets the new seed.
 * Caller must call cri_ufc_sync until the result is valid,
 * or CRI_O_SYNC must be set in cri_ufc_open.
 *
 * @param context Pointer to the device.
 * @param buffer Output buffer for generated data.
 * @param size Buffer size in bytes, currently max. TMC_OUTPUT_SIZE bytes.
 * @return Zero on success, -ERRNO on error.
 */
int cri_tmc_reseed(cri_tmc_t context, uint8_t *buffer, uint32_t size);

/**
 * @brief Generate random data.
 *
 * Generate random data. Caller must call tmc_sync to wait for completion.
 * Caller must call cri_ufc_sync until the result is valid,
 * or CRI_O_SYNC must be set in cri_ufc_open.
 *
 * @param context Pointer to the device.
 * @param buffer Output buffer for generated data.
 * @param size Buffer size in bytes, currently max. TMC_OUTPUT_SIZE bytes.
 * @return Zero on success, -ERRNO on error.
 */
int cri_tmc_generate(cri_tmc_t context, uint8_t *buffer, size_t size);

/**
 * @brief Get TMC result.
 *
 * Get TMC result, wait for it to finish.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_tmc_sync(cri_tmc_t context);

#if defined(CONFIG_CRI_FIPS_140_MODE) && defined(CONFIG_SUPERVISOR_MODE)
/**
 * @brief Set TMC command.
 *
 * Set a TMC command, wait for it to finish.
 *
 * @param context Pointer to the device.
 * @param command TMC command to be set.
 * @param buffer Output from DRBG
 * @param length Length to read
 * @return Zero on success, -ERRNO on error.
 */
int cri_tmc_command(cri_tmc_t context, uint32_t command, uint32_t *buffer, uint32_t length);
#endif

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
