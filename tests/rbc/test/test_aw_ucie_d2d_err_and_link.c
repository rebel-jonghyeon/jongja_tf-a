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
static int32_t (*sb_mem_wr32_bk)(const uint32_t, const uint32_t, uint32_t *const);
static int32_t (*mb_inject_test_flit_bk)(const uint32_t, const uint32_t,
										 const uint32_t, const uint32_t,
										 const uint32_t, const uint32_t);

TEST_GROUP(ucie_d2d_runtime_link_test);
TEST_GROUP(ucie_d2d_crc_err_injection);

static void _err_and_link_test_setup(void)
{
	CLEAR_SNAPSHOT_ARR(reg[ucie_ss_id]);
	CLEAR_SNAPSHOT_ARR(target_ss);

	link_training_bk = aw_ucie_link_training;
	link_retraining_bk = aw_ucie_link_retraining;
	sb_mem_rd32_bk = aw_ucie_sb_mem_rd32;
	sb_mem_wr32_bk = aw_ucie_sb_mem_wr32;
	mb_inject_test_flit_bk = aw_ucie_mb_inject_test_flit;

#ifdef USE_DILIGENT_PTR
	aw_ucie_link_training = dummy_aw_ucie_link_training;
	link_retraining_counter = 0;
	aw_ucie_link_retraining = dummy_aw_ucie_link_retraining;
	aw_ucie_sb_mem_wr32 = dummy_aw_ucie_sb_mem_wr32;
	aw_ucie_mb_inject_test_flit = dummy_aw_ucie_mb_inject_test_flit;
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

TEST_SETUP(ucie_d2d_runtime_link_test)
{
	_err_and_link_test_setup();
}

TEST_TEAR_DOWN(ucie_d2d_runtime_link_test)
{
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat corr_err_stat = {};
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl cntrl = {};

	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.runtime_link_testing_tx_en = DISABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_runtime_link_test_disable());

	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.parity_feature_nak_rcvd = ENABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	cntrl.val = wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_d2d_runtime_link_test_cntrl(cntrl.val));

	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.parity_feature_nak_rcvd = DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_runtime_link_test_cntrl(&cntrl.val));
	TEST_ASSERT_EQUAL(DISABLE, cntrl.parity_feature_nak_rcvd);

	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_corr_err_stat.run_time_link_testing_parity_err = ENABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_d2d_corr_err_status(RL_BIT(4)));

	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_corr_err_stat.run_time_link_testing_parity_err = DISABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_corr_err_status(&corr_err_stat.val));
	TEST_ASSERT_EQUAL(DISABLE, corr_err_stat.run_time_link_testing_parity_err);

	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);

	aw_ucie_link_training = link_training_bk;
	aw_ucie_link_retraining = link_retraining_bk;
	aw_ucie_sb_mem_rd32 = sb_mem_rd32_bk;
	aw_ucie_sb_mem_wr32 = sb_mem_wr32_bk;
	aw_ucie_mb_inject_test_flit = mb_inject_test_flit_bk;
}

TEST_SETUP(ucie_d2d_crc_err_injection)
{
	_err_and_link_test_setup();
}

TEST_TEAR_DOWN(ucie_d2d_crc_err_injection)
{
	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);

	aw_ucie_link_training = link_training_bk;
	aw_ucie_link_retraining = link_retraining_bk;
	aw_ucie_sb_mem_rd32 = sb_mem_rd32_bk;
	aw_ucie_sb_mem_wr32 = sb_mem_wr32_bk;
	aw_ucie_mb_inject_test_flit = mb_inject_test_flit_bk;
}

TEST(ucie_d2d_runtime_link_test, runtime_link_test_fail_due_to_invalid_parity_bytes)
{
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_mb_runtime_link_test_enable(CRC_ERR_INJ_COUNT_PER_64_FLIT + 1));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_mb_runtime_link_test_enable(-1));
}

static void _runtime_link_test(const uint32_t num_of_parity_bytes)
{
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl cntrl = {
		.remote_reg_access_th = 4
	};

#ifdef USE_DILIGENT_PTR
	aw_ucie_sb_mem_rd32 = dummy_aw_ucie_sb_mem_rd32_all_clear;
#endif /* USE_DILIGENT_PTR */

	/**
	 * set num of parity bytes and threshold.
	 * the Adapter inserts 64*N Bytes every 256*256*N Bytes of data,
	 * where N is obtained from the Error and Link Testing Control register
	 * (Field name: Number of 64 ByteInserts).
	 */
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val = cntrl.val;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	cntrl.no_of_64b_inserts = num_of_parity_bytes;
	cntrl.runtime_link_testing_tx_en = ENABLE;
	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val = cntrl.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr); // check feature Nak

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_runtime_link_test_enable(num_of_parity_bytes));

	/* insert test flits */
	aw_ucie_mb_inject_test_flit(FLIT_INJECT_MODE_CONT, NOT_USED_ARG, FLIT_INJECT_PAYLOAD_RANDOM_ALL,
								NOT_USED_ARG, NOT_USED_ARG, NOT_USED_ARG);

	/* To Do : Add delay enough to repeat several parity transactions. */

	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1.flit_tx_inj_enable = DISABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	aw_ucie_mb_inject_flit_disable();

	/* check correctable error status reg, parity log 0 reg */
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat corr_err_sts = {};

	corr_err_sts.val = 0xFFFFFFFF;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(0, 0x1C, &corr_err_sts.val));
	TEST_ASSERT_EQUAL(DISABLE, corr_err_sts.run_time_link_testing_parity_err);

	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_1 parity_log_low = {};
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_2 parity_log_high = {};

	parity_log_low.val = 0xFFFFFFFF;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(0, 0x34, &parity_log_low.val));
	TEST_ASSERT_EQUAL(0, parity_log_low.val);

	parity_log_high.val = 0xFFFFFFFF;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(0, 0x38, &parity_log_high.val));
	TEST_ASSERT_EQUAL(0, parity_log_high.val);

	parity_log_low.val = 0xFFFFFFFF;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(0, 0x3C, &parity_log_low.val));
	TEST_ASSERT_EQUAL(0, parity_log_low.val);

	parity_log_high.val = 0xFFFFFFFF;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(0, 0x40, &parity_log_high.val));
	TEST_ASSERT_EQUAL(0, parity_log_high.val);
}

TEST(ucie_d2d_runtime_link_test, runtime_link_test_fail_due_to_nak)
{
union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl cntrl = {
	.remote_reg_access_th = 4
	};

#ifdef USE_DILIGENT_PTR
	aw_ucie_sb_mem_rd32 = dummy_aw_ucie_sb_mem_rd32_all_clear;
#endif /* USE_DILIGENT_PTR */

	/**
	 * set num of parity bytes and threshold.
	 * the Adapter inserts 64*N Bytes every 256*256*N Bytes of data,
	 * where N is obtained from the Error and Link Testing Control register
	 * (Field name: Number of 64 ByteInserts).
	 */
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val = cntrl.val;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	cntrl.no_of_64b_inserts = NUM_OF_INSERTED_ONE_64BYTES;
	cntrl.runtime_link_testing_tx_en = ENABLE;
	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val = cntrl.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.parity_feature_nak_rcvd = ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr); // check feature Nak

	TEST_ASSERT_EQUAL(RL_EPERM, aw_ucie_mb_runtime_link_test_enable(NUM_OF_INSERTED_ONE_64BYTES));
}

TEST(ucie_d2d_runtime_link_test, no_err_runtime_link_test_w_one_parity_bytes)
{
	_runtime_link_test(NUM_OF_INSERTED_ONE_64BYTES);
}

TEST(ucie_d2d_runtime_link_test, no_err_runtime_link_test_w_two_parity_bytes)
{
	_runtime_link_test(NUM_OF_INSERTED_TWO_64BYTES);
}

TEST(ucie_d2d_runtime_link_test, no_err_runtime_link_test_w_three_parity_bytes)
{
	_runtime_link_test(NUM_OF_INSERTED_FOUR_64BYTES);
}

TEST(ucie_d2d_crc_err_injection, crc_injection_fail_due_to_invalid_inverted_bits)
{
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_mb_crc_err_inject(CRC_ERR_INJ_3BIT_INVERTED + 1, NOT_USED_ARG));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_mb_crc_err_inject(-1, NOT_USED_ARG));
}

TEST(ucie_d2d_crc_err_injection, crc_injection_fail_due_to_invalid_inj_count)
{
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_mb_crc_err_inject(-1, CRC_ERR_INJ_COUNT_PER_64_FLIT + 1));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_mb_crc_err_inject(-1, -1));
}

static void _crc_err_inj_test(const uint32_t inverted_bits, const uint32_t inejction_cnt)
{
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl cntrl = {};

#ifdef USE_DILIGENT_PTR
	aw_ucie_sb_mem_rd32 = dummy_aw_ucie_sb_mem_rd32_all_set;
#endif /* USE_DILIGENT_PTR */

	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val = cntrl.val;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	cntrl.crc_injection_en = inverted_bits;
	cntrl.crc_injection_count = inejction_cnt;
	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val = cntrl.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);

	cntrl.crc_injection_busy = ENABLE;
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val = cntrl.val;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_crc_err_inject(inverted_bits, inejction_cnt));

	aw_ucie_mb_inject_test_flit(FLIT_INJECT_MODE_CONT, NOT_USED_ARG, FLIT_INJECT_PAYLOAD_RANDOM_ALL,
								NOT_USED_ARG, NOT_USED_ARG, NOT_USED_ARG);

	/* To Do : Add delay enough to repeat several parity transactions. */

	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1.flit_tx_inj_enable = DISABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	aw_ucie_mb_inject_flit_disable();

	*wr_buf_ptr = *mmio_ptr;
	wr_buf_ptr->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.crc_injection_en = DISABLE;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_mb_crc_err_inject(CRC_ERR_INJ_DISABLE, NOT_USED_ARG));

	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat corr_err_sts = {};

	corr_err_sts.val = 0;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(0, 0x1C, &corr_err_sts.val));
	TEST_ASSERT_EQUAL(ENABLE, corr_err_sts.crc_err_detected);
}

TEST(ucie_d2d_crc_err_injection, no_err_crc_inject_one_bit_inverted)
{
	_crc_err_inj_test(CRC_ERR_INJ_1BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_1_FLIT);
	_crc_err_inj_test(CRC_ERR_INJ_1BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_8_FLIT);
	_crc_err_inj_test(CRC_ERR_INJ_1BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_16_FLIT);
	_crc_err_inj_test(CRC_ERR_INJ_1BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_64_FLIT);
}

TEST(ucie_d2d_crc_err_injection, no_err_crc_inject_two_bit_inverted)
{
	_crc_err_inj_test(CRC_ERR_INJ_2BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_1_FLIT);
	_crc_err_inj_test(CRC_ERR_INJ_2BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_8_FLIT);
	_crc_err_inj_test(CRC_ERR_INJ_2BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_16_FLIT);
	_crc_err_inj_test(CRC_ERR_INJ_2BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_64_FLIT);
}

TEST(ucie_d2d_crc_err_injection, no_err_crc_inject_three_bit_inverted)
{
	_crc_err_inj_test(CRC_ERR_INJ_3BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_1_FLIT);
	_crc_err_inj_test(CRC_ERR_INJ_3BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_8_FLIT);
	_crc_err_inj_test(CRC_ERR_INJ_3BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_16_FLIT);
	_crc_err_inj_test(CRC_ERR_INJ_3BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_64_FLIT);
}

TEST_GROUP_RUNNER(ucie_d2d_err_and_link_except_only_for_mock)
{
	RUN_TEST_CASE(ucie_d2d_runtime_link_test, runtime_link_test_fail_due_to_invalid_parity_bytes);
	RUN_TEST_CASE(ucie_d2d_runtime_link_test, no_err_runtime_link_test_w_one_parity_bytes);
	RUN_TEST_CASE(ucie_d2d_runtime_link_test, no_err_runtime_link_test_w_two_parity_bytes);
	RUN_TEST_CASE(ucie_d2d_runtime_link_test, no_err_runtime_link_test_w_three_parity_bytes);

	RUN_TEST_CASE(ucie_d2d_crc_err_injection, crc_injection_fail_due_to_invalid_inverted_bits);
	RUN_TEST_CASE(ucie_d2d_crc_err_injection, crc_injection_fail_due_to_invalid_inj_count);
	RUN_TEST_CASE(ucie_d2d_crc_err_injection, no_err_crc_inject_one_bit_inverted);
	RUN_TEST_CASE(ucie_d2d_crc_err_injection, no_err_crc_inject_two_bit_inverted);
	RUN_TEST_CASE(ucie_d2d_crc_err_injection, no_err_crc_inject_three_bit_inverted);
}

TEST_GROUP_RUNNER(ucie_d2d_err_and_link_only_for_mock)
{
	RUN_TEST_CASE(ucie_d2d_runtime_link_test, runtime_link_test_fail_due_to_nak);
}
