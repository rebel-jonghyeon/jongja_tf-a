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
#include "rl_sizes.h"

#include "bat.h"
#include "pcie_dw.h"
#include "pcie_dw_iatu.h"
#include "pcie_dw_bar.h"
#include "pcie_rebelh.h"

const int32_t width = 11;

static const char help_pcie_iatu[] =
	"[pcie iatu <mode=0> <base addr> <target addr> <size>]\r\n"
	"[pcie iatu <mode=1> <bar#> <target addr> <size>]\r\n"
	"[pcie iatu <mode=2> <base addr> <target addr> <size> <vf_num>]\r\n"
	"[pcie iatu <mode=3> <vfbar#> <target addr> <size>]\r\n"
	"[pcie iatu_ib_reset]\r\n"
	"[pcie iatu_ob <base_addr> <target addr> <size> <vf_active> <vf_num>]"
	"[pcie ob_wr <offset> <size> <value1> <value2> ...] : Request memory write to host\r\n"
	"[pcie ob_rd <offset> <size>] : Request memory read to host\r\n"
	"[pcie disable_region <direction> <index>} : Disable iATU inbound/outbound region#(index)"
	"\r\n";

uint8_t test_pcie_iatu_inbound(int argc, char *argv[])
{
	uint32_t mode, vf_num = 0;
	uint64_t bar_or_base, target, size = 0;

	if (argc < 2) {
		printf("Check command\n%s", help_pcie_iatu);
		return RL_BADARG;
	}

	mode = strtol(argv[1], NULL, 0);

	if (mode == 0 || mode == 1 || mode == 3) {
		/* 0: ADDRESS_MATCH_MODE, 1: BAR_MATCH_MODE, 3:VFBAR_MATCH_MODE */
		if (argc != 5) {
			return RL_BADARG;
		}
	} else if (mode == 2) {
		/* 2: VF_MATCH_MODE */
		if (argc != 6) {
			return RL_BADARG;
		}
		vf_num = strtol(argv[5], NULL, 0);
	} else {
		return RL_BADARG;
	}

	bar_or_base = strtoull(argv[2], NULL, 0);
	target = strtoull(argv[3], NULL, 0);
	size = strtoull(argv[4], NULL, 0);

	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	int32_t ret = RL_ERROR;

	if (mode == BAR_MATCH_MODE) {
		ret = pcie_reconfigure_bar_match_mode(epc, bar_or_base, target, size);
	} else if (mode == VF_BAR_MATCH_MODE) {
		ret = pcie_reconfigure_bar_match_mode(epc, bar_or_base + VF_BAR0, target, size);
	} else if (mode == ADDRESS_MATCH_MODE) {
		ret = pcie_configure_inbound_address_match_mode(epc, bar_or_base, target, size, false, 0);
	} else if (mode == VF_MATCH_MODE) {
		ret = pcie_configure_inbound_address_match_mode(epc, bar_or_base, target, size, true, vf_num);
	} else
		return ret;

	return ret;
}

uint8_t test_pcie_iatu_outbound(int argc, char *argv[])
{
	bool vf_active = false;
	uint32_t vf_num = 0;
	uint64_t base, target, size = 0;

	if (!(argc == 4 || argc == 5)) {
		printf("Check command\n%s", help_pcie_iatu);
		return RL_BADARG;
	}

	base = strtoll(argv[1], NULL, 0);
	target = strtoll(argv[2], NULL, 0);
	size = strtoll(argv[3], NULL, 0);

	if (argc == 5) {
		vf_active = true;
		vf_num = strtol(argv[4], NULL, 0);
	}

	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	int32_t ret = RL_ERROR;
	int8_t index;

	if (vf_active)
		ret = pcie_configure_outbound_address_match_mode(epc, base, target, size, &index, true, vf_num);
	else
		ret = pcie_configure_outbound_address_match_mode(epc, base, target, size, &index, false, 0);

	return ret;
}

int32_t test_pcie_iatu_disable_region(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Check the command's arguments\n%s", help_pcie_iatu);
		return RL_BADARG;
	}

	struct pcie_epc *epc = pcie_get_epc();
	uint32_t direction = strtoul(argv[1], NULL, 0);
	uint32_t index = strtoul(argv[2], NULL, 0);

	if (direction == DW_PCIE_INBOUND || direction == DW_PCIE_OUTBOUND)
		pcie_iatu_disable_region(epc, direction, index);
	else {
		printf("Enter appropriate <direction> value\n");
		return RL_BADARG;
	}

	return RL_OK;
}

int32_t test_pcie_outbound_write(int argc, char *argv[])
{
	if (argc < 4) {
		printf("Check the command's arguments\n%s", help_pcie_iatu);
		return RL_BADARG;
	}

	uint32_t offset = strtoul(argv[1], NULL, 0);
	uint32_t size = strtoul(argv[2], NULL, 0);
	uint32_t wdata;
	uint32_t len;
	uint32_t i;

	if (size > SZ_128M) {
		printf("The input size exceeds 128 MB of the BAT page size for PCIe host (page 4).\n");
		return RL_BADARG;
	}

	len = argc - 3;

	if (len > size / 4) {
		/* Consider only four byte unit write */
		printf("The number of the input values exceeds the input size.\n");
		return RL_BADARG;
	}

	for (i = 0; i < size / 4; i++) {
		if (i < len) {
			wdata = strtoul(argv[3 + i], NULL, 0);
			rl_writel(wdata, (uint32_t *)(PCIE_HOST_BAT_BASE + offset + i * 4));
			printf("wdata[%d]: 0x%08x\n", i, wdata);
		} else {
			wdata = strtoul(argv[3], NULL, 0) + i;
			rl_writel(wdata, (uint32_t *)(PCIE_HOST_BAT_BASE + offset + i * 4));
			printf("wdata[%d]: 0x%08x\n", i, wdata);
		}
	}

	printf("\nOutbound write done\n");

	return RL_OK;
}

int32_t test_pcie_outbound_read(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Check the command's arguments\n%s", help_pcie_iatu);
		return RL_BADARG;
	}

	uint32_t offset = strtoul(argv[1], NULL, 0);
	uint32_t size = strtoul(argv[2], NULL, 0);
	uint32_t i;

	if (size > SZ_128M) {
		printf("The input size exceeds 128 MB of the BAT page size for PCIe host (page 4).\n");
		return RL_BADARG;
	}

	printf("Read data from host\n");
	for (i = 0; i < size / SZ_4; i++) {
		if (i == 0) {
			printf("[0x%08x]:", offset);
		} else if ((offset + SZ_4 * i) % SZ_16 == 0) {
			printf("\n[0x%08x]:", offset + SZ_4 * i);
		}
		printf(" 0x%08x", rl_readl((uint32_t *)(PCIE_HOST_BAT_BASE + offset + SZ_4 * i)));
	}

	printf("\n\nOutbound read done\n");

	return RL_OK;
}

void test_pcie_iatu_disable_inbound_region_all(void)
{
	struct pcie_epc *epc = pcie_get_epc();

	pcie_iatu_disable_match_mode_region(epc, ADDRESS_MATCH_MODE);
	pcie_iatu_disable_match_mode_region(epc, BAR_MATCH_MODE);
	pcie_iatu_disable_match_mode_region(epc, VF_MATCH_MODE);
	pcie_iatu_disable_match_mode_region(epc, VF_BAR_MATCH_MODE);
}

int32_t test_pcie_show_iatu_table(void)
{
	struct iatu_region_info info = {0,};
	struct pcie_epc *epc = pcie_get_epc();
	uint8_t num_regions = epc->drv->iatu_info->iatu_num_ib_regions;
	uint32_t i;

	printf("---------------------------------------------------------------------------------------\n");
	printf("iATU Inbound Region\n");
	printf("---------------------------------------------------------------------------------------\n");
	printf(" Region\t     mode     \tbar/fun\t    Target\t     Base\t    Limit\t Incr\n");
	for (i = 0; i < num_regions; i++) {
		if (pcie_get_iatu_ib_info(epc, i, &info) < 0) {
			continue;
		}

		printf("   %d\t", info.region_num);

		if (info.match_mode == BAR_MATCH_MODE) {
			printf("PF(BAR_MATCH)\t");
			printf(" BAR%d\t", info.bar_num);
			printf("  0x%0*llx\t", width, info.target_addr);
			printf("\n");
		} else if (info.match_mode == VF_BAR_MATCH_MODE) {
			printf("VF(BAR_MATCH)\t");
			printf(" BAR%d\t", info.bar_num - VF_BAR0);
			printf("  0x%0*llx\t", width, info.target_addr);
			printf("\n");
		} else if (info.match_mode == ADDRESS_MATCH_MODE) {
			printf("ADDRESS_MATCH\t");
			printf(" ----\t");
			printf("  0x%0*llx\t", width, info.target_addr);
			printf(" 0x%0*llx\t", width, info.base_addr);
			printf("0x%0*llx\t", width, info.limit);
			printf("  0x%x\n", info.incr);
		} else {
			printf("  VF_MATCH\t");
			printf("VFUNC%d\t", info.vf_num & VF_NUM_MASK);
			printf("  0x%0*llx\t", width, info.target_addr);
			printf(" 0x%0*llx\t", width, info.base_addr);
			printf("0x%0*llx\t", width, info.limit);
			printf("  0x%x\n", info.incr);
		}
	}

	printf("-------------------------------------------------------------------------------\n");
	printf("iATU Outbound Region\n");
	printf("-------------------------------------------------------------------------------\n");
	printf(" Region\tbar/fun\t    Target\t     Base\t    Limit\t Incr\n");

	for (i = 0; i < num_regions; i++) {
		if (pcie_get_iatu_ob_info(epc, i, &info) < 0) {
			continue;
		}

		printf("   %d\t", info.region_num);
		if (info.vf_num & VF_MATCH)
			printf(" VF%d\t", info.vf_num & VF_NUM_MASK);
		else
			printf("  PF\t");
		printf("  0x%0*llx\t", width, info.target_addr);
		printf(" 0x%0*llx\t", width, info.base_addr);
		printf("0x%0*llx\t", width, info.limit);
		printf("  0x%x\n", info.incr);
	}
	printf("-------------------------------------------------------------------------------\n");

	return 0;
}

TEST_GROUP(pcie_iatu);

TEST_SETUP(pcie_iatu)
{
}

TEST_TEAR_DOWN(pcie_iatu)
{
}

static void change_bar_size_test(enum pcie_bar_num bar_num, int32_t match_mode)
{
	struct pcie_epc *epc;
	struct iatu_region_info info = {0,};
	struct pcie_bar_info bar_info;
	int32_t index;

	epc = pcie_get_epc();
	TEST_ASSERT_NOT_NULL(epc);

	/* Back-up bar info */
	bar_info = epc->drv->bar_info[bar_num];

	/* Configure iATU region */
	TEST_ASSERT_EQUAL(RL_OK, pcie_reconfigure_bar_match_mode(epc, bar_num, bar_info.phys_addr, SZ_1M));
	TEST_ASSERT_NOT_EQUAL(RL_NOT_FOUND, index = pcie_find_iatu_region_by_bar_num(epc, bar_num));
	TEST_ASSERT_EQUAL(index, pcie_get_iatu_ib_info(epc, index, &info));
	TEST_ASSERT_EQUAL(match_mode, info.match_mode);
	TEST_ASSERT_EQUAL(bar_num, info.bar_num);
	TEST_ASSERT_EQUAL(bar_info.phys_addr, info.target_addr);
	TEST_ASSERT_EQUAL(SZ_1M, epc->drv->bar_info[bar_num].size);

	/* Restore bar info */
	pcie_iatu_disable_region(epc, DW_PCIE_INBOUND, index);
	epc->drv->bar_info[bar_num] = bar_info;
	pcie_set_bar(epc->cfg, epc->drv, &bar_info);
}

TEST(pcie_iatu, change_resizable_bar01)
{
	change_bar_size_test(BAR0, BAR_MATCH_MODE);
}

TEST(pcie_iatu, change_programmable_bar23)
{
	change_bar_size_test(BAR2, BAR_MATCH_MODE);
}

TEST(pcie_iatu, change_programmable_bar4)
{
	change_bar_size_test(BAR4, BAR_MATCH_MODE);
}

TEST(pcie_iatu, change_resizable_vf_bar01)
{
	change_bar_size_test(VF_BAR0, VF_BAR_MATCH_MODE);
}

TEST(pcie_iatu, change_programmable_vf_bar23)
{
	change_bar_size_test(VF_BAR2, VF_BAR_MATCH_MODE);
}

TEST(pcie_iatu, change_programmable_vf_bar4)
{
	change_bar_size_test(VF_BAR4, VF_BAR_MATCH_MODE);
}

TEST_GROUP_RUNNER(pcie_change_bar_size_group_pf)
{
	RUN_TEST_CASE(pcie_iatu, change_resizable_bar01);
	RUN_TEST_CASE(pcie_iatu, change_programmable_bar23);
	RUN_TEST_CASE(pcie_iatu, change_programmable_bar4);
}

TEST_GROUP_RUNNER(pcie_change_bar_size_group_vf)
{
	RUN_TEST_CASE(pcie_iatu, change_resizable_vf_bar01);
	RUN_TEST_CASE(pcie_iatu, change_programmable_vf_bar23);
	RUN_TEST_CASE(pcie_iatu, change_programmable_vf_bar4);
}

static void pcie_iatu_tests(void)
{
	RUN_TEST_GROUP(pcie_change_bar_size_group_pf);
	RUN_TEST_GROUP(pcie_change_bar_size_group_vf);
}

int32_t test_pcie_iatu(int argc, char *argv[])
{
	return UnityMain(argc, (const char **)argv, pcie_iatu_tests);
}
