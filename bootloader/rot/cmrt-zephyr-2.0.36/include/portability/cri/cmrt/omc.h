/*
 * Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file omc.h
 *
 * @brief Public APIs for the OMC driver.
 */

#ifndef CRI_OMC_H
#define CRI_OMC_H

/**
 * @brief OMC Interface
 * @defgroup omc_interface OMC Interface
 * @ingroup io_interfaces
 * @{
 */
#include <stddef.h>
#include <stdint.h>
#include <omc_reg.h>
#include <oec_reg.h>
#include "aes.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CMRT_CSDK_VERSION_CODE
typedef int cri_otp_t;
#else
typedef struct cmrt_omc_context *cri_otp_t;
#endif

/**
 * @brief Get pointer to OTP base address.
 *
 * @retval Pointer to OTP base address.
 */
static inline void *cri_otp_layout(void)
{
#ifndef CONFIG_RISCV_OTP_BASE_ADDR
#error CONFIG_RISCV_OTP_BASE_ADDR Undefined!
#endif
	return (void *)(uintptr_t)CONFIG_RISCV_OTP_BASE_ADDR;
}

/**
 * @brief Open OMC context for subsequent operations.
 *
 * Open and reserve an OMC context. May block for a context to be available.
 *
 * When using emulated OTP, @ref CRI_O_OTP_COMMIT flag can be specified, then
 * OMC driver reserves HC and AES contexts. @ref cri_otp_close/
 * @ref cri_otp_sclose then auto commits OTP contents and releases HC and AES
 * contexts. This flag is NOP if CONFIG_CRI_OMC_EMULATED_OTP is not set.
 *
 * @param context Pointer to the device.
 * @param flags CRI_O_OTP_COMMIT for autocommit, see above.
 *              CRI_O_SYNC to autosync all operations, if not set one must call
 *              cri_otp_sync explicitly for most API calls.
 * @return Semaphore handle on success or NULL on error.
 */
cri_otp_t cri_otp_open(uint32_t flags);

/**
 * @brief Close OMC context, reverse of open.
 *
 * Close and free previously opened OMC context.
 *
 * When using emulated OTP, if @ref CRI_O_OTP_COMMIT flag is specified in @ref
 * cri_otp_open, then OTP contents are auto committed and HC and AES contexts
 * are released.
 *
 * @param context Pointer to the device.
 */
void cri_otp_close(cri_otp_t context);

/**
 * @brief Get OMC command result.
 *
 * Get OMC result after interrupt, or wait until it finishes.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_sync(cri_otp_t context);

#ifdef CMRT_CSDK_VERSION_CODE
/**
 * @brief Read device id from OTP.
 *
 * User mode only function.
 *
 * @param context Pointer to the device.
 * @param data Pointer to data.
 * @param datalen Data length.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_read_device_id(cri_otp_t dev, uint8_t *data, size_t datalen);

/**
 * @brief Read OEM id from OTP.
 *
 * User mode only function.
 *
 * @param context Pointer to the device.
 * @param data Pointer to data.
 * @param datalen Data length.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_read_oem_id(cri_otp_t dev, uint8_t *data, size_t datalen);

/**
 * @brief Read raw data from OTP.
 *
 * User mode only function.
 *
 * @param context Pointer to the device.
 * @param addr Address offset to the eSW area.
 * @param buffer Pointer to buffer.
 * @param buflen Buffer size.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_read_raw(cri_otp_t omc, uint32_t addr, uint32_t *buffer, size_t buflen);

/**
 * @brief Write raw data from OTP.
 *
 * User mode only function.
 *
 * @param context Pointer to the device.
 * @param addr Address offset to the eSW area.
 * @param buffer Pointer to buffer.
 * @param buflen Buffer size.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_write_raw(cri_otp_t omc, uint32_t addr, const uint32_t *buffer, size_t buflen);

int cri_otp_oec_fuses(cri_otp_t omc, size_t buflen, uint8_t *rbuf, const uint8_t *wbuf, uint32_t flags);
#endif

/**
 * @brief Reshadow OTP
 *
 * Request that OMC reparse OTP assets and update certain SIC registers,
 * DEVICE_LIFECYCLE register for example. Caller must call cri_otp_sync to
 * wait for completion, or CRI_O_SYNC must be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_reshadow(cri_otp_t context);

/**
 * @brief Burn device id into OTP.
 *
 * This can be done once and is typically done during device personalization
 * in machine mode. Caller must call cri_otp_sync to wait for completion,
 * or CRI_O_SYNC must be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @param data Pointer to data.
 * @param datalen Data length.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_write_device_id(cri_otp_t context, const uint8_t *data, size_t datalen);

/**
 * @brief Burn OEM id into OTP.
 *
 * This can be done once and is typically done during device personalization
 * in machine mode. Caller must call cri_otp_sync to wait for completion,
 * or CRI_O_SYNC must be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @param data Pointer to data.
 * @param datalen Data length.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_write_oem_id(cri_otp_t context, const uint8_t *data, size_t datalen);

/**
 * @brief Burn lifecycle into OTP.
 *
 * Setting lifecycle is typically done during device personalization
 * in machine mode. Each lifecycle value burns more bits. Caller must call
 * cri_otp_sync to wait for completion, or CRI_O_SYNC must be set in
 * cri_otp_open.
 *
 * @param context Pointer to the device.
 * @param lc Lifecycle value to burn.
 * @retval Zero on success or if the lc equals existing lifecycle.
 * @retval -EINVAL for invalid lc parameter value.
 * @retval -EFAULT if trying to set a lifecycle in the past.
 */
int cri_otp_set_lifecycle(cri_otp_t context, uint32_t lc);

/**
 * @brief Set up OMC privilege registers.
 *
 * This must be done in machine mode and is typically handled in the
 * security monitor.
 *
 * @param context Pointer to the device.
 * @param perm Caller must fill fields properly, see omc_reg.h.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_setup_privilege(cri_otp_t context, const omc_perm_t *perm);

/**
 * @brief Write keysplit to given index.
 *
 * Caller must call cri_otp_sync to wait for completion, or CRI_O_SYNC must
 * be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @param index Index of keysplit. Range from 0 to 6, inclusive.
 * @param keysplit Pointer to the keysplit data.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_write_keysplit(cri_otp_t context, int index,
			   const cmrt_omc_key_split_t *keysplit);

#if defined(CONFIG_CRI_OMC_LAYOUT_VERSION) && CONFIG_CRI_OMC_LAYOUT_VERSION >= 2
/**
 * @brief Obliterate keysplit at given index.
 *
 * The keysplit must be valid before it can be obliterated. Caller must call
 * cri_otp_sync to wait for completion, or CRI_O_SYNC must be set in
 * cri_otp_open.
 *
 * @param context Pointer to the device.
 * @param index Index of keysplit. Range from 0 to 6, inclusive.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_obliterate_keysplit(cri_otp_t context, int index);

/**
 * @brief Obliterate DGOK.
 *
 * The DGOK must be valid before it can be obliterated. Caller must call
 * cri_otp_sync to wait for completion, or CRI_O_SYNC must be set in
 * cri_otp_open.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_obliterate_dgok(cri_otp_t context);
#endif

/**
 * @brief Read root at given index.
 *
 * @param context Pointer to the device.
 * @param index Index of root. Range from 0 to 7, inclusive.
 * @param root Pointer to root object to fill.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_read_root(cri_otp_t context, int index, cmrt_omc_root_t *root);

/**
 * @brief Write root to given index.
 *
 * Only machine mode is allowed to write roots, this is typically done in
 * the security monitor. Caller must call cri_otp_sync to wait for completion,
 * or CRI_O_SYNC must be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @param index Index of root. Range from 0 to 7, inclusive.
 * @param root Pointer to root object to write.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_write_root(cri_otp_t context, int index, const cmrt_omc_root_t *root);

/**
 * @brief Obliterate root at given index.
 *
 * Only machine mode is allowed to obliterate roots, this is typically done in
 * the security monitor. Caller must call cri_otp_sync to wait for completion,
 * or CRI_O_SYNC must be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @param index Index of root. Range from 0 to 7, inclusive.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_obliterate_root(cri_otp_t context, int index);

/**
 * @brief Obliterate perso root.
 *
 * Only machine mode is allowed to obliterate roots, this is typically done in
 * the security monitor. Perso root is a manufacturing root which can be
 * obliterated after device personalization. Caller must call cri_otp_sync to
 * wait for completion, or CRI_O_SYNC must be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_obliterate_perso(cri_otp_t context);

/**
 * @brief Set test and debug vector.
 *
 * Only machine mode is allowed to set TDV. Caller must call cri_otp_sync to
 * wait for completion, or CRI_O_SYNC must be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @param tdv Test and debug vector.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_set_tdv(cri_otp_t context, const uint32_t tdv[OMC_TDV_WORDS]);

/**
 * @brief Read reserved eSW control/config word from OTP.
 *
 * Reserved control/config words are placed to the beginning or end of
 * the OTP eSW area depending on configuration. See @cri_otp_is_esw_area().
 *
 * @param context Pointer to the device.
 * @param offset Reserved word offset, see below for values.
 * @param word Pointer to result data.
 * @retval Zero on success.
 * @retval -EINVAL if parameters were invalid.
 * @retval -EFAULT if the reserved eSW area is invalid.
 */
int cri_otp_read_esw_rsvd(cri_otp_t context, uint32_t offset, uint32_t *word);

/**
 * @brief Write reserved eSW control/config word to OTP.
 *
 * Reserved control/config words are placed to the beginning or end of
 * the OTP eSW area depending on configuration. See @cri_otp_is_esw_area().
 *
 * @param context Pointer to the device.
 * @param offset Reserved word offset, see below for values.
 * @param word Data to write.
 * @retval Zero on success.
 * @retval -EINVAL if parameters were invalid.
 * @retval -EFAULT if the reserved eSW area is invalid.
 */
int cri_otp_write_esw_rsvd(cri_otp_t context, uint32_t offset, uint32_t word);

#define OTP_TBOOT_VERSION_WORD_OFFSET 0
#define OTP_SUPERVISOR_VERSION_WORD_OFFSET (OTP_TBOOT_VERSION_WORD_OFFSET + sizeof(uint32_t))
#define OTP_EIP76_CONTROL_WORD_OFFSET (OTP_SUPERVISOR_VERSION_WORD_OFFSET + sizeof(uint32_t))
#define OTP_EIP76_CONFIG_WORD_OFFSET (OTP_EIP76_CONTROL_WORD_OFFSET + sizeof(uint32_t))

/**
 * @brief Check for valid eSW area address.
 *
 * This function can be used to make sure not to accidentally write
 * to the reserved eSW area in OTP. For example, writing on top of sboot
 * image will make boot up fail permanently.
 *
 * @param context Pointer to the device.
 * @param address Address to check, this is pointer not an offset nor value.
 * @retval Positive value if address hits the valid eSW area.
 * @retval Zero if address is valid but hits the reserved eSW area.
 * @retval -EINVAL if address is not a valid OTP address.
 * @retval -EBADF if the reserved eSW area parsing failed.
 * @retval -EFAULT for OTP layout configuration mismatch.
 * @retval -EACCES if address is valid but hits the hardware managed area.
 */
int cri_otp_is_esw_area(cri_otp_t context, const uint32_t *address);

/**
 * @brief Read OEC controlled data.
 *
 * This function is a NOP if CONFIG_CRI_OMC_EMULATED_OTP is not set.
 * See oec_reg.h for address values. Caller must call cri_otp_sync to
 * wait for completion, or CRI_O_SYNC must be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @param address Requested data address.
 * @param buffer Output buffer for data.
 * @param size Buffer size in bytes.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_oec_read(cri_otp_t context, uint32_t address, void *buffer, size_t *len);

/**
 * @brief Write OEC controlled data.
 *
 * This function is a NOP if CONFIG_CRI_OMC_EMULATED_OTP is not set.
 * See oec_reg.h for address values. Caller must call cri_otp_sync to
 * wait for completion, or CRI_O_SYNC must be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @param address Requested data address.
 * @param buffer Output buffer for data.
 * @param size Buffer size in bytes.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_oec_write(cri_otp_t context, uint32_t address, const void *buffer, size_t len);

/**
 * @brief Commit changes to the OTP.
 *
 * This function is a NOP if CONFIG_CRI_OMC_EMULATED_OTP is not set.
 * When using emulated OTP one must call this function to commit
 * written changes to the OTP. Caller must call cri_otp_sync to
 * wait for completion, or CRI_O_SYNC must be set in cri_otp_open.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
int cri_otp_oec_commit(cri_otp_t context);

/**
 * @brief Derive key to AES.
 *
 * The aes must be opened with CRI_O_HWC_KEYED.
 * The AES core will be keyed and initialized with the correct IV and
 * tag length of 96 bits.
 *
 * @param oec open handle to emulation core
 * @param operation AES_ENCRYPT or AES_DECRYPT
 * @param keysplit keysplit to derive from.  0 or 1.
 * @return cri_aes_t handle to the keyed aes core
 */
cri_aes_t cri_otp_oec_derive(cri_otp_t oec, cri_aes_operation_t operation,
			     uint8_t keysplit);

#ifdef __cplusplus
}
#endif

#endif
/** @}*/
