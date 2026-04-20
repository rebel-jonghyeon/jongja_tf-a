/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file ktc.h
 *
 * @brief Public APIs for the KTC driver.
 */

#ifndef CRI_KTC_H
#define CRI_KTC_H

/**
 * @brief KTC Interface
 * @defgroup ktc_interface KTC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <ktc_reg.h>
#include <omc_reg.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_ktc_t;
#else
typedef struct cmrt_ktc_context *cri_ktc_t;
#endif

typedef struct {
	/** 64 bit key metadata. Metadata is transferred along with key to SOC. */
	uint32_t metadata[2];
	/** Key destination. Valid values: 0-15. */
	uint32_t destination;
	/** key size in bytes, upto 4080, should be multiple of 16. */
	uint32_t key_size;
	/** bytes of key */
	uint32_t *key;
} ktc_cmd_t;

/**
 * @brief Open KTC context for subsequent operations.
 *
 * Open and reserve a KTC context. May block for a context to be available.
 *
 * @return Context handle on success or NULL on error.
 */
cri_ktc_t cri_ktc_open(void);

/**
 * @brief Close KTC context, reverse of open.
 *
 * Close and free previously opened KTC context.
 *
 * @param context Pointer to the device context.
 */
void cri_ktc_close(cri_ktc_t context);

/**
 * @brief Export key.
 *
 * Export the key to SOC. If during the key export operation KTC core does not
 * reach expected state within 1,000,000 iterations then operation fails with
 * -ETIMEDOUT, it can happen if SOC does not acknowledge receipt of a key block
 * for example.
 *
 * @param context Pointer to the device context.
 * @param cmd In and Out parameters.
 * @return Zero on success, -ERRNO on error.
 */
int cri_ktc_export_key(cri_ktc_t context, const ktc_cmd_t *cmd);

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
int cri_ktc_set_permissions(cri_ktc_t context, const cmrt_omc_key_perm_t *perm);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
