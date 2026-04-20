/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#include <fboot.h>
#include <sboot.h>
#include <syscalls.h>
#include "supervisor.h"
#include "lifecycle.h"
#include "img.h"
#ifdef CONFIG_CMRT_CFI
#include "cfi.h"
#endif

#include <linker/linker-defs.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

/*
 * Hash of (public key type PK_HMAC_SHA256 0x02 0x00 0x00 0x00 ||
 * the PNAK key value 0x02 0x00 0x00 0x00)
 */
static alignas(4) const uint8_t pnak_pkhash[SHA256_BYTES] = {
	0x41, 0xd8, 0x05, 0xe6, 0x13, 0xef, 0xbe, 0x1a,
	0xcb, 0x36, 0xea, 0xa0, 0x12, 0x7a, 0x35, 0xda,
	0x4a, 0x1f, 0xaa, 0x1a, 0xc9, 0x79, 0x85, 0xd0,
	0x78, 0xe5, 0x0d, 0x1f, 0xd9, 0x60, 0x55, 0xfd
};

static bool perso_root_valid;

cmrt_omc_t fboot_permissions(const cmrt_omc_root_id_t *id, bool init)
{
	/* Set permissions for fboot itself when running in machine mode. */
	static const cmrt_omc_root_perm_t perms = {
		.slot_perm.val = 0xFFFFFFFF,
		.key_perm.val = 0xFFFFFFFF,
		.feature_perm.val = 0xFFFFFFFF,
		.sw_otp_perm = {
			{ .val = 0x1FFFFUL << 15 },
			{ .val = 0x1FFFFUL << 15 },
		},
		.software_perm.val = 0xFFFFFFFF,
	};
	/* First assert canary to be able to set permissions. */
	int res = cmrt_assert_canary();
	if (res != 0) { halt(-ENOEXEC, res, "Failed to assert CC: %d", res); }

	/* Open OMC handle which we return if all goes as planned. */
	cmrt_omc_t omc = cmrt_omc_open(0);
	if (!cmrt_is_valid(omc)) { halt(-ENOEXEC, -ENODEV, "Cannot open OMC"); }

	/* Save perso root status for later. */
	const cmrt_otp_layout_t *otp = cmrt_otp_layout(0);
	perso_root_valid = (otp->h.status_word & OTP_PERSO_INVALID) != OTP_PERSO_INVALID;
	set_root_permissions(omc, &perms, false);
	if (id != NULL) {
		/* Use silo mode for fboot containers. */
		set_derive_path(id, CAVEAT_SILO);
	}
	if (init) {
		/* Initialize the security monitor. */
		fboot_init_sm(omc);
	}
	return omc;
}

static int load_fboot_container(void *blob, size_t *size, uint32_t *peerid)
{
	cmrt_sic_t sic = cmrt_sic_open(CMRT_O_FEED_WDT, 0);
	if (!cmrt_is_valid(sic)) { return -ENODEV; }

	int res = cmrt_sic_read(sic, blob, size, peerid, 0);
	if (res != 0) { goto out; }
	cmrt_set_boot_status(READY_TO_RUN_CONTAINER, READY_TO_RUN_CONTAINER);
	res = cmrt_sic_sync(sic);
	if (res != 0) { goto out; }

	LOG_INF("Received perso of %d bytes", *size);
 out:
	cmrt_set_boot_status(0, READY_TO_RUN_CONTAINER);
	cmrt_sic_close(sic);
	return res;
}

#define CASSERT1_VERIFY_HMAC       (0x3954faf3UL)
#define CASSERT2_VERIFY_HMAC       (0xf5cb6918UL)

static int run_fboot_container(void)
{
	/* Max buflen is all the rest of the memory. */
	uint32_t imglen = (uint32_t)&_image_ram_end - (uint32_t)CONFIG_SRAM_BASE_ADDRESS;
	uint32_t size = (uint32_t)KB(CONFIG_SRAM_SIZE) - imglen;

	/* Wait for container image, that's all we can get. */
	uint32_t peerid;
	uint32_t *blob = (uint32_t *)&_image_ram_end;
	LOG_INF("Reading machine mode perso from HLOS to %p", blob);
	int res = load_fboot_container(blob, &size, &peerid);
	if (res != 0) { return res; }

	cmrt_img_footer_t footer;
	res = cmrt_img_footer_parse(blob, size, &footer);
	if (res < 0) { return res; }

	LOG_INF("HMAC verify for image at %p", blob);
	cmrt_cc_t cc = cmrt_cc_open();
	if (!cmrt_is_valid(cc)) { return -ENODEV; }
	res = cmrt_cc_assert(cc, CASSERT1_VERIFY_HMAC, CASSERT2_VERIFY_HMAC);
	if (res == 0) {
		res = fboot_verify_hmac(cc, blob, size, pnak_pkhash, &footer);
		if (res == 0) { res = cmrt_cc_sync(cc); }
	}
	cmrt_cc_close(cc);
	if (res != 0) { return res; }

	cmrt_raw_footer_t raw;
	res = cmrt_raw_footer_parse(blob, size - footer.footer_length, false, &raw);
	if (res < 0) { return res; }
#ifdef CONFIG_CMRT_CFI
	res = cmrt_cfi_load_metadata(blob, size - footer.footer_length - raw.verlen, &raw);
	if (res != 0) { return res; }
#endif
	cmrt_raw_image_init(&raw);
	int (*perso)(void) = (void *)(uintptr_t)raw.entry_point;
	LOG_INF("Starting perso...");
	return perso();
}

#define SUPERVISOR_PERSO_MAXSIZE (RISCV_RAM_SIZE - CONFIG_CMRT_MACHINE_RAM_SIZE)

static int enter_supervisor(void)
{
	alignas(4) cmrt_omc_root_t root;
	cmrt_omc_root_t *perso_root = NULL;
	if (perso_root_valid) {
		/* Set perso root for the fboot container based on lifecycle. */
		perso_root = &root;
		(void)memset(perso_root, 0, sizeof(*perso_root));

		uint32_t lc = cmrt_read_reg(CMRT_SIC_BASE, R_DEVICE_LIFECYCLE);
		switch (lc) {
		case DLC_TESTED:
		case DLC_PROVISIONED:
			perso_root->perm.slot_perm.val = 0xFFFFFFFF;
			perso_root->perm.key_perm.val = 0xFFFFFFFF;
			perso_root->perm.feature_perm.val = 0xFFFFFFFF;
			perso_root->perm.sw_otp_perm[0].val = 0x1FFFFUL << 15;
			perso_root->perm.sw_otp_perm[1].val = 0x1FFFFUL << 15;
			perso_root->perm.software_perm.val = 0xFFFFFFFF;
			break;
		case DLC_MISSION:
			perso_root->perm.slot_perm.val = OMC_SLOT_PERM_LIFECYCLE;
			perso_root->perm.key_perm.val = 0;
#ifdef CONFIG_DEBUG
			perso_root->perm.feature_perm.val = 1UL << FMC_FEATURE_INT_MIN;
#else
			perso_root->perm.feature_perm.val = 0;
#endif
			perso_root->perm.sw_otp_perm[0].val = 0;
			perso_root->perm.sw_otp_perm[1].val = 0;
			perso_root->perm.software_perm.val = 0xFFFFFFFF & ~(OMC_SW_LOAD_PERM_MASK);
			perso_root->perm.software_perm.val |= OMC_SW_PERM_FBOOT_CONTAINER;
			break;
		case DLC_FRA:
			perso_root->perm.slot_perm.val = OMC_SLOT_PERM_LIFECYCLE;
			perso_root->perm.key_perm.val = 0;
			perso_root->perm.feature_perm.val = 1UL << FMC_FEATURE_INT_MIN;
			perso_root->perm.sw_otp_perm[0].val = 0;
			perso_root->perm.sw_otp_perm[1].val = 0;
			perso_root->perm.software_perm.val = 0xFFFFFFFF & ~(OMC_SW_LOAD_PERM_MASK);
			perso_root->perm.software_perm.val |= OMC_SW_PERM_FBOOT_CONTAINER;
			break;
		default:
			/* Leave perso_root empty. */
			break;
		}
		/* Copy perso public key hash from SIC registers. */
		uint32_t *perso_pkhash = (uint32_t *)perso_root->id.hash;
		for (size_t i = 0; i < SHA256_WORDS; i++) {
			uint32_t offset = R_PERSO_PUBLIC_KEY_HASH_0 + i * 4u;
			*perso_pkhash++ = cmrt_read_reg(CMRT_SIC_BASE, offset);
		}
	}
	/* Set perso root into security monitor. */
	set_perso_root(perso_root);

	/* Make more space for s-perso. */
	undo_sboot_bootstrap();

	/* Load fboot container into SRAM. */
	uint32_t *blob = (uint32_t *)(uintptr_t)fboot_supervisor_clear();
	uint32_t peer_flowid;
	size_t size = (size_t)SUPERVISOR_PERSO_MAXSIZE;
	LOG_INF("Reading supervisor mode perso from HLOS to %p, maxsize %u", blob, size);
	int res = load_fboot_container(blob, &size, &peer_flowid);
	if (res != 0) { return res; }

	/* Verify image and call tboot to set MPU and run in S mode. */
	cmrt_raw_footer_t raw;
	res = fboot_load_image(blob, size, &raw, NULL);
	if (res < 0) { return res; }
	if (res != CAVEAT_SILO) {
	    /* Only allow silo fboot container to be started. */
	    return -EPERM;
	}
	return fboot_supervisor_start();
}

#define CASSERT1_ENTER_SBOOT       (0xb1c293a0UL)
#define CASSERT2_ENTER_SBOOT       (0x5b0d46feUL)

static int enter_sboot(cmrt_omc_t omc, const cmrt_omc_root_id_t *id)
{
	cmrt_img_header_t hdr;
#ifdef CONFIG_CMRT_SBOOT_IN_ROM
	uint32_t esw_start = (uint32_t)RISCV_ROM_BASE;
	LOG_INF("Reading sboot from ROM at 0x%x", esw_start);

	(void)memcpy(&hdr, (void *)esw_start, sizeof(hdr));
	uint32_t *blob = (uint32_t *)((uint8_t *)esw_start + sizeof(hdr));
#else
	uint32_t esw_start = cmrt_otp_esw_start();
	LOG_INF("Reading sboot from OTP offset 0x%x", esw_start);

	(void)memcpy((uint8_t *)&hdr, cmrt_otp_layout(esw_start), sizeof(hdr));
	uint32_t *blob = cmrt_otp_layout(esw_start + sizeof(hdr));
#endif
	int res = -ENOSPC;
	if (!cmrt_is_valid_hdr(&hdr, SBOOT_MAXSIZE)) {
		LOG_INF("Invalid sboot header");
		cmrt_omc_close(omc);
		goto out;
	}
	uint32_t digest[SHA256_WORDS];
	uint8_t *sboot_sram = (uint8_t *)(uintptr_t)SBOOT_START;
	(void)memcpy(sboot_sram, (uint8_t *)blob, hdr.length);
	size_t sboot_len = (size_t)hdr.length - SHA256_BYTES;
	cmrt_omc_close(omc);

	LOG_INF("Verifying sboot IMG in SRAM");
	res = fboot_hash(NULL, CMRT_HASH_SHA256, sboot_sram, sboot_len, digest);
	if (res != 0) { goto out; }

	res = -ENODEV;
	cmrt_cc_t cc = cmrt_cc_open();
	if (!cmrt_is_valid(cc)) { goto out; }
	res = cmrt_cc_assert(cc, CASSERT1_ENTER_SBOOT, CASSERT2_ENTER_SBOOT);
	if (res == 0) {
		res = -EPERM;
		if (fboot_memmatch(cc, digest, sboot_sram + sboot_len, sizeof(digest))) {
			res = cmrt_cc_sync(cc);
		}
	}
	cmrt_cc_close(cc);
#ifdef CONFIG_CMRT_FIPS_140_MODE
	LOG_INF("Zero sboot digest");
	(void)memset(digest, 0x00, sizeof(digest));
#endif
	if (res != 0) { goto out; }

	cmrt_raw_footer_t raw;
	/* Execute sboot from SRAM. */
	res = cmrt_raw_footer_parse(sboot_sram, sboot_len, false, &raw);
	if (res < 0) { goto out; }
#ifdef CONFIG_CMRT_CFI
	res = cmrt_cfi_load_metadata(sboot_sram, sboot_len - res, &raw);
	if (res != 0) { goto out; }
#endif
	cmrt_raw_image_init(&raw);
	/* SHA256 is stored always in big endian */
	for (uint32_t i = 0; i < SIC_SBOOT_HASH_REGS; ++i) {
	    cmrt_write_reg(CMRT_SIC_BASE, R_SBOOT_HASH_0 + i*4u,
			   __builtin_bswap32(digest[i]));
	}
	sboot_bootstrap(&raw);
	int (*sboot)(void) = (void *)(uintptr_t)raw.entry_point;
	res = sboot();
	LOG_INF("Sboot returned %d", res);
	/* Clear derive path and set permissions again. */
	cmrt_clear_container_context();
	cmrt_omc_close(fboot_permissions(id, false));
 out:
	cmrt_eac_set_internal_error(-EAGAIN, res);
	return id == NULL ? enter_supervisor() : res;
}

static int handle_lc_blank(void)
{
	/* Set root id to pnak_pkhash defined above for the derivation path. */
	cmrt_omc_t omc = fboot_permissions((const cmrt_omc_root_id_t *)pnak_pkhash, true);

	/* Set KDC hardware state to initial value. */
	int res = fboot_kdc_set_hw_state((uint8_t)CONFIG_CMRT_KDC_HW_STATE);
	if (res != 0) { goto out; }

	uint32_t tdv[CMRT_FMC_TDV_SIZE];
#ifdef CONFIG_CMRT_SIC2
	/* Set TDV to the customer specified value. */
	for (int i = 0; i < CMRT_FMC_TDV_SIZE; ++i) {
		tdv[i] = cmrt_read_reg(CMRT_SIC_BASE, R_DEFAULT_TDV_BLANK_0 + i*4u);
	}
#else
	/* Set TDV to all ones. */
	for (int i = 0; i < CMRT_FMC_TDV_SIZE; ++i) {
		tdv[i] = 0xffffffffu;
	}
#endif
	/* Always clear the low 4 bits. */
	tdv[0] &= ~0xfu;
	res = fboot_set_tdv(tdv);
	if (res != 0) { goto out; }

#ifdef CONFIG_CMRT_SBOOT_IN_ROM
	res = enter_sboot(omc, (const cmrt_omc_root_id_t *)pnak_pkhash);
#else
	cmrt_omc_close(omc);
#endif
	while (res == 0) {
		res = run_fboot_container();
		if (res == 0) { cmrt_eac_set_internal_error(-EAGAIN, 0); }
	}

	return res;
 out:
	cmrt_omc_close(omc);
	return res;
}

static int handle_lc_tested(void)
{
	cmrt_omc_t omc = fboot_permissions(NULL, true);
	const cmrt_otp_layout_t *otp = cmrt_otp_layout(0);

	/* Set KDC hardware state to initial value. */
	int res = fboot_kdc_set_hw_state((uint8_t)CONFIG_CMRT_KDC_HW_STATE);
	if (res != 0) { goto out; }

	/* Set test and debug vector to values in OTP. */
	res = fboot_set_tdv(otp->h.test_debug_vector);
	if (res != 0) { goto out; }

	/* OMC is closed in enter_sboot. */
	return enter_sboot(omc, NULL);
 out:
	cmrt_omc_close(omc);
	return res;
}

static int handle_lc_provisioned(void)
{
	return handle_lc_tested();
}

static int handle_lc_mission(void)
{
	cmrt_omc_t omc = fboot_permissions(NULL, true);
	/* OMC is closed in enter_sboot. */
	return enter_sboot(omc, NULL);
}

static int handle_lc_fra(void)
{
	/* We don't need OTP here, but fboot containers will need it. */
	cmrt_omc_close(fboot_permissions(NULL, true));

	/* Set KDC hardware state to initial value. */
	int res = fboot_kdc_set_hw_state((uint8_t)CONFIG_CMRT_KDC_HW_STATE);
	if (res != 0) { return res; }

	cmrt_eac_set_internal_error(-EAGAIN, 0);
	return enter_supervisor();
}

static int handle_lc_decommisioned(void)
{
	halt(-ENOEXEC, -ENOEXEC, "Device is non-functional.");
	return 0;
}

int run_lifecycle_op(uint32_t lc)
{
	int res = -ENOENT;
	switch (lc) {
	case DLC_BLANK:
		res = handle_lc_blank();
		break;
	case DLC_TESTED:
		res = handle_lc_tested();
		break;
	case DLC_PROVISIONED:
		res = handle_lc_provisioned();
		break;
	case DLC_MISSION:
		res = handle_lc_mission();
		break;
	case DLC_FRA:
		res = handle_lc_fra();
		break;
	case DLC_DECOMMISSIONED:
		res = handle_lc_decommisioned();
		break;
	default:
		halt(-ENOENT, 0, "No operation for lifecycle %x", lc);
		CODE_UNREACHABLE;
		break;
	}
	return res;
}
