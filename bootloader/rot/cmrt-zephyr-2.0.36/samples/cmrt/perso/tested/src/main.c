/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <string.h>
#include <stdalign.h>
#include <assert.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/util.h>
#include <drivers/cmrt/fboot.h>

#ifndef CONFIG_CMRT_SBOOT_IN_ROM
#include "sboot_img.h"
#endif
#include "common.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define PERSO_STATUS_STARTED  0x930200ff
#define PERSO_STATUS_DONE     0x93020000
#define PERSO_STATUS_ERROR    0x93020100

const static char version_info[] __version = PERSO_VERSION_INFO;

#ifdef FIXED_DEVICE_ID
static_assert(sizeof(FIXED_DEVICE_ID) - 1 == OTP_DEVICE_ID_SIZE,
	"invalid fixed device size");
#endif

static cmrt_omc_root_t root_ecdsa_p256 = {
	.id.hash = {
#include "pkhash_ecdsa_p256.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE07,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};

#ifdef CONFIG_CMRT_FBOOT_HAS_ECDSA_P521
static cmrt_omc_root_t root_ecdsa_p521 = {
	.id.hash = {
#include "pkhash_ecdsa_p521.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE07,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};
#endif

#ifdef CONFIG_CMRT_FBOOT_HAS_ECDSA_P384
static cmrt_omc_root_t root_ecdsa_p384 = {
	.id.hash = {
#include "pkhash_ecdsa_p384.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE07,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};
#endif

#ifdef CONFIG_CMRT_FBOOT_HAS_RSA_VERIFY
static cmrt_omc_root_t root_rsa_3k = {
	.id.hash = {
#include "pkhash_rsa_3k.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE07,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};

static cmrt_omc_root_t root_rsa_4k = {
	.id.hash = {
#include "pkhash_rsa_4k.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE07,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};
#endif
#ifdef CONFIG_CMRT_SUPERVISOR_IN_ROM
static cmrt_omc_root_t omc_root4 = {
	.id.hash = {
#include "pkhash_sha256.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE0F,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};
#endif

#ifdef CONFIG_CMRT_FIPS_140_MODE
static cmrt_omc_root_t root_fips = {
	.id.hash = {
#include "pkhash_ecdsa_fips.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE07,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};
#endif

#ifdef CONFIG_CMRT_FBOOT_HAS_LMS_VERIFY
static cmrt_omc_root_t root_lms = {
	.id.hash = {
#include "pkhash_lms.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE07,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};
#endif

#ifdef CONFIG_CMRT_FBOOT_HAS_LMS_HSS_VERIFY
static cmrt_omc_root_t root_lms_hss = {
	.id.hash = {
#include "pkhash_lms_hss.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE07,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};
#endif

#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_VERIFY
static cmrt_omc_root_t root_xmss = {
	.id.hash = {
#include "pkhash_xmss.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE07,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};
#endif

#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_MT_VERIFY
static cmrt_omc_root_t root_xmss_mt = {
	.id.hash = {
#include "pkhash_xmss_mt.inc"
	},
	.perm.slot_perm.val = 0xFFFFFF1F,
	.perm.key_perm.val = 0xFFFFFE07,
	.perm.feature_perm.val = 0x7FFFFFFF,
	.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
	.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
	.perm.software_perm.val = 0xFFFFFFFF,
};
#endif

static struct cmrt_perso_root roots[] = {
	{&root_ecdsa_p256, "ECDSA P256"},
#ifdef CONFIG_CMRT_FIPS_140_MODE
	{&root_fips, "FIPS"},
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_ECDSA_P521
	{&root_ecdsa_p521, "ECDSA P521"},
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_RSA_VERIFY
	{&root_rsa_3k, "RSA 3K"},
	{&root_rsa_4k, "RSA 4K"},
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_ECDSA_P384
	{&root_ecdsa_p384, "ECDSA P384"},
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_LMS_VERIFY
	{&root_lms, "LMS"},
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_LMS_HSS_VERIFY
	{&root_lms_hss, "LMS_HSS"},
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_VERIFY
	{&root_xmss, "XMSS"},
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_MT_VERIFY
	{&root_xmss_mt, "XMSS_MT"},
#endif

	{NULL, ""}
};

static_assert(
	CONFIG_CRI_OMC_ROOTS_NUM + 1  >= sizeof(roots) / sizeof(struct cmrt_perso_root),
	"too many roots for device");

static const cmrt_omc_key_split_t omc_keysplit0 = {
	.key = { 0x2e, 0xd4, 0xd0, 0x81, 0xa5, 0x11, 0xff, 0xde,
		 0xa6, 0x3e, 0xcb, 0x58, 0xc0, 0x50, 0x20, 0x23,
		 0x32, 0x92, 0x0a, 0x72, 0xe3, 0x0f, 0x9e, 0x80,
		 0x4c, 0xe3, 0xaf, 0xd8, 0xdb, 0x61, 0xaf, 0xf2
	}
};

int main(void)
{
	cmrt_set_boot_status(CONTAINER_RUNNING_ID, CONTAINER_RUNNING_ID);
	uint32_t lifecycle = cmrt_read_reg(CMRT_SIC_BASE, R_SCRATCH_0);
	if (lifecycle == 0 || lifecycle == 0xffffffff) {
	    lifecycle = DLC_PROVISIONED;
	}
	cmrt_set_perso_status(PERSO_STATUS_STARTED);
	LOG_INF("Tested perso %s starting up", version_info);

	int res;
#ifndef CONFIG_CMRT_CFI
	res = cmrt_burn_dgok();
	if (res) goto out;
#endif
	res = cmrt_perso_burn_device_id();
	if (res) goto out;

	res = cmrt_perso_create_roots(roots);
	if (res) goto out;

	res = cmrt_perso_write_otp_keysplit(0, &omc_keysplit0);
	if (res) goto out;

#ifndef CONFIG_CMRT_SBOOT_IN_ROM
	res = cmrt_perso_burn_sboot(sboot_img, sboot_img_len);
	if (res) goto out;
#endif
	res = cmrt_set_lifecycle(lifecycle);
	if (res) goto out;

	LOG_INF("All done for tested perso");
 out:
	cmrt_set_boot_status(0, CONTAINER_RUNNING_ID);
	cmrt_set_perso_status((res < 0) ? PERSO_STATUS_ERROR : PERSO_STATUS_DONE);

	return fboot_halt(-EFAULT, res);
}
