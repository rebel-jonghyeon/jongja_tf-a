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
#include "rl_errors.h"
#include "unity_fixture.h"

static struct aw_ucie *mmio_ptr;
static struct aw_ucie *wr_buf_ptr;
static const int32_t ucie_ss_id = UCIE_SS_V10_ID;
static int32_t (*link_training_bk)(void);
static int32_t (*link_retraining_bk)(void);

TEST_GROUP(ucie_eye_of_margin);

TEST_SETUP(ucie_eye_of_margin)
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
}

TEST_TEAR_DOWN(ucie_eye_of_margin)
{
	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);
	aw_ucie_link_retraining = link_retraining_bk;
	aw_ucie_link_training = link_training_bk;
}

static void _set_mock_status_for_eom(uint32_t status)
{
	mmio_ptr->phy_d2d_reg_reg_phy_d2d_uhm_status.val = 0;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, mmio_ptr);

	mmio_ptr->phy_d2d_reg_reg_phy_d2d_uhm_status.status_emv = status;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
}

static void _set_mock_eml_emr_for_eom(uint32_t module_sel, uint32_t exp_eml, uint32_t exp_emr, uint32_t lane_id)
{
	uint32_t offset = lane_id / 2;
	uint32_t parity = lane_id % 2;

	if (module_sel == 0) {
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0 *eml_emr_m0 =
			(union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0 *)
			(&mmio_ptr->phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0 + offset);

		eml_emr_m0->val = (((parity == 0) ? exp_eml & 0xFF : 0) << 0)  |
						  (((parity == 0) ? exp_emr & 0xFF : 0) << 8)  |
						  (((parity == 1) ? exp_eml & 0xFF : 0) << 16) |
						  (((parity == 1) ? exp_emr & 0xFF : 0) << 24);
	} else if (module_sel == 1) {
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1 *eml_emr_m1 =
			(union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1 *)
			(&mmio_ptr->phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1 + offset);

		eml_emr_m1->val = (((parity == 0) ? exp_eml & 0xFF : 0) << 0)  |
						  (((parity == 0) ? exp_emr & 0xFF : 0) << 8)  |
						  (((parity == 1) ? exp_eml & 0xFF : 0) << 16) |
						  (((parity == 1) ? exp_emr & 0xFF : 0) << 24);
	}

	_set_mock_status_for_eom(1);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
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
	aw_ucie_set_rx_vref_offset(module_sel, rx_vref_offset);

	*wr_buf_ptr = *mmio_ptr;

	if (!module_sel)
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_rx_vref_offset_enable = rx_vref_offset_enable;
	else
		wr_buf_ptr->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_rx_vref_offset_enable = rx_vref_offset_enable;

	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	aw_ucie_set_rx_vref_offset_enable(module_sel, rx_vref_offset_enable);
}

TEST(ucie_eye_of_margin, normal_m0_eom_status_check)
{
	uint32_t eml_m0[68];
	uint32_t emr_m0[68];

	uint32_t exp_eml_m0[68];
	uint32_t exp_emr_m0[68];

	for (int i = 0; i < 68; i++) {
		exp_eml_m0[i] = i;
		exp_emr_m0[i] = i;
	}

	_set_rx_vref_offset_by_phy_compliance_test(0, RX_VREF_OFFSET_EN_NONE, 0);

	for (int i = 0; i < 68; i++) {
		_set_mock_eml_emr_for_eom(0, exp_eml_m0[i], exp_emr_m0[i], i);
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_retrain_and_get_new_eml_emr(0, &eml_m0[i], &emr_m0[i], i));
	}
}

TEST(ucie_eye_of_margin, fail_m0_eom_status_check)
{
	uint32_t eml_m0[68];
	uint32_t emr_m0[68];

	_set_rx_vref_offset_by_phy_compliance_test(0, RX_VREF_OFFSET_EN_NONE, 0);

	for (int i = 0; i < 68; i++) {
		_set_mock_status_for_eom(0);
		TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_retrain_and_get_new_eml_emr(0, &eml_m0[i], &emr_m0[i], i));
	}
}

TEST(ucie_eye_of_margin, check_m0_eom_by_rx_vref_offset_none)
{
	uint32_t eml_m0[68];
	uint32_t emr_m0[68];

	uint32_t exp_eml_m0[68];
	uint32_t exp_emr_m0[68];

	for (int i = 0; i < 68; i++) {
		exp_eml_m0[i] = i;
		exp_emr_m0[i] = i;
	}

	_set_rx_vref_offset_by_phy_compliance_test(0, RX_VREF_OFFSET_EN_NONE, 0);

	for (int i = 0; i < 68; i++) {
		_set_mock_eml_emr_for_eom(0, exp_eml_m0[i], exp_emr_m0[i], i);
		aw_ucie_retrain_and_get_new_eml_emr(0, &eml_m0[i], &emr_m0[i], i);

		TEST_ASSERT_EQUAL(eml_m0[i], exp_eml_m0[i]);
		TEST_ASSERT_EQUAL(emr_m0[i], exp_emr_m0[i]);
	}
}

TEST(ucie_eye_of_margin, check_m0_eom_by_rx_vref_offset_add_max)
{
	uint32_t eml_m0[68];
	uint32_t emr_m0[68];

	uint32_t exp_eml_m0[68];
	uint32_t exp_emr_m0[68];

	for (int i = 0; i < 68; i++) {
		exp_eml_m0[i] = i;
		exp_emr_m0[i] = i;
	}
	_set_rx_vref_offset_by_phy_compliance_test(0, RX_VREF_OFFSET_EN_ADD, 0XFF);

	for (int i = 0; i < 68; i++) {
		_set_mock_eml_emr_for_eom(0, exp_eml_m0[i], exp_emr_m0[i], i);
		aw_ucie_retrain_and_get_new_eml_emr(0, &eml_m0[i], &emr_m0[i], i);

		TEST_ASSERT_EQUAL(eml_m0[i], exp_eml_m0[i]);
		TEST_ASSERT_EQUAL(emr_m0[i], exp_emr_m0[i]);
	}
}

TEST(ucie_eye_of_margin, check_m0_eom_by_rx_vref_offset_sub_max)
{
	uint32_t eml_m0[68];
	uint32_t emr_m0[68];

	uint32_t exp_eml_m0[68];
	uint32_t exp_emr_m0[68];

	for (int i = 0; i < 68; i++) {
		exp_eml_m0[i] = i;
		exp_emr_m0[i] = i;
	}
	_set_rx_vref_offset_by_phy_compliance_test(0, RX_VREF_OFFSET_EN_SUB, 0XFF);

	for (int i = 0; i < 68; i++) {
		_set_mock_eml_emr_for_eom(0, exp_eml_m0[i], exp_emr_m0[i], i);
		aw_ucie_retrain_and_get_new_eml_emr(0, &eml_m0[i], &emr_m0[i], i);

		TEST_ASSERT_EQUAL(eml_m0[i], exp_eml_m0[i]);
		TEST_ASSERT_EQUAL(emr_m0[i], exp_emr_m0[i]);
	}
}

TEST(ucie_eye_of_margin, normal_m1_eom_status_check)
{
	uint32_t eml_m1[68];
	uint32_t emr_m1[68];

	uint32_t exp_eml_m1[68];
	uint32_t exp_emr_m1[68];

	for (int i = 0; i < 68; i++) {
		exp_eml_m1[i] = i;
		exp_emr_m1[i] = i;
	}

	_set_rx_vref_offset_by_phy_compliance_test(1, RX_VREF_OFFSET_EN_NONE, 0);

	for (int i = 0; i < 68; i++) {
		_set_mock_eml_emr_for_eom(1, exp_eml_m1[i], exp_emr_m1[i], i);

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_retrain_and_get_new_eml_emr(1, &eml_m1[i], &emr_m1[i], i));
	}
}

TEST(ucie_eye_of_margin, fail_m1_eom_status_check)
{
	uint32_t eml_m1[68];
	uint32_t emr_m1[68];

	_set_rx_vref_offset_by_phy_compliance_test(1, RX_VREF_OFFSET_EN_NONE, 0);

	for (int i = 0; i < 68; i++) {
		_set_mock_status_for_eom(0);

		TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_retrain_and_get_new_eml_emr(1, &eml_m1[i], &emr_m1[i], i));
	}
}

TEST(ucie_eye_of_margin, check_m1_eom_by_rx_vref_offset_none)
{
	uint32_t eml_m1[68];
	uint32_t emr_m1[68];

	uint32_t exp_eml_m1[68];
	uint32_t exp_emr_m1[68];

	for (int i = 0; i < 68; i++) {
		exp_eml_m1[i] = i;
		exp_emr_m1[i] = i;
	}
	_set_rx_vref_offset_by_phy_compliance_test(1, RX_VREF_OFFSET_EN_NONE, 0);

	for (int i = 0; i < 68; i++) {
		_set_mock_eml_emr_for_eom(1, exp_eml_m1[i], exp_emr_m1[i], i);
		aw_ucie_retrain_and_get_new_eml_emr(1, &eml_m1[i], &emr_m1[i], i);

		TEST_ASSERT_EQUAL(eml_m1[i], exp_eml_m1[i]);
		TEST_ASSERT_EQUAL(emr_m1[i], exp_emr_m1[i]);
	}
}

TEST(ucie_eye_of_margin, check_m1_eom_by_rx_vref_offset_add_max)
{
	uint32_t eml_m1[68];
	uint32_t emr_m1[68];

	uint32_t exp_eml_m1[68];
	uint32_t exp_emr_m1[68];

	for (int i = 0; i < 68; i++) {
		exp_eml_m1[i] = i;
		exp_emr_m1[i] = i;
	}
	_set_rx_vref_offset_by_phy_compliance_test(0, RX_VREF_OFFSET_EN_ADD, 0XFF);

	for (int i = 0; i < 68; i++) {
		_set_mock_eml_emr_for_eom(1, exp_eml_m1[i], exp_emr_m1[i], i);
		aw_ucie_retrain_and_get_new_eml_emr(1, &eml_m1[i], &emr_m1[i], i);

		TEST_ASSERT_EQUAL(eml_m1[i], exp_eml_m1[i]);
		TEST_ASSERT_EQUAL(emr_m1[i], exp_emr_m1[i]);
	}
}

TEST(ucie_eye_of_margin, check_m1_eom_by_rx_vref_offset_sub_max)
{
	uint32_t eml_m1[68];
	uint32_t emr_m1[68];

	uint32_t exp_eml_m1[68];
	uint32_t exp_emr_m1[68];

	for (int i = 0; i < 68; i++) {
		exp_eml_m1[i] = i;
		exp_emr_m1[i] = i;
	}
	_set_rx_vref_offset_by_phy_compliance_test(0, RX_VREF_OFFSET_EN_SUB, 0XFF);

	for (int i = 0; i < 68; i++) {
		_set_mock_eml_emr_for_eom(1, exp_eml_m1[i], exp_emr_m1[i], i);
		aw_ucie_retrain_and_get_new_eml_emr(1, &eml_m1[i], &emr_m1[i], i);

		TEST_ASSERT_EQUAL(eml_m1[i], exp_eml_m1[i]);
		TEST_ASSERT_EQUAL(emr_m1[i], exp_emr_m1[i]);
	}
}

TEST_GROUP_RUNNER(ucie_eye_of_margin_except_only_for_mock)
{
	RUN_TEST_CASE(ucie_eye_of_margin, normal_m0_eom_status_check);
	RUN_TEST_CASE(ucie_eye_of_margin, fail_m0_eom_status_check);

	RUN_TEST_CASE(ucie_eye_of_margin, check_m0_eom_by_rx_vref_offset_none);
	RUN_TEST_CASE(ucie_eye_of_margin, check_m0_eom_by_rx_vref_offset_add_max);
	RUN_TEST_CASE(ucie_eye_of_margin, check_m0_eom_by_rx_vref_offset_sub_max);

	RUN_TEST_CASE(ucie_eye_of_margin, normal_m1_eom_status_check);
	RUN_TEST_CASE(ucie_eye_of_margin, fail_m1_eom_status_check);

	RUN_TEST_CASE(ucie_eye_of_margin, check_m1_eom_by_rx_vref_offset_none);
	RUN_TEST_CASE(ucie_eye_of_margin, check_m1_eom_by_rx_vref_offset_add_max);
	RUN_TEST_CASE(ucie_eye_of_margin, check_m1_eom_by_rx_vref_offset_sub_max);
}

TEST_GROUP_RUNNER(ucie_eye_of_margin_only_for_mock)
{

}
