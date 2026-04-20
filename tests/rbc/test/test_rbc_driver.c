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
#include <unity_fixture.h>
#include <rbc_driver.h>
#include <rl_errors.h>
#include <cmu_rbc.h>
#include <pmu.h>
#include <mailbox.h>
#include <sysreg_rbc.h>
#include <string.h>
#ifndef USE_DILIGENT_PTR
#include <test_common.h>
#else
#include <diligent_ptr.h>
#endif
#include "aw_ucie_reg.h"
#include "aw_ucie.h"
#include "test_aw_ucie_util.h"

#define EOM_ITER_COUNT  10

static const int32_t blk_rbc_id = BLK_RBC_H00_ID;

#ifdef USE_DILIGENT_PTR
	extern struct diligent_ptr < struct cmu_rbc > cmu_rbc_reg[NUM_OF_BLK_RBC_ID];
	extern struct diligent_ptr < struct sysreg_rbc > sysreg_rbc_reg[NUM_OF_BLK_RBC_ID];

	static struct cmu_rbc stuff_cmu_rbc;
	static struct sysreg_rbc stuff_sysreg_rbc;
	static struct aw_ucie stuff_aw_ucie;

	static struct cmu_rbc *real_cmu_rbc = &stuff_cmu_rbc;
	static struct sysreg_rbc *real_sysreg_rbc = &stuff_sysreg_rbc;
	static struct aw_ucie *real_aw_ucie = &stuff_aw_ucie;
#else
	extern volatile struct cmu_rbc *cmu_rbc_reg[NUM_OF_BLK_RBC_ID];
	extern volatile struct sysreg_rbc *sysreg_rbc_reg[NUM_OF_BLK_RBC_ID];

	static const uint64_t cmu_rbc_base_addr_array[] = {
		CMU_RBC_H00_PRIVATE, CMU_RBC_H01_PRIVATE,
		CMU_RBC_V00_PRIVATE, CMU_RBC_V01_PRIVATE,
		CMU_RBC_V10_PRIVATE, CMU_RBC_V11_PRIVATE};
	static const uint64_t sysreg_rbc_base_addr_array[] = {
		SYSREG_RBC_H00_PRIVATE, SYSREG_RBC_H01_PRIVATE,
		SYSREG_RBC_V00_PRIVATE, SYSREG_RBC_V01_PRIVATE,
		SYSREG_RBC_V10_PRIVATE, SYSREG_RBC_V11_PRIVATE};
	static struct cmu_rbc *real_cmu_rbc = (struct cmu_rbc *)cmu_rbc_base_addr_array[blk_rbc_id];
	static struct sysreg_rbc *real_sysreg_rbc = (struct sysreg_rbc *)sysreg_rbc_base_addr_array[blk_rbc_id];
	static struct aw_ucie *real_aw_ucie = (struct aw_ucie *)ucie_ss_base_addr_array[blk_rbc_id];
#endif /* USE_DILIGENT_PTR */

static int32_t (*init_bk)(int32_t, void*);
static int32_t (*link_training_bk)(void);
static int32_t (*link_retraining_bk)(void);

TEST_GROUP(rbc_driver);

TEST_SETUP(rbc_driver)
{
	init_bk = aw_ucie_init;
	link_training_bk = aw_ucie_link_training;
	link_retraining_bk = aw_ucie_link_retraining;
#ifdef USE_DILIGENT_PTR
	aw_ucie_init = fake_aw_ucie_init;
	aw_ucie_link_training = dummy_aw_ucie_link_training;
	aw_ucie_link_retraining = dummy_aw_ucie_link_retraining;
#endif /* USE_DILIGENT_PTR */
	init_mmio_map(blk_rbc_id);

	TEST_ASSERT_EQUAL(RL_OK, rbc_driver_init(blk_rbc_id, real_cmu_rbc, real_sysreg_rbc, real_aw_ucie));
	TEST_ASSERT_EQUAL(RL_OK, rbc_set_target_blk_id(blk_rbc_id));

	real_map = get_aw_ucie_real_map();
}

TEST_TEAR_DOWN(rbc_driver)
{
	VERIFY(cmu_rbc_reg[blk_rbc_id]);
	VERIFY(sysreg_rbc_reg[blk_rbc_id]);

	CLEAR_SNAPSHOT_ARR(cmu_rbc_reg[blk_rbc_id]);
	CLEAR_SNAPSHOT_ARR(sysreg_rbc_reg[blk_rbc_id]);

	aw_ucie_init = init_bk;
	aw_ucie_link_training = link_training_bk;
	aw_ucie_link_retraining = link_retraining_bk;
}

TEST(rbc_driver, rbc_driver_init)
{
	TEST_ASSERT_EQUAL(RL_BADARG, rbc_driver_init(NUM_OF_BLK_RBC_ID, real_cmu_rbc, real_sysreg_rbc, real_aw_ucie));
	TEST_ASSERT_EQUAL(RL_OK, rbc_driver_init(blk_rbc_id, real_cmu_rbc, real_sysreg_rbc, real_aw_ucie));
}

TEST(rbc_driver, set_target_rbc_blk)
{
	cmu_rbc_reg[blk_rbc_id] = 0;
	sysreg_rbc_reg[blk_rbc_id] = 0;

	TEST_ASSERT_EQUAL(RL_NOTREADY, rbc_set_target_blk_id(blk_rbc_id));
	rbc_driver_init(blk_rbc_id, real_cmu_rbc, real_sysreg_rbc, real_aw_ucie);
	TEST_ASSERT_EQUAL(RL_BADARG, rbc_set_target_blk_id(NUM_OF_BLK_RBC_ID));
	TEST_ASSERT_EQUAL(RL_OK, rbc_set_target_blk_id(blk_rbc_id));
}

#ifndef USE_DILIGENT_PTR
static void _write_read_comp(uint64_t base_addr, uint64_t size)
{
	volatile uint32_t *dest_ptr = (volatile uint32_t *)base_addr;
	uint32_t offset = 0;
	const uint32_t DATA = 0xabcd1234;

	memset((void *)base_addr, 0, size);

	while (offset < size) {
		dest_ptr[offset++] = DATA;
		if (*dest_ptr != DATA) {
			printf("[base 0x%lx] offset : 0x%x fail\n", base_addr, offset);
			while (1) {
			}
		}
	}
}

static void _send_mailbox(uint32_t chiplet_id, uint32_t cmd)
{
	ipm_samsung_write(IDX_MAILBOX_PERI0_M7_CPU0, chiplet_id, &cmd, TEST_CMD_SIZE, TEST_BUF);
	ipm_samsung_send(IDX_MAILBOX_PERI0_M7_CPU0, chiplet_id, TEST_CHANNEL, CPU0);
}

static void _lp_entry_chiplet_1_rbcv00_direct(uint32_t lp_mode)
{
	/* In order to satisfy the 1us interval,
	 * it is coded in a way that minimizes overhead.
	 */
	const uint32_t APMW_BIT_OFFSET = 20;
	uint32_t lp_mode_val = (lp_mode - 1) << APMW_BIT_OFFSET;
	uint32_t lp_mode_mask = ~(1 << APMW_BIT_OFFSET);

	*(volatile uint32_t *)(0x3ff504000c) = ((*(volatile uint32_t *)0x3ff504000c) & lp_mode_mask) | lp_mode_val;
	*(volatile uint32_t *)(0x3ff501025c) = 1;
	*(volatile uint32_t *)(0x3ff501025c) = 0;
}

TEST(rbc_driver, l1_rbcv11_w_chiplet1_rbcv00)
{
	const uint32_t remote_chiplet_id = 1;
	const uint32_t LP_MODE_L1 = 1;

	_send_mailbox(remote_chiplet_id, RBC_V00_INIT_TEST);

	_write_read_comp(0x2040000000, 0x100);

	/* LPI Entry */
	pmu_rbc_lpi_entry(blk_rbc_id);
	_send_mailbox(remote_chiplet_id, RBC_LPI_ENTRY_TEST);

	/* PCH MUX ON for access APB */
	rbc_pch_mux_on();

	/* L1 Entry */
	rbc_set_lp_mode(LP_MODE_L1);
	_lp_entry_chiplet_1_rbcv00_direct(LP_MODE_L1);
	rbc_lp_entry();

	uint32_t state = 0;
	uint32_t mod_id = 0;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_aw_ucie_ltsm_state(mod_id, &state));
	TEST_ASSERT_EQUAL(LTSM_L1_L2, state);

	state = 0;
	mod_id = 1;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_aw_ucie_ltsm_state(mod_id, &state));
	TEST_ASSERT_EQUAL(LTSM_L1_L2, state);

	/* L1 Exit */
	_send_mailbox(remote_chiplet_id, RBC_LP_EXIT_TEST);
	rbc_lp_exit();

	/* PCH MUX Off */
	rbc_pch_mux_off();

	/* LPI Exit */
	_send_mailbox(remote_chiplet_id, RBC_LPI_EXIT_TEST);
	pmu_rbc_lpi_exit(blk_rbc_id);

	_write_read_comp(0x2050000000, 0x100);
}

TEST(rbc_driver, l2_rbcv11_w_chiplet1_rbcv00)
{
	const uint32_t remote_chiplet_id = 1;
	const uint32_t LP_MODE_L2 = 2;

	_send_mailbox(remote_chiplet_id, RBC_V00_INIT_TEST);

	_write_read_comp(0x2040000000, 0x100);

	/* LPI Entry */
	pmu_rbc_lpi_entry(blk_rbc_id);
	_send_mailbox(remote_chiplet_id, RBC_LPI_ENTRY_TEST);

	/* PCH MUX ON for access APB */
	rbc_pch_mux_on();

	/* L2 Entry */
	rbc_set_lp_mode(LP_MODE_L2);
	_lp_entry_chiplet_1_rbcv00_direct(LP_MODE_L2);
	rbc_lp_entry();

	uint32_t state = 0;
	uint32_t mod_id = 0;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_aw_ucie_ltsm_state(mod_id, &state));
	TEST_ASSERT_EQUAL(LTSM_L1_L2, state);

	state = 0;
	mod_id = 1;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_aw_ucie_ltsm_state(mod_id, &state));
	TEST_ASSERT_EQUAL(LTSM_L1_L2, state);

	/* L2 Exit */
	_send_mailbox(remote_chiplet_id, RBC_LP_EXIT_TEST);
	rbc_lp_exit();

	/* PCH MUX Off */
	rbc_pch_mux_off();

	/* LPI Exit */
	_send_mailbox(remote_chiplet_id, RBC_LPI_EXIT_TEST);
	pmu_rbc_lpi_exit(blk_rbc_id);

	_write_read_comp(0x2040000000, 0x100);
}

TEST(rbc_driver, l1_abort_rbcv11_w_chiplet1_rbcv00)
{
	const uint32_t remote_chiplet_id = 1;
	const uint32_t LP_MODE_L1 = 1;

	_send_mailbox(remote_chiplet_id, RBC_V00_INIT_TEST);

	_write_read_comp(0x2040000000, 0x100);

	/* LPI Entry */
	pmu_rbc_lpi_entry(blk_rbc_id);
	_send_mailbox(remote_chiplet_id, RBC_LPI_ENTRY_TEST);

	/* PCH MUX ON for access APB */
	rbc_pch_mux_on();

	/* L2 Entry */
	rbc_set_lp_mode(LP_MODE_L1);
	_send_mailbox(remote_chiplet_id, RBC_SET_LP_MODE_L1_TEST);

	rbc_lp_entry();
	_send_mailbox(remote_chiplet_id, RBC_LP_ENTRY_TEST);

	uint32_t state = 0;
	uint32_t mod_id = 0;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_aw_ucie_ltsm_state(mod_id, &state));
	TEST_ASSERT_EQUAL(LTSM_L1_L2, state);

	state = 0;
	mod_id = 1;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_aw_ucie_ltsm_state(mod_id, &state));
	TEST_ASSERT_EQUAL(LTSM_L1_L2, state);

	/* L2 Exit */
	_send_mailbox(remote_chiplet_id, RBC_LP_EXIT_TEST);
	rbc_lp_exit();

	/* PCH MUX Off */
	rbc_pch_mux_off();

	/* LPI Exit */
	_send_mailbox(remote_chiplet_id, RBC_LPI_EXIT_TEST);
	pmu_rbc_lpi_exit(blk_rbc_id);

	_write_read_comp(0x2040000000, 0x100);
}

TEST(rbc_driver, l2_abort_rbcv11_w_chiplet1_rbcv00)
{
	const uint32_t remote_chiplet_id = 1;
	const uint32_t LP_MODE_L2 = 2;

	_send_mailbox(remote_chiplet_id, RBC_V00_INIT_TEST);

	_write_read_comp(0x2040000000, 0x100);

	/* LPI Entry */
	pmu_rbc_lpi_entry(blk_rbc_id);
	_send_mailbox(remote_chiplet_id, RBC_LPI_ENTRY_TEST);

	/* PCH MUX ON for access APB */
	rbc_pch_mux_on();

	/* L2 Entry */
	rbc_set_lp_mode(LP_MODE_L2);
	_send_mailbox(remote_chiplet_id, RBC_SET_LP_MODE_L2_TEST);

	rbc_lp_entry();
	_send_mailbox(remote_chiplet_id, RBC_LP_ENTRY_TEST);

	uint32_t state = 0;
	uint32_t mod_id = 0;

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_aw_ucie_ltsm_state(mod_id, &state));
	TEST_ASSERT_EQUAL(LTSM_L1_L2, state);

	state = 0;
	mod_id = 1;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_aw_ucie_ltsm_state(mod_id, &state));
	TEST_ASSERT_EQUAL(LTSM_L1_L2, state);

	/*L2 Exit */
	_send_mailbox(remote_chiplet_id, RBC_LP_EXIT_TEST);
	rbc_lp_exit();

	/* PCH MUX Off */
	rbc_pch_mux_off();

	/* LPI Exit */
	_send_mailbox(remote_chiplet_id, RBC_LPI_EXIT_TEST);
	pmu_rbc_lpi_exit(blk_rbc_id);

	_write_read_comp(0x2040000000, 0x100);
}
#endif /* not USE_DILIGENT_PTR */

TEST_GROUP_RUNNER(rbc_driver_except_only_for_mock)
{
	RUN_TEST_CASE(rbc_driver, rbc_driver_init);
	RUN_TEST_CASE(rbc_driver, set_target_rbc_blk);
#ifndef USE_DILIGENT_PTR
	/*
	 *RUN_TEST_CASE(rbc_driver, l1_rbcv11_w_chiplet1_rbcv00);
	 *RUN_TEST_CASE(rbc_driver, l2_rbcv11_w_chiplet1_rbcv00);
	 *RUN_TEST_CASE(rbc_driver, l1_abort_rbcv11_w_chiplet1_rbcv00);
	 *RUN_TEST_CASE(rbc_driver, l2_abort_rbcv11_w_chiplet1_rbcv00);
	 */
#endif /* not USE_DILIGENT_PTR */
}

TEST_GROUP_RUNNER(rbc_driver_only_for_mock)
{
}

#ifdef USE_DILIGENT_PTR

int32_t dummy_aw_ucie_set_rx_vref_offset(const uint32_t module_sel, const uint32_t rx_vref_offset)
{
	return 0;
}

int32_t dummy_aw_ucie_set_rx_vref_offset_enable(const uint32_t module_sel, const uint32_t rx_vref_offset_enable)
{
	return 0;
}

static uint32_t iter_cnt;
static uint32_t reg_eml[INIT_VREF_OFFSET * 2];
static uint32_t reg_emr[INIT_VREF_OFFSET * 2];
static uint32_t eml_emr_set_index;
static uint32_t eml_emr_get_index;

void set_value_fake_aw_ucie_retrain_and_get_new_eml_emr(const uint32_t module_sel, const uint32_t eml,
														const uint32_t emr, const uint32_t lane_id)
{
	reg_eml[eml_emr_set_index] = eml;
	reg_emr[eml_emr_set_index] = emr;
	eml_emr_set_index = (eml_emr_set_index + 1) % (INIT_VREF_OFFSET * 2);
}

int32_t fake_aw_ucie_retrain_and_get_new_eml_emr(const uint32_t module_sel, uint32_t *const eml, uint32_t *const emr,
												 const uint32_t lane_id)
{
	*eml = reg_eml[eml_emr_get_index];
	*emr = reg_emr[eml_emr_get_index];
	eml_emr_get_index = (eml_emr_get_index + 1) % (INIT_VREF_OFFSET * 2);
	return 0;
}

#endif /* USE_DILIGENT_PTR */

static int32_t (*set_rx_vref_offset_bk)(const uint32_t module_sel, const uint32_t rx_vref_offset);
static int32_t (*set_rx_vref_offset_enable_bk)(const uint32_t module_sel, const uint32_t rx_vref_offset_enable);
static int32_t (*retrain_and_get_new_eml_emr_bk)(const uint32_t module_sel, uint32_t *const eml, uint32_t *const emr,
												 const uint32_t lane_id);

TEST(rbc_driver, check_print_eye_diagram)
{
	set_rx_vref_offset_bk = aw_ucie_set_rx_vref_offset;
	set_rx_vref_offset_enable_bk = aw_ucie_set_rx_vref_offset_enable;
	retrain_and_get_new_eml_emr_bk = aw_ucie_retrain_and_get_new_eml_emr;

#ifdef USE_DILIGENT_PTR
	aw_ucie_set_rx_vref_offset = dummy_aw_ucie_set_rx_vref_offset;
	aw_ucie_set_rx_vref_offset_enable = dummy_aw_ucie_set_rx_vref_offset_enable;
	aw_ucie_retrain_and_get_new_eml_emr = fake_aw_ucie_retrain_and_get_new_eml_emr;
#endif /* USE_DILIGENT_PTR */

	uint32_t module_sel = 0;

	for (int land_id = 0; land_id < 64; land_id++) {

#ifdef USE_DILIGENT_PTR
		for (iter_cnt = 0; iter_cnt < EOM_ITER_COUNT; iter_cnt++) {
			for (int i = INIT_VREF_OFFSET; i > 0; i--) {
				set_value_fake_aw_ucie_retrain_and_get_new_eml_emr(module_sel, EOM_LINE_LENGTH / 2 - i,
																   EOM_LINE_LENGTH / 2 - i, land_id);
			}
			for (int i = 0; i < INIT_VREF_OFFSET; i++) {
				set_value_fake_aw_ucie_retrain_and_get_new_eml_emr(module_sel, EOM_LINE_LENGTH / 2 - 1 - i,
																   EOM_LINE_LENGTH / 2 - 1 - i, land_id);
			}
		}

#endif /* USE_DILIGENT_PTR */
		TEST_ASSERT_EQUAL(RL_OK, rbc_aw_ucie_print_eye_diagram(module_sel, land_id, EOM_ITER_COUNT));
	}

	module_sel = 1;

	for (int land_id = 0; land_id < 64; land_id++) {
#ifdef USE_DILIGENT_PTR
		for (iter_cnt = 0; iter_cnt < EOM_ITER_COUNT; iter_cnt++) {
			for (int i = INIT_VREF_OFFSET; i > 0; i--) {
				set_value_fake_aw_ucie_retrain_and_get_new_eml_emr(module_sel, EOM_LINE_LENGTH / 2 - i,
																   EOM_LINE_LENGTH / 2 - i, land_id);
			}
			for (int i = 0; i < INIT_VREF_OFFSET; i++) {
				set_value_fake_aw_ucie_retrain_and_get_new_eml_emr(module_sel, EOM_LINE_LENGTH / 2 - 1 - i,
																   EOM_LINE_LENGTH / 2 - 1 - i, land_id);
			}
		}
#endif /* USE_DILIGENT_PTR */

		TEST_ASSERT_EQUAL(RL_OK, rbc_aw_ucie_print_eye_diagram(module_sel, land_id, EOM_ITER_COUNT));
	}

		aw_ucie_set_rx_vref_offset = set_rx_vref_offset_bk;
		aw_ucie_set_rx_vref_offset_enable = set_rx_vref_offset_enable_bk;
		aw_ucie_retrain_and_get_new_eml_emr = retrain_and_get_new_eml_emr_bk;
}
