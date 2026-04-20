/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include "rl_errors.h"
#include "rl_sizes.h"
#include "rl_utils.h"
#include <rebel_h_platform.h>

#include "pcie_dw.h"
#include "pcie_irq.h"
#include "pcie_dw_iatu.h"
#include "pcie_dw_bar.h"
#include "pcie_dw_msix.h"
#include "pcie_dw_hdma.h"
#include "pcie_subctrl.h"
#include "pcie_snps_phy.h"
#include "pcie_doe.h"
#include "sysreg_pcie_register.h"
#include "sysreg_buscsr_pcie_register.h"
#include "sysreg_buscsr_cp.h"
#include "pcie_rebelh.h"
#include "pmu.h"

#define PCIE_DEBUG_ON 1
#define PCIE_ERR_ON 1
#include "pcie_log.h"

struct pcie_bar_info pcie_ep_bar_info[12] = {
	/* PF BARn */
	{BAR0, BAR0_TARGET_ADDR, SZ_32G, BAR_MASK_RESIZABLE, 0},
	{BAR1, TARGET_ADDR_NONE, 0, BAR_MASK_FIXED, 0},
	{BAR2, BAR2_TARGET_ADDR, SZ_64M, BAR_MASK_PROGRAMMABLE, 0},
	{BAR3, TARGET_ADDR_NONE, 0, BAR_MASK_FIXED, 0},
	{BAR4, BAR4_TARGET_ADDR, SZ_4K, BAR_MASK_PROGRAMMABLE, 0},
	{BAR5, TARGET_ADDR_NONE, SZ_2M, BAR_MASK_PROGRAMMABLE, 0},
	/* VF BARn */
#ifdef __TEST
	{VF_BAR0, BAR0_TARGET_ADDR + DRAM_USER_BASE, SZ_16M, BAR_MASK_RESIZABLE, 0},
#else
	{VF_BAR0, VF_BAR0_TARGET_ADDR, SZ_16G, BAR_MASK_RESIZABLE, 0},
#endif
	{VF_BAR1, TARGET_ADDR_NONE, 0, BAR_MASK_FIXED, 0},
	{VF_BAR2, VF_BAR2_TARGET_ADDR, SZ_64M, BAR_MASK_PROGRAMMABLE, 0},
	{VF_BAR3, TARGET_ADDR_NONE, 0, BAR_MASK_FIXED, 0},
	{VF_BAR4, VF_BAR4_TARGET_ADDR, SZ_4K, BAR_MASK_PROGRAMMABLE, 0},
	{VF_BAR5, TARGET_ADDR_NONE, SZ_8K, BAR_MASK_PROGRAMMABLE, 0}
};

struct pcie_iatu_info pcie_ep_iatu_info = {
	.iatu_num_ib_regions = PCIE_IATU_NUM_REGION,
	.iatu_num_ob_regions = PCIE_IATU_NUM_REGION,
	.iatu_ib_regions_mask = 0,
	.iatu_ob_regions_mask = 0,
};

struct dw_pcie_drv pcie_ep_drv = {
	.bar_info = pcie_ep_bar_info,
	.iatu_info = &pcie_ep_iatu_info,
};

struct pcie_epc dw_pcie_epc;

static void pcie_ep_reset_release(const struct dw_pcie_config *cfg)
{
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	subctrl_base->sfr_power_up_rst_n_ovrd.power_up_rst_n_ovrd = 1;

#ifndef ZEBU
	/* Enable refb clk */
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane0_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane1_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane2_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane3_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane4_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane5_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane6_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane7_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane8_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane9_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane10_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane11_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane12_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane13_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane14_refb_clk_en = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane15_refb_clk_en = 1;

	subctrl_base->sfr_phy_cfg_701_reg.phy_lane0_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane1_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane2_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane3_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane4_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane5_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane6_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_701_reg.phy_lane7_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane8_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane9_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane10_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane11_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane12_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane13_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane14_ref_sel = 1;
	subctrl_base->sfr_phy_cfg_702_reg.phy_lane15_ref_sel = 1;

	/* Check if refclk is being supplied */
	subctrl_base->sfr_phy_cfg_693_reg.phy0_refa_clkdet_en = 1;
	subctrl_base->sfr_phy_cfg_693_reg.phy0_refb_clkdet_en = 1;
	subctrl_base->sfr_phy_cfg_695_reg.phy1_refa_clkdet_en = 1;
	subctrl_base->sfr_phy_cfg_695_reg.phy1_refb_clkdet_en = 1;
	subctrl_base->sfr_phy_cfg_697_reg.phy2_refa_clkdet_en = 1;
	subctrl_base->sfr_phy_cfg_697_reg.phy2_refb_clkdet_en = 1;
	subctrl_base->sfr_phy_cfg_699_reg.phy3_refa_clkdet_en = 1;
	subctrl_base->sfr_phy_cfg_699_reg.phy3_refb_clkdet_en = 1;

	/* perst mask */
	subctrl_base->sfr_perstn_control.pad_perstn_mask = 1;

	pcie_dbg_log("Wait for CLK\n");
	while (!(subctrl_base->sfr_phy_cfg_738_reg.phy0_refa_clkdet_result == 1 &&
			 subctrl_base->sfr_phy_cfg_739_reg.phy1_refa_clkdet_result == 1 &&
			 subctrl_base->sfr_phy_cfg_740_reg.phy2_refa_clkdet_result == 1 &&
			 subctrl_base->sfr_phy_cfg_741_reg.phy3_refa_clkdet_result == 1))
		;

	while (!(subctrl_base->sfr_phy_cfg_738_reg.phy0_refb_clkdet_result == 1 &&
			 subctrl_base->sfr_phy_cfg_739_reg.phy1_refb_clkdet_result == 1 &&
			 subctrl_base->sfr_phy_cfg_740_reg.phy2_refb_clkdet_result == 1 &&
			 subctrl_base->sfr_phy_cfg_741_reg.phy3_refb_clkdet_result == 1))
		;
	pcie_dbg_log("Clk detect done\n");
#endif

	pcie_dbg_log("Wait for PERST_N\n");
	/* Wait PERST_N de-assertion */
	pcie_dbg_log("PCIE EP: wait for perst\n");
	while (!subctrl_base->irq_2.perst_n_rise)
		;
}

static void pcie_ep_hotreset_init(const struct dw_pcie_config *cfg)
{
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;
	volatile struct pmu *pmu = (struct pmu *)CPMU_PRIVATE;

	subctrl_base->sfr_mask_control.core_rst_n_ltssm_enable_mask = 1;

	subctrl_base->sfr_hotreset_control.hotreset_global_mask = 1;
	subctrl_base->sfr_hotreset.global_hotreset = 1;

	subctrl_base->irq_reset.irq_core_rst_n_assert = 1;
	subctrl_base->irq_reset.irq_link_req_rst_not = 1;
	subctrl_base->irq_reset.irq_smlh_req_rst_not = 1;

	pmu->cluster0_noncpu_reset.disable_level2_l2reset = 0;
	pmu->cluster1_noncpu_reset.disable_level2_l2reset = 0;
	__DSB();
	pmu->mask_wdt_reset_request.hotreset_global = 0;
}

static void pcie_ep_config_init(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data)
{
	/* Set max target speed */
	pcie_set_speed(&dw_pcie_epc, PCIE_TARGET_SPEED);

	/* Set lanes */
	pcie_link_setup(cfg);

	/* Set PCIe EQ presets */
	pcie_eq_setup(cfg);

	/* Configure PCIe Capabilities and Extended Capabilities */
	pcie_cap_setup(cfg);

	/* Set lane margin */
	pcie_lane_margin_setup(cfg);

	/* Configure resizable BAR size */
	pcie_set_resizable_bar_size(cfg, BAR0, data->bar_info[BAR0].size);
	pcie_set_resizable_bar_size(cfg, VF_BAR0, data->bar_info[VF_BAR0].size);

	/* LTSSM history store start */
	pcie_subctrl_history_store_config(&dw_pcie_epc, GROUP1_SUBGRP1, G1_SMLH_LTSSM_STATE,
									  HIST_SET_G1_SMLH_LTSSM_STATE(PCIE_LTSSM_STATE_DETECT_ACT));
	pcie_subctrl_history_store_start(&dw_pcie_epc, GROUP1_SUBGRP1, COMPARE_START_MODE);
}

static int32_t pcie_ep_linkup_check(const struct dw_pcie_config *cfg)
{
	uint32_t val;
	uint32_t last_val;

	last_val = pcie_get_ltssm_state(cfg);
	pcie_dbg_log("PCIE EP: LTSSM [0x%x]\n", (unsigned int)last_val);

	while (1) {
		val = pcie_get_ltssm_state(cfg);

		if (last_val != val) {
			pcie_dbg_log("PCIE EP: LTSSM [0x%x]\n", (unsigned int)val);
			last_val = val;
		}

		if (val == PCIE_LTSSM_STATE_L0) {
			pcie_dbg_log("PCIE EP: Linkup Successful [0x%x]\n", (unsigned int)val);
			return RL_OK;
		}
	}

	return RL_ERROR;
}

static void pcie_ep_bar_init(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data)
{
	int32_t i;
	uint8_t num_valid_bar;
	struct pcie_bar_info bar_info;

	num_valid_bar = pcie_get_num_valid_bar(cfg, data);

	pcie_get_bar_info(cfg, data);

	for (i = 0; i < num_valid_bar; i++) {
		if (data->bar_info[i].flags == BAR_NOT_USED)
			continue;

		bar_info = data->bar_info[i];
		pcie_set_bar(cfg, data, &bar_info);

		if ((bar_info.bar_type & BAR_TYPE_MASK) == BAR_TYPE_64)
			i++;
	}
}

static void pcie_ep_vfbar_init(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data)
{
	int32_t i;
	struct pcie_bar_info bar_info;

	pcie_get_vfbar_info(cfg, data);

	for (i = VF_BAR0; i <= VF_BAR5; i++) {
		if (data->bar_info[i].flags == BAR_NOT_USED)
			continue;

		bar_info = data->bar_info[i];
		pcie_set_bar(cfg, data, &bar_info);

		if ((bar_info.bar_type & BAR_TYPE_MASK) == BAR_TYPE_64)
			i++;
	}
}

static void pcie_ep_config_post_init(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data)
{
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;
#ifndef ZEBU_POC
	volatile struct sysreg_buscsr_cp_register *buscsr_cp0 =
		(void *)IP_BLK_PRIV_REG_BAT_BASE + SYSREG_BUSCSR_CP0_REG_OFFSET;
#endif /* ZEBU_POC */
	volatile struct sysreg_buscsr_pcie_register *sysreg_buscsr_base = cfg->sysreg_buscsr_base;

	/* Program BAR and iATU */
	pcie_ep_vfbar_init(cfg, data);
	pcie_ep_bar_init(cfg, data);

	/* Enable MSI-X */
	if (CHIPLET_ID == CHIPLET_ID0)
		pcie_msix_setup(cfg, REBELH_PCIE_MSIX_ADDR);
	else
		pcie_msix_setup(cfg, REBELH_PCIE_MSIX_ADDR + CHIPLET_BASE_ADDRESS);

#ifndef ZEBU_POC
	/* Enable ACP */
	buscsr_cp0->m1_user_ovrd_value.aruser_sfr = 0;
	buscsr_cp0->m1_user_ovrd_value.awuser_sfr = 0;
	buscsr_cp0->m1_user_ovrd_value.aruser_sfr_en = 0xF;
	buscsr_cp0->m1_user_ovrd_value.awuser_sfr_en = 0xF;
	buscsr_cp0->m1_user_ovrd_sel.aruser_ovrd_sel = 1;
	buscsr_cp0->m1_user_ovrd_sel.awuser_ovrd_sel = 1;
#endif /* ZEBU_POC */

	sysreg_buscsr_base->m1_cache_ovrd_value.arcache_sfr = 0xF;
	sysreg_buscsr_base->m1_cache_ovrd_value.awcache_sfr = 0xF;
	sysreg_buscsr_base->m1_cache_ovrd_value.arcache_sfr_en = 0xF;
	sysreg_buscsr_base->m1_cache_ovrd_value.awcache_sfr_en = 0xF;
	sysreg_buscsr_base->m1_cache_ovrd_sel.arcache_ovrd_sel = 0x1;
	sysreg_buscsr_base->m1_cache_ovrd_sel.awcache_ovrd_sel = 0x1;

	/* Enable accessing MEM & I/O space and issuing MEM & I/O request */
	dbi_base->pf0_type0_hdr_status_command_reg.pci_type0_io_en = 1;
	dbi_base->pf0_type0_hdr_status_command_reg.pci_type0_bus_master_en = 1;
	dbi_base->pf0_type0_hdr_status_command_reg.pci_type0_mem_space_en = 1;

	/* Disable PASID support */
	pcie_disable_ext_capability(&dw_pcie_epc, PCI_EXT_CAP_ID_PASID);
	pcie_disable_ext_capability(&dw_pcie_epc, PCI_EXT_CAP_ID_ATS);

	/* History store start */
	pcie_subctrl_history_store_config(&dw_pcie_epc, GROUP2, G2_CFG_NEG_LINK_WIDTH,
									  HIST_SET_G2_CFG_NEG_LINK_WIDTH(NEGO_LINK_WIDTH_16));
	pcie_subctrl_history_store_start(&dw_pcie_epc, GROUP2, COMPARE_START_MODE);

	pcie_subctrl_history_store_config(&dw_pcie_epc, GROUP3, G3_PM_DSTATE, HIST_SET_G3_PM_DSTATE(PM_DSTATE_D0));
	pcie_subctrl_history_store_start(&dw_pcie_epc, GROUP3, COMPARE_START_MODE);

	pcie_subctrl_history_store_config(&dw_pcie_epc, GROUP4, G4_PM_USP_PROT_STATE,
									  HIST_SET_G4_PM_USP_PROT_STATE(USP_PROT_ENTER_L23));
	pcie_subctrl_history_store_start(&dw_pcie_epc, GROUP4, COMPARE_EXIT_MODE);

#ifndef ZEBU_POC
	/* Setup DOE */
	pcie_doe_setup(&dw_pcie_epc, PCIE_DOE_DATA_ADDR);
#endif /* ZEBU_POC */
}

static void pcie_ep_set_base_address(struct dw_pcie_config *cfg)
{
	int32_t i;

	for (i = 0; i < PCIE_IATU_NUM_REGION; i++)
		cfg->iatu_base[i] = cfg->iatu_base[0] + i;

	for (i = 0; i < HDMA_READ_CH0; i++)
		cfg->hdma_base[i] = cfg->hdma_base[0] + i;

	for (i = 0; i < PCIE_VF_NUM_MAX; i++)
		cfg->vf_base[i] = cfg->vf_base[0] + i;

	for (i = 0; i < PCIE_VF_NUM_MAX; i++)
		cfg->vf_msix_tbl[i] = (struct pcie_msix_tbl *)(PCIE_MSIX_TABLE_BASE + PCIE_MSIX_VF_ACTIVE +
													   PCIE_MSIX_VF_TABLE_OFFSET * i);
}

struct pcie_epc *pcie_get_epc(void)
{
	return &dw_pcie_epc;
}

struct dw_pcie_config pcie_ep_cfg = {
	.dbi_base = (struct pcie_ctrl_register *)PCIE_DBI_REG_BASE,
	.dbi2_base = (struct pcie_ctrl_dbi2_register *)PCIE_DBI2_REG_BASE,
	.port_base = (struct pcie_ctrl_port_register *)PCIE_PORT_REG_BASE,
	.vf_base = {(struct pcie_ctrl_vf_pf0_register *)PCIE_DBI_VF_REG_BASE,},
	.iatu_base = {(struct pcie_ctrl_pf0_atu_cap_iatu_register *)PCIE_IATU_REG_BASE,},
	.hdma_base = {(struct pcie_ctrl_pf0_hdma_cap_hdma_register *)PCIE_HDMA_REG_BASE,},
	.subctrl_base = (struct pcie_subctrl_register *)PCIE_SUBCTRL_REG_BASE,
	.sysreg_base = (struct sysreg_pcie_register *)PCIE_SYSREG_REG_BASE,
	.sysreg_buscsr_base = (struct sysreg_buscsr_pcie_register *)PCIE_SYSREG_BUSCSR_REG_BASE,
	.doe_base = (struct pcie_doe_register *)PCIE_DOE_REG_BASE,
	.ide_apb_base = (struct pcie_ide_apb_register *)PCIE_IDE_APB_REG_BASE,
	.msix_tbl = (struct pcie_msix_tbl *)PCIE_MSIX_TABLE_BASE,
	.num_lanes = PCIE_TARGET_NUM_LANES,
};

struct pcie_epc dw_pcie_epc = {
	.drv = &pcie_ep_drv,
	.cfg = &pcie_ep_cfg,
};

static int pcie_ep_post_init(void);

static int pcie_ep_init(void)
{
	struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	struct dw_pcie_drv *data = dw_pcie_epc.drv;
	uint32_t ret = RL_ERROR;

	pcie_ep_set_base_address(cfg);

	pcie_crs_enable(cfg, true);

	pcie_ep_reset_release(cfg);

	/* Initialize hotreset */
	pcie_ep_hotreset_init(cfg);

	pcie_phy_init(cfg, data);

	pcie_dbi_ro_wr_enable(cfg, true);

	pcie_ep_config_init(cfg, data);

	pcie_ep_request_irq(cfg);

	/* TODO: This will remove after bring-up */
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	dbi_base->pf0_pcie_cap_link_capabilities_reg.pcie_cap_active_state_link_pm_support = 0;

	pcie_ep_post_init();

	pcie_ltssm_enable(cfg, true);

	ret = pcie_ep_linkup_check(cfg);
	if (ret == 0)
		data->state = LINK_UP;

	/* TODO: This will be fixed after bring-up*/
#ifdef ZEBU
	pcie_ep_post_init();
#endif /* ZEBU */

	pcie_dbg_log("PCIE EP: PCIe pre-init done\n");

	return RL_OK;
}

static int pcie_ep_post_init(void)
{
	struct dw_pcie_config *cfg = dw_pcie_epc.cfg;
	struct dw_pcie_drv *data = dw_pcie_epc.drv;

	pcie_ep_config_post_init(cfg, data);

	pcie_crs_enable(cfg, false);

	pcie_dbi_ro_wr_enable(cfg, false);

	pcie_dbg_log("PCIE EP: PCIe post-init done\n");

#ifndef ZEBU_POC
	/* TODO: This is added for test. Need to modified for real scenario */
	cfg->sysreg_base->tzpc_r0size.intmem_pcie_r0size1 = 0x0;
#endif /* ZEBU_POC */

	return RL_OK;
}

void dram_init_done_cb(void)
{
	struct dw_pcie_drv *data = dw_pcie_epc.drv;

	pcie_dbg_log("%s\n\n", __func__);

	if (data->state == POST_INIT_DONE)
		return;

	/* TODO: This will be fixed after bring-up */
#ifndef ZEBU
	/* TODO: This will roll-back after bring-up */
	// pcie_ep_post_init();
#endif /* ZEBU */

	data->state = POST_INIT_DONE;
	BOOT_LOG(CM7, TBOOT_P0, BOOT_DONE(CM7));
}

#if defined(__RUN_RTOS)
	/*
	 * TODO: Modify init priority to 0,
	 * if it is okay for the UART to be initialized later
	 */
	DRIVER_INIT_ENTRY_DEFINE(2, pcie_ep_init);
#endif /* defined(__RUN_RTOS)*/
