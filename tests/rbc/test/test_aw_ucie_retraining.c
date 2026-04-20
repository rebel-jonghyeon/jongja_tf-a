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

static int32_t _retraining_with_specific_done_link_stat(uint32_t specific_done_link_stat)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_default_link_stat()
	};

	link_stat.lstatus_link_status = ENABLE;

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status = link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, mmio_ptr);

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.val = get_default_link_ctrl();
	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.lcntrl_retrain_ucie_link = ENABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.lcntrl_retrain_ucie_link = DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val = specific_done_link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	return aw_ucie_link_retraining();
}

TEST_GROUP(ucie_retraining);

TEST_SETUP(ucie_retraining)
{
	CLEAR_SNAPSHOT_ARR(reg[ucie_ss_id]);
	CLEAR_SNAPSHOT_ARR(target_ss);

	link_training_bk = aw_ucie_link_training;
#ifdef USE_DILIGENT_PTR
	aw_ucie_link_training = dummy_aw_ucie_link_training;
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
}

TEST_TEAR_DOWN(ucie_retraining)
{
	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);

	aw_ucie_link_training = link_training_bk;
}

TEST(ucie_retraining, retraining_success_w_default_config)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_default_link_stat()};

	link_stat.lstatus_link_status = ENABLE;

	TEST_ASSERT_EQUAL(RL_OK, _retraining_with_specific_done_link_stat(link_stat.val));

	link_stat.lstatus_link_status_change = DISABLE;
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status = link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_status(&link_stat.val));
	TEST_ASSERT_EQUAL(DISABLE, link_stat.lstatus_link_status_change);
}

/* Only for Mock */
TEST(ucie_retraining, retraining_fail_due_to_keeping_link_down_after_ending_training)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_default_link_stat() };

	link_stat.lstatus_link_status = DISABLE;

	TEST_ASSERT_EQUAL(RL_ERROR, _retraining_with_specific_done_link_stat(link_stat.val));
}

/* Only for Mock */
TEST(ucie_retraining, retraining_fail_due_to_keeping_training_status_after_ending_training)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_default_link_stat()};

	link_stat.lstatus_link_status = ENABLE;
	link_stat.lstatus_link_train_or_retrain = ENABLE;

	TEST_ASSERT_EQUAL(RL_ERROR, _retraining_with_specific_done_link_stat(link_stat.val));
}

/* Only for Mock */
TEST(ucie_retraining, retraining_fail_in_link_down)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_default_link_stat()};

	link_stat.lstatus_link_status = DISABLE;

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status = link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	TEST_ASSERT_EQUAL(RL_NOTREADY, aw_ucie_link_retraining());
}

/* Only for Mock */
TEST(ucie_retraining, retraining_fail_when_trainig_already_ongoing)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {
		.val = get_default_link_stat() };

	link_stat.lstatus_link_status = ENABLE;
	link_stat.lstatus_link_train_or_retrain = ENABLE;

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status = link_stat;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	TEST_ASSERT_EQUAL(RL_BUSY, aw_ucie_link_retraining());
}

TEST_GROUP_RUNNER(ucie_retraining_except_only_for_mock)
{
	RUN_TEST_CASE(ucie_retraining, retraining_success_w_default_config);
}

TEST_GROUP_RUNNER(ucie_retraining_only_for_mock)
{
	RUN_TEST_CASE(ucie_retraining,
				  retraining_fail_due_to_keeping_link_down_after_ending_training);
	RUN_TEST_CASE(ucie_retraining,
				  retraining_fail_due_to_keeping_training_status_after_ending_training);
	RUN_TEST_CASE(ucie_retraining, retraining_fail_in_link_down);
	RUN_TEST_CASE(ucie_retraining, retraining_fail_when_trainig_already_ongoing);
}
