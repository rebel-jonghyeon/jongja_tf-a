/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file xmss.h
 *
 * @brief XMSS and XMSS-MT APIs.
 */

#ifndef CMRT_SHSIG_XMSS_MT_H
#define CMRT_SHSIG_XMSS_MT_H

#include <stdint.h>
#include <stddef.h>
#include <drivers/cmrt/hc.h>

/**
 * @brief XMSS-MT Interface
 * @defgroup xmss_mt_interface XMSS-MT Interface
 * @ingroup xmss_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	XMSS_MT_RESERVED           = 0x00000000,
	XMSS_MT_SHA2_20_2_256      = 0x00000001,
	XMSS_MT_SHA2_20_4_256      = 0x00000002,
	XMSS_MT_SHA2_40_2_256      = 0x00000003,
	XMSS_MT_SHA2_40_4_256      = 0x00000004,
	XMSS_MT_SHA2_40_8_256      = 0x00000005,
	XMSS_MT_SHA2_60_3_256      = 0x00000006,
	XMSS_MT_SHA2_60_6_256      = 0x00000007,
	XMSS_MT_SHA2_60_12_256     = 0x00000008,
	XMSS_MT_SHA2_20_2_512      = 0x00000009,
	XMSS_MT_SHA2_20_4_512      = 0x0000000A,
	XMSS_MT_SHA2_40_2_512      = 0x0000000B,
	XMSS_MT_SHA2_40_4_512      = 0x0000000C,
	XMSS_MT_SHA2_40_8_512      = 0x0000000D,
	XMSS_MT_SHA2_60_3_512      = 0x0000000E,
	XMSS_MT_SHA2_60_6_512      = 0x0000000F,
	XMSS_MT_SHA2_60_12_512     = 0x00000010,
	XMSS_MT_SHAKE_20_2_256     = 0x00000011,
	XMSS_MT_SHAKE_20_4_256     = 0x00000012,
	XMSS_MT_SHAKE_40_2_256     = 0x00000013,
	XMSS_MT_SHAKE_40_4_256     = 0x00000014,
	XMSS_MT_SHAKE_40_8_256     = 0x00000015,
	XMSS_MT_SHAKE_60_3_256     = 0x00000016,
	XMSS_MT_SHAKE_60_6_256     = 0x00000017,
	XMSS_MT_SHAKE_60_12_256    = 0x00000018,
	XMSS_MT_SHAKE_20_2_512     = 0x00000019,
	XMSS_MT_SHAKE_20_4_512     = 0x0000001A,
	XMSS_MT_SHAKE_40_2_512     = 0x0000001B,
	XMSS_MT_SHAKE_40_4_512     = 0x0000001C,
	XMSS_MT_SHAKE_40_8_512     = 0x0000001D,
	XMSS_MT_SHAKE_60_3_512     = 0x0000001E,
	XMSS_MT_SHAKE_60_6_512     = 0x0000001F,
	XMSS_MT_SHAKE_60_12_512    = 0x00000020
} cmrt_xmss_mt_algorithm_type;

/**
 * @brief Read XMSS-MT OID from public key.
 *
 * @param pk Public key.
 *
 * @return Valid cmrt_xmss_mt_algorithm_type,
 *         XMSS_RESERVED on error or not supported OID.
 */
cmrt_xmss_mt_algorithm_type cmrt_xmss_mt_get_type(const uint8_t *pk);

/**
 * @brief Get CMRT hash type from XMSS-MT OID.
 *
 * @param xmss_mt_type cmrt_xmss_mt_algorithm_type.
 *
 * @return valid cmrt_hash_algo_t, in case of wrong xmss_mt_type
 *         defaults to CMRT_HASH_SHAKE256.
 */
cmrt_hash_algo_t cmrt_xmss_mt_get_hash_algo(cmrt_xmss_mt_algorithm_type xmss_mt_type);

/**
 * @brief Load XMSS-MT parameters.
 *
 * @param atype Predefined hashing schema type cmrt_xmss_mt_algorithm_type.
 *
 * @return Valid pointer to XMSS parameters on success, NULL on error.
 */
const cmrt_xmss_param_t *cmrt_xmss_mt_load_param(cmrt_xmss_mt_algorithm_type atype);

/**
 * @brief Verify XMSS^MT message.
 *
 * @param hc open hash core handle.
 * @param pk Pointer to a constant buffer that contains the public key for
 *           the XMSS^MT operation.
 * @param digest Pointer to a constant buffer that contains the digest.
 * @param dlen A size_t value that specifies the length of the digest.
 * @param sm Pointer to a constant buffer that contains the signature.
 * @param wdt_feed watchdog feeding function or NULL
 *
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_xmss_mt_verify(cmrt_hc_t hc, const uint8_t *pk, const uint8_t *digest,
			size_t dlen, const uint8_t *sm, wdt_feed_func *wdt_feed);
#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
