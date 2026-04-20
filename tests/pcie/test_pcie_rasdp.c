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

#include <stdlib.h>

#include "rl_utils.h"
#include "rl_errors.h"

#include "pcie_dw.h"

static const char help_pcie_dp[] =
	"[pcie dp corr] : Print current corrected error count for the selected counter region\r\n"
	"[pcie dp uncorr] : Print current uncorrected error count for the selected counter region\r\n"
	"[pcie dp all] : Print all error count for the selected counter region\r\n"
	"[pcie dp sel_region <region_num>] : Select both correctable and uncorrectable counter region\r\n"
	"[pcie dp err_en <loc> <count> <type>] : Enable error injection\r\n"
	"\r\n";

struct ras_region_info {
	char *region_name;
	int32_t counter_sel_min;
	int32_t counter_sel_max;
};

static const struct ras_region_info ras_info[] =  {
	{"ADM_RX_PATH", 0, 41},
	{"L3_RX_PATH", 0, 15},
	{"L2_RX_PATH", 0, 0},
	{"DMA_INBOUND_PATH", 0, 23},
	{"AXI_INBOUND_REQ_PATH", 0, 29},
	{"AXI_INBOUND_CMPL_PATH", 1, 6},
	{"ADM_TX_PATH", 1, 14},
	{"L3_TX_PATH", 0, 5},
	{"L2_TX_PATH", 0, 5},
	{"DMA_OUTBOUND_PATH", 0, 16},
	{"AXI_OUTBOUND_REQ_PATH", 0, 20},
	{"AXI_OUTBOUND_CMPL_PATH", 0, 9},
	{"CXS_TX_RX_PATH", 0, 7},
	{"DTIM_TX_RX_PATH", 0, 12},
	{"CXL_TX_RX_PATH", 0, 7}
};

static int32_t print_count_selection(struct pcie_epc *epc, bool corr)
{
	int32_t i;
	uint8_t region = pcie_rasdp_get_region(epc, corr);

	printf("========================================\n");
	printf("%s Error counter\n", corr ? "Corrected" : "Uncorrected");
	printf("Selected region: %s\n", ras_info[region].region_name);
	printf("Counter sel: <value>\n");
	printf("----------------------------------------\n");

	for (i = ras_info[region].counter_sel_min; i <= ras_info[region].counter_sel_max; i++) {
		printf("%d: %d\n", i, pcie_rasdp_get_count(epc, corr, i));
	}

	printf("========================================\n");

	return RL_OK;
}

int32_t test_pcie_rasdp(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Check command again\n%s", help_pcie_dp);
		return RL_BADARG;
	}

	struct pcie_epc *epc = pcie_get_epc();

	if (!epc)
		return RL_ERROR;

	if (strcmp(argv[1], "corr") == 0) {
		print_count_selection(epc, true);
	} else if (strcmp(argv[1], "uncorr") == 0) {
		print_count_selection(epc, false);
	} else if (strcmp(argv[1], "all") == 0) {
		print_count_selection(epc, true);
		print_count_selection(epc, false);
	} else if (strcmp(argv[1], "sel_region") == 0) {
		if (argc != 3) {
			printf("Check command again\n%s", help_pcie_dp);
			return RL_BADARG;
		}

		uint8_t region = strtol(argv[2], NULL, 0);

		pcie_rasdp_select_region(epc, true, region);
		pcie_rasdp_select_region(epc, false, region);
	} else if (strcmp(argv[1], "err_en") == 0) {
		if (argc != 5) {
			printf("Check command again\n%s", help_pcie_dp);
			return RL_BADARG;
		}

		uint8_t loc = strtol(argv[2], NULL, 0);
		uint8_t count = strtol(argv[3], NULL, 0);
		uint8_t type = strtol(argv[4], NULL, 0);

		pcie_rasdp_enable_error_injection(epc, true, loc, count, type);
	} else {
		printf("Check command again\n%s", help_pcie_dp);
		return RL_BADARG;
	}

	return RL_OK;
}
