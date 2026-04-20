/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>
#include <init.h>
#include <drivers/cmrt/kdc.h>
#include <drivers/cmrt/eac.h>
#include <drivers/cmrt/sic.h>
#include "kdc_kat.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

typedef struct {
	uint32_t diversify_len;
	const uint8_t *output_key;  /** length must be KDC_KEY_SIZE */
	const uint8_t *test_mode_key;  /** length must be KDC_KEY_SIZE */
} kdc_kat_t;

#define INIT_KDC_KAT_T(diversify_len, output_key, test_mode_key) \
	{							 \
		diversify_len,					 \
		output_key,					 \
		test_mode_key,					 \
	},

/* KDC Core Vectors */

/* Path length: 0x7 */
/* Final key real key split */
static const uint8_t kdc_kat_output_key0[] = {
	0xFB, 0x9e, 0x7F, 0x6e,
	0xef, 0xe3, 0x52, 0xef,
	0xc1, 0xc4, 0x6d, 0xac,
	0x26, 0xf2, 0x7D, 0xCD,
	0xed, 0xd6, 0x1B, 0x74,
	0x7F, 0x95, 0xb0, 0x15,
	0x47, 0x75, 0xed, 0x5a,
	0x10, 0x42, 0xdc, 0x16,
};

/* Path length: 0x7 */
/* Final key test mode */
static const uint8_t kdc_kat_test_mode_output_key0[] = {
	0xa9, 0x9b, 0xe2, 0x61,
	0xdc, 0x0a, 0x77, 0x99,
	0x14, 0x25, 0xf6, 0x5b,
	0x36, 0x97, 0xa6, 0x3a,
	0x89, 0x9a, 0x8c, 0x05,
	0x2c, 0xb5, 0xaa, 0x87,
	0x7e, 0xf9, 0xd8, 0xc5,
	0xe4, 0xbf, 0xc2, 0xc6
};

/* Populate KDC KAT vectors array. */
static const kdc_kat_t kdc_kat_vectors[] = {
	INIT_KDC_KAT_T(6, kdc_kat_output_key0, kdc_kat_test_mode_output_key0)
};

/* Number of HC KAT vectors array elements */
#define KDC_KAT_VECTORS_COUNT (sizeof(kdc_kat_vectors) / sizeof(kdc_kat_vectors[0]))

static void kdc_run_kat(cmrt_kdc_t kdc, const kdc_kat_t *kat)
{
	cmrt_kdc_cmd_t kcmd = {0};

	/* Derive the key and sync. */
	kcmd.base_key_id = KEY_ID_SELF_TEST;
	kcmd.dest = KDC_DEST_SW;
	kcmd.key_size = KDC_SIZE_256;
	kcmd.diversify_len = kat->diversify_len;

	int rc = cmrt_kdc_derive_key(kdc, &kcmd);
	if (rc != 0) {
		cmrt_eac_kat_error(CORE_ID_KDC, -EXDEV, rc);
	}
	rc = cmrt_kdc_sync(kdc);
	if (rc != 0) {
		cmrt_eac_kat_error(CORE_ID_KDC, -EXDEV, rc);
	}

	/* Verify the results. */
	if (memcmp(kat->output_key, (uint8_t *)kcmd.key, sizeof(kcmd.key)) != 0) {
		if ((kat->test_mode_key == NULL) ||
		    (memcmp(kat->test_mode_key, (uint8_t *)kcmd.key, sizeof(kcmd.key)) != 0)) {
			cmrt_eac_kat_error(CORE_ID_KDC, -EXDEV, -EFAULT);
		}
	}

	rc = cmrt_dd_flush((cmrt_dd_context_t *)kdc);
	if (rc != 0) {
		cmrt_eac_kat_error(CORE_ID_KDC, -EXDEV, rc);
	}
	/* Success if we are here. */
}

void kdc_open_kat(cmrt_dd_context_t *context)
{
	LOG_INF("Running KDC KAT vectors");

	cmrt_kdc_t kdc = (cmrt_kdc_t)context;
	/* Run the KDC kats and expect output vector match */
	for (uint32_t i = 0; i < KDC_KAT_VECTORS_COUNT; i++) {
		kdc_run_kat(kdc, &kdc_kat_vectors[i]);
	}
}

int kdc_init_kat(const struct device *dev)
{
	ARG_UNUSED(dev);
#if defined(CONFIG_CMRT_ASIL_B_MODE) && !defined(CONFIG_SUPERVISOR_MODE)
	cmrt_kdc_t kdc = cmrt_kdc_open(CMRT_O_HWC_FORCE_KAT);
	if (!cmrt_dd_valid(kdc)) {
		cmrt_eac_kat_error(CORE_ID_KDC, -EXDEV, -ENODEV);
	}
	cmrt_kdc_close(kdc);
#endif
	return 0;
}
