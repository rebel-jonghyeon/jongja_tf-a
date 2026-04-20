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

#include "pcie_dw.h"
#include "pcie_dw_iatu.h"
#include "pcie_dw_bar.h"

#define PCIE_DEBUG_ON 1
#define PCIE_ERR_ON 1
#include "pcie_log.h"

static int32_t pcie_check_iatu_region_available(struct dw_pcie_drv *data,
												enum dw_pcie_iatu_direction direction, uint8_t index)
{
	uint64_t iatu_regions_mask;

	if (direction == DW_PCIE_INBOUND)
		iatu_regions_mask = data->iatu_info->iatu_ib_regions_mask;
	else if (direction == DW_PCIE_OUTBOUND)
		iatu_regions_mask = data->iatu_info->iatu_ob_regions_mask;
	else {
		pcie_dbg_log("%s: Enter appropriate direction value\n", __func__);
		return RL_BADARG;
	}

	if (iatu_regions_mask & (0x1 << index))
		return RL_ERROR;
	else
		return RL_OK;
}

static int8_t pcie_find_iatu_free_region(struct dw_pcie_drv *data,
										 enum dw_pcie_iatu_direction direction)
{
	uint8_t iatu_num_regions;
	uint64_t iatu_regions_mask;
	int8_t shift = 0;

	if (direction == DW_PCIE_INBOUND) {
		iatu_num_regions = data->iatu_info->iatu_num_ib_regions;
		iatu_regions_mask = data->iatu_info->iatu_ib_regions_mask;
	} else if (direction == DW_PCIE_OUTBOUND) {
		iatu_num_regions = data->iatu_info->iatu_num_ob_regions;
		iatu_regions_mask = data->iatu_info->iatu_ob_regions_mask;
	} else {
		pcie_dbg_log("%s: Enter appropriate direction value\n", __func__);
		return RL_BADARG;
	}

	do {
		if (iatu_regions_mask & (0x1 << shift)) {
			shift++;
			continue;
		}

		break;
	} while (shift < iatu_num_regions);

	if (shift == iatu_num_regions)
		return RL_ERROR;

	return shift;
}

static int32_t pcie_iatu_assign_region(struct dw_pcie_drv *data, enum dw_pcie_iatu_direction direction,
									   uint8_t index)
{
	if (direction == DW_PCIE_INBOUND)
		data->iatu_info->iatu_ib_regions_mask |= (0x1 << index);
	else if (direction == DW_PCIE_OUTBOUND)
		data->iatu_info->iatu_ob_regions_mask |= (0x1 << index);
	else {
		pcie_dbg_log("%s: Enter appropriate direction value\n", __func__);
		return RL_BADARG;
	}

	return RL_OK;
}

static int32_t pcie_iatu_inbound_config(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data,
										uint8_t index, struct pcie_bar_info *bar_info,
										struct pcie_iatu_cfg *iatu_ib_cfg, uint32_t match_mode)
{
	int32_t ret = pcie_check_iatu_region_available(data, DW_PCIE_INBOUND, index);

	if (ret != RL_OK)
		return ret;

	volatile struct pcie_ctrl_pf0_atu_cap_iatu_register *iatu_base = cfg->iatu_base[index];

	if (match_mode == BAR_MATCH_MODE) {
		if (!bar_info || bar_info->num < BAR0 || bar_info->num > VF_BAR_MAX)
			return RL_ERROR;

		/* lower target address */
		iatu_base->pf0_atu_cap_iatu_lwr_target_addr_off_inbound.val =
			LOWER_32_BITS(bar_info->phys_addr);
		/* upper target address */
		iatu_base->pf0_atu_cap_iatu_upper_target_addr_off_inbound.val =
			UPPER_32_BITS(bar_info->phys_addr);

		/* ATU BAR configuration */
		if (bar_info->num <= BAR_MAX) {
			iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.bar_num = bar_info->num;
			iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.match_mode = BAR_MATCH_MODE;
		} else {
			iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.bar_num =
				bar_info->num - VF_BAR0;
			iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.vfbar_match_mode_en = 1;
		}

		/* ATU memory type */
		iatu_base->pf0_atu_cap_iatu_region_ctrl_1_off_inbound.type_ = ATU_TYPE_MEM;
	} else if (match_mode == ADDRESS_MATCH_MODE) {
		if (!iatu_ib_cfg)
			return RL_ERROR;

		uint64_t limit = iatu_ib_cfg->pci_addr + iatu_ib_cfg->size - 1;

		/* limit address */
		if (iatu_ib_cfg->size <= SZ_4G) {
			iatu_base->pf0_atu_cap_iatu_region_ctrl_1_off_inbound.increase_region_size = 0;
			iatu_base->pf0_atu_cap_iatu_limit_addr_off_inbound.val = LOWER_32_BITS(limit);
			iatu_base->pf0_atu_cap_iatu_uppr_limit_addr_off_inbound.val = 0;
		} else {
			iatu_base->pf0_atu_cap_iatu_region_ctrl_1_off_inbound.increase_region_size = 1;
			iatu_base->pf0_atu_cap_iatu_limit_addr_off_inbound.val = LOWER_32_BITS(limit);
			iatu_base->pf0_atu_cap_iatu_uppr_limit_addr_off_inbound.val = UPPER_32_BITS(limit);
		}

		/* lower base address */
		iatu_base->pf0_atu_cap_iatu_lwr_base_addr_off_inbound.val =
			LOWER_32_BITS(iatu_ib_cfg->pci_addr);
		/* upper base address */
		iatu_base->pf0_atu_cap_iatu_upper_base_addr_off_inbound.val =
			UPPER_32_BITS(iatu_ib_cfg->pci_addr);

		/* lower target address */
		iatu_base->pf0_atu_cap_iatu_lwr_target_addr_off_inbound.val =
			LOWER_32_BITS(iatu_ib_cfg->cpu_addr);
		/* upper target address */
		iatu_base->pf0_atu_cap_iatu_upper_target_addr_off_inbound.val =
			UPPER_32_BITS(iatu_ib_cfg->cpu_addr);

		iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.match_mode = ADDRESS_MATCH_MODE;

		if (iatu_ib_cfg->vf_number & VF_MATCH) {
			iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.vf_match_en = 1;
			iatu_base->pf0_atu_cap_iatu_region_ctrl_3_off_inbound.vf_number =
				iatu_ib_cfg->vf_number & VF_NUM_MASK;
		} else {
			iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.vf_match_en = 0;
		}

		/* ATU memory type */
		iatu_base->pf0_atu_cap_iatu_region_ctrl_1_off_inbound.type_ = iatu_ib_cfg->type;
	} else {
		pcie_dbg_log("%s: Select proper match mode for iATU inbound setting\n", __func__);
		return RL_BADARG;
	}

	/* ATU enable */
	iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.region_en = 1;

	ret = pcie_iatu_assign_region(data, DW_PCIE_INBOUND, index);

	return ret;
}

static int32_t pcie_iatu_outbound_config(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data,
										 uint8_t index,	struct pcie_iatu_cfg *iatu_ob_cfg)
{
	if (!iatu_ob_cfg)
		return RL_BADARG;

	int32_t ret = pcie_check_iatu_region_available(data, DW_PCIE_OUTBOUND, index);

	if (ret != RL_OK)
		return ret;

	volatile struct pcie_ctrl_pf0_atu_cap_iatu_register *iatu_base = cfg->iatu_base[index];

	uint64_t limit = iatu_ob_cfg->cpu_addr + iatu_ob_cfg->size - 1;

	/* limit address */
	if (iatu_ob_cfg->size <= SZ_4G) {
		iatu_base->pf0_atu_cap_iatu_region_ctrl_1_off_outbound.increase_region_size = 0;
		iatu_base->pf0_atu_cap_iatu_limit_addr_off_outbound.val = LOWER_32_BITS(limit);
		iatu_base->pf0_atu_cap_iatu_uppr_limit_addr_off_outbound.val = 0;
	} else {
		iatu_base->pf0_atu_cap_iatu_region_ctrl_1_off_outbound.increase_region_size = 1;
		iatu_base->pf0_atu_cap_iatu_limit_addr_off_outbound.val = LOWER_32_BITS(limit);
		iatu_base->pf0_atu_cap_iatu_uppr_limit_addr_off_outbound.val = UPPER_32_BITS(limit);
	}

	/* lower base address */
	iatu_base->pf0_atu_cap_iatu_lwr_base_addr_off_outbound.val =
		LOWER_32_BITS(iatu_ob_cfg->cpu_addr);
	/* upper base address */
	iatu_base->pf0_atu_cap_iatu_upper_base_addr_off_outbound.val =
		UPPER_32_BITS(iatu_ob_cfg->cpu_addr);

	/* lower target address */
	iatu_base->pf0_atu_cap_iatu_lwr_target_addr_off_outbound.val =
		LOWER_32_BITS(iatu_ob_cfg->pci_addr);
	/* upper target address */
	iatu_base->pf0_atu_cap_iatu_upper_target_addr_off_outbound.val =
		UPPER_32_BITS(iatu_ob_cfg->pci_addr);

	/* ATU memory type */
	iatu_base->pf0_atu_cap_iatu_region_ctrl_1_off_outbound.type_ = iatu_ob_cfg->type;

	/* VF Active */
	if (iatu_ob_cfg->vf_number & VF_MATCH) {
		iatu_base->pf0_atu_cap_iatu_region_ctrl_3_off_outbound.vf_active = 1;
		iatu_base->pf0_atu_cap_iatu_region_ctrl_3_off_outbound.vf_number = iatu_ob_cfg->vf_number & VF_NUM_MASK;
	}

	/* ATU enable */
	iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_outbound.region_en = 1;

	ret = pcie_iatu_assign_region(data, DW_PCIE_OUTBOUND, index);

	return ret;
}

int32_t pcie_set_iatu_inbound(const struct dw_pcie_config *cfg,	struct dw_pcie_drv *data,
							  struct pcie_bar_info *bar_info, struct pcie_iatu_cfg *iatu_ib_cfg,
							  uint32_t match_mode)
{
	struct pcie_iatu_info *iatu_info = data->iatu_info;
	int32_t index;
	int32_t ret = RL_ERROR;

	index = pcie_find_iatu_free_region(data, DW_PCIE_INBOUND);

	if (index >= 0 && index < iatu_info->iatu_num_ib_regions) {
		if (match_mode == BAR_MATCH_MODE) {
			if (!bar_info)
				return ret;

			ret = pcie_iatu_inbound_config(cfg, data, index, bar_info, NULL, match_mode);
		} else if (match_mode == ADDRESS_MATCH_MODE) {
			if (!iatu_ib_cfg)
				return ret;

			ret = pcie_iatu_inbound_config(cfg, data, index, NULL, iatu_ib_cfg, match_mode);
		}
	}

	return ret;
}

int32_t pcie_set_iatu_outbound(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data,
							   struct pcie_iatu_cfg *iatu_ob_cfg, int8_t *index)
{
	struct pcie_iatu_info *iatu_info = data->iatu_info;
	int32_t ret = RL_ERROR;

	*index = pcie_find_iatu_free_region(data, DW_PCIE_OUTBOUND);

	if (*index >= 0 && *index < iatu_info->iatu_num_ob_regions) {
		ret = pcie_iatu_outbound_config(cfg, data, *index, iatu_ob_cfg);
	}

	return ret;
}

int32_t pcie_iatu_disable_region(struct pcie_epc *dw_pcie_epc, enum dw_pcie_iatu_direction direction,
								 uint32_t index)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_pf0_atu_cap_iatu_register *iatu_region = cfg->iatu_base[index];
	struct dw_pcie_drv *data = dw_pcie_epc->drv;

	if (direction == DW_PCIE_INBOUND) {
		iatu_region->pf0_atu_cap_iatu_region_ctrl_1_off_inbound.val = 0;
		iatu_region->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.val = 0;
		iatu_region->pf0_atu_cap_iatu_region_ctrl_3_off_inbound.val = 0;
		data->iatu_info->iatu_ib_regions_mask &= ~(0x1 << index);
		pcie_dbg_log("Disable inbound region %d\n", index);
	} else if (direction == DW_PCIE_OUTBOUND) {
		iatu_region->pf0_atu_cap_iatu_region_ctrl_1_off_outbound.val = 0;
		iatu_region->pf0_atu_cap_iatu_region_ctrl_2_off_outbound.val = 0;
		iatu_region->pf0_atu_cap_iatu_region_ctrl_3_off_outbound.val = 0;
		data->iatu_info->iatu_ob_regions_mask &= ~(0x1 << index);
		pcie_dbg_log("Disable outbound region %d\n", index);
	} else {
		pcie_dbg_log("%s: Enter appropriate direction value\n", __func__);
		return RL_BADARG;
	}

	return RL_OK;
}

int32_t pcie_iatu_disable_match_mode_region(struct pcie_epc *dw_pcie_epc, uint32_t match_mode)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	struct dw_pcie_drv *data = dw_pcie_epc->drv;
	uint64_t num_regions;
	uint64_t regions_mask;
	uint32_t i;
	int32_t ret = RL_ERROR;

	num_regions = data->iatu_info->iatu_num_ib_regions;
	regions_mask = data->iatu_info->iatu_ib_regions_mask;

	for (i = 0; i < num_regions; i++) {
		if ((regions_mask & (0x1 << i)) == 0)
			continue;

		volatile struct pcie_ctrl_pf0_atu_cap_iatu_register *iatu_base = cfg->iatu_base[i];

		switch (match_mode) {
		case ADDRESS_MATCH_MODE:
			if (!iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.match_mode &&
				!iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.vf_match_en &&
				!iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.vfbar_match_mode_en)
				ret = pcie_iatu_disable_region(dw_pcie_epc, DW_PCIE_INBOUND, i);
			break;
		case BAR_MATCH_MODE:
			if (iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.match_mode)
				ret = pcie_iatu_disable_region(dw_pcie_epc, DW_PCIE_INBOUND, i);
			break;
		case VF_MATCH_MODE:
			if (iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.vf_match_en)
				ret = pcie_iatu_disable_region(dw_pcie_epc, DW_PCIE_INBOUND, i);
			break;
		case VF_BAR_MATCH_MODE:
			if (iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.vfbar_match_mode_en)
				ret = pcie_iatu_disable_region(dw_pcie_epc, DW_PCIE_INBOUND, i);
			break;
		default:
			break;
		}
	}

	return ret;
}

int32_t pcie_find_iatu_region_by_bar_num(struct pcie_epc *dw_pcie_epc, enum pcie_bar_num bar)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	struct dw_pcie_drv *data = dw_pcie_epc->drv;
	union pcie_ctrl_pf0_atu_cap_iatu_region_ctrl_2_off_inbound reg;
	uint64_t num_regions, regions_mask;
	uint32_t i;

	num_regions = data->iatu_info->iatu_num_ib_regions;
	regions_mask = data->iatu_info->iatu_ib_regions_mask;

	for (i = 0; i < num_regions; i++) {
		if ((regions_mask & (0x1 << i)) == 0)
			continue;

		reg.val = cfg->iatu_base[i]->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.val;

		if (bar >= VF_BAR0 && bar <= VF_BAR5) {
			if (reg.vfbar_match_mode_en && reg.bar_num == (bar - VF_BAR0))
				return i;
		} else if (bar >= BAR0 && bar <= BAR5) {
			if (reg.match_mode && reg.bar_num == bar)
				return i;
		}
	}

	return RL_NOT_FOUND;
}

int32_t pcie_reconfigure_bar_match_mode(struct pcie_epc *dw_pcie_epc, enum pcie_bar_num bar_num,
										uint64_t target_addr, uint64_t size)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	struct dw_pcie_drv *data = dw_pcie_epc->drv;
	struct pcie_bar_info bar_info;
	uint32_t index;
	int32_t ret = RL_ERROR;

	if (bar_num < BAR0 || bar_num == BAR5 || bar_num > VF_BAR4)
		return ret;

	pcie_dbg_log("Set Inbound iATU\n"
				"BAR num: %d\n"
				"target address: 0x%llx\n"
				"size : 0x%llx\n", bar_num, target_addr, size);

	bar_info = data->bar_info[bar_num];

	if (size) {
		bar_info.size = size;
	} else {
		pcie_dbg_log("%s: The size of bar_info[%d] will be applied.\n", __func__, bar_num);
	}
	bar_info.phys_addr = target_addr;

	index = pcie_find_iatu_region_by_bar_num(dw_pcie_epc, bar_num);
	if (index != RL_NOT_FOUND)
		pcie_iatu_disable_region(dw_pcie_epc, DW_PCIE_INBOUND, index);

	ret = pcie_set_iatu_inbound(cfg, data, &bar_info, NULL, BAR_MATCH_MODE);
	if (ret) {
		pcie_err_log("Setting iatu for BAR%d failed\n", bar_num);
		return ret;
	}

	/* NOTE: If pcie_set_iatu_inbound fails, the BAR mask will not be changed. */
	if (size) {
		if (bar_info.bar_type & BAR_MASK_PROGRAMMABLE)
			pcie_set_programmable_bar_size(cfg, &bar_info);
		else if (bar_info.bar_type & BAR_MASK_RESIZABLE)
			pcie_change_resizable_bar_size(dw_pcie_epc, bar_num, size);
	}

	data->bar_info[bar_num] = bar_info;

	return ret;
}

int32_t pcie_configure_inbound_address_match_mode(struct pcie_epc *dw_pcie_epc, uint64_t pci_addr,
												  uint64_t cpu_addr, uint64_t size,
												  bool vf_match, uint32_t vf_num)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	struct dw_pcie_drv *data = dw_pcie_epc->drv;
	struct pcie_iatu_cfg iatu_ib_cfg;
	int32_t ret;

	pcie_dbg_log("Set Inbound iATU\n"
				"base address: 0x%llx\n"
				"target address: 0x%llx\n"
				"size : 0x%llx\n"
				"vf_active:%d vf_num:%d\n", pci_addr, cpu_addr, size, vf_match, vf_num);

	iatu_ib_cfg.pci_addr = pci_addr;
	iatu_ib_cfg.cpu_addr = cpu_addr;
	iatu_ib_cfg.size = size;
	iatu_ib_cfg.type = ATU_TYPE_MEM;
	if (vf_match) {
		iatu_ib_cfg.vf_number = VF_MATCH | vf_num;
	} else {
		iatu_ib_cfg.vf_number = 0;
	}

	ret = pcie_set_iatu_inbound(cfg, data, NULL, &iatu_ib_cfg, ADDRESS_MATCH_MODE);

	return ret;
}

int32_t pcie_configure_outbound_address_match_mode(struct pcie_epc *dw_pcie_epc, uint64_t cpu_addr,
												   uint64_t pci_addr, uint64_t size, int8_t *index,
												   bool vf_match, uint32_t vf_num)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	struct dw_pcie_drv *data = dw_pcie_epc->drv;
	struct pcie_iatu_cfg iatu_ob_cfg;
	int32_t ret;

	pcie_dbg_log("Set Outbound iATU\n"
				"base address: 0x%llx\n"
				"target address: 0x%llx\n"
				"size : 0x%llx\n"
				"vf_active:%d vf_num:%d\n", cpu_addr, pci_addr, size, vf_match, vf_num);

	iatu_ob_cfg.pci_addr = pci_addr;
	iatu_ob_cfg.cpu_addr = cpu_addr;
	iatu_ob_cfg.size = size;
	iatu_ob_cfg.type = ATU_TYPE_MEM;
	if (vf_match) {
		iatu_ob_cfg.vf_number = VF_MATCH | vf_num;
	} else {
		iatu_ob_cfg.vf_number = 0;
	}

	ret = pcie_set_iatu_outbound(cfg, data, &iatu_ob_cfg, index);

	return ret;
}

int32_t pcie_get_iatu_ib_info(struct pcie_epc *dw_pcie_epc, uint32_t index, struct iatu_region_info *info)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	struct dw_pcie_drv *data = dw_pcie_epc->drv;
	uint8_t iatu_num_regions = data->iatu_info->iatu_num_ib_regions;

	if (index > iatu_num_regions) {
		return RL_BADARG;
	}

	volatile struct pcie_ctrl_pf0_atu_cap_iatu_register *iatu_base = cfg->iatu_base[index];

	if (iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.region_en == 0) {
		return RL_NOT_FOUND;
	}

	info->region_num = index;
	info->target_addr = ((uint64_t)iatu_base->pf0_atu_cap_iatu_upper_target_addr_off_inbound.val << 32) +
					iatu_base->pf0_atu_cap_iatu_lwr_target_addr_off_inbound.val;

	if (iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.match_mode) {
		info->match_mode = BAR_MATCH_MODE;
		info->bar_num = iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.bar_num;

	} else if (iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.vfbar_match_mode_en) {
		info->match_mode = VF_BAR_MATCH_MODE;
		info->bar_num = iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.bar_num + VF_BAR0;
	} else {
		if (iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_inbound.vf_match_en) {
			info->match_mode = VF_MATCH_MODE;
			info->vf_num = iatu_base->pf0_atu_cap_iatu_region_ctrl_3_off_inbound.vf_number;
		} else {
			info->match_mode = ADDRESS_MATCH_MODE;
		}

		info->base_addr = ((uint64_t)iatu_base->pf0_atu_cap_iatu_upper_base_addr_off_inbound.val << 32) +
							iatu_base->pf0_atu_cap_iatu_lwr_base_addr_off_inbound.val;
		info->limit = ((uint64_t)iatu_base->pf0_atu_cap_iatu_uppr_limit_addr_off_inbound.val << 32) +
						iatu_base->pf0_atu_cap_iatu_limit_addr_off_inbound.val;
		info->incr = iatu_base->pf0_atu_cap_iatu_region_ctrl_1_off_inbound.increase_region_size;
	}

	return index;
}

int32_t pcie_get_iatu_ob_info(struct pcie_epc *dw_pcie_epc, uint32_t index, struct iatu_region_info *info)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	struct dw_pcie_drv *data = dw_pcie_epc->drv;
	uint8_t iatu_num_regions = data->iatu_info->iatu_num_ob_regions;

	if (index > iatu_num_regions) {
		return RL_BADARG;
	}

	volatile struct pcie_ctrl_pf0_atu_cap_iatu_register *iatu_base = cfg->iatu_base[index];

	if (iatu_base->pf0_atu_cap_iatu_region_ctrl_2_off_outbound.region_en == 0) {
		return RL_NOT_FOUND;
	}

	info->region_num = index;
	info->target_addr = ((uint64_t)iatu_base->pf0_atu_cap_iatu_upper_target_addr_off_outbound.val << 32) +
					iatu_base->pf0_atu_cap_iatu_lwr_target_addr_off_outbound.val;

	info->base_addr = ((uint64_t)iatu_base->pf0_atu_cap_iatu_upper_base_addr_off_outbound.val << 32) +
							iatu_base->pf0_atu_cap_iatu_lwr_base_addr_off_outbound.val;
	info->limit = ((uint64_t)iatu_base->pf0_atu_cap_iatu_uppr_limit_addr_off_outbound.val << 32) +
						iatu_base->pf0_atu_cap_iatu_limit_addr_off_outbound.val;
	info->incr = iatu_base->pf0_atu_cap_iatu_region_ctrl_1_off_outbound.increase_region_size;

	info->vf_num = iatu_base->pf0_atu_cap_iatu_region_ctrl_3_off_outbound.val;

	return index;
}
