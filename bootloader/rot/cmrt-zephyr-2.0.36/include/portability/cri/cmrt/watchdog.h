/*
 * Copyright (c) 2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file watchdog.h
 *
 * @brief Public APIs for the watchdog driver.
 */

#ifndef CRI_WATCHDOG_H
#define CRI_WATCHDOG_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief WATCHDOG Interface
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_watchdog_t;
#else
typedef struct cmrt_watchdog_context *cri_watchdog_t;
#endif

/**
 * @brief Open watchdog for subsequent operations.
 *
 * Open a watchdog context, multiple opens are possible.
 * Starting the watchdog must be done outside this driver,
 * for example, by using CONFIG_WDT_CMRT_START_AT_BOOT.
 *
 * @param flags Must be zero.
 * @return Context handle on success or NULL on error.
 */
cri_watchdog_t cri_watchdog_open(uint32_t flags);

/**
 * @brief Close watchdog, reverse of open.
 *
 * Close and free previously opened watchdog.
 * Note that closing does not disable the watchdog.
 *
 * @param[in] dev Pointer to the device.
 */
void cri_watchdog_close(cri_watchdog_t dev);

/**
 * @brief Poll the watchdog.
 *
 * Polling checks if the watchdog counter is more than half way
 * through and if so, it activates one watchdog context ready for
 * calling cri_watchdog_sync(). Polling can be called manually in
 * an application or automatically in the timer interrupt by using
 * CONFIG_CRI_WATCHDOG_TIMER_POLL.
 *
 * Calling cri_watchdog_poll with a non null context will only
 * check if the context has been activated.
 *
 * @param dev NULL to poll, pointer to the device to check.
 * @return Zero on not hungry, -ERRNO on error, positive if hungry.
 */
int cri_watchdog_poll(cri_watchdog_t dev);

/**
 * @brief Feed the watchdog.
 *
 * Calling this function will block until the watchdog is ready to
 * eat, that is, cri_watchdog_poll() has returned positive and this
 * watchdog context has been assigned to feed.
 *
 * @param dev Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_watchdog_sync(cri_watchdog_t dev);

#ifdef __cplusplus
}
#endif
#endif
