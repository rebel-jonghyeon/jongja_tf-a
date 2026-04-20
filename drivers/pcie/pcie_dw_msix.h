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

#pragma once

/* AXI DBI Address Bus Layout for MSI-X */
/* ---------------------------------------------------------------------------------------------
 * | Access Type |32 |31 |30 |29-22|     21    |20-16|15 |             14-2             | 1 | 0 |
 * |--------------------------------------------------------------------------------------------|
 * | MSI-X Table | 1 | 1 | 1 | VF# | VF Active | PF# | 0 | 8K-DWORD MSI-X Table Address | 0 | 0 |
 * | MSI-X PBA   | 1 | 1 | 1 | VF# | VF Active | PF# | 1 | 8K-DWORD MSI-X Table Address | 0 | 0 |
 * ---------------------------------------------------------------------------------------------
 */
#define PCIE_MSIX_VF_ACTIVE BIT(21)
#define PCIE_MSIX_VF_TABLE_OFFSET (0x400000)

/* MSI-X Table entry format (in memory mapped by a BAR) */
#define PCI_MSIX_ENTRY_SIZE			16
#define PCI_MSIX_ENTRY_LOWER_ADDR	0x0  /* Message Address */
#define PCI_MSIX_ENTRY_UPPER_ADDR	0x4  /* Message Upper Address */
#define PCI_MSIX_ENTRY_DATA			0x8  /* Message Data */
#define PCI_MSIX_ENTRY_VECTOR_CTRL	0xC  /* Vector Control */
#define PCI_MSIX_ENTRY_CTRL_MASKBIT	0x00000001

/* MSI-X DOORBELL OFF */
#define MSIX_DOORBELL_VECTOR_MASK (0x7FF)
#define MSIX_DOORBELL_VECTOR_SET(x) ((x) & MSIX_DOORBELL_VECTOR_MASK)
#define MSIX_DOORBELL_TC_MASK (0x7000)
#define MSIX_DOORBELL_TC_SET(x) (((x) << 12) & MSIX_DOORBELL_TC_MASK)
#define MSIX_DOORBELL_VF_ACTIVE_MASK (0X8000)
#define MSIX_DOORBELL_VF_ACTIVE_SET (((1) << 15) & MSIX_DOORBELL_VF_ACTIVE_MASK)
#define MSIX_DOORBELL_VF_MASK (0xFF0000)
#define MSIX_DOORBELL_VF_SET(x) (((x) << 16) & MSIX_DOORBELL_VF_MASK)
#define MSIX_DOORBELL_PF_MASK (0x1F000000)
#define MSIX_DOORBELL_PF_SET(x) (((x) << 24) & MSIX_DOORBELL_PF_MASK)

/* MSI-X CAP CTRL */
#define MSIX_CAP_CTRL_ENABLE BIT(31)
#define MSIX_CAP_CTRL_FUNCTION_MASK BIT(30)

struct pcie_msix_tbl_entry {
	uint32_t msg_addr_lwr;
	uint32_t msg_addr_up;
	uint32_t msg_data;
	uint32_t vector_ctrl;
};

struct pcie_msix_tbl {
	struct pcie_msix_tbl_entry entries[32];
};

int32_t pcie_msix_setup(const struct dw_pcie_config *cfg, uint64_t addr);
int32_t pcie_raise_msix_irq(struct pcie_epc *dw_pcie_epc, enum pcie_func_type type,
							uint32_t func_id, uint32_t tc, uint32_t vector);
