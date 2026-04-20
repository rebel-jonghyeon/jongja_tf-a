/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <fboot.h>
#include <sboot.h>
#include <syscalls.h>
#ifdef CONFIG_WDT_CMRT
#include <drivers/watchdog.h>
#endif
#ifdef CONFIG_CMRT_CALIPTRA_SUPPORT
#include "caliptra.h"
#endif

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

const static char version_info[] __version = SBOOT_VERSION_INFO;

#include <rebel_h.h>
#include <rebel_h_gpt.h>
#include <rebel_h_integrity.h>
#include "sac_custom.h"
#include "dma.h"
#include "dma_reg.h"
#include "cmu.h"
#include "dwc_ssi.h"
#include "uart.h"
#include "emergency.h"

#define SYSREG_ROT_PRIVATE			(0x1E00210000ULL)
#define PAD_ROT						(0x6A8)
#define EMERGENCY_DOWNLOAD			(0x1)

#define OM_STAT						(0x0)
#define OM_MASK						(0x7)
#define PCIE_OPTION					(0x4248)
#define CM7_CPU_PCIE_OPTION			(0x6E48)
#define ENABLE_CPU					(0x1)
#define PCIE_ISOLATION				(0x20000000U)

#define SECURE_OTP_BOOT				(0x1)
#define SECURE_XIP_BOOT				(0x3)
#define NORMAL_BOOT					(0x5)
#define RECOVERY_BOOT				(0x6)
#define TEST_BOOT					(0x7)

#define TBOOT_S_DEST_ADDR			(0x1006A00)
#define TBOOT_P0_DEST_ADDR			(0x1FF8000000ULL)
#define TBOOT_P1_DEST_ADDR			(0x1FF8230000ULL)
/* Copy TBOOT_P1 footer to CMRT sram because of PCIe sram size limit */
#define TBOOT_P1_FOOTER_DEST_ADDR	TBOOT_S_DEST_ADDR

#define PCIE_SUB_CTRL_INST			(0x1E08180000ULL)
#define SFR_PHY_CFG_0_REG			(0x20EC)
#define SFR_PHY_CFG_102_REG			(0x1138)
#define SFR_PHY_CFG_103_REG			(0x113C)
#define SFR_PHY_CFG_104_REG			(0x1140)
#define PHY_SRAM_EXT_LD_DONE		(0x20)

#define PHY_SRAM_INIT_DONE			(0x1)
#define WAIT_PCIE_PHY_SRAM_INIT_DONE(sfr)								\
	cmrt_sac_set_base(NULL, GET_SAC_BASE(PCIE_SUB_CTRL_INST + (sfr)));	\
	do {																\
		cmrt_wdt_feed();											\
	} while (!(sys_read32(GET_SAC_R_CPU_DATA(sfr)) & PHY_SRAM_INIT_DONE))

#define PCIE_PHY0_CFG_REG			(0x215C)
#define PCIE_PHY1_CFG_REG			(0x112C)
#define PCIE_PHY2_CFG_REG			(0x1130)
#define PCIE_PHY3_CFG_REG			(0x1134)

#define SYSREG_PCIE_BASE			(0x1E08110000ULL)
#define MUX_CR_PARA_SEL				(0x644)
#define MUX_CR_PARA_SEL_SEPARATE	(0x1)
#define MUX_CR_PARA_SEL_BROADCAST	(0x0)

#define SRAM_INTEGRITY_CHECK_DONE	(0xAAAAAAAAU)

#define SAC_EXT_ADDR_WIDTH_HI_MASK	(0xFF)

enum sboot_s_boot_sequence {
	NOT_STARTED,
	INIT_LOG,
	HW_INIT,
	CHECK_EMERGENCY_DOWNLOAD,
	RUN_EMERGENCY_DOWNLOAD,
	LOAD_AND_CHECK_TBOOT_P0,
	RESET_RELEASE_CM7,
	WAIT_CM7_RESET_DONE,
	LOAD_AND_CHECK_TBOOT_P1,
	NOTIFY_CM7_PHY_RESET_DONE,
	LOAD_AND_CHECK_TBOOT_S,
	RETURN_TO_FBOOT_S,
};

extern uint32_t fboot_supervisor_clear(void);
extern int fboot_supervisor_start(void);

struct dma_block_config img_info[] = {
	/* Sboot_n default info */
	{
	},
	/* Tboot_s default info */
	{
		.dest_address = TBOOT_S_DEST_ADDR,
	},
	/* tboot_n default info */
	{
	},
	/* Tboot_p0 default info */
	{
		.dest_address = TBOOT_P0_DEST_ADDR,
	},
	/* Tboot_p1 default info */
	{
		.dest_address = TBOOT_P1_DEST_ADDR,
	},
	/* Tboot_u default info */
	{
	},
	/* CP0_BL31 default info */
	{
	},
	/* CP0_FREERTOS default info */
	{
	},
	/* CP1_BL31 default info */
	{
	},
	/* CP1_FREERTOS default info */
	{
	},
	/* Tboot_p1_footer default info */
	{
	},
};

int copy_image(uint32_t img_type, uint32_t length, struct dma_block_config img_info[])
{
	/*
	 * TBOOT_S and footer will be copied in CMRT sram
	 * TBOOT_P0 and footer will be copied in BLK_PCIE intmem,
	 * then footer will be copied from intmem to CMRT sram
	 * TBOOT_P1 will be copied in BLK_PCIE intmem, footer will be in CMRT sram
	 */
	if (img_type == IMG_TBOOT_P0) {
		sboot_dma_config(&img_info[img_type]);
		sboot_dma_start();
		sboot_dma_xfer_done();
		return 0;
	} else if (img_type == IMG_TBOOT_P1) {
		uint64_t img_footer_addr = img_info[img_type].source_address + length - sizeof(uint32_t);

		cmrt_sac_set_base(NULL, GET_SAC_BASE(img_footer_addr));
		uint32_t img_footer_length = sys_read32(GET_SAC_R_CPU_DATA(img_footer_addr));

		if (length != TBOOT_P1_SRAM_MAX * 2 + img_footer_length) {
			return -EINVAL;
		}
		img_info[img_type].block_size = TBOOT_P1_SRAM_MAX;

		cmrt_sac_set_base(NULL, GET_SAC_BASE(PHY0_APB2CR_PARA_PCIE + MUX_SWITCH));
		int value = sys_read32(GET_SAC_R_CPU_DATA(MUX_SWITCH));

		sboot_dma_config(&img_info[img_type]);
		sboot_dma_start();
		sboot_dma_xfer_done();

		uint64_t base = PHY0_APB2CR_PARA_PCIE + MUX_SWITCH;

		cmrt_sac_set_base(NULL, GET_SAC_BASE(base));
		sys_write32(value | MUX_VALUE, GET_SAC_R_CPU_DATA(base));
		img_info[img_type].source_address += img_info[img_type].block_size;

		sboot_dma_config(&img_info[img_type]);
		sboot_dma_start();
		sboot_dma_xfer_done();

		base = PHY0_APB2CR_PARA_PCIE + MUX_SWITCH;
		cmrt_sac_set_base(NULL, GET_SAC_BASE(base));
		sys_write32(value, GET_SAC_R_CPU_DATA(base));

		img_info[IMG_TBOOT_P1_FOOTER].block_size = img_footer_length;
		img_info[IMG_TBOOT_P1_FOOTER].source_address = img_info[img_type].source_address
														+ img_info[img_type].block_size;

		return 0;
	} else if (img_type == IMG_TBOOT_S) {
		uint64_t src = img_info[IMG_TBOOT_S].source_address;
		int res = 0;

		if ((src >> 32) > 0) {
			cmrt_sac_set_base(NULL, GET_SAC_BASE(src));

			cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);

			if (!cmrt_is_valid(dmac)) {
				return -ENODEV;
			}

			res = cmrt_dmac_data(dmac, GET_SAC_OFFSET(src),
								 img_info[IMG_TBOOT_S].dest_address, length, 0);
			cmrt_dmac_close(dmac);

			return res;
		} else {
			return -EINVAL;
		}
	} else {
		return -EINVAL;
	}
}

static void disable_timer(void)
{
	const struct device *wdt = device_get_binding(DT_LABEL(DT_ALIAS(watchdog0)));

	if (wdt) {
		(void)wdt_disable(wdt);
	}
}

static uint64_t check_condition(void)
{
	cmrt_sac_set_base(NULL, GET_SAC_BASE(CPMU_PRIVATE + OM_STAT));
	uint32_t bootmode = sys_read32(GET_SAC_R_CPU_DATA(OM_STAT)) & OM_MASK;

	if (bootmode != SECURE_OTP_BOOT && bootmode != SECURE_XIP_BOOT) {
		LOG_ERR("Not expected boot mode: %d", bootmode);
		disable_timer();
		while (1)
			__asm__("wfi");
	}

	return get_chiplet_id();
}

void hw_init(uint64_t chiplet_id)
{
	sac_set_config(SAC_EXT_ADDR_WIDTH_HI_MASK);

	cmu_init(chiplet_id);
	if (chiplet_id == CHIPLET_PRIMARY) {
		sboot_dma_init();
		dwc_ssi_config();
		gpt_init();
	}
}

void cm7_release_reset(void)
{
	uint64_t base = CPMU_PRIVATE;
	uint32_t val;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base + PCIE_OPTION));
	val = sys_read32(GET_SAC_R_CPU_DATA(base + PCIE_OPTION));
	val &= ~PCIE_ISOLATION;
	sys_write32(val, GET_SAC_R_CPU_DATA(base + PCIE_OPTION));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base + CM7_CPU_PCIE_OPTION));
	sys_write32(ENABLE_CPU, GET_SAC_R_CPU_DATA(base + CM7_CPU_PCIE_OPTION));
}

#ifdef CONFIG_WDT_CMRT
void cmrt_wdt_feed(void)
{
	(void)wdt_cmrt_feed(NULL, 0);
}
#else
void cmrt_wdt_feed(void)
{
	;
}
#endif

void cm7_wait_reset_done(void)
{
	WAIT_PCIE_PHY_SRAM_INIT_DONE(PCIE_PHY0_CFG_REG);
	WAIT_PCIE_PHY_SRAM_INIT_DONE(PCIE_PHY1_CFG_REG);
	WAIT_PCIE_PHY_SRAM_INIT_DONE(PCIE_PHY2_CFG_REG);
	WAIT_PCIE_PHY_SRAM_INIT_DONE(PCIE_PHY3_CFG_REG);
}

void cm7_notify_phy_load_done(void)
{
	uint64_t base = PCIE_SUB_CTRL_INST;
	uint32_t val;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base + SFR_PHY_CFG_0_REG));
	val = sys_read32(GET_SAC_R_CPU_DATA(base + SFR_PHY_CFG_0_REG));
	sys_write32(val | PHY_SRAM_EXT_LD_DONE, GET_SAC_R_CPU_DATA(base + SFR_PHY_CFG_0_REG));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base + SFR_PHY_CFG_102_REG));
	val = sys_read32(GET_SAC_R_CPU_DATA(base + SFR_PHY_CFG_102_REG));
	sys_write32(val | PHY_SRAM_EXT_LD_DONE, GET_SAC_R_CPU_DATA(base + SFR_PHY_CFG_102_REG));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base + SFR_PHY_CFG_103_REG));
	val = sys_read32(GET_SAC_R_CPU_DATA(base + SFR_PHY_CFG_103_REG));
	sys_write32(val | PHY_SRAM_EXT_LD_DONE, GET_SAC_R_CPU_DATA(base + SFR_PHY_CFG_103_REG));

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base + SFR_PHY_CFG_104_REG));
	val = sys_read32(GET_SAC_R_CPU_DATA(base + SFR_PHY_CFG_104_REG));
	sys_write32(val | PHY_SRAM_EXT_LD_DONE, GET_SAC_R_CPU_DATA(base + SFR_PHY_CFG_104_REG));
}

void cm7_pcie_phy_para_sel(bool broadcast)
{
	cmrt_sac_set_base(NULL, GET_SAC_BASE(SYSREG_PCIE_BASE + MUX_CR_PARA_SEL));
	if (broadcast)
		sys_write32(MUX_CR_PARA_SEL_BROADCAST, GET_SAC_R_CPU_DATA(SYSREG_PCIE_BASE + MUX_CR_PARA_SEL));
	else
		sys_write32(MUX_CR_PARA_SEL_SEPARATE, GET_SAC_R_CPU_DATA(SYSREG_PCIE_BASE + MUX_CR_PARA_SEL));
}

int main(void)
{
	cmrt_set_boot_status(SBOOT_RUNNING_ID, SBOOT_RUNNING_ID);
	LOG_INF("Sboot is running");

	uint64_t chiplet_id = check_condition();

	BOOT_LOG(ROT, SBOOT_S, INIT_LOG);
	INIT_BOOT_LOG(chiplet_id);
	UPDATE_RESET_LOG;

	hw_init(chiplet_id);

	extern int z_clock_hw_cycles_per_sec;

#ifdef CONFIG_WDT_CMRT
	/* It's possible to change the clock frequency here in sboot
	 * The watchdog driver uses this value in wdt_install_timeout.
	 * As an example set it to the same value it already has.
	 */
	z_clock_hw_cycles_per_sec = CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC;
	/* Possibly define new watchdog timeout and feed it. */
	const struct device *wdt = device_get_binding(DT_LABEL(DT_ALIAS(watchdog0)));

	if (wdt) {
#if CONFIG_CMRT_SBOOT_WATCHDOG_TIMEOUT_MS > 0
		struct wdt_timeout_cfg cfg = { .window = { .max = CONFIG_CMRT_SBOOT_WATCHDOG_TIMEOUT_MS } };
		(void)wdt_install_timeout(wdt, &cfg);
		(void)wdt_setup(wdt, 0);
#endif
		(void)wdt_cmrt_feed(NULL, 0);
	}
#endif

	cmrt_sac_set_base(NULL, GET_SAC_BASE(SYSREG_ROT_PRIVATE + PAD_ROT));
	if (sys_read32(GET_SAC_R_CPU_DATA(PAD_ROT)) == EMERGENCY_DOWNLOAD) {
		BOOT_LOG(ROT, SBOOT_S, RUN_EMERGENCY_DOWNLOAD);
		emergency_download();
	}

	if (chiplet_id != CHIPLET_PRIMARY) {
		start_image(IMG_TBOOT_S, copy_image, img_info,
					fboot_supervisor_clear,
					fboot_supervisor_start);

		disable_timer();
		while (1)
			__asm__("wfi");

		/* Never touch here */
		__asm__("j .");
	}

#if IS_ENABLED(CMRT_SIC_BOOT_CONTROL)
	/* A placeholder to change the boot flow. CMRT has issued fboot_reset
	 * with info written to the SIC boot control register. This makes it
	 * possible to change the logic to boot to a secondary image, etc.
	 */
	uint32_t boot_control = cmrt_read_reg(CMRT_SIC_BASE, R_BOOT_CONTROL);

	if (boot_control != 0) {
		LOG_INF("SIC boot control: 0x%08x", boot_control);
		/* Sboot could clear the register here to avoid possible
		 * boot loop. However, we keep the value for fboot_reset_info
		 * system call to return the value to the supervisor, too.
		 */
	}
#endif
#ifdef CONFIG_CMRT_DATASTORE
	/* Sample code for using a datastore key in image decryption.
	 * Fboot will use this key if datastore key source is set in footer.
	 * MAKE SURE NOT TO USE THIS KEY IN PRODUCTION!
	 */
	LOG_INF("Writing static decryption key to datastore");
	static const uint8_t ds_key[KDC_KEY_SIZE] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
	(void)fboot_data_store_write("CMRT_IMAGE_KEY_SRC_DS", sizeof("CMRT_IMAGE_KEY_SRC_DS") - 1,
									ds_key, sizeof(ds_key), false);
	/* Supervisor has permission to use and update the key. */
	(void)fboot_data_store_grant("CMRT_IMAGE_KEY_SRC_DS", sizeof("CMRT_IMAGE_KEY_SRC_DS") - 1,
									DS_ALL_ROOTS | DS_S_WRITE | DS_S_EXECUTE, -1, false);
#endif
	if (start_image(IMG_TBOOT_P0, copy_image, img_info, NULL, NULL) != 0) {
		handling_img_error(write_flash_256b);
	}

	cm7_release_reset();

	if (get_is_pcie_phy_sram_load() == IS_PHY_SRAM_LOAD) {
		cm7_wait_reset_done();

		cm7_pcie_phy_para_sel(true);
		if (start_image(IMG_TBOOT_P1, copy_image, img_info, NULL, NULL) != 0) {
			handling_img_error(write_flash_256b);
		}
		cm7_pcie_phy_para_sel(false);

		cm7_notify_phy_load_done();
	}

	/* Try the primary image location. */
	if (start_image(IMG_TBOOT_S, copy_image, img_info,
					fboot_supervisor_clear,
					fboot_supervisor_start) != 0) {
		handling_img_error(write_flash_256b);
	}

	/* Never touch here */
	disable_timer();
	__asm__("j .");

	return 0;
}
