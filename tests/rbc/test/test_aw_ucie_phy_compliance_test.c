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

static struct aw_ucie *mmio_ptr;
static struct aw_ucie *wr_buf_ptr;
static const int32_t ucie_ss_id = UCIE_SS_H00_ID;
static int32_t (*link_training_bk)(void);
static int32_t (*link_retraining_bk)(void);

static void _enable_phy_compliance_mode(uint32_t module_sel);
static void _disable_phy_compliance_mode(uint32_t module_sel);

TEST_GROUP(ucie_phy_compliance_test);

TEST_SETUP(ucie_phy_compliance_test)
{
	CLEAR_SNAPSHOT_ARR(reg[ucie_ss_id]);
	CLEAR_SNAPSHOT_ARR(target_ss);

	link_training_bk = aw_ucie_link_training;
	link_retraining_bk = aw_ucie_link_retraining;
#ifdef USE_DILIGENT_PTR
	aw_ucie_link_training = dummy_aw_ucie_link_training;
	aw_ucie_link_retraining = dummy_aw_ucie_link_retraining;
#endif /* USE_DILIGENT_PTR */
	init_mmio_map(ucie_ss_id);

	mmio_ptr = get_aw_ucie_mmio_var();
	wr_buf_ptr = get_aw_ucie_mmio_write_buf();
	real_map = get_aw_ucie_real_map();

	PAUSE(target_ss);
	aw_ucie_init(ucie_ss_id, real_map);
	aw_ucie_set_target_ss(ucie_ss_id);
	aw_ucie_link_training();
	RESUME(target_ss);

	_enable_phy_compliance_mode(0);
	_enable_phy_compliance_mode(1);
}

TEST_TEAR_DOWN(ucie_phy_compliance_test)
{
	_disable_phy_compliance_mode(0);
	_disable_phy_compliance_mode(1);

	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);

	aw_ucie_link_training = link_training_bk;
	aw_ucie_link_retraining = link_retraining_bk;
}

static void _enable_phy_compliance_mode(uint32_t module_sel)
{
	*wr_buf_ptr = *mmio_ptr;

	if (!module_sel)
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_compl_en = ENABLE;
	else
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_compl_en = ENABLE;

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_phy_compliance_enable(module_sel, ENABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());

	if (!module_sel)
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1.m0_mode = ENABLE;
	else
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1.m1_mode = ENABLE;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	uint32_t mode = DISABLE;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_compliance_mode(module_sel, &mode));
	TEST_ASSERT_EQUAL(ENABLE, mode);
}

static void _disable_phy_compliance_mode(uint32_t module_sel)
{
	*wr_buf_ptr = *mmio_ptr;

	if (!module_sel)
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_compl_en = DISABLE;
	else
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_compl_en = DISABLE;

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_phy_compliance_enable(module_sel, DISABLE));

	if (!module_sel)
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1.m0_mode = DISABLE;
	else
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1.m1_mode = DISABLE;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	uint32_t mode = ENABLE;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_compliance_mode(module_sel, &mode));
	TEST_ASSERT_EQUAL(DISABLE, mode);
}

static void _set_scrambling_disable(uint32_t module_sel)
{
	*wr_buf_ptr = *mmio_ptr;

	if (!module_sel)
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_scram_disabled = ENABLE;
	else
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_scram_disabled = ENABLE;

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_scrambling_disable(module_sel, ENABLE));

	if (!module_sel)
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_scram_disabled = ENABLE;
	else
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_scram_disabled = ENABLE;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	uint32_t scram_disabled = DISABLE;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_scrambling_disable(module_sel, &scram_disabled));
	TEST_ASSERT_EQUAL(ENABLE, scram_disabled);
}

static void _do_phy_compliance_operation(uint32_t module_sel, uint32_t operation_type)
{
	union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1 *wr_compl_ctrl1_1 = 0;

	if (!module_sel)
		wr_compl_ctrl1_1 = &wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1;
	else
		wr_compl_ctrl1_1 = (union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1 *)
						   &wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1;

	*wr_buf_ptr = *mmio_ptr;
	wr_compl_ctrl1_1->m0_operation_type = operation_type;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	wr_compl_ctrl1_1->m0_operation_trigger = ENABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_do_phy_compliance_operation(module_sel, ENABLE, operation_type));

	union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1 *mmio_compl_status = 0;

	if (!module_sel)
		mmio_compl_status = &mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1;
	else
		mmio_compl_status =
		(union aw_ucie_phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1 *)
															&mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1;

	mmio_compl_status->m0_operation_status = 1;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	uint32_t operation_status_for_comp = 0;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_compliance_operation_status(module_sel, &operation_status_for_comp));
	TEST_ASSERT_EQUAL(1, operation_status_for_comp);
}

static void _set_trainig_setup1_by_phy_compliance_test(uint32_t module_sel, uint32_t data_pattern,
													   uint32_t valid_pattern, uint32_t clk_phase_cntrl,
													   uint32_t train_mode, uint32_t burst_cnt)
{
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup1 *wr_train_setup1 = 0;

	if (!module_sel)
		wr_train_setup1 = &wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup1;
	else
		wr_train_setup1 =
		(union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup1 *)&wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_m1_train_setup1;

	*wr_buf_ptr = *mmio_ptr;
	wr_train_setup1->m0_data_pattern = data_pattern;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	wr_train_setup1->m0_valid_pattern = valid_pattern;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	wr_train_setup1->m0_clk_phase_cntrl = clk_phase_cntrl;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	wr_train_setup1->m0_train_mode = train_mode;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	wr_train_setup1->m0_burst_cnt = burst_cnt;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_data_pattern_of_train_setup1(module_sel, data_pattern));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_valid_pattern_of_train_setup1(module_sel, valid_pattern));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_clk_phase_cntrl_of_train_setup1(module_sel, clk_phase_cntrl));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_train_mode_of_train_setup1(module_sel, train_mode));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_burst_cnt_of_train_setup1(module_sel, burst_cnt));

	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup1 *mmio_train_setup1 = 0;

	if (!module_sel)
		mmio_train_setup1 = &mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup1;
	else
		mmio_train_setup1 =
		(union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup1 *)&mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_train_setup1;

	mmio_train_setup1->m0_data_pattern = data_pattern;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_train_setup1->m0_valid_pattern = valid_pattern;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_train_setup1->m0_clk_phase_cntrl = clk_phase_cntrl;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_train_setup1->m0_train_mode = train_mode;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_train_setup1->m0_burst_cnt = burst_cnt;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	uint32_t data_pattern_for_comp = 0xFF;
	uint32_t valid_pattern_for_comp = 0xFF;
	uint32_t clk_phase_cntrl_for_comp = 0xFF;
	uint32_t train_mode_for_comp = 0xFF;
	uint32_t burst_cnt_for_comp = 0xFF;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_data_pattern_of_train_setup1(module_sel, &data_pattern_for_comp));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_valid_pattern_of_train_setup1(module_sel, &valid_pattern_for_comp));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_clk_phase_cntrl_of_train_setup1(module_sel, &clk_phase_cntrl_for_comp));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_train_mode_of_train_setup1(module_sel, &train_mode_for_comp));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_burst_cnt_of_train_setup1(module_sel, &burst_cnt_for_comp));

	TEST_ASSERT_EQUAL(data_pattern, data_pattern_for_comp);
	TEST_ASSERT_EQUAL(valid_pattern, valid_pattern_for_comp);
	TEST_ASSERT_EQUAL(clk_phase_cntrl, clk_phase_cntrl_for_comp);
	TEST_ASSERT_EQUAL(train_mode, train_mode_for_comp);
	TEST_ASSERT_EQUAL(burst_cnt, burst_cnt_for_comp);

	_do_phy_compliance_operation(module_sel, PHY_COMP_OP_TYPE_TX_D2C_POINT);
}

static void _set_trainig_setup2_by_phy_compliance_test(uint32_t module_sel, uint32_t idle_cnt, uint32_t iterations)
{
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup2 *wr_train_setup2 = 0;

	if (!module_sel)
		wr_train_setup2 = &wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup2;
	else
		wr_train_setup2 =
		(union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup2 *)&wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_m1_train_setup2;

	*wr_buf_ptr = *mmio_ptr;
	wr_train_setup2->m0_idle_cnt = idle_cnt;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	wr_train_setup2->m0_iterations = iterations;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_idle_cnt_of_train_setup2(module_sel, idle_cnt));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_iterations_of_train_setup2(module_sel, iterations));

	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup2 *mmio_train_setup2 = 0;

	if (!module_sel)
		mmio_train_setup2 = &mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup2;
	else
		mmio_train_setup2 =
		(union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup2 *)&mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_train_setup2;

	mmio_train_setup2->m0_idle_cnt = idle_cnt;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_train_setup2->m0_iterations = iterations;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	uint32_t m0_idle_cnt_for_comp = 0xFF;
	uint32_t m0_iterations_for_comp = 0xFF;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_idle_cnt_of_train_setup2(module_sel, &m0_idle_cnt_for_comp));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_iterations_of_train_setup2(module_sel, &m0_iterations_for_comp));

	TEST_ASSERT_EQUAL(idle_cnt, m0_idle_cnt_for_comp);
	TEST_ASSERT_EQUAL(iterations, m0_iterations_for_comp);

	_do_phy_compliance_operation(module_sel, PHY_COMP_OP_TYPE_TX_D2C_POINT);
}

static void _set_trainig_setup3_by_phy_compliance_test(uint32_t module_sel, uint64_t reg_lane_mask)
{
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1 *wr_train_setup3_1 = 0;
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2 *wr_train_setup3_2 = 0;

	if (!module_sel) {
		wr_train_setup3_1 = &wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1;
		wr_train_setup3_2 = &wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2;
	} else {
		wr_train_setup3_1 = (union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1 *)
							 &wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_m1_train_setup3_1;
		wr_train_setup3_2 =	(union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2 *)
							 &wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_m1_train_setup3_2;
	}

	*wr_buf_ptr = *mmio_ptr;
	wr_train_setup3_1->m0_reg1_lane_mask = reg_lane_mask & (0xFFFFFFFF);
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	wr_train_setup3_2->m0_reg2_lane_mask = (reg_lane_mask >> 32) & (0xFFFFFFFF);
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_lane_mask_of_train_setup3(module_sel, reg_lane_mask));

	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1 *mmio_train_setup3_1 = 0;
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2 *mmio_train_setup3_2 = 0;

	if (!module_sel) {
		mmio_train_setup3_1 = &mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1;
		mmio_train_setup3_2 = &mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2;
	} else {
		mmio_train_setup3_1 =
			(union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1 *)
																&mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_train_setup3_1;
		mmio_train_setup3_2 =
			(union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2 *)
																&mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_train_setup3_2;
	}
	mmio_train_setup3_1->m0_reg1_lane_mask = reg_lane_mask & (0xFFFFFFFF);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_train_setup3_2->m0_reg2_lane_mask = (reg_lane_mask >> 32) & (0xFFFFFFFF);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	uint64_t reg_lane_mask_comp = 0xFFFFFFFF;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_lane_mask_of_train_setup3(module_sel, &reg_lane_mask_comp));
	TEST_ASSERT_EQUAL(reg_lane_mask, reg_lane_mask_comp);

	_do_phy_compliance_operation(module_sel, PHY_COMP_OP_TYPE_TX_D2C_POINT);
}

static void _set_trainig_setup4_by_phy_compliance_test(uint32_t module_sel, uint32_t repair_lane_mask,
													   uint32_t max_err_th_per_lane, uint32_t max_err_th_aggregate)
{
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup4 *wr_train_setup4 = 0;

	if (!module_sel)
		wr_train_setup4 = &wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup4;
	else
		wr_train_setup4 =
		(union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup4 *)&wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_m1_train_setup4;

	*wr_buf_ptr = *mmio_ptr;
	wr_train_setup4->m0_repair_lane_mask = repair_lane_mask;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	wr_train_setup4->m0_max_err_th_per_lane = max_err_th_per_lane;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	wr_train_setup4->m0_max_err_th_aggregate = max_err_th_aggregate;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_repair_lane_mask_of_train_setup4(module_sel, repair_lane_mask));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_max_err_th_per_lane_of_train_setup4(module_sel, max_err_th_per_lane));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_max_err_th_aggregate_of_train_setup4(module_sel, max_err_th_aggregate));

	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup4 *mmio_train_setup4 = 0;

	if (!module_sel)
		mmio_train_setup4 = &mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup4;
	else
		mmio_train_setup4 =
		(union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_train_setup4 *)&mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_train_setup4;

	mmio_train_setup4->m0_repair_lane_mask = repair_lane_mask;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_train_setup4->m0_max_err_th_per_lane = max_err_th_per_lane;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_train_setup4->m0_max_err_th_aggregate = max_err_th_aggregate;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	uint32_t repair_lane_mask_for_comp = 0;
	uint32_t max_err_th_per_lane_for_comp = 0;
	uint32_t max_err_th_aggregate_for_comp = 0;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_repair_lane_mask_of_train_setup4(module_sel, &repair_lane_mask_for_comp));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_max_err_th_per_lane_of_train_setup4(module_sel,
																			 &max_err_th_per_lane_for_comp));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_max_err_th_aggregate_of_train_setup4(module_sel,
																			  &max_err_th_aggregate_for_comp));
	TEST_ASSERT_EQUAL(repair_lane_mask, repair_lane_mask_for_comp);
	TEST_ASSERT_EQUAL(max_err_th_per_lane, max_err_th_per_lane_for_comp);
	TEST_ASSERT_EQUAL(max_err_th_aggregate, max_err_th_aggregate_for_comp);

	_do_phy_compliance_operation(module_sel, PHY_COMP_OP_TYPE_TX_D2C_POINT);

	/*
	 * TODO
	 * it is necessary to consider how long the data transaction will last.
	 */
}

static void _set_rx_vref_offset_by_phy_compliance_test(uint32_t module_sel, uint32_t rx_vref_offset_enable,
													   uint32_t rx_vref_offset)
{
	*wr_buf_ptr = *mmio_ptr;

	if (!module_sel)
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_rx_vref_offset = rx_vref_offset;
	else
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_rx_vref_offset = rx_vref_offset;

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_rx_vref_offset(module_sel, rx_vref_offset));

	*wr_buf_ptr = *mmio_ptr;

	if (!module_sel)
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_rx_vref_offset_enable = rx_vref_offset_enable;
	else
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_rx_vref_offset_enable = rx_vref_offset_enable;

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_rx_vref_offset_enable(module_sel, rx_vref_offset_enable));
}

static void _set_compare_setup_by_phy_compliance_test(uint32_t module_sel, uint32_t compare_setup)
{
	*wr_buf_ptr = *mmio_ptr;

	if (!module_sel)
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_compare_setup = compare_setup;
	else
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_compare_setup = compare_setup;

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_compare_setup(module_sel, compare_setup));

	if (!module_sel)
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_compare_setup = compare_setup;
	else
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_compare_setup = compare_setup;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	uint32_t compare_setup_for_comp = 0;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_compare_setup(module_sel, &compare_setup_for_comp));
	TEST_ASSERT_EQUAL(compare_setup, compare_setup_for_comp);
}

static void _set_even_ui_compare_mask(uint32_t module_sel)
{
	*wr_buf_ptr = *mmio_ptr;

	if (!module_sel)
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_even_ui_compare_mask = ENABLE;
	else
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_even_ui_compare_mask = ENABLE;

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_even_ui_compare_mask(module_sel, ENABLE));

	if (!module_sel)
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_even_ui_compare_mask = ENABLE;
	else
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_even_ui_compare_mask = ENABLE;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	uint32_t even_ui_compare_mask = DISABLE;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_even_ui_compare_mask(module_sel, &even_ui_compare_mask));
	TEST_ASSERT_EQUAL(ENABLE, even_ui_compare_mask);
}

static void _set_odd_ui_compare_mask(uint32_t module_sel)
{
	*wr_buf_ptr = *mmio_ptr;

	if (!module_sel)
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_odd_ui_compare_mask = ENABLE;
	else
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_odd_ui_compare_mask = ENABLE;

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_odd_ui_compare_mask(module_sel, ENABLE));

	if (!module_sel)
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_odd_ui_compare_mask = ENABLE;
	else
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_odd_ui_compare_mask = ENABLE;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	uint32_t odd_ui_compare_mask = DISABLE;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_odd_ui_compare_mask(module_sel, &odd_ui_compare_mask));
	TEST_ASSERT_EQUAL(ENABLE, odd_ui_compare_mask);
}

static void _set_track_enable(uint32_t module_sel)
{
	*wr_buf_ptr = *mmio_ptr;

	if (!module_sel)
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_track_enable = ENABLE;
	else
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_track_enable = ENABLE;

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_track_enable(module_sel, ENABLE));

	if (!module_sel)
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_track_enable = ENABLE;
	else
		mmio_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_track_enable = ENABLE;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	uint32_t track_enable = DISABLE;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_track_enable(module_sel, &track_enable));
	TEST_ASSERT_EQUAL(ENABLE, track_enable);
}

TEST(ucie_phy_compliance_test, check_m0_phy_compliance_mode)
{
	_enable_phy_compliance_mode(0);
	_disable_phy_compliance_mode(0);
}

TEST(ucie_phy_compliance_test, m0_scrambling_disable_by_phy_compliance_test)
{
	_set_scrambling_disable(0);
}

TEST(ucie_phy_compliance_test, check_m0_phy_compliance_no_operation)
{
	_do_phy_compliance_operation(0, PHY_COMP_OP_TYPE_NO_OP);
}

TEST(ucie_phy_compliance_test, check_m0_phy_compliance_tx_point_operation)
{
	_do_phy_compliance_operation(0, PHY_COMP_OP_TYPE_TX_D2C_POINT);
}

TEST(ucie_phy_compliance_test, check_m0_phy_compliance_tx_sweep_operation)
{
	_do_phy_compliance_operation(0, PHY_COMP_OP_TYPE_TX_D2C_SWEEP);
}

TEST(ucie_phy_compliance_test, check_m0_phy_compliance_rx_point_operation)
{
	_do_phy_compliance_operation(0, PHY_COMP_OP_TYPE_RX_D2C_POINT);
}

TEST(ucie_phy_compliance_test, check_m0_phy_compliance_rx_sweep_operation)
{
	_do_phy_compliance_operation(0, PHY_COMP_OP_TYPE_RX_D2C_SWEEP);
}

TEST(ucie_phy_compliance_test, check_m0_data_pattern000_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, DATA_PAT_PER_LANE_LFSR, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_data_pattern001_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, DATA_PAT_PER_LANE_ID, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_data_pattern010_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, DATA_PAT_PER_LANE_AA, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_data_pattern011_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, DATA_PAT_PER_LANE_ALL_0, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_data_pattern100_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, DATA_PAT_PER_LANE_ALL_1, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_data_pattern101_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, DATA_PAT_PER_LANE_IVT_CLK, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_valid_pattern_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, 0, VAL_PAT_FUNC_VALID, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_clk_phase_cntrl_center_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, 0, 0, CLK_PHASE_CON_CENTER, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_clk_phase_cntrl_left_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, 0, 0, CLK_PHASE_CON_LEFT, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_clk_phase_cntrl_right_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, 0, 0, CLK_PHASE_CON_RIGHT, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_training_mode_conti_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, 0, 0, 0, TRAIN_MODE_CONT, 0);
}

TEST(ucie_phy_compliance_test, check_m0_training_mode_burst_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, 0, 0, 0, TRAIN_MODE_BURST, 0);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_burst_cnt0_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, 0, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_burst_cnt1_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, 0, 0, 0, 0, 1);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_burst_cnt4_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, 0, 0, 0, 0, 4);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_burst_cntFFFF_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(0, 0, 0, 0, 0, 0xFFFF);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_idle_cnt0_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_idle_cnt1_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(0, 1, 0);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_idle_cnt4_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(0, 4, 0);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_idle_cntFFFF_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(0, 0xFFFF, 0);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_iterations0_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_iterations1_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(0, 0, 1);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_iterations4_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(0, 0, 4);
}

TEST(ucie_phy_compliance_test, check_m0_16bit_iterationsFFFF_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(0, 0, 0xFFFF);
}

TEST(ucie_phy_compliance_test, check_m0_lane_mask_all_0_of_train_setup3)
{
	_set_trainig_setup3_by_phy_compliance_test(0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_lane_mask_all_1_of_train_setup3)
{
	_set_trainig_setup3_by_phy_compliance_test(0, 0xFFFFFFFFFFFFFFFF);
}

TEST(ucie_phy_compliance_test, check_m0_repair_lane_no_mask_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_repair_lane_rd1_mask_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(0, 1, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_repair_lane_rd2_mask_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(0, 2, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_max_err_th_per_lane0_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_max_err_th_per_lane1_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(0, 0, 1, 0);
}

TEST(ucie_phy_compliance_test, check_m0_max_err_th_per_laneFFF_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(0, 0, 0xFFF, 0);
}

TEST(ucie_phy_compliance_test, check_m0_max_err_th_aggregate0_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m0_max_err_th_aggregate1_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(0, 0, 0, 1);
}

TEST(ucie_phy_compliance_test, check_m0_max_err_th_aggregateFFF_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(0, 0, 0, 0xFFF);
}

TEST(ucie_phy_compliance_test, no_change_m0_rx_vref_offset_by_phy_compliance_test)
{
	_set_rx_vref_offset_by_phy_compliance_test(0, RX_VREF_OFFSET_EN_NONE, 0);
}

TEST(ucie_phy_compliance_test, add_m0_rx_vref_offset_in_per_lane_comp_by_phy_compliance_test)
{
	_set_rx_vref_offset_by_phy_compliance_test(0, RX_VREF_OFFSET_EN_ADD, 0XFF);
	_set_compare_setup_by_phy_compliance_test(0, 0);
	_set_trainig_setup4_by_phy_compliance_test(0, 0, 0xFFF, 0);
}

TEST(ucie_phy_compliance_test, sub_m0_rx_vref_offset_in_aggregate_comp_by_phy_compliance_test)
{
	_set_rx_vref_offset_by_phy_compliance_test(0, RX_VREF_OFFSET_EN_SUB, 0XFF);
	_set_compare_setup_by_phy_compliance_test(0, 1);
	_set_trainig_setup4_by_phy_compliance_test(0, 0, 0, 0xFFF);
}

TEST(ucie_phy_compliance_test, check_m0_even_ui_compare_mask)
{
	_set_even_ui_compare_mask(0);
}

TEST(ucie_phy_compliance_test, check_m0_odd_ui_compare_mask)
{
	_set_odd_ui_compare_mask(0);
}

TEST(ucie_phy_compliance_test, check_m0_track_enable_by_phy_compliance_test)
{
	_set_track_enable(0);
}

TEST(ucie_phy_compliance_test, check_m0_compare_setup_by_phy_compliance_test)
{
	_set_compare_setup_by_phy_compliance_test(0, 1);
}

/* test module 1*/
TEST(ucie_phy_compliance_test, check_m1_phy_compliance_mode)
{
	_enable_phy_compliance_mode(1);
	_disable_phy_compliance_mode(1);

}

TEST(ucie_phy_compliance_test, m1_scrambling_disable_by_phy_compliance_test)
{
	_set_scrambling_disable(1);
}

TEST(ucie_phy_compliance_test, check_m1_phy_compliance_no_operation)
{
	_do_phy_compliance_operation(1, PHY_COMP_OP_TYPE_NO_OP);
}

TEST(ucie_phy_compliance_test, check_m1_phy_compliance_tx_point_operation)
{
	_do_phy_compliance_operation(1, PHY_COMP_OP_TYPE_TX_D2C_POINT);
}

TEST(ucie_phy_compliance_test, check_m1_phy_compliance_tx_sweep_operation)
{
	_do_phy_compliance_operation(1, PHY_COMP_OP_TYPE_TX_D2C_SWEEP);
}

TEST(ucie_phy_compliance_test, check_m1_phy_compliance_rx_point_operation)
{
	_do_phy_compliance_operation(1, PHY_COMP_OP_TYPE_RX_D2C_POINT);
}

TEST(ucie_phy_compliance_test, check_m1_phy_compliance_rx_sweep_operation)
{
	_do_phy_compliance_operation(1, PHY_COMP_OP_TYPE_RX_D2C_SWEEP);
}

TEST(ucie_phy_compliance_test, check_m1_data_pattern000_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, DATA_PAT_PER_LANE_LFSR, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_data_pattern001_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, DATA_PAT_PER_LANE_ID, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_data_pattern010_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, DATA_PAT_PER_LANE_AA, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_data_pattern011_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, DATA_PAT_PER_LANE_ALL_0, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_data_pattern100_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, DATA_PAT_PER_LANE_ALL_1, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_data_pattern101_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, DATA_PAT_PER_LANE_IVT_CLK, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_valid_pattern_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, 0, VAL_PAT_FUNC_VALID, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_clk_phase_cntrl_center_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, 0, 0, CLK_PHASE_CON_CENTER, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_clk_phase_cntrl_left_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, 0, 0, CLK_PHASE_CON_LEFT, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_clk_phase_cntrl_right_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, 0, 0, CLK_PHASE_CON_RIGHT, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_training_mode_conti_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, 0, 0, 0, TRAIN_MODE_CONT, 0);
}

TEST(ucie_phy_compliance_test, check_m1_training_mode_burst_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, 0, 0, 0, TRAIN_MODE_BURST, 0);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_burst_cnt0_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, 0, 0, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_burst_cnt1_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, 0, 0, 0, 0, 1);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_burst_cnt4_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, 0, 0, 0, 0, 4);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_burst_cntFFFF_of_train_setup1)
{
	_set_trainig_setup1_by_phy_compliance_test(1, 0, 0, 0, 0, 0xFFFF);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_idle_cnt0_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(1, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_idle_cnt1_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(1, 1, 0);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_idle_cnt4_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(1, 4, 0);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_idle_cntFFFF_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(1, 0xFFFF, 0);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_iterations0_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(1, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_iterations1_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(1, 0, 1);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_iterations4_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(1, 0, 4);
}

TEST(ucie_phy_compliance_test, check_m1_16bit_iterationsFFFF_of_train_setup2)
{
	_set_trainig_setup2_by_phy_compliance_test(1, 0, 0xFFFF);
}

TEST(ucie_phy_compliance_test, check_m1_lane_mask_all_0_of_train_setup3)
{
	_set_trainig_setup3_by_phy_compliance_test(1, 0);
}

TEST(ucie_phy_compliance_test, check_m1_lane_mask_all_1_of_train_setup3)
{
	_set_trainig_setup3_by_phy_compliance_test(1, 0xFFFFFFFFFFFFFFFF);
}

TEST(ucie_phy_compliance_test, check_m1_repair_lane_no_mask_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(1, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_repair_lane_rd1_mask_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(1, 1, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_repair_lane_rd2_mask_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(1, 2, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_max_err_th_per_lane0_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(1, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_max_err_th_per_lane1_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(1, 0, 1, 0);
}

TEST(ucie_phy_compliance_test, check_m1_max_err_th_per_laneFFF_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(1, 0, 0xFFF, 0);
}

TEST(ucie_phy_compliance_test, check_m1_max_err_th_aggregate0_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(1, 0, 0, 0);
}

TEST(ucie_phy_compliance_test, check_m1_max_err_th_aggregate1_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(1, 0, 0, 1);
}

TEST(ucie_phy_compliance_test, check_m1_max_err_th_aggregateFFF_of_train_setup4)
{
	_set_trainig_setup4_by_phy_compliance_test(1, 0, 0, 0xFFF);
}

TEST(ucie_phy_compliance_test, no_change_m1_rx_vref_offset_by_phy_compliance_test)
{
	_set_rx_vref_offset_by_phy_compliance_test(1, RX_VREF_OFFSET_EN_NONE, 0);
}

TEST(ucie_phy_compliance_test, add_m1_rx_vref_offset_in_per_lane_comp_by_phy_compliance_test)
{
	_set_rx_vref_offset_by_phy_compliance_test(1, RX_VREF_OFFSET_EN_ADD, 0XFF);
	_set_compare_setup_by_phy_compliance_test(1, 0);
	_set_trainig_setup4_by_phy_compliance_test(1, 0, 0xFFF, 0);
}

TEST(ucie_phy_compliance_test, sub_m1_rx_vref_offset_in_aggregate_comp_by_phy_compliance_test)
{
	_set_rx_vref_offset_by_phy_compliance_test(1, RX_VREF_OFFSET_EN_SUB, 0XFF);
	_set_compare_setup_by_phy_compliance_test(1, 1);
	_set_trainig_setup4_by_phy_compliance_test(1, 0, 0, 0xFFF);
}

TEST(ucie_phy_compliance_test, check_m1_even_ui_compare_mask)
{
	_set_even_ui_compare_mask(1);
}

TEST(ucie_phy_compliance_test, check_m1_odd_ui_compare_mask)
{
	_set_odd_ui_compare_mask(1);
}

TEST(ucie_phy_compliance_test, check_m1_track_enable_by_phy_compliance_test)
{
	_set_track_enable(1);
}

TEST(ucie_phy_compliance_test, check_m1_compare_setup_by_phy_compliance_test)
{
	_set_compare_setup_by_phy_compliance_test(1, 1);
}

TEST_GROUP_RUNNER(ucie_phy_compliance_test_except_only_for_mock)
{
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_phy_compliance_mode);
	RUN_TEST_CASE(ucie_phy_compliance_test, m0_scrambling_disable_by_phy_compliance_test);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_phy_compliance_no_operation);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_phy_compliance_tx_point_operation);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_phy_compliance_tx_sweep_operation);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_phy_compliance_rx_point_operation);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_phy_compliance_rx_sweep_operation);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_data_pattern000_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_data_pattern001_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_data_pattern010_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_data_pattern011_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_data_pattern100_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_data_pattern101_of_train_setup1);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_valid_pattern_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_clk_phase_cntrl_center_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_clk_phase_cntrl_left_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_clk_phase_cntrl_right_of_train_setup1);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_training_mode_conti_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_training_mode_burst_of_train_setup1);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_burst_cnt0_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_burst_cnt1_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_burst_cnt4_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_burst_cntFFFF_of_train_setup1);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_idle_cnt0_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_idle_cnt1_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_idle_cnt4_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_idle_cntFFFF_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_iterations0_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_iterations1_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_iterations4_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_16bit_iterationsFFFF_of_train_setup2);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_lane_mask_all_0_of_train_setup3);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_lane_mask_all_1_of_train_setup3);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_repair_lane_no_mask_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_repair_lane_rd1_mask_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_repair_lane_rd2_mask_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_max_err_th_per_lane0_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_max_err_th_per_lane1_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_max_err_th_per_laneFFF_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_max_err_th_aggregate0_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_max_err_th_aggregate1_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_max_err_th_aggregateFFF_of_train_setup4);

	RUN_TEST_CASE(ucie_phy_compliance_test, no_change_m0_rx_vref_offset_by_phy_compliance_test);
	RUN_TEST_CASE(ucie_phy_compliance_test, add_m0_rx_vref_offset_in_per_lane_comp_by_phy_compliance_test);
	RUN_TEST_CASE(ucie_phy_compliance_test, sub_m0_rx_vref_offset_in_aggregate_comp_by_phy_compliance_test);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_even_ui_compare_mask);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_odd_ui_compare_mask);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_track_enable_by_phy_compliance_test);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m0_compare_setup_by_phy_compliance_test);

	/* test module 1*/
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_phy_compliance_mode);
	RUN_TEST_CASE(ucie_phy_compliance_test, m1_scrambling_disable_by_phy_compliance_test);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_phy_compliance_no_operation);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_phy_compliance_tx_point_operation);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_phy_compliance_tx_sweep_operation);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_phy_compliance_rx_point_operation);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_phy_compliance_rx_sweep_operation);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_data_pattern000_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_data_pattern001_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_data_pattern010_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_data_pattern011_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_data_pattern100_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_data_pattern101_of_train_setup1);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_valid_pattern_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_clk_phase_cntrl_center_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_clk_phase_cntrl_left_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_clk_phase_cntrl_right_of_train_setup1);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_training_mode_conti_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_training_mode_burst_of_train_setup1);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_burst_cnt0_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_burst_cnt1_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_burst_cnt4_of_train_setup1);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_burst_cntFFFF_of_train_setup1);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_idle_cnt0_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_idle_cnt1_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_idle_cnt4_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_idle_cntFFFF_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_iterations0_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_iterations1_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_iterations4_of_train_setup2);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_16bit_iterationsFFFF_of_train_setup2);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_lane_mask_all_0_of_train_setup3);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_lane_mask_all_1_of_train_setup3);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_repair_lane_no_mask_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_repair_lane_rd1_mask_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_repair_lane_rd2_mask_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_max_err_th_per_lane0_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_max_err_th_per_lane1_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_max_err_th_per_laneFFF_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_max_err_th_aggregate0_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_max_err_th_aggregate1_of_train_setup4);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_max_err_th_aggregateFFF_of_train_setup4);

	RUN_TEST_CASE(ucie_phy_compliance_test, no_change_m1_rx_vref_offset_by_phy_compliance_test);
	RUN_TEST_CASE(ucie_phy_compliance_test, add_m1_rx_vref_offset_in_per_lane_comp_by_phy_compliance_test);
	RUN_TEST_CASE(ucie_phy_compliance_test, sub_m1_rx_vref_offset_in_aggregate_comp_by_phy_compliance_test);

	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_even_ui_compare_mask);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_odd_ui_compare_mask);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_track_enable_by_phy_compliance_test);
	RUN_TEST_CASE(ucie_phy_compliance_test, check_m1_compare_setup_by_phy_compliance_test);

}

TEST_GROUP_RUNNER(ucie_phy_compliance_test_only_for_mock)
{
}
