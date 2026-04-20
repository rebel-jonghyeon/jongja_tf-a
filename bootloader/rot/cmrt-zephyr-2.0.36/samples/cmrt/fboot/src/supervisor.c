/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <fboot.h>
#include <syscalls.h>
#include "supervisor.h"
#include "lifecycle.h"
#include "img.h"
#include <linker/linker-defs.h>
#include <cmrt_mpu.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define RUN_IN_ROM(f) ((f)->text_start > (uint32_t)ROM_BASE && (f)->rodata_end < (uint32_t)ROM_END)
#define RUN_IN_RAM(f) ((f)->text_start > (uint32_t)RAM_BASE && (f)->rodata_end < (uint32_t)RAM_END)

#define PKE_RAM_END (RAM_BASE + CONFIG_CMRT_PKERAM_SIZE)
#define IMAGE_RAM_END (uint32_t)&_image_ram_end

__noinit static int (*tboot)(void);
__noinit static cmrt_raw_footer_t tb_raw;
__noinit void *tboot_irq_wrapper; /* possibly set by tboot */
__noinit static int (*supervisor)(void);
__noinit static cmrt_raw_footer_t sv_raw;
__noinit static cmrt_img_footer_t sv_footer;

bool has_supervisor(void)
{
	return supervisor != NULL;
}

cmrt_omc_root_id_t *supervisor_root(void)
{
	return has_supervisor() ? &sv_footer.scid.cid.root : NULL;
}

bool has_tboot(void)
{
	return tboot != NULL;
}

static int supervisor_permissions(bool ccc)
{
	int res = 0;
	if (ccc) {
	    /* Clear fboot permissions. */
	    cmrt_clear_container_context();
#ifdef CONFIG_CMRT_PMU
	} else {
		/* Non-silo supervisor may have permissions in boot bypass.
		 * It is possible to go to sleep even with containers
		 * running and permissions set. */
		if (sv_footer.scid.cid.handling_caveats == CAVEAT_NONE) {
			res = cmrt_assert_canary();
			if (res == 0) {
				cmrt_omc_t omc = cmrt_omc_open(0);
				if (!cmrt_is_valid(omc)) { return -ENODEV; }
				set_root_permissions(omc, NULL, true);
				set_derive_path(NULL, CAVEAT_NONE);
				cmrt_omc_close(omc);
			}
		}
#endif
	}
	/* Apply footer permissions for monolithic supervisor. */
	if (sv_footer.scid.cid.handling_caveats != CAVEAT_NONE) {
		res = cmrt_assert_canary();
		if (res == 0) {
			cmrt_omc_t omc = cmrt_omc_open(0);
			if (!cmrt_is_valid(omc)) { return -ENODEV; }
			set_root_permissions(omc, &sv_footer.permissions, true);
			set_derive_path(&sv_footer.scid.cid.root, CAVEAT_SILO);
			cmrt_omc_close(omc);
		}
	}
	return res;
}

void supervisor_update(size_t size, cmrt_img_footer_t *footer, const cmrt_raw_footer_t *raw)
{
	if (footer->scid.cid.handling_caveats == CAVEAT_BOOT) {
		(void)memcpy(&tb_raw, raw, sizeof(*raw));
		tboot = (void *)(uintptr_t)tb_raw.entry_point;
		cmrt_raw_image_init(&tb_raw);
	} else {
		(void)memcpy(&sv_raw, raw, sizeof(*raw));
		supervisor = (void *)(uintptr_t)sv_raw.entry_point;
		(void)memcpy(&sv_footer, footer, sizeof(*footer));
	}
}

uint32_t *supervisor_image(enum cmrt_image_version_id image)
{
	if (image == CMRT_TBOOT_IMAGE_VERSION && has_tboot()) {
		return (uint32_t *)(uintptr_t)tb_raw.text_start;
	}
	if (image == CMRT_SUPERVISOR_IMAGE_VERSION && has_supervisor()) {
		return (uint32_t *)(uintptr_t)sv_raw.text_start;
	}
	return NULL;
}

int supervisor_bootbypass(void *bbv)
{
	int res = supervisor_permissions(false);
#ifdef CONFIG_CMRT_PMU
	if (res == 0) { res = fboot_verify_bb(false); }
#endif
	if (res == 0) { res = start_supervisor(bbv); }
	return res;
}

uint32_t fboot_supervisor_clear()
{
	tboot = NULL;
	(void)memset(&tb_raw, 0, sizeof(tb_raw));
	tboot_irq_wrapper = NULL;
	supervisor = NULL;
	(void)memset(&sv_raw, 0, sizeof(sv_raw));
	(void)memset(&sv_footer, 0, sizeof(sv_footer));
	/* OS image is placed after PKE and machine mode RAM.
	 * Note that OS image is compiled to start at that
	 * particular memory address. */
	return  (uint32_t)CONFIG_SRAM_BASE_ADDRESS +
		(uint32_t)CONFIG_CMRT_PKERAM_SIZE +
		(uint32_t)CONFIG_CMRT_MACHINE_RAM_SIZE +
		(uint32_t)CONFIG_PIX_OFFSET;
}

void sboot_bootstrap(const cmrt_raw_footer_t *raw)
{
	/* MPU rules at bootup:
	 * MPRR0 is set to machine <R-X> SOG + ROM
	 * MPRR1 is set to machine <---> gap
	 * MPRR2 is set to machine <RWX> SRAM
	 *
	 * Sboot is placed to the end of SRAM. Set sboot code area
	 * non-writable to make it impossible for sboot to load an image
	 * on top of itself. These rules will be replaced in mpu_bootstrap. */

	/* <RWX> up to sboot start. */
	cmrt_mpu_write_region(2, cmrt_mpu_encode_region(raw->text_start, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_MODE_WRITABLE | MPU_MODE_EXECUTABLE));
	/* <R-X> for sboot text. */
	cmrt_mpu_write_region(3, cmrt_mpu_encode_region(raw->text_end, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_MODE_EXECUTABLE));
	/* <R--> for sboot rodata. */
	cmrt_mpu_write_region(4, cmrt_mpu_encode_region(raw->rodata_end, MPU_PRIVILEGE_M, MPU_MODE_READABLE));
	/* <RW-> up to RAM end. */
	cmrt_mpu_write_region(5, cmrt_mpu_encode_region(RAM_END, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_MODE_WRITABLE));
}

void undo_sboot_bootstrap(void)
{
	/* Revert the MPU rules from sboot_bootstrap() when sboot is not needed
	 * to be able to load as big perso as possible (to use all of SRAM). */
	uint32_t region = cmrt_mpu_encode_region(RAM_END, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_MODE_WRITABLE | MPU_MODE_EXECUTABLE);
	cmrt_mpu_write_region(2, region);
	cmrt_mpu_write_region(5, 0);
	cmrt_mpu_write_region(4, 0);
	cmrt_mpu_write_region(3, 0);
}

static int mpu_bootstrap(const cmrt_raw_footer_t *tb, const cmrt_raw_footer_t *sv)
{
	if ((tb != NULL && tb->text_start == 0u) || sv == NULL || sv->text_start == 0u) {
		/* This really should not happen unless we have a bug. */
		return -EINVAL;
	}
	if (RUN_IN_RAM(sv) && /* if sv is in ROM tb must be in ROM, too */
	    ((sv->text_start < IMAGE_RAM_END) ||
	     (tb != NULL && tb->text_start < IMAGE_RAM_END))) {
		/* CONFIG_RISCV_MACHINERAM_SIZE is too small. */
		return -ENOMEM;
	}
	/*
	 * We will overwrite current rules, and that might lock SRAM out
	 * completely, so start filling the MPU with RWX entries for M.
	 */
	uint32_t region = cmrt_mpu_encode_region(RAM_END, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_MODE_WRITABLE | MPU_MODE_EXECUTABLE);
	for (int i = 3; i < CONFIG_CMRT_MPU_NUM_REGIONS; i++) {
		cmrt_mpu_write_region(i, region);
	}

	/*
	 * Machine privilege MPU configuration.
	 */

	/* <R-X> up to machine ROM end. */
	int index = 0;
	cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(MACHINE_ROM_END, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_MODE_EXECUTABLE | MPU_START_OF_RANGE | MPU_LOCKED));
#if ROM_END > MACHINE_ROM_END
	/* <R--> up to ROM end. */
	cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(ROM_END, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_LOCKED));
#endif
	/* <---> up to the SRAM start. */
	cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(RAM_BASE, MPU_PRIVILEGE_M, MPU_LOCKED));

	/* Tboot text and rodata if it is in SRAM. */
	if (tb != NULL && RUN_IN_RAM(tb)) {
		if (sv->text_start < tb->rodata_end) {
			/* TBOOT_OFFSET is too small. */
			return -ENOMEM;
		}
		/* <RW-> up to tboot start. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(tb->text_start, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_MODE_WRITABLE | MPU_LOCKED));
		/* <R-X> for tboot text. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(tb->text_end, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_MODE_EXECUTABLE | MPU_LOCKED));
		/* <R--> for tboot rodata. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(tb->rodata_end, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_LOCKED));
	}
	/* Supervisor text and rodata if it is in SRAM. */
	if (RUN_IN_RAM(sv)) {
		/* <RW-> up to supervisor start. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(sv->text_start, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_MODE_WRITABLE | MPU_LOCKED));
		/* <R--> up to Supervisor rodata end. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(sv->rodata_end, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_LOCKED));
	}
	/* Wipe out any temp entries left. */
	for (int i = CONFIG_CMRT_MPU_NUM_REGIONS - 1; i > index; i--) {
		cmrt_mpu_write_region(i, 0);
	}
	/* <RW-> for the rest of SRAM. */
	cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(RAM_END, MPU_PRIVILEGE_M, MPU_MODE_READABLE | MPU_MODE_WRITABLE | MPU_LOCKED));

	/*
	 * Supervisor privilege MPU configuration.
	 */

	if (RUN_IN_RAM(sv)) {
		/* <---> up to start of SRAM. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(RAM_BASE, MPU_PRIVILEGE_S, MPU_START_OF_RANGE | MPU_LOCKED));
	} else {
		if (sv->text_start < (uint32_t)MACHINE_ROM_END) {
			/* Invalid build configuration. */
			return -ENOMEM;
		}
		/* <---> up to the start of Supervisor ROM. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(MACHINE_ROM_END, MPU_PRIVILEGE_S, MPU_START_OF_RANGE | MPU_LOCKED));
		/* <R-X> for Supervisor text. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(sv->text_end, MPU_PRIVILEGE_S, MPU_MODE_READABLE | MPU_MODE_EXECUTABLE | MPU_LOCKED));
		/* <R--> for Supervisor rodata and for z_data_copy. */
		uint32_t data_end = sv->rodata_end + sv->data_end - sv->data_start;
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(data_end, MPU_PRIVILEGE_S, MPU_MODE_READABLE | MPU_LOCKED));
		/* <---> up to start of SRAM. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(RAM_BASE, MPU_PRIVILEGE_S, MPU_LOCKED));
	}
	/* <RW-> for the PKE RAM. */
	cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(PKE_RAM_END, MPU_PRIVILEGE_S, MPU_MODE_WRITABLE | MPU_MODE_READABLE | MPU_LOCKED));
	/* <---> for all machine privilege SRAM. */
	if (RUN_IN_ROM(sv)) {
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(sv->data_start, MPU_PRIVILEGE_S, MPU_LOCKED));
	} else {
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(sv->text_start, MPU_PRIVILEGE_S, MPU_LOCKED));
		/* <R-X> for Supervisor text. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(sv->text_end, MPU_PRIVILEGE_S, MPU_MODE_READABLE | MPU_MODE_EXECUTABLE | MPU_LOCKED));
		/* <R--> for Supervisor rodata. */
		cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(sv->rodata_end, MPU_PRIVILEGE_S, MPU_MODE_READABLE | MPU_LOCKED));
	}
	/* <RW-> for the rest of SRAM. */
	cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(RAM_END, MPU_PRIVILEGE_S, MPU_MODE_READABLE | MPU_MODE_WRITABLE | MPU_LOCKED));

	/*
	 * User privilege MPU configuration
	 */
	/* <---> up to the start of Supervisor text. */
	cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(sv->text_start, MPU_PRIVILEGE_U, MPU_START_OF_RANGE | MPU_LOCKED));
	/* <---> Rest of SRAM is not accessible by default. */
	cmrt_mpu_write_region(index++, cmrt_mpu_encode_region(RAM_END, MPU_PRIVILEGE_U, 0));

	(void)index; /* silence coverity about the last index++ being unused */
	return 0;
}

int fboot_tboot_start(void)
{
	if (has_tboot()) {
		if (!has_supervisor()) {
			/* Jump to tboot image in machine mode. */
			int res = tboot();
			/* Reset back to fboot permissions for loading the
			 * supervisor image. It may be signed by a different
			 * root and we need to reset KDC derive path. */
			cmrt_clear_container_context();
			cmrt_omc_close(fboot_permissions(NULL, false));
			/* Return back to sboot. */
			return res;
		}
		LOG_INF("Tboot must run before loading supervisor");
		return -EFAULT;
	}
	LOG_INF("Tboot has not been loaded");
	return -ENOENT;
}

int fboot_supervisor_start(void)
{
	if (!has_supervisor()) {
		LOG_INF("Supervisor has not been loaded");
		return -ENOENT;
	}
	/* We have supervisor set always and possibly tboot. */
	int res = mpu_bootstrap(has_tboot() ? &tb_raw : NULL, &sv_raw);
	if (res != 0) {
		LOG_INF("MPU bootstrap returned %d", res);
		return res;
	}
	/*
	 * Can't return to sboot at this point anymore. MPU settings
	 * have been applied and would prohibit sboot execution.
	 * Any failures must either be handled here or ignored.
	 */
#ifdef CONFIG_CMRT_PMU
	res = fboot_verify_bb(true);
	if (res != 0) {
		LOG_INF("Boot bypass setup returned %d", res);
	}
#endif
	res = supervisor_permissions(true);
	if (res != 0) {
		LOG_INF("Setting permissions returned %d", res);
	}
	cmrt_raw_image_init(&sv_raw);

	LOG_INF("Starting OS from %p", supervisor);
	return start_supervisor(supervisor);
}
