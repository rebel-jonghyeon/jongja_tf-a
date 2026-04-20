/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file lms.h
 *
 * @brief LMS and LMS-HSS APIs.
 */

#ifndef CMRT_SHSIG_LMS_H
#define CMRT_SHSIG_LMS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <drivers/cmrt/hc.h>
#include <cmrt/shsig/lms_ots.h>

/**
 * @brief LMS and LMS-HSS Interface
 * @defgroup lms_interface LMS and LMS-HSS Interface
 * @ingroup lms_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	LMS_RESERVED       = 0,
	LMS_SHA256_N32_H5  = 5,
	LMS_SHA256_N32_H10 = 6,
	LMS_SHA256_N32_H15 = 7,
	LMS_SHA256_N32_H20 = 8,
	LMS_SHA256_N32_H25 = 9
} cmrt_lms_algorithm_type;

/* q || ots_sig || type || path x h */
#define LMS_SIG_LEN(p, h) (4u + LMS_OTS_SIG_LEN(p) + 4u + 32u * (h))

/* type || otstype || I || root_hash */
#define LMS_PK_LEN (4u + 4u + 16u + 32u)

/* level || LMS_PK */
#define LMS_HSS_PK_LEN (LMS_PK_LEN + 4u)

/**
 * @brief Read LMS OID from public key.
 *
 * @param pk Public key.
 * @param is_hss Public key is LMS-HSS type.
 *
 * @note:
 *        LMS public key has following format:
 *        pk = type || otstype || I || root_hash
 *        LMS-HSS public key has following format:
 *        pk = level || type || otstype || I || root_hash
 *
 * @return Valid cmrt_lms_algorithm_type,
 *         LMS_RESERVED on error or not supported OID.
 */
cmrt_lms_algorithm_type cmrt_lms_get_type(const uint8_t *pk, bool is_hss);
/**
 * @brief Verify LMS message.
 *
 * @param hc First open hash core handle.
 * @param pk Pointer to a constant buffer that contains the public key for
 *           the LMS operation.
 * @param msg Pointer to a constant buffer that contains the message.
 * @param mlen A size_t value that specifies the length of the message.
 * @param sig Pointer to a constant buffer that contains the signature.
 *
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_lms_verify(cmrt_hc_t hc, const uint8_t *pk, const uint8_t *msg,
		    size_t mlen, const uint8_t *sig);

/**
 * @brief Verify LMS-HSS message.
 *
 * @param hc First open hash core handle.
 * @param pk Pointer to a constant buffer that contains the public key for
 *           the LMS-HSS operation.
 * @param msg Pointer to a constant buffer that contains the message.
 * @param mlen A size_t value that specifies the length of the message.
 * @param sig Pointer to a constant buffer that contains the signature.
 *
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_lms_hss_verify(cmrt_hc_t hc, const uint8_t *pk, const uint8_t *msg,
			size_t mlen, const uint8_t *sig);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
