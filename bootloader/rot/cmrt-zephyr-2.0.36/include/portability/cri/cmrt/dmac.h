/*
 * Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file dmac.h
 *
 * @brief Public APIs for the DMAC driver.
 */

#ifndef CRI_DMAC_H
#define CRI_DMAC_H

/**
 * @brief DMAC Interface
 * @defgroup dmac_interface DMAC Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <dmac_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_dmac_t;
#else
typedef struct cmrt_dmac_context *cri_dmac_t;
#endif

/**
 * @brief Open DMAC channel for subsequent operations.
 *
 * Open and reserve a DMA channel. May block for a channel to be available.
 *
 * @param flags Zero to call cri_dmac_sync after an operation,
 *              CRI_O_SYNC to autosync all operations.
 * @return Context handle on success, NULL on error.
 */
cri_dmac_t cri_dmac_open(uint32_t flags);

/**
 * @brief Close DMAC channel, reverse of open.
 *
 * Close and free previously opened DMA channel.
 *
 * @param channel Pointer to the device.
 */
void cri_dmac_close(cri_dmac_t channel);

/**
 * @brief Start DMAC data transfer.
 *
 * Start DMAC data transfer. Caller must call cri_dmac_sync to wait for
 * completion, or CRI_O_SYNC must be set in cri_dmac_open.
 *
 * @param channel Pointer to the device.
 * @param src_addr Source address.
 * @param dst_addr Destination address.
 * @param size Transfer size in bytes (must be word aligned).
 * @return Zero on success, -ERRNO on error.
 */
int cri_dmac_data(cri_dmac_t channel, uint32_t src_addr,
		  uint32_t dst_addr, uint32_t size);

/**
 * @brief Start DMAC data transfer with descriptor flags.
 *
 * Start DMAC data transfer. Caller must call cri_dmac_sync to wait for
 * completion, or CRI_O_SYNC must be set in cri_dmac_open.
 *
 * @param channel Pointer to the device.
 * @param src_addr Source address.
 * @param dst_addr Destination address.
 * @param size Transfer size in bytes (must be word aligned).
 * @param desc_flags Descriptor flags. See DSEC_XXX_BIT defined in dmac_reg.h.
 * @return Zero on success, -ERRNO on error.
 */
int cri_dmac_data_ex(cri_dmac_t channel, uint32_t src_addr,
		     uint32_t dst_addr, uint32_t size, uint32_t desc_flags);

/**
 * @brief Start DMAC fill transfer.
 *
 * Start DMAC fill transfer. Caller must call cri_dmac_sync to wait for
 * completion, or CRI_O_SYNC must be set in cri_dmac_open.
 *
 * @param channel Pointer to the device.
 * @param fill_data Source data.
 * @param dst_addr Destination address.
 * @param size Transfer size in bytes (must be word aligned).
 * @return Zero on success, -ERRNO on error.
 */
int cri_dmac_fill(cri_dmac_t channel, uint32_t fill_data,
		  uint32_t dst_addr, uint32_t size);

/**
 * @brief Start DMAC fill transfer with descriptor flags.
 *
 * Start DMAC fill transfer. Caller must call cri_dmac_sync to wait for
 * completion, or CRI_O_SYNC must be set in cri_dmac_open.
 *
 * @param channel Pointer to the device.
 * @param fill_data Source data.
 * @param dst_addr Destination address.
 * @param size Transfer size in bytes (must be word aligned).
 * @param desc_flags Descriptor flags. See DSEC_XXX_BIT defined in dmac_reg.h.
 * @return Zero on success, -ERRNO on error.
 */
int cri_dmac_fill_ex(cri_dmac_t channel, uint32_t fill_data,
		     uint32_t dst_addr, uint32_t size,
		     uint32_t desc_flags);

#ifdef CONFIG_CRI_CFI
/**
 * @brief Start DMAC CFI data transfer.
 *
 * Start DMAC CFI data transfer. Caller must call cri_dmac_sync to wait for
 * completion, or CRI_O_SYNC must be set in cri_dmac_open.
 *
 * @param channel Pointer to the device.
 * @param src_addr Source address.
 * @param dst_addr Destination address.
 * @param size Transfer size in bytes (must be word aligned).
 * @return Zero on success, -ERRNO on error.
 */
int cri_dmac_cfi(cri_dmac_t channel, uint32_t src_addr,
		 uint32_t dst_addr, uint32_t size);
#endif

/**
 * @brief Get DMA result.
 *
 * Get DMA result after interrupt, or wait until it finishes.
 *
 * @param channel Pointer to the device.
 * @return Zero on success, -ERRNO errno code on error.
 */
int cri_dmac_sync(cri_dmac_t channel);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
