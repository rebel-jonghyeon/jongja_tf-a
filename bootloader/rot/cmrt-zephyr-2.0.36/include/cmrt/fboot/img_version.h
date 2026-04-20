/*
 * Copyright (c) 2021-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file img_version.h
 *
 * @brief Define CMRT image versions ids.
 */

#ifndef CMRT_IMG_VERSION_H
#define CMRT_IMG_VERSION_H

#include <drivers/cmrt/otp_off.h>

enum cmrt_image_version_id {
	CMRT_FBOOT_IMAGE_VERSION = 0x10001,
	CMRT_SBOOT_IMAGE_VERSION = 0x10002,
	CMRT_TBOOT_IMAGE_VERSION = 0x10003,
	CMRT_SUPERVISOR_IMAGE_VERSION = 0x10004,
};

enum cmrt_enforced_version_id {
	CMRT_MACHINE_ENFORCED_VERSION = OTP_MACHINE_VERSION_OFFSET,
	CMRT_SUPERVISOR_ENFORCED_VERSION = OTP_SUPERVISOR_VERSION_OFFSET,
	CMRT_USER_ENFORCED_VERSION = OTP_USER_VERSION_OFFSET,
};

#endif
/** @}*/
