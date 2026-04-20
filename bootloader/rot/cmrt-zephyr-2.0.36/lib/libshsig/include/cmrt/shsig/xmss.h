/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file xmss.h
 *
 * @brief XMSS and XMSS-MT APIs.
 */

#ifndef CMRT_SHSIG_XMSS_H
#define CMRT_SHSIG_XMSS_H

#include <stdint.h>
#include <stddef.h>
#include <drivers/cmrt/hc.h>

/**
 * @brief XMSS and XMSS-MT Interface
 * @defgroup xmss_interface XMSS and XMSS-MT Interface
 * @ingroup xmss_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	WOTSP_RESERVED = 0,
	WOTSP_SHA2_256,
	WOTSP_SHA2_512,
	WOTSP_SHAKE_256,
	WOTSP_SHAKE_512,
} cmrt_xmss_ots_type;

typedef enum {
	XMSS_RESERVED        = 0x00000000,
	XMSS_SHA2_10_256     = 0x00000001,
	XMSS_SHA2_16_256     = 0x00000002,
	XMSS_SHA2_20_256     = 0x00000003,
	XMSS_SHA2_10_512     = 0x00000004,
	XMSS_SHA2_16_512     = 0x00000005,
	XMSS_SHA2_20_512     = 0x00000006,
	XMSS_SHAKE_10_256    = 0x00000007,
	XMSS_SHAKE_16_256    = 0x00000008,
	XMSS_SHAKE_20_256    = 0x00000009,
	XMSS_SHAKE_10_512    = 0x0000000A,
	XMSS_SHAKE_16_512    = 0x0000000B,
	XMSS_SHAKE_20_512    = 0x0000000C,
} cmrt_xmss_algorithm_type;

typedef struct {
	uint32_t atype; /* cmrt_xmss_algorithm_type or cmrt_xmss_mt_algorithm_type */
	uint32_t otstype; /* cmrt_xmss_ots_param_t type of OTS. */
	uint32_t layer;  /* Tree layer. */
	uint32_t height; /* Tree heigth. */
	uint32_t hsize;  /* Hash size in bytes. */
} cmrt_xmss_param_t;


/**
 * @brief Read XMSS OID from public key.
 *
 * @param pk Public key.
 *
 * @return Valid cmrt_xmss_algorithm_type,
 *         XMSS_RESERVED on error or not supported OID.
 */
cmrt_xmss_algorithm_type cmrt_xmss_get_type(const uint8_t *pk);

/**
 * @brief Get CMRT hash type from XMSS OID.
 *
 * @param xmss_type cmrt_xmss_algorithm_type.
 *
 * @return valid cmrt_hash_algo_t, in case of wrong xmss_type
 *         defaults to CMRT_HASH_SHAKE256.
 */
cmrt_hash_algo_t cmrt_xmss_get_hash_algo(cmrt_xmss_algorithm_type xmss_type);

/**
 * @brief Load XMSS parameters.
 *
 * @param atype Predefined hashing schema type cmrt_xmss_algorithm_type.
 *
 * @return Valid pointer to XMSS parameters on success, NULL on error.
 */
const cmrt_xmss_param_t *cmrt_xmss_load_param(cmrt_xmss_algorithm_type atype);

typedef void (wdt_feed_func)(void);

/**
 * @brief Verify XMSS message.
 *
 * @param hc open hash core handle.
 * @param pk Pointer to a constant buffer that contains the public key for
 *           the XMSS operation.
 * @param digest Pointer to a constant buffer that contains the digest.
 * @param dlen A size_t value that specifies the length of the digest.
 * @param sm Pointer to a constant buffer that contains the signature.
 * @param wdt_feed watchdog feeding function or NULL
 *
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_xmss_verify(cmrt_hc_t hc, const uint8_t *pk, const uint8_t *digest,
		     size_t dlen, const uint8_t *sm, wdt_feed_func *wdt_feed);
#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
