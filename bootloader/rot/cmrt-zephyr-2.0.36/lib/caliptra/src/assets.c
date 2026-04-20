/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <cmrt/ucu/span.h>
#include <drivers/cmrt/cmrt.h>
#include <cmrt/fboot/img_format.h>
#include <drivers/cmrt/omc.h>

#include <cmrt/caliptra/types.h>
#include <cmrt/caliptra/assets.h>
#include "internal.h"

/* Asset layout in OTP. */
typedef struct cmrt_caliptra_otp_assets {
	/* Obfuscated UDS seed. */
	uint8_t uds_seed[CMRT_CALIPTRA_UDS_LEN];
	/* Obfuscated field entropy slots. */
	uint8_t field_entropy[CMRT_CALIPTRA_FIELD_ENTROPY_SLOTS][CMRT_CALIPTRA_FIELD_ENTROPY_LEN];
	/* The true length of the cert chain. */
	uint32_t idevid_cert_chain_size;
	/* Stored as full 32-bit words. */
	uint8_t idevid_cert_chain[CMRT_CALIPTRA_IDEVID_CHAIN_MAX_LEN];
} cmrt_caliptra_otp_assets_t;

#define asset_size(name) sizeof(((cmrt_caliptra_otp_assets_t *)0)->name)
#define asset_offset(name) (uint32_t)(&(((cmrt_caliptra_otp_assets_t *)0)->name))

static int calc_otp_esw_area_offset(cmrt_caliptra_oam_t oam)
{
	int res = 0;
	size_t off = OTP_ESW_OFFSET;

#ifndef CONFIG_CMRT_SBOOT_IN_ROM
	cmrt_img_header_t sboot_header;
	res = cmrt_omc_read(oam->omc, off, &sboot_header, sizeof(sboot_header));
	if (res == 0) {
		if (sboot_header.length == ~sboot_header.mirror) {
			/* We have an sboot in OTP. */
			off += sizeof(sboot_header) + sboot_header.length;
		} else {
			/* Wrong sboot header. */
			res = -ENOSPC;
		}
	}
#endif
	if (res == 0) {
		oam->caliptra_offset = off;
	}
	return res;
}

int cmrt_caliptra_oam_open(cmrt_caliptra_oam_t oam)
{
	int res = -EIO;
	oam->omc = cmrt_omc_open(CMRT_O_SYNC);
	if (cmrt_is_valid(oam->omc)) {
		res = 0;
	}
	return res;
}

int cmrt_caliptra_oam_init(cmrt_caliptra_oam_t oam, size_t offset)
{
	int res = -EIO;
	if (cmrt_is_valid(oam->omc)) {
		if (offset == 0) {
			/* Determine offset automatically. */
			res = calc_otp_esw_area_offset(oam);
		} else {
			oam->caliptra_offset = offset;
			res = 0;
		}
	}
	return res;
}

void cmrt_caliptra_oam_close(cmrt_caliptra_oam_t oam)
{
	cmrt_omc_close(oam->omc);
}

static int oam_read(cmrt_caliptra_oam_t oam, size_t aoffset, size_t asize, span out)
{
	if (!span_valid(out)) {
		return -EINVAL;
	}
	if (out.n < asize) {
		return -ENOBUFS;
	}
	return cmrt_omc_read(oam->omc, oam->caliptra_offset + aoffset, (void *)out.p, asize);
}
#define OAM_READ_FIELD(oam, name, out) oam_read(oam, asset_offset(name), asset_size(name), out)

static int oam_write(cmrt_caliptra_oam_t oam, size_t aoffset, size_t asize, const span data)
{
	if (!span_valid(data)) {
		return -EINVAL;
	}
	if (data.n != asize) {
		return -EINVAL;
	}
	return cmrt_omc_write(oam->omc, oam->caliptra_offset + aoffset, (void *)data.p, asize);
}
#define OAM_WRITE_FIELD(oam, name, data) oam_write(oam, asset_offset(name), asset_size(name), data)

int cmrt_caliptra_oam_read_uds_seed(cmrt_caliptra_oam_t oam, cmrt_caliptra_uds_t *out)
{
	return OAM_READ_FIELD(oam, uds_seed, SPAN(*out));
}

int cmrt_caliptra_oam_read_field_entropy(cmrt_caliptra_oam_t oam, cmrt_caliptra_field_entropy_t *out, int *slot_index)
{
	/* Look for the last non-zero entropy slot. */
	if (slot_index == NULL) {
		return -EINVAL;
	}
	int res = 0;
	int i;
	for (i = CMRT_CALIPTRA_FIELD_ENTROPY_SLOTS - 1; i >= 0; --i) {
		res = OAM_READ_FIELD(oam, field_entropy[i], SPAN(*out));
		if ((res == 0) && !allzero(SPAN(*out))) {
			break;
		}
	}
	if (i < 0) {
		res = -ENOENT;
	} else {
		*slot_index = i;
	}
	return res;
}

int cmrt_caliptra_oam_read_idevid_cert_chain(cmrt_caliptra_oam_t oam, void *out, size_t *out_len)
{
	if (out_len == NULL) {
		return -EINVAL;
	}
	size_t len;
	int res = OAM_READ_FIELD(oam, idevid_cert_chain_size, SPAN(len));
	if (res == 0) {
		/* Stored in OTP as whole 32-bit words.  */
		size_t wlen = ROUND_UP(len, 4);
		if (*out_len < wlen) {
			return -ENOBUFS;
		}
		*out_len = len;
		res = oam_read(oam, asset_offset(idevid_cert_chain), wlen, span_from(out, wlen));
	}
	return res;
}

int cmrt_caliptra_oam_write_uds_seed(cmrt_caliptra_oam_t oam, const cmrt_caliptra_uds_t *data)
{
	alignas(4) uint8_t seed[asset_size(uds_seed)];
	int res = OAM_READ_FIELD(oam, uds_seed, SPAN(seed));
	if (res == 0) {
		if (allzero(SPAN(seed))) {
			res = OAM_WRITE_FIELD(oam, uds_seed, SPAN(*data));
		} else {
			/* UDS seed has been already written. */
			res = -ENOSPC;
		}
	}
	zeroize(SPAN(seed));
	return res;
}

int cmrt_caliptra_oam_write_field_entropy(cmrt_caliptra_oam_t oam, const cmrt_caliptra_field_entropy_t *data)
{
	/* Find the next empty slot. */
	alignas(4) uint8_t ent[asset_size(field_entropy[0])];
	unsigned int i;
	int res = 0;
	for (i = 0; i < CMRT_CALIPTRA_FIELD_ENTROPY_SLOTS; ++i) {
		res = OAM_READ_FIELD(oam, field_entropy[i], SPAN(ent));
		if (res != 0 || allzero(SPAN(ent))) {
			break;
		}
	}
	if ((res == 0) && (i < CMRT_CALIPTRA_FIELD_ENTROPY_SLOTS)) {
		res = OAM_WRITE_FIELD(oam, field_entropy[i], SPAN(*data));
	} else {
		/* No free field entropy slots. */
		res = -ENOSPC;
	}
	zeroize(SPAN(ent));
	return res;
}

int cmrt_caliptra_oam_write_idevid_cert_chain(cmrt_caliptra_oam_t oam, const void *data, size_t data_len)
{
	if (data == NULL) {
		return -EINVAL;
	}
	if (data_len > CMRT_CALIPTRA_IDEVID_CHAIN_MAX_LEN) {
		return -EINVAL;
	}
	size_t cur_len;
	int res = OAM_READ_FIELD(oam, idevid_cert_chain_size, SPAN(cur_len));
	if ((res != 0) || (cur_len != 0u)) {
		/* Cert chain has been already written. */
		return -ENOSPC;
	}
	/* Write actual size of data. */
	res = OAM_WRITE_FIELD(oam, idevid_cert_chain_size, SPAN(data_len));
	if (res == 0) {
		/* Write whole words. */
		size_t size = (data_len + 3) & ~3;
		res = oam_write(oam, asset_offset(idevid_cert_chain), size,
				span_from(data, size));
	}
	return res;
}
