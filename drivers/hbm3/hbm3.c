/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "hbm3.h"
#include "hbm3ephy.h"
#include "ddr_csr.h"

static struct hbm3_config hbm3_cfg[MAX_CHIPLET_COUNT];

struct hbm3_config *get_hbm_cfg(uint32_t chiplet_id)
{
	if (chiplet_id >= MAX_CHIPLET_COUNT)
		return NULL;

	return &hbm3_cfg[chiplet_id];
}

uint16_t get_phy_lock_value(volatile struct hbm3_config *cfg, uint8_t ch)
{
	return (cfg->phy_base[ch]->mdll_con1.ctrl_lock_value & CTL_LOCK_VALUE_MASK);
}

void phy_do_training(volatile struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t rdata;

	cfg->phy_base[ch]->cal_con4.phy_train_en = 0x1;

	do {
		rdata = cfg->phy_base[ch]->cal_con4.phy_train_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x1);

	cfg->phy_base[ch]->cal_con4.phy_train_en = 0x0;
}

void phy_gen_pattern(volatile struct hbm3_config *cfg, uint8_t ch)
{
	cfg->phy_base[ch]->direct_cmd_con_0.cmd_cacal_req = 0x1;
	udelay(1 * 10);
	cfg->phy_base[ch]->direct_cmd_con_0.cmd_cacal_req = 0x0;
	udelay(1 * 10);

	cfg->phy_base[ch]->direct_cmd_con_0.cmd_cacal_req = 0x1;
	udelay(1 * 10);
	cfg->phy_base[ch]->direct_cmd_con_0.cmd_cacal_req = 0x0;
	udelay(1 * 10);
}

void phy_update_dll_code(volatile struct hbm3_config *cfg, uint8_t ch)
{
	cfg->phy_base[ch]->offsetd_con0.ctrl_resync = 0x1;
	udelay(1);
	cfg->phy_base[ch]->offsetd_con0.ctrl_resync = 0x0;
	udelay(1);
}

void phy_clear_feedback_data(volatile struct hbm3_config *cfg, uint8_t ch)
{
	cfg->phy_base[ch]->par_con.cmd_par_err_rst_n = 0x0;
	udelay(1);
	cfg->phy_base[ch]->par_con.cmd_par_err_rst_n = 0x1;
	udelay(1);
}

void mrw_mask(volatile struct hbm3_config *cfg, uint8_t ch, uint8_t mr_addr, uint32_t mr_data, uint32_t mask)
{
	uint32_t rdata;

	cfg->csr_base[ch]->mc_base2_init_mr_addr.init_mr_addr = mr_addr;
	cfg->csr_base[ch]->mc_base2_init_mr_wr_data.init_mr_wr_data = mr_data;
	cfg->csr_base[ch]->mc_base2_init_mr_wr_mask.init_mr_wr_mask = mask;
	cfg->csr_base[ch]->mc_base2_init_mr_w_req.init_mr_w_req = 0x1;

	udelay(1);

	do {
		rdata = cfg->csr_base[ch]->mc_base4_init_ack.val;
	} while ((rdata & 0x1) != 0x1);

	cfg->csr_base[ch]->mc_base2_init_mr_w_req.init_mr_w_req = 0x0;
}

void mrw(volatile struct hbm3_config *cfg, uint8_t ch, uint8_t mr_addr, uint32_t mr_data)
{
	mrw_mask(cfg, ch, mr_addr, mr_data, MRW_MASK);
}

void mrw_phy_direct_cmd(volatile struct hbm3_config *cfg, uint8_t ch, uint8_t ma, uint8_t op)
{
	uint32_t rdata;

	cfg->phy_base[ch]->scheduler_mode.sw_cmd_start = 0x1;
	cfg->phy_base[ch]->scheduler_mode.scheduler_sw_mode = 0x1;
	if (GET_REVISION == REVISION_EVT0)
		cfg->phy_base[ch]->scheduler_con3.evt0_ma_code_apb = ma;
	else
		cfg->phy_base[ch]->scheduler_con3.evt1_ma_code_apb = ma;

	cfg->phy_base[ch]->scheduler_con5.op_code_apb = op;

	cfg->phy_base[ch]->direct_cmd_con_0.cmd_mrs_req = 0x1;
	udelay(1);
	cfg->phy_base[ch]->direct_cmd_con_0.cmd_mrs_req = 0x0;
	cfg->phy_base[ch]->scheduler_mode.sw_cmd_start = 0x1;

	do {
		rdata = cfg->phy_base[ch]->scheduler_state.schd_fifo_empty_status;
	} while ((rdata & 0x1) != 0x1);

	cfg->phy_base[ch]->scheduler_mode.scheduler_sw_mode = 0x0;

	udelay(1 * 10);
}

void phy_set_read_vref(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t dword0_vref, uint16_t dword1_vref)
{
	cfg->phy_base[ch]->io_vref_con1.zq_dword0_vref = HBM3_SET_VREF(dword0_vref);
	cfg->phy_base[ch]->io_vref_con2.zq_dword1_vref = HBM3_SET_VREF(dword1_vref);
}

void phy_set_write_vref(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t dram_vref)
{
	mrw_phy_direct_cmd(cfg, ch, MR15, dram_vref << 1);
}

void phy_dq_offset_control(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t p, uint16_t n)
{
	uint32_t data = ((p & 0x7)) | ((n & 0x7) << 0x3);

	for (int i = 0 ; i < 16 ; i++) {
		PHY_SET_DUTY_CTRL_0(i, (data << 1) | 0x1);
		PHY_SET_DUTY_CTRL_1(i, (data << 1) | 0x1);
	}
}

void phy_ecc_offset_control(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t p, uint16_t n)
{
	uint32_t rdata;
	uint32_t data = ((p & 0x7)) | ((n & 0x7) << 0x3);

	rdata = (cfg->phy_base[ch]->duty_ctrl16.io_offset_cal_ecc0 & 0x1);
	cfg->phy_base[ch]->duty_ctrl16.io_offset_cal_ecc0 = (rdata | (data << 1));

	rdata = (cfg->phy_base[ch]->duty_ctrl16.io_offset_cal_ecc1 & 0x1);
	cfg->phy_base[ch]->duty_ctrl16.io_offset_cal_ecc1 = (rdata | (data << 1));
}

void phy_sev_offset_control(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t p, uint16_t n)
{
	uint32_t rdata;
	uint32_t data = ((p & 0x7)) | ((n & 0x7) << 0x3);

	rdata = (cfg->phy_base[ch]->duty_ctrl17.io_offset_cal_sev0 & 0x1);
	cfg->phy_base[ch]->duty_ctrl17.io_offset_cal_sev0 = (rdata | (data << 1));

	rdata = (cfg->phy_base[ch]->duty_ctrl17.io_offset_cal_sev1 & 0x1);
	cfg->phy_base[ch]->duty_ctrl17.io_offset_cal_sev1 = (rdata | (data << 1));
}

void phy_dbi_offset_control(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t p, uint16_t n)
{
	uint32_t rdata;
	uint32_t data = ((p & 0x7)) | ((n & 0x7) << 0x3);

	rdata = (cfg->phy_base[ch]->duty_ctrl18.io_offset_cal_dbi0 & 0x1);
	cfg->phy_base[ch]->duty_ctrl18.io_offset_cal_dbi0 = (rdata | (data << 1));

	rdata = (cfg->phy_base[ch]->duty_ctrl18.io_offset_cal_dbi1 & 0x1);
	cfg->phy_base[ch]->duty_ctrl18.io_offset_cal_dbi1 = (rdata | (data << 1));

	rdata = (cfg->phy_base[ch]->duty_ctrl19.io_offset_cal_dbi2 & 0x1);
	cfg->phy_base[ch]->duty_ctrl19.io_offset_cal_dbi2 = (rdata | (data << 1));

	rdata = (cfg->phy_base[ch]->duty_ctrl19.io_offset_cal_dbi3 & 0x1);
	cfg->phy_base[ch]->duty_ctrl19.io_offset_cal_dbi3 = (rdata | (data << 1));
}

void phy_rdqs_offset_control(volatile struct hbm3_config *cfg, uint8_t ch, uint16_t p, uint16_t n)
{
	uint32_t rdata;
	uint32_t data = ((p & 0x7)) | ((n & 0x7) << 0x3);

	rdata = (cfg->phy_base[ch]->duty_ctrl22.io_offset_cal_rdqs & 0x1);
	cfg->phy_base[ch]->duty_ctrl22.io_offset_cal_rdqs = (rdata | (data << 1));
}

void phy_offset_update(volatile struct hbm3_config *cfg, uint8_t ch)
{
	uint32_t rdata;

	cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_start_en = 0x1;

	do {
		rdata = cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_set_state_busy;
	} while ((rdata & 0x1) != 0);

	cfg->phy_base[ch]->duty_ctrl_en.duty_ctrl_start_en = 0x0;
}

static inline uint64_t get_chiplet_addr(uint32_t chiplet_id, uint64_t base_addr)
{
#if defined(__RUN_RTOS)
	return CPVA_TO_PA(chiplet_id, base_addr);
#else
	return (chiplet_id * CHIPLET_OFFSET) + base_addr;
#endif
}

int32_t hbm3_config_init(void)
{
	for (uint32_t chiplet_id = 0; chiplet_id < MAX_CHIPLET_COUNT; chiplet_id++) {
		struct hbm3_config *cfg = &hbm3_cfg[chiplet_id];

		cfg->icon_base = (struct ieee1500_icon *)get_chiplet_addr(chiplet_id, HBM3_ICON_BASE);
		cfg->sysreg_base = (struct sysreg_dram *)get_chiplet_addr(chiplet_id, SYSREG_DRAM);

		for (uint32_t ch = 0; ch < HBM3_NUM_CH; ch++) {
			cfg->csr_base[ch] = (struct ddr_csr *)get_chiplet_addr(chiplet_id,
				HBM3_CON_0_BASE + ch * HBM3_CON_BASE_OFFSET);
			cfg->phy_base[ch] = (struct hbm3ephy *)get_chiplet_addr(chiplet_id,
				HBM3_PHY_0_BASE + ch * HBM3_PHY_BASE_OFFSET);
		}
	}

	return 0;
}

#if defined(__RUN_RTOS)
#include "driver.h"

DRIVER_INIT_ENTRY_DEFINE(9, hbm3_config_init);
#endif
