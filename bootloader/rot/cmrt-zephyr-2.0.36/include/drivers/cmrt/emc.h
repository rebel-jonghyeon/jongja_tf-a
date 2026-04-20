/*
 * Copyright (c) 2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file emc.h
 *
 * @brief Public APIs for the EMC driver.
 */

#ifndef CMRT_EMC_H
#define CMRT_EMC_H

/**
 * @brief EMC Interface
 * @defgroup emc_interface EMC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <device.h>
#include <drivers/cmrt/emc_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_emc_context *cmrt_emc_t;

/**
 * @brief Open EMC context for subsequent operations.
 *
 * Open and reserve a EMC context. May block for a context to be available.
 *
 * @param flags CMRT_O_SYNC operations automatically call sync.
 * @return Context handle on success or NULL on error.
 */
cmrt_emc_t cmrt_emc_open(uint32_t flags);

/**
 * @brief Close EMC context, reverse of open.
 *
 * Close and free previously opened EMC context.
 *
 * @param context Pointer to the device context.
 */
void cmrt_emc_close(cmrt_emc_t context);

/**
 * @brief Read entropy.
 *
 * @note The driver stores a reference to the @p buffer parameter that is
 * used in cmrt_emc_sync(). Callers must ensure that the parameter
 * value lives at least until cmrt_emc_sync() is called.
 *
 * @param context Pointer to the device context.
 * @param buffer Pointer to buffer for read entropy.
 * @param buflen Number of bytes to read.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_emc_read(cmrt_emc_t context, void *buffer, size_t buflen);

/**
 * @brief Synchronize EMC operation.
 *
 * Wait for completion of ongoing cmrt_emc_read() operation.
 * Does return immediately if operations have been completed.
 * Must be called if CMRT_O_SYNC is not given in cmrt_emc_open(),
 * must not be called if CMRT_O_SYNC is given in cmrt_emc_open().
 *
 * @param context Pointer to the device context.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_emc_sync(cmrt_emc_t context);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
