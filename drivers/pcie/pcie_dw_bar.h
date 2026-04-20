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

/* Base Address Register */
#define BAR_MEM_IO_MASK	0x01
#define BAR_MEM			0x00
#define BAR_IO			0x01
#define BAR_TYPE_MASK	0x06
#define BAR_TYPE_32		0x00	/* 32 bit address */
#define BAR_TYPE_64		0x04	/* 64 bit address */
#define BAR_PREFETCH	0x08	/* prefetchable */

/* PF0_RESBAR_CAP_RESBAR_CAP_REG_0_REG (0x4BC) */
/* PF0_VF_RESBAR_CAP_RESBAR_CAP_REG_0_REG (0x4FC) */
#define RESBAR_CAP_MAX_SIZE_BAR0 (0x4000000000ULL) /* 256G */
#define RESBAR_CAP_MAX_SIZE_VFBAR0 (0x400000000ULL) /* 16G */
#define RESBAR_CAP_MIN_SIZE (0x100000ULL) /* 1M */
#define RESBAR_CAP_REG_RESERVED 4
#define RESBAR_CAP_REG_1MB 0x10
#define RESBAR_CAP_REG_2MB 0x30
#define RESBAR_CAP_REG_4MB 0x70
#define RESBAR_CAP_REG_8MB 0xF0
#define RESBAR_CAP_REG_16MB 0x1F0
#define RESBAR_CAP_REG_32MB 0x3F0
#define RESBAR_CAP_REG_64MB 0x7F0
#define RESBAR_CAP_REG_128MB 0xFF0
#define RESBAR_CAP_REG_256MB 0x1FF0
#define RESBAR_CAP_REG_512MB 0x3FF0
#define RESBAR_CAP_REG_1GB 0x7FF0
#define RESBAR_CAP_REG_2GB 0xFFF0
#define RESBAR_CAP_REG_4GB 0x1FFF0
#define RESBAR_CAP_REG_8GB 0x3FFF0
#define RESBAR_CAP_REG_16GB 0x7FFF0
#define RESBAR_CAP_REG_32GB 0xFFFF0
#define RESBAR_CAP_REG_64GB 0x1FFFF0
#define RESBAR_CAP_REG_128GB 0x3FFFF0
#define RESBAR_CAP_REG_256GB 0x7FFFF0

/* PF0_RESBAR_CAP_RESBAR_CTRL_REG_0_REG (0x4C0) */
/* PF0_VF_RESBAR_CAP_RESBAR_CTRL_REG_0_REG (0x500) */
#define RESBAR_CTRL_REG_1MB 0x0
#define RESBAR_CTRL_REG_2MB 0x1
#define RESBAR_CTRL_REG_4MB 0x2
#define RESBAR_CTRL_REG_8MB 0x3
#define RESBAR_CTRL_REG_16MB 0x4
#define RESBAR_CTRL_REG_32MB 0x5
#define RESBAR_CTRL_REG_64MB 0x6
#define RESBAR_CTRL_REG_128MB 0x7
#define RESBAR_CTRL_REG_256MB 0x8
#define RESBAR_CTRL_REG_512MB 0x9
#define RESBAR_CTRL_REG_1GB 0xA
#define RESBAR_CTRL_REG_2GB 0xB
#define RESBAR_CTRL_REG_4GB 0xC
#define RESBAR_CTRL_REG_8GB 0xD
#define RESBAR_CTRL_REG_16GB 0xE
#define RESBAR_CTRL_REG_32GB 0xF
#define RESBAR_CTRL_REG_64GB 0x10
#define RESBAR_CTRL_REG_128GB 0x11
#define RESBAR_CTRL_REG_256GB 0x12

/* BAR Mask Register */
#define DBI2_BAR_ENABLED 0x1

enum pcie_bar_num {
	BAR0 = 0x0,
	BAR1 = 0x1,
	BAR2 = 0x2,
	BAR3 = 0x3,
	BAR4 = 0x4,
	BAR5 = 0x5,
	BAR_MAX = BAR5,
	VF_BAR0 = 0x6,
	VF_BAR1 = 0x7,
	VF_BAR2 = 0x8,
	VF_BAR3 = 0x9,
	VF_BAR4 = 0xA,
	VF_BAR5 = 0xB,
	VF_BAR_MAX = VF_BAR5
};

enum pcie_bar_state {
	BAR_ENABLED = 0,
	BAR_DISABLED,
	BAR_NOT_USED
};

enum pcie_bar_type {
	/*
	 * BAR_TYPE_MEM = 0x00,
	 * BAR_TYPE_IO = 0x01,
	 * BAR_TYPE_32 = 0x02,
	 * BAR_TYPE_64 = 0x04,
	 * BAR_TYPE_PREFETCH = 0x8,
	 */
	BAR_MASK_FIXED = 0x10,
	BAR_MASK_PROGRAMMABLE = 0x20,
	BAR_MASK_RESIZABLE = 0x40
};

struct pcie_bar_info {
	enum pcie_bar_num num;
	uint64_t phys_addr;
	uint64_t size;
	uint32_t bar_type;
	uint32_t flags;
};

void pcie_set_programmable_bar_size(const struct dw_pcie_config *cfg,
									struct pcie_bar_info *bar_info);
void pcie_set_resizable_bar_size(const struct dw_pcie_config *cfg, enum pcie_bar_num bar,
								 uint64_t size);
void pcie_change_resizable_bar_size(struct pcie_epc *dw_pcie_epc, enum pcie_bar_num, uint64_t size);
uint8_t pcie_get_num_valid_bar(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data);
void pcie_get_bar_info(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data);
int32_t pcie_set_bar(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data,
					 struct pcie_bar_info *bar_info);
int32_t pcie_load_bar_info(struct pcie_epc *dw_pcie_epc, enum pcie_bar_num bar_num,
						   struct pcie_bar_info *bar_info);
void pcie_get_vfbar_info(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data);
void pcie_clear_bar(struct pcie_epc *dw_pcie_epc);
