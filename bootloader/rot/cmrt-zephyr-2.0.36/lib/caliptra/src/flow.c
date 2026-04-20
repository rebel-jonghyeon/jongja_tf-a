/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/omc.h>
#include <cmrt/caliptra/types.h>
#include <cmrt/caliptra/flow.h>
#include <errno.h>

int cmrt_caliptra_get_deviceinfo(cmrt_caliptra_deviceinfo_t *info)
{
	int res = -EIO;
	if (info == NULL) {
		return -EINVAL;
	}
	cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC);
	if (cmrt_is_valid(omc)) {
		res = cmrt_omc_read(omc, OTP_DEVICE_ID_OFFSET,
				    info->device_id, sizeof(info->device_id));
		if (res == 0) {
			res = cmrt_omc_read(omc, OTP_OEM_ID_OFFSET,
					    info->oem_id, sizeof(info->oem_id));
		}
		cmrt_omc_close(omc);
	}
	return res;
}
