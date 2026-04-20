/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */
#include "aw_ucie.h"
#include "aw_ucie_reg.h"
#ifdef USE_DILIGENT_PTR
	#include "diligent_ptr.h"
#endif /* USE_DILIGENT_PTR */
#include "test_aw_ucie_util.h"
#include "rl_utils.h"
#include "rl_errors.h"
#include "unity_fixture.h"
#include "stdbool.h"

static struct aw_ucie *mmio_ptr;
static struct aw_ucie *wr_buf_ptr;
static const int32_t ucie_ss_id = UCIE_SS_H00_ID;

TEST_GROUP(ucie_training);

TEST_SETUP(ucie_training)
{
	CLEAR_SNAPSHOT_ARR(reg[ucie_ss_id]);
	CLEAR_SNAPSHOT_ARR(target_ss);

	init_mmio_map(ucie_ss_id);

	mmio_ptr = get_aw_ucie_mmio_var();
	wr_buf_ptr = get_aw_ucie_mmio_write_buf();
	real_map = get_aw_ucie_real_map();

	PAUSE(target_ss);
	aw_ucie_init(ucie_ss_id, real_map);
	aw_ucie_set_target_ss(ucie_ss_id);
	RESUME(target_ss);
}

TEST_TEAR_DOWN(ucie_training)
{
	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);
}

static void _training_mock_status_setting(uint32_t before_link_stat, uint32_t done_link_stat,
										  uint32_t link_ctrl)
{
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val = before_link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read. */
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, mmio_ptr);/* for write. and some bits may be cleard */

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.val = link_ctrl;
	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.lcntrl_start_ucie_link_training = 1;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_link_train_or_retrain = 1;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read. */

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read UCIe Link Control. */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read UCIe Link Control. */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read UCIe Link Control. */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read UCIe Link Control. */

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.lcntrl_start_ucie_link_training = 0;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read UCIe Link Control. */

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val = done_link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read. */
}

static int32_t _training_w_spcf_regs(uint32_t before_link_stat, uint32_t done_link_stat,
									 uint32_t link_ctrl, uint32_t phy_ctrl)
{
	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.val = link_ctrl;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	aw_ucie_set_link_control(link_ctrl);

	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_phy_cntrl.val = phy_ctrl;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	aw_ucie_set_phy_control(phy_ctrl);

	_training_mock_status_setting(before_link_stat, done_link_stat, link_ctrl);
	return aw_ucie_link_training();
}

TEST(ucie_training, training_success_w_default_config)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_default_link_stat() };

	TEST_ASSERT_EQUAL(RL_OK,
					  _training_w_spcf_regs(link_stat.val,
											get_done_link_stat(),
											get_default_link_ctrl(),
											get_default_phy_ctrl())
	);

	link_stat.lstatus_link_status_change = ENABLE;
	link_stat.lstatus_link_train_or_retrain = DISABLE;
	link_stat.lstatus_link_status = ENABLE;
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status = link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
	TEST_ASSERT_EQUAL(ENABLE, link_stat.lstatus_link_status_change);
	TEST_ASSERT_EQUAL(DISABLE, link_stat.lstatus_link_train_or_retrain);
}

TEST(ucie_training, training_success_when_link_was_already_up)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_default_link_stat() };

	TEST_ASSERT_EQUAL(RL_OK,
					  _training_w_spcf_regs(get_default_link_stat(),
											get_done_link_stat(),
											get_default_link_ctrl(),
											get_default_phy_ctrl())
	);

	link_stat.lstatus_link_status = ENABLE;/* link status is already up */
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status = link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read. */
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
	TEST_ASSERT_EQUAL(ENABLE, link_stat.lstatus_link_status);
	/* pre-condition done */

	link_stat.lstatus_link_status = ENABLE;/* link status is already up */
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status = link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read. */
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, mmio_ptr);/* for write. and some bits may be cleard */

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.val = get_default_link_ctrl();
	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.lcntrl_start_ucie_link_training =
		ENABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);/* for write UCIe Link Control */

	link_stat.lstatus_link_status_change = ENABLE;
	link_stat.lstatus_link_train_or_retrain = ENABLE;
	link_stat.lstatus_link_status = DISABLE;
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status = link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read. */
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, mmio_ptr);/* for write. */

	link_stat.lstatus_link_status_change = DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read UCIe Link Control. */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read UCIe Link Control. */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read UCIe Link Control. */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read UCIe Link Control. */

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.lcntrl_start_ucie_link_training =
		DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read UCIe Link Control. */

	link_stat.lstatus_link_status_change = ENABLE;
	link_stat.lstatus_link_train_or_retrain = DISABLE;
	link_stat.lstatus_link_status = ENABLE;
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status = link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read. */

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_training());

	/* need to check whether the link go through full training from Link Down state */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* for read. */
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
	TEST_ASSERT_EQUAL(ENABLE, link_stat.lstatus_link_status_change);
	TEST_ASSERT_EQUAL(DISABLE, link_stat.lstatus_link_train_or_retrain);
}

/* Only for Mock */
TEST(ucie_training, training_fail_when_trainig_already_ongoing)
{
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val = get_default_link_stat();
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_link_train_or_retrain = ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	TEST_ASSERT_EQUAL(RL_BUSY, aw_ucie_link_training());
}

/* Only for Mock */
TEST(ucie_training, training_fail_due_to_keeping_training_status_after_ending_training)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_done_link_stat() };

	link_stat.lstatus_link_train_or_retrain = ENABLE;

	TEST_ASSERT_EQUAL(RL_ERROR,
					  _training_w_spcf_regs(get_default_link_stat(),
											link_stat.val,
											get_default_link_ctrl(),
											get_default_phy_ctrl()
		)
	);
}

/* Only for Mock */
TEST(ucie_training, training_fail_due_to_keeping_link_down_after_ending_training)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_done_link_stat() };

	link_stat.lstatus_link_status = DISABLE;
	TEST_ASSERT_EQUAL(RL_ERROR,
					  _training_w_spcf_regs(get_default_link_stat(),
											link_stat.val,
											get_default_link_ctrl(),
											get_default_phy_ctrl()
		)
	);
}

/**
 * It should be moved to upper level layer test.
 * Otherwise hw would resume training by remote SB msg.
 * So this test should be performed on both sides at the same time.
 */
TEST(ucie_training, training_with_initialization_and_debug_register)
{
	/* check each Initialization control value is worked well. */
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_init_debug init_debug = {};
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_done_link_stat() };
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_err_log0 err_log0 = {};
	/* union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_err_log1 err_log1 = {}; */
	uint32_t init_control[5] = {0/* LINKINIT */, 1/* MBINIT.CAL? */, 2/* MBTRAIN.VALREF? */,
					3/* MBTRAIN.RXDESKEW */, 4/* MBTRAIN.DATATRAINCENTER2 */};
	uint32_t state_n_1[5] = {LTSM_LINKINIT, LTSM_MBINIT_CAL, LTSM_MBTRAIN_VALVREF,
					LTSM_MBTRAIN_RXDESKEW, LTSM_MBTRAIN_DATATRAINCENTER2};
	uint32_t idx = 0;

	for (; idx < ARRAY_SIZE(init_control); ++idx) {
		init_debug.init_debug_init_cntrl = init_control[idx];

		*wr_buf_ptr = *mmio_ptr;
		wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_phy_init_debug = init_debug;
		PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
		aw_ucie_set_phy_init_debug(init_debug.val);

		link_stat.lstatus_link_status = (idx == 0) ? ENABLE : DISABLE;
		TEST_ASSERT_EQUAL((idx == 0) ? RL_OK : RL_ERROR,
						  _training_w_spcf_regs(get_default_link_stat(), link_stat.val,
												get_default_link_ctrl(),
												get_default_phy_ctrl()));

		/* check if Error Log 0/1 indiates corresponding state N and State (N-1), (N-2) and (N-3) */
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_err_log0.m0_state_n1 = state_n_1[idx];
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_err_log0(0, &err_log0.val));
		TEST_ASSERT_EQUAL(state_n_1[idx], err_log0.m0_state_n1);

		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_err_log0.m1_state_n1 = state_n_1[idx];
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_err_log0(1, &err_log0.val));
		TEST_ASSERT_EQUAL(state_n_1[idx], err_log0.m0_state_n1);
	}
}

TEST(ucie_training, training_with_multi_stack_enable_disable_of_link_control_register)
{
	uint32_t multi_stack_en = DISABLE;

	while (multi_stack_en <= ENABLE) {
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl = {
			.val = get_default_link_ctrl() };

		link_ctrl.lcntrl_multi_stack_en = multi_stack_en;

		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												link_ctrl.val, get_default_phy_ctrl())
		);

		/* rigel doesn't support multi stack */
		mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_multi_stack_en = DISABLE;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
		TEST_ASSERT_EQUAL(RL_OK, link_stat.lstatus_multi_stack_en);
		multi_stack_en++;
	}
}

TEST(ucie_training, training_with_all_target_link_width_of_link_control_register)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl = {
		.val = get_default_link_ctrl() };

	uint32_t target_link_width = TARGET_LINK_WIDTH_X16;

	while (target_link_width <= TARGET_LINK_WIDTH_X32) {
		link_ctrl.lcntrl_target_link_width = target_link_width;
		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												link_ctrl.val, get_default_phy_ctrl())
		);

		mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_link_width_en =
			target_link_width;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat;

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
		TEST_ASSERT_EQUAL(link_stat.lstatus_link_width_en, target_link_width);

		target_link_width++;
	}
}

TEST(ucie_training, training_with_all_target_link_speed_of_link_control_register)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl = {
		.val = get_default_link_ctrl() };

	uint32_t target_link_speed = TARGET_LINK_SPEED_4GT;

	while (target_link_speed <= TARGET_LINK_SPEED_32GT) {
		link_ctrl.lcntrl_target_link_speed = target_link_speed;
		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												link_ctrl.val, get_default_phy_ctrl())
		);

		mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_link_speed_en =
			target_link_speed;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat;

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
		TEST_ASSERT_EQUAL(link_stat.lstatus_link_speed_en, target_link_speed);

		target_link_speed++;
	}
}

TEST(ucie_training, training_with_phy_layer_clock_gating_enable_disable_of_link_control_register)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl = {
		.val = get_default_link_ctrl() };

	uint32_t phy_layer_clock_gating = DISABLE;

	while (phy_layer_clock_gating <= ENABLE) {
		link_ctrl.lcntrl_phy_layer_clk_gating_en = phy_layer_clock_gating;
		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												link_ctrl.val, get_default_phy_ctrl())
		);

		phy_layer_clock_gating++;
	}
}

static void _train_w_spc_flit(uint32_t flit_form, bool raw, bool _68b,
							  bool std_end, bool std_stt, bool lat_wo, bool lat_w)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {};
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log2 d2d_hdr_log2;
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1 adv_adp_log1 = {};
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log1 fin_adp_log1 = {};

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl = {
		.val = get_default_link_ctrl() };

	link_ctrl.lcntrl_raw_format_en = raw;
	link_ctrl.lcntrl_68b_flit_fmt_strmng = _68b;
	link_ctrl.lcntrl_std_256b_end_hdr_flit_fmt_strmng = std_end;
	link_ctrl.lcntrl_std_256b_start_hdr_flit_fmt_strmng = std_stt;
	link_ctrl.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng = lat_wo;
	link_ctrl.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng = lat_w;

	TEST_ASSERT_EQUAL(RL_OK,
					  _training_w_spcf_regs(get_default_link_stat(),
											get_done_link_stat(),
											link_ctrl.val,
											get_default_phy_ctrl()
					  )
	);

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_flit_format_status = flit_form;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
	TEST_ASSERT_EQUAL(flit_form, link_stat.lstatus_flit_format_status);

	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_hdr_log2.flit_format = flit_form;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_hdr_log2(&d2d_hdr_log2.val));
	TEST_ASSERT_EQUAL(flit_form, d2d_hdr_log2.flit_format);

	adv_adp_log1.raw_format = link_ctrl.lcntrl_raw_format_en;
	adv_adp_log1._68b_flit_format = link_ctrl.lcntrl_68b_flit_fmt_strmng;
	adv_adp_log1.std_256b_end_header_flit_format =
		link_ctrl.lcntrl_std_256b_end_hdr_flit_fmt_strmng;
	adv_adp_log1.std_256b_start_header_flit_format =
		link_ctrl.lcntrl_std_256b_start_hdr_flit_fmt_strmng;
	adv_adp_log1.latopt_256b_wo_opt_flit_format =
		link_ctrl.lcntrl_lat_opt_256b_flit_fmt_no_optnl_bytes_strmng;
	adv_adp_log1.latopt_256b_w_opt_flit_format =
		link_ctrl.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng;
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1 =
		adv_adp_log1;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_adv_adp_log1(&adv_adp_log1.val));
	TEST_ASSERT_EQUAL(link_ctrl.lcntrl_raw_format_en, adv_adp_log1.raw_format);
	TEST_ASSERT_EQUAL(link_ctrl.lcntrl_68b_flit_fmt_strmng, adv_adp_log1._68b_flit_format);
	TEST_ASSERT_EQUAL(link_ctrl.lcntrl_std_256b_end_hdr_flit_fmt_strmng,
					  adv_adp_log1.std_256b_end_header_flit_format);
	TEST_ASSERT_EQUAL(link_ctrl.lcntrl_std_256b_start_hdr_flit_fmt_strmng,
					  adv_adp_log1.std_256b_start_header_flit_format);
	TEST_ASSERT_EQUAL(link_ctrl.lcntrl_lat_opt_256b_flit_fmt_no_optnl_bytes_strmng,
					  adv_adp_log1.latopt_256b_wo_opt_flit_format);
	TEST_ASSERT_EQUAL(link_ctrl.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng,
					  adv_adp_log1.latopt_256b_w_opt_flit_format);

	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log1.val = 0;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK,
					  aw_ucie_get_d2d_fin_adp_log1(&fin_adp_log1.val));
	TEST_ASSERT_EQUAL(0, fin_adp_log1.val);

	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);

	CLEAR_SNAPSHOT_ARR(reg[ucie_ss_id]);
	CLEAR_SNAPSHOT_ARR(target_ss);
}

/**
 * Table 3-10 (Truth Table 2) provides the Truth Table for determining the Flit Format for Streaming
 * Protocols if Streaming Flit Format capability is negotiated.
 * [Table 3-10] Truth Table 2
 *			|   Raw   |   68B   | Std end | Std stt | Lat w/o | Lat w/
 * Raw		|    1    |    x    |    x    |    x    |    x    |    x
 * 68B		|    0    |    1    |    0    |    0    |    x    |    0
 * Std end	|    0    |    x    |    1    |    0    |    x    |    0
 * Std std	|    0    |    x    |    x    |    1    |    x    |    0
 * Lat w/o	|    0    |    0    |    0    |    0    |    1    |    0
 * Lat w/	|    0    |    x    |    x    |    x    |    x    |    1
 * 'x' indicates 'don't care'.
 */
TEST(ucie_training, training_with_raw_flit_formats_of_link_control_register)
{
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_ENA, X_ENA, X_ENA, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_ENA, X_ENA, X_ENA, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_ENA, X_ENA, X_DIS, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_ENA, X_ENA, X_DIS, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_ENA, X_DIS, X_ENA, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_ENA, X_DIS, X_ENA, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_ENA, X_DIS, X_DIS, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_ENA, X_DIS, X_DIS, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_DIS, X_ENA, X_ENA, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_DIS, X_ENA, X_ENA, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_DIS, X_ENA, X_DIS, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_DIS, X_ENA, X_DIS, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_DIS, X_DIS, X_ENA, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_DIS, X_DIS, X_ENA, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_DIS, X_DIS, X_DIS, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_ENA, X_DIS, X_DIS, X_DIS, X_DIS);

	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_ENA, X_ENA, X_ENA, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_ENA, X_ENA, X_ENA, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_ENA, X_ENA, X_DIS, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_ENA, X_ENA, X_DIS, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_ENA, X_DIS, X_ENA, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_ENA, X_DIS, X_ENA, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_ENA, X_DIS, X_DIS, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_ENA, X_DIS, X_DIS, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_DIS, X_ENA, X_ENA, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_DIS, X_ENA, X_ENA, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_DIS, X_ENA, X_DIS, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_DIS, X_ENA, X_DIS, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_DIS, X_DIS, X_ENA, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_DIS, X_DIS, X_ENA, X_DIS);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_DIS, X_DIS, X_DIS, X_ENA);
	_train_w_spc_flit(FLIT_FORMAT_1_RAW, ENABLE, X_DIS, X_DIS, X_DIS, X_DIS, X_DIS);
}

TEST(ucie_training, training_with_lat_w_formats_of_link_control_register)
{
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_ENA, X_ENA, X_ENA, X_ENA, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_ENA, X_ENA, X_ENA, X_DIS, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_ENA, X_ENA, X_DIS, X_ENA, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_ENA, X_ENA, X_DIS, X_DIS, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_ENA, X_DIS, X_ENA, X_ENA, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_ENA, X_DIS, X_ENA, X_DIS, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_ENA, X_DIS, X_DIS, X_ENA, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_ENA, X_DIS, X_DIS, X_DIS, ENABLE);

	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_DIS, X_ENA, X_ENA, X_ENA, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_DIS, X_ENA, X_ENA, X_DIS, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_DIS, X_ENA, X_DIS, X_ENA, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_DIS, X_ENA, X_DIS, X_DIS, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_DIS, X_DIS, X_ENA, X_ENA, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_DIS, X_DIS, X_ENA, X_DIS, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_DIS, X_DIS, X_DIS, X_ENA, ENABLE);
	_train_w_spc_flit(FLIT_FORMAT_6_LAT_256_W, DISABLE, X_DIS, X_DIS, X_DIS, X_DIS, ENABLE);
}

/**
 * It should be moved to upper level layer test.
 * This test check detail reason of link training fail after ending training.
 * But 'aw_ucie_link_training' is not the stage that analize detailed error result.
 * And Test seq also is wrong, it should be changed.
 */
TEST(ucie_training, training_with_invalid_flit_formats_of_link_control_register_w_unmasking)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl = {
		.val = get_default_link_ctrl() };

	/* in latopt 256B with optional bytes, raw_moe must be disabled. */
	link_ctrl.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng = ENABLE;
	link_ctrl.lcntrl_raw_format_en = ENABLE;

	for (int fatal_flag = DISABLE; fatal_flag <= ENABLE; ++fatal_flag) {
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
			.val = get_done_link_stat() };
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat uncorr_err_stat;
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity uncorr_err_severity;
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log2 d2d_hdr_log2;

		init_mmio_map(ucie_ss_id);
		uncorr_err_severity.invld_param_exchange_severity = fatal_flag;

		/* unmasking before test */
		*wr_buf_ptr = *mmio_ptr;
		wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask.invld_param_exchange_mask =
			DISABLE;
		PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
		uint32_t val = wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask.val;

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_d2d_uncorr_err_mask(val));

		*wr_buf_ptr = *mmio_ptr;
		wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity = uncorr_err_severity;
		PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_d2d_uncorr_err_severity(uncorr_err_severity.val));

		/* status clear before test */
		wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat.invld_param_exchange = ENABLE;
		PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
		val = wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat.val;
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_d2d_uncorr_err_status(val));

		link_stat.lstatus_link_status = DISABLE;
		TEST_ASSERT_EQUAL(RL_ERROR,
						  _training_w_spcf_regs(get_default_link_stat(), link_stat.val,
												link_ctrl.val, get_default_phy_ctrl())
		);

		mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat.invld_param_exchange = ENABLE;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_uncorr_err_status(&uncorr_err_stat.val));
		TEST_ASSERT_EQUAL(ENABLE, uncorr_err_stat.invld_param_exchange);

		/* Invalid Param Exchange */
		mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_hdr_log2.first_fatal_err_indicator = 1 << 4;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_hdr_log2(&d2d_hdr_log2.val));
		TEST_ASSERT_EQUAL(1 << 4, d2d_hdr_log2.first_fatal_err_indicator);

		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_uncorr_err_severity(&uncorr_err_severity.val));
if (uncorr_err_severity.invld_param_exchange_severity == ENABLE) {
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_ucie_link_uncorr_fatal_err =
		ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
	TEST_ASSERT_EQUAL(ENABLE, link_stat.lstatus_ucie_link_uncorr_fatal_err);
} else {
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_ucie_link_uncorr_non_fatal_err =
		ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
	TEST_ASSERT_EQUAL(ENABLE, link_stat.lstatus_ucie_link_uncorr_non_fatal_err);
}

	}
}

/**
 * It is the same case as the above.
 */
TEST(ucie_training, training_with_invalid_flit_formats_of_link_control_register_w_masking)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl = {
		.val = get_default_link_ctrl() };

	/* in latopt 256B with optional bytes, raw_moe must be disabled. */
	link_ctrl.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng = ENABLE;
	link_ctrl.lcntrl_raw_format_en = ENABLE;

	for (int fatal_flag = DISABLE; fatal_flag <= ENABLE; ++fatal_flag) {
		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
			.val = get_done_link_stat() };
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat uncorr_err_stat;
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity uncorr_err_severity;
		union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_hdr_log2 d2d_hdr_log2;

		init_mmio_map(ucie_ss_id);
		uncorr_err_severity.invld_param_exchange_severity = fatal_flag;

		/* unmasking before test */
		*wr_buf_ptr = *mmio_ptr;
		wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask.invld_param_exchange_mask =
			ENABLE;
		PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
		uint32_t val;

		val = wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask.val;
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_d2d_uncorr_err_mask(val));

		*wr_buf_ptr = *mmio_ptr;
		wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity = uncorr_err_severity;
		PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_d2d_uncorr_err_severity(uncorr_err_severity.val));

		/* status clear before test */
		wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat.invld_param_exchange = ENABLE;
		PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
		val = wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat.val;
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_d2d_uncorr_err_status(val));

		link_stat.lstatus_link_status = DISABLE;
		TEST_ASSERT_EQUAL(RL_ERROR,
						  _training_w_spcf_regs(get_default_link_stat(), link_stat.val,
												link_ctrl.val, get_default_phy_ctrl())
		);

		mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat.invld_param_exchange = ENABLE;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_uncorr_err_status(&uncorr_err_stat.val));
		TEST_ASSERT_EQUAL(ENABLE, uncorr_err_stat.invld_param_exchange);

		/* Invalid Param Exchange */
		mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_hdr_log2.first_fatal_err_indicator = 1 << 4;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_hdr_log2(&d2d_hdr_log2.val));
		TEST_ASSERT_EQUAL(1 << 4, d2d_hdr_log2.first_fatal_err_indicator);

		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_uncorr_err_severity(&uncorr_err_severity.val));
if (uncorr_err_severity.invld_param_exchange_severity == ENABLE) {
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_ucie_link_uncorr_fatal_err =
		ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
	TEST_ASSERT_EQUAL(ENABLE, link_stat.lstatus_ucie_link_uncorr_fatal_err);
} else {
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_ucie_link_uncorr_non_fatal_err =
		ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
	TEST_ASSERT_EQUAL(ENABLE, link_stat.lstatus_ucie_link_uncorr_non_fatal_err);
}

	}
}

TEST(ucie_training, training_with_enhanced_multi_protocol_enable_disable_of_link_control_register)
{
	uint32_t enh_multi_stack_en = DISABLE;
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl = {
		.val = get_default_link_ctrl() };

	while (enh_multi_stack_en <= ENABLE) {
		link_ctrl.lcntrl_enhanced_multi_protocol_cap = enh_multi_stack_en;

		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												link_ctrl.val, get_default_phy_ctrl())
		);

		/* rigel doesn't support multi stack */
		mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_enhanced_multi_protocol_en =
			DISABLE;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
		TEST_ASSERT_EQUAL(DISABLE, link_stat.lstatus_enhanced_multi_protocol_en);
		enh_multi_stack_en++;
	}
}

TEST(ucie_training, training_with_random_configuration_of_link_control_register)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl = {
		.val = get_default_link_ctrl() };
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_default_link_stat() };
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1 adv_adp_log1 = {};
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log1 fin_adp_log1 = {};

	uint32_t flit_format = FLIT_FORMAT_1_RAW;

	link_ctrl.lcntrl_multi_stack_en = get_random_of_range(DISABLE, ENABLE);
	link_ctrl.lcntrl_target_link_width = get_random_of_range(TARGET_LINK_WIDTH_X16,
															 TARGET_LINK_WIDTH_X64);
	link_ctrl.lcntrl_target_link_speed = get_random_of_range(TARGET_LINK_SPEED_4GT,
															 TARGET_LINK_SPEED_16GT);
	link_ctrl.lcntrl_phy_layer_clk_gating_en = get_random_of_range(DISABLE, ENABLE);
	link_ctrl.lcntrl_enhanced_multi_protocol_cap = get_random_of_range(DISABLE, ENABLE);

	while (flit_format <= FLIT_FORMAT_6_LAT_256_W) {
		link_ctrl.lcntrl_68b_flit_fmt_strmng = get_random_of_range(DISABLE, ENABLE);
		link_ctrl.lcntrl_std_256b_end_hdr_flit_fmt_strmng = get_random_of_range(DISABLE, ENABLE);
		link_ctrl.lcntrl_std_256b_start_hdr_flit_fmt_strmng = get_random_of_range(DISABLE, ENABLE);
		link_ctrl.lcntrl_lat_opt_256b_flit_fmt_no_optnl_bytes_strmng = get_random_of_range(DISABLE,
																						   ENABLE);
		/* link_ctrl.lcntrl_std_start_hdr_flit_pcie = get_random_of_range(DISABLE, ENABLE); */
		/* link_ctrl.lcntrl_lat_opt_flit_optnl_bytes_pcie = get_random_of_range(DISABLE, ENABLE); */

		if (flit_format == FLIT_FORMAT_1_RAW) {
			link_ctrl.lcntrl_raw_format_en = ENABLE;
			link_ctrl.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng = get_random_of_range(DISABLE,
																							ENABLE);
		} else {
			link_ctrl.lcntrl_raw_format_en = DISABLE;
			link_ctrl.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng = ENABLE;
		}
		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												link_ctrl.val, get_default_phy_ctrl())
		);

		/* check result */
		link_stat.lstatus_multi_stack_en = link_ctrl.lcntrl_multi_stack_en;
		link_stat.lstatus_enhanced_multi_protocol_en = link_ctrl.lcntrl_enhanced_multi_protocol_cap;
		link_stat.lstatus_link_width_en = link_ctrl.lcntrl_target_link_width;
		link_stat.lstatus_link_speed_en = link_ctrl.lcntrl_target_link_speed;
		link_stat.lstatus_flit_format_status = flit_format;
		mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status = link_stat;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
		TEST_ASSERT_EQUAL(link_ctrl.lcntrl_multi_stack_en, link_stat.lstatus_multi_stack_en);
		TEST_ASSERT_EQUAL(link_ctrl.lcntrl_enhanced_multi_protocol_cap,
						  link_stat.lstatus_enhanced_multi_protocol_en);
		TEST_ASSERT_EQUAL(link_ctrl.lcntrl_target_link_width, link_stat.lstatus_link_width_en);
		TEST_ASSERT_EQUAL(link_ctrl.lcntrl_target_link_speed, link_stat.lstatus_link_speed_en);
		TEST_ASSERT_EQUAL(flit_format, link_stat.lstatus_flit_format_status);

		adv_adp_log1.streaming = ENABLE;
		adv_adp_log1.retry = ENABLE;
		adv_adp_log1.stack0_enable = ENABLE;
		adv_adp_log1.raw_format = link_ctrl.lcntrl_raw_format_en;
		adv_adp_log1.latopt_256b_w_opt_flit_format =
			link_ctrl.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng;
		mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1 = adv_adp_log1;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_adv_adp_log1(&adv_adp_log1.val));
		TEST_ASSERT_EQUAL(link_ctrl.lcntrl_raw_format_en, adv_adp_log1.raw_format);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1._68b_flit_mode);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.cxl_256b_flit_mode);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.pcie_flit_mode);
		TEST_ASSERT_EQUAL(ENABLE, adv_adp_log1.streaming);
		TEST_ASSERT_EQUAL(ENABLE, adv_adp_log1.retry);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.multi_protocol_enable);
		TEST_ASSERT_EQUAL(ENABLE, adv_adp_log1.stack0_enable);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.stack1_enable);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.cxl_latopt_fmt5);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.cxl_latopt_fmt6);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.retimer);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.retimer_credits);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.dp);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.up);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1._68b_flit_format);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.std_256b_end_header_flit_format);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.std_256b_start_header_flit_format);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.latopt_256b_wo_opt_flit_format);
		TEST_ASSERT_EQUAL(link_ctrl.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng,
						  adv_adp_log1.latopt_256b_w_opt_flit_format);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.enhanced_multi_protocol_enable);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.stack_0_max_bandwidth_limit);
		TEST_ASSERT_EQUAL(DISABLE, adv_adp_log1.stack_1_max_bandwidth_limit);

		mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log1.val = 0;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_fin_adp_log1(&fin_adp_log1.val));
		TEST_ASSERT_EQUAL(0, fin_adp_log1.val);

		if (flit_format == FLIT_FORMAT_1_RAW) {
			flit_format = FLIT_FORMAT_6_LAT_256_W;
		} else {
			break;
		}
	}
}

TEST(ucie_training, training_fail_with_byte_mapping_disable_of_phy_control_register)
{
	mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_cntrl.val = get_default_phy_ctrl();
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl phy_ctrl = {};

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_control(&phy_ctrl.val));
	phy_ctrl.cntrl_mod_to_byte_map = DISABLE;

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_done_link_stat() };

	link_stat.lstatus_link_status = DISABLE;
	TEST_ASSERT_EQUAL(RL_ERROR,
					  _training_w_spcf_regs(get_default_link_stat(), link_stat.val,
											get_default_link_ctrl(), phy_ctrl.val)
	);

	mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_stat.status_mod_to_byte_map = DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_stat phy_stat = {};

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_status(&phy_stat.val));
	/* The lanes of Rigel are reversaled */
	TEST_ASSERT_EQUAL(DISABLE, phy_stat.status_mod_to_byte_map);
}

TEST(ucie_training, training_with_rx_terminated_enable_disable_of_phy_control_register)
{
	uint32_t rx_terminated_en = DISABLE;

	while (rx_terminated_en <= ENABLE) {
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_cntrl.val = get_default_phy_ctrl();
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl phy_ctrl = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_control(&phy_ctrl.val));
		phy_ctrl.cntrl_rx_terminated_cntrl = rx_terminated_en;

		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												get_default_link_ctrl(), phy_ctrl.val)
		);

		mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_stat.status_rx_terminated_status = rx_terminated_en;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_stat phy_stat = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_status(&phy_stat.val));
		TEST_ASSERT_EQUAL(rx_terminated_en, phy_stat.status_rx_terminated_status);
		rx_terminated_en++;
	}
}

TEST(ucie_training, training_with_tx_equal_enable_disable_of_phy_control_register)
{
	uint32_t tx_equal_en = DISABLE;

	while (tx_equal_en <= ENABLE) {
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_cntrl.val = get_default_phy_ctrl();
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl phy_ctrl = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_control(&phy_ctrl.val));
		phy_ctrl.cntrl_tx_eq_en = tx_equal_en;

		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												get_default_link_ctrl(), phy_ctrl.val)
		);

		mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_stat.status_tx_eq_status = tx_equal_en;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_stat phy_stat = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_status(&phy_stat.val));
		TEST_ASSERT_EQUAL(tx_equal_en, phy_stat.status_tx_eq_status);
		tx_equal_en++;
	}
}

TEST(ucie_training, training_with_clock_mode_strobe_freerun_of_phy_control_register)
{
	uint32_t clock_mode = CLOCK_MODE_STROBE;

	while (clock_mode <= CLOCK_MODE_FREERUN) {
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_cntrl.val = get_default_phy_ctrl();
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl phy_ctrl = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_control(&phy_ctrl.val));
		phy_ctrl.cntrl_clk_mode_sel = clock_mode;

		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												get_default_link_ctrl(), phy_ctrl.val)
		);

		mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_stat.status_clk_mode_status = clock_mode;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_stat phy_stat = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_status(&phy_stat.val));
		TEST_ASSERT_EQUAL(clock_mode, phy_stat.status_clk_mode_status);
		clock_mode++;
	}
}

TEST(ucie_training, training_with_clock_phase_differ_quad_of_phy_control_register)
{
	uint32_t clock_phase = CLOCK_PHASE_DIFF;

	while (clock_phase <= CLOCK_PHASE_QUAD) {
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_cntrl.val = get_default_phy_ctrl();
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl phy_ctrl = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_control(&phy_ctrl.val));
		phy_ctrl.cntrl_clk_phase_sel = clock_phase;

		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												get_default_link_ctrl(), phy_ctrl.val)
		);

		mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_stat.status_clk_phase_status = clock_phase;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_stat phy_stat = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_status(&phy_stat.val));
		TEST_ASSERT_EQUAL(clock_phase, phy_stat.status_clk_phase_status);
		clock_phase++;
	}
}

TEST(ucie_training, training_with_force_x32_width_mode_of_phy_control_register)
{
	uint32_t force_x32_width = DISABLE;

	while (force_x32_width <= ENABLE) {
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_cntrl.val = get_default_phy_ctrl();
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl phy_ctrl = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_control(&phy_ctrl.val));
		phy_ctrl.cntrl_force_width_mode = force_x32_width;

		TEST_ASSERT_EQUAL(RL_OK,
						  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
												get_default_link_ctrl(), phy_ctrl.val)
		);

		mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val = get_default_link_stat();
mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_adv_pkg_mod_size = force_x32_width;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
		TEST_ASSERT_EQUAL(force_x32_width, link_stat.lstatus_adv_pkg_mod_size);
		force_x32_width++;
	}
}

TEST(ucie_training, training_with_random_configuration_of_phy_control_register)
{
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl phy_ctrl = {};

	phy_ctrl.cntrl_mod_to_byte_map = get_random_of_range(0, 1);
	phy_ctrl.cntrl_rx_terminated_cntrl = get_random_of_range(0, 1);
	phy_ctrl.cntrl_tx_eq_en = get_random_of_range(0, 1);
	phy_ctrl.cntrl_clk_mode_sel = get_random_of_range(0, 1);
	phy_ctrl.cntrl_clk_phase_sel = get_random_of_range(0, 1);
	phy_ctrl.cntrl_force_width_mode = get_random_of_range(0, 1);

	TEST_ASSERT_EQUAL(RL_OK,
					  _training_w_spcf_regs(get_default_link_stat(), get_done_link_stat(),
											get_default_link_ctrl(), phy_ctrl.val)
	);

	union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_stat phy_stat = {};

	phy_stat.status_mod_to_byte_map = phy_ctrl.cntrl_mod_to_byte_map;
	phy_stat.status_rx_terminated_status = phy_ctrl.cntrl_rx_terminated_cntrl;
	phy_stat.status_tx_eq_status = phy_ctrl.cntrl_tx_eq_en;
	phy_stat.status_clk_mode_status = phy_ctrl.cntrl_clk_mode_sel;
	phy_stat.status_clk_phase_status = phy_ctrl.cntrl_clk_phase_sel;
	mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_stat = phy_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_status(&phy_stat.val));
	TEST_ASSERT_EQUAL(phy_ctrl.cntrl_mod_to_byte_map, phy_stat.status_mod_to_byte_map);
	TEST_ASSERT_EQUAL(phy_ctrl.cntrl_rx_terminated_cntrl, phy_stat.status_rx_terminated_status);
	TEST_ASSERT_EQUAL(phy_ctrl.cntrl_tx_eq_en, phy_stat.status_tx_eq_status);
	TEST_ASSERT_EQUAL(phy_ctrl.cntrl_clk_mode_sel, phy_stat.status_clk_mode_status);
	TEST_ASSERT_EQUAL(phy_ctrl.cntrl_clk_phase_sel, phy_stat.status_clk_phase_status);

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_adv_pkg_mod_size =
		phy_ctrl.cntrl_force_width_mode;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {};

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
	TEST_ASSERT_EQUAL(phy_ctrl.cntrl_force_width_mode, link_stat.lstatus_adv_pkg_mod_size);
}

TEST_GROUP_RUNNER(ucie_training_except_only_for_mock)
{
	RUN_TEST_CASE(ucie_training, training_success_w_default_config);
	RUN_TEST_CASE(ucie_training, training_success_when_link_was_already_up);
	RUN_TEST_CASE(ucie_training,/* It should be moved to upper layer. */
				  training_with_initialization_and_debug_register);
	RUN_TEST_CASE(ucie_training, training_with_multi_stack_enable_disable_of_link_control_register);
	RUN_TEST_CASE(ucie_training, training_with_all_target_link_width_of_link_control_register);
	RUN_TEST_CASE(ucie_training, training_with_all_target_link_speed_of_link_control_register);
	RUN_TEST_CASE(ucie_training,
				  training_with_phy_layer_clock_gating_enable_disable_of_link_control_register);
	RUN_TEST_CASE(ucie_training, training_with_raw_flit_formats_of_link_control_register);
	RUN_TEST_CASE(ucie_training, training_with_lat_w_formats_of_link_control_register);
	RUN_TEST_CASE(ucie_training,/* It should be moved to upper layer. */
				  training_with_invalid_flit_formats_of_link_control_register_w_unmasking);
	RUN_TEST_CASE(ucie_training,/* It should be moved to upper layer. */
				  training_with_invalid_flit_formats_of_link_control_register_w_masking);
	RUN_TEST_CASE(ucie_training,
				  training_with_enhanced_multi_protocol_enable_disable_of_link_control_register);
	RUN_TEST_CASE(ucie_training, training_with_random_configuration_of_link_control_register);

	RUN_TEST_CASE(ucie_training, training_fail_with_byte_mapping_disable_of_phy_control_register);
	RUN_TEST_CASE(ucie_training,
				  training_with_rx_terminated_enable_disable_of_phy_control_register);
	RUN_TEST_CASE(ucie_training, training_with_tx_equal_enable_disable_of_phy_control_register);
	RUN_TEST_CASE(ucie_training, training_with_clock_mode_strobe_freerun_of_phy_control_register);
	RUN_TEST_CASE(ucie_training, training_with_clock_phase_differ_quad_of_phy_control_register);
	RUN_TEST_CASE(ucie_training, training_with_force_x32_width_mode_of_phy_control_register);
	RUN_TEST_CASE(ucie_training, training_with_random_configuration_of_phy_control_register);
}

TEST_GROUP_RUNNER(ucie_training_only_for_mock)
{
	RUN_TEST_CASE(ucie_training, training_fail_when_trainig_already_ongoing);
	RUN_TEST_CASE(ucie_training,
				  training_fail_due_to_keeping_training_status_after_ending_training);
	RUN_TEST_CASE(ucie_training, training_fail_due_to_keeping_link_down_after_ending_training);
}
