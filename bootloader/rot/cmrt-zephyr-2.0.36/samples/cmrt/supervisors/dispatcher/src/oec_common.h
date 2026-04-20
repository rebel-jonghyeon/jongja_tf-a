/*
 * Copyright (c) 2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#ifndef OEC_COMMON_H
#define OEC_COMMON_H


#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <cri/cmrt/aes.h>
#include <cri/cmrt/omc.h>

#ifdef __cplusplus
extern "C" {
#endif


/*!
 * Transfer OEC key to AES.  The current IV from OEC is used when
 * encrypting and returned in iv.  When decrypting, iv an input used
 * for the aes, on encryption, it is actually an output buffer.
 * @param keynr keysplit index to use (0)
 * @param op operation (CRI_AES_ENCRYPT or CRI_AES_DECRYPT.)
 * @param[out] iv buffer for the initialization vector (16 bytes)
 */
cri_aes_t oec_derive(uint8_t keynr, cri_aes_operation_t op, uint32_t *iv);


/*!
 * In-place decrypt the image in \a image.  Image is started with 16
 * bytes of initialization vector (only 12 bytes used), and ends with
 * 16 bytes tag.
 * @note regardless of success, the image is corrupted
 * @param[in,out] image image data buffer
 * @param imlen length of \a image in bytes
 * @param keynr number to use
 */
int oec_image_decrypt(void *image, size_t imlen, uint8_t keynr);


/*!
 * Inplace encrypt the image.
 */
int oec_image_encrypt(void *image, size_t imlen, uint8_t keynr);


/*!
 * Update OTP emulation images.
 * @param image image
 * @param which bitmap of images to update
 */
int oec_image_update(const void *image, size_t imlen, unsigned int which);


#ifdef __cplusplus
}
#endif


#endif
