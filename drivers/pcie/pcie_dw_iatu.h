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

/* iATU Register */
#define ATU_TYPE_MEM 0x0
#define ATU_TYPE_IO 0x2

#define ADDRESS_MATCH_MODE 0
#define BAR_MATCH_MODE 1
#define VF_MATCH_MODE 2
#define VF_BAR_MATCH_MODE 3

#define VF_MATCH BIT(31)
#define VF_NUM_MASK (0xFF)

struct pcie_iatu_info {
	uint8_t iatu_num_ib_regions;
	uint8_t iatu_num_ob_regions;
	uint64_t iatu_ib_regions_mask;
	uint64_t iatu_ob_regions_mask;
};

struct pcie_iatu_cfg {
	uint64_t cpu_addr;
	uint64_t pci_addr;
	uint64_t size;
	uint32_t type;
	uint32_t vf_number;
};

struct iatu_region_info {
	uint64_t target_addr;
	uint64_t base_addr;
	uint32_t region_num;
	uint32_t match_mode;
	uint32_t bar_num;
	uint32_t vf_num;  /* BIT(31) is used for VF_ACTIVE */
	uint64_t limit;
	uint32_t incr;
};

enum dw_pcie_iatu_direction {
	DW_PCIE_INBOUND = 0,
	DW_PCIE_OUTBOUND
};

enum pcie_bar_num;

int32_t pcie_set_iatu_inbound(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data,
							  struct pcie_bar_info *bar_info, struct pcie_iatu_cfg *iatu_ib_cfg,
							  uint32_t match_mode);
int32_t pcie_set_iatu_outbound(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data,
							   struct pcie_iatu_cfg *iatu_ob_cfg, int8_t *index);
int32_t pcie_iatu_disable_region(struct pcie_epc *dw_pcie_epc, enum dw_pcie_iatu_direction direction,
								 uint32_t index);
int32_t pcie_iatu_disable_match_mode_region(struct pcie_epc *dw_pcie_epc, uint32_t match_mode);
int32_t pcie_find_iatu_region_by_bar_num(struct pcie_epc *dw_pcie_epc, enum pcie_bar_num bar);
int32_t pcie_reconfigure_bar_match_mode(struct pcie_epc *dw_pcie_epc, enum pcie_bar_num bar_num,
										uint64_t target_addr, uint64_t size);
int32_t pcie_configure_inbound_address_match_mode(struct pcie_epc *dw_pcie_epc,	uint64_t pci_addr,
												  uint64_t cpu_addr, uint64_t size, bool vf_match, uint32_t vf_num);
int32_t pcie_configure_outbound_address_match_mode(struct pcie_epc *dw_pcie_epc, uint64_t cpu_addr,
												   uint64_t pci_addr, uint64_t size, int8_t *index,
												   bool vf_match, uint32_t vf_num);
int32_t pcie_get_iatu_ib_info(struct pcie_epc *dw_pcie_epc, uint32_t index, struct iatu_region_info *info);
int32_t pcie_get_iatu_ob_info(struct pcie_epc *dw_pcie_epc, uint32_t index, struct iatu_region_info *info);
