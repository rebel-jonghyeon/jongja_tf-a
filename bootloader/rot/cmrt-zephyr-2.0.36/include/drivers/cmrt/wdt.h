/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file wdt.h
 *
 * @brief Public APIs for the watchdog driver.
 */

#ifndef CMRT_WDT_H
#define CMRT_WDT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <device.h>

/**
 * @brief WATCHDOG Interface
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_wdt_context *cmrt_wdt_t;

/**
 * @brief Open watchdog for subsequent operations.
 *
 * Open a watchdog context, multiple opens are possible.
 * Every opening thread can specify a reload period specific to the
 * thread. High priority thread could use shorter period, for example.
 * Internally CMRT Watchdog uses task_wdt subsystem backed up by the
 * CMRT HW watchdog. Minumum allowed period for a thread is
 * CONFIG_TASK_WDT_MIN_TIMEOUT and CONFIG_TASK_WDT_HW_FALLBACK_DELAY
 * defines the time it has to react.
 *
 * @param flags Must be zero.
 * @param period Reload period in milliseconds for this thread.
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_wdt_t cmrt_wdt_open(uint32_t flags, uint32_t period);

/**
 * @brief Close watchdog, reverse of open.
 *
 * Close and free previously opened watchdog.
 * Note that closing does not disable the watchdog.
 *
 * @param[in] dev Pointer to the device.
 */
__syscall void cmrt_wdt_close(cmrt_wdt_t dev);

/**
 * @brief Wait the watchdog.
 *
 * Calling this function will block until the watchdog is ready to eat.
 * Typically one will wait on the device handle to know when to feed.
 *
 * @param dev Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_wdt_sync(cmrt_wdt_t dev);

/**
 * @brief Feed the watchdog.
 *
 * Feed the watchdog. Typically called after cmrt_wdt_sync() but can
 * be called anytime, for example, before lenghty operation.
 *
 * @param dev Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_wdt_feed(cmrt_wdt_t dev);

#ifdef __cplusplus
}
#endif

#include <syscalls/wdt.h>

#endif
