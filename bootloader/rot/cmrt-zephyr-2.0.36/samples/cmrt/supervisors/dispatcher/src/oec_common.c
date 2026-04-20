/*
 * Copyright (c) 2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */


#include "oec_common.h"
#include "common.h"
#include <string.h>
#include <cri/cmrt.h>
#include <cri/cmrt/axi_flash.h>


/* This image must have a 12/16 byte iv at the front, which is not touched.
 */
int oec_image_decrypt(void *image, size_t imlen, uint8_t keynr)
{
	int res = -1;
	size_t taglen = 16;

	if (imlen < 16 + taglen)
		return res;

	cri_aes_t aes = oec_derive(keynr, CRI_AES_DECRYPT, image);

	if (cri_is_valid(aes)) {
		uint32_t tag[4];
		size_t taglen = 16;
		char *p = image;
		p += 16;
		imlen = imlen - 16 - taglen;
		memcpy(tag, p + imlen, taglen);
		res = cri_aes_ae_final(aes, p, imlen, p, p + imlen, &taglen);
		if (res >= 0) {
			if (taglen != sizeof(tag)) {
				res = -3;
			} else if (memcmp(tag, p + imlen, sizeof(tag)) != 0) {
				res = -4;
			} else {
				res = imlen;
			}
		}
		cri_aes_close(aes);
	}

	return res;
}


static size_t flash_page_size(off_t off) { return 4096; }
static bool flash_page_aligned(off_t off) { return (off & 4095u) == 0u; };

/*!
 * Update the flash area; for each page to touch;
 * - erase the page
 * - write the page
 * - if partial, only touch overwritten data
 * @pre flash is opened
 */
int flash_update(struct device *flash, off_t offset,
		 const void *data, size_t ndata)
{
	int res = 0;
	while (ndata != 0) {
		enum { page_size = 4096 };
		char buffer[page_size];
		(void)flash_page_size;
		const void *pwrite = data;
		off_t woff = offset & ~(page_size - 1);
		size_t nw = page_size;
		if (!flash_page_aligned(offset) || (ndata < page_size)) {
			size_t boff = offset & (page_size - 1);
			size_t toend = page_size - boff;
			nw = (ndata < toend) ? ndata : toend;
			flash_read(flash, offset - boff, buffer, page_size);
			memcpy(buffer + boff, data, nw);
			pwrite = buffer;
		}
		/* if either erase of write fails, bail out. */
		if (flash_erase(flash, woff, page_size) < 0) {
			return -1;
		}
		if (flash_write(flash, woff, pwrite, page_size) < 0) {
			return -1;
		}

		offset += nw;
		ndata -= nw;
	}
	return res;
}

/* This is really useless as the IV is not there.  The data can only
 * be updated externally by specifying the exact IV we need.
 */
int oec_image_update(const void *image, size_t imlen, unsigned int which)
{
	enum {
		k_main_offset = 0x400000,
		k_backup_offset = 0x401000
	};
	int res = 0;
	cri_otp_t oec = cri_otp_open(0);
	if (cri_is_valid(oec)) {
		/* the otp is locked, we will update the image
		 */
		struct device *flash =
			device_get_binding(DT_FLASH_DEV_NAME);
		if (flash && flash_open(flash) >= 0) {
			flash_write_protection_set(flash, false);
			if (which & 1u) {
				if (flash_update(flash, k_main_offset,
						 image, imlen) >= 0) {
					res |= 1u;
				}
			}
			if (which & 2u) {
				if (flash_update(flash, k_backup_offset,
						 image, imlen) >= 0) {
					res |= 2u;
				}
			}
			flash_write_protection_set(flash, true);
			flash_close(flash);
		}
		cri_otp_close(oec);
	}
	return res;
}

static void readiv(uint32_t *iv)
{
	for (uint32_t i = 0; i < 4; ++i) {
		iv[i] = sys_read32(CMRT_OEC_BASE + R_OEC_IV_OUTPUT + 4*i);
	}
}

cri_aes_t oec_derive(uint8_t keynr, cri_aes_operation_t op, uint32_t *iv)
{
	cri_aes_t aes = CRI_INVALID_HANDLE;

	cri_otp_t oec = cri_otp_open(CRI_O_OTP_COMMIT);
	if (cri_is_valid(oec)) {
		aes = cri_otp_oec_derive(oec, op, keynr);
		if (iv != NULL) {
			if (op == CRI_AES_ENCRYPT) {
				readiv(iv);
			} else {
				if (cri_aes_init(aes, CRI_AES_DECRYPT, CRI_AES_GCM, NULL, 0, iv, 12, 16) < 0) {
					cri_aes_close(aes);
					aes = CRI_INVALID_HANDLE;
				}
			}
		}
	}
	cri_otp_close(oec);

	return aes;
}

/*!
 * Do an in-place image encryption of the data with the otp.
 * @param[in, out] image updated image buffer with tag added on
 * @note aes will require a word-padded input
 * @param imlen image length in bytes
 * @param key the key to use
 */
int oec_image_encrypt(void *image, size_t imlen, uint8_t keynr)
{
	int res = -1;
	uint32_t iv[4];
	cri_aes_t aes = oec_derive(keynr, CRI_AES_ENCRYPT, iv);

	if (cri_is_valid(aes)) {
		uint32_t tag[4];
		size_t taglen = sizeof(tag);
		res = cri_aes_ae_final(aes, image, imlen, image, tag, &taglen);
		if (res >= 0) {
			char *p = image;
			memmove(p + 16, p, imlen);
			memcpy(p, iv, 16);
			memcpy(p + 16 + imlen, tag, taglen);
			res = imlen + 16 + taglen;
		}
		cri_aes_close(aes);
	}

	return res;
}
