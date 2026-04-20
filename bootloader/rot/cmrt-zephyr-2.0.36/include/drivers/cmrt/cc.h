/*
 * Copyright (c) 2018-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file cc.h
 *
 * @brief Public APIs for the CC driver.
 */

#ifndef CMRT_CC_H
#define CMRT_CC_H

/**
 * @brief CC Interface
 * @defgroup cc_interface CC Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <device.h>
#include <drivers/cmrt/cc_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_cc_context *cmrt_cc_t;

/**
 * @brief Open CC for subsequent operations.
 *
 * Open and reserve CC, may block for it to be available.
 *
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_cc_t cmrt_cc_open(void);

/**
 * @brief Close CC, reverse of open.
 *
 * Close and free previously opened CC.
 *
 * @param context Pointer to the device.
 */
__syscall void cmrt_cc_close(cmrt_cc_t context);

/**
 * @brief Set assert values to match in sync.
 *
 * Set assert values to match in sync.
 *
 * @param context Pointer to the device.
 * @param assert0 First assert word
 * @param assert1 Second assert word
 * @return zero on success, -ERRNO on error.
 */
__syscall int cmrt_cc_assert(cmrt_cc_t context, uint32_t assert0, uint32_t assert1);

/**
 * @brief Mix CC with a value.
 *
 * Mix CC with a value.
 *
 * @param context Pointer to the device.
 * @param value Mix value.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_cc_mix(cmrt_cc_t context, uint32_t value);

/**
 * @brief Assert CC to match given assert values.
 *
 * Assert CC to match given assert values. Assert failure will result into
 * NMI error or HW panic.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_cc_sync(cmrt_cc_t context);

#ifdef __cplusplus
}
#endif

#include <syscalls/cc.h>

#endif
/** @}*/
