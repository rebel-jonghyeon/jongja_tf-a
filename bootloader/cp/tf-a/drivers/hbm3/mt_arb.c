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

/**
 * MT arbitrary Test
 * param : channel(0~15)
 * param : addr
 * return : 0 (success), 1 (fail)
 */
static int memtest_arb(uint32_t chiplet_id, uint32_t ch, uint32_t addr)
{
	volatile struct ddr_csr *ctrl = get_hbm_cfg(chiplet_id)->csr_base[ch];
	uint32_t rdata = 0;
	uint32_t cycle = 0x8;	// max 0x8

	rdata = ctrl->mem_test_mt_error_sts.val;	// clear error status

	// error mask
	// ctrl->mem_test_mt_error_mask_0.mt_error_mask_31_0 = 0x1;
	// ctrl->mem_test_mt_error_mask_1.mt_error_mask_63_32 = 0x1;

	ctrl->mem_test_mt_arb_mem_addr.mt_arb_mem_addr = 0;
	_WAIT2(ctrl->mem_test_mt_arb_ack.mt_arb_ack, 1);

	for (int i = 0 ; i < cycle ; i++) {
		ctrl->mem_test_mt_wd_wdata_0.mt_wd_wdata_31_0	  = 0x55555555;
		ctrl->mem_test_mt_wd_wdata_1.mt_wd_wdata_63_32	  = 0x55555555;
		ctrl->mem_test_mt_wd_wdata_2.mt_wd_wdata_95_64	  = 0x55555550;	// MD0[3:0] | Data0[63:0]
		ctrl->mem_test_mt_wd_wdata_3.mt_wd_wdata_127_96	  = 0x55555555;
		ctrl->mem_test_mt_wd_wdata_4.mt_wd_wdata_159_128  = 0x55555505;	// MD0[3:0] | Data0[63:0]
		ctrl->mem_test_mt_wd_wdata_5.mt_wd_wdata_191_160  = 0x55555555;
		ctrl->mem_test_mt_wd_wdata_6.mt_wd_wdata_223_192  = 0x55555055;	// MD0[3:0] | Data0[63:0]
		ctrl->mem_test_mt_wd_wdata_7.mt_wd_wdata_255_224  = 0x55555555;
		ctrl->mem_test_mt_wd_wdata_8.mt_wd_wdata_287_256  = 0x55550555;	//
		ctrl->mem_test_mt_wd_wdata_9.mt_wd_wdata_319_288  = 0x55555555;
		ctrl->mem_test_mt_wd_wdata_10.mt_wd_wdata_351_320 = 0x55505555;	//
		ctrl->mem_test_mt_wd_wdata_11.mt_wd_wdata_383_352 = 0x55555555;
		ctrl->mem_test_mt_wd_wdata_12.mt_wd_wdata_415_384 = 0x55055555;	//
		ctrl->mem_test_mt_wd_wdata_13.mt_wd_wdata_447_416 = 0x55555555;
		ctrl->mem_test_mt_wd_wdata_14.mt_wd_wdata_479_448 = 0x50555555;	//
		ctrl->mem_test_mt_wd_wdata_15.mt_wd_wdata_511_480 = 0x55555555;
		ctrl->mem_test_mt_wd_wdata_16.mt_wd_wdata_543_512 = 0x05555555;	//
		_WAIT2(ctrl->mem_test_mt_arb_ack.mt_arb_ack, 1);
	}

	ctrl->mem_test_mt_max_wd.mt_max_wd = cycle - 1;

	ctrl->mem_test_mt_arb_mem_addr.mt_arb_mem_addr = 0;
	_WAIT2(ctrl->mem_test_mt_arb_ack.mt_arb_ack, 1);

	for (int i = 0 ; i < cycle ; i++) {
		ctrl->mem_test_mt_ex_wdata_0.mt_ex_wdata_31_0	  = 0x55555555;
		ctrl->mem_test_mt_ex_wdata_1.mt_ex_wdata_63_32	  = 0x55555555;
		ctrl->mem_test_mt_ex_wdata_2.mt_ex_wdata_95_64	  = 0x55555550;	// MD0[3:0] | Data0[63:0]
		ctrl->mem_test_mt_ex_wdata_3.mt_ex_wdata_127_96   = 0x55555555;
		ctrl->mem_test_mt_ex_wdata_4.mt_ex_wdata_159_128  = 0x55555505;	// MD0[3:0] | Data0[63:0]
		ctrl->mem_test_mt_ex_wdata_5.mt_ex_wdata_191_160  = 0x55555555;
		ctrl->mem_test_mt_ex_wdata_6.mt_ex_wdata_223_192  = 0x55555055;	// MD0[3:0] | Data0[63:0]
		ctrl->mem_test_mt_ex_wdata_7.mt_ex_wdata_255_224  = 0x55555555;
		ctrl->mem_test_mt_ex_wdata_8.mt_ex_wdata_287_256  = 0x55550555;	//
		ctrl->mem_test_mt_ex_wdata_9.mt_ex_wdata_319_288  = 0x55555555;
		ctrl->mem_test_mt_ex_wdata_10.mt_ex_wdata_351_320 = 0x55505555;	//
		ctrl->mem_test_mt_ex_wdata_11.mt_ex_wdata_383_352 = 0x55555555;
		ctrl->mem_test_mt_ex_wdata_12.mt_ex_wdata_415_384 = 0x55055555;	//
		ctrl->mem_test_mt_ex_wdata_13.mt_ex_wdata_447_416 = 0x55555555;
		ctrl->mem_test_mt_ex_wdata_14.mt_ex_wdata_479_448 = 0x50555555;	//
		ctrl->mem_test_mt_ex_wdata_15.mt_ex_wdata_511_480 = 0x55555555;
		ctrl->mem_test_mt_ex_wdata_16.mt_ex_wdata_543_512 = 0x05555555;	//
		_WAIT2(ctrl->mem_test_mt_arb_ack.mt_arb_ack, 1);
	}

	ctrl->mem_test_mt_max_ex.mt_max_ex = cycle - 1;

	// Run one test for each byte  for each byte pair
	// for other valuse of ACQ_DATA_WIDTH.
	ctrl->mem_test_mt_cycles.mt_cycles = cycle * 2;		// Wr cycle, Rd cycle
	ctrl->mem_test_mt_addr_pattern.mt_addr_pattern = 0x2;	// arbitrary address pattern

#if defined(USE_MTA)
	ctrl->mta_cfg_en_mask.cfg_en_mask = 0x0;	// 0 - Valid cycles containing read data mismatch error
	ctrl->mta_cfg_trig_mode.cfg_trig_mode = 0x1;
	ctrl->mta_cfg_trig_mask.cfg_trig_mask = 0x4;	// 3’b100 - valid cycles with an read data mismatch error
	ctrl->mta_cfg_pre_trig_cycs.cfg_pre_trig_cycs = 0x0;
	ctrl->mta_cfg_post_trig_cycs.cfg_post_trig_cycs = 0x2;
	ctrl->mta_cfg_trig_mt_addr_0.cfg_trig_mt_addr = 0x0;

	// k will be cfg_data_sel
	ctrl->mta_cfg_error_group_sel.cfg_error_group_sel = 0x0; // 0x0;
	ctrl->mta_cfg_data_sel.cfg_data_sel = 0x0;
#endif

	volatile uint32_t errcnt = 0;

	for (int k = 0 ; k < 1 ; k++) {
		ctrl->mem_test_mt_arb_mem_addr.mt_arb_mem_addr = 0;
		_WAIT2(ctrl->mem_test_mt_arb_ack.mt_arb_ack, 1);

		// write
		for (int i = 0 ; i < cycle ; i++) {
			ctrl->mem_test_mt_ac_wdata_0.mt_ac_wdata_31_0 = cycle * k + i;	// 64 byte per each
			ctrl->mem_test_mt_ac_wdata_1.mt_ac_wdata_63_32 = 0x8000000;	// l_b_size 1
			_WAIT2(ctrl->mem_test_mt_arb_ack.mt_arb_ack, 0x1);
		}

		// read
		for (int i = 0 ; i < cycle ; i++) {
			ctrl->mem_test_mt_ac_wdata_0.mt_ac_wdata_31_0 = cycle * k + i;	// 64 byte per each
			ctrl->mem_test_mt_ac_wdata_1.mt_ac_wdata_63_32 = 0x88000000;	// l_b_size 1
			_WAIT2(ctrl->mem_test_mt_arb_ack.mt_arb_ack, 0x1);
		}

		ctrl->mem_test_mt_max_ac.mt_max_ac = cycle * 2 - 1;

		// run test
		ctrl->mem_test_mt_en_single.mt_en_single = 0x1;
		_WAIT(ctrl->mem_test_mt_done_ack.val, 0x1);
		ctrl->mem_test_mt_en_single.mt_en_single = 0x0;

#if defined(USE_MTA)
		errcnt = ctrl->mta_mtc_acq_error_cnt.mtc_acq_error_cnt;
		if (errcnt > 0) {
			printf("mtc_acq_error_cnt : %d\n", ctrl->mta_mtc_acq_error_cnt.mtc_acq_error_cnt);
			break;
		}
#endif

		// ctrl->mta_mtc_acq_addr.mtc_acq_addr = cycle * i;
		// _WAIT(ctrl->mta_mtc_ack.mtc_ack, 0x1);
	}

	printf("mta_mtc_acq_cycs_stored: 0x%x\n", ctrl->mta_mtc_acq_cycs_stored.mtc_acq_cycs_stored);
	printf("mta_cfg_trig_mode: 0x%x\n", ctrl->mta_cfg_trig_mode.cfg_trig_mode);
	printf("mta_mtc_acq_trig_detect: 0x%x\n", ctrl->mta_mtc_acq_trig_detect.mtc_acq_trig_detect);
	printf("mta_mtc_acq_mem_trig_addr : 0x%x\n", ctrl->mta_mtc_acq_mem_trig_addr.mtc_acq_mem_trig_addr);
	printf("mta_mtc_acq_mem_last_addr : 0x%x\n", ctrl->mta_mtc_acq_mem_last_addr.mtc_acq_mem_last_addr);

#if defined(USE_MTA)
	ctrl->mta_mtc_acq_addr.mtc_acq_addr = 0;
	_WAIT(ctrl->mta_mtc_ack.mtc_ack, 0x1);

	for (int i = 0 ; i < cycle ; i++) {
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
		printf("mta_mtc_ack : 0x%x\n", ctrl->mta_mtc_ack.mtc_ack);
	}
#endif

	// check test pass/fail
	rdata = ctrl->mem_test_mt_error_sts.val;

	if ((rdata & 0x1) == 0x1) {
		return 1;	// error
	} else {
		return 0;
	}
}

/**
 * Need to call before Memory Test Arbitrary
 */
void mt_arb_pre(uint32_t chiplet_id, uint32_t ch)
{
	uint32_t rdata;
	volatile struct ddr_csr *ctrl = get_hbm_cfg(chiplet_id)->csr_base[ch];

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

	// ensure for linear-address test patterns that each subsequent burst location is
	// a different bank for maximum possible interleaved memory perfromance stress
	_SAVE(cfg_force_bgpos0, ctrl->mc_base3_cfg_force_bgpos0.cfg_force_bgpos0 & 0x1);
	ctrl->mc_base3_cfg_force_bgpos0.cfg_force_bgpos0 = 0x1;

	// Need only for algorithm test
	_SAVE(mt_addr_bits, ctrl->mem_test_mt_addr_bits.mt_addr_bits & MT_ADDR_BIT_MASK);
	ctrl->mem_test_mt_wr_only.mt_wr_only = 0x0;
	ctrl->mem_test_mt_stop_on_error.mt_stop_on_error = 0x1;
	ctrl->mem_test_mt_rd_only.mt_rd_only = 0x0;
	ctrl->mem_test_mt_en.mt_en = 0x0;

	rdata = ctrl->mem_test_mt_error_sts.val;	// clear error status
	printf("ready for mt_arb_test %u\n", rdata);
}

/**
 * Need to call after Memory Test Arbitrary
 */
void mt_arb_post(uint32_t chiplet_id, uint32_t ch)
{
	volatile struct ddr_csr *ctrl = get_hbm_cfg(chiplet_id)->csr_base[ch];

	ctrl->mem_test_mt_addr_bits.mt_addr_bits = mt_saved._mt_addr_bits & MT_ADDR_BIT_MASK;
	ctrl->mc_base3_cfg_force_bgpos0.cfg_force_bgpos0 = mt_saved._cfg_force_bgpos0;

	restore_reorder_sbref(ctrl, mt_saved._cfg_reorder_en, mt_saved._init_sbref_en);

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
}

/**
 * Test All Memory Region per Channel
 */
int mt_arb_test(uint32_t chiplet_id, uint32_t ch)
{
	uint32_t start_addr = 0x0;

	mt_arb_pre(chiplet_id, ch);

	if (memtest_arb(chiplet_id, ch, start_addr)) {
		printf("mt_arb_test failed\n");
		return 1;
	}

	mt_arb_post(chiplet_id, ch);

	return 0;
}
