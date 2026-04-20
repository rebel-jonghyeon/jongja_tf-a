/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <fboot.h>
#include <cmrt/shsig/xmss.h>

#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_MT_VERIFY
#include <cmrt/shsig/xmss_mt.h>
#endif

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);


#ifdef CONFIG_WDT_CMRT
static void wdt_feed_call(void) {
	extern int wdt_cmrt_feed(const struct device *dev, int channel_id);
	(void)wdt_cmrt_feed(NULL, 0);
}
#else
static wdt_feed_func *wdt_feed_call = NULL;
#endif

int fboot_verify_xmss(cmrt_cc_t cc,
				  const void *blob,
				  size_t bsize,
				  const cmrt_img_footer_t *footer,
				  uint32_t *digest, size_t dsize)
{
	bool mt = footer->public_key_type == PK_XMSS_MT;
	uint32_t xmss_type = XMSS_RESERVED;
	cmrt_hash_algo_t halgo;
	if (mt) {
#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_MT_VERIFY
		xmss_type = cmrt_xmss_mt_get_type(footer->public_key);
		halgo = cmrt_xmss_mt_get_hash_algo(xmss_type);
#endif
	} else {
		xmss_type = cmrt_xmss_get_type(footer->public_key);
		halgo = cmrt_xmss_get_hash_algo(xmss_type);
	}
	if (xmss_type == XMSS_RESERVED) {
		return -EINVAL; /* wrong or unspported OID */
	}

	size_t dlen = cmrt_hc_hash_size(halgo, false, dsize);
	if (dlen > dsize) {
		return -EINVAL;
	}

	/* Calculate given hash over the image and footer, rambus_fboot_hc
	 * should support given hash algo, hash_final() closes HC */
	int res = img_digest(NULL, halgo, blob, bsize, footer, digest);
	if (res != 0) {
		return res;
	}
	cmrt_hc_t hc = (cmrt_hc_t)cmrt_dd_open(DEVICE_DT_GET(DT_CHOSEN(rambus_fboot_hc)), 0, NULL);
	if (!cmrt_is_valid(hc)) {
		return -ENODEV;
	}

	if (mt) {
#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_MT_VERIFY
		res = cmrt_xmss_mt_verify(hc, footer->public_key,
					  (const uint8_t *)digest, dlen,
					  footer->signature, wdt_feed_call);
#else
		res = -EINVAL;
#endif
	} else {
		res = cmrt_xmss_verify(hc, footer->public_key,
				       (const uint8_t *)digest, dlen,
				       footer->signature, wdt_feed_call);
	}
	cmrt_hc_close(hc);

	if (cc != NULL) {
		for (int i = 0; i < SHA256_WORDS; i++) {
			/*
			 * Mix the minimum number of words (zeros) for all hash
			 * algo types. We cannot really do more because we
			 * already have set CC to the expected value.
			 */
			(void)cmrt_cc_mix(cc, res);
		}
	}
	if (res != 0) {
		LOG_INF("XMSS verify failed: %d", res);
		return -EPERM;
	}
	LOG_INF("XMSS verify OK.");

	return 0;
}
