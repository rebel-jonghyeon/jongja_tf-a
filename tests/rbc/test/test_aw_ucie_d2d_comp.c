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
static int32_t (*sb_mem_wr32_bk)(const uint32_t, const uint32_t, uint32_t *const);

static void _retrain_and_check_adv_cap_log1_zero(void)
{
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1 adv_cap = {};

	*wr_buf_ptr = *mmio_ptr;
	adv_cap.val = ~(0);
	wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1.val =
		adv_cap.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_d2d_adv_adp_log1(adv_cap.val));
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1.val = 0;

	PAUSE(target_ss);
	aw_ucie_link_retraining();
	RESUME(target_ss);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_adv_adp_log1(&adv_cap.val));
	TEST_ASSERT_EQUAL(0, adv_cap.val);
}

static void _set_adap_compliance_mode(int mode)
{
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl compliance_ctrl = {};

	*wr_buf_ptr = *mmio_ptr;
	compliance_ctrl.compliance_mode = mode;
	compliance_ctrl.compliance_force_link_reset = DISABLE;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl.val =
		compliance_ctrl.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	if (mode == ADAP_COMPLIANCE_MODE_PHY_ONLY) {
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_adap_test_comp_phy_only_mode());
	} else if (mode == ADAP_COMPLIANCE_MODE_ADAPTER) {
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_adap_test_comp_adap_mode());
	} else if (mode == ADAP_COMPLIANCE_MODE_NORMAL) {
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_adap_test_comp_normal_mode());
	} else {
		TEST_FAIL_MESSAGE("Invalid injection mode!!");
	}
	aw_ucie_sb_mem_wr32(UCIE_REG_BLK_ID_TEST_COMP, 0x20/* Adapter Compliance Control Reg */, &compliance_ctrl.val);
}

static void _mocking_for_disable_flit_inj(void)
{
	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1.flit_tx_inj_enable = DISABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
}

static int32_t _test_inject_test_flits(uint32_t inj_mode, uint32_t flit_num, uint32_t flit_type,
									   uint32_t payload_type, uint32_t payload_pattern,
									   uint32_t pattern_offset, uint32_t pattern_rep)
{
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1 injt_ctrl1 = {};
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl2 injt_ctrl2 = {};

	_set_adap_compliance_mode(ADAP_COMPLIANCE_MODE_ADAPTER);

	*wr_buf_ptr = *mmio_ptr;
	injt_ctrl1.flit_tx_inj_enable = ENABLE;
	injt_ctrl1.flit_type = flit_type;
	injt_ctrl1.flit_inj_number = flit_num;
	injt_ctrl1.inj_mode = inj_mode;
	injt_ctrl1.payload_type = payload_type;
	injt_ctrl1.flit_byte_offset = pattern_offset;
	injt_ctrl1.pattern_repetition = pattern_rep;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1.val =
		injt_ctrl1.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	if (flit_type != FLIT_INJECT_FLIT_TYPE_NOP) {
		injt_ctrl2.payload_fixed_pattern = payload_pattern;
		wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl2.val =
			injt_ctrl2.val;
		PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	}

	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.flit_tx_inj_sts =
		FLIT_INJECT_STAT_NO_FLIT;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.flit_tx_inj_sts =
		FLIT_INJECT_STAT_ONGOING;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	if (inj_mode != FLIT_INJECT_MODE_CONT) {
		mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.flit_tx_inj_sts =
			FLIT_INJECT_STAT_DONE;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		_mocking_for_disable_flit_inj();
	}

	if (flit_type == FLIT_INJECT_FLIT_TYPE_NOP)
		return aw_ucie_mb_inject_nop_flit(inj_mode, flit_num);
	else if (flit_type == FLIT_INJECT_FLIT_TYPE_TEST)
		return aw_ucie_mb_inject_test_flit(inj_mode, flit_num, injt_ctrl1.payload_type,
											payload_pattern, pattern_offset, pattern_rep);
	else if (flit_type == FLIT_INJECT_FLIT_TYPE_ALT)
		return aw_ucie_mb_inject_alt_flit(inj_mode, flit_num, injt_ctrl1.payload_type,
											payload_pattern, pattern_offset, pattern_rep);
	else
		TEST_FAIL();
	/* Should be added checking flit rx status of remote side through SB mailbox */
}

TEST_GROUP(ucie_d2d_comp);

TEST_SETUP(ucie_d2d_comp)
{
	CLEAR_SNAPSHOT_ARR(reg[ucie_ss_id]);
	CLEAR_SNAPSHOT_ARR(target_ss);

	link_training_bk = aw_ucie_link_training;
	link_retraining_bk = aw_ucie_link_retraining;
	sb_mem_wr32_bk = aw_ucie_sb_mem_wr32;
#ifdef USE_DILIGENT_PTR
	aw_ucie_link_training = dummy_aw_ucie_link_training;
	link_retraining_counter = 0;
	aw_ucie_link_retraining = dummy_aw_ucie_link_retraining;
	aw_ucie_sb_mem_wr32 = dummy_aw_ucie_sb_mem_wr32;
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

static void _adap_test_comp_force_reset(void)
{
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl compliance_ctrl = {};

	compliance_ctrl.val = mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl.val;
	compliance_ctrl.compliance_force_link_reset = ENABLE;
	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl.val = compliance_ctrl.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_link_status = DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_link_status = ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_adap_test_comp_force_reset());
}

TEST_TEAR_DOWN(ucie_d2d_comp)
{
	_set_adap_compliance_mode(ADAP_COMPLIANCE_MODE_NORMAL);
	_adap_test_comp_force_reset();

	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);

	aw_ucie_link_training = link_training_bk;
	aw_ucie_link_retraining = link_retraining_bk;
	aw_ucie_sb_mem_wr32 = sb_mem_wr32_bk;
}

TEST(ucie_d2d_comp, adap_compliance_ctrl_phy_only)
{
	uint32_t retrain_check_loop = 3;

	_set_adap_compliance_mode(ADAP_COMPLIANCE_MODE_PHY_ONLY);
	while (retrain_check_loop--) {
		_retrain_and_check_adv_cap_log1_zero();
	}

	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};

	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.compliance_sts = ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_adap_test_comp_stat(&test_sts.val));
	TEST_ASSERT_EQUAL(ENABLE, test_sts.compliance_sts);
}

TEST(ucie_d2d_comp, adap_compliance_ctrl_adapter)
{
	uint32_t retrain_check_loop = 3;

	_set_adap_compliance_mode(ADAP_COMPLIANCE_MODE_ADAPTER);
	while (retrain_check_loop--) {
		_retrain_and_check_adv_cap_log1_zero();
	}

	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};

	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.compliance_sts = ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_adap_test_comp_stat(&test_sts.val));
	TEST_ASSERT_EQUAL(ENABLE, test_sts.compliance_sts);
}

TEST(ucie_d2d_comp, adap_compliance_force_reset)
{
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl compliance_ctrl = {};

	_set_adap_compliance_mode(ADAP_COMPLIANCE_MODE_ADAPTER);
	_adap_test_comp_force_reset();

	/* Check result */
	compliance_ctrl.val = 0;
	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl.val =
		compliance_ctrl.val;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_adap_test_comp_ctrl(&compliance_ctrl.val));
	TEST_ASSERT_EQUAL(0, compliance_ctrl.val);
}

TEST(ucie_d2d_comp, inject_nop_flits_20)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_NOP,
											  NOT_USED_ARG, NOT_USED_ARG,
											  NOT_USED_ARG, NOT_USED_ARG));
}

TEST(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_all)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_ALL,
											  0xABCD0123, NOT_USED_ARG, NOT_USED_ARG));
}

TEST(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_offset_once)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_OFFSET_ONCE,
											  0xABCD0123, 0x3, NOT_USED_ARG));
}

TEST(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_offset_rep_0)
{
/* 7.5.4.4.2 Table 7-73 A value of 00h or 01h must be interpreted as a single pattern occurrence. */
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_OFFSET_REP,
											  0xABCD0123, 0x3, 0));
}

TEST(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_offset_rep_1)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_OFFSET_REP,
											  0xABCD0123, 0x3, 1));
}

TEST(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_offset_rep_2)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_OFFSET_REP,
											  0xABCD0123, 0x3, 2));
}

TEST(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_offset_rep_33)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_OFFSET_REP,
											  0xABCD0123, 0x3, 33));
}

TEST(ucie_d2d_comp, inject_test_flits_20_random_pattern_all)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_ALL,
											  NOT_USED_ARG, NOT_USED_ARG, NOT_USED_ARG));
}

TEST(ucie_d2d_comp, inject_test_flits_20_random_pattern_offset_once)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_ONCE,
											  NOT_USED_ARG, 0x3, NOT_USED_ARG));
}

TEST(ucie_d2d_comp, inject_test_flits_20_random_pattern_offset_rep_0)
{
/* 7.5.4.4.2 Table 7-73 A value of 00h or 01h must be interpreted as a single pattern occurrence. */
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_REP,
											  NOT_USED_ARG, 0x3, 0));
}

TEST(ucie_d2d_comp, inject_test_flits_20_random_pattern_offset_rep_1)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_REP,
											  NOT_USED_ARG, 0x3, 1));
}

TEST(ucie_d2d_comp, inject_test_flits_20_random_pattern_offset_rep_2)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_REP,
											  NOT_USED_ARG, 0x3, 2));
}

TEST(ucie_d2d_comp, inject_test_flits_20_random_pattern_offset_rep_33)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 20, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_REP,
											  NOT_USED_ARG, 0x3, 33));
}

TEST(ucie_d2d_comp, inject_nop_flits_cont)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_NOP,
											  NOT_USED_ARG, NOT_USED_ARG,
											  NOT_USED_ARG, NOT_USED_ARG));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_nop_flits_cont_with_prot_flit)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_NOP,
											  NOT_USED_ARG, NOT_USED_ARG,
											  NOT_USED_ARG, NOT_USED_ARG));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_all)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_ALL,
											  0xABCD0123, NOT_USED_ARG, NOT_USED_ARG));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_offset_once)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_OFFSET_ONCE,
											  0xABCD0123, 0x3, NOT_USED_ARG));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_offset_rep_0)
{
/* 7.5.4.4.2 Table 7-73 A value of 00h or 01h must be interpreted as a single pattern occurrence. */
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_OFFSET_REP,
											  0xABCD0123, 0x3, 0));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_offset_rep_1)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_OFFSET_REP,
											  0xABCD0123, 0x3, 1));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_offset_rep_2)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_OFFSET_REP,
											  0xABCD0123, 0x3, 2));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_offset_rep_33)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_FIXED_OFFSET_REP,
											  0xABCD0123, 0x3, 33));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_random_pattern_all)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_ALL,
											  NOT_USED_ARG, NOT_USED_ARG, NOT_USED_ARG));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_random_pattern_offset_once)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_ONCE,
											  NOT_USED_ARG, 0x3, NOT_USED_ARG));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_random_pattern_offset_rep_0)
{
/* 7.5.4.4.2 Table 7-73 A value of 00h or 01h must be interpreted as a single pattern occurrence. */
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_REP,
											  NOT_USED_ARG, 0x3, 0));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_random_pattern_offset_rep_1)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_REP,
											  NOT_USED_ARG, 0x3, 1));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_random_pattern_offset_rep_2)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_REP,
											  NOT_USED_ARG, 0x3, 2));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_test_flits_cont_random_pattern_offset_rep_33)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_OFFSET_REP,
											  NOT_USED_ARG, 0x3, 33));
	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

IGNORE_TEST(ucie_d2d_comp, inject_test_flits_cont_interleaving_random_pattern_all)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_W_INTL, -1, FLIT_INJECT_FLIT_TYPE_TEST,
											  FLIT_INJECT_PAYLOAD_RANDOM_ALL,
											  NOT_USED_ARG, NOT_USED_ARG, NOT_USED_ARG));
#ifndef USE_DILIGENT_PTR
	/* remote die area access should be added and then it would be moved to higher level test. */
#endif /* USE_DILIGENT_PTR */

	_mocking_for_disable_flit_inj();
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_inject_flit_disable());
}

TEST(ucie_d2d_comp, inject_alt_flits_50_random_pattern_all)
{
	TEST_ASSERT_EQUAL(RL_OK,
					  _test_inject_test_flits(FLIT_INJECT_MODE_NUM_WO_INTL, 50, FLIT_INJECT_FLIT_TYPE_ALT,
											  FLIT_INJECT_PAYLOAD_RANDOM_ALL,
											  NOT_USED_ARG, NOT_USED_ARG, NOT_USED_ARG));
}

static void _test_inject_req_fdi_state(const uint32_t state)
{
	_set_adap_compliance_mode(ADAP_COMPLIANCE_MODE_ADAPTER);

	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 inj_ctrl = {};

	*wr_buf_ptr = *mmio_ptr;
	inj_ctrl.stack0_link_req = state;
	inj_ctrl.stack0_inj_type = LINK_STATE_INJ_TYPE_REQ;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 = inj_ctrl;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	inj_ctrl.stack0_req_or_resp_inj_en_at_tx = ENABLE;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 = inj_ctrl;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.lstate_req_inj_sts_for_stack0 =
		DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.lstate_req_inj_sts_for_stack0 =
		ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	*wr_buf_ptr = *mmio_ptr;
	inj_ctrl.stack0_req_or_resp_inj_en_at_tx = DISABLE;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 = inj_ctrl;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_state_req_inject_stack0(state));
}

TEST(ucie_d2d_comp, inject_req_fdi_state_nop)
{
	_test_inject_req_fdi_state(RDI_FDI_STATE_NOP);
}

TEST(ucie_d2d_comp, inject_req_fdi_state_active)
{
	_test_inject_req_fdi_state(RDI_FDI_STATE_ACTIVE);
}

TEST(ucie_d2d_comp, inject_req_fdi_state_l1)
{
	_test_inject_req_fdi_state(RDI_FDI_STATE_L1);
}

TEST(ucie_d2d_comp, inject_req_fdi_state_l2)
{
	_test_inject_req_fdi_state(RDI_FDI_STATE_L2);
}

TEST(ucie_d2d_comp, inject_req_fdi_state_linkreset)
{
	_test_inject_req_fdi_state(RDI_FDI_STATE_LINKRESET);
}

TEST(ucie_d2d_comp, inject_req_fdi_state_retrain)
{
	_test_inject_req_fdi_state(RDI_FDI_STATE_RETRAIN);
}

TEST(ucie_d2d_comp, inject_req_fdi_state_disabled)
{
	_test_inject_req_fdi_state(RDI_FDI_STATE_DISABLED);
}

static void _test_inject_resp_fdi_state(const uint32_t state)
{
	_set_adap_compliance_mode(ADAP_COMPLIANCE_MODE_ADAPTER);

	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 inj_ctrl = {};

	*wr_buf_ptr = *mmio_ptr;
	inj_ctrl.stack0_link_resp = state;
	inj_ctrl.stack0_inj_type = LINK_STATE_INJ_TYPE_RESP;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 = inj_ctrl;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	inj_ctrl.stack0_req_or_resp_inj_en_at_tx = ENABLE;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 = inj_ctrl;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.lstate_resp_inj_sts_for_stack0 =
		DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.lstate_resp_inj_sts_for_stack0 =
		ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	*wr_buf_ptr = *mmio_ptr;
	inj_ctrl.stack0_req_or_resp_inj_en_at_tx = DISABLE;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 = inj_ctrl;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_state_resp_inject_stack0(state));
}

TEST(ucie_d2d_comp, inject_resp_fdi_state_nop)
{
	_test_inject_resp_fdi_state(RDI_FDI_STATE_NOP);
}

TEST(ucie_d2d_comp, inject_resp_fdi_state_active)
{
	_test_inject_resp_fdi_state(RDI_FDI_STATE_ACTIVE);
}

TEST(ucie_d2d_comp, inject_resp_fdi_state_l1)
{
	_test_inject_resp_fdi_state(RDI_FDI_STATE_L1);
}

TEST(ucie_d2d_comp, inject_resp_fdi_state_l2)
{
	_test_inject_resp_fdi_state(RDI_FDI_STATE_L2);
}

TEST(ucie_d2d_comp, inject_resp_fdi_state_linkreset)
{
	_test_inject_resp_fdi_state(RDI_FDI_STATE_LINKRESET);
}

TEST(ucie_d2d_comp, inject_resp_fdi_state_retrain)
{
	_test_inject_resp_fdi_state(RDI_FDI_STATE_RETRAIN);
}

TEST(ucie_d2d_comp, inject_resp_fdi_state_disabled)
{
	_test_inject_resp_fdi_state(RDI_FDI_STATE_DISABLED);
}

static void _set_inject_retry_ctrl(const uint32_t err_type, const uint32_t byte_offset,
								   const uint32_t num_btwn_err, const uint32_t num_err_flits,
								   const uint32_t flit_type, const uint32_t retry_thre)
{
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1 inj_ctrl1 = {};
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl2 inj_ctrl2 = {};

	inj_ctrl1.error_inj_type_on_txd_flits = err_type;
	inj_ctrl1.byte_offset = byte_offset;
	inj_ctrl1.num_of_errs_btwn_inj_errs = num_btwn_err;
	inj_ctrl1.num_of_errs_inj = num_err_flits;
	inj_ctrl1.flit_type_for_err_inj = flit_type;
	inj_ctrl2.tx_retry_err_th = retry_thre;

	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1.val = inj_ctrl1.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl2.val = inj_ctrl2.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1.retry_inj_enable = ENABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.retry_inj_sts =
		RETRY_INJECT_STAT_NO_ERROR;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.retry_inj_sts =
		RETRY_INJECT_STAT_ONGOING;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.retry_inj_sts =
		RETRY_INJECT_STAT_DONE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1.retry_inj_enable = DISABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	aw_ucie_mb_inject_error(err_type, byte_offset, num_btwn_err, num_err_flits, flit_type,
							retry_thre);
}

int32_t (*bk_inject_test_func)(const uint32_t inj_mode, const uint32_t flit_num,
							   const uint32_t payload_type, const uint32_t pattern,
							   const uint32_t offset, const uint32_t repetition);
int32_t (*bk_inject_nop_func)(const uint32_t inj_mode, const uint32_t flit_num);

TEST(ucie_d2d_comp, inject_retry_1bit_error_w_threshold)
{
	bk_inject_test_func = aw_ucie_mb_inject_test_flit;
#ifdef USE_DILIGENT_PTR
	aw_ucie_mb_inject_test_flit = dummy_aw_ucie_mb_inject_test_flit;
#endif /* USE_DILIGENT_PTR */
	aw_ucie_mb_inject_test_flit(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_PAYLOAD_RANDOM_ALL,
								NOT_USED_ARG, NOT_USED_ARG, NOT_USED_ARG);

	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};
	const uint32_t num_of_inj_flits = 0x0;

	_set_inject_retry_ctrl(ERROR_INJ_TYPE_1BIT, get_random_of_range(0, 63), 0x0, num_of_inj_flits,
						   ERROR_INJ_FLIT_ANY, 0xf);

	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.num_of_retries_exceeded_th = ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_adap_test_comp_stat(&test_sts.val));
	TEST_ASSERT_EQUAL(ENABLE, test_sts.num_of_retries_exceeded_th);

	aw_ucie_mb_inject_test_flit = bk_inject_test_func;
}

TEST(ucie_d2d_comp, inject_retry_1bit_error_wo_threshold)
{
	bk_inject_test_func = aw_ucie_mb_inject_test_flit;
#ifdef USE_DILIGENT_PTR
	aw_ucie_mb_inject_test_flit = dummy_aw_ucie_mb_inject_test_flit;
#endif /* USE_DILIGENT_PTR */
	aw_ucie_mb_inject_test_flit(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_PAYLOAD_RANDOM_ALL,
								NOT_USED_ARG, NOT_USED_ARG, NOT_USED_ARG);

	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};
	const uint32_t num_of_inj_flits = 0x1;

	_set_inject_retry_ctrl(ERROR_INJ_TYPE_1BIT, get_random_of_range(0, 63), 0x1, num_of_inj_flits,
						   ERROR_INJ_FLIT_PAYLOAD, num_of_inj_flits + 1);

mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.num_of_retries_exceeded_th = DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_adap_test_comp_stat(&test_sts.val));
	TEST_ASSERT_EQUAL(DISABLE, test_sts.num_of_retries_exceeded_th);

	aw_ucie_mb_inject_test_flit = bk_inject_test_func;
}

TEST(ucie_d2d_comp, inject_retry_2bit_error_w_threshold)
{
	bk_inject_test_func = aw_ucie_mb_inject_test_flit;
#ifdef USE_DILIGENT_PTR
	aw_ucie_mb_inject_test_flit = dummy_aw_ucie_mb_inject_test_flit;
#endif /* USE_DILIGENT_PTR */
	aw_ucie_mb_inject_test_flit(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_PAYLOAD_RANDOM_ALL,
								NOT_USED_ARG, NOT_USED_ARG, NOT_USED_ARG);

	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};
	const uint32_t num_of_inj_flits = 0xf;

	_set_inject_retry_ctrl(ERROR_INJ_TYPE_2BIT, get_random_of_range(0, 63), 0x2, num_of_inj_flits,
						   ERROR_INJ_FLIT_TEST, num_of_inj_flits - 1);

	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.num_of_retries_exceeded_th = ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_adap_test_comp_stat(&test_sts.val));
	TEST_ASSERT_EQUAL(ENABLE, test_sts.num_of_retries_exceeded_th);

	aw_ucie_mb_inject_test_flit = bk_inject_test_func;
}

TEST(ucie_d2d_comp, inject_retry_2bit_error_wo_threshold)
{
	bk_inject_test_func = aw_ucie_mb_inject_test_flit;
#ifdef USE_DILIGENT_PTR
	aw_ucie_mb_inject_test_flit = dummy_aw_ucie_mb_inject_test_flit;
#endif /* USE_DILIGENT_PTR */
	aw_ucie_mb_inject_test_flit(FLIT_INJECT_MODE_CONT, -1, FLIT_INJECT_PAYLOAD_RANDOM_ALL,
								NOT_USED_ARG, NOT_USED_ARG, NOT_USED_ARG);

	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};
	const uint32_t num_of_inj_flits = 0xe;

	_set_inject_retry_ctrl(ERROR_INJ_TYPE_2BIT, get_random_of_range(0, 63), 0x1ff, num_of_inj_flits,
						   ERROR_INJ_FLIT_PAYLOAD_SAME_SEQ, num_of_inj_flits + 1);

mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.num_of_retries_exceeded_th = DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_adap_test_comp_stat(&test_sts.val));
	TEST_ASSERT_EQUAL(DISABLE, test_sts.num_of_retries_exceeded_th);

	aw_ucie_mb_inject_test_flit = bk_inject_test_func;
}

TEST(ucie_d2d_comp, inject_retry_3bit_error_w_threshold)
{
	bk_inject_nop_func = aw_ucie_mb_inject_nop_flit;
#ifdef USE_DILIGENT_PTR
	aw_ucie_mb_inject_nop_flit = dummy_aw_ucie_inject_nop_flit;
#endif /* USE_DILIGENT_PTR */
	aw_ucie_mb_inject_nop_flit(FLIT_INJECT_MODE_CONT, -1);

	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};
	const uint32_t num_of_inj_flits = 0xf;

	_set_inject_retry_ctrl(ERROR_INJ_TYPE_3BIT, get_random_of_range(0, 63), 0x1fe, num_of_inj_flits,
						   ERROR_INJ_FLIT_ANY, num_of_inj_flits - 1);

	mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.num_of_retries_exceeded_th = ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_adap_test_comp_stat(&test_sts.val));
	TEST_ASSERT_EQUAL(ENABLE, test_sts.num_of_retries_exceeded_th);

	aw_ucie_mb_inject_nop_flit = bk_inject_nop_func;
}

TEST(ucie_d2d_comp, inject_retry_3bit_error_wo_threshold)
{
	bk_inject_nop_func = aw_ucie_mb_inject_nop_flit;
#ifdef USE_DILIGENT_PTR
	aw_ucie_mb_inject_nop_flit = dummy_aw_ucie_inject_nop_flit;
#endif /* USE_DILIGENT_PTR */
	aw_ucie_mb_inject_nop_flit(FLIT_INJECT_MODE_CONT, -1);

	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};
	const uint32_t num_of_inj_flits = 0xe;

	_set_inject_retry_ctrl(ERROR_INJ_TYPE_3BIT, get_random_of_range(0, 63), 0x1ff, num_of_inj_flits,
						   ERROR_INJ_FLIT_NOP, num_of_inj_flits + 1);

mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.num_of_retries_exceeded_th = DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_adap_test_comp_stat(&test_sts.val));
	TEST_ASSERT_EQUAL(DISABLE, test_sts.num_of_retries_exceeded_th);

	aw_ucie_mb_inject_nop_flit = bk_inject_nop_func;
}

TEST_GROUP_RUNNER(ucie_d2d_comp_except_only_for_mock)
{
	RUN_TEST_CASE(ucie_d2d_comp, adap_compliance_ctrl_phy_only);
	RUN_TEST_CASE(ucie_d2d_comp, adap_compliance_ctrl_adapter);
	RUN_TEST_CASE(ucie_d2d_comp, adap_compliance_force_reset);

	RUN_TEST_CASE(ucie_d2d_comp, inject_nop_flits_20);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_all);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_offset_once);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_offset_rep_0);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_offset_rep_1);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_offset_rep_2);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_fixed_pattern_offset_rep_33);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_random_pattern_all);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_random_pattern_offset_once);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_random_pattern_offset_rep_0);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_random_pattern_offset_rep_1);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_random_pattern_offset_rep_2);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_20_random_pattern_offset_rep_33);

	RUN_TEST_CASE(ucie_d2d_comp, inject_nop_flits_cont);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_all);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_offset_once);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_offset_rep_0);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_offset_rep_1);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_offset_rep_2);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_fixed_pattern_offset_rep_33);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_random_pattern_all);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_random_pattern_offset_once);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_random_pattern_offset_rep_0);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_random_pattern_offset_rep_1);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_random_pattern_offset_rep_2);
	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_random_pattern_offset_rep_33);

	RUN_TEST_CASE(ucie_d2d_comp, inject_test_flits_cont_interleaving_random_pattern_all);
	RUN_TEST_CASE(ucie_d2d_comp, inject_alt_flits_50_random_pattern_all);

	RUN_TEST_CASE(ucie_d2d_comp, inject_req_fdi_state_nop);
	RUN_TEST_CASE(ucie_d2d_comp, inject_req_fdi_state_active);
	RUN_TEST_CASE(ucie_d2d_comp, inject_req_fdi_state_l1);
	RUN_TEST_CASE(ucie_d2d_comp, inject_req_fdi_state_l2);
	RUN_TEST_CASE(ucie_d2d_comp, inject_req_fdi_state_linkreset);
	RUN_TEST_CASE(ucie_d2d_comp, inject_req_fdi_state_retrain);
	RUN_TEST_CASE(ucie_d2d_comp, inject_req_fdi_state_disabled);
	RUN_TEST_CASE(ucie_d2d_comp, inject_resp_fdi_state_nop);
	RUN_TEST_CASE(ucie_d2d_comp, inject_resp_fdi_state_active);
	RUN_TEST_CASE(ucie_d2d_comp, inject_resp_fdi_state_l1);
	RUN_TEST_CASE(ucie_d2d_comp, inject_resp_fdi_state_l2);
	RUN_TEST_CASE(ucie_d2d_comp, inject_resp_fdi_state_linkreset);
	RUN_TEST_CASE(ucie_d2d_comp, inject_resp_fdi_state_retrain);
	RUN_TEST_CASE(ucie_d2d_comp, inject_resp_fdi_state_disabled);

	RUN_TEST_CASE(ucie_d2d_comp, inject_retry_1bit_error_w_threshold);
	RUN_TEST_CASE(ucie_d2d_comp, inject_retry_1bit_error_wo_threshold);
	RUN_TEST_CASE(ucie_d2d_comp, inject_retry_2bit_error_w_threshold);
	RUN_TEST_CASE(ucie_d2d_comp, inject_retry_2bit_error_wo_threshold);
	RUN_TEST_CASE(ucie_d2d_comp, inject_retry_3bit_error_w_threshold);
	RUN_TEST_CASE(ucie_d2d_comp, inject_retry_3bit_error_wo_threshold);
}

TEST_GROUP_RUNNER(ucie_d2d_comp_only_for_mock)
{

}

