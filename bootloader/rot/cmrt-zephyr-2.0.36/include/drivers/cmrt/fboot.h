/*
 * Copyright (c) 2021-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file cmrt/fboot.h
 *
 * @brief FBOOT system call APIs.
 */

#ifndef CMRT_FBOOT_H
#define CMRT_FBOOT_H

/**
 * @brief FBOOT Interface
 * @defgroup fboot_interface FBOOT Interface
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <stdbool.h>
#include <drivers/cmrt/omc.h>
#include <cmrt/fboot/img_format.h>
#include <cmrt/fboot/img_version.h>
#include <cmrt/fboot/datastore_attr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Validate image and setup HW security context.
 *
 * Verify supervisor mode access to container image, check image signature and
 * validate container permissions. Container root must exist. If all checks are
 * good then setup HW security context.
 *
 * @param blob Pointer to container image.
 * @param size Size of container image.
 * @param raw Raw footer on return.
 * @param usr User footer on return.
 * @return Image caveat on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
int fboot_load_image(void *blob, size_t size, cmrt_raw_footer_t *raw, cmrt_usr_footer_t *usr);

/**
 * Establish a new root.
 *
 * When using emulated OTP, AES and HC core must be free.
 *
 * @param index Root table index (allowed values 0-7 for OTP roots).
 * @param new_root New root entry to create.
 * @return Zero on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
__syscall int fboot_create_root(int index, const cmrt_omc_root_t *new_root);

/**
 * Obliterate an existing root.
 *
 * When using emulated OTP, AES and HC core must be free.
 *
 * @param index Root table index (allowed values 0-7 for OTP roots).
 * @return Zero on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
__syscall int fboot_obliterate_root(int index);

/**
 * @brief Call when supervisor exits.
 *
 * Call when supervisor exits due to a trap in essential thread
 * or when HLOS tells it to exit.
 *
 * @param major Reason for exit.
 * @param minor Lower level reason.
 * @return Does not return.
 *
 * @ingroup FBOOT_API
 */
__syscall int fboot_halt(int major, int minor);

/**
 * @brief Call to reboot CMRT.
 *
 * Reboot fully reboots and restarts CMRT.
 *
 * @return Does not return.
 *
 * @ingroup FBOOT_API
 */
__syscall int fboot_reboot(void);

/**
 * @brief Call to reset CMRT.
 *
 * Reset reboots and restarts CMRT and clears SRAM.
 * Reset can be used to alter the normal startup. For example,
 * sboot could be told to load a secondary image instead of the
 * default image, and supervisor could be told not to autoload a
 * user container. The reset info is application specific.
 *
 * @param info Information for sboot and/or supervisor.
 * @return Does not return.
 */
__syscall int fboot_reset(uint32_t info);

/**
 * @brief Get previous reset information.
 *
 * When booting up this function can be called to get the
 * reset information set in a call to fboot_reset.
 * Returns the number of low power events since last reset.
 *
 * @param info Information for sboot and/or supervisor.
 * @return Zero or positive on success, -ERRNO on error.
 */
__syscall int fboot_reset_info(uint32_t *info);

/**
 * @brief Get currently running image version string.
 *
 * Version string is set at compile time for each image.
 *
 * @param image Image identifier
 * @param version Version value
 * @param size Version value size
 * @return Zero on success, -ERRNO on error.
 */
__syscall int fboot_get_image_version(enum cmrt_image_version_id image, void *version, size_t *size);

/**
 * @brief Get enforced image version in OTP.
 *
 * At boot image footer versions are checked against values in OTP.
 * Value in the image footer must be equal or greater than the value in OTP.
 *
 * @param image Image identifier
 * @param version Pointer to the version value
 * @return Zero on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
__syscall int fboot_get_enforced_version(enum cmrt_enforced_version_id image, uint32_t *version);

/**
 * @brief Set enforced image version in OTP.
 *
 * At boot image footer versions are checked against values in OTP.
 * Value in the image footer must be equal or greater than the value in OTP.
 * Typically these values are set at image upgrades only to prevent booting
 * up to older possibly buggy versions.
 *
 * @param image Image identifier
 * @param version New version value
 * @return Zero on success, -ERRNO on error.
 *
 * @ingroup FBOOT_API
 */
__syscall int fboot_set_enforced_version(enum cmrt_enforced_version_id image, uint32_t version);

/**
 * @brief Setup boot bypass when waking up from sleep.
 *
 * Called by the idle thread if PMU support has been enabled. Saves the OS
 * state just before calling WFI. HLOS can command CMRT to sleep, when waking
 * up fboot will restore the OS state and jump back to the idle thread.
 *
 * @param stack Pointer to the boot bypass stack frame.
 * @param function Pointer to the boot bypass function.
 * @return Zero on success, -ERRNO on error.
 */
int fboot_prepare_boot_bypass(const void *stack, const void *function);

/**
 * @brief Read object from security monitor data store.
 *
 * Security monitor data store can be used to pass access controlled
 * objects between CMRT boot stages and applications.
 *
 * Caller must be signed by a root that has read access to the object.
 *
 * @param [in] name Object name can be string or binary.
 * @param [in] namelen Object name length.
 * @param [out] data Object data can be string or binary.
 * @param [in,out] datalen Object data length in return.
 * @param [in] user True if the syscall was relayed by the supervisor.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int fboot_data_store_read(const void *name, size_t namelen, void *data, size_t *datalen, bool user);

/**
 * @brief Write or update object in security monitor data store.
 *
 * Security monitor data store can be used to pass access controlled
 * objects between CMRT boot stages and applications.
 *
 * Caller must be signed by a root that has write access to an
 * existing object. New object will be created if the name cannot be found.
 * Default attributes for new object are zero for machine (sboot/tboot) and
 * DS_S_GRANT/DS_U_GRANT for supervisor/user. Call fboot_data_store_grant()
 * to define object visibility.
 *
 * @param [in] name Object name can be string or binary.
 * @param [in] namelen Object name length.
 * @param [in] data Object data can be string or binary.
 * @param [in] datalen Object data length in return.
 * @param [in] user True if the syscall was relayed by the supervisor.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int fboot_data_store_write(const void *name, size_t namelen, const void *data, size_t datalen, bool user);

/**
 * @brief Grant or revoke access to object in security monitor data store.
 *
 * Security monitor data store can be used to pass access controlled
 * objects between CMRT boot stages and applications.
 *
 * Caller must be signed by a root that has grant access to the existing
 * object. The object will be removed if it has no access from any root after
 * the operation. Root index values 0 .. CMRT_OTP_NUM_ROOTS-1 are OTP roots
 * and index value CMRT_OTP_NUM_ROOTS is for the perso root.
 *
 * @param [in] name Object name can be string or binary.
 * @param [in] namelen Object name length.
 * @param [in] attributes Access for the root, see datastore_attr.h.
 * @param [in] index Root index to set attributes for or -1 for current root.
 * @param [in] user True if the syscall was relayed by the supervisor.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int fboot_data_store_grant(const void *name, size_t namelen, uint32_t attributes, int index, bool user);

#ifdef __cplusplus
}
#endif

#include <syscalls/fboot.h>

#endif
/** @}*/
