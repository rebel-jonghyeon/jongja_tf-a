/*
 * Copyright (c) 2022-2023, Intel Corporation. All rights reserved.
<<<<<<< HEAD
=======
 * Copyright (c) 2024-2025, Altera Corporation. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include <arch_helpers.h>
#include <common/debug.h>
#include <drivers/cadence/cdns_sdmmc.h>
#include <drivers/delay_timer.h>
#include <drivers/mmc.h>
#include <lib/mmio.h>
#include <lib/utils.h>

<<<<<<< HEAD
/* Card busy and present */
#define CARD_BUSY					1
#define CARD_NOT_BUSY					0

/* 500 ms delay to read the RINST register */
#define DELAY_MS_SRS_READ				500
#define DELAY_RES					10

/* SRS12 error mask */
#define SRS12_ERR_MASK					0xFFFF8000

/* Check DV dfi_init val=0 */
#define IO_MASK_END_DATA				0x0

/* Check DV dfi_init val=2; DDR Mode */
#define IO_MASK_END_DATA_DDR				0x2
#define IO_MASK_START_DATA				0x0
#define DATA_SELECT_OE_END_DATA				0x1

#define TIMEOUT						100000

/* General define */
#define SDHC_REG_MASK					UINT_MAX
#define SD_HOST_BLOCK_SIZE				0x200
#define DTCVVAL_DEFAULT_VAL				0xE
#define CDMMC_DMA_MAX_BUFFER_SIZE			64*1024
#define CDNSMMC_ADDRESS_MASK				U(0x0f)
#define CONFIG_CDNS_DESC_COUNT				8

=======
>>>>>>> upstream_import/upstream_v2_14_1
void cdns_init(void);
int cdns_send_cmd(struct mmc_cmd *cmd);
int cdns_set_ios(unsigned int clk, unsigned int width);
int cdns_prepare(int lba, uintptr_t buf, size_t size);
int cdns_read(int lba, uintptr_t buf, size_t size);
int cdns_write(int lba, uintptr_t buf, size_t size);

const struct mmc_ops cdns_sdmmc_ops = {
	.init			= cdns_init,
	.send_cmd		= cdns_send_cmd,
	.set_ios		= cdns_set_ios,
	.prepare		= cdns_prepare,
	.read			= cdns_read,
	.write			= cdns_write,
};
<<<<<<< HEAD

struct cdns_sdmmc_params cdns_params;
struct cdns_sdmmc_combo_phy sdmmc_combo_phy_reg;
struct cdns_sdmmc_sdhc sdmmc_sdhc_reg;
#ifdef CONFIG_DMA_ADDR_T_64BIT
struct cdns_idmac_desc cdns_desc[CONFIG_CDNS_DESC_COUNT];
#else
struct cdns_idmac_desc cdns_desc[CONFIG_CDNS_DESC_COUNT] __aligned(32);
#endif
=======
void sd_host_adma_prepare(struct cdns_idmac_desc *desc_ptr, uintptr_t buf,
			  size_t size);
struct cdns_sdmmc_params cdns_params;
struct cdns_sdmmc_combo_phy sdmmc_combo_phy_reg;
struct cdns_sdmmc_sdhc sdmmc_sdhc_reg;
struct cdns_idmac_desc cdns_desc[CONFIG_CDNS_DESC_COUNT] __aligned(8);
>>>>>>> upstream_import/upstream_v2_14_1

bool data_cmd;

int cdns_wait_ics(uint16_t timeout, uint32_t cdn_srs_res)
{
	/* Clock for sdmclk and sdclk */
	uint32_t count = 0;
	uint32_t data = 0;

	/* Wait status command response ready */
	do {
		data = mmio_read_32(cdn_srs_res);
		count++;
<<<<<<< HEAD
=======

		/* delay 300us to prevent CPU polling too frequently */
		udelay(300);
>>>>>>> upstream_import/upstream_v2_14_1
		if (count >= timeout) {
			return -ETIMEDOUT;
		}
	} while ((data & (1 << SDMMC_CDN_ICS)) == 0);

	return 0;
}

<<<<<<< HEAD
int cdns_busy(void)
{
	unsigned int data;

	data = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS09);
	return (data & STATUS_DATA_BUSY) ? CARD_BUSY : CARD_NOT_BUSY;
}

int cdns_vol_reset(void)
{
	/* Reset embedded card */
	mmio_write_32((MMC_REG_BASE + SDHC_CDNS_SRS10), (7 << SDMMC_CDN_BVS) | (1 << SDMMC_CDN_BP));
	udelay(250);
	mmio_write_32((MMC_REG_BASE + SDHC_CDNS_SRS10), (7 << SDMMC_CDN_BVS) | (0 << SDMMC_CDN_BP));
	udelay(500);

	/* Turn on supply voltage */
	/* BVS = 7, BP = 1, BP2 only in UHS2 mode */
	mmio_write_32((MMC_REG_BASE + SDHC_CDNS_SRS10), (7 << SDMMC_CDN_BVS) | (1 << SDMMC_CDN_BP));
	udelay(250);
	return 0;
}

void cdns_set_sdmmc_var(struct cdns_sdmmc_combo_phy *combo_phy_reg,
	struct cdns_sdmmc_sdhc *sdhc_reg)
=======
void cdns_set_sdmmc_var(struct cdns_sdmmc_combo_phy *combo_phy_reg,
			struct cdns_sdmmc_sdhc *sdhc_reg)
>>>>>>> upstream_import/upstream_v2_14_1
{
	/* Values are taken by the reference of cadence IP documents */
	combo_phy_reg->cp_clk_wr_delay = 0;
	combo_phy_reg->cp_clk_wrdqs_delay = 0;
<<<<<<< HEAD
	combo_phy_reg->cp_data_select_oe_end = 0;
	combo_phy_reg->cp_dll_bypass_mode = 1;
	combo_phy_reg->cp_dll_locked_mode = 0;
	combo_phy_reg->cp_dll_start_point = 0;
	combo_phy_reg->cp_gate_cfg_always_on = 1;
	combo_phy_reg->cp_io_mask_always_on = 0;
	combo_phy_reg->cp_io_mask_end = 0;
=======
	combo_phy_reg->cp_data_select_oe_end = 1;
	combo_phy_reg->cp_dll_bypass_mode = 1;
	combo_phy_reg->cp_dll_locked_mode = 0;
	combo_phy_reg->cp_dll_start_point = 254;
	combo_phy_reg->cp_gate_cfg_always_on = 1;
	combo_phy_reg->cp_io_mask_always_on = 0;
	combo_phy_reg->cp_io_mask_end = 5;
>>>>>>> upstream_import/upstream_v2_14_1
	combo_phy_reg->cp_io_mask_start = 0;
	combo_phy_reg->cp_rd_del_sel = 52;
	combo_phy_reg->cp_read_dqs_cmd_delay = 0;
	combo_phy_reg->cp_read_dqs_delay = 0;
	combo_phy_reg->cp_sw_half_cycle_shift = 0;
	combo_phy_reg->cp_sync_method = 1;
	combo_phy_reg->cp_underrun_suppress = 1;
	combo_phy_reg->cp_use_ext_lpbk_dqs = 1;
	combo_phy_reg->cp_use_lpbk_dqs = 1;
	combo_phy_reg->cp_use_phony_dqs = 1;
	combo_phy_reg->cp_use_phony_dqs_cmd = 1;

	sdhc_reg->sdhc_extended_rd_mode = 1;
	sdhc_reg->sdhc_extended_wr_mode = 1;
<<<<<<< HEAD
	sdhc_reg->sdhc_hcsdclkadj = 0;
	sdhc_reg->sdhc_idelay_val = 0;
	sdhc_reg->sdhc_rdcmd_en = 1;
	sdhc_reg->sdhc_rddata_en = 1;
	sdhc_reg->sdhc_rw_compensate = 9;
	sdhc_reg->sdhc_sdcfsh = 0;
	sdhc_reg->sdhc_sdcfsl = 1;
=======
	sdhc_reg->sdhc_hcsdclkadj = 3;
	sdhc_reg->sdhc_idelay_val = 0;
	sdhc_reg->sdhc_rdcmd_en = 1;
	sdhc_reg->sdhc_rddata_en = 1;
	sdhc_reg->sdhc_rw_compensate = 10;
	sdhc_reg->sdhc_sdcfsh = 0;
	sdhc_reg->sdhc_sdcfsl = 0;
>>>>>>> upstream_import/upstream_v2_14_1
	sdhc_reg->sdhc_wrcmd0_dly = 1;
	sdhc_reg->sdhc_wrcmd0_sdclk_dly = 0;
	sdhc_reg->sdhc_wrcmd1_dly = 0;
	sdhc_reg->sdhc_wrcmd1_sdclk_dly = 0;
<<<<<<< HEAD
	sdhc_reg->sdhc_wrdata0_dly = 1;
=======
	sdhc_reg->sdhc_wrdata0_dly = 0;
>>>>>>> upstream_import/upstream_v2_14_1
	sdhc_reg->sdhc_wrdata0_sdclk_dly = 0;
	sdhc_reg->sdhc_wrdata1_dly = 0;
	sdhc_reg->sdhc_wrdata1_sdclk_dly = 0;
}

<<<<<<< HEAD
static int cdns_program_phy_reg(struct cdns_sdmmc_combo_phy *combo_phy_reg,
	struct cdns_sdmmc_sdhc *sdhc_reg)
{
	uint32_t value = 0;
	int ret = 0;
=======
int cdns_program_phy_reg(struct cdns_sdmmc_combo_phy *combo_phy_reg,
				struct cdns_sdmmc_sdhc *sdhc_reg)
{
	uint32_t value = 0;
	int ret = 0;
	uint32_t timeout = 0;

	/* HRS00 - Software Reset */
	mmio_write_32((cdns_params.reg_base + SDHC_CDNS_HRS00), SDHC_CDNS_HRS00_SWR);

	/* Waiting for SDHC_CDNS_HRS00_SWR reset */
	timeout = TIMEOUT;
	do {
		udelay(250);
		if (--timeout <= 0) {
			NOTICE(" SDHC Software Reset failed!!!\n");
			panic();
		}
	} while (((mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS00) &
		SDHC_CDNS_HRS00_SWR) == 1));

	/* Step 1, switch on DLL_RESET */
	value = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS09);
	value &= ~SDHC_PHY_SW_RESET;
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS09, value);
>>>>>>> upstream_import/upstream_v2_14_1

	/* program PHY_DQS_TIMING_REG */
	value = (CP_USE_EXT_LPBK_DQS(combo_phy_reg->cp_use_ext_lpbk_dqs)) |
		(CP_USE_LPBK_DQS(combo_phy_reg->cp_use_lpbk_dqs)) |
		(CP_USE_PHONY_DQS(combo_phy_reg->cp_use_phony_dqs)) |
		(CP_USE_PHONY_DQS_CMD(combo_phy_reg->cp_use_phony_dqs_cmd));
<<<<<<< HEAD
	ret = cdns_sdmmc_write_phy_reg(MMC_REG_BASE + SDHC_CDNS_HRS04,
			COMBO_PHY_REG + PHY_DQS_TIMING_REG, MMC_REG_BASE +
			SDHC_CDNS_HRS05, value);
	if (ret != 0) {
=======
	ret = cdns_sdmmc_write_phy_reg(cdns_params.reg_base + SDHC_CDNS_HRS04,
					COMBO_PHY_REG + PHY_DQS_TIMING_REG,
					cdns_params.reg_base + SDHC_CDNS_HRS05, value);
	if (ret != 0U) {
>>>>>>> upstream_import/upstream_v2_14_1
		return ret;
	}

	/* program PHY_GATE_LPBK_CTRL_REG */
	value = (CP_SYNC_METHOD(combo_phy_reg->cp_sync_method)) |
		(CP_SW_HALF_CYCLE_SHIFT(combo_phy_reg->cp_sw_half_cycle_shift)) |
		(CP_RD_DEL_SEL(combo_phy_reg->cp_rd_del_sel)) |
		(CP_UNDERRUN_SUPPRESS(combo_phy_reg->cp_underrun_suppress)) |
		(CP_GATE_CFG_ALWAYS_ON(combo_phy_reg->cp_gate_cfg_always_on));
<<<<<<< HEAD
	ret = cdns_sdmmc_write_phy_reg(MMC_REG_BASE + SDHC_CDNS_HRS04,
			COMBO_PHY_REG + PHY_GATE_LPBK_CTRL_REG, MMC_REG_BASE +
			SDHC_CDNS_HRS05, value);
	if (ret != 0) {
		return ret;
	}

	/* program PHY_DLL_MASTER_CTRL_REG */
	value = (CP_DLL_BYPASS_MODE(combo_phy_reg->cp_dll_bypass_mode))
			| (CP_DLL_START_POINT(combo_phy_reg->cp_dll_start_point));
	ret = cdns_sdmmc_write_phy_reg(MMC_REG_BASE + SDHC_CDNS_HRS04,
			COMBO_PHY_REG + PHY_DLL_MASTER_CTRL_REG, MMC_REG_BASE
			+ SDHC_CDNS_HRS05, value);
	if (ret != 0) {
=======
	ret = cdns_sdmmc_write_phy_reg(cdns_params.reg_base + SDHC_CDNS_HRS04,
				 COMBO_PHY_REG + PHY_GATE_LPBK_CTRL_REG,
				 cdns_params.reg_base + SDHC_CDNS_HRS05, value);
	if (ret != 0U) {
		return -ret;
	}

	/* program PHY_DLL_MASTER_CTRL_REG */
	value = (CP_DLL_BYPASS_MODE(combo_phy_reg->cp_dll_bypass_mode)) | (2 << 20) |
		(CP_DLL_START_POINT(combo_phy_reg->cp_dll_start_point));
	ret = cdns_sdmmc_write_phy_reg(cdns_params.reg_base + SDHC_CDNS_HRS04,
					COMBO_PHY_REG + PHY_DLL_MASTER_CTRL_REG,
					cdns_params.reg_base + SDHC_CDNS_HRS05, value);
	if (ret != 0U) {
>>>>>>> upstream_import/upstream_v2_14_1
		return ret;
	}

	/* program PHY_DLL_SLAVE_CTRL_REG */
<<<<<<< HEAD
	value = (CP_READ_DQS_CMD_DELAY(combo_phy_reg->cp_read_dqs_cmd_delay))
		| (CP_CLK_WRDQS_DELAY(combo_phy_reg->cp_clk_wrdqs_delay))
		| (CP_CLK_WR_DELAY(combo_phy_reg->cp_clk_wr_delay))
		| (CP_READ_DQS_DELAY(combo_phy_reg->cp_read_dqs_delay));
	ret = cdns_sdmmc_write_phy_reg(MMC_REG_BASE + SDHC_CDNS_HRS04,
			COMBO_PHY_REG + PHY_DLL_SLAVE_CTRL_REG, MMC_REG_BASE
			+ SDHC_CDNS_HRS05, value);
	if (ret != 0) {
=======
	value = (CP_READ_DQS_CMD_DELAY(combo_phy_reg->cp_read_dqs_cmd_delay)) |
		(CP_CLK_WRDQS_DELAY(combo_phy_reg->cp_clk_wrdqs_delay)) |
		(CP_CLK_WR_DELAY(combo_phy_reg->cp_clk_wr_delay)) |
		(CP_READ_DQS_DELAY(combo_phy_reg->cp_read_dqs_delay));
	ret = cdns_sdmmc_write_phy_reg(cdns_params.reg_base + SDHC_CDNS_HRS04,
					COMBO_PHY_REG + PHY_DLL_SLAVE_CTRL_REG,
					cdns_params.reg_base + SDHC_CDNS_HRS05, value);
	if (ret != 0U) {
>>>>>>> upstream_import/upstream_v2_14_1
		return ret;
	}

	/* program PHY_CTRL_REG */
<<<<<<< HEAD
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS04, COMBO_PHY_REG
			+ PHY_CTRL_REG);
	value = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS05);

	/* phony_dqs_timing=0 */
	value &= ~(CP_PHONY_DQS_TIMING_MASK << CP_PHONY_DQS_TIMING_SHIFT);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS05, value);

	/* switch off DLL_RESET */
	do {
		value = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS09);
		value |= SDHC_PHY_SW_RESET;
		mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS09, value);
		value = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS09);
=======
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS04, COMBO_PHY_REG + PHY_CTRL_REG);
	value = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS05);

	/* phony_dqs_timing=0 */
	value &= ~(CP_PHONY_DQS_TIMING_MASK << CP_PHONY_DQS_TIMING_SHIFT);
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS05, value);

	/* switch off DLL_RESET */
	do {
		value = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS09);
		value |= SDHC_PHY_SW_RESET;
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS09, value);
		value = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS09);
>>>>>>> upstream_import/upstream_v2_14_1
	/* polling PHY_INIT_COMPLETE */
	} while ((value & SDHC_PHY_INIT_COMPLETE) != SDHC_PHY_INIT_COMPLETE);

	/* program PHY_DQ_TIMING_REG */
<<<<<<< HEAD
	combo_phy_reg->cp_io_mask_end = 0U;
	value = (CP_IO_MASK_ALWAYS_ON(combo_phy_reg->cp_io_mask_always_on))
		| (CP_IO_MASK_END(combo_phy_reg->cp_io_mask_end))
		| (CP_IO_MASK_START(combo_phy_reg->cp_io_mask_start))
		| (CP_DATA_SELECT_OE_END(combo_phy_reg->cp_data_select_oe_end));

	ret = cdns_sdmmc_write_phy_reg(MMC_REG_BASE + SDHC_CDNS_HRS04,
			COMBO_PHY_REG + PHY_DQ_TIMING_REG, MMC_REG_BASE
			+ SDHC_CDNS_HRS05, value);
	if (ret != 0) {
		return ret;
	}
=======
	value = (CP_IO_MASK_ALWAYS_ON(combo_phy_reg->cp_io_mask_always_on)) |
		(CP_IO_MASK_END(combo_phy_reg->cp_io_mask_end)) |
		(CP_IO_MASK_START(combo_phy_reg->cp_io_mask_start)) |
		(CP_DATA_SELECT_OE_END(combo_phy_reg->cp_data_select_oe_end));

	ret = cdns_sdmmc_write_phy_reg(cdns_params.reg_base + SDHC_CDNS_HRS04,
				 COMBO_PHY_REG + PHY_DQ_TIMING_REG,
				 cdns_params.reg_base + SDHC_CDNS_HRS05, value);
	if (ret != 0U) {
		return ret;
	}

	value = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS09);
	value |= (HRS_09_EXTENDED_RD_MODE | HRS_09_EXTENDED_WR_MODE |
		HRS_09_RDCMD_EN | HRS_09_RDDATA_EN);
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS09, value);

	value = 0;
	value = SDHC_HCSDCLKADJ(HRS_10_HCSDCLKADJ_VAL);
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS10, value);

	value = 0;
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS16, value);

	value = (10 << 16);
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS07, value);

>>>>>>> upstream_import/upstream_v2_14_1
	return 0;
}

int cdns_read(int lba, uintptr_t buf, size_t size)
{
<<<<<<< HEAD
	inv_dcache_range(buf, size);

=======
	return 0;
}

int cdns_write(int lba, uintptr_t buf, size_t size)
{
>>>>>>> upstream_import/upstream_v2_14_1
	return 0;
}

void cdns_init(void)
{
	/* Dummy function pointer for cdns_init. */
}

int cdns_prepare(int dma_start_addr, uintptr_t dma_buff, size_t size)
{
<<<<<<< HEAD
	data_cmd = true;
	struct cdns_idmac_desc *desc;
	uint32_t desc_cnt, i;
	uint64_t desc_base;

	assert(((dma_buff & CDNSMMC_ADDRESS_MASK) == 0) &&
			(cdns_params.desc_size > 0) &&
			((MMC_REG_BASE & MMC_BLOCK_MASK) == 0) &&
			((cdns_params.desc_base & MMC_BLOCK_MASK) == 0) &&
			((cdns_params.desc_size & MMC_BLOCK_MASK) == 0));

	flush_dcache_range(dma_buff, size);

	desc_cnt = (size + (CDMMC_DMA_MAX_BUFFER_SIZE) - 1) / (CDMMC_DMA_MAX_BUFFER_SIZE);
	assert(desc_cnt * sizeof(struct cdns_idmac_desc) < cdns_params.desc_size);

	if (desc_cnt > CONFIG_CDNS_DESC_COUNT) {
		ERROR("Requested data transfer length %ld is greater than configured length %d",
				size, (CONFIG_CDNS_DESC_COUNT * CDMMC_DMA_MAX_BUFFER_SIZE));
		return -EINVAL;
	}

	desc = (struct cdns_idmac_desc *)cdns_params.desc_base;
	desc_base = (uint64_t)desc;
	i = 0;

	while ((i + 1) < desc_cnt) {
		desc->attr = ADMA_DESC_ATTR_VALID | ADMA_DESC_TRANSFER_DATA;
		desc->reserved = 0;
		desc->len = MAX_64KB_PAGE;
		desc->addr_lo = (dma_buff & UINT_MAX) + (CDMMC_DMA_MAX_BUFFER_SIZE * i);
#if CONFIG_DMA_ADDR_T_64BIT == 1
		desc->addr_hi = (dma_buff >> 32) & 0xffffffff;
#endif
		size -= CDMMC_DMA_MAX_BUFFER_SIZE;
		desc++;
		i++;
	}

	desc->attr = ADMA_DESC_ATTR_VALID | ADMA_DESC_TRANSFER_DATA |
			ADMA_DESC_ATTR_END;
	desc->reserved = 0;
	desc->len = size;
#if CONFIG_DMA_ADDR_T_64BIT == 1
	desc->addr_lo = (dma_buff & UINT_MAX) + (CDMMC_DMA_MAX_BUFFER_SIZE * i);
	desc->addr_hi = (dma_buff >> 32) & UINT_MAX;
#else
	desc->addr_lo = (dma_buff & UINT_MAX);
#endif

	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS22, (uint32_t)desc_base);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS23, (uint32_t)(desc_base >> 32));
	flush_dcache_range(cdns_params.desc_base,
				desc_cnt * CDMMC_DMA_MAX_BUFFER_SIZE);

	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS01,
			((512 << BLOCK_SIZE) | ((size/512) << BLK_COUNT_CT) | SDMA_BUF));
	return 0;
}

static void cdns_host_set_clk(int clk)
{
	uint32_t ret = 0;
	uint32_t sdclkfsval = 0;
	uint32_t dtcvval = DTCVVAL_DEFAULT_VAL;

	sdclkfsval = (cdns_params.clk_rate / 2000) / clk;
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS11, 0);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS11, (dtcvval << SDMMC_CDN_DTCV) |
			(sdclkfsval << SDMMC_CDN_SDCLKFS) | (1 << SDMMC_CDN_ICE));

	ret = cdns_wait_ics(5000, MMC_REG_BASE + SDHC_CDNS_SRS11);
	if (ret != 0U) {
		ERROR("Waiting SDMMC_CDN_ICS timeout");
	}

	/* Enable DLL reset */
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS09, mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS09) &
			~SDHC_DLL_RESET_MASK);
	/* Set extended_wr_mode */
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS09, (mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS09)
			& SDHC_EXTENDED_WR_MODE_MASK) | (1 << EXTENDED_WR_MODE));
	/* Release DLL reset */
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS09, mmio_read_32(MMC_REG_BASE
			+ SDHC_CDNS_HRS09) | 1);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS09, mmio_read_32(MMC_REG_BASE
			+ SDHC_CDNS_HRS09) | (3 << RDCMD_EN));

	do {
		mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS09);
	} while (~mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS09) & (1 << 1));

	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS11, (dtcvval << SDMMC_CDN_DTCV) |
	(sdclkfsval << SDMMC_CDN_SDCLKFS) | (1 << SDMMC_CDN_ICE) | (1 << SDMMC_CDN_SDCE));
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS13, UINT_MAX);
=======
	struct cdns_idmac_desc *cdns_desc_data;
	assert(((dma_buff & CDNSMMC_ADDRESS_MASK) == 0) &&
	 (cdns_params.desc_size > 0));

	cdns_desc_data = (struct cdns_idmac_desc *)cdns_params.desc_base;
	sd_host_adma_prepare(cdns_desc_data, dma_buff, size);

	return 0;
}

void cdns_host_set_clk(uint32_t clk)
{
	uint32_t ret = 0;
	uint32_t sdclkfsval = 0;
	uint32_t dtcvval = 0xE;

	sdclkfsval = (cdns_params.sdmclk / 2) / clk;
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS11, 0);
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS11,
			(dtcvval << SDMMC_CDN_DTCV) | (sdclkfsval << SDMMC_CDN_SDCLKFS) |
			(1 << SDMMC_CDN_ICE));

	ret = cdns_wait_ics(5000, cdns_params.reg_base + SDHC_CDNS_SRS11);
	if (ret != 0) {
		ERROR("Waiting ICS timeout");
	}
	/* Enable DLL reset */
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS09,
		mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS09) & ~0x00000001);
	/* Set extended_wr_mode */
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS09,
		(mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS09) & 0xFFFFFFF7) |
			(1 << EXTENDED_WR_MODE));
	/* Release DLL reset */
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS09,
		mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS09) | PHY_SW_RESET_EN);
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_HRS09,
		mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS09) | RDCMD_EN);

	do {
		mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS09);
	} while (~mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS09) &
		(PHY_INIT_COMPLETE_BIT));

	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS11, (dtcvval << SDMMC_CDN_DTCV) |
			(sdclkfsval << SDMMC_CDN_SDCLKFS) | (1 << SDMMC_CDN_ICE) |
			(1 << SDMMC_CDN_SDCE));

	ret = cdns_wait_ics(5000, cdns_params.reg_base + SDHC_CDNS_SRS11);
	if (ret != 0)
		ERROR("Waiting ICS timeout");

	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS13, 0xFFFFFFFF);
>>>>>>> upstream_import/upstream_v2_14_1
}

int cdns_set_ios(unsigned int clk, unsigned int width)
{
<<<<<<< HEAD

	switch (width) {
	case MMC_BUS_WIDTH_1:
		mmio_write_32((MMC_REG_BASE + SDHC_CDNS_SRS10), LEDC_OFF);
		break;
	case MMC_BUS_WIDTH_4:
		mmio_write_32((MMC_REG_BASE + SDHC_CDNS_SRS10), DTW_4BIT);
		break;
	case MMC_BUS_WIDTH_8:
		mmio_write_32((MMC_REG_BASE + SDHC_CDNS_SRS10), EDTW_8BIT);
		break;
=======
	uint32_t _status = 0;

	_status = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS10);
	switch (width) {
	case MMC_BUS_WIDTH_1:
		_status &= ~(BIT4);
		break;

	case MMC_BUS_WIDTH_4:
		_status |= BIT4;
		break;

	case MMC_BUS_WIDTH_8:
		_status |= BIT8;
		break;

>>>>>>> upstream_import/upstream_v2_14_1
	default:
		assert(0);
		break;
	}
<<<<<<< HEAD
=======
	mmio_write_32((cdns_params.reg_base + SDHC_CDNS_SRS10), _status);
>>>>>>> upstream_import/upstream_v2_14_1
	cdns_host_set_clk(clk);

	return 0;
}

int cdns_sdmmc_write_sd_host_reg(uint32_t addr, uint32_t data)
{
	uint32_t value = 0;

	value = mmio_read_32(addr);
	value &= ~SDHC_REG_MASK;
	value |= data;
	mmio_write_32(addr, value);
	value = mmio_read_32(addr);
<<<<<<< HEAD
=======

>>>>>>> upstream_import/upstream_v2_14_1
	if (value != data) {
		ERROR("SD host address is not set properly\n");
		return -ENXIO;
	}

	return 0;
}

<<<<<<< HEAD
int cdns_write(int lba, uintptr_t buf, size_t size)
{
	return 0;
}

static int cdns_init_hrs_io(struct cdns_sdmmc_combo_phy *combo_phy_reg,
	struct cdns_sdmmc_sdhc *sdhc_reg)
{
	uint32_t value = 0;
	int ret = 0;

	/* program HRS09, register 42 */
	value = (SDHC_RDDATA_EN(sdhc_reg->sdhc_rddata_en))
		| (SDHC_RDCMD_EN(sdhc_reg->sdhc_rdcmd_en))
		| (SDHC_EXTENDED_WR_MODE(sdhc_reg->sdhc_extended_wr_mode))
		| (SDHC_EXTENDED_RD_MODE(sdhc_reg->sdhc_extended_rd_mode));
	ret = cdns_sdmmc_write_sd_host_reg(MMC_REG_BASE + SDHC_CDNS_HRS09, value);
	if (ret != 0) {
		ERROR("Program HRS09 failed");
		return ret;
	}

	/* program HRS10, register 43 */
	value = (SDHC_HCSDCLKADJ(sdhc_reg->sdhc_hcsdclkadj));
	ret = cdns_sdmmc_write_sd_host_reg(MMC_REG_BASE + SDHC_CDNS_HRS10, value);
	if (ret != 0) {
		ERROR("Program HRS10 failed");
		return ret;
	}

	/* program HRS16, register 48 */
	value = (SDHC_WRDATA1_SDCLK_DLY(sdhc_reg->sdhc_wrdata1_sdclk_dly))
		| (SDHC_WRDATA0_SDCLK_DLY(sdhc_reg->sdhc_wrdata0_sdclk_dly))
		| (SDHC_WRCMD1_SDCLK_DLY(sdhc_reg->sdhc_wrcmd1_sdclk_dly))
		| (SDHC_WRCMD0_SDCLK_DLY(sdhc_reg->sdhc_wrcmd0_sdclk_dly))
		| (SDHC_WRDATA1_DLY(sdhc_reg->sdhc_wrdata1_dly))
		| (SDHC_WRDATA0_DLY(sdhc_reg->sdhc_wrdata0_dly))
		| (SDHC_WRCMD1_DLY(sdhc_reg->sdhc_wrcmd1_dly))
		| (SDHC_WRCMD0_DLY(sdhc_reg->sdhc_wrcmd0_dly));
	ret = cdns_sdmmc_write_sd_host_reg(MMC_REG_BASE + SDHC_CDNS_HRS16, value);
	if (ret != 0) {
		ERROR("Program HRS16 failed");
		return ret;
	}

	/* program HRS07, register 40 */
	value = (SDHC_RW_COMPENSATE(sdhc_reg->sdhc_rw_compensate))
		| (SDHC_IDELAY_VAL(sdhc_reg->sdhc_idelay_val));
	ret = cdns_sdmmc_write_sd_host_reg(MMC_REG_BASE + SDHC_CDNS_HRS07, value);
	if (ret != 0) {
		ERROR("Program HRS07 failed");
		return ret;
	}

	return ret;
}

static int cdns_hc_set_clk(struct cdns_sdmmc_params *cdn_sdmmc_dev_mode_params)
{
	uint32_t ret = 0;
	uint32_t dtcvval, sdclkfsval;

	dtcvval = DTC_VAL;
	sdclkfsval = 0;

	if ((cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == SD_DS) ||
		(cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == SD_UHS_SDR12) ||
		(cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == EMMC_SDR_BC)) {
		sdclkfsval = 4;
	} else if ((cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == SD_HS) ||
		(cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == SD_UHS_SDR25) ||
		(cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == SD_UHS_DDR50) ||
		(cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == EMMC_SDR)) {
		sdclkfsval = 2;
	} else if ((cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == SD_UHS_SDR50) ||
		(cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == EMMC_DDR) ||
		(cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == EMMC_HS400) ||
		(cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == EMMC_HS400es)) {
		sdclkfsval = 1;
	} else if ((cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == SD_UHS_SDR104) ||
		(cdn_sdmmc_dev_mode_params->cdn_sdmmc_dev_mode == EMMC_HS200)) {
		sdclkfsval = 0;
	}

	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS11, 0);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS11, (dtcvval << SDMMC_CDN_DTCV) |
		(sdclkfsval << SDMMC_CDN_SDCLKFS) | (1 << SDMMC_CDN_ICE));
	ret = cdns_wait_ics(5000, MMC_REG_BASE + SDHC_CDNS_SRS11);
	if (ret != 0U) {
		ERROR("Waiting SDMMC_CDN_ICS timeout");
		return ret;
	}

	/* Enable DLL reset */
	mmio_write_32((MMC_REG_BASE + SDHC_CDNS_HRS09), mmio_read_32(MMC_REG_BASE
			+ SDHC_CDNS_HRS09) & ~SDHC_DLL_RESET_MASK);
	/* Set extended_wr_mode */
	mmio_write_32((MMC_REG_BASE + SDHC_CDNS_HRS09),
	(mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS09) &	SDHC_EXTENDED_WR_MODE_MASK) |
			(1 << EXTENDED_WR_MODE));
	/* Release DLL reset */
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS09, mmio_read_32(MMC_REG_BASE
			+ SDHC_CDNS_HRS09) | 1);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS09, mmio_read_32(MMC_REG_BASE
			+ SDHC_CDNS_HRS09) | (3 << RDCMD_EN));
	do {
		mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS09);
	} while (~mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS09) & (1 << 1));

	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS11, (dtcvval << SDMMC_CDN_DTCV) |
		(sdclkfsval << SDMMC_CDN_SDCLKFS) | (1 << SDMMC_CDN_ICE) | (1 << SDMMC_CDN_SDCE));

	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS13, UINT_MAX);
	return 0;
=======


void sd_host_oper_mode(enum sd_opr_modes opr_mode)
{

	uint32_t reg = 0;

	switch (opr_mode) {
	case SD_HOST_OPR_MODE_HV4E_0_SDMA_32:
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS10);
		reg &= ~(DMA_SEL_BIT);
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS10, reg);
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS15);
		reg &= ~(HV4E | BIT_AD_64);
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS15, reg);
		break;

	case SD_HOST_OPR_MODE_HV4E_1_SDMA_32:
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS10);
		reg &= ~(DMA_SEL_BIT);
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS10, reg);
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS15);
		reg &= ~(HV4E | BIT_AD_64);
		reg |= (HV4E);
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS15, reg);
		break;

	case SD_HOST_OPR_MODE_HV4E_1_SDMA_64:
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS10);
		reg &= ~(DMA_SEL_BIT);
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS10, reg);
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS15);
		reg |= (HV4E | BIT_AD_64);
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS15, reg);
		break;

	case SD_HOST_OPR_MODE_HV4E_0_ADMA_32:
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS10);
		reg &= ~(DMA_SEL_BIT);
		reg |= DMA_SEL_BIT_2;
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS10, reg);
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS15);
		reg &= ~(HV4E | BIT_AD_64);
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS15, reg);
		break;

	case SD_HOST_OPR_MODE_HV4E_0_ADMA_64:
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS10);
		reg &= ~(DMA_SEL_BIT);
		reg |= DMA_SEL_BIT_3;
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS10, reg);
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS15);
		reg &= ~(HV4E | BIT_AD_64);
		reg |= BIT_AD_64;
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS15, reg);
		break;

	case SD_HOST_OPR_MODE_HV4E_1_ADMA_32:
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS10);
		reg &= ~(DMA_SEL_BIT);
		reg |= DMA_SEL_BIT_2;
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS10, reg);
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS15);
		reg &= ~(HV4E | BIT_AD_64);
		reg |= HV4E;
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS15, reg);
		break;

	case SD_HOST_OPR_MODE_HV4E_1_ADMA_64:
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS10);
		reg &= ~(DMA_SEL_BIT);
		reg |= DMA_SEL_BIT_2;
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS10, reg);
		reg = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS15);
		reg |= (HV4E | BIT_AD_64);
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS15, reg);
		break;
	}
}

void card_reset(bool power_enable)
{
	uint32_t reg_value = 0;

	/* Reading SRS10 value before writing */
	reg_value = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS10);

	if (power_enable == true) {
		reg_value &= ~((7 << SDMMC_CDN_BVS) | (1 << SDMMC_CDN_BP));
		reg_value = ((1 << SDMMC_CDN_BVS) | (1 << SDMMC_CDN_BP));
	} else {
		reg_value &= ~((7 << SDMMC_CDN_BVS) | (1 << SDMMC_CDN_BP));
	}
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS10, reg_value);
}

void high_speed_enable(bool mode)
{

	uint32_t reg_value = 0;
	/* Reading SRS10 value before writing */
	reg_value = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS10);

	if (mode == true) {
		reg_value |= HS_EN;
	} else {
		reg_value &= ~HS_EN;
	}

	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS10, reg_value);
>>>>>>> upstream_import/upstream_v2_14_1
}

int cdns_reset(void)
{
<<<<<<< HEAD
	uint32_t data = 0;
	uint32_t count = 0;
	uint32_t value = 0;

	value = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS11);
	value &= ~(0xFFFF);
	value |= 0x0;
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS11, value);
	udelay(500);

	/* Software reset */
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS00, 1);
	/* Wait status command response ready */
	do {
		data = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS00);
		count++;
		if (count >= 5000) {
			return -ETIMEDOUT;
		}
	/* Wait for HRS00.SWR */
	} while ((data & 1) == 1);

	/* Step 1, switch on DLL_RESET */
	value = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_HRS09);
	value &= ~SDHC_PHY_SW_RESET;
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_HRS09, value);
=======
	volatile uint32_t data = 0;
	uint32_t count = 0;

	/* Software reset */
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS11, SRS11_SRFA);
	/* Wait status command response ready */
	do {
		data = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_HRS00);
		count++;
		if (count >= CDNS_TIMEOUT) {
			return -ETIMEDOUT;
		}
	/* Wait for SRS11 */
	} while (((SRS11_SRFA_CHK(data)) & 1) == 1);
>>>>>>> upstream_import/upstream_v2_14_1

	return 0;
}

<<<<<<< HEAD
int cdns_sd_host_init(struct cdns_sdmmc_combo_phy *mmc_combo_phy_reg,
struct cdns_sdmmc_sdhc *mmc_sdhc_reg)
=======
void sdmmc_host_init(bool uhs2_enable)
{
	uint32_t timeout;

	/* SRS11 - Host Control  default value set */
	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS11, 0x0);

	/* Waiting for detect card */
	timeout = TIMEOUT;
	do {
		udelay(250);
		if (--timeout <= 0) {
			NOTICE(" SDHC Card Detecion failed!!!\n");
			panic();
		}
	} while (((mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS09) & CHECK_CARD) == 0));

	/* UHS2 Host setting */
	if (uhs2_enable == true) {
	/** need to implement*/
	}

	/* Card reset */

	card_reset(1);
	udelay(2500);
	card_reset(0);
	udelay(2500);
	card_reset(1);
	udelay(2500);

	/* Enable Interrupt Flags*/
	mmio_write_32((cdns_params.reg_base + SDHC_CDNS_SRS13), ~0);
	high_speed_enable(true);
}

int cdns_sd_host_init(struct cdns_sdmmc_combo_phy *mmc_combo_phy_reg,
		      struct cdns_sdmmc_sdhc *mmc_sdhc_reg)
>>>>>>> upstream_import/upstream_v2_14_1
{
	int ret = 0;

	ret = cdns_reset();
<<<<<<< HEAD
	if (ret != 0) {
=======
	if (ret != 0U) {
>>>>>>> upstream_import/upstream_v2_14_1
		ERROR("Program phy reg init failed");
		return ret;
	}

	ret = cdns_program_phy_reg(&sdmmc_combo_phy_reg, &sdmmc_sdhc_reg);
<<<<<<< HEAD
	if (ret != 0) {
		ERROR("Program phy reg init failed");
		return ret;
	}

	ret = cdns_init_hrs_io(&sdmmc_combo_phy_reg, &sdmmc_sdhc_reg);
	if (ret != 0) {
		ERROR("Program init for HRS reg is failed");
		return ret;
	}

	ret = cdns_sd_card_detect();
	if (ret != 0) {
		ERROR("SD card does not detect");
		return ret;
	}

	ret = cdns_vol_reset();
	if (ret != 0) {
		ERROR("eMMC card reset failed");
		return ret;
	}

	ret = cdns_hc_set_clk(&cdns_params);
	if (ret != 0) {
		ERROR("hc set clk failed");
		return ret;
	}
=======
	if (ret != 0U) {
		ERROR("Program phy reg init failed");
		return ret;
	}
	sdmmc_host_init(0);
	cdns_host_set_clk(100000);

	sd_host_oper_mode(SD_HOST_OPR_MODE_HV4E_0_ADMA_64);
>>>>>>> upstream_import/upstream_v2_14_1

	return 0;
}

<<<<<<< HEAD
void cdns_srs10_value_toggle(uint8_t write_val, uint8_t prev_val)
{
	uint32_t data_op = 0U;

	data_op = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS10);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS10, (data_op & (prev_val << 0)));
	mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS10);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS10, data_op | (write_val << 0));
}

void cdns_srs11_srs15_config(uint32_t srs11_val, uint32_t srs15_val)
{
	uint32_t data = 0U;

	data = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS11);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS11, (data | srs11_val));
	data = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS15);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS15, (data | srs15_val));
}

int cdns_send_cmd(struct mmc_cmd *cmd)
{
	uint32_t op = 0, ret = 0;
	uint8_t write_value = 0, prev_val = 0;
	uint32_t value;
	int32_t timeout;
	uint32_t cmd_indx;
	uint32_t status = 0, srs15_val = 0, srs11_val = 0;
	uint32_t status_check = 0;

	assert(cmd);
	cmd_indx = (cmd->cmd_idx) << COM_IDX;

	if (data_cmd) {
		switch (cmd->cmd_idx) {
		case SD_SWITCH:
			op = DATA_PRESENT;
			write_value = ADMA2_32 | DT_WIDTH;
			prev_val = ADMA2_32 | DT_WIDTH;
			cdns_srs10_value_toggle(write_value, prev_val);
			srs11_val = READ_CLK | SDMMC_CDN_ICE | SDMMC_CDN_ICS | SDMMC_CDN_SDCE;
			srs15_val = BIT_AD_64 | HV4E | V18SE;
			cdns_srs11_srs15_config(srs11_val, srs15_val);
			break;

		case SD_WRITE_SINGLE_BLOCK:
		case SD_READ_SINGLE_BLOCK:
			op = DATA_PRESENT;
			write_value = ADMA2_32 | HS_EN | DT_WIDTH | LEDC;
			prev_val = ADMA2_32 | HS_EN | DT_WIDTH;
			cdns_srs10_value_toggle(write_value, prev_val);
			srs15_val = PVE | BIT_AD_64 | HV4E | SDR104_MODE | V18SE;
			srs11_val = READ_CLK | SDMMC_CDN_ICE | SDMMC_CDN_ICS | SDMMC_CDN_SDCE;
			cdns_srs11_srs15_config(srs11_val, srs15_val);
			mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS00, SAAR);
			break;

		case SD_WRITE_MULTIPLE_BLOCK:
		case SD_READ_MULTIPLE_BLOCK:
			op = DATA_PRESENT | AUTO_CMD_EN | MULTI_BLK_READ;
			write_value = ADMA2_32 | HS_EN | DT_WIDTH | LEDC;
			prev_val = ADMA2_32 | HS_EN | DT_WIDTH;
			cdns_srs10_value_toggle(write_value, prev_val);
			srs15_val = PVE | BIT_AD_64 | HV4E | SDR104_MODE | V18SE;
			srs11_val = READ_CLK | SDMMC_CDN_ICE | SDMMC_CDN_ICS | SDMMC_CDN_SDCE;
			cdns_srs11_srs15_config(srs11_val, srs15_val);
			mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS00, SAAR);
			break;

		case SD_APP_SEND_SCR:
			op = DATA_PRESENT;
			write_value = ADMA2_32 | LEDC;
			prev_val = LEDC;
			cdns_srs10_value_toggle(write_value, prev_val);
			srs15_val = BIT_AD_64 | HV4E | V18SE;
			srs11_val = READ_CLK | SDMMC_CDN_ICE | SDMMC_CDN_ICS | SDMMC_CDN_SDCE;
			cdns_srs11_srs15_config(srs11_val, srs15_val);
			break;

		case SD_SEND_IF_COND:
			op = DATA_PRESENT | CMD_IDX_CHK_ENABLE;
			write_value = LEDC;
			prev_val = 0x0;
			cdns_srs10_value_toggle(write_value, prev_val);
			srs15_val = HV4E;
			srs11_val = READ_CLK | SDMMC_CDN_ICE | SDMMC_CDN_ICS | SDMMC_CDN_SDCE;
			cdns_srs11_srs15_config(srs11_val, srs15_val);
			break;

		default:
			write_value = LEDC;
			prev_val = 0x0;
			cdns_srs10_value_toggle(write_value, prev_val);
			op = 0;
			break;
		}
	} else {
		switch (cmd->cmd_idx) {
		case SD_GO_IDLE_STATE:
			write_value = LEDC;
			prev_val = 0x0;
			cdns_srs10_value_toggle(write_value, prev_val);
			srs15_val = HV4E;
			srs11_val = SDMMC_CDN_ICE | SDMMC_CDN_ICS | SDMMC_CDN_SDCE;
			cdns_srs11_srs15_config(srs11_val, srs15_val);
			break;

		case SD_ALL_SEND_CID:
			write_value = LEDC;
			prev_val = 0x0;
			cdns_srs10_value_toggle(write_value, prev_val);
			srs15_val = HV4E | V18SE;
			srs11_val = SDMMC_CDN_ICE | SDMMC_CDN_ICS | SDMMC_CDN_SDCE;
			cdns_srs11_srs15_config(srs11_val, srs15_val);
			break;

		case SD_SEND_IF_COND:
			op = CMD_IDX_CHK_ENABLE;
			write_value = LEDC;
			prev_val = 0x0;
			cdns_srs10_value_toggle(write_value, prev_val);
			srs15_val = HV4E;
			srs11_val = READ_CLK | SDMMC_CDN_ICE | SDMMC_CDN_ICS | SDMMC_CDN_SDCE;
			cdns_srs11_srs15_config(srs11_val, srs15_val);
			break;

		case SD_STOP_TRANSMISSION:
			op = CMD_STOP_ABORT_CMD;
			break;

		case SD_SEND_STATUS:
			break;

		case 1:
			cmd->cmd_arg = 0;
			break;

		case SD_SELECT_CARD:
			op = MULTI_BLK_READ;
			break;

		case SD_APP_CMD:
		default:
			write_value = LEDC;
			prev_val = 0x0;
			cdns_srs10_value_toggle(write_value, prev_val);
			op = 0;
			break;
		}
	}

	switch (cmd->resp_type) {
	case MMC_RESPONSE_NONE:
		op |= CMD_READ | MULTI_BLK_READ | DMA_ENABLED | BLK_CNT_EN;
		break;

	case MMC_RESPONSE_R2:
		op |= CMD_READ | MULTI_BLK_READ | DMA_ENABLED | BLK_CNT_EN |
			RES_TYPE_SEL_136 | CMD_CHECK_RESP_CRC;
		break;

	case MMC_RESPONSE_R3:
		op |= CMD_READ | MULTI_BLK_READ | DMA_ENABLED | BLK_CNT_EN |
			RES_TYPE_SEL_48;
		break;

	case MMC_RESPONSE_R1:
		if ((cmd->cmd_idx == SD_WRITE_SINGLE_BLOCK) || (cmd->cmd_idx
			== SD_WRITE_MULTIPLE_BLOCK)) {
			op |= DMA_ENABLED | BLK_CNT_EN | RES_TYPE_SEL_48
			| CMD_CHECK_RESP_CRC | CMD_IDX_CHK_ENABLE;
		} else {
			op |= DMA_ENABLED | BLK_CNT_EN | CMD_READ | RES_TYPE_SEL_48
			| CMD_CHECK_RESP_CRC | CMD_IDX_CHK_ENABLE;
		}
		break;

	default:
		op |= DMA_ENABLED | BLK_CNT_EN | CMD_READ | MULTI_BLK_READ |
			RES_TYPE_SEL_48 | CMD_CHECK_RESP_CRC | CMD_IDX_CHK_ENABLE;
		break;
=======
int cdns_send_cmd(struct mmc_cmd *cmd)
{
	uint32_t cmd_flags = 0;
	uint32_t timeout = 0;
	uint32_t status_check = 0;
	uint32_t mode = 0;
	uint32_t status;

	assert(cmd);

	cmd_flags = CDNS_HOST_CMD_INHIBIT | CDNS_HOST_DATA_INHIBIT;

	if ((cmd->cmd_idx == SD_STOP_TRANSMISSION) && (!data_cmd)) {
		cmd_flags &= ~CDNS_HOST_DATA_INHIBIT;
>>>>>>> upstream_import/upstream_v2_14_1
	}

	timeout = TIMEOUT;
	do {
		udelay(100);
<<<<<<< HEAD
		ret = cdns_busy();
		if (--timeout <= 0) {
			udelay(50);
			panic();
		}
	} while (ret);

	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS12, UINT_MAX);

	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS02, cmd->cmd_arg);
	mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS14, 0x00000000);
	if (cmd_indx == 1)
		mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS03, SDHC_CDNS_SRS03_VALUE);
	else
		mmio_write_32(MMC_REG_BASE + SDHC_CDNS_SRS03, op | cmd_indx);

	timeout = TIMEOUT;
	do {
		udelay(500);
		value = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS12);
	} while (((value & (INT_CMD_DONE | ERROR_INT)) == 0) && (timeout-- > 0));

	timeout = TIMEOUT;

	if (data_cmd) {
		data_cmd = false;
		do {
			udelay(250);
		} while (((value & TRAN_COMP) == 0) && (timeout-- > 0));
	}

	status_check = value & SRS12_ERR_MASK;
	if (status_check != 0U) {
		ERROR("SD host controller send command failed, SRS12 = %x", status);
		return -1;
	}

	if ((op & RES_TYPE_SEL_48) || (op & RES_TYPE_SEL_136)) {
		cmd->resp_data[0] = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS04);
		if (op & RES_TYPE_SEL_136) {
			cmd->resp_data[1] = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS05);
			cmd->resp_data[2] = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS06);
			cmd->resp_data[3] = mmio_read_32(MMC_REG_BASE + SDHC_CDNS_SRS07);
		}
	}

	return 0;
}
=======
		if (--timeout <= 0) {
			udelay(50);
			NOTICE("Timeout occur data and cmd line %x\n",
			 mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS09));
			panic();
		}
	} while ((mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS09) & (cmd_flags)));

	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS12, 0xFFFFFFFF);
	cmd_flags = 0;
	cmd_flags = (cmd->cmd_idx) << COM_IDX;

	if ((cmd->resp_type & MMC_RSP_136) != 0) {
		cmd_flags |= RES_TYPE_SEL_136;
	} else if (((cmd->resp_type & MMC_RSP_48) != 0) &&
			((cmd->resp_type & MMC_RSP_BUSY) != 0)) {
		cmd_flags |= RES_TYPE_SEL_48_B;
	} else if ((cmd->resp_type & MMC_RSP_48) != 0) {
		cmd_flags |= RES_TYPE_SEL_48;
	} else {
		cmd_flags &= ~RES_TYPE_SEL_NO;
	}

	if ((cmd->resp_type & MMC_RSP_CRC) != 0) {
		cmd_flags |= CMD_CHECK_RESP_CRC;
	}

	if ((cmd->resp_type & MMC_RSP_CMD_IDX) != 0) {
		cmd_flags |= CMD_IDX_CHK_ENABLE;
	}

	if ((cmd->cmd_idx == MMC_ACMD(51)) || (cmd->cmd_idx == MMC_CMD(17)) ||
		(cmd->cmd_idx == MMC_CMD(18)) || (cmd->cmd_idx == MMC_CMD(24)) ||
		(cmd->cmd_idx == MMC_CMD(25)) || (cmd->cmd_idx == MMC_CMD(8) &&
		cdns_params.cdn_sdmmc_dev_type == MMC_IS_EMMC)) {
		mmio_write_8((cdns_params.reg_base + DTCV_OFFSET), DTCV_VAL);
		cmd_flags |= DATA_PRESENT;
		mode |= BLK_CNT_EN;

		mode |= (DMA_ENABLED);
		if ((cmd->cmd_idx == SD_WRITE_MULTIPLE_BLOCK) ||
		(cmd->cmd_idx == SD_READ_MULTIPLE_BLOCK)) {
			mode |= (MULTI_BLK_READ);
		} else {
			mode &= ~(MULTI_BLK_READ);
		}
		if ((cmd->cmd_idx == SD_WRITE_MULTIPLE_BLOCK) ||
		(cmd->cmd_idx == SD_WRITE_SINGLE_BLOCK)) {
			mode &= ~CMD_READ;
		} else {
			mode |= CMD_READ;
		}
		mmio_write_16(cdns_params.reg_base + SDHC_CDNS_SRS03, mode);

	} else {
		mmio_write_8((cdns_params.reg_base + DTCV_OFFSET), DTCV_VAL);
	}

	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS02, cmd->cmd_arg);
	mmio_write_16((cdns_params.reg_base + CICE_OFFSET),
		SDHCI_MAKE_CMD(cmd->cmd_idx, cmd_flags));

	timeout = TIMEOUT;

	do {
		udelay(CDNS_TIMEOUT);
		status = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS12);
	} while (((status & (INT_CMD_DONE | ERROR_INT)) == 0) && (timeout-- > 0));

	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS12, (SRS_12_CC_EN));
	status_check = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS12) & 0xffff8000;
	if (status_check != 0U) {
		timeout = TIMEOUT;
		ERROR("SD host controller send command failed, SRS12 = %x", status_check);
		return -1;
	}

	if (!((cmd_flags & RES_TYPE_SEL_NO) == 0)) {
		cmd->resp_data[0] = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS04);
		if ((cmd_flags & RES_TYPE_SEL_NO) == RES_TYPE_SEL_136) {
			cmd->resp_data[1] = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS05);
			cmd->resp_data[2] = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS06);
			cmd->resp_data[3] = mmio_read_32(cdns_params.reg_base + SDHC_CDNS_SRS07);
			/* 136-bit: RTS=01b, Response field R[127:8] - RESP3[23:0],
			 * RESP2[31:0], RESP1[31:0], RESP0[31:0]
			 * Subsystem expects 128 bits response but cadence SDHC sends
			 * 120 bits response from R[127:8]. Bits manupulation to address
			 * the correct responses for the 136 bit response type.
			 */
			cmd->resp_data[3] = ((cmd->resp_data[3] << 8) |
						((cmd->resp_data[2] >> 24) &
						CDNS_CSD_BYTE_MASK));
			cmd->resp_data[2] = ((cmd->resp_data[2] << 8) |
						((cmd->resp_data[1] >> 24) &
						CDNS_CSD_BYTE_MASK));
			cmd->resp_data[1] = ((cmd->resp_data[1] << 8) |
						((cmd->resp_data[0] >> 24) &
						CDNS_CSD_BYTE_MASK));
			cmd->resp_data[0] = (cmd->resp_data[0] << 8);
		}
	}

	mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS12, (SRS_12_CC_EN));

	return 0;
}

void sd_host_adma_prepare(struct cdns_idmac_desc *desc_ptr, uint64_t buf,
			  size_t size)
{
	uint32_t full_desc_cnt = 0;
	uint32_t non_full_desc_cnt = 0;
	uint64_t desc_address;
	uint32_t block_count;
	uint32_t transfer_block_size;

	full_desc_cnt = (size / PAGE_BUFFER_LEN);
	non_full_desc_cnt = (size % PAGE_BUFFER_LEN);
	for (int i = 0; i < full_desc_cnt; i++) {
		desc_ptr->attr = (ADMA_DESC_TRANSFER_DATA | ADMA_DESC_ATTR_VALID);
		desc_ptr->len = 0; // 0 means 64kb page size it will take
		desc_ptr->addr_lo = 0;
#if CONFIG_DMA_ADDR_T_64BIT == 1
		desc_ptr->addr_hi = (uint32_t)((buf >> 32) & 0xffffffff);
#endif
		if (non_full_desc_cnt == 0) {
			desc_ptr->attr |= (ADMA_DESC_ATTR_END);
		}
	buf += PAGE_BUFFER_LEN;
	}

	if (non_full_desc_cnt != 0) {
		desc_ptr->attr =
		(ADMA_DESC_TRANSFER_DATA | ADMA_DESC_ATTR_END | ADMA_DESC_ATTR_VALID);
		desc_ptr->addr_lo = buf & 0xffffffff;
		desc_ptr->len = size;
#if CONFIG_DMA_ADDR_T_64BIT == 1
		desc_ptr->addr_hi = (uint32_t)((buf >> 32) & 0xffffffff);
#endif
		desc_address = (uint64_t)desc_ptr;
		if (size > MMC_MAX_BLOCK_LEN) {
			transfer_block_size = MMC_MAX_BLOCK_LEN;
		} else {
			transfer_block_size = size;
		}

		block_count = (size / transfer_block_size);
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS01,
				((transfer_block_size << BLOCK_SIZE) | SDMA_BUF |
				(block_count << BLK_COUNT_CT)));
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS22,
				(uint32_t)desc_address & 0xFFFFFFFF);
		mmio_write_32(cdns_params.reg_base + SDHC_CDNS_SRS23,
				(uint32_t)(desc_address >> 32 & 0xFFFFFFFF));
	}
}

int cdns_mmc_init(struct cdns_sdmmc_params *params,
		  struct mmc_device_info *info)
{

	int result = 0;

	assert((params != NULL) &&
		((params->reg_base & MMC_BLOCK_MASK) == 0) &&
		((params->desc_size & MMC_BLOCK_MASK) == 0) &&
		((params->reg_pinmux & MMC_BLOCK_MASK) == 0) &&
		((params->reg_phy & MMC_BLOCK_MASK) == 0) &&
		(params->desc_size > 0) &&
		(params->clk_rate > 0) &&
		(params->sdmclk > 0) &&
		((params->bus_width == MMC_BUS_WIDTH_1) ||
		(params->bus_width == MMC_BUS_WIDTH_4) ||
		(params->bus_width == MMC_BUS_WIDTH_8)));

	memcpy(&cdns_params, params, sizeof(struct cdns_sdmmc_params));

	cdns_set_sdmmc_var(&sdmmc_combo_phy_reg, &sdmmc_sdhc_reg);
	result = cdns_sd_host_init(&sdmmc_combo_phy_reg, &sdmmc_sdhc_reg);
	if (result < 0) {
		return result;
	}

	cdns_params.cdn_sdmmc_dev_type = info->mmc_dev_type;
	cdns_params.cdn_sdmmc_dev_mode = SD_DS;

	result = mmc_init(&cdns_sdmmc_ops, params->clk_rate, params->bus_width,
			params->flags, info);

	return result;
}
>>>>>>> upstream_import/upstream_v2_14_1
