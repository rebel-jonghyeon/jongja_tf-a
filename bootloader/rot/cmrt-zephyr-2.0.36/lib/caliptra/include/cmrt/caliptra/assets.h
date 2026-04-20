/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#ifndef CMRT_CALIPTRA_SRC_ASSETS_H
#define CMRT_CALIPTRA_SRC_ASSETS_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <cmrt/ucu/span.h>
#include <drivers/cmrt/omc.h>

#include <cmrt/caliptra/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Caliptra OTP Asset Manager */
typedef struct cmrt_caliptra_oam {
	cmrt_omc_t omc;
	/* offset of Caliptra assets in OTP */
	size_t caliptra_offset;
} cmrt_caliptra_oam_t[1];

/**
 * Open an asset manager instance.
 *
 * Reserves the required hardware resources, which can be later
 * released with cmrt_caliptra_oam_close() and then re-acquired again
 * with this function.
 *
 * @param oam the asset manager instance
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_oam_open(cmrt_caliptra_oam_t oam);

/**
 * Initialize an asset manager instance.
 *
 * Determines (or specifies) the location of Caliptra assets in OTP.
 * The asset manager must be opened before calling this function.
 *
 * @param oam the asset manager instance
 * @param offset OTP offset of Caliptra assets (e.g. after sboot).
 * Specify 0 to determine automatically.
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_oam_init(cmrt_caliptra_oam_t oam, size_t offset);

/**
 * Shut down the asset manager.
 *
 * @param oam the asset manager instance
 */
void cmrt_caliptra_oam_close(cmrt_caliptra_oam_t oam);

/**
 * Read the Caliptra UDS seed.
 *
 * @param oam the asset manager instance
 * @param out location for the UDS seed
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_oam_read_uds_seed(cmrt_caliptra_oam_t oam, cmrt_caliptra_uds_t *out);

/**
 * Read the current Caliptra field entropy.
 *
 * The function returns the field entropy in the last non-empty slot.
 *
 * @param oam the asset manager instance
 * @param out location for the (obfuscated) field entropy
 * @param slot_index location for the slot index of the current field entropy
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_oam_read_field_entropy(cmrt_caliptra_oam_t oam, cmrt_caliptra_field_entropy_t *out, int *slot_index);

/**
 * Read the Caliptra IDevID certificate chain.
 *
 * @param oam the asset manager instance
 * @param out location for the certificate chain
 * @param[inout] out_len available space in the @a out buffer. Must be
 * a multiple of 4. On return it contains the true length of the
 * chain.
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_oam_read_idevid_cert_chain(cmrt_caliptra_oam_t oam, void *out, size_t *out_len);

/**
 * Write the Caliptra UDS seed.
 *
 * An error is returned if the UDS seed has already been provisioned.
 *
 * @param oam the asset manager instance
 * @param data the UDS seed
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_oam_write_uds_seed(cmrt_caliptra_oam_t oam, const cmrt_caliptra_uds_t *data);

/**
 * Update the Caliptra field entropy.
 *
 * The entropy is written to the next empy slot. An error is returned
 * if no slots are available.
 *
 * @param oam the asset manager instance
 * @param data the (obfuscated) entropy data
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_oam_write_field_entropy(cmrt_caliptra_oam_t oam, const cmrt_caliptra_field_entropy_t *data);

/**
 * Write the Caliptra IDevID certificate chain.
 *
 * The cert chain always occupies a number of full words (32-bit) in
 * OTP. The contents are not interpreted by CMRT.
 *
 * @param oam the asset manager instance
 * @param data the certificate chain. At least @a ROUND_UP(data_len, 4)
 * bytes must be accessible.
 * @param data_len true length of the certificate @a data.
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_oam_write_idevid_cert_chain(cmrt_caliptra_oam_t oam, const void *data, size_t data_len);

#ifdef __cplusplus
}
#endif
#endif
