/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file xmss.h
 *
 * @brief XMSS and XMSS-MT APIs.
 */

#ifndef CMRT_SHSIG_XMSS_INT_H
#define CMRT_SHSIG_XMSS_INT_H

#include <stdint.h>
#include <stddef.h>
#include <drivers/cmrt/hc.h>

#include <cmrt/shsig/xmss.h>

/**
 * @brief XMSS and XMSS-MT internal definitions
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*hash_f)(cmrt_hc_t hc, void *dig, const void *key, const void *msg);
typedef void (*hash_msg_f)(cmrt_hc_t hc, void *dig, const void *r, const void *root, uint64_t idx, const void *msg, uint32_t mlen);

typedef struct {
	cmrt_xmss_ots_type type;
	int n;
	int w;
	int len;
	int len_1;
	int len_2;

	hash_f f;
	hash_f prf;
	hash_f h;
	hash_msg_f h_msg;
} cmrt_xmss_ots_param_t;

/**
 * @brief Load XMSS OTS parameters.
 *
 * @param otstype Predefined hashing schema type cmrt_xmss_ots_type.
 *
 * @return Valid pointer to XMSS OTS parameters on success, NULL on error.
 */
const cmrt_xmss_ots_param_t *cmrt_xmss_load_ots_parm(cmrt_xmss_ots_type otstype);

/**
 * @brief Verify XMSS message.
 *
 * @param hc open hash core handle.
 * @param pk Pointer to a constant buffer that contains the public key for
 *           the XMSS operation.
 * @param msg Pointer to a constant buffer that contains the message.
 * @param mlen A size_t value that specifies the length of the message.
 * @param height Height of a tree within the multi-tree.
 * @param layer
 * @param param Hashing algorithm parameters.
 * @param sm Pointer to a constant buffer that contains the signature.
 * @param wdt_feed watchdog feeding function or NULL
 *
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_xmss_verify_internal(cmrt_hc_t hc, const uint8_t *pk, const uint8_t *msg,
			      size_t mlen, uint32_t height, uint32_t layer,
			      const cmrt_xmss_ots_param_t *parm, const uint8_t *sm,
			      wdt_feed_func *wdt_feed);
#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
