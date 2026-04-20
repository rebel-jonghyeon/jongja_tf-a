/*
 * Copyright (c) 2019-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */
/** \addtogroup teefs_interface TEEFS Interface */
/*@{*/

#ifndef TEEDEV_OTP_H
#define TEEDEV_OTP_H

#include <teedev.h>

/**
 * @brief Open OTP based device.
 *
 * Open flash device. Initializes given dev structure to implementation
 * specific functions. Resulting device can be used as a teefs device.
 *
 * @param[in] base Base address.
 * @param[in] blocks Number of fs blocks in log2.
 * @param[in] path Key derivation path or NULL for no encryption.
 * @param[in] pathlen Key derivation path length or 0 for no encryption.
 * @return Pointer to device on success, NULL on error.
 */
tee_device_t *teedev_otp_open(uint32_t *base, uint8_t blocks, const char *path, size_t pathlen);

/**
 * @brief Close OTP based device.
 *
 * Close device.
 *
 * @param[in] dev Pointer to device structure.
 */
void teedev_otp_close(tee_device_t *dev);

#endif
