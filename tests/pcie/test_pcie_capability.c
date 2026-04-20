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

#include "rl_errors.h"

#include "pcie_dw.h"

static const char help_pcie_cap[] =
	"[pcie find_cap <id>]: Find PCIe capability\r\n"
	"[pcie find_ext_cap <id>]: Find PCIe extended capability\r\n"
	"[pcie dis_cap <id>]: Disable PCIe capability\r\n"
	"[pcie dis_ext_cap <id>]: Disable PCIe extended capability\r\n"
	"\r\n";

int32_t test_pcie_find_capability(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command again\n%s", help_pcie_cap);
		return RL_BADARG;
	}

	uint32_t cap = strtol(argv[1], NULL, 0);
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc)
		return RL_ERROR;

	uint32_t cap_ptr;

	cap_ptr = pcie_find_capability(epc, cap);
	if (cap_ptr > 0) {
		printf("Capability 0x%x is found at address 0x%x\n", cap, cap_ptr);
	} else {
		printf("Capability 0x%x is not found\n", cap);
	}

	return 0;
}

int32_t test_pcie_find_ext_capability(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command again\n%s", help_pcie_cap);
		return RL_BADARG;
	}

	uint32_t cap = strtol(argv[1], NULL, 0);
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc)
		return RL_ERROR;

	uint32_t cap_ptr;

	cap_ptr = pcie_find_ext_capability(epc, cap);
	if (cap_ptr > 0) {
		printf("Capability 0x%x is found at address 0x%x\n", cap, cap_ptr);
	} else {
		printf("Capability 0x%x is not found\n", cap);
	}

	return 0;
}

int32_t test_pcie_disable_capability(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command again\n%s", help_pcie_cap);
		return RL_BADARG;
	}

	uint32_t cap = strtol(argv[1], NULL, 0);
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc)
		return RL_ERROR;

	bool ret = false;

	ret = pcie_disable_capability(epc, cap);
	if (ret == true) {
		printf("Capability 0x%x is disabled\n", cap);
	} else {
		printf("Capability 0x%x is not found\n", cap);
	}

	return 0;
}

int32_t test_pcie_disable_ext_capability(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command again\n%s", help_pcie_cap);
		return RL_BADARG;
	}

	uint32_t cap = strtol(argv[1], NULL, 0);
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc)
		return RL_ERROR;

	bool ret = false;

	ret = pcie_disable_ext_capability(epc, cap);
	if (ret == true) {
		printf("Capability 0x%x is disabled\n", cap);
	} else {
		printf("Capability 0x%x is not found\n", cap);
	}

	return 0;
}
