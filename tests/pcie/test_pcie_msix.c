/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#include "unity_fixture.h"
#include "rl_utils.h"
#include "rl_errors.h"

#include "pcie_rebelh.h"
#include "pcie_dw.h"
#include "pcie_dw_msix.h"

#include "test_pcie_utils.h"

static const char help_pcie_msix[] =
	"[pcie msix <type> <func_id> <tc> <vector>]\r\n"
	"\r\n";

int32_t test_pcie_request_msix(int argc, char *argv[])
{
	if (argc != 5) {
		printf("Check command\n%s", help_pcie_msix);
		return RL_BADARG;
	}

	uint8_t type = strtoul(argv[1], NULL, 0);
	uint8_t func_id = strtoul(argv[2], NULL, 0);
	uint8_t tc = strtoul(argv[3], NULL, 0);
	uint8_t vector = strtoul(argv[4], NULL, 0);

	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}
	printf("Request MSI-X type[%s] Func ID[%d] TC[%d] vector[%d]\n",
		   (type == TYPE_PF) ? "PF" : "VF", func_id, tc, vector);

	return pcie_raise_msix_irq(epc, type, func_id, tc, vector);
}

/* Unit Test for MSI-X */
static struct pcie_epc *pcie_epc;

TEST_GROUP(pcie_msix_test);

TEST_SETUP(pcie_msix_test)
{
	pcie_epc = pcie_get_epc();
}

TEST_TEAR_DOWN(pcie_msix_test)
{
	pcie_epc = NULL;
}

static void save_msix_data(struct pcie_msix_tbl *backup_msix_tbl, struct pcie_msix_tbl *ori_msix_tbl,
						   uint32_t *backup_data)
{
	int i;

	*backup_msix_tbl = *ori_msix_tbl;

	for (i = 0; i < REBELH_PCIE_MSIX_TABLE_SIZE; i++) {
		backup_data[i] = rl_readl((uint32_t *)(PCIE_MSIX_TEST_HOST_ADDRESS_BAT_BASE + 0x4 * i));
	}
}

static void restore_msix_data(struct pcie_msix_tbl *ori_msix_tbl, struct pcie_msix_tbl *backup_msix_tbl,
							  uint32_t *backup_data)
{
	int i;

	*ori_msix_tbl = *backup_msix_tbl;

	for (i = 0; i < REBELH_PCIE_MSIX_TABLE_SIZE; i++) {
		rl_writel(backup_data[i], (uint32_t *)(PCIE_MSIX_TEST_HOST_ADDRESS_BAT_BASE + 0x4 * i));
	}
}

static void prepare_msix_table(struct pcie_msix_tbl *msix_tbl)
{
	uint64_t addr;
	uint32_t msg_data = PCIE_MSIX_TEST_MSG_DATA;
	uint32_t vector_control = 0;
	int i;

	for (i = 0; i < REBELH_PCIE_MSIX_TABLE_SIZE; i++) {
		addr = PCIE_MSIX_TEST_HOST_ADDRESS + (0x4 * i);
		rl_writel(LOWER_32_BITS(addr), &msix_tbl->entries[i].msg_addr_lwr);
		rl_writel(UPPER_32_BITS(addr), &msix_tbl->entries[i].msg_addr_up);
		rl_writel(msg_data + i, &msix_tbl->entries[i].msg_data);
		rl_writel(vector_control, &msix_tbl->entries[i].vector_ctrl);
	}
}

static void run_msix_test_sequence(struct pcie_msix_tbl *ori_msix_tbl, uint8_t type, uint8_t func_id)
{
	struct pcie_msix_tbl backup_msix_tbl;
	uint32_t backup_data[REBELH_PCIE_MSIX_TABLE_SIZE];
	uint8_t vector;

	/* Save MSI-X Table and host message data */
	save_msix_data(&backup_msix_tbl, ori_msix_tbl, backup_data);

	/* Write MSI-X Table */
	prepare_msix_table(ori_msix_tbl);

	/* Raise MSI-X */
	for (vector = 1; vector <= REBELH_PCIE_MSIX_TABLE_SIZE; vector++)
		TEST_ASSERT_EQUAL(RL_OK, pcie_raise_msix_irq(pcie_epc, type, func_id, 0, vector));

	/* Check test result */
	rl_writel(TEST_ID_MSIX, (uint32_t *)PCIE_HOST_TC_ADDR);
	TEST_ASSERT_EQUAL(RESULT_PASS, check_pcie_test_result());

	/* Restore MSI-X Table and host message data */
	restore_msix_data(ori_msix_tbl, &backup_msix_tbl, backup_data);
}

static void run_msix_fail_test_sequence(uint8_t type, uint8_t func_id, uint8_t vector)
{
	/* Raise MSI-X */
	TEST_ASSERT_NOT_EQUAL(RL_OK, pcie_raise_msix_irq(pcie_epc, type, func_id, 0, vector));
}

TEST(pcie_msix_test, raise_msix_pf)
{
	run_msix_test_sequence(pcie_epc->cfg->msix_tbl, TYPE_PF, 0);
}

TEST(pcie_msix_test, raise_msix_vf0)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[0], TYPE_VF, 0);
}

TEST(pcie_msix_test, raise_msix_vf1)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[1], TYPE_VF, 1);
}

TEST(pcie_msix_test, raise_msix_vf2)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[2], TYPE_VF, 2);
}

TEST(pcie_msix_test, raise_msix_vf3)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[3], TYPE_VF, 3);
}

TEST(pcie_msix_test, raise_msix_vf4)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[4], TYPE_VF, 4);
}

TEST(pcie_msix_test, raise_msix_vf5)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[5], TYPE_VF, 5);
}

TEST(pcie_msix_test, raise_msix_vf6)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[6], TYPE_VF, 6);
}

TEST(pcie_msix_test, raise_msix_vf7)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[7], TYPE_VF, 7);
}

TEST(pcie_msix_test, raise_msix_vf8)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[8], TYPE_VF, 8);
}

TEST(pcie_msix_test, raise_msix_vf9)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[9], TYPE_VF, 9);
}

TEST(pcie_msix_test, raise_msix_vf10)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[10], TYPE_VF, 10);
}

TEST(pcie_msix_test, raise_msix_vf11)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[11], TYPE_VF, 11);
}

TEST(pcie_msix_test, raise_msix_vf12)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[12], TYPE_VF, 12);
}

TEST(pcie_msix_test, raise_msix_vf13)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[13], TYPE_VF, 13);
}

TEST(pcie_msix_test, raise_msix_vf14)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[14], TYPE_VF, 14);
}

TEST(pcie_msix_test, raise_msix_vf15)
{
	run_msix_test_sequence(pcie_epc->cfg->vf_msix_tbl[15], TYPE_VF, 15);
}

TEST(pcie_msix_test, fail_to_raise_msix_pf1)
{
	run_msix_fail_test_sequence(TYPE_PF, 1, 1);
}

TEST(pcie_msix_test, fail_to_raise_msix_pf0_v0)
{
	run_msix_fail_test_sequence(TYPE_PF, 0, 0);
}

TEST(pcie_msix_test, fail_to_raise_msix_vf16)
{
	run_msix_fail_test_sequence(TYPE_VF, 16, 1);
}

TEST(pcie_msix_test, fail_to_raise_msix_vf0_v0)
{
	run_msix_fail_test_sequence(TYPE_VF, 0, 0);
}

TEST_GROUP_RUNNER(raise_msix_pf_group)
{
	RUN_TEST_CASE(pcie_msix_test, raise_msix_pf);
}

TEST_GROUP_RUNNER(raise_msix_vf_group)
{
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf0);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf1);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf2);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf3);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf4);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf5);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf6);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf7);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf8);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf9);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf10);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf11);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf12);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf13);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf14);
	RUN_TEST_CASE(pcie_msix_test, raise_msix_vf15);
}

TEST_GROUP_RUNNER(raise_msix_fail_group)
{
	RUN_TEST_CASE(pcie_msix_test, fail_to_raise_msix_pf1);
	RUN_TEST_CASE(pcie_msix_test, fail_to_raise_msix_pf0_v0);
	RUN_TEST_CASE(pcie_msix_test, fail_to_raise_msix_vf16);
	RUN_TEST_CASE(pcie_msix_test, fail_to_raise_msix_vf0_v0);
}

static void pcie_msix_tests(void)
{
	RUN_TEST_GROUP(raise_msix_pf_group);
	RUN_TEST_GROUP(raise_msix_vf_group);
	RUN_TEST_GROUP(raise_msix_fail_group);
}

int32_t test_pcie_msix(int argc, char *argv[])
{
	return UnityMain(argc, (const char **)argv, pcie_msix_tests);
}
