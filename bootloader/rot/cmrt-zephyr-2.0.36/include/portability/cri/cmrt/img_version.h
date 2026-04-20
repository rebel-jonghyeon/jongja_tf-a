/*
 * Copyright (c) 2021-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file img_version.h
 *
 * @brief Define CMRT image versions ids.
 */

#ifndef CRI_IMG_VERSION_H
#define CRI_IMG_VERSION_H

/* Image ids for version checking and for cri_mcall_img_version(). */
enum cri_image_version_id {
	CMRT_TBOOT_IMG_OTP = 0, /* OTP_TBOOT_VERSION_WORD_OFFSET */
	CMRT_SUPERVISOR_IMG_OTP = 4, /* OTP_SUPERVISOR_VERSION_WORD_OFFSET */
	CMRT_FBOOT_VERSION = 0x10001,
	CMRT_SBOOT_VERSION = 0x10002,
	CMRT_SUPERVISOR_VERSION = 0x10003
};

#endif
/** @}*/
