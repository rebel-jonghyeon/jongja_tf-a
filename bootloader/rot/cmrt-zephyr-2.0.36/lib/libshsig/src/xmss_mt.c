/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <errno.h>
#include <stdalign.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/byteorder.h>

#include <drivers/cmrt/hc.h>
#include <cmrt/shsig/xmss.h>
#include <cmrt/shsig/xmss_mt.h>
#include "xmss_int.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define ntohl(x) sys_be32_to_cpu(x)

cmrt_xmss_mt_algorithm_type cmrt_xmss_mt_get_type(const uint8_t *pk)
{
	if (pk != NULL) {
		uint32_t type = ntohl(*(uint32_t *)pk);
		if ((type >= XMSS_MT_SHA2_20_2_256) &&
#ifdef CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES
		    (type <= XMSS_MT_SHAKE_60_12_512))
#else
		    (type <= XMSS_MT_SHA2_60_12_256))
#endif
		{
			return (cmrt_xmss_mt_algorithm_type)type;
		}
	}
	return XMSS_MT_RESERVED;
}

cmrt_hash_algo_t cmrt_xmss_mt_get_hash_algo(cmrt_xmss_mt_algorithm_type xmss_mt_type)
{
	const cmrt_xmss_param_t *p = cmrt_xmss_mt_load_param(xmss_mt_type);
	switch(p->otstype) {
	case WOTSP_SHA2_256:
		return CMRT_HASH_SHA256;
#ifdef CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES
	case WOTSP_SHA2_512:
		return CMRT_HASH_SHA512;
	case WOTSP_SHAKE_256:
		return CMRT_HASH_SHAKE128;
	case WOTSP_SHAKE_512:
#endif
	default:
		/* there is no invalid cmrt_hash_algo_t */
		return CMRT_HASH_SHAKE256;
	}
}

const cmrt_xmss_param_t *cmrt_xmss_mt_load_param(cmrt_xmss_mt_algorithm_type xmss_mt_type)
{
	static const cmrt_xmss_param_t xmss_mt_parms[] = {
		{ XMSS_MT_SHA2_20_2_256,   WOTSP_SHA2_256,   2u, 20u, 32u },
		{ XMSS_MT_SHA2_20_4_256,   WOTSP_SHA2_256,   4u, 20u, 32u },
		{ XMSS_MT_SHA2_40_2_256,   WOTSP_SHA2_256,   2u, 40u, 32u },
		{ XMSS_MT_SHA2_40_4_256,   WOTSP_SHA2_256,   4u, 40u, 32u },
		{ XMSS_MT_SHA2_40_8_256,   WOTSP_SHA2_256,   8u, 40u, 32u },
		{ XMSS_MT_SHA2_60_3_256,   WOTSP_SHA2_256,   3u, 60u, 32u },
		{ XMSS_MT_SHA2_60_6_256,   WOTSP_SHA2_256,   6u, 60u, 32u },
		{ XMSS_MT_SHA2_60_12_256,  WOTSP_SHA2_256,  12u, 60u, 32u },
#ifdef CONFIG_CMRT_SHSIG_XMSS_ENABLE_ALL_MODES
		{ XMSS_MT_SHA2_20_2_512,   WOTSP_SHA2_512,   2u, 20u, 64u },
		{ XMSS_MT_SHA2_20_4_512,   WOTSP_SHA2_512,   4u, 20u, 64u },
		{ XMSS_MT_SHA2_40_2_512,   WOTSP_SHA2_512,   2u, 40u, 64u },
		{ XMSS_MT_SHA2_40_4_512,   WOTSP_SHA2_512,   4u, 40u, 64u },
		{ XMSS_MT_SHA2_40_8_512,   WOTSP_SHA2_512,   8u, 40u, 64u },
		{ XMSS_MT_SHA2_60_3_512,   WOTSP_SHA2_512,   3u, 60u, 64u },
		{ XMSS_MT_SHA2_60_6_512,   WOTSP_SHA2_512,   6u, 60u, 64u },
		{ XMSS_MT_SHA2_60_12_512,  WOTSP_SHA2_512,  12u, 60u, 64u },
		{ XMSS_MT_SHAKE_20_2_256,  WOTSP_SHAKE_256,  2u, 20u, 32u },
		{ XMSS_MT_SHAKE_20_4_256,  WOTSP_SHAKE_256,  4u, 20u, 32u },
		{ XMSS_MT_SHAKE_40_2_256,  WOTSP_SHAKE_256,  2u, 40u, 32u },
		{ XMSS_MT_SHAKE_40_4_256,  WOTSP_SHAKE_256,  4u, 40u, 32u },
		{ XMSS_MT_SHAKE_40_8_256,  WOTSP_SHAKE_256,  8u, 40u, 32u },
		{ XMSS_MT_SHAKE_60_3_256,  WOTSP_SHAKE_256,  3u, 60u, 32u },
		{ XMSS_MT_SHAKE_60_6_256,  WOTSP_SHAKE_256,  6u, 60u, 32u },
		{ XMSS_MT_SHAKE_60_12_256, WOTSP_SHAKE_256, 12u, 60u, 32u },
		{ XMSS_MT_SHAKE_20_2_512,  WOTSP_SHAKE_512,  2u, 20u, 64u },
		{ XMSS_MT_SHAKE_20_4_512,  WOTSP_SHAKE_512,  4u, 20u, 64u },
		{ XMSS_MT_SHAKE_40_2_512,  WOTSP_SHAKE_512,  2u, 40u, 64u },
		{ XMSS_MT_SHAKE_40_4_512,  WOTSP_SHAKE_512,  4u, 40u, 64u },
		{ XMSS_MT_SHAKE_40_8_512,  WOTSP_SHAKE_512,  8u, 40u, 64u },
		{ XMSS_MT_SHAKE_60_3_512,  WOTSP_SHAKE_512,  3u, 60u, 64u },
		{ XMSS_MT_SHAKE_60_6_512,  WOTSP_SHAKE_512,  6u, 60u, 64u },
		{ XMSS_MT_SHAKE_60_12_512, WOTSP_SHAKE_512, 12u, 60u, 64u }
#endif
	};
	for (unsigned int i = 0; i < sizeof(xmss_mt_parms)/sizeof(cmrt_xmss_param_t); ++i) {
		const cmrt_xmss_param_t *p = &xmss_mt_parms[i];
		if (p->atype == xmss_mt_type) {
			return p;
		}
	}
	return NULL;
}

int cmrt_xmss_mt_verify(cmrt_hc_t hc, const uint8_t *pk, const uint8_t *digest,
			size_t dlen, const uint8_t *sm, wdt_feed_func *wdt_feed)
{
	cmrt_xmss_mt_algorithm_type xmss_mt_type = cmrt_xmss_mt_get_type(pk);
	if (xmss_mt_type == XMSS_MT_RESERVED) {
		return -EINVAL; /* wrong or unspported OID */
	}
	const cmrt_xmss_param_t *parm = cmrt_xmss_mt_load_param(xmss_mt_type);
	if ((parm == NULL) || (dlen > parm->hsize)) {
		return -EINVAL; /* unspported algo type or too big message */
	}
	const cmrt_xmss_ots_param_t *otsparm = cmrt_xmss_load_ots_parm(parm->otstype);
	if (otsparm == NULL) {
		return -EINVAL; /* unspported ots type */
	}
	return cmrt_xmss_verify_internal(hc, pk, digest, dlen, parm->height / parm->layer,
					 parm->layer, otsparm, sm, wdt_feed);
}
