/*
 * Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file fmc.h
 *
 * @brief Public APIs for the FMC driver.
 */

#ifndef CRI_FMC_H
#define CRI_FMC_H

/**
 * @brief FMC Interface
 * @defgroup fmc_interface FMC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <stdbool.h>
#include <fmc_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_fmc_t;
#else
typedef struct cmrt_fmc_context *cri_fmc_t;
#endif

/**
 * @brief Open FMC context for subsequent operations.
 *
 * Open and reserve an FMC context. May block for a context to be available.
 *
 * @return Context handle on success or NULL on error.
 */
cri_fmc_t cri_fmc_open(void);

/**
 * @brief Close FMC context.
 *
 * Close and free a previously opened FMC context.
 *
 * @param context Pointer to the device.
 */
void cri_fmc_close(cri_fmc_t context);

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
int cri_fmc_feature_read(cri_fmc_t context, uint32_t addr, uint32_t *data);

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
int cri_fmc_feature_write(cri_fmc_t context, uint32_t addr, uint32_t data, uint32_t mask);

/**
 * @brief Read GPIO data
 *
 * Read feature data from specified GPIO space address.
 *
 * @param context Pointer to the device.
 * @param addr GPIO space address.
 * @param data Pointer to storage where to read the data.
 * @return Zero on success, -ERRNO on error.
 */
int cri_fmc_gpio_read(cri_fmc_t context, uint32_t addr, uint32_t *data);

/**
 * @brief Write GPIO data with mask
 *
 * Write feature data to specified feature space address using a mask. Only
 * bits which are set in mask will be modified. Writes are not subject to the
 * permission bitmap.
 *
 * @param context Pointer to the device.
 * @param addr Feature space address.
 * @param data Data to write.
 * @param mask Mask to use when writing.
 * @return Zero on success, -ERRNO on error.
 */
int cri_fmc_gpio_write(cri_fmc_t context, uint32_t addr, uint32_t data, uint32_t mask);

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
int cri_fmc_set_perm_bitmap(cri_fmc_t context, uint32_t bitmap);

/**
 * @brief Convenience function to enable debug mode
 *
 * Put system to debug mode. Consequently, JTAT will be reachable
 * from HLOS. Further, KDC will see masked base keys, which implies that
 * the keys derived by KDC will be different.
 *
 * Debug mode is persistent unless a power on reset is applied.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_fmc_set_debug_mode(cri_fmc_t context);

#ifdef __cplusplus
}
#endif

#endif
 /** @}*/
