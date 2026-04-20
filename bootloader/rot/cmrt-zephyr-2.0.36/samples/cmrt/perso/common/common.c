/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */

#include <zephyr.h>
#include <device.h>
#include <string.h>
#include <stdalign.h>
#include <assert.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/fboot.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/util.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#include "common.h"

int cmrt_perso_burn_device_id(void)
{
	int res;
	uint8_t device_id[OTP_DEVICE_ID_SIZE];

	/* Copy device_id from (first three) custom registers. */
	memcpy(device_id, (void *)(CMRT_SIC_BASE + R_CUSTOM_0), sizeof(device_id));
	uint8_t is_set_in_custom = 0;
	for (int i = 0; i < OTP_DEVICE_ID_SIZE; i++) {
		is_set_in_custom |= device_id[i];
	}
	if (is_set_in_custom == 0) {
		LOG_INF("Generating random device id");
		res = cmrt_get_random(device_id, OTP_DEVICE_ID_SIZE);
		if (res) {
			LOG_INF("Failed to generate random data: %d!", res);
			return res;
		}
	}
	cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(omc)) {
		LOG_INF("Failed to open omc!");
		return -ENODEV;
	}
	LOG_HEXDUMP_INF(device_id, sizeof(device_id), "Writing device id into OTP:");
	res = cmrt_omc_write(omc, OTP_DEVICE_ID_OFFSET, device_id, sizeof(device_id));
	if (res) LOG_INF("Failed to write device id: %d!", res);
	cmrt_omc_close(omc);

	return res;
}

int cmrt_perso_burn_oem_id(const uint32_t *oem_id, size_t size)
{
	if (size != 8) {
		LOG_INF("OEM ID is of wrong size");
		return -EINVAL;
	}
	cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(omc)) {
		LOG_INF("Failed to open omc!");
		return -ENODEV;
	}
	LOG_HEXDUMP_INF(oem_id, size, "Writing OEM ID into OTP:");
	int res = cmrt_omc_write(omc, OTP_OEM_ID_OFFSET, oem_id, size);
	if (res) LOG_INF("Failed to write OEM ID: %d!", res);
	cmrt_omc_close(omc);

	return res;
}

int cmrt_perso_write_otp_keysplit(int index, const cmrt_omc_key_split_t *keysplit)
{
	LOG_INF("Writing keysplit into index %d", index);

	cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(omc)) {
		LOG_INF("Failed to open omc!");
		return -ENODEV;
	}
	int res = cmrt_omc_write(omc, OTP_KEYSPLIT_OFFSET(index), keysplit, sizeof(*keysplit));
	if (res) LOG_INF("Failed to write keysplit into OTP: %d!", res);
	cmrt_omc_close(omc);

	return res;
}

int cmrt_perso_create_roots(struct cmrt_perso_root *roots)
{
	int res = 0;
	for (int i = 0; res == 0 && roots[i].root; i++) {
		LOG_INF("Writing %s root into index %d", roots[i].type, i);
		res = fboot_create_root(i, roots[i].root);
	}
	return res;
}

int cmrt_perso_burn_sboot(const void *img_data, size_t size)
{
	cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(omc)) {
		LOG_INF("Failed to open omc!");
		return -ENODEV;
	}
	uint32_t esw_start = cmrt_otp_esw_start();
	LOG_INF("Burning sboot to OTP offset %d with %d bytes",
		(int)esw_start, (int)size);
	int res = cmrt_omc_write(omc, esw_start, img_data, size);
	cmrt_omc_close(omc);
	return res;
}
