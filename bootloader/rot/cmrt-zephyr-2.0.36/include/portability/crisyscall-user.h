/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <cri/cmrt/omc_reg.h>
#include <cri/cmrt/img_version.h>

#ifndef CRISYSCALL_USER_H
#define CRISYSCALL_USER_H

/*!
 * @name Flags
 * @{
 */
#define O_SYNC 0x1
#define O_ASYNC 0x2
#define CRI_O_HWC_KEYED 0x4UL
/*! @} */

/*!
 * Seconds as ticks.
 * @param x seconds to wait
 * @return tick count to pass into cri_wait()
 */
#define CRI_SECONDS(x) ((x) * 1000)

/*!
 * Wait forever.  A value to pass into cri_wait().
 */
#define CRI_FOREVER (-1)

/*!
 * Default flow id for container samples.
 */
#define CRI_UNIT_CONTAINER_SAMPLE 100

/*!
 * Exit for containers. RC is ignored.
 */
int cri_exit(int rc);

/**
 * @brief Establish a new root.
 **/
int cri_create_root(int index, cmrt_omc_root_t *new_root);

/**
 * @brief Obliterate root.
 **/
int cri_obliterate_root(int index);

/**
 * @brief Get minimum image version in OTP or running component version.
 **/
int cri_get_img_version(enum cri_image_version_id imageid, void *version, size_t *size);

/**
 * @brief Get uptime in ms since boot
 *
 * @param[out] uptime in ms
 *
 * @return Zero on success, -ERRNO on failure
 */
int cri_get_uptime(int64_t *uptime);

/**
 * @brief Get elapsed time in ms
 *
 * Updates the reference to current time if there was no error.
 *
 * @param[in,out] ref reference time
 *
 * @return Positive for elapsed time, -ERRNO on failure
 */
int cri_uptime_delta(int64_t *ref);

/**
 * @brief Get CPU cycles since boot
 *
 * @param cycles[out] cycle counter value
 *
 * @return Zero on success, -ERRNO on failure
 */
int cri_get_cycles(uint64_t *cycles);

/**
 * @brief Get elapsed cycles.
 *
 * Updates the reference to current cycles if there was no error.
 *
 * @param[in,out] ref reference cycles
 *
 * @return Positive for elapsed cycles, -ERRNO on failure
 */
int cri_cycles_delta(uint64_t *ref);

#endif
