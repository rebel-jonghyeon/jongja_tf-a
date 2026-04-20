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
#include "rl_sizes.h"
#include "rl_utils.h"

#include "pcie_dw.h"
#include "pcie_dw_ide.h"
#include "pcie_doe.h"

#define PCIE_DEBUG_ON 1
#define PCIE_ERR_ON 1
#include "pcie_log.h"

extern struct pcie_epc dw_pcie_epc;

int32_t pcie_ide_setup(struct pcie_epc *epc, struct pcie_ide_cfg *ide_cfg)
{
	const struct dw_pcie_config *cfg = epc->cfg;

	volatile struct pcie_ide_apb_register *ide_apb_base = cfg->ide_apb_base;

	if (ide_cfg->is_link_stream) {
		if (ide_cfg->enable_tbit) {
			/* Set T-Bit for IDE link Streams */
			ide_apb_base->tx_link_tbit_cfg.val = IDE_CFG_S0_PR | IDE_CFG_S0_NPR | IDE_CFG_S0_CPL;
		}
	} else {
		if (ide_cfg->enable_tbit) {
			/* Set T-Bit for IDE Selective Streams */
			ide_apb_base->tx_slt_tbit1_cfg.val = IDE_CFG_S0_PR | IDE_CFG_S0_NPR | IDE_CFG_S0_CPL;
		}
	}

	ide_apb_base->ide_irq_en.val = 0x0;

	return RL_OK;
}

int32_t pcie_ide_enable_stream(struct pcie_epc *epc, bool is_link_stream, uint8_t stream_id)
{
	const struct dw_pcie_config *cfg = epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	if (is_link_stream) {
		dbi_base->wire_ide_link_stream_ctrl_0.stream_id = stream_id;
		dbi_base->wire_ide_link_stream_ctrl_0.link_ide_stream_enabled = 1;

		pcie_dbg_log("link stream enabled 0x%x\n", dbi_base->wire_ide_link_stream_ctrl_0.val);
	} else {
		dbi_base->wire_ide_slct_ide_stream_ctrl_0.stream_id = stream_id;
		dbi_base->wire_ide_slct_ide_stream_ctrl_0.slct_ide_stream_enabled = 1;

		pcie_dbg_log("selective link stream enabled 0x%x\n", dbi_base->wire_ide_slct_ide_stream_ctrl_0.val);
	}

	return RL_OK;
}

int32_t pcie_ide_swap_key(struct pcie_epc *epc, bool is_link_stream, uint8_t new_key)
{
	const struct dw_pcie_config *cfg = epc->cfg;

	volatile struct pcie_ide_apb_register *ide_apb_base = cfg->ide_apb_base;
	uint32_t tx_kbit, rx_kbit;
	/*
	 * Write Current K-bit value to RX_*_KBIT_CFG
	 * Write New K-bit value to TX_*_KBIT_CFG
	 */
	if (new_key) {
		rx_kbit = 0;
		tx_kbit = IDE_CFG_S0_PR | IDE_CFG_S0_NPR | IDE_CFG_S0_CPL;
	} else {
		rx_kbit = IDE_CFG_S0_PR | IDE_CFG_S0_NPR | IDE_CFG_S0_CPL;
		tx_kbit = 0;
	}

	if (is_link_stream) {
		ide_apb_base->rx_lnk_kbit_cfg.val = rx_kbit;
		ide_apb_base->tx_lnk_kbit_cfg.val = tx_kbit;

		pcie_dbg_log("rx_lnk_kbit_cfg 0x%x\n", ide_apb_base->rx_lnk_kbit_cfg.val);
		pcie_dbg_log("tx_lnk_kbit_cfg 0x%x\n", ide_apb_base->tx_lnk_kbit_cfg.val);
	} else {
		ide_apb_base->rx_slt_kbit1_cfg.val = rx_kbit;
		ide_apb_base->tx_slt_kbit1_cfg.val = tx_kbit;

		pcie_dbg_log("rx_slt_kbit_cfg 0x%x\n", ide_apb_base->rx_slt_kbit1_cfg.val);
		pcie_dbg_log("tx_slt_kbit_cfg 0x%x\n", ide_apb_base->tx_slt_kbit1_cfg.val);
	}

	return RL_OK;
}

#ifdef __TEST
void pcie_ide_cb(void)
{
	struct dw_pcie_drv *data = dw_pcie_epc.drv;

	/*
	 * Write the word to the end of doe_fifo_addr to notify that the key insert has been completed
	 * Address could be changed but update address in tests/pcie/test_pcie_ide_scenario.c also.
	 */
	rl_writel(MB_RECEIVED_KEY_INSERT_DONE, data->doe_fifo_addr + DOE_MAX_LENGTH);
}
#endif
