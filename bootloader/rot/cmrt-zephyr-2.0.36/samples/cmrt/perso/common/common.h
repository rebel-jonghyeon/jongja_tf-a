/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */

#ifndef CMRT_PERSO_COMMON_H
#define CMRT_PERSO_COMMON_H

#include <stdint.h>
#include <drivers/cmrt/omc.h>

/**
 * Typically an element of an array passed to @ref cmrt_perso_create_roots.
 */
struct cmrt_perso_root {
	cmrt_omc_root_t *root; /* OTP root, to be created. */
	const char type[16]; /* String to be printed to logs. */
};

/**
 * Write device ID OTP slot
 *
 * Device ID is read from SIC.CUSTOMx registers, if it is zero then random
 * device ID is generated using TMC.
 *
 * @return Error number of error, otherwise zero.
 * */
int cmrt_perso_burn_device_id(void);

/**
 * Write OEM ID OTP slot
 *
 * @param[in] oem_id Pointer to OEM ID data.
 * @param size Size of OEM ID data (bytes).
 * @return Error number on error, otherwise zero.
 */
int cmrt_perso_burn_oem_id(const uint32_t *oem_id, size_t size);

/**
 * Write sboot image to OTP
 *
 * Sboot image is placed after OTP reserved words, if those are configured to be
 * before sboot image, otherwise at start of OTP ESW region.
 *
 * @param[in] img_data Pointer to sboot image.
 * @param size Size of sboot image (bytes).
 * @return Error number on error, otherwise zero.
 */
int cmrt_perso_burn_sboot(const void *img_data, size_t size);

/**
 * Create OTP roots
 *
 * Create OTP described by @p roots. @p '.name' is printed to log.
 *
 * @param[in] roots Pointer to array of struct @ref cmrt_perso_root elements.
 *                  Terminated with an element having NULL '.root' member.
 * @return Error number on error, otherwise zero.
 */
int cmrt_perso_create_roots(struct cmrt_perso_root *roots);

/**
 * Write OTP keysplit slot.
 *
 * @param index OTP Keysplit slot number (0 - CMRT_OTP_NUM_KEYSPLIT-1).
 * @param keysplit Pointer to keysplit data.
 * @return Error number on error, otherwise zero.
 */
int cmrt_perso_write_otp_keysplit(int index, const cmrt_omc_key_split_t *keysplit);
#endif /* CMRT_PERSO_COMMON_H */
