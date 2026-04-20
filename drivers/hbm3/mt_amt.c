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
/* Test pattern */
#include "drivers/hbm3/mscan.h"

// #define AMT_PERF_MEASURE 1
#define SBREF_ISSUE_PER 10
#define RF_WADDR_ERRCNT 30

struct _amt_bin {
	char *name;
	unsigned long *inst;
	unsigned int len;
};

/**
 * Need to call before Advanced Memory Test
 */
void mt_amt_pre(uint32_t chiplet_id, uint32_t ch)
{
	volatile struct ddr_csr *ctrl = get_hbm_cfg(chiplet_id)->csr_base[ch];
	uint32_t rdata;

	_SAVE(init_ecc_scrub_en, ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en & 0x1);
	_SAVE(cfg_ecc_scrub_init_rmw,
		  ctrl->ecc_config_cfg_ecc_scrub_init_rmw.cfg_ecc_scrub_init_rmw & 0x1);
	ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en = 0x0;

	// wait for any outstanding patrol-read
	udelay(1);

	_SAVE(init_idle_time_to_power_down,
		  ctrl->mc_base5_init_idle_time_to_power_down.init_idle_time_to_power_down);
	ctrl->mc_base5_init_idle_time_to_power_down.init_idle_time_to_power_down = 0;

	disable_reorder_sbref(ctrl);

	_SAVE(mt_addr_bits, ctrl->mem_test_mt_addr_bits.mt_addr_bits & MT_ADDR_BIT_MASK);

	rdata = ctrl->mem_test_mt_error_sts.val;	// clear error status
	printf("mt_amt_pre ready %u\n", rdata);
}

/**
 * Need to call after Advaned Memory Test
 */
void mt_amt_post(uint32_t chiplet_id, uint32_t ch)
{
	volatile struct ddr_csr *ctrl = get_hbm_cfg(chiplet_id)->csr_base[ch];

	ctrl->mem_test_mt_addr_bits.mt_addr_bits = mt_saved._mt_addr_bits & MT_ADDR_BIT_MASK;

	// re-init ECC
	ctrl->ecc_config_cfg_ecc_scrub_init_rmw.cfg_ecc_scrub_init_rmw = 0;

	ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en = 0;
	udelay(1);
	ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en = 1;
	udelay(1);
	ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en = 0;

	// restore ECC settings
	ctrl->ecc_config_cfg_ecc_scrub_init_rmw.cfg_ecc_scrub_init_rmw = mt_saved._cfg_ecc_scrub_init_rmw;
	ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en = mt_saved._init_ecc_scrub_en;
	ctrl->mc_base5_init_idle_time_to_power_down.init_idle_time_to_power_down =
		mt_saved._init_idle_time_to_power_down;

	restore_reorder_sbref(ctrl, mt_saved._cfg_reorder_en, mt_saved._init_sbref_en);
}

uint32_t amt_iram_test(uint32_t chiplet_id, uint32_t ch)
{
	volatile struct ddr_csr *ctrl = get_hbm_cfg(chiplet_id)->csr_base[ch];
	int i, ret = 0, len;
	uint32_t wdat0, wdat1;
	uint64_t wdata[7];
	uint32_t rdat0, rdat1;
	uint64_t rdata[7];
	uint64_t randin[7] = {
		0xff8542ff31d91163,
		0x2a742b54a3d80047,
		0xdf9ddcbf2744ef4e,
		0x5f4dbfbeefc466df,
		0x6727bbce99e76a33,
		0x9571fe2a57b069af,
		0x1d521b3af5d0aeeb};

	mt_amt_pre(chiplet_id, ch);

	ctrl->adv_mem_test_amt_useq_iram_waddr.amt_useq_iram_waddr = 0x0;
	_WAIT(ctrl->adv_mem_test_amt_useq_iram_ack.val, 0x1);

	len = sizeof(randin) / sizeof(uint64_t);
	for (i = 0; i < len; i++)	{
		wdat0 = (uint32_t)(randin[i] & 0xFFFFFFFF);
		wdat1 = (uint32_t)((randin[i] >> 32) & 0xFFFFFFFF);
		wdata[i] = (uint64_t)(((uint64_t)(wdat1 & 0xFFFF) << 32) | (wdat0));

		ctrl->adv_mem_test_amt_useq_iram_wdata_0.val = wdat0;
		ctrl->adv_mem_test_amt_useq_iram_wdata_1.val = wdat1;
		_WAIT(ctrl->adv_mem_test_amt_useq_iram_ack.val, 0x1);
	}

	ctrl->adv_mem_test_amt_useq_iram_waddr.amt_useq_iram_waddr = 0x0;
	_WAIT(ctrl->adv_mem_test_amt_useq_iram_ack.val, 0x1);

	for (i = 0; i < 7; i++)	{
		rdat0 = ctrl->adv_mem_test_amt_useq_iram_rdata_0.val;
		rdat1 = ctrl->adv_mem_test_amt_useq_iram_rdata_1.val;
		_WAIT(ctrl->adv_mem_test_amt_useq_iram_ack.val, 0x1);

		rdata[i] = (uint64_t)(((uint64_t)(rdat1 & 0xFFFF) << 32) | (rdat0));
	}

	for (i = 0; i < sizeof(randin) / sizeof(uint64_t); i++)	{
		if (wdata[i] != rdata[i]) {
			printf("amt_iram_test Error %d\n", i);
			ret = 1;
		}
	}

	mt_amt_post(chiplet_id, ch);

	return ret;
}

uint32_t amt_useq_test(uint32_t chiplet_id, uint32_t ch, uint64_t *inst, uint32_t ninst)
{
	volatile struct ddr_csr *ctrl = get_hbm_cfg(chiplet_id)->csr_base[ch];
	int ret = 0;
	uint32_t wdat0, wdat1;
	uint32_t rdat0;
	uint32_t addr_bits;
	uint32_t cycle = 0x9;
#if AMT_PERF_MEASURE
	uint64_t before_tick = 0, after_tick = 0;

	before_tick = read_cntpct_el0();
#endif

	mt_amt_pre(chiplet_id, ch);

	addr_bits = ctrl->mem_test_mt_addr_bits.mt_addr_bits;

	ctrl->adv_mem_test_amt_useq_iram_waddr.amt_useq_iram_waddr = 0x0;
	_WAIT(ctrl->adv_mem_test_amt_useq_iram_ack.val, 0x1);

	for (int i = 0; i < ninst; i++)	{
		wdat0 = (uint32_t)(inst[i] & 0xFFFFFFFF);
		wdat1 = (uint32_t)((inst[i] >> 32) & 0xFFFF);

		ctrl->adv_mem_test_amt_useq_iram_wdata_0.val = wdat0;
		ctrl->adv_mem_test_amt_useq_iram_wdata_1.val = wdat1;
		_WAIT(ctrl->adv_mem_test_amt_useq_iram_ack.val, 0x1);
	}

	// when repeating, stop on error on each repeat
	// ctrl->mem_test_mt_stop_on_error.mt_stop_on_error = 0x1;

#if defined(USE_MTA)
	ctrl->mta_cfg_en_mask.cfg_en_mask = 0x0;	// 0 - Valid cycles containing read data mismatch error
	ctrl->mta_cfg_trig_mode.cfg_trig_mode = 0x1;
	ctrl->mta_cfg_trig_mask.cfg_trig_mask = 0x4;	// 3’b100 - valid cycles with an read data mismatch error
	ctrl->mta_cfg_pre_trig_cycs.cfg_pre_trig_cycs = 0x0;
	ctrl->mta_cfg_post_trig_cycs.cfg_post_trig_cycs = cycle;
	ctrl->mta_cfg_trig_mt_addr_0.cfg_trig_mt_addr = 0x0;

	// k will be cfg_data_sel
	ctrl->mta_cfg_error_group_sel.cfg_error_group_sel = 0x0;
	ctrl->mta_cfg_data_sel.cfg_data_sel = 0x0;
#endif

	ctrl->adv_mem_test_amt_useq_mta_storage_sel.amt_useq_mta_storage_sel = 0x0;	//r0 and r1 registers

	ctrl->adv_mem_test_amt_sequencer_enable.amt_sequencer_enable = 0x1;
	_WAIT(ctrl->mem_test_mt_done_ack.val, 0x0);

	ctrl->mem_test_mt_en_single.mt_en_single = 0x1;
	_WAIT(ctrl->mem_test_mt_done_ack.val, 0x1);
	ctrl->mem_test_mt_en_single.mt_en_single = 0x0;

	// clear residual ack
	rdat0 = ctrl->adv_mem_test_amt_useq_rf_ack.amt_useq_rf_ack;

	// check for errors in micro sequencer ERRCNT reg 30
	ctrl->adv_mem_test_amt_useq_rf_waddr.amt_useq_rf_waddr = RF_WADDR_ERRCNT;
	_WAIT(ctrl->adv_mem_test_amt_useq_rf_ack.val, 0x1);
	rdat0 = ctrl->adv_mem_test_amt_useq_rf_rdata_0.val;

	if (rdat0 != 0)	{
		printf("TEST Failed Detected %d errors\n", rdat0);
		ret = 1;
	} else {
		printf("TEST Passed Detected %d errors\n", rdat0);
	}

	rdat0 = ctrl->mem_test_mt_error_sts.val;

	if ((rdat0 & 0x1) == 0x1) {
		printf("TEST Err Sts %d\n", rdat0);
		printf("AMT Exception count %d\n", ctrl->adv_mem_test_amt_useq_exceptions.amt_useq_exceptions);

#if defined(USE_MTA)
		printf("mtc_acq_error_cnt : %d\n", ctrl->mta_mtc_acq_error_cnt.mtc_acq_error_cnt);

		ctrl->mta_mtc_acq_addr.mtc_acq_addr = 0;
		_WAIT(ctrl->mta_mtc_ack.mtc_ack, 0x1);

		for (int i = 0; i < cycle; i++) {
			printf("mta_mtc_acq_rd_data : 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%05x\n",
				   ctrl->mta_mtc_acq_rd_data_0.val,
				   ctrl->mta_mtc_acq_rd_data_1.val,
				   ctrl->mta_mtc_acq_rd_data_2.val,
				   ctrl->mta_mtc_acq_rd_data_3.val,
				   ctrl->mta_mtc_acq_rd_data_4.val,
				   ctrl->mta_mtc_acq_rd_data_5.val,
				   ctrl->mta_mtc_acq_rd_data_6.val,
				   ctrl->mta_mtc_acq_rd_data_7.val,
				   ctrl->mta_mtc_acq_rd_data_8.val);
		}
#endif
	}

	// final cleanup
	ctrl->adv_mem_test_amt_sequencer_enable.amt_sequencer_enable = 0x0;
	ctrl->mem_test_mt_addr_bits.mt_addr_bits = addr_bits & 0x3F;

#if AMT_PERF_MEASURE
	after_tick = read_cntpct_el0();

	printf("before tick : 0x%lx, after tick 0x%lx\n", before_tick, after_tick);
	printf("diff = %lu\n", after_tick - before_tick);
#endif

	mt_amt_post(chiplet_id, ch);

	return ret;
}

int mt_amt_test(uint32_t chiplet_id, uint32_t ch)
{
	int ret = 0;
	int len;

	struct _amt_bin amt_bin[1] = {
		{"mscan", mscan_bin, mscan_bin_len},
	};

	len = sizeof(amt_bin) / sizeof(struct _amt_bin);
	for (int i = 0 ; i < len ; i++) {

		printf("amt_useq_test ch%d [%s]\n", ch, amt_bin[i].name);

		if (amt_useq_test(chiplet_id, ch, amt_bin[i].inst, amt_bin[i].len)) {
			printf("amt_useq_test ch%d [%s] failed\n", ch, amt_bin[i].name);
			ret = 1;
		} else {
			printf("amt_useq_test ch%d [%s] passed\n", ch, amt_bin[i].name);
		}
	}

	return ret;
}
