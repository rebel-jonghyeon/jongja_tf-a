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

#include "pcie_dw.h"
#include "pcie_doe.h"

#include "test_pcie_utils.h"

static const char help_pcie_doe[] =
	"[pcie doe_send <length>]\r\n"
	"[pcie doe_read <length>]\r\n"
	"[pcie doe_setup <addr>]\r\n"
	"\r\n";

int32_t test_pcie_write_to_rmb(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command\n%s", help_pcie_doe);
		return RL_BADARG;
	}

	uint32_t len = strtoul(argv[1], NULL, 0);
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	uint32_t payload[DOE_MAX_LENGTH] = {0,};
	int32_t i;

	if (len > DOE_MAX_LENGTH || len <= PCI_DOE_HEADER_LEN) {
		return RL_BADLEN;
	}

	payload[1] = len & PCI_DOE_HEADER_2_LENGTH;
	for (i = 0; i < len - PCI_DOE_HEADER_LEN; i++) {
		payload[i + PCI_DOE_HEADER_LEN] = i;
	}

	printf("Write to DOE READ MB\n");
	return pcie_doe_write_rmb(epc, len, payload);
}

/* This function is only for Debug purpose */
int32_t test_pcie_doe_print_wmb_data(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command\n%s", help_pcie_doe);
		return RL_BADARG;
	}

	uint32_t len = strtoul(argv[1], NULL, 0);
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	int32_t i;
	struct dw_pcie_drv *data = epc->drv;

	for (i = 0; i < len; i++) {
		if (i % 4 == 0)
			printf("\n0x%08x: ", data->doe_fifo_addr + i);
		printf("0x%08x ", rl_readl(data->doe_fifo_addr + i));
	}
	printf("\n");

	return RL_OK;
}

int32_t test_pcie_doe_setup_addr(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command\n%s", help_pcie_doe);
		return RL_BADARG;
	}

	uint32_t addr = strtoul(argv[1], NULL, 0);
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	return pcie_doe_setup(epc, addr);
}

/* Unit Test for DOE */
static struct pcie_epc *pcie_epc;

TEST_GROUP(pcie_doe_test);

TEST_SETUP(pcie_doe_test)
{
	pcie_epc = pcie_get_epc();
}

TEST_TEAR_DOWN(pcie_doe_test)
{
	pcie_epc = NULL;
}

TEST(pcie_doe_test, pcie_doe_lb)
{
	rl_writel(TEST_ID_DOE, (uint32_t *)PCIE_HOST_TC_ADDR);

	struct dw_pcie_drv *data = pcie_epc->drv;
	uint32_t *src_addr = data->doe_fifo_addr;
	uint32_t payload[DOE_MAX_LENGTH] = {0,};
	uint32_t len;
	int i;

	src_addr++; /* length is in second DW */
	while (1) {
		len = rl_readl(src_addr);
		if (len)
			break;
		vTaskDelay(1);
	}
	rl_writel(0, src_addr);

	TEST_ASSERT_EQUAL(PCIE_DOE_TEST_LENGTH, len);

	payload[1] = len & PCI_DOE_HEADER_2_LENGTH;
	for (i = 0; i < len - PCI_DOE_HEADER_LEN; i++) {
		payload[i + PCI_DOE_HEADER_LEN] = rl_readl(++src_addr);
	}
	TEST_ASSERT_EQUAL(PCIE_DOE_TEST_PAYLOAD_0, payload[2]);
	TEST_ASSERT_EQUAL(PCIE_DOE_TEST_PAYLOAD_1, payload[3]);
	TEST_ASSERT_EQUAL(RL_OK, pcie_doe_write_rmb(pcie_epc, len, payload));

	TEST_ASSERT_EQUAL(RESULT_PASS, check_pcie_test_result());
}

static void pcie_doe_tests(void)
{
	RUN_TEST_CASE(pcie_doe_test, pcie_doe_lb);
}

int32_t test_pcie_doe(int argc, char *argv[])
{
	return UnityMain(argc, (const char **)argv, pcie_doe_tests);
}
