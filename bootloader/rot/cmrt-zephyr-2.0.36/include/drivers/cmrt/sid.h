/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file sid.h
 *
 * @brief Public APIs for SIC IRQ driver.
 */

#ifndef CMRT_SID_H
#define CMRT_SID_H

/**
 * @brief SID Interface
 * @defgroup sid_interface SID Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <device.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_sid_context *cmrt_sid_t;

/**
 * @brief Open SID context and reserve IRQs for subsequent operations.
 *
 * Open and reserve a SID context and reserve IRQs. May block for a context to
 * be available. If not all of the specified IRQs can be reserved then the
 * operation fails. Reserved IRQs are initially unmonitored.
 *
 * @param flags Zero to call cmrt_sid_sync after an operation,
 *              CMRT_O_SYNC to autosync all operations.
 * @param irqs Bitfield of IRQs to reserve, b1 reserves IRQ.
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_sid_t cmrt_sid_open(uint32_t flags, uint32_t irqs);

/**
 * @brief Close SID context, reverse of open.
 *
 * Close and free previously opened SID context.
 *
 * @param dev Pointer to the device.
 */
__syscall void cmrt_sid_close(cmrt_sid_t dev);

/**
 * @brief Enable/disable IRQ monitoring.
 *
 * Change monitoring state of reserved IRQs. An IRQ can be in either of the two
 * states, monitored or unmonitored.
 *
 * When a monitored IRQ triggers, its status is updated, its state is changed
 * to unmonitored and its owner process is notified.
 *
 * Function cmrt_wait() can be used to wait for monitored interrupts.
 * The result parameter @p irqs is valid after a call to cmrt_sid_sync()
 * which must be called after cmrt_wait() returns. Alternatively,
 * one can call cmrt_sid_sync() without cmrt_wait() or set CMRT_O_SYNC in
 * cmrt_sid_open() to make the monitoring operation synchronous. With
 * CMRT_O_SYNC the call to cmrt_sid_sync() is done internally.
 *
 * @param dev Pointer to the device.
 * @param watch Bitfield, b1 selects IRQ for monitoring.
 * @param irqs Bitfield of triggered IRQs after cmrt_sid_sync(), triggered IRQs
 *             have b1. Caller must ensure @p irqs is in scope between calls to
 *             cmrt_sid_watch() and cmrt_sid_sync().
 * @return Zero on success and
 *         -EINVAL if an unreserved IRQ is specified to @p mask.
 */
__syscall int cmrt_sid_watch(cmrt_sid_t dev, uint32_t watch, uint32_t *irqs);

/**
 * @brief Synchronize SID operation.
 *
 * Wait for completion of ongoing cmrt_sid_watch() operation.
 * Does return immediately if operations have been completed.
 *
 * @param[in] dev Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_sid_sync(cmrt_sid_t dev);

#ifdef __cplusplus
}
#endif

#include <syscalls/sid.h>

#endif
/** @}*/
