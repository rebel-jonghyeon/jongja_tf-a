/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef FBOOT_SMCALLS_H
#define FBOOT_SMCALLS_H

#include <omc_reg.h>
#include <stddef.h>
#include <zephyr/types.h>
#include <cri/cmrt/img_format.h>
#include <cri/cmrt/img_version.h>

/*
 * Security Monitor System Calls client side
 *
 * These functions implement the syscall trampoline, and are typically
 * included in a client library. Simply include cri_syscall.h and
 * define your system calls.
 */

/**
 * @brief Load container.
 *
 * @param blob Pointer to binary blob.
 * @param size Size of the blob.
 * @return Zero on success, ERRNO on error.
 */
int cri_mcall_load_container(void *blob, size_t size);

/**
 * @brief Unload container.
 *
 * @param blob Pointer to binary blob.
 * @param size Size of the blob.
 * @return Zero on success, -ERRNO on error.
 */
int cri_mcall_unload_container(void *blob, size_t size);

/**
 * @brief Establish a new root.
 *
 * @param index Root table index (allowed values 0-7 for OTP roots).
 * @param new_root New root entry to create.
 * @return Zero on success, -ERRNO on error.
 */
int cri_mcall_create_root(int index, const cmrt_omc_root_t *new_root);

/**
 * @brief Obliterate an existing root.
 *
 * @param index Root table index (allowed values 0-7 for OTP roots).
 * @return Zero on success, -ERRNO on error.
 */
int cri_mcall_obliterate_root(int index);

/**
 * @brief Call when supervisor exits.
 *
 * Call when supervisor exits due to a trap in essential thread
 * or when HLOS tells it to exit.
 *
 * @param major Reason for exit.
 * @param minor Lower level reason.
 * @param reboot True to reboot, false to halt.
 * @return Does not return.
 */
int cri_mcall_exit(int major, int minor, bool reboot);

/**
 * @brief Store "IPC" message.
 *
 * @param range Container ID range of recipient.
 * @param buf Pointer to message buffer.
 * @param size Size of the message.
 * @param scid SCID of the sender.
 * @return Zero on success, -ERRNO on error.
 */
int cri_mcall_send_message(const cri_container_range_t *range,
			   const u8_t *buf,
			   size_t size,
			   const cri_container_scid_t *scid);

/**
 * @brief Retrieve "IPC" message.
 *
 * @param sender Container ID for the message sender.
 * @param buf Pointer to buffer for the message.
 * @param size Size of the buffer.
 * @param scid SCID of the retriever.
 * @return Size of the message on success, -ERRNO on error.
 */
int cri_mcall_receive_message(const cri_container_scid_t *sender,
			      u8_t *buf, size_t size,
			      const cri_container_scid_t *scid);

/**
 * @brief Clear stored "IPC" message.
 * @return 0 always.
 */
int cri_mcall_clear_message(void);

/**
 * @brief Perform a soft reset - clear supervisor .bss and .noinit sections,
 * and restart supervisor.
 *
 * @return Does not return on success, -ERRNO on error.
 */
int cri_mcall_soft_reset(void);

/**
 * @brief Disable KDC
 *
 * @param disable Disable KDC if non-zero; do noting if zero.
 * @return Zero if KDC is enabled, 1 if KDC is disabled.
 */
int cri_mcall_disable_kdc(int disable);

/**
 * @brief Set SAC segment configuration.
 *
 * @param index Segment index
 * @param value Segment value
 * @return Zero on success, -ERRNO on error.
 */
int cri_mcall_sac_segment_config(u32_t index, u32_t value);

/**
 * @brief Get or set minimum image version in OTP.
 *
 * At boot image footer versions are checked against values in OTP.
 * Value in the image footer must be equal or greater than the value in OTP.
 *
 * @param image Image identifier
 * @param version Pointer to the version value
 * @param size Version value size
 * @return Zero on success, -ERRNO on error.
 */
int cri_mcall_get_img_version(enum cri_image_version_id image, void *version, size_t *size);
int cri_mcall_set_img_version(enum cri_image_version_id image, const void *version, size_t size);

/**
 * @brief Get next image location.
 *
 * The image bundle loaded at boot may have other images than just the
 * supervisor. This function returns the offset to the next image that
 * was not consumed at boot.
 *
 * @param location Pointer to returned location value.
 * @param flags flags, must be 0
 * @return Zero on success, -ERRNO on error.
 */
int cri_mcall_img_location(u32_t *location, u32_t flags);

#endif /* FBOOT_SMCALLS_H */
