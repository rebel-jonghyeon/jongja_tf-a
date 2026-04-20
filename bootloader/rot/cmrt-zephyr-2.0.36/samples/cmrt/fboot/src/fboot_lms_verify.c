/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <fboot.h>
#include <cmrt/shsig/lms.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

int fboot_verify_lms(cmrt_cc_t cc, const uint8_t *pk,
				 const uint8_t *digest, size_t dlen,
				 const uint8_t *signature)
{
	cmrt_hc_t hc = (cmrt_hc_t)cmrt_dd_open(DEVICE_DT_GET(DT_CHOSEN(rambus_fboot_hc)), 0, NULL);
	if (!cmrt_is_valid(hc)) {
		return -ENODEV;
	}

	int res = cmrt_lms_verify(hc, pk, digest, dlen, signature);
	cmrt_hc_close(hc);

	if (cc != NULL) {
		for (int i = 0; i < SHA256_WORDS; i++) {
			/*
			 * Mix the minimum number of words (zeros) for all pktypes.
			 * We cannot really do more because we already have set CC
			 * to the expected value.
			 */
			(void)cmrt_cc_mix(cc, res);
		}
	}
	if (res != 0) {
		LOG_INF("LMS verify failed: %d", res);
		return -EPERM;
	}
	LOG_INF("LMS verify OK.");

	return 0;
}
