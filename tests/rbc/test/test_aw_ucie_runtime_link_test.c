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
static int32_t (*sb_mem_rd32_bk)(const uint32_t, const uint32_t, uint32_t *const);

TEST_GROUP(ucie_runtime_link_test);

TEST_SETUP(ucie_runtime_link_test)
{
	CLEAR_SNAPSHOT_ARR(reg[ucie_ss_id]);
	CLEAR_SNAPSHOT_ARR(target_ss);

	link_training_bk = aw_ucie_link_training;
	link_retraining_bk = aw_ucie_link_retraining;
	sb_mem_rd32_bk = aw_ucie_sb_mem_rd32;
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

TEST_TEAR_DOWN(ucie_runtime_link_test)
{
	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);

	aw_ucie_link_training = link_training_bk;
	aw_ucie_link_retraining = link_retraining_bk;
	aw_ucie_sb_mem_rd32 = sb_mem_rd32_bk;
}

static void _set_mock_for_runtime_link_test(uint32_t m0_repair, uint32_t m1_repair, uint32_t m0_lane_id,
											uint32_t m1_lane_id, uint32_t stuck_at_fault)
{
	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1.m0_lane_repair = m0_repair;
	wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1.m1_lane_repair = m1_repair;
	wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1.m0_lane_repair_id = m0_lane_id;
	wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1.m1_lane_repair_id = m1_lane_id;
	wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1.inj_stuck_at_fault = stuck_at_fault;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1.start = ENABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	mmio_ptr->phy_d2d_reg_reg_phy_d2d_runtime_link_status_reg2.busy = true;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	mmio_ptr->phy_d2d_reg_reg_phy_d2d_runtime_link_status_reg2.busy = false;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
}

static void _set_repair_addr_by_lane_id(const uint32_t lane_id, uint32_t * const repair_addr_p0,
										uint32_t * const repair_addr_p1, uint32_t * const repair_addr_p2,
										uint32_t * const repair_addr_p3)
{
	if (lane_id < 32) {
		*repair_addr_p0 = lane_id;
		*repair_addr_p1 = 0xFF;
		*repair_addr_p2 = 0xFF;
		*repair_addr_p3 = 0xFF;
	} else if (lane_id < 64) {
		*repair_addr_p0 = 0xFF;
		*repair_addr_p1 = 0xFF;
		*repair_addr_p2 = lane_id;
		*repair_addr_p3 = 0xFF;
	} else if (lane_id == 64) {
		*repair_addr_p0 = 0xF0;
		*repair_addr_p1 = 0xFF;
		*repair_addr_p2 = 0xFF;
		*repair_addr_p3 = 0xFF;
	} else if (lane_id == 65) {
		*repair_addr_p0 = 0xFF;
		*repair_addr_p1 = 0xF0;
		*repair_addr_p2 = 0xFF;
		*repair_addr_p3 = 0xFF;
	} else if (lane_id == 66) {
		*repair_addr_p0 = 0xFF;
		*repair_addr_p1 = 0xFF;
		*repair_addr_p2 = 0xF0;
		*repair_addr_p3 = 0xFF;
	} else if (lane_id == 67) {
		*repair_addr_p0 = 0xFF;
		*repair_addr_p1 = 0xFF;
		*repair_addr_p2 = 0xFF;
		*repair_addr_p3 = 0xF0;
	} else {
		TEST_FAIL();
	}
}

static void _set_mock_for_check_mb_rpair_status_on_local(uint32_t m0_repair, uint32_t m1_repair,
														 uint32_t expt_trd_p0, uint32_t expt_trd_p1,
														 uint32_t expt_trd_p2, uint32_t expt_trd_p3)
{
	if (m0_repair) {
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1.m0_repair_addr_trd_p0 = expt_trd_p0;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1.m0_repair_addr_trd_p1 = expt_trd_p1;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1.m0_repair_addr_trd_p2 = expt_trd_p2;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1.m0_repair_addr_trd_p3 = expt_trd_p3;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2.m0_repair_addr_rrd_p0 = 0xFF;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2.m0_repair_addr_rrd_p1 = 0xFF;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2.m0_repair_addr_rrd_p2 = 0xFF;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2.m0_repair_addr_rrd_p3 = 0xFF;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	} else if (m1_repair) {
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1.m1_repair_addr_trd_p0 = expt_trd_p0;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1.m1_repair_addr_trd_p1 = expt_trd_p1;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1.m1_repair_addr_trd_p2 = expt_trd_p2;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1.m1_repair_addr_trd_p3 = expt_trd_p3;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2.m1_repair_addr_rrd_p0 = 0xFF;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2.m1_repair_addr_rrd_p1 = 0xFF;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2.m1_repair_addr_rrd_p2 = 0xFF;
		mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2.m1_repair_addr_rrd_p3 = 0xFF;
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	}
}

static void _test_assert_for_check_mb_rpair_status_on_local(uint32_t m0_repair, uint32_t m1_repair,
															uint32_t expt_trd_p0, uint32_t expt_trd_p1,
															uint32_t expt_trd_p2, uint32_t expt_trd_p3)
{
	if (m0_repair) {
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1 data_repair_reg1 = {};
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2 data_repair_reg2 = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_m0_lane_repair_stat(&data_repair_reg1.val, &data_repair_reg2.val));

		TEST_ASSERT_EQUAL(expt_trd_p0, data_repair_reg1.m0_repair_addr_trd_p0);
		TEST_ASSERT_EQUAL(expt_trd_p1, data_repair_reg1.m0_repair_addr_trd_p1);
		TEST_ASSERT_EQUAL(expt_trd_p2, data_repair_reg1.m0_repair_addr_trd_p2);
		TEST_ASSERT_EQUAL(expt_trd_p3, data_repair_reg1.m0_repair_addr_trd_p3);

		TEST_ASSERT_EQUAL(0xFF, data_repair_reg2.m0_repair_addr_rrd_p0);
		TEST_ASSERT_EQUAL(0xFF, data_repair_reg2.m0_repair_addr_rrd_p1);
		TEST_ASSERT_EQUAL(0xFF, data_repair_reg2.m0_repair_addr_rrd_p2);
		TEST_ASSERT_EQUAL(0xFF, data_repair_reg2.m0_repair_addr_rrd_p3);
	} else if (m1_repair) {
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1 data_repair_reg1 = {};
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2 data_repair_reg2 = {};

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_m1_lane_repair_stat(&data_repair_reg1.val, &data_repair_reg2.val));

		TEST_ASSERT_EQUAL(expt_trd_p0, data_repair_reg1.m1_repair_addr_trd_p0);
		TEST_ASSERT_EQUAL(expt_trd_p1, data_repair_reg1.m1_repair_addr_trd_p1);
		TEST_ASSERT_EQUAL(expt_trd_p2, data_repair_reg1.m1_repair_addr_trd_p2);
		TEST_ASSERT_EQUAL(expt_trd_p3, data_repair_reg1.m1_repair_addr_trd_p3);

		TEST_ASSERT_EQUAL(0xFF, data_repair_reg2.m1_repair_addr_rrd_p0);
		TEST_ASSERT_EQUAL(0xFF, data_repair_reg2.m1_repair_addr_rrd_p1);
		TEST_ASSERT_EQUAL(0xFF, data_repair_reg2.m1_repair_addr_rrd_p2);
		TEST_ASSERT_EQUAL(0xFF, data_repair_reg2.m1_repair_addr_rrd_p3);
	}
}

static void _check_mb_repair_status_on_local(uint32_t m0_repair, uint32_t m1_repair, uint32_t lane_id)
{
	uint32_t expt_trd_rrd_p0 = 0xFF;
	uint32_t expt_trd_rrd_p1 = 0xFF;
	uint32_t expt_trd_rrd_p2 = 0xFF;
	uint32_t expt_trd_rrd_p3 = 0xFF;

	_set_repair_addr_by_lane_id(lane_id, &expt_trd_rrd_p0, &expt_trd_rrd_p1, &expt_trd_rrd_p2, &expt_trd_rrd_p3);

	_set_mock_for_check_mb_rpair_status_on_local(m0_repair, m1_repair, expt_trd_rrd_p0, expt_trd_rrd_p1,
												 expt_trd_rrd_p2, expt_trd_rrd_p3);

	_test_assert_for_check_mb_rpair_status_on_local(m0_repair, m1_repair, expt_trd_rrd_p0, expt_trd_rrd_p1,
													expt_trd_rrd_p2, expt_trd_rrd_p3);
}

static void _test_assert_for_check_trd_of_mb_repair_status_on_remote_by_sb(uint32_t m0_repair, uint32_t m1_repair)
{
	if (m0_repair) {
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1 sb_data_repair_reg1 = {}; // tx

		sb_data_repair_reg1.val = 0;

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(0, 0x110C, &sb_data_repair_reg1.val)); // tx
		TEST_ASSERT_EQUAL(0xFF, sb_data_repair_reg1.m0_repair_addr_trd_p0);
		TEST_ASSERT_EQUAL(0xFF, sb_data_repair_reg1.m0_repair_addr_trd_p1);
		TEST_ASSERT_EQUAL(0xFF, sb_data_repair_reg1.m0_repair_addr_trd_p2);
		TEST_ASSERT_EQUAL(0xFF, sb_data_repair_reg1.m0_repair_addr_trd_p3);
	}
	if (m1_repair) {
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1 sb_data_repair_reg1 = {}; // tx

		sb_data_repair_reg1.val = 0;

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(0, 0x1114, &sb_data_repair_reg1.val)); // tx
		TEST_ASSERT_EQUAL(0xFF, sb_data_repair_reg1.m1_repair_addr_trd_p0);
		TEST_ASSERT_EQUAL(0xFF, sb_data_repair_reg1.m1_repair_addr_trd_p1);
		TEST_ASSERT_EQUAL(0xFF, sb_data_repair_reg1.m1_repair_addr_trd_p2);
		TEST_ASSERT_EQUAL(0xFF, sb_data_repair_reg1.m1_repair_addr_trd_p3);
	}
}

static void _test_assert_for_check_rrd_of_mb_repair_status_on_remote_by_sb(uint32_t m0_repair, uint32_t m1_repair,
																		   uint32_t expt_rrd_p0,
																		   uint32_t expt_rrd_p1,
																		   uint32_t expt_rrd_p2,
																		   uint32_t expt_rrd_p3)
{
	if (m0_repair) {
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2 sb_data_repair_reg2 = {}; // rx

		sb_data_repair_reg2.val = 0;

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(0, 0x1110, &sb_data_repair_reg2.val)); // rx
		TEST_ASSERT_EQUAL(expt_rrd_p0, sb_data_repair_reg2.m0_repair_addr_rrd_p0);
		TEST_ASSERT_EQUAL(expt_rrd_p1, sb_data_repair_reg2.m0_repair_addr_rrd_p1);
		TEST_ASSERT_EQUAL(expt_rrd_p2, sb_data_repair_reg2.m0_repair_addr_rrd_p2);
		TEST_ASSERT_EQUAL(expt_rrd_p3, sb_data_repair_reg2.m0_repair_addr_rrd_p3);
	}
	if (m1_repair) {
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2 sb_data_repair_reg2 = {}; // rx

		sb_data_repair_reg2.val = 0;

		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(0, 0x1118, &sb_data_repair_reg2.val)); // rx
		TEST_ASSERT_EQUAL(expt_rrd_p0, sb_data_repair_reg2.m1_repair_addr_rrd_p0);
		TEST_ASSERT_EQUAL(expt_rrd_p1, sb_data_repair_reg2.m1_repair_addr_rrd_p1);
		TEST_ASSERT_EQUAL(expt_rrd_p2, sb_data_repair_reg2.m1_repair_addr_rrd_p2);
		TEST_ASSERT_EQUAL(expt_rrd_p3, sb_data_repair_reg2.m1_repair_addr_rrd_p3);
	}
}

static void _check_mb_repair_status_on_remote_by_sb(uint32_t m0_repair, uint32_t m1_repair, uint32_t lane_id)
{
	uint32_t expt_trd_rrd_p0 = 0xFF;
	uint32_t expt_trd_rrd_p1 = 0xFF;
	uint32_t expt_trd_rrd_p2 = 0xFF;
	uint32_t expt_trd_rrd_p3 = 0xFF;

	_set_repair_addr_by_lane_id(lane_id, &expt_trd_rrd_p0, &expt_trd_rrd_p1, &expt_trd_rrd_p2, &expt_trd_rrd_p3);

#ifdef USE_DILIGENT_PTR
	aw_ucie_sb_mem_rd32 = fake_aw_ucie_sb_mem_rd32;
#endif /* USE_DILIGENT_PTR */

#ifdef USE_DILIGENT_PTR
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1 exp_data_repair_reg1_for_sb = {};

	exp_data_repair_reg1_for_sb.m0_repair_addr_trd_p0 = 0xFF;
	exp_data_repair_reg1_for_sb.m0_repair_addr_trd_p1 = 0xFF;
	exp_data_repair_reg1_for_sb.m0_repair_addr_trd_p2 = 0xFF;
	exp_data_repair_reg1_for_sb.m0_repair_addr_trd_p3 = 0xFF;

	set_value_fake_aw_ucie_sb_mem_rd32(exp_data_repair_reg1_for_sb.val);
#endif

	_test_assert_for_check_trd_of_mb_repair_status_on_remote_by_sb(m0_repair,  m1_repair);

#ifdef USE_DILIGENT_PTR
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2 exp_data_repair_reg2_for_sb = {};

	exp_data_repair_reg2_for_sb.m0_repair_addr_rrd_p0 = expt_trd_rrd_p0;
	exp_data_repair_reg2_for_sb.m0_repair_addr_rrd_p1 = expt_trd_rrd_p1;
	exp_data_repair_reg2_for_sb.m0_repair_addr_rrd_p2 = expt_trd_rrd_p2;
	exp_data_repair_reg2_for_sb.m0_repair_addr_rrd_p3 = expt_trd_rrd_p3;

	set_value_fake_aw_ucie_sb_mem_rd32(exp_data_repair_reg2_for_sb.val);
#endif

	_test_assert_for_check_rrd_of_mb_repair_status_on_remote_by_sb(m0_repair, m1_repair, expt_trd_rrd_p0,
																   expt_trd_rrd_p1, expt_trd_rrd_p2, expt_trd_rrd_p3);
}

static void _check_repair_status(uint32_t m0_repair, uint32_t m1_repair, uint32_t m0_lane_id, uint32_t m1_lane_id)
{
	if (!m0_repair && !m1_repair)
		TEST_FAIL();

	if (m0_repair) {
		_check_mb_repair_status_on_local(m0_repair, m1_repair, m0_lane_id);
		_check_mb_repair_status_on_remote_by_sb(m0_repair, m1_repair, m0_lane_id);
	}
	if (m1_repair) {
		_check_mb_repair_status_on_local(m0_repair, m1_repair, m1_lane_id);
		_check_mb_repair_status_on_remote_by_sb(m0_repair, m1_repair, m1_lane_id);
	}
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id00_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 0, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 0, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 0, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id01_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 1, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 1, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 1, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id02_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 2, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 2, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 2, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id03_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 3, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 3, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 3, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id04_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 4, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 4, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 4, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id05_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 5, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 5, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 5, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id06_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 6, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 6, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 6, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id07_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 7, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 7, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 7, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id08_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 8, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 8, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 8, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id09_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 9, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 9, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 9, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id10_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 10, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 10, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 10, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id11_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 11, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 11, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 11, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id12_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 12, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 12, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 12, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id13_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 13, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 13, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 13, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id14_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 14, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 14, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 14, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id15_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 15, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 15, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 15, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id16_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 16, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 16, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 16, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id17_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 17, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 17, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 17, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id18_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 18, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 18, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 18, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id19_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 19, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 19, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 19, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id20_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 20, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 20, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 20, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id21_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 21, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 21, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 21, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id22_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 22, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 22, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 22, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id23_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 23, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 23, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 23, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id24_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 24, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 24, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 24, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id25_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 25, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 25, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 25, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id26_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 26, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 26, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 26, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id27_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 27, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 27, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 27, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id28_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 28, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 28, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 28, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id29_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 29, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 29, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 29, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id30_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 30, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 30, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 30, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id31_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 31, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 31, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 31, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id32_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 32, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 32, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 32, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id33_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 33, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 33, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 33, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id34_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 34, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 34, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 34, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id35_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 35, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 35, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 35, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id36_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 36, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 36, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 36, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id37_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 37, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 37, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 37, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id38_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 38, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 38, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 38, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id39_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 39, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 39, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 39, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id40_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 40, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 40, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 40, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id41_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 41, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 41, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 41, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id42_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 42, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 42, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 42, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id43_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 43, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 43, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 43, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id44_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 44, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 44, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 44, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id45_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 45, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 45, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 45, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id46_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 46, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 46, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 46, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id47_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 47, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 47, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 47, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id48_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 48, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 48, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 48, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id49_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 49, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 49, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 49, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id50_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 50, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 50, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 50, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id51_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 51, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 51, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 51, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id52_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 52, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 52, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 52, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id53_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 53, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 53, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 53, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id54_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 54, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 54, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 54, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id55_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 55, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 55, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 55, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id56_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 56, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 56, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 56, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id57_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 57, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 57, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 57, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id58_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 58, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 58, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 58, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id59_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 59, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 59, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 59, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id60_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 60, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 60, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 60, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id61_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 61, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 61, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 61, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id62_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 62, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 62, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 62, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id63_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 63, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 63, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 63, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id64_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 64, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 64, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 64, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id65_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 65, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 65, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 65, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id66_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 66, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 66, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 66, -1);
}

TEST(ucie_runtime_link_test, check_m0_lane_repair_id67_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 67, -1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 67, -1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(ENABLE, DISABLE, 67, -1);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id00_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 0, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 0, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 0);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id01_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 1, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 1, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 1);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id02_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 2, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 2, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 2);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id03_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 3, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 3, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 3);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id04_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 4, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 4, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 4);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id05_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 5, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 5, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 5);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id06_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 6, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 6, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 6);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id07_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 7, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 7, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 7);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id08_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 8, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 8, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 8);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id09_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 9, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 9, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 9);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id10_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 10, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 10, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 10);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id11_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 11, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 11, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 11);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id12_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 12, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 12, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 12);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id13_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 13, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 13, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 13);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id14_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 14, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 14, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 14);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id15_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 15, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 15, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 15);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id16_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 16, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 16, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 16);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id17_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 17, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 17, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 17);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id18_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 18, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 18, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 18);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id19_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 19, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 19, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 19);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id20_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 20, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 20, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 20);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id21_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 21, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 21, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 21);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id22_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 22, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 22, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 22);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id23_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 23, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 23, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 23);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id24_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 24, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 24, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 24);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id25_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 25, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 25, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 25);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id26_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 26, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 26, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 26);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id27_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 27, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 27, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 27);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id28_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 28, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 28, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 28);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id29_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 29, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 29, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 29);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id30_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 30, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 30, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 30);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id31_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 31, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 31, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 31);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id32_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 32, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 32, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 32);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id33_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 33, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 33, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 33);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id34_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 34, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 34, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 34);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id35_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 35, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 35, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 35);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id36_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 36, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 36, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 36);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id37_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 37, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 37, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 37);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id38_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 38, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 38, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 38);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id39_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 39, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 39, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 39);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id40_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 40, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 40, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 40);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id41_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 41, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 41, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 41);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id42_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 42, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 42, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 42);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id43_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 43, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 43, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 43);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id44_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 44, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 44, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 44);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id45_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 45, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 45, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 45);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id46_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 46, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 46, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 46);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id47_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 47, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 47, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 47);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id48_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 48, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 48, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 48);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id49_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 49, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 49, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 49);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id50_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 50, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 50, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 50);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id51_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 51, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 51, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 51);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id52_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 52, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 52, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 52);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id53_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 53, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 53, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 53);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id54_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 54, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 54, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 54);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id55_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 55, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 55, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 55);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id56_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 56, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 56, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 56);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id57_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 57, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 57, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 57);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id58_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 58, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 58, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 58);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id59_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 59, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 59, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 59);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id60_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 60, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 60, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 60);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id61_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 61, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 61, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 61);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id62_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 62, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 62, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 62);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id63_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 63, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 63, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 63);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id64_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 64, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 64, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 64);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id65_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 65, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 65, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 65);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id66_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 66, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 66, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 66);
}

TEST(ucie_runtime_link_test, check_m1_lane_repair_id67_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(DISABLE, ENABLE, -1, 67, DISABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(DISABLE, ENABLE, -1, 67, DISABLE));

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_link_retraining());
	_check_repair_status(DISABLE, ENABLE, -1, 67);
}

IGNORE_TEST(ucie_runtime_link_test, check_m0_lane_repair_id00_inject_stuck_at_fault_by_runtime_link_test)
{
	_set_mock_for_runtime_link_test(ENABLE, DISABLE, 0, 0, ENABLE);
	TEST_ASSERT_EQUAL(RL_OK, do_runtime_link_test(ENABLE, DISABLE, 0, 0, ENABLE));
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_link_retraining());
	//_check_repair_inject_stuck_at_fault_status(ENABLE, DISABLE, 0, 0, ENABLE);
}

TEST_GROUP_RUNNER(ucie_runtime_link_test_except_only_for_mock)
{
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id00_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id01_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id02_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id03_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id04_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id05_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id06_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id07_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id08_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id09_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id10_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id11_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id12_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id13_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id14_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id15_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id16_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id17_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id18_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id19_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id20_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id21_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id22_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id23_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id24_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id25_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id26_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id27_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id28_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id29_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id30_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id31_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id32_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id33_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id34_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id35_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id36_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id37_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id38_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id39_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id40_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id41_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id42_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id43_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id44_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id45_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id46_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id47_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id48_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id49_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id50_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id51_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id52_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id53_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id54_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id55_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id56_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id57_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id58_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id59_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id60_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id61_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id62_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id63_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id64_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id65_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id66_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id67_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id00_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id01_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id02_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id03_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id04_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id05_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id06_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id07_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id08_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id09_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id10_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id11_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id12_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id13_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id14_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id15_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id16_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id17_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id18_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id19_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id20_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id21_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id22_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id23_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id24_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id25_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id26_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id27_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id28_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id29_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id30_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id31_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id32_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id33_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id34_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id35_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id36_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id37_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id38_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id39_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id40_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id41_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id42_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id43_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id44_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id45_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id46_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id47_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id48_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id49_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id50_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id51_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id52_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id53_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id54_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id55_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id56_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id57_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id58_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id59_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id60_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id61_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id62_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id63_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id64_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id65_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id66_by_runtime_link_test);
	RUN_TEST_CASE(ucie_runtime_link_test, check_m1_lane_repair_id67_by_runtime_link_test);

	RUN_TEST_CASE(ucie_runtime_link_test, check_m0_lane_repair_id00_inject_stuck_at_fault_by_runtime_link_test);
}

TEST_GROUP_RUNNER(ucie_runtime_link_test_only_for_mock)
{
}
