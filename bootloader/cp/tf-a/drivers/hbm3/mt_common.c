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

#include "drivers/hbm3/mt_test.h"

void turn_off_phy_mastering(volatile struct ddr_csr *ctrl)
{
	int timeout = 1000;
	uint32_t stat_dfi_phymstr_ack, sr_status, auto_sr_time;

	stat_dfi_phymstr_ack = ctrl->dfi_stat_dfi_phymstr_ack.stat_dfi_phymstr_ack;
	while (timeout > 0 && stat_dfi_phymstr_ack) {
		stat_dfi_phymstr_ack = ctrl->dfi_stat_dfi_phymstr_ack.stat_dfi_phymstr_ack;
		timeout--;
	}

	auto_sr_time = ctrl->mc_base5_cfg_idle_time_to_self_refresh.cfg_idle_time_to_self_refresh;
	ctrl->mc_base5_cfg_idle_time_to_self_refresh.cfg_idle_time_to_self_refresh = 0x0;

	sr_status = ctrl->mc_base2_init_self_refresh_status.init_self_refresh_status;
	timeout = 1000;
	while (timeout > 0 && sr_status) {
		sr_status = ctrl->mc_base2_init_self_refresh_status.init_self_refresh_status;
		timeout--;
	}

	ctrl->mc_base5_cfg_idle_time_to_self_refresh.cfg_idle_time_to_self_refresh = auto_sr_time;
}

void turn_on_phy_mastering(volatile struct ddr_csr *ctrl)
{
	ctrl->dfi_init_dfi_phymstr_en.init_dfi_phymstr_en = 1;
}

void turn_off_auto_refresh(volatile struct ddr_csr *ctrl)
{
	uint32_t cfg_idle_time_to_self_refresh, init_ecc_scrub_en, cfg_sbref_issue_per;
	uint32_t sbref_en, auto_ref_en, init_phyupd_en, init_phymstr_en;
	uint32_t init_ref_per;

	sbref_en = ctrl->mc_base1_init_sbref_en.init_sbref_en;
	auto_ref_en = ctrl->mc_base2_init_auto_ref_en.init_auto_ref_en;

	if (auto_ref_en) {

		cfg_idle_time_to_self_refresh = ctrl->mc_base5_cfg_idle_time_to_self_refresh.cfg_idle_time_to_self_refresh;
		if (cfg_idle_time_to_self_refresh)
			ctrl->mc_base5_cfg_idle_time_to_self_refresh.cfg_idle_time_to_self_refresh = 0;

		if (sbref_en) {
			cfg_sbref_issue_per = ctrl->mc_base5_cfg_sbref_issue_per.cfg_sbref_issue_per;
			ctrl->mc_base5_cfg_sbref_issue_per.cfg_sbref_issue_per = SBREF_ISSUE_PER;
		}

		init_ecc_scrub_en = ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en;

		if (init_ecc_scrub_en) {
			ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en = 0x0;
			udelay(1);
		}

		init_phyupd_en = ctrl->dfi_init_dfi_phyupd_en.init_dfi_phyupd_en;

		if (init_phyupd_en)
			ctrl->dfi_init_dfi_phyupd_en.init_dfi_phyupd_en = 0x0;

		init_phymstr_en = ctrl->dfi_init_dfi_phymstr_en.init_dfi_phymstr_en;

		if (init_phymstr_en)
			turn_off_phy_mastering(ctrl);

		init_ref_per = ctrl->mc_base5_init_ref_per.init_ref_per;
		if (sbref_en)
			ctrl->mc_base5_init_ref_per.init_ref_per = 2 * init_ref_per;

		udelay(1);

		if (init_phyupd_en)
			ctrl->dfi_init_dfi_phyupd_en.init_dfi_phyupd_en = init_phyupd_en & 0x1;

		if (init_phymstr_en)
			turn_on_phy_mastering(ctrl);

		if (sbref_en) {
			ctrl->mc_base5_cfg_sbref_issue_per.cfg_sbref_issue_per = cfg_sbref_issue_per & 0x3FF;
		}

		if (init_ecc_scrub_en) {
			ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en = init_ecc_scrub_en & 0x1;
		}

		if (cfg_idle_time_to_self_refresh) {
			ctrl->mc_base5_cfg_idle_time_to_self_refresh.cfg_idle_time_to_self_refresh = cfg_idle_time_to_self_refresh;
		}
	}
}

void turn_on_auto_refresh(volatile struct ddr_csr *ctrl)
{
	uint32_t auto_ref_en;

	auto_ref_en = ctrl->mc_base2_init_auto_ref_en.init_auto_ref_en;

	if (!auto_ref_en) {
		ctrl->mc_base2_init_auto_ref_en.init_auto_ref_en = 0x1;
	}
}

void disable_reorder_sbref(volatile struct ddr_csr *ctrl)
{
	uint32_t init_auto_ref_en;

	init_auto_ref_en = ctrl->mc_base2_init_auto_ref_en.init_auto_ref_en;
	_SAVE(init_sbref_en, ctrl->mc_base1_init_sbref_en.init_sbref_en & 0x1);
	_SAVE(cfg_reorder_en, ctrl->reorder_cfg_reorder_en.cfg_reorder_en & 0x1);

	if (mt_saved._cfg_reorder_en) {

		if (init_auto_ref_en)
			turn_off_auto_refresh(ctrl);

		ctrl->reorder_cfg_reorder_en.cfg_reorder_en = 0x0;

		if (init_auto_ref_en)
			turn_on_auto_refresh(ctrl);
	}
}

void restore_reorder_sbref(volatile struct ddr_csr *ctrl, uint32_t reorder_en, uint32_t sbref_en)
{
	uint32_t auto_ref_en, init_sbref_en, init_reorder_en;

	auto_ref_en = ctrl->mc_base2_init_auto_ref_en.init_auto_ref_en & 0x1;
	init_sbref_en = ctrl->mc_base1_init_sbref_en.init_sbref_en & 0x1;
	init_reorder_en = ctrl->reorder_cfg_reorder_en.cfg_reorder_en & 0x1;

	if (init_reorder_en != reorder_en || init_sbref_en != sbref_en) {
		if (auto_ref_en)
			turn_off_auto_refresh(ctrl);

		if (init_sbref_en != sbref_en)
			ctrl->mc_base1_init_sbref_en.init_sbref_en = sbref_en & 0x1;

		if (init_reorder_en != reorder_en)
			ctrl->reorder_cfg_reorder_en.cfg_reorder_en = reorder_en & 0x1;

		if (auto_ref_en)
			turn_on_auto_refresh(ctrl);
	}
}
