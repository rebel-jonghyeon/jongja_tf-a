/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file pdma.h
 *
 * @brief Public APIs for the PCIe DMA (PDMA) core driver.
 */

#ifndef CMRT_PDMA_H
#define CMRT_PDMA_H

/**
 * PDMA copies data from HLOS memory to CMRT external DRAM and from CMRT external
 * DRAM to HLOS memory. PDMA operates is driven by an Address Table, which exists
 * in HLOS memory. It specifies a list of source and destination memory pages
 * and associated meta data (for HSAES use). See @ref cmrt_pdma_at_t.
 *
 * @defgroup pdma_interface PDMA Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <device.h>
#include <drivers/cmrt/pdma_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_pdma_context *cmrt_pdma_t;

/**
 * Open a PDMA device context.
 *
 * Open and return a PDMA context. Given channel is reserved and used in all
 * operation executed with the returned context.
 *
 * A channel can be used by up to two contexts. Call may block for a context to
 * be available. Up to 128 contexts can be opened.
 *
 * @param flags Zero to call cmrt_pdma_sync after an operation,
 *              CMRT_O_SYNC to autosync all operations.
 * @param channel  Channel that PDMA operations will use.
 * @param key_bank For bidirectional HSAES operation only, Key bank that PDMA
 *                 operations will use.
 *
 * @return         Device context handle on success or NULL on error.
 */
cmrt_pdma_t cmrt_pdma_open(uint32_t flags, uint32_t channel, uint32_t key_bank);

/**
 * Close PDMA device context, reverse of open.
 *
 * Close and free previously opened PDMA context. Call only if all queued
 * operations have finished. Otherwise an abort is issued @ref
 * cmrt_pdma_abort().
 *
 * @param dev PDMA device context handle.
 */
void cmrt_pdma_close(cmrt_pdma_t dev);

/**
 * Return channel and key bank used by PDMA context.
 *
 * @param dev          Pointer to device context.
 * @param[out] channel  Pointer to return channel.
 * @param[out] key_bank Pointer to return key_bank.
 */
void cmrt_pdma_get_channel_context(cmrt_pdma_t dev, uint32_t *channel, uint32_t *key_bank);

/**
 * Wait for queued operations to finish and return status.
 *
 * @param dev PDMA device context handle.
 *
 * @return Zero on success. On error, the number of queued operations that have
 *         failed.
 */
int cmrt_pdma_sync(cmrt_pdma_t dev);

/**
 * Abort all queued operations across all open contexts. All open context should
 * be closed afterwards.
 *
 * @param dev PDMA device context handle.
 *
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_pdma_abort(cmrt_pdma_t dev);

/**
 * Enqueue a PDMA data copy operation.
 *
 * Normally copy operation is bidirectional, that is data is copied from HLOS
 * memory to DRAM and from DRAM to HLOS memory. If either of @p inbuf or @p outbuf
 * is 0 then copy operation is unidirectional. If @p outbuf is 0 then data is
 * copied only from HLOS to DRAM. If @p inbuf is 0 then data is copied
 * only from DRAM to HLOS.
 *
 * @note This only queue operations for PDMA to process, therefore
 * buffers backing arguments should not be repurposed unless @ref
 * cmrt_pdma_sync() has been called or CMRT_O_SYNC is set in @ref cmrt_pdma_open().
 *
 * @param dev       PDMA device context handle.
 * @param at_addr   Address of Address Table in HLOS memory. Address must be
 *                  word aligned.
 * @param at_count  Number of entries in Address Table.
 * @param inbuf     Address of buffer in DRAM, to which data from HLOS in copied
 *                  in ingress direction. For non-bidirectional mode address
 *                  must be aligned to CMRT_DCM_DDR_BUFFER_SIZE. In other modes
 *                  address must be aligned to CMRT_PDMA_DATA_WIDTH.
 * @param outbuf    Address of buffer in DRAM, from which data to HLOS is copied
 *                  in egress direction. For non-bidirectional mode address
 *                  must be aligned to CMRT_DCM_DDR_BUFFER_SIZE. In other modes
 *                  address must be aligned to CMRT_PDMA_DATA_WIDTH.
 * @param update_at If true, AT is copied to HLOS at address @p at_addr after
 *                  all AT entries have been processed.
 *
 * @return          Zero on success, -ERRNO on error.
 * @retval -EAGAIN  If operation queue is full.
 * @retval -EINVAL  If an invalid argument is supplied.
 * @retval -EIO     If a HW error is encountered.
 */
int cmrt_pdma_copy(cmrt_pdma_t dev, uint64_t at_addr, uint32_t at_count,
		   uint64_t inbuf, uint64_t outbuf, bool update_at);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
