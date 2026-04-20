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

#include "rl_errors.h"
#include "rl_utils.h"

#include "pcie_dw.h"
#include "pcie_doe.h"

#define PCIE_DEBUG_ON 1
#define PCIE_ERR_ON 1
#include "pcie_log.h"

int32_t pcie_doe_read_wmb(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data)
{
	volatile struct pcie_doe_register *doe_base = cfg->doe_base;
	volatile uint32_t val, h0, h1;
	uint32_t len;

	/* Read the first dword
	 * [15:0] - Vendor ID
	 * [23:16] - Data Object Type
	 */
	h0 = doe_base->doe_write_data_mailbox.val;

	/* Read the second dword
	 * [17:0] - Length
	 * [29:18] - Connection ID
	 */
	h1 = doe_base->doe_write_data_mailbox.val;
	len = (h1 & PCI_DOE_HEADER_2_LENGTH);
	if (len == 0) {
		len = DOE_MAX_LENGTH;
	} else if (len < 2) {
		pcie_err_log("Wrong length size\n");
		return RL_ERROR;
	} else {
		/* 2 dwords for Header have already been read */
		len -= 2;
	}

	uint32_t *dst_addr = data->doe_fifo_addr;

	pcie_dbg_log("Write header to 0x%08x\n", dst_addr);

	rl_writel(h0, dst_addr); dst_addr++;
	rl_writel(h1, dst_addr); dst_addr++;

	pcie_dbg_log("Write payload to 0x%08x length: %d\n", dst_addr, len);
	while (len > 0) {
		val = doe_base->doe_write_data_mailbox.val;
		rl_writel(val, dst_addr);

		dst_addr++;
		len--;
	}

	return RL_OK;
}

int32_t pcie_doe_write_rmb(struct pcie_epc *dw_pcie_epc, int32_t len, uint32_t *payload)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_doe_register *doe_base = cfg->doe_base;
	int32_t i;

	for (i = 0; i < len; i++) {
		doe_base->doe_read_data_mailbox.val = *(payload + i);
	}

	doe_base->doe_error_flag.rbox_dw_mismatch_check = 1;

	return RL_OK;
}

int32_t pcie_doe_setup(struct pcie_epc *dw_pcie_epc, uint32_t addr)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	struct dw_pcie_drv *data = dw_pcie_epc->drv;
	volatile struct pcie_doe_register *doe_base = cfg->doe_base;

	/* Set address to be write */
	data->doe_fifo_addr = (uint32_t *)addr;

	/* Clear data and irq */
	doe_base->doe_control.doe_abort = 1;
	doe_base->doe_error_flag.irq_clear = 1;

	return RL_OK;
}
