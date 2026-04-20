/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file ktc.h
 *
 * @brief Public APIs for the KTC driver.
 */

#ifndef CMRT_KTC_H
#define CMRT_KTC_H

/**
 * @brief KTC Interface
 * @defgroup ktc_interface KTC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <device.h>
#include <drivers/cmrt/ktc_reg.h>
#include <drivers/cmrt/omc_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_ktc_context *cmrt_ktc_t;

typedef struct {
	/** 64 bit key metadata. Metadata is transferred along with key to SOC. */
	uint32_t metadata[2];
	/** Key destination. Valid values: 0-15. */
	uint32_t destination;
	/** key size in bytes, upto 4080, should be multiple of 16. */
	uint32_t key_size;
	/** bytes of key */
	uint32_t *key;
} cmrt_ktc_cmd_t;

/**
 * @brief Open KTC context for subsequent operations.
 *
 * Open and reserve a KTC context. May block for a context to be available.
 *
 * @param flags Zero to call cmrt_ktc_sync after an operation,
 *              CMRT_O_SYNC to autosync all operations.
 * @param timeout Time in ms to wait for HLOS to react when operations
 *                are synced. Zero means indefinite. ETIMEDOUT is returned
 *                if the timeout expires.
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_ktc_t cmrt_ktc_open(uint32_t flags, uint32_t timeout);

/**
 * @brief Close KTC context, reverse of open.
 *
 * Close and free previously opened KTC context.
 *
 * @param context Pointer to the device context.
 */
__syscall void cmrt_ktc_close(cmrt_ktc_t context);

/**
 * @brief Export key.
 *
 * Export the key to SOC. Caller must call cmrt_ktc_sync or set the
 * CMRT_O_SYNC flag in cmrt_ktc_open to finish the operation.
 *
 * @param context Pointer to the device context.
 * @param cmd In and Out parameters.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_ktc_export(cmrt_ktc_t context, const cmrt_ktc_cmd_t *cmd);

/**
 * @brief Synchronize KTC operation to get the result.
 *
 * Wait for completion of ongoing KTC operation.
 * Does return immediately if operation has been completed.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_ktc_sync(cmrt_ktc_t context);

/**
 * @brief Set allowed key destinations.
 *
 * Permissions are locked once written until CCC or reset.
 * Setting requires canary to be valid. Permissions are typically set
 * by the machine mode security monitor.
 *
 * @param context Pointer to the device context.
 * @param perm Pointer to permissions.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_ktc_permissions(cmrt_ktc_t context, const cmrt_omc_key_perm_t *perm);

#ifdef __cplusplus
}
#endif

#include <syscalls/ktc.h>

#endif
/** @}*/
