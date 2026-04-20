/*
 * Copyright (c) 2018-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file cc.h
 *
 * @brief Public APIs for the CC driver.
 */

#ifndef CRI_CC_H
#define CRI_CC_H

/**
 * @brief CC Interface
 * @defgroup cc_interface CC Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <cc_reg.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_cc_t;
#else
typedef struct cmrt_cc_context *cri_cc_t;
#endif

/**
 * @brief Open CC for subsequent operations.
 *
 * Open and reserve CC, may block for it to be available.
 *
 * @return Context handle on success or NULL on error.
 */
cri_cc_t cri_cc_open(void);

/**
 * @brief Close CC, reverse of open.
 *
 * Close and free previously opened CC.
 *
 * @param context Pointer to the device.
 */
void cri_cc_close(cri_cc_t context);

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
int cri_cc_assert(cri_cc_t context, uint32_t assert0, uint32_t assert1);

/**
 * @brief Mix CC with a value.
 *
 * Mix CC with a value.
 *
 * @param context Pointer to the device.
 * @param value Mix value.
 * @return Zero on success, -ERRNO on error.
 */
int cri_cc_mix(cri_cc_t context, uint32_t value);

/**
 * @brief Assert CC to match given assert values.
 *
 * Assert CC to match given assert values. Assert failure will result into
 * NMI error or HW panic.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_cc_sync(cri_cc_t context);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
