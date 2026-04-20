/*
 * Copyright (c) 2019-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file sid.h
 *
 * @brief Public APIs for SIC IRQ driver.
 */

#ifndef CRI_SID_H
#define CRI_SID_H

/**
 * @brief SID Interface
 * @defgroup sid_interface SID Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_sid_t;
#else
typedef struct cmrt_sid_context *cri_sid_t;
#endif

/**
 * @brief Open SID context and reserve IRQs for subsequent operations.
 *
 * Open and reserve a SID context and reserve IRQs. May block for a context to
 * be available. If not all of the specified IRQs can be reserved then the
 * operation fails. Reserved IRQs are initially unmonitored.
 *
 * @param flags Zero to call cri_sid_sync after an operation,
 *              CRI_O_SYNC to autosync all operations.
 * @param irqs Bitfield of IRQs to reserve, b1 reserves IRQ.
 * @return Context handle on success or NULL on error.
 */
cri_sid_t cri_sid_open(uint32_t flags, uint32_t irqs);

/**
 * @brief Close SID context, reverse of open.
 *
 * Close and free previously opened SID context.
 *
 * @param dev Pointer to the device.
 */
void cri_sid_close(cri_sid_t dev);

/**
 * @brief Enable/disable IRQ monitoring.
 *
 * Change monitoring state of reserved IRQs. An IRQ can be in either of the two
 * states, monitored or unmonitored.
 *
 * When a monitored IRQ triggers, its status is updated, its state is changed
 * to unmonitored and its owner process is notified.
 *
 * Function cri_wait() can be used to wait for monitored interrupts.
 * The result parameter @p irqs is valid after a call to cri_sid_sync()
 * which must be called after cri_wait() returns. Alternatively,
 * one can call cri_sid_sync() without cri_wait() or set CRI_O_SYNC in
 * cri_sid_open() to make the monitoring operation synchronous. With
 * CRI_O_SYNC the call to cri_sid_sync() is done internally.
 *
 * @param dev Pointer to the device.
 * @param state Bitfield, b1 puts IRQ in monitored state and b0 puts IRQ in
 *              unmonitored state.
 * @param mask Bitfield, b1 selects IRQ for state manipulation.
 * @param irqs Bitfield of triggered IRQs after cri_sid_sync(), triggered IRQs
 *             have b1. Caller must ensure @p irqs is in scope between calls to
 *             cri_sid_watch() and cri_sid_sync().
 * @return Zero on success and
 *         -EINVAL if an unreserved IRQ is specified to @p state or @p mask.
 */
int cri_sid_watch(cri_sid_t dev, uint32_t state, uint32_t mask, uint32_t *irqs);

/**
 * @brief Synchronize SID operation.
 *
 * Wait for completion of ongoing cri_sid_watch() operation.
 * Does return immediately if operations have been completed.
 *
 * @param[in] dev Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_sid_sync(cri_sid_t dev);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
