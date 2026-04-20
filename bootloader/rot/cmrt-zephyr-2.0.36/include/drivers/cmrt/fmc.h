/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file fmc.h
 *
 * @brief Public APIs for the FMC driver.
 */

#ifndef CMRT_FMC_H
#define CMRT_FMC_H

/**
 * @brief FMC Interface
 * @defgroup fmc_interface FMC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <stdbool.h>
#include <device.h>
#include <drivers/cmrt/fmc_reg.h>

#ifdef __ZEPHYR__
#define CMRT_FMC_TDV_SIZE DT_PROP(DT_NODELABEL(fmc), tdv_size)
#define CMRT_FMC_FEATURE_SIZE DT_PROP(DT_NODELABEL(fmc), feature_size)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_fmc_context *cmrt_fmc_t;

/**
 * @brief Open FMC context for subsequent operations.
 *
 * Open and reserve an FMC context. May block for a context to be available.
 *
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_fmc_t cmrt_fmc_open(void);

/**
 * @brief Close FMC context.
 *
 * Close and free a previously opened FMC context.
 *
 * @param context Pointer to the device.
 */
__syscall void cmrt_fmc_close(cmrt_fmc_t context);

/**
 * @brief Read feature data
 *
 * Read feature data from specified feature space address.
 *
 * @param context Pointer to the device.
 * @param addr Feature space address.
 * @param data Pointer to storage where to read the data.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_fmc_read(cmrt_fmc_t context, uint32_t addr, uint32_t *data);

/**
 * @brief Write feature data with mask
 *
 * Write feature data to specified feature space address using a mask. Only
 * bits which are set in mask will be modified. Writes are subject to the
 * permission bitmap such that the bitmap must have bit N set when writing
 * to addresses (1 << N) (inclusive) ... (1 << N) + block_size (exclusive).
 *
 * @param context Pointer to the device.
 * @param addr Feature space address.
 * @param data Data to write.
 * @param mask Mask to use when writing.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_fmc_write(cmrt_fmc_t context, uint32_t addr, uint32_t data, uint32_t mask);

/**
 * @brief Set permission bitmap
 *
 * Set the permission bitmap. This can be done only once, and only by machine.
 * Each bit in the bitmap enables feature writes to portion of the feature
 * address space.
 *
 * @param context Pointer to the device.
 * @param bitmap Bitmap.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_fmc_permissions(cmrt_fmc_t context, uint32_t bitmap);

/**
 * @brief Convenience function to enable debug mode
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_fmc_set_debug_mode(cmrt_fmc_t context);

#ifdef __cplusplus
}
#endif

#include <syscalls/fmc.h>

#endif
/** @}*/
