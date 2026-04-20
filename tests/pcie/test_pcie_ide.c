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

#include "test_common.h"
#include "rl_errors.h"

#include "pcie_dw.h"
#include "pcie_dw_ide.h"

/* Used same Stream ID into both Ports associated with a given Link IDE Stream. */
#define STREAM_ID (1)

static const char help_pcie_key_swap[] =
	"[pcie ide_key <key_set>]\r\n"
	"\r\n";

int32_t test_pcie_ide(void)
{
	struct pcie_epc *epc = pcie_get_epc();
	struct pcie_ide_cfg cfg = {0,};

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	printf("Setup and enable IDE\n");

	cfg.enable_tbit = true;
	cfg.is_link_stream = true;
	if (pcie_ide_setup(epc, &cfg))
		return RL_ERROR;

	if (pcie_ide_enable_stream(epc, true, STREAM_ID))
		return RL_ERROR;

	return RL_OK;
}

int32_t test_pcie_ide_key_swap(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Check command\n%s", help_pcie_key_swap);
		return RL_BADARG;
	}

	uint8_t key_set = strtoul(argv[1], NULL, 0);
	struct pcie_epc *epc = pcie_get_epc();

	if (!epc) {
		printf("Could not get pcie ep!!\n");
		return RL_ERROR;
	}

	printf("IDE Key swap to %d\n", key_set);
	if (pcie_ide_swap_key(epc, true, key_set))
		return RL_ERROR;

	return RL_OK;
}
