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
#include "pcie_dw_iatu.h"
#include "pcie_dw_msix.h"
#include "pcie_rebelh.h"

#define PCIE_DEBUG_ON 1
#define PCIE_ERR_ON 1
#include "pcie_log.h"

int32_t pcie_msix_setup(const struct dw_pcie_config *cfg, uint64_t addr)
{
	volatile struct pcie_ctrl_port_register *port_base = cfg->port_base;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;

	/* Default values of MSI-X Capability registers on IP Configuration
	 * MSI-X Table BIR = 0x5
	 * MSI-X Table offset = 0x400
	 * MSI-X PBA BIR = 0x5
	 * MSI-X PBA offset = 0x300
	 */

	port_base->pf0_port_logic_msix_address_match_low_off.msix_address_match_low =
		LOWER_32_BITS(addr) >> 2;
	port_base->pf0_port_logic_msix_address_match_high_off.msix_address_match_high =
		UPPER_32_BITS(addr);
	port_base->pf0_port_logic_msix_address_match_low_off.msix_address_match_en = 1;

	dbi_base->pf0_msix_cap_pci_msix_cap_id_next_ctrl_reg.pci_msix_enable = 1;

	return RL_OK;
}

int32_t pcie_raise_msix_irq(struct pcie_epc *dw_pcie_epc, enum pcie_func_type type,
							uint32_t func_id, uint32_t tc, uint32_t vector)
{
	struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	uint32_t msix_cap_ctrl, vec_ctrl;

	if (vector < 1 || vector > REBELH_PCIE_MSIX_TABLE_SIZE) {
		pcie_err_log("Fail: Check vector num %d\n", vector);
		return RL_BADARG;
	}

	if (type == TYPE_PF) {
		if (func_id) {
			pcie_err_log("Fail: Check func_id PF%d\n", func_id);
			return RL_BADARG;
		}
		msix_cap_ctrl = cfg->dbi_base->pf0_msix_cap_pci_msix_cap_id_next_ctrl_reg.val;
		vec_ctrl = cfg->msix_tbl->entries[vector - 1].vector_ctrl;
	} else if (type == TYPE_VF) {
		if (func_id >= PCIE_VF_NUM_MAX) {
			pcie_err_log("Fail: Check func_id VF%d\n", func_id);
			return RL_BADARG;
		}
		msix_cap_ctrl = cfg->vf_base[func_id]->vf_pf0_msix_cap_vf_pci_msix_cap_id_next_ctrl_reg.val;
		vec_ctrl = cfg->vf_msix_tbl[func_id]->entries[vector - 1].vector_ctrl;
	} else {
		pcie_err_log("Invalid PCIe function type\n");
		return RL_BADARG;
	}

	if ((msix_cap_ctrl & MSIX_CAP_CTRL_ENABLE) == 0) {
		pcie_err_log("Fail: MSI-X is not enabled\n");
		return RL_ERROR;
	}

	if (msix_cap_ctrl & MSIX_CAP_CTRL_FUNCTION_MASK) {
		pcie_dbg_log("PCI_MSIX_CAP_ID_NEXT_CTRL_REG[PCI_MSIX_FUNCTION_MASK] is masked\n"
						"It will be pending until cleared\n");
	}

	if (vec_ctrl & PCI_MSIX_ENTRY_CTRL_MASKBIT) {
		pcie_dbg_log("The vector[%d] is masked\n", vector);
		pcie_dbg_log("It will be pending until the Vector Control mask bit is cleared\n");
	}

	/*  Write msg_data to the same address on MSIX_ADDRESS_MATCH_*
	 *  | 31:29 | 28:24 | 23:16 |     15    | 14:12 |  11  |  10:0  |
	 *  | Rsvd  |  PF   |  VF   | VF Active |  TC   | Rsvd | Vector |
	 */
	uint32_t db_data = MSIX_DOORBELL_VF_SET(tc) | MSIX_DOORBELL_VECTOR_SET(vector - 1);

	if (type == TYPE_PF) {
		db_data |= MSIX_DOORBELL_PF_SET(func_id);
	} else {
		db_data |= (MSIX_DOORBELL_VF_SET(func_id) | MSIX_DOORBELL_VF_ACTIVE_SET);
	}

	/* This trigger address must be mapped with the address defined in MSIX_ADDRESS_MATCH_*. */
	uint32_t trigger_addr = REBELH_PCIE_MSIX_ADDR_BAT_TRANSLATED;

	rl_writel(db_data, (uint32_t *)trigger_addr);

	return RL_OK;
}
