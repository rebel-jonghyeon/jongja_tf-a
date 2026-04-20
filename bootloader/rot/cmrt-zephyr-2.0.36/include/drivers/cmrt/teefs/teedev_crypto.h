/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/** \addtogroup teefs_interface TEEFS Interface */
/*@{*/
#ifndef TEEDEV_CRYPTO_H
#define TEEDEV_CRYPTO_H

#include <drivers/cmrt/kdc.h>
#include <drivers/cmrt/aes.h>

/**
 * @brief Encrypt/Decrypt one page.
 *
 * Internal function for TEEDEV implementations to call.
 *
 * @param[in] key Pointer to the key of size KDC_KEY_SIZE.
 * @param[in] operation Currently AES_ENCRYPT or AES_DECRYPT.
 * @param[in] base TEEDEV base address.
 * @param[in] page Page number.
 * @param[in] src Source data.
 * @param[out] dst Destination data.
 * @param[in] len Data size.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int teedev_page_crypto(uint8_t *key, int operation, uint32_t base, uint32_t page, const void *src, void *dst, size_t len);

/**
 * @brief Derive key for the crypto operations.
 *
 * Internal function for TEEDEV implementations to call.
 *
 * @param[out] key Pointer to the key of size KDC_KEY_SIZE.
 * @param[in] path Pointer to the diversification path.
 * @param[in] pathlen Diversification path length of 1-16 bytes.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int teedev_derive_key(uint8_t *key, const uint8_t *path, size_t pathlen);

#include <syscalls/teedev_crypto.h>

#endif
