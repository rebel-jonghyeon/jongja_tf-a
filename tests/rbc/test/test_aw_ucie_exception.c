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
#include "fake_gic.h" /* TO DO. it will be replaced with interrupt test helper. */
#include "test_aw_ucie_util.h"
#include "rl_utils.h"
#include "rl_errors.h"
#include "unity_fixture.h"

#define FATAL		(1)
#define NON_FATAL	(0)

static struct aw_ucie *mmio_ptr;
static struct aw_ucie *wr_buf_ptr;
static const int32_t ucie_ss_id = UCIE_SS_V10_ID;
static int32_t (*init_bk)(int32_t, void*);
static int32_t (*link_training_bk)(void);
static int32_t (*link_retraining_bk)(void);
static char log_buf[UCIE_INTR_LOG_SIZE][UCIE_INTR_LOG_LEN] = {};

static const int ucie_ss_intr_id[] = {
	BLK_RBC_H00_UCIE_INTR_ID,
	BLK_RBC_H01_UCIE_INTR_ID,
	BLK_RBC_V00_UCIE_INTR_ID,
	BLK_RBC_V01_UCIE_INTR_ID,
	BLK_RBC_V10_UCIE_INTR_ID,
	BLK_RBC_V11_UCIE_INTR_ID,
};

TEST_GROUP(ucie_exception);

TEST_SETUP(ucie_exception)
{
	CLEAR_SNAPSHOT_ARR(reg[ucie_ss_id]);
	CLEAR_SNAPSHOT_ARR(target_ss);
	for (int i = 0; i < UCIE_INTR_LOG_SIZE; i++)
		memset(log_buf[i], 0, UCIE_INTR_LOG_LEN);

	init_bk = aw_ucie_init;
	link_training_bk = aw_ucie_link_training;
	link_retraining_bk = aw_ucie_link_retraining;
#ifdef USE_DILIGENT_PTR
	aw_ucie_init = fake_aw_ucie_init;
	aw_ucie_link_training = dummy_aw_ucie_link_training;
	link_retraining_counter = 0;
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

	aw_ucie_clear_intr_log();
}

TEST_TEAR_DOWN(ucie_exception)
{
	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);

	aw_ucie_init = init_bk;
	aw_ucie_link_training = link_training_bk;
	aw_ucie_link_retraining = link_retraining_bk;
}

TEST(ucie_exception, clear_intr_log)
{
	uint32_t log_cnt = 10;
	char log_arr[UCIE_INTR_LOG_SIZE][UCIE_INTR_LOG_LEN] = {};

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&log_cnt));
	TEST_ASSERT_EQUAL(0, log_cnt);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_arr(log_arr, UCIE_INTR_LOG_SIZE));
	for (int i = 0; i < UCIE_INTR_LOG_SIZE; i++) {
		TEST_ASSERT_EQUAL_STRING("", log_arr[i]);
	}
}

static void _set_link_evnet_noti(const bool link_event_intr_en, const bool auto_bw_changed_intr_en)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl *nf_ctrl =
		&wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	*wr_buf_ptr = *mmio_ptr;
	nf_ctrl->link_status_change_ucie_link_event_intr_en = link_event_intr_en;
	nf_ctrl->hw_autonomous_bw_change_ucie_link_event_intr_en = auto_bw_changed_intr_en;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_link_event_noti(link_event_intr_en, auto_bw_changed_intr_en));
}

static void _set_mock_for_link_event_handling(void)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status *link_stat =
		&mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status;

	/* on -> off */
	link_stat->lstatus_link_status_change = ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	*wr_buf_ptr = *mmio_ptr;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	link_stat->lstatus_link_status_change = DISABLE; /* Write clear */

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump hdr log2 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump err log */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	/* off -> on */
	link_stat->lstatus_link_status_change = ENABLE;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	*wr_buf_ptr = *mmio_ptr;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	link_stat->lstatus_link_status_change = DISABLE; /* Write clear */

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump hdr log2 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump err log */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
}

TEST(ucie_exception, assert_intr_by_link_status_changed_set)
{
	uint32_t intr_log_cnt = 0;

	_set_link_evnet_noti(ENABLE, DISABLE);

	_set_mock_for_link_event_handling();
	aw_ucie_link_training();
#ifdef USE_DILIGENT_PTR
	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);
	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);
#endif /* USE_DILIGENT_PTR */
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&intr_log_cnt));
	TEST_ASSERT_EQUAL(2, intr_log_cnt);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_arr(log_buf, intr_log_cnt));
	TEST_ASSERT_EQUAL_STRING("Link Status changed.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("Link Status changed.", log_buf[1]);
}

TEST(ucie_exception, not_assert_intr_by_link_status_changed_cleared)
{
	uint32_t intr_log_cnt = 0;

	_set_link_evnet_noti(DISABLE, DISABLE);

	memcpy(log_buf[0], "aa", 3);
	memcpy(log_buf[1], "bb", 3);
	aw_ucie_link_training();

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&intr_log_cnt));
	TEST_ASSERT_EQUAL(0, intr_log_cnt);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_arr(log_buf, intr_log_cnt));
	TEST_ASSERT_EQUAL_STRING("aa", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("bb", log_buf[1]);
}

TEST(ucie_exception, overflow_intr_log)
{
	uint32_t log_cnt = 0;

	PAUSE(target_ss);
	aw_ucie_set_link_event_noti(ENABLE, DISABLE);
	aw_ucie_link_training();
#ifdef USE_DILIGENT_PTR
	RESUME(target_ss);
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl.link_status_change_ucie_link_event_intr_en = ENABLE;
	_set_mock_for_link_event_handling();
	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);
	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);
	_set_link_evnet_noti(DISABLE, DISABLE); /* for clear expected write */
	PAUSE(target_ss);
#endif /* USE_DILIGENT_PTR */
	aw_ucie_set_link_event_noti(DISABLE, DISABLE);

	for (int i = 2; i < UCIE_INTR_LOG_SIZE; i++)
		call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&log_cnt));
	TEST_ASSERT_EQUAL(UCIE_INTR_LOG_SIZE, log_cnt);

	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&log_cnt));
	TEST_ASSERT_EQUAL(UCIE_INTR_LOG_SIZE, log_cnt);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_arr(log_buf, UCIE_INTR_LOG_SIZE));
	TEST_ASSERT_EQUAL_STRING("Link Status changed.", log_buf[0]);
	for (int i = 1; i < UCIE_INTR_LOG_SIZE; i++) {
		TEST_ASSERT_EQUAL_STRING("Unknown interrupt source.", log_buf[i]);
	}
	RESUME(target_ss);
}

static void _set_mock_checking_hdr_log(uint32_t hdr_log[3])
{
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_hdr_log1_1.val = hdr_log[0];
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_hdr_log1_2.val = hdr_log[1];
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_hdr_log2.val = hdr_log[2];
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
}

static void _set_mock_checking_err_log(uint32_t err_log[4][2])
{
	mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_err_log0.val = err_log[0][0];
	mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_err_log1.val = err_log[0][1];

	mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_err_log0.val = err_log[1][0];
	mmio_ptr->phy_d2d_reg_reg_phy_d2d_m1_err_log1.val = err_log[1][1];

	mmio_ptr->phy_d2d_reg_reg_phy_d2d_m2_err_log0.val = err_log[2][0];
	mmio_ptr->phy_d2d_reg_reg_phy_d2d_m2_err_log1.val = err_log[2][1];

	mmio_ptr->phy_d2d_reg_reg_phy_d2d_m3_err_log0.val = err_log[3][0];
	mmio_ptr->phy_d2d_reg_reg_phy_d2d_m3_err_log1.val = err_log[3][1];

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
}

TEST(ucie_exception, check_log_dump)
{
	uint32_t intr_log_cnt = 0;
	const uint32_t SPCF_DATA = 0x12345678;
	uint32_t hdr_log[3] = {SPCF_DATA, ~SPCF_DATA, SPCF_DATA};
	uint32_t err_log[4][2] = {
		{SPCF_DATA, ~SPCF_DATA}, {SPCF_DATA, ~SPCF_DATA},
		{SPCF_DATA, ~SPCF_DATA}, {SPCF_DATA, ~SPCF_DATA}
	};
	uint32_t hdr_log2 = 0;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr); /* event noti and stat access */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	_set_mock_checking_hdr_log(hdr_log);
	_set_mock_checking_err_log(err_log);
	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);

	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_hdr_log2.val = SPCF_DATA;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_hdr_log2(&hdr_log2));
	TEST_ASSERT_EQUAL(SPCF_DATA, hdr_log2);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&intr_log_cnt));
	TEST_ASSERT_EQUAL(1, intr_log_cnt);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_log_data(&hdr_log, &err_log, intr_log_cnt));
	TEST_ASSERT_EQUAL(SPCF_DATA, hdr_log[0]);
	TEST_ASSERT_EQUAL(~SPCF_DATA, hdr_log[1]);
	TEST_ASSERT_EQUAL(SPCF_DATA, hdr_log[2]);

	TEST_ASSERT_EQUAL(SPCF_DATA, err_log[0][0]);
	TEST_ASSERT_EQUAL(~SPCF_DATA, err_log[0][1]);
	TEST_ASSERT_EQUAL(SPCF_DATA, err_log[1][0]);
	TEST_ASSERT_EQUAL(~SPCF_DATA, err_log[1][1]);
	TEST_ASSERT_EQUAL(SPCF_DATA, err_log[2][0]);
	TEST_ASSERT_EQUAL(~SPCF_DATA, err_log[2][1]);
	TEST_ASSERT_EQUAL(SPCF_DATA, err_log[3][0]);
	TEST_ASSERT_EQUAL(~SPCF_DATA, err_log[3][1]);
}

static void _set_link_error_noti(const bool corr_err_intr_en,
								 const bool non_fatal_uncorr_err_intr_en, const bool fatal_uncorr_err_intr_en)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl *nf_ctrl =
		&wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	*wr_buf_ptr = *mmio_ptr;
	nf_ctrl->err_nf_ctrl_corr_err_ucie_link_err_intr_en = corr_err_intr_en;
	nf_ctrl->err_nf_ctrl_uncorr_non_fatal_err_ucie_link_err_intr_en = non_fatal_uncorr_err_intr_en;
	nf_ctrl->err_nf_ctrl_uncorr_fatal_err_ucie_link_err_intr_en = fatal_uncorr_err_intr_en;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	if (corr_err_intr_en)
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_corr_err_noti(DISABLE, corr_err_intr_en));
	else if (non_fatal_uncorr_err_intr_en)
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_non_fatal_uncorr_err_noti(DISABLE, non_fatal_uncorr_err_intr_en));
	else if (fatal_uncorr_err_intr_en)
		TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_fatal_uncorr_err_noti(DISABLE, fatal_uncorr_err_intr_en));
	else
		TEST_FAIL();
}

static void _set_mock_checking_noti_for_link_error_handling(const bool corr_err,
															const bool non_fatal_uncorr_err,
															const bool fatal_uncorr_err)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status *link_stat =
		&mmio_ptr->dvsec1_reg_reg_global_dvsec1_ucie_link_status;
	/* check noti control */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	/* check corr/uncorr stat and clear */
	link_stat->lstatus_ucie_link_corr_err = corr_err;
	link_stat->lstatus_ucie_link_uncorr_non_fatal_err = non_fatal_uncorr_err;
	link_stat->lstatus_ucie_link_uncorr_fatal_err = fatal_uncorr_err;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	/* Write clear */
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, mmio_ptr);
	link_stat->lstatus_ucie_link_corr_err = DISABLE;
	link_stat->lstatus_ucie_link_uncorr_non_fatal_err = DISABLE;
	link_stat->lstatus_ucie_link_uncorr_fatal_err = DISABLE;
}

static void _set_mock_checking_corr_mask_for_link_error_handling(const bool crc_err, const bool adap_lsm_retrain,
																 const bool corr_in_err, const bool sb_corr_err_msg,
																 const bool runtime_link_test)
{
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_mask *corr_err_mask =
		&mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_corr_err_mask;

	/* check masking */
	corr_err_mask->crc_err_detected_mask = crc_err;
	corr_err_mask->adpt_lsm_trns_to_retrain_mask = adap_lsm_retrain;
	corr_err_mask->corr_internal_err_mask = corr_in_err;
	corr_err_mask->device_corr_err_msg_recv_mask = sb_corr_err_msg;
	corr_err_mask->runtime_link_tstng_parity_err_mask = runtime_link_test;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
}

static void _set_mock_checking_corr_stat_for_link_error_handling(const bool crc_err, const bool adap_lsm_retrain,
																 const bool corr_in_err, const bool sb_corr_err_msg,
																 const bool runtime_link_test)
{
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat *corr_err_stat =
		&mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_corr_err_stat;

	corr_err_stat->crc_err_detected = crc_err;
	corr_err_stat->adpt_lsm_trans_retrain = adap_lsm_retrain;
	corr_err_stat->corr_internal_err = corr_in_err;
	corr_err_stat->sb_corr_err_msg_rcvd = sb_corr_err_msg;
	corr_err_stat->run_time_link_testing_parity_err = runtime_link_test;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	if (crc_err || adap_lsm_retrain || corr_in_err || sb_corr_err_msg || runtime_link_test)
		PUSH_EXPECT_WRITE(target_ss, mmio_ptr, mmio_ptr); /* Write clear */
	corr_err_stat->crc_err_detected = DISABLE;
	corr_err_stat->adpt_lsm_trans_retrain = DISABLE;
	corr_err_stat->corr_internal_err = DISABLE;
	corr_err_stat->sb_corr_err_msg_rcvd = DISABLE;
	corr_err_stat->run_time_link_testing_parity_err = DISABLE;
}

/**
 * AW UCIe SS does not support D2D Comp, So Test Flit can not be used.
 * This test cannot check the result automatically,
 * and the masking result of chiplet 1 must be checked manually.
 */
IGNORE_TEST(ucie_exception, unmasking_corr_err_intr_from_crc_err)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl err_noti = {.val = 0};
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_mask corr_err_mask = {.val = 0};
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat corr_err_stat = {.val = 0};
	const uint32_t CORR_ERR_STAT_OFFSET = 0x1C;
	const uint32_t CORR_ERR_MASK_OFFSET = 0x20;
	const uint32_t LIKK_N_ERR_NOTI_OFFSET = 0x18;
	const uint32_t INFORM6_OFFSET = 0x848;

	/* clear corr err stat */
	aw_ucie_sb_mem_rd32(UCIE_SB_MEM_REG_LOCATOR_0, CORR_ERR_STAT_OFFSET, &corr_err_stat.val);
	corr_err_stat.crc_err_detected = 0x1;
	aw_ucie_sb_mem_wr32(UCIE_SB_MEM_REG_LOCATOR_0, CORR_ERR_STAT_OFFSET, &corr_err_stat.val);

	/* unmasking crc err */
	aw_ucie_sb_mem_rd32(UCIE_SB_MEM_REG_LOCATOR_0, CORR_ERR_MASK_OFFSET, &corr_err_mask.val);
	corr_err_mask.crc_err_detected_mask = 0x0;
	aw_ucie_sb_mem_wr32(UCIE_SB_MEM_REG_LOCATOR_0, CORR_ERR_MASK_OFFSET, &corr_err_mask.val);

	/* enable corr err intr */
	aw_ucie_sb_config_rd32(UCIE_SB_MEM_REG_LOCATOR_0, LIKK_N_ERR_NOTI_OFFSET, &err_noti.val);
	err_noti.err_nf_ctrl_corr_err_ucie_link_err_intr_en = 0x1;
	aw_ucie_sb_config_wr32(UCIE_SB_MEM_REG_LOCATOR_0, LIKK_N_ERR_NOTI_OFFSET, &err_noti.val);

	/* enable crc err inject */
	aw_ucie_mb_crc_err_inject(CRC_ERR_INJ_1BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_1_FLIT);

	/* trigger crc err and get err result */
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {.val = 0};

	const uint32_t LIKK_STAT_OFFSET = 0x14;

	volatile uint32_t *remote_cpmu_inform6 = (volatile uint32_t *)(CHIPLET_OFFSET + CPMU + INFORM6_OFFSET);

	while (!link_stat.lstatus_ucie_link_corr_err) {
		*remote_cpmu_inform6++;
		aw_ucie_sb_config_rd32(UCIE_SB_MEM_REG_LOCATOR_0, LIKK_STAT_OFFSET, &link_stat.val);
	}
	aw_ucie_sb_mem_rd32(UCIE_SB_MEM_REG_LOCATOR_0, CORR_ERR_STAT_OFFSET, &corr_err_stat.val);
	TEST_ASSERT_EQUAL(0x1, corr_err_stat.crc_err_detected);

	/* disable crc err inject */
	aw_ucie_mb_crc_err_inject(CRC_ERR_INJ_DISABLE, NOT_USED_ARG);
}

/**
 * AW UCIe SS does not support D2D Comp, So Test Flit can not be used.
 * This test cannot check the result automatically,
 * and the masking result of chiplet 1 must be checked manually.
 */
IGNORE_TEST(ucie_exception, masking_corr_err_intr_from_crc_err)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl err_noti = {.val = 0};
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_mask corr_err_mask = {.val = 0};
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat corr_err_stat = {.val = 0};
	const uint32_t CORR_ERR_STAT_OFFSET = 0x1C;
	const uint32_t CORR_ERR_MASK_OFFSET = 0x20;
	const uint32_t LIKK_N_ERR_NOTI_OFFSET = 0x18;
	const uint32_t INFORM6_OFFSET = 0x848;

	/* clear corr err stat */
	aw_ucie_sb_mem_rd32(UCIE_SB_MEM_REG_LOCATOR_0, CORR_ERR_STAT_OFFSET, &corr_err_stat.val);
	corr_err_stat.crc_err_detected = 0x1;
	aw_ucie_sb_mem_wr32(UCIE_SB_MEM_REG_LOCATOR_0, CORR_ERR_STAT_OFFSET, &corr_err_stat.val);

	/* masking crc err */
	aw_ucie_sb_mem_rd32(UCIE_SB_MEM_REG_LOCATOR_0, CORR_ERR_MASK_OFFSET, &corr_err_mask.val);
	corr_err_mask.crc_err_detected_mask = 0x1;
	aw_ucie_sb_mem_wr32(UCIE_SB_MEM_REG_LOCATOR_0, CORR_ERR_MASK_OFFSET, &corr_err_mask.val);

	/* enable corr err intr */
	aw_ucie_sb_config_rd32(UCIE_SB_MEM_REG_LOCATOR_0, LIKK_N_ERR_NOTI_OFFSET, &err_noti.val);
	err_noti.err_nf_ctrl_corr_err_ucie_link_err_intr_en = 0x1;
	aw_ucie_sb_config_wr32(UCIE_SB_MEM_REG_LOCATOR_0, LIKK_N_ERR_NOTI_OFFSET, &err_noti.val);

	/* enable crc err inject */
	aw_ucie_mb_crc_err_inject(CRC_ERR_INJ_1BIT_INVERTED, CRC_ERR_INJ_COUNT_PER_1_FLIT);

	/* trigger crc err and get err result */
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat = {.val = 0};
	const uint32_t LIKK_STAT_OFFSET = 0x14;
	volatile uint32_t *remote_cpmu_inform6 = (volatile uint32_t *)(CHIPLET_OFFSET + CPMU + INFORM6_OFFSET);

	while (!link_stat.lstatus_ucie_link_corr_err) {
		*remote_cpmu_inform6++;
		aw_ucie_sb_config_rd32(UCIE_SB_MEM_REG_LOCATOR_0, LIKK_STAT_OFFSET, &link_stat.val);
	}
	aw_ucie_sb_mem_rd32(UCIE_SB_MEM_REG_LOCATOR_0, CORR_ERR_STAT_OFFSET, &corr_err_stat.val);
	TEST_ASSERT_EQUAL(0x1, corr_err_stat.crc_err_detected);

	/* disable crc err inject */
	aw_ucie_mb_crc_err_inject(CRC_ERR_INJ_DISABLE, NOT_USED_ARG);
}

static void _assert_intr_corr_err(const bool crc_err, const bool adap_lsm_retrain,
								  const bool corr_in_err, const bool sb_corr_err_msg,
								  const bool runtime_link_test)
{
	uint32_t intr_log_cnt = 0;
#ifdef USE_DILIGENT_PTR
	uint32_t before_link_retraining_cnt = link_retraining_counter;
#endif /* USE_DILIGENT_PTR */

	_set_link_error_noti(ENABLE, DISABLE, DISABLE);

	_set_mock_checking_noti_for_link_error_handling(ENABLE, DISABLE, DISABLE);
	_set_mock_checking_corr_mask_for_link_error_handling(!crc_err, !adap_lsm_retrain,
														 !corr_in_err, !sb_corr_err_msg, !runtime_link_test);
	_set_mock_checking_corr_stat_for_link_error_handling(crc_err, adap_lsm_retrain,
														 corr_in_err, sb_corr_err_msg, runtime_link_test);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump hdr log2 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump err log */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&intr_log_cnt));
	TEST_ASSERT_EQUAL(crc_err + adap_lsm_retrain + corr_in_err + sb_corr_err_msg + runtime_link_test, intr_log_cnt);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_arr(log_buf, intr_log_cnt));
#ifdef USE_DILIGENT_PTR
	TEST_ASSERT_EQUAL(before_link_retraining_cnt + 1, link_retraining_counter);
#endif /* USE_DILIGENT_PTR */
}

TEST(ucie_exception, assert_intr_corr_err_by_crc_err_detecting)
{
	_assert_intr_corr_err(ENABLE, DISABLE, DISABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("CRC Error Detected.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_corr_err_by_adap_lsm_retrain)
{
	_assert_intr_corr_err(DISABLE, ENABLE, DISABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Adapter LSM transition to Retrain.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_corr_err_by_internal_err)
{
	_assert_intr_corr_err(DISABLE, DISABLE, ENABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Correctable Internal Error.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_corr_err_by_sb_corr_err_msg)
{
	_assert_intr_corr_err(DISABLE, DISABLE, DISABLE, ENABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Sideband Correctable Error Message received.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_corr_err_by_runtime_link_test)
{
	_assert_intr_corr_err(DISABLE, DISABLE, DISABLE, DISABLE, ENABLE);
	TEST_ASSERT_EQUAL_STRING("Runtime Link Testing Parity Error.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, invalid_intr_corr_error_with_none_of_reason)
{
	uint32_t intr_log_cnt = 0;
#ifdef USE_DILIGENT_PTR
	uint32_t before_link_retraining_cnt = link_retraining_counter;
#endif /* USE_DILIGENT_PTR */

	_set_link_error_noti(ENABLE, DISABLE, DISABLE);

	_set_mock_checking_noti_for_link_error_handling(ENABLE, DISABLE, DISABLE);
	_set_mock_checking_corr_mask_for_link_error_handling(DISABLE, DISABLE, DISABLE, DISABLE, DISABLE);
	_set_mock_checking_corr_stat_for_link_error_handling(DISABLE, DISABLE, DISABLE, DISABLE, DISABLE);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump hdr log*/
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump err log*/
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&intr_log_cnt));
	TEST_ASSERT_EQUAL(1, intr_log_cnt);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_arr(log_buf, intr_log_cnt));
	TEST_ASSERT_EQUAL_STRING("Corr err asserted but all status are clean.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
#ifdef USE_DILIGENT_PTR
	TEST_ASSERT_EQUAL(before_link_retraining_cnt + 1, link_retraining_counter);
#endif /* USE_DILIGENT_PTR */
}

static void _set_uncorr_fatal_severity_for_link_error_handling(const bool adap_to, const bool rcv_of,
															   const bool internal, const bool sb_fatal,
															   const bool sb_nfatal, const bool inv_param)
{
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity *uncorr_err_severity =
		&mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity;

	/* set uncorr err serverity */
	uncorr_err_severity->adpt_timeout_severity = adap_to;
	uncorr_err_severity->rcvr_overflow_severity = rcv_of;
	uncorr_err_severity->internal_err_severity = internal;
	uncorr_err_severity->sb_fatal_err_msg_rcvd_severity = sb_fatal;
	uncorr_err_severity->sb_nonfatal_err_msg_rcvd_severity = sb_nfatal;
	uncorr_err_severity->invld_param_exchange_severity = inv_param;
	*wr_buf_ptr = *mmio_ptr;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_uncorr_err_severity(adap_to, rcv_of, internal,
															 sb_fatal, sb_nfatal, inv_param));
}

static void _set_mock_checking_uncorr_mask_for_link_error_handling(const bool adap_to, const bool rcv_of,
																   const bool internal, const bool sb_fatal,
																   const bool sb_nfatal, const bool inv_param)
{
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask *uncorr_err_mask =
		&mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask;

	/* check masking */
	uncorr_err_mask->adpt_timeout_mask = adap_to;
	uncorr_err_mask->rcvr_overflow_mask = rcv_of;
	uncorr_err_mask->internal_err_mask = internal;
	uncorr_err_mask->sb_fatal_err_msg_rcvd_mask = sb_fatal;
	uncorr_err_mask->sb_nonfatal_err_msg_rcvd_mask = sb_nfatal;
	uncorr_err_mask->invld_param_exchange_mask = inv_param;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
}

static void _set_mock_checking_uncorr_stat_for_link_error_handling(const bool adap_to, const bool rcv_of,
																   const bool internal, const bool sb_fatal,
																   const bool sb_nfatal, const bool inv_param)
{
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat *uncorr_err_stat =
		&mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat;

	/* check stat */
	uncorr_err_stat->adpt_timeout = adap_to;
	uncorr_err_stat->rcvr_overflow = rcv_of;
	uncorr_err_stat->internal_err = internal;
	uncorr_err_stat->sb_fatal_err_msg_rcvd = sb_fatal;
	uncorr_err_stat->sb_nonfatal_err_msg_rcvd = sb_nfatal;
	uncorr_err_stat->invld_param_exchange = inv_param;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, mmio_ptr);
	uncorr_err_stat->adpt_timeout = DISABLE; /* Write Clear */
	uncorr_err_stat->rcvr_overflow = DISABLE;
	uncorr_err_stat->internal_err = DISABLE;
	uncorr_err_stat->sb_fatal_err_msg_rcvd = DISABLE;
	uncorr_err_stat->sb_nonfatal_err_msg_rcvd = DISABLE;
	uncorr_err_stat->invld_param_exchange = DISABLE;
}

static void _assert_intr_non_fatal_uncorr_err(const bool adap_to, const bool rcv_of,
											  const bool internal, const bool sb_fatal,
											  const bool sb_nfatal, const bool inv_param)
{
	uint32_t intr_log_cnt = 0;
#ifdef USE_DILIGENT_PTR
	uint32_t before_link_retraining_cnt = link_retraining_counter;
#endif /* USE_DILIGENT_PTR */

	_set_link_error_noti(DISABLE, ENABLE, DISABLE);
	_set_uncorr_fatal_severity_for_link_error_handling(NON_FATAL, NON_FATAL, NON_FATAL,
													   NON_FATAL, NON_FATAL, NON_FATAL);

	_set_mock_checking_noti_for_link_error_handling(DISABLE, ENABLE, DISABLE);
	_set_mock_checking_uncorr_mask_for_link_error_handling(!adap_to, !rcv_of, !internal,
														   !sb_fatal, !sb_nfatal, !inv_param);
	_set_mock_checking_uncorr_stat_for_link_error_handling(adap_to, rcv_of, internal, sb_fatal, sb_nfatal, inv_param);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump hdr log2 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump err log */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&intr_log_cnt));
	TEST_ASSERT_EQUAL(adap_to + rcv_of + internal + sb_fatal + sb_nfatal + inv_param, intr_log_cnt);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_arr(log_buf, intr_log_cnt));
#ifdef USE_DILIGENT_PTR
	TEST_ASSERT_EQUAL(before_link_retraining_cnt + 1, link_retraining_counter);
#endif /* USE_DILIGENT_PTR */
}

TEST(ucie_exception, assert_intr_non_fatal_uncorr_err_by_adap_timeout)
{
	_assert_intr_non_fatal_uncorr_err(ENABLE, DISABLE, DISABLE, DISABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Adapter Timeout.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_non_fatal_uncorr_err_by_recv_overflow)
{
	_assert_intr_non_fatal_uncorr_err(DISABLE, ENABLE, DISABLE, DISABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Receiver Overflow.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_non_fatal_uncorr_err_by_internal_error)
{
	_assert_intr_non_fatal_uncorr_err(DISABLE, DISABLE, ENABLE, DISABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Internal Error.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_non_fatal_uncorr_err_by_sb_fatal_err_msg)
{
	_assert_intr_non_fatal_uncorr_err(DISABLE, DISABLE, DISABLE, ENABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Sideband Fatal Error Message received.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_non_fatal_uncorr_err_by_sb_non_fatal_err_msg)
{
	_assert_intr_non_fatal_uncorr_err(DISABLE, DISABLE, DISABLE, DISABLE, ENABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Sideband Non-Fatal Error Message received.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_non_fatal_uncorr_err_from_invalid_param_exchange)
{
	_assert_intr_non_fatal_uncorr_err(DISABLE, DISABLE, DISABLE, DISABLE, DISABLE, ENABLE);
	TEST_ASSERT_EQUAL_STRING("Invalid Parameter Exchange.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, invalid_intr_non_fatal_uncorr_error_with_none_of_reason)
{
	uint32_t intr_log_cnt = 0;
#ifdef USE_DILIGENT_PTR
	uint32_t before_link_retraining_cnt = link_retraining_counter;
#endif /* USE_DILIGENT_PTR */

	_set_link_error_noti(DISABLE, ENABLE, DISABLE);
	_set_uncorr_fatal_severity_for_link_error_handling(NON_FATAL, NON_FATAL, NON_FATAL,
													   NON_FATAL, NON_FATAL, NON_FATAL);

	_set_mock_checking_noti_for_link_error_handling(DISABLE, ENABLE, DISABLE);
	_set_mock_checking_uncorr_mask_for_link_error_handling(DISABLE, DISABLE, DISABLE, DISABLE, DISABLE, DISABLE);
	_set_mock_checking_uncorr_stat_for_link_error_handling(DISABLE, DISABLE, DISABLE, DISABLE, DISABLE, DISABLE);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr); /* dump hdr log */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr); /* dump err log */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&intr_log_cnt));
	TEST_ASSERT_EQUAL(1, intr_log_cnt);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_arr(log_buf, intr_log_cnt));
	TEST_ASSERT_EQUAL_STRING("Non-fatal Uncorr err asserted but all status are clean.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
#ifdef USE_DILIGENT_PTR
	TEST_ASSERT_EQUAL(before_link_retraining_cnt + 1, link_retraining_counter);
#endif /* USE_DILIGENT_PTR */
}

static void _assert_intr_fatal_uncorr_err(const bool adap_to, const bool rcv_of,
										  const bool internal, const bool sb_fatal,
										  const bool sb_nfatal, const bool inv_param)
{
	uint32_t intr_log_cnt = 0;
#ifdef USE_DILIGENT_PTR
	uint32_t before_link_retraining_cnt = link_retraining_counter;
#endif /* USE_DILIGENT_PTR */

	_set_link_error_noti(DISABLE, DISABLE, ENABLE);
	_set_uncorr_fatal_severity_for_link_error_handling(FATAL, FATAL, FATAL, FATAL, FATAL, FATAL);

	_set_mock_checking_noti_for_link_error_handling(DISABLE, DISABLE, ENABLE);
	_set_mock_checking_uncorr_mask_for_link_error_handling(!adap_to, !rcv_of, !internal,
														   !sb_fatal, !sb_nfatal, !inv_param);
	_set_mock_checking_uncorr_stat_for_link_error_handling(adap_to, rcv_of, internal, sb_fatal, sb_nfatal, inv_param);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump hdr log2 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dump err log */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&intr_log_cnt));
	TEST_ASSERT_EQUAL(adap_to + rcv_of + internal + sb_fatal + sb_nfatal + inv_param, intr_log_cnt);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_arr(log_buf, intr_log_cnt));
#ifdef USE_DILIGENT_PTR
	TEST_ASSERT_EQUAL(before_link_retraining_cnt + 1, link_retraining_counter);
#endif /* USE_DILIGENT_PTR */
}

TEST(ucie_exception, assert_intr_fatal_uncorr_err_by_adap_timeout)
{
	_assert_intr_fatal_uncorr_err(ENABLE, DISABLE, DISABLE, DISABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Adapter Timeout.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_fatal_uncorr_err_by_recv_overflow)
{
	_assert_intr_fatal_uncorr_err(DISABLE, ENABLE, DISABLE, DISABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Receiver Overflow.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_fatal_uncorr_err_by_internal_error)
{
	_assert_intr_fatal_uncorr_err(DISABLE, DISABLE, ENABLE, DISABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Internal Error.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_fatal_uncorr_err_by_sb_fatal_err_msg)
{
	_assert_intr_fatal_uncorr_err(DISABLE, DISABLE, DISABLE, ENABLE, DISABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Sideband Fatal Error Message received.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_fatal_uncorr_err_by_sb_non_fatal_err_msg)
{
	_assert_intr_non_fatal_uncorr_err(DISABLE, DISABLE, DISABLE, DISABLE, ENABLE, DISABLE);
	TEST_ASSERT_EQUAL_STRING("Sideband Non-Fatal Error Message received.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, assert_intr_fatal_uncorr_err_from_invalid_param_exchange)
{
	_assert_intr_fatal_uncorr_err(DISABLE, DISABLE, DISABLE, DISABLE, DISABLE, ENABLE);
	TEST_ASSERT_EQUAL_STRING("Invalid Parameter Exchange.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
}

TEST(ucie_exception, invalid_intr_fatal_uncorr_error_with_none_of_reason)
{
	uint32_t intr_log_cnt = 0;
#ifdef USE_DILIGENT_PTR
	uint32_t before_link_retraining_cnt = link_retraining_counter;
#endif /* USE_DILIGENT_PTR */

	_set_link_error_noti(DISABLE, DISABLE, ENABLE);
	_set_uncorr_fatal_severity_for_link_error_handling(FATAL, FATAL, FATAL, FATAL, FATAL, FATAL);

	_set_mock_checking_noti_for_link_error_handling(DISABLE, DISABLE, ENABLE);
	_set_mock_checking_uncorr_mask_for_link_error_handling(DISABLE, DISABLE, DISABLE, DISABLE, DISABLE, DISABLE);
	_set_mock_checking_uncorr_stat_for_link_error_handling(DISABLE, DISABLE, DISABLE, DISABLE, DISABLE, DISABLE);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr); /* dump hdr log */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr); /* dump err log */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	call_interrupt_handler(ucie_ss_intr_id[ucie_ss_id]);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_count(&intr_log_cnt));
	TEST_ASSERT_EQUAL(1, intr_log_cnt);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_intr_log_arr(log_buf, intr_log_cnt));
	TEST_ASSERT_EQUAL_STRING("Fatal Uncorr err asserted but all status are clean.", log_buf[0]);
	TEST_ASSERT_EQUAL_STRING("", log_buf[1]);
#ifdef USE_DILIGENT_PTR
	TEST_ASSERT_EQUAL(before_link_retraining_cnt + 1, link_retraining_counter);
#endif /* USE_DILIGENT_PTR */
}

TEST_GROUP_RUNNER(ucie_exception_except_only_for_mock)
{
	RUN_TEST_CASE(ucie_exception, clear_intr_log);
	RUN_TEST_CASE(ucie_exception, assert_intr_by_link_status_changed_set);
	RUN_TEST_CASE(ucie_exception, not_assert_intr_by_link_status_changed_cleared);
	RUN_TEST_CASE(ucie_exception, overflow_intr_log);
	RUN_TEST_CASE(ucie_exception, unmasking_corr_err_intr_from_crc_err);
	RUN_TEST_CASE(ucie_exception, masking_corr_err_intr_from_crc_err);
}

TEST_GROUP_RUNNER(ucie_exception_only_for_mock)
{
	RUN_TEST_CASE(ucie_exception, check_log_dump);

	RUN_TEST_CASE(ucie_exception, assert_intr_corr_err_by_crc_err_detecting);
	RUN_TEST_CASE(ucie_exception, assert_intr_corr_err_by_adap_lsm_retrain);
	RUN_TEST_CASE(ucie_exception, assert_intr_corr_err_by_internal_err);
	RUN_TEST_CASE(ucie_exception, assert_intr_corr_err_by_sb_corr_err_msg);
	RUN_TEST_CASE(ucie_exception, assert_intr_corr_err_by_runtime_link_test);
	RUN_TEST_CASE(ucie_exception, invalid_intr_corr_error_with_none_of_reason);

	RUN_TEST_CASE(ucie_exception, assert_intr_non_fatal_uncorr_err_by_adap_timeout);
	RUN_TEST_CASE(ucie_exception, assert_intr_non_fatal_uncorr_err_by_recv_overflow);
	RUN_TEST_CASE(ucie_exception, assert_intr_non_fatal_uncorr_err_by_internal_error);
	RUN_TEST_CASE(ucie_exception, assert_intr_non_fatal_uncorr_err_by_sb_fatal_err_msg);
	RUN_TEST_CASE(ucie_exception, assert_intr_non_fatal_uncorr_err_by_sb_non_fatal_err_msg);
	RUN_TEST_CASE(ucie_exception, assert_intr_non_fatal_uncorr_err_from_invalid_param_exchange);
	RUN_TEST_CASE(ucie_exception, invalid_intr_non_fatal_uncorr_error_with_none_of_reason);

	RUN_TEST_CASE(ucie_exception, assert_intr_fatal_uncorr_err_by_adap_timeout);
	RUN_TEST_CASE(ucie_exception, assert_intr_fatal_uncorr_err_by_recv_overflow);
	RUN_TEST_CASE(ucie_exception, assert_intr_fatal_uncorr_err_by_internal_error);
	RUN_TEST_CASE(ucie_exception, assert_intr_fatal_uncorr_err_by_sb_fatal_err_msg);
	RUN_TEST_CASE(ucie_exception, assert_intr_fatal_uncorr_err_by_sb_non_fatal_err_msg);
	RUN_TEST_CASE(ucie_exception, assert_intr_fatal_uncorr_err_from_invalid_param_exchange);
	RUN_TEST_CASE(ucie_exception, invalid_intr_fatal_uncorr_error_with_none_of_reason);
}
