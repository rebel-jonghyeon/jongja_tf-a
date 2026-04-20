/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file dmac.h
 *
 * @brief Public APIs for the DMAC driver.
 */

#ifndef CMRT_DMAC_H
#define CMRT_DMAC_H

/**
 * @brief DMAC Interface
 * @defgroup dmac_interface DMAC Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <device.h>
#include <drivers/cmrt/dmac_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_dmac_context *cmrt_dmac_t;

/*!
 * DMAC operation flags. Not implemented in HW.
 */
typedef enum cmrt_dmac_flags_e {
	DMAC_FLAG_DECSRCADDR = DESC_DECSRCADDR_BIT,     /* decrement src addr */
	DMAC_FLAG_DECDSTADDR = DESC_DECDSTADDR_BIT,     /* decrement dst addr */
	DMAC_FLAG_SWPSRCBYTES = DESC_SWPSRCBYTES_BIT,   /* swap src bytes */
	DMAC_FLAG_SWPDSTBYTES = DESC_SWPDSTBYTES_BIT,   /* swap dst bytes */
#ifdef CONFIG_CMRT_CFI
	DMAC_FLAG_CFI = DESC_CFI_BIT,                   /* reserved for CFI */
#endif
} cmrt_dmac_flags_t;

/**
 * @brief Open DMAC channel for subsequent operations.
 *
 * Open and reserve a DMA channel. May block for a channel to be available.
 *
 * @param flags Zero to call cmrt_dmac_sync after an operation,
 *              CMRT_O_SYNC to autosync all operations.
 * @return Context handle on success, NULL on error.
 */
__syscall cmrt_dmac_t cmrt_dmac_open(uint32_t flags);

/**
 * @brief Close DMAC channel, reverse of open.
 *
 * Close and free previously opened DMA channel.
 *
 * @param channel Pointer to the device.
 */
__syscall void cmrt_dmac_close(cmrt_dmac_t channel);

/**
 * @brief Start DMAC data transfer.
 *
 * Start DMAC data transfer. Caller must call cmrt_dmac_sync to wait for
 * completion, or CMRT_O_SYNC must be set in cmrt_dmac_open.
 *
 * @param channel Pointer to the device.
 * @param src_addr Source address.
 * @param dst_addr Destination address.
 * @param size Transfer size in bytes (must be word aligned).
 * @param flags Descriptor flags, zero until supported by HW.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_dmac_data(cmrt_dmac_t channel, uint32_t src_addr, uint32_t dst_addr, uint32_t size, cmrt_dmac_flags_t flags);

/**
 * @brief Start DMAC fill transfer.
 *
 * Start DMAC fill transfer. Caller must call cmrt_dmac_sync to wait for
 * completion, or CMRT_O_SYNC must be set in cmrt_dmac_open.
 *
 * @param channel Pointer to the device.
 * @param fill_data Source data.
 * @param dst_addr Destination address.
 * @param size Transfer size in bytes (must be word aligned).
 * @param flags Descriptor flags, zero until supported by HW.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_dmac_fill(cmrt_dmac_t channel, uint32_t fill_data, uint32_t dst_addr, uint32_t size, cmrt_dmac_flags_t flags);

/**
 * @brief Get DMA result.
 *
 * Get DMA result after interrupt, or wait until it finishes.
 *
 * @param channel Pointer to the device.
 * @return Zero on success, -ERRNO errno code on error.
 */
__syscall int cmrt_dmac_sync(cmrt_dmac_t channel);

#ifdef __cplusplus
}
#endif

#include <syscalls/dmac.h>

#endif
/** @}*/
