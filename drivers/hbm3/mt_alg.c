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
 * MT algorithm Test
 * param : channel(0~15)
 * param : pattern (TEST_PATTERN)
 * return : 0 (success), 1 (fail)
 */
int memtest_alg(uint32_t chiplet_id, uint32_t ch, uint32_t addr, enum mt_bits bits,
				enum TEST_PATTERN pattern, uint8_t pat_user, bool isdebug)
{
	volatile struct ddr_csr *ctrl = get_hbm_cfg(chiplet_id)->csr_base[ch];
	uint32_t rdata = 0;
	uint32_t nbits = bits;	// size = 2^nbits * BIT(BL8_SHIFT)
	uint32_t cycle = 0x8;

	rdata = ctrl->mem_test_mt_error_sts.val;	// clear error status
	// ctrl->mem_test_mt_alg_auto_pch.mt_alg_auto_pch = 0x1;

	if ((pattern & 0xF) == TP_USER) {
		ctrl->mem_test_mt_user_data_pattern.mt_user_data_pattern = pat_user;
	}

#if defined(USE_MTA)
	ctrl->mta_cfg_en_mask.cfg_en_mask = 0x0;	// 0 - Valid cycles containing read data mismatch error
	ctrl->mta_cfg_trig_mode.cfg_trig_mode = 0x1;
	ctrl->mta_cfg_trig_mask.cfg_trig_mask = 0x4;	// 3’b100 - valid cycles with an read data mismatch error
	ctrl->mta_cfg_pre_trig_cycs.cfg_pre_trig_cycs = 0x0;
	ctrl->mta_cfg_post_trig_cycs.cfg_post_trig_cycs = cycle;
	ctrl->mta_cfg_trig_mt_addr_0.cfg_trig_mt_addr = 0x0;

	ctrl->mta_cfg_error_group_sel.cfg_error_group_sel = 0x0;
	ctrl->mta_cfg_data_sel.cfg_data_sel = 0x0;
#endif

	ctrl->mem_test_mt_data_pattern.mt_data_pattern = pattern & 0xF;
	ctrl->mem_test_mt_addr_pattern.mt_addr_pattern = 0x0;	// counting address pattern
	// ctrl->mem_test_mt_addr_pattern.mt_addr_pattern = 0x1;	// Pseudo-Random address pattern
	ctrl->mem_test_mt_data_invert.mt_data_invert = 0x0;
	ctrl->mem_test_mt_addr_bits.mt_addr_bits = nbits & MT_ADDR_BIT_MASK;
	ctrl->mem_test_mt_start_addr_0.mt_start_addr = addr & MT_ADDR_MASK;

	ctrl->mem_test_mt_en_single.mt_en_single = 0x1;
	_WAIT(ctrl->mem_test_mt_done_ack.val, 0x1);
	ctrl->mem_test_mt_en_single.mt_en_single = 0x0;

	rdata = ctrl->mem_test_mt_error_sts.val;

	if ((rdata & 0x1) == 0x1) {
		if (isdebug) {
			printf("TEST Err Sts %d\n", rdata);
			printf("mtc_acq_error_cnt : %d\n", ctrl->mta_mtc_acq_error_cnt.mtc_acq_error_cnt);

#if defined(USE_MTA)
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

		return 1;	// error
	} else {
		return 0;
	}
}

/**
 * MT algorithm Test per DQ
 * param : channel(0~15)
 * param : pattern (TEST_PATTERN)
 * return : 0 (success), 1 (fail)
 */
static int memtest_alg_dq(uint32_t chiplet_id, uint32_t ch, uint32_t addr, enum mt_bits bits,
						  enum TEST_PATTERN pattern, uint8_t pat_user, uint8_t dq)
{
	volatile struct ddr_csr *ctrl = get_hbm_cfg(chiplet_id)->csr_base[ch];
	uint32_t rdata = 0;
	uint32_t nbits = bits;	// size = 2^nbits * BIT(BL8_SHIFT)

	rdata = ctrl->mem_test_mt_error_sts.val;	// clear error status

	uint64_t mask = 0xFFFFFFFFFFFFFFFF;
	uint32_t mask_h = (uint32_t)(mask >> 32);

	mask ^= (((uint64_t)0x1) << dq);

	// error mask
	ctrl->mem_test_mt_error_mask_0.mt_error_mask_31_0 =  mask & 0xFFFFFFFF;
	ctrl->mem_test_mt_error_mask_1.mt_error_mask_63_32 = (mask >> 32) & 0xFFFFFFFF;
	ctrl->mem_test_mt_error_mask_2.mt_error_mask_95_64 = (mask << 4) & 0xFFFFFFF0;
	ctrl->mem_test_mt_error_mask_3.mt_error_mask_127_96 = (mask >> 28) & 0xFFFFFFFF;
	ctrl->mem_test_mt_error_mask_4.mt_error_mask_159_128 = ((mask << 8) & 0xFFFFFF00)  | ((mask_h >> 28) & 0xF);
	ctrl->mem_test_mt_error_mask_5.mt_error_mask_191_160 = (mask >> 24) & 0xFFFFFFFF;
	ctrl->mem_test_mt_error_mask_6.mt_error_mask_223_192 = ((mask << 12) & 0xFFFFF000) | ((mask_h >> 24) & 0xFF);
	ctrl->mem_test_mt_error_mask_7.mt_error_mask_255_224 = (mask >> 20) & 0xFFFFFFFF;
	ctrl->mem_test_mt_error_mask_8.mt_error_mask_287_256 = ((mask << 16) & 0xFFFF0000) | ((mask_h >> 20) & 0xFFF);
	ctrl->mem_test_mt_error_mask_9.mt_error_mask_319_288 = (mask >> 16) & 0xFFFFFFFF;
	ctrl->mem_test_mt_error_mask_10.mt_error_mask_351_320 = ((mask << 20) & 0xFFF00000) | ((mask_h >> 16) & 0xFFFF);
	ctrl->mem_test_mt_error_mask_11.mt_error_mask_383_352 = (mask >> 12) & 0xFFFFFFFF;
	ctrl->mem_test_mt_error_mask_12.mt_error_mask_415_384 = ((mask << 24) & 0xFF000000) | ((mask_h >> 12) & 0xFFFFF);
	ctrl->mem_test_mt_error_mask_13.mt_error_mask_447_416 = (mask >> 8) & 0xFFFFFFFF;
	ctrl->mem_test_mt_error_mask_14.mt_error_mask_479_448 = ((mask << 28) & 0xF0000000) | ((mask_h >> 8) & 0xFFFFFF);
	ctrl->mem_test_mt_error_mask_15.mt_error_mask_511_480 = (mask >> 4) & 0xFFFFFFFF;
	ctrl->mem_test_mt_error_mask_16.mt_error_mask_543_512 = (mask_h >> 4) & 0x0FFFFFFF;

	if ((pattern & 0xF) == TP_USER) {
		ctrl->mem_test_mt_user_data_pattern.mt_user_data_pattern = pat_user;
	}

	ctrl->mem_test_mt_data_pattern.mt_data_pattern = pattern & 0xF;
	ctrl->mem_test_mt_addr_pattern.mt_addr_pattern = 0x0;	// counting address pattern
	// ctrl->mem_test_mt_addr_pattern.mt_addr_pattern = 0x1;	// Pseudo-Random address pattern
	ctrl->mem_test_mt_data_invert.mt_data_invert = 0x0;
	ctrl->mem_test_mt_addr_bits.mt_addr_bits = nbits & MT_ADDR_BIT_MASK;
	ctrl->mem_test_mt_start_addr_0.mt_start_addr = addr & MT_ADDR_MASK;

	ctrl->mem_test_mt_en_single.mt_en_single = 0x1;
	_WAIT(ctrl->mem_test_mt_done_ack.val, 0x1);
	ctrl->mem_test_mt_en_single.mt_en_single = 0x0;

	// check test pass/fail
	rdata = ctrl->mem_test_mt_error_sts.val;

	if ((rdata & 0x1) == 0x1) {
		return 1;	// error
	} else {
		return 0;
	}
}

/**
 * Need to call before Memory Test Algorithm
 */
void mt_alg_pre(uint32_t chiplet_id, uint32_t ch)
{
	uint32_t rdata;
	volatile struct ddr_csr *ctrl = get_hbm_cfg(chiplet_id)->csr_base[ch];

	/* disable ecc & ecs */
	_SAVE(cfg_ecc_correction_en, ctrl->ecc_config_cfg_ecc_correction_en.cfg_ecc_correction_en & 0x1);
	ctrl->ecc_config_cfg_ecc_correction_en.cfg_ecc_correction_en = 0x0;

	_SAVE(init_ecc_scrub_en, ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en & 0x1);
	_SAVE(cfg_ecc_scrub_init_rmw,
		  ctrl->ecc_config_cfg_ecc_scrub_init_rmw.cfg_ecc_scrub_init_rmw & 0x1);
	ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en = 0x0;
	ctrl->ecc_config_cfg_ecc_scrub_init_rmw.cfg_ecc_scrub_init_rmw = 0x0;

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

	rdata = ctrl->mem_test_mt_error_sts.val;	// clear error status
	printf("ready for mt_alg_test %u\n", rdata);
}

/**
 * Need to call after Memory Test Algorithm
 */
void mt_alg_post(uint32_t chiplet_id, uint32_t ch)
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
	ctrl->ecc_config_cfg_ecc_correction_en.cfg_ecc_correction_en = mt_saved._cfg_ecc_correction_en;
	ctrl->ecc_config_cfg_ecc_scrub_init_rmw.cfg_ecc_scrub_init_rmw = mt_saved._cfg_ecc_scrub_init_rmw;
	ctrl->ecc_config_init_ecc_scrub_en.init_ecc_scrub_en = mt_saved._init_ecc_scrub_en;
	ctrl->mc_base5_init_idle_time_to_power_down.init_idle_time_to_power_down =
		mt_saved._init_idle_time_to_power_down;
}

int mt_alg_test_internal(uint32_t chiplet_id, uint32_t ch, uint64_t addr, unsigned int bits, enum TEST_PATTERN pattern)
{
	uint32_t start_addr = (uint32_t)(addr >> 6) & MT_ADDR_MASK;
	uint32_t end_addr = start_addr + BIT(bits);
	uint8_t pat_user = 0x55;

	if (bits < MTBITS_512B || bits > MTBITS_MAX) {
		printf("bits is out of range\n");
		return 1;
	} else if (end_addr > MAX_ADDR_RANGE) {
		printf("addr is out of max\n");
		return 1;
	}

	return memtest_alg(chiplet_id, ch, start_addr, bits, pattern, pat_user, true);
}

int mt_alg_test(uint32_t chiplet_id, uint32_t ch)
{
	uint32_t addr = 0;
	uint32_t bits = MTBITS_256MB;

	return mt_alg_test_internal(chiplet_id, ch, addr, bits, TP_USER);
}

int mt_alg_dq_eom(uint32_t chiplet_id, uint32_t ch, uint8_t dq)
{
	uint32_t addr = 0;
	enum mt_bits bits = 0;
	uint32_t pattern = TP_NREPSEUDO;
	uint8_t pat_user = 0x55;
	uint32_t start_addr = (uint32_t)(addr >> 6) & MT_ADDR_MASK;

	bits = MTBITS_256MB;

	if (memtest_alg_dq(chiplet_id, ch, start_addr, bits, pattern, pat_user, dq)) {
		return 1;
	}

	// 2GB
	start_addr = start_addr + BIT(MTBITS_256MB);
	bits = MTBITS_2GB;

	if (memtest_alg_dq(chiplet_id, ch, start_addr, bits, pattern, pat_user, dq)) {
		return 1;
	}

	return 0;
}

/**
 * Test All Memory Region per Channel
 */
int mt_alg_channel_eom(uint32_t chiplet_id, uint32_t ch)
{
	uint32_t addr = 0;
	enum mt_bits bits = 0;
	uint32_t pattern = TP_NREPSEUDO;
	uint8_t pat_user = 0x55;
	uint32_t start_addr = (uint32_t)(addr >> 6) & MT_ADDR_MASK;

	bits = MTBITS_256MB;

	if (memtest_alg(chiplet_id, ch, start_addr, bits, pattern, pat_user, false)) {
		return 1;
	}

	// 2GB
	start_addr = start_addr + BIT(MTBITS_256MB);
	bits = MTBITS_2GB;

	if (memtest_alg(chiplet_id, ch, start_addr, bits, pattern, pat_user, false)) {
		return 1;
	}

	return 0;
}
