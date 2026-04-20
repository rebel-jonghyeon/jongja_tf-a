/*
 * Copyright (c) 2017-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file sic.h
 *
 * @brief Public APIs for the SIC driver.
 */

#ifndef CRI_SIC_H
#define CRI_SIC_H

/**
 * @brief SIC Interface
 * @defgroup sic_interface SIC Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <sic_reg.h>


#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Flow ID to specify for opening the reserved flow id of the loadable
 * user container. This flow id gets translated to the flow id used to
 * load the container.
 */
#define CRI_RESERVED_FLOWID 0x1000

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_sic_t;
#else
typedef struct cmrt_sic_context *cri_sic_t;
#endif

/**
 * @brief Open SIC channel for given flow id.
 *
 * Thread can open many SIC channels but one flow id can be opened
 * only once in the system. Flow ids are like ports in the TCP/IP world.
 *
 * @param[in] flags Zero requires cri_sic_sync only after cri_sic_read,
 *                      cri_sic_write calls sync automatically (cri_sic_sync
 *                      must not be called)
 *                  CRI_O_SYNC both cri_sic_read and cri_sic_write calls
 *                      automatically call sync
 *                  CRI_O_ASYNC no need to call cri_sic_sync after either
 *                      cri_sic_read or cri_sic_write
 * @param[in] flowid Flow id to open for reading and writing.
 * @return Context handle on success or NULL on error.
 */
cri_sic_t cri_sic_open(uint32_t flags, uint32_t flowid);

/**
 * @brief Close SIC channel for given flow id.
 *
 * @param[in] context Pointer to the SIC device.
 */
void cri_sic_close(cri_sic_t context);

/**
 * @brief Read SIC protocol request for given flow id.
 *
 * Setup for reading SIC protocol request. Reading completes when one full
 * protocol message has been received for given flow id. To finish reading
 * cri_sic_sync must be called, or CRI_O_SYNC must be set in cri_sic_open.
 *
 * @param[in] context Pointer to the SIC device.
 * @param[out] buffer Pointer to buffer for message data.
 * @param[in,out] buflen Length of max data in bytes and returned length.
 * @param[out] peerid Sending flow id in return for read.
 * @return Zero on success, -ERRNO on error.
 */
int cri_sic_read(cri_sic_t context, void *buffer, size_t *buflen, uint32_t *peerid);

/**
 * @brief Write SIC protocol response.
 *
 * Setup for writing SIC protocol response. Writing completes when all data
 * has been sent. By default cri_sic_write calls cri_sic_sync automatically,
 * unless CRI_O_ASYNC has been set in cri_sic_open.
 *
 * @param[in] context Pointer to the SIC device.
 * @param[in] buffer Pointer to buffer for message data.
 * @param[in] buflen Length of the buffer in bytes.
 * @param[in] peerid Destination flow id received in cri_sic_read.
 * @return Zero on success, -ERRNO on error.
 */
int cri_sic_write(cri_sic_t context, const void *buffer, size_t buflen, uint32_t peerid);

/**
 * @brief Synchronize SIC protocol operation.
 *
 * Wait for completion of ongoing read and/or write asyncronious operation.
 * Does return immediately if operations have been completed.
 * cri_sic_sync call may or may not be required to complete
 * cri_sic_read/cri_sic_write operations and may even block indefinitely,
 * depending upon the flag used, refer to @ref cri_sic_open.
 *
 * @param[in] context Pointer to the SIC device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_sic_sync(cri_sic_t context);

/**
 * @brief Test if SIC is idle.
 *
 * This function is used by the OS to detect possibility to go
 * into low power mode.
 *
 * @return True if idle, false otherwise.
 */
bool cri_sic_is_idle(void);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
