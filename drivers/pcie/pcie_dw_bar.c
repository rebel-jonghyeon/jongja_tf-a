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
#include "pcie_dw_bar.h"
#include "pcie_dw_iatu.h"

#define PCIE_DEBUG_ON 1
#define PCIE_ERR_ON 1
#include "pcie_log.h"

uint8_t pcie_get_num_valid_bar(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data)
{
	volatile uint32_t *bar_ptr = (uint32_t *)&cfg->dbi_base->pf0_type0_hdr_bar0_reg;
	uint32_t i, temp;
	uint8_t num_valid_bar = 0;

	for (i = 0; i <= BAR5; i++) {
		if (bar_ptr[i] & BAR_TYPE_64) {
			num_valid_bar++;
			continue;
		} else {
			temp = bar_ptr[i];

			bar_ptr[i] = 0xFFFFFFFF;

			if (bar_ptr[i] == 0x0) {
				data->bar_info[i].flags = BAR_NOT_USED;
				continue;
			}

			bar_ptr[i] = temp;

			num_valid_bar++;
		}
	}

	return num_valid_bar;
}

void pcie_get_bar_info(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data)
{
	uint32_t *bar_ptr = (uint32_t *)&cfg->dbi_base->pf0_type0_hdr_bar0_reg;
	uint32_t bar, i;

	for (i = 0; i <= BAR5; i++) {
		if (data->bar_info[i].flags == BAR_NOT_USED)
			continue;

		bar = bar_ptr[i];
		data->bar_info[i].bar_type &= ~(BAR_MEM_IO_MASK | BAR_TYPE_MASK | BAR_PREFETCH);
		data->bar_info[i].bar_type |= bar & (BAR_MEM_IO_MASK | BAR_TYPE_MASK | BAR_PREFETCH);
	}
}

void pcie_get_vfbar_info(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data)
{
	uint32_t *bar_ptr = (uint32_t *)&cfg->dbi_base->pf0_sriov_cap_sriov_bar0_reg;
	uint32_t bar, i;

	for (i = VF_BAR0; i <= VF_BAR5; i++) {
		if (data->bar_info[i].flags == BAR_NOT_USED)
			continue;

		bar = bar_ptr[i - VF_BAR0];
		data->bar_info[i].bar_type &= ~(BAR_TYPE_MASK | BAR_PREFETCH);
		data->bar_info[i].bar_type |= bar & (BAR_TYPE_MASK | BAR_PREFETCH);
	}
}

void pcie_set_resizable_bar_size(const struct dw_pcie_config *cfg, enum pcie_bar_num bar,
								 uint64_t size)
{
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;
	uint32_t size_val = 0;

	if (bar != BAR0 && bar != VF_BAR0) {
		pcie_err_log("ERR: BAR%d is not resizable BAR\n", bar);
		return;
	}

	if (size < RESBAR_CAP_MIN_SIZE) {
		pcie_err_log("ERR: Entered size gets out of resizable BAR size capability\n");
		pcie_err_log("Skip setting resizable BAR size\n");
		return;
	}

	switch (size) {
	case SZ_1M:
		size_val = RESBAR_CAP_REG_1MB; break;
	case SZ_2M:
		size_val = RESBAR_CAP_REG_2MB; break;
	case SZ_4M:
		size_val = RESBAR_CAP_REG_4MB; break;
	case SZ_8M:
		size_val = RESBAR_CAP_REG_8MB; break;
	case SZ_16M:
		size_val = RESBAR_CAP_REG_16MB; break;
	case SZ_32M:
		size_val = RESBAR_CAP_REG_32MB; break;
	case SZ_64M:
		size_val = RESBAR_CAP_REG_64MB; break;
	case SZ_128M:
		size_val = RESBAR_CAP_REG_128MB; break;
	case SZ_256M:
		size_val = RESBAR_CAP_REG_256MB; break;
	case SZ_512M:
		size_val = RESBAR_CAP_REG_512MB; break;
	case SZ_1G:
		size_val = RESBAR_CAP_REG_1GB; break;
	case SZ_2G:
		size_val = RESBAR_CAP_REG_2GB; break;
	case SZ_4G:
		size_val = RESBAR_CAP_REG_4GB; break;
	case SZ_8G:
		size_val = RESBAR_CAP_REG_8GB; break;
	case SZ_16G:
		size_val = RESBAR_CAP_REG_16GB; break;
	case SZ_32G:
		size_val = RESBAR_CAP_REG_32GB; break;
	case SZ_64G:
		size_val = RESBAR_CAP_REG_64GB; break;
	case SZ_128G:
		size_val = RESBAR_CAP_REG_128GB; break;
	case SZ_256G:
		size_val = RESBAR_CAP_REG_256GB; break;
	default:
		size_val = 0;
		break;
	}

	if (size_val == 0) {
		pcie_err_log("ERR: Invalid resizable BAR size\n");
		pcie_err_log("Skip setting resizable BAR size\n");
		return;
	}

	if (bar == BAR0)
		dbi_base->pf0_resbar_cap_resbar_cap_reg_0_reg.val = size_val;
	else if (bar == VF_BAR0)
		dbi_base->pf0_vf_resbar_cap_vf_resbar_cap_reg_0_reg.val = size_val;
}

void pcie_change_resizable_bar_size(struct pcie_epc *dw_pcie_epc, enum pcie_bar_num bar,
									uint64_t size)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	volatile struct pcie_ctrl_register *dbi_base = cfg->dbi_base;
	uint32_t size_val = 0;

	if (bar != BAR0 && bar != VF_BAR0) {
		pcie_err_log("ERR: BAR%d is not resizable BAR\n", bar);
		return;
	}

	switch (size) {
	case SZ_1M:
		size_val = RESBAR_CTRL_REG_1MB; break;
	case SZ_2M:
		size_val = RESBAR_CTRL_REG_2MB; break;
	case SZ_4M:
		size_val = RESBAR_CTRL_REG_4MB; break;
	case SZ_8M:
		size_val = RESBAR_CTRL_REG_8MB; break;
	case SZ_16M:
		size_val = RESBAR_CTRL_REG_16MB; break;
	case SZ_32M:
		size_val = RESBAR_CTRL_REG_32MB; break;
	case SZ_64M:
		size_val = RESBAR_CTRL_REG_64MB; break;
	case SZ_128M:
		size_val = RESBAR_CTRL_REG_128MB; break;
	case SZ_256M:
		size_val = RESBAR_CTRL_REG_256MB; break;
	case SZ_512M:
		size_val = RESBAR_CTRL_REG_512MB; break;
	case SZ_1G:
		size_val = RESBAR_CTRL_REG_1GB; break;
	case SZ_2G:
		size_val = RESBAR_CTRL_REG_2GB; break;
	case SZ_4G:
		size_val = RESBAR_CTRL_REG_4GB; break;
	case SZ_8G:
		size_val = RESBAR_CTRL_REG_8GB; break;
	case SZ_16G:
		size_val = RESBAR_CTRL_REG_16GB; break;
	case SZ_32G:
		size_val = RESBAR_CTRL_REG_32GB; break;
	case SZ_64G:
		size_val = RESBAR_CTRL_REG_64GB; break;
	case SZ_128G:
		size_val = RESBAR_CTRL_REG_128GB; break;
	case SZ_256G:
		size_val = RESBAR_CTRL_REG_256GB; break;
	default:
		size_val = 0;
		break;
	}

	uint32_t cap_reg;

	if (bar == BAR0) {
		cap_reg = dbi_base->pf0_resbar_cap_resbar_cap_reg_0_reg.val;

		if (cap_reg & (1 << (size_val + RESBAR_CAP_REG_RESERVED)))
			dbi_base->pf0_resbar_cap_resbar_ctrl_reg_0_reg.resbar_ctrl_reg_bar_size = size_val;
		else {
			pcie_err_log("ERR: Entered size gets out of resizable BAR size capability\n");
			return;
		}
	} else if (bar == VF_BAR0) {
		cap_reg = dbi_base->pf0_vf_resbar_cap_vf_resbar_cap_reg_0_reg.val;

		if (cap_reg & (1 << (size_val + RESBAR_CAP_REG_RESERVED)))
			dbi_base->pf0_vf_resbar_cap_vf_resbar_ctrl_reg_0_reg.vf_resbar_ctrl_reg_bar_size =
				size_val;
		else {
			pcie_err_log("ERR: Entered size gets out of resizable BAR size capability\n");
			return;
		}
	}
}

void pcie_set_programmable_bar_size(const struct dw_pcie_config *cfg,
									struct pcie_bar_info *bar_info)
{
	uint32_t *bar_mask_ptr;
	int8_t bar_ptr_index;

	if (bar_info->num >= VF_BAR0) {
		bar_mask_ptr = (uint32_t *)&cfg->dbi2_base->pf0_sriov_cap_dbi2_sriov_bar2_mask_reg;
		bar_ptr_index = bar_info->num - VF_BAR2;
	} else {
		bar_mask_ptr = (uint32_t *)&cfg->dbi2_base->pf0_type0_hdr_dbi2_bar0_mask_reg;
		bar_ptr_index = bar_info->num;
	}

	if (bar_ptr_index < 0 || bar_ptr_index > 5) {
		pcie_err_log("%s Invalid BAR number\n", __func__);
		return;
	}

	if ((bar_info->bar_type & BAR_TYPE_MASK) == BAR_TYPE_64)
		bar_mask_ptr[bar_ptr_index + 1] &= ~DBI2_BAR_ENABLED;

	if (bar_info->size < SZ_4K) {
		pcie_dbg_log("%s: warning: minimum iATU region size is 4KB\n", __func__);
		pcie_dbg_log("%s:          BAR size will be forced to 4KB\n", __func__);
		bar_info->size = SZ_4K;
	}

	if (bar_info->bar_type & BAR_MASK_PROGRAMMABLE) {
		bar_mask_ptr[bar_ptr_index] = LOWER_32_BITS(bar_info->size - 1);

		if ((bar_info->bar_type & BAR_TYPE_MASK) == BAR_TYPE_64) {
			bar_mask_ptr[bar_ptr_index + 1] = UPPER_32_BITS(bar_info->size - 1);
		}
	}
}

int32_t pcie_set_bar(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data,
					 struct pcie_bar_info *bar_info)
{
	int32_t ret;

	if (bar_info->bar_type & BAR_MASK_PROGRAMMABLE)
		pcie_set_programmable_bar_size(cfg, bar_info);

	if (bar_info->num == BAR5 || bar_info->num == VF_BAR5) {
		pcie_dbg_log("iATU inbound setting for BAR5/VFBAR5 is passed\n");
	} else {
		ret = pcie_set_iatu_inbound(cfg, data, bar_info, NULL, BAR_MATCH_MODE);
		if (ret) {
			pcie_err_log("ERR: Fail to set iATU inbound for BAR%d\n", bar_info->num);
			return ret;
		}
	}

	return RL_OK;
}

int32_t pcie_load_bar_info(struct pcie_epc *dw_pcie_epc, enum pcie_bar_num bar_num,
						   struct pcie_bar_info *bar_info)
{
	struct dw_pcie_drv *data = dw_pcie_epc->drv;
	struct pcie_bar_info *info = data->bar_info;
	int32_t i;

	for (i = 0; i <= VF_BAR5; i++) {
		if (info[i].num != bar_num)
			continue;

		bar_info->num = info[i].num;
		bar_info->phys_addr = info[i].phys_addr;
		bar_info->size = info[i].size;
		bar_info->bar_type = info[i].bar_type;
		bar_info->flags = info[i].flags;

		return RL_OK;
	}

	return RL_ERROR;
}

void pcie_clear_bar(struct pcie_epc *dw_pcie_epc)
{
	const struct dw_pcie_config *cfg = dw_pcie_epc->cfg;
	uint32_t *bar_ptr = (uint32_t *)&cfg->dbi_base->pf0_type0_hdr_bar0_reg;
	uint32_t i;

	for (i = BAR0; i <= BAR5; i++) {
		bar_ptr[i] = 0x0;
	}

	bar_ptr = (uint32_t *)&cfg->dbi_base->pf0_sriov_cap_sriov_bar2_reg;
	for (i = VF_BAR0; i <= VF_BAR5; i++) {
		bar_ptr[i] = 0x0;
	}
}
