/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file hs_aes.h
 *
 * @brief Public APIs for the High Speed AES (HSAES) core driver.
 */

#ifndef CMRT_HS_AES_H
#define CMRT_HS_AES_H

/**
 * HSAES support AES-GCM operations. It can operate in either of two operation
 * modes, viz. linear and bidirectional. There are two sets of API, one for
 * each mode (see @ref HSAES_LINEAR_API and @ref HSAES_BIDI_API).
 *
 * @defgroup hsaes_interface HSAES Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stdint.h>
#include <drivers/cmrt/aes.h>
#include <drivers/cmrt/kdc.h>
#include <drivers/cmrt/ktc.h>
#include <drivers/cmrt/hs_aes_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cmrt_hs_aes_context *cmrt_hs_aes_t;

/**
 * Open an HSAES device context.
 *
 * Open and return an HSAES context. Call may block for a context to be
 * available. Up to 128 contexts can be opened in Bidirectional mode. Up to 64
 * contexts can be opened Linear mode.
 *
 * By default Bidirectional mode is used. To select Linear mode @p flags should
 * be set to @ref CMRT_O_HSAES_LINEAR.
 *
 * All of the open contexts should be in same mode. To select a
 * different mode all open contexts must first be closed.
 *
 * @param flags Can be 0 or @ref CMRT_O_HSAES_LINEAR,
 *              CMRT_O_SYNC to autosync all operations.
 * @return      Device context handle on success or NULL on error.
 */
cmrt_hs_aes_t cmrt_hs_aes_open(uint32_t flags);

/**
 * Close HSAES device context, reverse of open.
 *
 * Close and free previously opened HSAES context. Call only if all queued
 * operations have finished. Otherwise an abort is issued @ref
 * cmrt_hs_aes_abort(). Linear buffer mode operation round should have concluded.
 *
 * @param dev Pointer to device context.
 */
void cmrt_hs_aes_close(cmrt_hs_aes_t dev);

/**
 * Return channel and key bank used by HSAES context.
 *
 * @param context           HSAES device context handle.
 * @param[out] channel   Pointer to return channel.
 * @param[out] key_bank  Pointer to return key_bank.
 */
void cmrt_hs_aes_get_channel_context(cmrt_hs_aes_t context, uint32_t *channel, uint32_t *key_bank);

/**
 * Wait for queued operations to finish and return status.
 *
 * @param dev HSAES device context handle.
 *
 * @return Zero on success. On error number of queued operations that have
 *         failed.
 */
int cmrt_hs_aes_sync(cmrt_hs_aes_t dev);

/**
 * Abort all queued operations across all open contexts. All open context should
 * be closed afterwards.
 *
 * @param dev HSAES device context handle.
 *
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_hs_aes_abort(cmrt_hs_aes_t dev);

/**
 * Derive key using Key Derivation Core (KDC) and set it to context @p dev.
 * KDC must not be in use. @p cmd's base_key_id, diversify_len and
 * diversify_path fields must be initialized.
 *
 * @param dev     HSAES device context handle.
 * @param keylen  Length of AES-GCM key in bytes. Should be either 16 or 32.
 * @param cmd     KDC command structure.
 *
 * @return          Zero on success, -ERRNO on error.
 * @retval -EBUSY   If KTC or AES core is not available.
 */
int cmrt_hs_aes_kdc_cmd(cmrt_hs_aes_t dev, size_t keylen, cmrt_kdc_cmd_t *cmd);

/**
 * @anchor HSAES_LINEAR_API
 * @name Linear buffer AES-GCM operation functions
 *
 * Functions should be called in following order. <BR>
 * • @ref cmrt_hs_aes_init <BR>
 * • @ref cmrt_hs_aes_update_aad (optional) <BR>
 * • @ref cmrt_hs_aes_final_aad (optional) <BR>
 * • @ref cmrt_hs_aes_update <BR>
 * • @ref cmrt_hs_aes_ae_final <BR>
 *
 * All buffers except for the key should be in DRAM.
 *
 * @ref cmrt_hs_aes_init() can be called again after @ref cmrt_hs_aes_ae_final()
 * to start another round of linear AES-GCM operation using the same key that
 * has been loaded into the context.
 *
 * Once a AES-GCM round has been started it must be finished before another
 * round can be started with the same context. A round can be aborted with
 * @ref cmrt_hs_aes_abort() and then all open contexts have to be closed.
 *
 * @note All of the above functions queue operations for HSAES to process,
 * therefore buffers backing arguments should not be repurposed unless
 * @ref cmrt_hs_aes_sync() has been called or CMRT_O_SYNC is set in
 * @ref cmrt_hs_aes_open().
 *
 * @note All buffers except for the key should be in DRAM.
 * <HR>
 * @{
 */

/**
 * Initialize linear AES-GCM operation.
 *
 * Once a key has been set, all subsequent operation of the context can
 * utilize it by setting @p key to NULL.
 *
 * @note This only queue operations for HSAES to process, therefore
 * buffers backing arguments should not be repurposed unless @ref
 * cmrt_hs_aes_sync() has been called or CMRT_O_SYNC is set in @ref
 * cmrt_hs_aes_open().
 *
 * @note All buffers except for the key should be in DRAM.

 * @param dev       HSAES device context handle.
 * @param operation Should be either CMRT_AES_ENCRYPT or CMRT_AES_DECRYPT,
 *                  see @ref cmrt_aes_operation_t.
 * @param mode      Should always be CMRT_AES_GCM, see @ref cmrt_aes_mode_t.
 * @param key       Pointer to AES-GCM key, should be NULL if KDC is used for
 *                  setting key, see @ref cmrt_hs_aes_kdc_cmd.
 * @param keylen    Length of key in bytes, should be either 16 or 32 if @p key
 *                  is not NULL, otherwise should be zero.
 * @param iv        Address of Initialization Vector (IV) buffer.
 * @param ivlen     Length of IV in bytes, should be 12.
 *
 * @return          Zero on success, -ERRNO on error.
 * @retval -EAGAIN  If operation queue is full.
 * @retval -EBUSY   If KTC or AES core is not available (only if @p key is
 *                  not NULL).
 * @retval -EINVAL  If an invalid argument is supplied.
 * @retval -EIO     If a HW error is encountered.
 */
int cmrt_hs_aes_init(cmrt_hs_aes_t dev,
		     cmrt_aes_operation_t operation, cmrt_aes_mode_t mode,
		     const void *key, size_t keylen,
		     uint64_t iv, size_t ivlen);

/**
 * Supply Associated Authentication Data (AAD) for linear AES-GCM operation.
 *
 * @note This only queue operations for HSAES to process, therefore
 * buffers backing arguments should not be repurposed unless @ref
 * cmrt_hs_aes_sync() has been called or CMRT_O_SYNC is set in @ref
 * cmrt_hs_aes_open().
 *
 * @note All buffers should be in DRAM.

 * @param dev       HSAES device context handle.
 * @param aad       Address of AAD buffer.
 * @param aadlen    Length of AAD in bytes. Should be multiple of
 *                  @ref CMRT_HSAES_BLOCK_SIZE.
 *
 * @return          Zero on success, -ERRNO on error.
 * @retval -EAGAIN  If operation queue is full.
 * @retval -EINVAL  If an invalid argument is supplied.
 * @retval -EIO     If a HW error is encountered.
 */
int cmrt_hs_aes_update_aad(cmrt_hs_aes_t dev, uint64_t aad, size_t aadlen);

/**
 * Supply final block of Associated Authentication Data (AAD) for linear AES-GCM
 * operation.
 *
 * @note This only queue operations for HSAES to process, therefore
 * buffers backing arguments should not be repurposed unless @ref
 * cmrt_hs_aes_sync() has been called or CMRT_O_SYNC is set in @ref
 * cmrt_hs_aes_open().
 *
 * @note All buffers should be in DRAM.
 *
 * @param dev       HSAES device context handle.
 * @param aad       Address of AAD buffer.
 * @param aadlen    Length of AAD in bytes. Should be multiple of
 *                  @ref CMRT_HSAES_BLOCK_SIZE.
 *
 * @return          Zero on success, -ERRNO on error.
 * @retval -EAGAIN  If operation queue is full.
 * @retval -EINVAL  If an invalid argument is supplied.
 * @retval -EIO     If a HW error is encountered.
 */
int cmrt_hs_aes_final_aad(cmrt_hs_aes_t dev, uint64_t aad, size_t aadlen);

/**
 * Process a block of data for linear AES-GCM operation.
 *
 * @note This only queue operations for HSAES to process, therefore
 * buffers backing arguments should not be repurposed unless @ref
 * cmrt_hs_aes_sync() has been called or CMRT_O_SYNC is set in @ref
 * cmrt_hs_aes_open().
 *
 * @note All buffers should be in DRAM.
 *
 * @param dev       HSAES device context handle.
 * @param input     Address of input buffer.
 * @param inlen     Length of input in bytes. Should be multiple of
 *                  @ref CMRT_HSAES_BLOCK_SIZE
 * @param output    Address of output buffer.
 *
 * @return          Zero on success, -ERRNO on error.
 * @retval -EAGAIN  If operation queue is full.
 * @retval -EINVAL  If an invalid argument is supplied.
 * @retval -EIO     If a HW error is encountered.
 */
int cmrt_hs_aes_update(cmrt_hs_aes_t dev, uint64_t input, size_t inlen, uint64_t output);

/**
 * Conclude linear AES-GCM operation.
 *
 * @note This only queue operations for HSAES to process, therefore
 * buffers backing arguments should not be repurposed unless @ref
 * cmrt_hs_aes_sync() has been called or CMRT_O_SYNC is set in @ref
 * cmrt_hs_aes_open().
 *
 * @param dev       HSAES device context handle.
 * @param input     Address of input buffer.
 * @param inlen     Length of input in bytes. Should be multiple of
 *                  @ref CMRT_HSAES_BLOCK_SIZE
 * @param output    Address of output buffer.
 * @param tag       Address of tag buffer. Should be aligned to 16 and should
 *                  not be @ref CMRT_EXT_MEMORY_DDR_CMRT.
 * @param taglen    Length of tag in bytes. Should be 16.
 *
 * @return          Zero on success, -ERRNO on error.
 * @retval -EAGAIN  If operation queue is full.
 * @retval -EINVAL  If an invalid argument is supplied.
 * @retval -EIO     If a HW error is encountered.
 */
int cmrt_hs_aes_ae_final(cmrt_hs_aes_t dev, uint64_t input, size_t inlen, uint64_t output, uint64_t tag, size_t *taglen);
/** @} */

/**
 * @anchor HSAES_BIDI_API
 * @name Bidirectional AES-GCM operation function
 *
 * Bidirectional HSAES operation is driven by Address Table, in lockstep with
 * PDMA. PDMA copies data from HLOS to DRAM and from DRAM to HLOS, HSAES process
 * data copied from HLOS and produces data to be copied to HLOS. Address Table
 * specifies a list of source and destination memory pages (in HLOS address
 * space, for PDMA use) and associated meta data (iv, tag, ad).  See @ref
 * cmrt_pdma_at_t, @ref pdma_interface.
 *
 * All buffers except for the key should be in DRAM.
 *
 * Multiple bidirectional operation can be queued once a key has been set.
 *
 * Both HSAES and PDMA should use same channel to work in lockstep. An HSAES
 * context must be opened first. The channel and key bank associated with HSAES
 * context can be queried using @ref cmrt_hs_aes_get_channel_context(), it should
 * be used for opening PDMA context.
 *
 * @note All buffers except for the key should be in DRAM.
 * <HR>
 * @{
 */

/**
 * Enqueue a bidirectional AES-GCM operation.
 *
 * Once a key has been set, all subsequent operation of the context can
 * utilize it by setting @p key to NULL.
 *
 * @note All buffers except for the key should be in DRAM.
 *
 * @note This only queue operations for HSAES to process, therefore
 * buffers backing arguments should not be repurposed unless @ref
 * cmrt_hs_aes_sync() has been called or CMRT_O_SYNC is set in @ref
 * cmrt_hs_aes_open().
 *
 * @param dev       HSAES device context handle.
 * @param operation Should be either CMRT_AES_ENCRYPT or CMRT_AES_DECRYPT,
 *                  see @ref cmrt_aes_operation_t.
 * @param mode      Should always be CMRT_AES_GCM, see @ref cmrt_aes_mode_t.
 * @param key       Pointer to AES-GCM key, should be NULL if the key has
 *                  already been loaded by a previous operation or by
 *                  @ref cmrt_hs_aes_kdc_cmd.
 * @param keylen    Length of key in bytes, should be either 16 or 32. Ignored
 *                  if @p key is NULL.
 * @param at_count  Number of entries in the Address Table.
 * @param inbuf     Address of first input buffer. Must be aligned to
 *                  @ref CMRT_DCM_DDR_BUFFER_SIZE.
 * @param outbuf    Address of first output buffer. Must be aligned to
 *                  @ref CMRT_DCM_DDR_BUFFER_SIZE.
 *
 * @return          Zero on success, -ERRNO on error.
 * @retval -EAGAIN  If operation queue is full.
 * @retval -EBUSY   If KTC or AES core is not available (only if @p key is
 *                  not NULL).
 * @retval -EINVAL  If an invalid argument is supplied.
 * @retval -EIO     If a HW error is encountered.
 */
int cmrt_hs_aes_queue_at(cmrt_hs_aes_t dev,
			 cmrt_aes_operation_t operation, cmrt_aes_mode_t mode,
			 const void *key, size_t keylen,
			 uint32_t at_count, uint64_t inbuf, uint64_t outbuf);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
