/*
 * Copyright (c) 2023-2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#define SMMU_SMMUEN			(1)
#define SMMU_SMMUEN_MASK	(1)
#define SMMU_PRIQEN			(2)
#define SMMU_PRIQEN_MASK	(2)
#define SMMU_EVENTQEN		(4)
#define SMMU_EVENTQEN_MASK	(4)
#define SMMU_CMDQEN			(8)
#define SMMU_CMDQEN_MASK	(8)
#define SMMU_QEN_MASK		(0x0c)

#define SMMU_GBPA_SHCFG_USEINCOMING	(0x1 << 12)
#define SMMU_GBPA_SHCFG_INNER		(0x3 << 12)
#define SMMU_GBPA_SHCFG_MAKS		(0x3 << 12)
#define SMMU_GBPA_ALLOCCFG			(0xE << 8)
#define SMMU_GBPA_COMPLETE			(0x80000000)
#define SMMU_GBPA_COMPLETE_MASK		(0x80000000)

#define EVENTQ_BASE_ADDR		(SMMU_EVENTQ_BASE_ADDR)
#define CMDQ_BASE_ADDR			(SMMU_EVENTQ_BASE_ADDR + (SMMU_EVENT_SIZE * Q_SIZE))
#define PRIQ_BASE_ADDR			(CMDQ_BASE_ADDR + (SMMU_CMD_SIZE * Q_SIZE))
#define Q_LOG2SIZE				(10)
#define Q_SIZE					(2 << Q_LOG2SIZE)
#define SMMU_EVENT_SIZE			(32)
#define SMMU_CMD_SIZE			(16)

#define CD_START_OFFSET_ADDR		(0x00001000)
#define CD_SIZE						(0x00000040)
#define CD_SIZE_PER_EACH_STE		(0x00001000)
#define CD_BASE_ADDR(sid, ssid)		((struct str_cd *)(uint64_t)(SMMU_STE_BASE_ADDR + \
									CD_START_OFFSET_ADDR + CD_SIZE_PER_EACH_STE * (sid) + \
									0x40 * (ssid)))
#define CD_BASE_ADDR3(sid, ssid)	((struct str_cd *)(uint64_t)(SMMU_STE_BASE_ADDR + \
									CD_START_OFFSET_ADDR + CD_SIZE_PER_EACH_STE * (sid) + \
									0x40 * (ssid) + CHIPLET3_BASE_ADDRESS))
#define CD_MAX_NUM					(0)
#define CD_MAX						(CD_MAX_NUM << 27)
#define CD_T0SZ						0x17

#define CD_MAIR_VALUE				(0xFFFFFF00)

#define CD_VALID					(0x80000000)
#define CD_EPD1_DISABLE				(0x1 << 30)
#define CD_R						(0x1 << 13)
#define CD_AA64						(0x1 << 9)
#define CD_TBI0						(0x1 << 6)
#define CD_AFF						(0x1 << 3)
#define CD_IPS_40BIT				(0x2 << 0)

#define STE_SIZE					(0x40)
#define STE_ADDR(sid)				((struct str_ste *)(uint64_t)(SMMU_STE_BASE_ADDR + \
									STE_SIZE * (sid)))
#define STE_ADDR3(sid)				((struct str_ste *)(uint64_t)(SMMU_STE_BASE_ADDR + \
									CHIPLET3_BASE_ADDRESS + STE_SIZE * (sid)))

#define STE_CONFIG_STAGE1_VALID		(0xB)
#define STE_SID						(0x11)
#define STE_S1_DSS					(0x2)
#define STE_STRW_EL2_E2H			(0x80000000)
#define STE_S1DSS_SS0				(0x2)
#define STE_SHCFG_USE_INCOMING		(0x1000)

#define STRTAB_CFG_FMT			(0)
#define STRTAB_CFG_SPLIT		(0x6 << 6)
#define STRTAB_CFG_LOG2SIZE		(0x5)
#define STRTAB_CFG_VALUE		(STRTAB_CFG_FMT | STRTAB_CFG_SPLIT | STRTAB_CFG_LOG2SIZE)

#define DESCRIPTOR_ADDR_L0(x)	((x) + 0x0000)
#define DESCRIPTOR_ADDR_L1(x)	((x) + 0x1000)
#define CALC_DESCRIPTOR_ADDR(x, y)	(DESCRIPTOR_ADDR_L1(x) + 0x1000 * (y))

#define PT_BLOCK_OFFSET_L1(x)	((((uint64_t)(x) >> 30) & 0x1ff) * 8)
#define PT_BLOCK_OFFSET_L2(x)	((((uint64_t)(x) >> 21) & 0x1ff) * 8)
#define PT_PAGE_OFFSET_L3(x)	((((uint64_t)(x) >> 12) & 0x1ff) * 8)

#define NUM_OF_1G_REGION		1
#define NUM_OF_2M_REGION		4
#define NUM_OF_4K_REGION		1

#define PT_TABLE_ATTR			(0x003)
#define PT_BLOCK_ATTR			(0x401)
#define PT_PAGE_ATTR			(0x403)

#define BLOCK_SIZE_512G			ULL(0x8000000000)
#define BLOCK_SIZE_1G			ULL(0x40000000)
#define BLOCK_SIZE_2M			ULL(0x200000)
#define PAGE_SIZE_4K			ULL(0x1000)
#define BLOCK_SIZE_1G_MASK		ULL(0xFFFFC0000000)
#define BLOCK_SIZE_2M_MASK		ULL(0xFFFFFFE00000)
#define TABLE_SIZE_4K			ULL(0x1000)
#define TABLE_SIZE_4K_BY_64BIT	ULL(0x200)

#define CALC_NUM_OF_512G(x)		(((x) >> 39) + 1)
#define CALC_NUM_OF_1G(x)		(((x) & 0x7FFFFFFFFF) >> 30)
#define CALC_NUM_OF_2M(x)		(((x) & 0x3FFFFFFF) >> 21)
#define CALC_NUM_OF_4K(x)		(((x) & 0x1FFFFF) >> 12)

#define CALC_ADDR_512G_BLOCK_DESC(x)	ULL(PT_DESCRIPTOR_ADDR_L0 + (x) * 8)
#define CALC_512G_BLOCK_DESC(x, y)		ULL(DESCRIPTOR_ADDR_L0(x) + (y) * 8)

#define CALC_ADDR_L0_OFFSET(x)			ULL((x) >> 39 & 0x1ff)
#define CALC_ADDR_L1_OFFSET(x)			ULL((x) >> 30 & 0x1ff)
#define CALC_ADDR_L2_OFFSET(x)			ULL((x) >> 21 & 0x1ff)
#define CALC_ADDR_L3_OFFSET(x)			ULL((x) >> 12 & 0x1ff)

#define MT_IS					(0x3 << 8)
#define MT_OS					(0x2 << 8)
#define MT_ATTRINDX_C			(0x1 << 2)
#define MT_C_IS					(MT_IS | MT_ATTRINDX_C)
#define MT_C_OS					(MT_OS | MT_ATTRINDX_C)

#define SMMU_ENABLE_ACP			1
#define SMMU_DISABLE_ACP		0

#define SMMU_ABS(v)				(((v) < 0) ? -(v) : (v))

#define SMMU_UART_LSR			(0x14)
#define SMMU_UART_DATA_READY	(0x1)
#define SMMU_UART_DATA			(0)

struct smmu600_regs {
	volatile uint32_t idr0;
	volatile uint32_t idr1;
	volatile uint32_t idr2;
	volatile uint32_t idr3;
	/* 0x10 */
	volatile uint32_t idr4;
	volatile uint32_t idr5;
	volatile uint32_t iidr;
	volatile uint32_t aidr;
	/* 0x20 */
	volatile uint32_t cr0;
	volatile uint32_t cr0ack;
	volatile uint32_t cr1;
	volatile uint32_t cr2;
	/* 0x30 */
	volatile uint32_t reserved0[4];
	/* 0x40 */
	volatile uint32_t statusr;
	volatile uint32_t gbpa;
	volatile uint32_t agbpa;
	volatile uint32_t reserved1;
	/* 0x50 */
	volatile uint32_t irq_ctrl;
	volatile uint32_t irq_ctrlack;
	volatile uint32_t reserved2[2];
	/* 0x60 */
	volatile uint32_t gerror;
	volatile uint32_t gerrorn;
	volatile uint64_t gerror_irq_cfg0;
	/* 0x70 */
	volatile uint32_t gerror_irq_cfg1;
	volatile uint32_t gerror_irq_cfg2;
	volatile uint32_t reserved4[2];
	/* 0x80 */
	volatile uint64_t strtab_base;
	volatile uint32_t strtab_base_cfg;
	volatile uint32_t reserved6;
	/* 0x90 */
	volatile uint64_t cmdq_base;
	volatile uint32_t cmdq_prod;
	volatile uint32_t cmdq_cons;
	/* 0xa0 */
	volatile uint64_t eventq_base;
	volatile uint32_t eventq_prod_alias;
	volatile uint32_t eventq_cons_alias;
	/* 0xb0 */
	volatile uint64_t eventq_irq_cfg0;
	volatile uint32_t eventq_irq_cfg1;
	volatile uint32_t eventq_irq_cfg2;
	/* 0xc0 */
	volatile uint64_t priq_base;
	volatile uint32_t priq_prod_alias;
	volatile uint32_t priq_cons_alias;
	/* 0xd0 */
	volatile uint64_t priq_irq_cfg0;
	volatile uint32_t priq_irq_cfg1;
	volatile uint32_t priq_irq_cfg2;
	/* 0xe0~ to be defined */
};

struct str_cd {
	volatile uint32_t word0;
	volatile uint32_t word1;
	volatile uint32_t word2;
	volatile uint32_t word3;
	volatile uint32_t word4;
	volatile uint32_t word5;
	volatile uint32_t word6;
	volatile uint32_t word7;
	volatile uint32_t word8;
	volatile uint32_t word9;
	volatile uint32_t word10;
	volatile uint32_t word11;
	volatile uint32_t word12;
	volatile uint32_t word13;
	volatile uint32_t word14;
	volatile uint32_t word15;

};

struct str_ste {
	volatile uint32_t word0;
	volatile uint32_t word1;
	volatile uint32_t word2;
	volatile uint32_t word3;
	volatile uint32_t word4;
	volatile uint32_t word5;
	volatile uint32_t word6;
	volatile uint32_t word7;
	volatile uint32_t word8;
	volatile uint32_t word9;
	volatile uint32_t word10;
	volatile uint32_t word11;
	volatile uint32_t word12;
	volatile uint32_t word13;
	volatile uint32_t word14;
	volatile uint32_t word15;

};

struct str_pt {
	uint64_t va;
	uint64_t pa;
	uint64_t num;
	uint64_t acp;
};

struct str_region_info {
	uint32_t region_num_1g;
	uint32_t region_num_2m;
	uint32_t region_num_4k;
	struct str_pt *region_info_1g;
	struct str_pt *region_info_2m;
	struct str_pt *region_info_4k;
};

/**
 * @fn	    void smmu_test_pcie(void)
 * @brief	Test function for SMMU-PCIe in the early init stage
 * @param	none
 * @return	none
 */
void smmu_test_pcie(void);

/**
 * @fn	    void smmu_early_init(void)
 * @brief	Initialize SMMU for PCIe as an early init
 * @param	secondary_chiplet_cnt the number of chiplet available
 * @return	none
 */
void smmu_early_init(uint32_t secondary_chiplet_cnt);
