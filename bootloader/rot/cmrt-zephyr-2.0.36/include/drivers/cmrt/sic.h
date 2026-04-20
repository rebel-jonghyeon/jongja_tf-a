/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file sic.h
 *
 * @brief Public APIs for the SIC driver.
 */

#ifndef CMRT_SIC_H
#define CMRT_SIC_H

/**
 * @brief SIC Interface
 * @defgroup sic_interface SIC Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <device.h>
#include <drivers/cmrt/sic_reg.h>

#ifdef __ZEPHYR__
#define CMRT_SIC_IRQ DT_IRQN(DT_NODELABEL(sic))
#define CMRT_SIC_NUM_CUSTOM DT_PROP(DT_NODELABEL(sic), num_custom)
#if DT_NODE_HAS_PROP(DT_NODELABEL(sic), num_instances)
#define CMRT_SIC_NUM_INSTANCES DT_PROP(DT_NODELABEL(sic), num_instances)
#if CMRT_SIC_NUM_INSTANCES >= 32
#define CMRT_SIC_IRQ_MASK (0xFFFFFFFFu)
#else
#define CMRT_SIC_IRQ_MASK (((1u << CMRT_SIC_NUM_INSTANCES) - 1) | 0xFFFF0000u)
#endif
#else
#define CMRT_SIC_IRQ_MASK SIC_IRQ_MASK /* fixed in original sic */
#endif
#if CONFIG_SOC_NUM_IRQS >= 32
#define CMRT_SOC_INTERRUPT_IN_MASK (0xFFFFFFFFu)
#else
#define CMRT_SOC_INTERRUPT_IN_MASK ((1 << CONFIG_SOC_NUM_IRQS) - 1)
#endif
#define CMRT_SOC_IRQ(nr) (IRQ_TO_LEVEL_2(IRQ_FROM_LEVEL_2(CMRT_SIC_IRQ)) | IRQ_TO_LEVEL_3(nr))
#endif
#define CMRT_SIC_BOOT_CONTROL DT_PROP(DT_NODELABEL(sic), has_boot_control)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_sic_context *cmrt_sic_t;

/**
 * @brief Open SIC channel for given flow id.
 *
 * Thread can open many SIC channels but one flow id can be opened
 * only once in the system. Flow ids are like ports in the TCP/IP world.
 *
 * @param[in] flags Zero requires cmrt_sic_sync only after cmrt_sic_read,
 *                  cmrt_sic_write calls sync automatically (cmrt_sic_sync
 *                  must not be called)
 *                  CMRT_O_SYNC both cmrt_sic_read and cmrt_sic_write calls
 *                  automatically call sync
 *                  CMRT_O_ASYNC no need to call cmrt_sic_sync after either
 *                  cmrt_sic_read or cmrt_sic_write
 * @param[in] flowid Flow id to open for reading and writing.
 *                   Can include a HLOS timeout in ms (use macro SET_SICTIMEOUT)
 *                   to wait for HLOS to react when operations are synced.
 *                   Zero means indefinite. ETIMEDOUT is returned if the
 *                   timeout expires.
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_sic_t cmrt_sic_open(uint32_t flags, uint32_t flowid);

/**
 * @brief Close SIC channel for given flow id.
 *
 * @param[in] context Pointer to the SIC device.
 */
__syscall void cmrt_sic_close(cmrt_sic_t context);

/* Receive data to the end of the buffer. Data will be word aligned. */
#define CMRT_SIC_ALIGN_RIGHT 0x1UL

/**
 * @brief Read SIC protocol request for given flow id.
 *
 * Setup for reading SIC protocol request. Reading completes when one full
 * protocol message has been received for given flow id. To finish reading
 * cmrt_sic_sync must be called, or CMRT_O_SYNC must be set in cmrt_sic_open.
 *
 * @param[in] context Pointer to the SIC device.
 * @param[out] buffer Pointer to buffer for message data.
 * @param[in,out] buflen Length of max data in bytes and returned length.
 * @param[out] peerid Sending flow id in return for read.
 * @param[in] flags 0 (default) or CMRT_SIC_ALIGN_RIGHT. Flags can also define
              a SIC instance id where a non-zero value sets the only instance
              from where data is accepted. Typically one would use it to read
              only local traffic within CMRT by using SET_LOCAL_SICID.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_sic_read(cmrt_sic_t context, void *buffer, size_t *buflen, uint32_t *peerid, uint32_t flags);

/**
 * @brief Write SIC protocol response.
 *
 * Setup for writing SIC protocol response. Writing completes when all data
 * has been sent. By default cmrt_sic_write calls cmrt_sic_sync automatically,
 * unless CMRT_O_ASYNC has been set in cmrt_sic_open.
 *
 * @param[in] context Pointer to the SIC device.
 * @param[in] buffer Pointer to buffer for message data.
 * @param[in] buflen Length of the buffer in bytes.
 * @param[in] peerid Destination flow id received in cmrt_sic_read.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_sic_write(cmrt_sic_t context, const void *buffer, size_t buflen, uint32_t peerid);

/**
 * @brief Synchronize SIC protocol operation.
 *
 * Wait for completion of ongoing read and/or write asyncronious operation.
 * Does return immediately if operations have been completed.
 * cmrt_sic_sync call may or may not be required to complete
 * cmrt_sic_read/cmrt_sic_write operations and may even block indefinitely,
 * depending upon the flag used, refer to @ref cmrt_sic_open.
 *
 * @param[in] context Pointer to the SIC device.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_sic_sync(cmrt_sic_t context);

/**
 * @brief Test if SIC is idle.
 *
 * This function is used by the OS to detect possibility to go
 * into low power mode.
 *
 * @return True if idle, false otherwise.
 */
bool cmrt_sic_is_idle(void);

/**
 * @brief Read SIC register.
 *
 * Allowed for all registers in supervisor mode.
 * User mode can access SCRATCH and CUSTOM registers.
 *
 * @param reg Register id.
 * @return Current value.
 */
__syscall uint32_t cmrt_sic_read_reg(uint32_t reg);

/**
 * @brief Write SIC register.
 *
 * Allowed for all registers in supervisor mode.
 * User mode can access SCRATCH and CUSTOM registers.
 *
 * @param reg Register id.
 * @param value New value.
 */
__syscall void cmrt_sic_write_reg(uint32_t reg, uint32_t value);

#ifdef __cplusplus
}
#endif

#include <syscalls/sic.h>

#endif
/** @}*/
