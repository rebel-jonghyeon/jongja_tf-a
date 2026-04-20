/*
 * Copyright (c) 2023-2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <lib/libc/stdint.h>
#include <string.h>
#include <stddef.h>
#include <platform_def.h>
#include <drivers/smmu/smmu.h>
#include <common/debug.h>

#define SMMU_REGS_BASE  (TCU)
#define SMMU_SID_NUM	(17)
#define SMMU_SSID_NUM	(0)

static struct smmu600_regs *smmu_regs = (struct smmu600_regs *)SMMU_REGS_BASE;
static struct smmu600_regs *smmu_regs_chiplet3 = (struct smmu600_regs *)(SMMU_REGS_BASE +
												CHIPLET3_BASE_ADDRESS);
static struct str_ste *smmu_ste = STE_ADDR(SMMU_SID_NUM);
static struct str_ste *smmu_ste3 = STE_ADDR3(SMMU_SID_NUM);
static struct str_cd *smmu_ste17_cd = CD_BASE_ADDR(SMMU_SID_NUM, SMMU_SSID_NUM);
static struct str_cd *smmu_ste17_cd3 = CD_BASE_ADDR3(SMMU_SID_NUM, SMMU_SSID_NUM);
/*
 * Notes on the region info structures
 * 1. Have to be VA aligned by block/page size and allocate VA regions in acending order.
 *    If not, it will operate in a wrong way.
 * 2. 4K table region(NUM_OF_4K_REGION) must be equal to or less than 1.
 */
static struct str_pt pt_1g_region_info[NUM_OF_1G_REGION] = {
	{.va = 0x10000000000, .pa = 0x0000000000, .num = 36, .acp = SMMU_DISABLE_ACP},
};

static struct str_pt pt_2m_region_info[NUM_OF_2M_REGION] = {
	{.va = 0x10000000000 + 0x03F40000000, .pa = 0x1FE0000000, .num = 32, .acp = SMMU_DISABLE_ACP},
	{.va = 0x10000000000 + 0x03F80000000, .pa = 0x1FE4000000, .num = 32, .acp = SMMU_DISABLE_ACP},
	{.va = 0x10000000000 + 0x03FC0000000, .pa = 0x1FF0000000, .num = 128, .acp = SMMU_DISABLE_ACP},
	{.va = 0x14000000000, .pa = 0x0010000000, .num = 32, .acp = SMMU_ENABLE_ACP},
};

#if NUM_OF_4K_REGION == 1
static struct str_pt pt_4k_region_info[NUM_OF_4K_REGION] = {
	{.va = 0x01FF8170000, .pa = 0x01ff8170000, .num = 1, .acp = SMMU_DISABLE_ACP},
};
#endif

static struct str_region_info region_info = {
	.region_num_1g = NUM_OF_1G_REGION,
	.region_num_2m = NUM_OF_2M_REGION,
	.region_num_4k = NUM_OF_4K_REGION,
	.region_info_1g = pt_1g_region_info,
	.region_info_2m = pt_2m_region_info,
#if NUM_OF_4K_REGION == 1
	.region_info_4k = pt_4k_region_info,
#else
	.region_info_4k = NULL,
#endif
};

/* Page table for chiplet3 */
static struct str_pt pt_1g_region_info_cl3[NUM_OF_1G_REGION] = {
	{.va = 0x10000000000, .pa = 0x6000000000, .num = 36, .acp = SMMU_DISABLE_ACP},
};

static struct str_pt pt_2m_region_info_cl3[NUM_OF_2M_REGION] = {
	{.va = 0x10000000000 + 0x03F40000000, .pa = 0x7FE0000000, .num = 32, .acp = SMMU_DISABLE_ACP},
	{.va = 0x10000000000 + 0x03F80000000, .pa = 0x7FE4000000, .num = 32, .acp = SMMU_DISABLE_ACP},
	{.va = 0x10000000000 + 0x03FC0000000, .pa = 0x7FF0000000, .num = 128, .acp = SMMU_DISABLE_ACP},
	{.va = 0x14000000000, .pa = 0x6010000000, .num = 32, .acp = SMMU_ENABLE_ACP},
};

#if NUM_OF_4K_REGION == 1
static struct str_pt pt_4k_region_info_cl3[NUM_OF_4K_REGION] = {
	{.va = 0x01FF8170000, .pa = 0x07ff8170000, .num = 1, .acp = SMMU_DISABLE_ACP},
};
#endif

static struct str_region_info region_info_cl3 = {
	.region_num_1g = NUM_OF_1G_REGION,
	.region_num_2m = NUM_OF_2M_REGION,
	.region_num_4k = NUM_OF_4K_REGION,
	.region_info_1g = pt_1g_region_info_cl3,
	.region_info_2m = pt_2m_region_info_cl3,
#if NUM_OF_4K_REGION == 1
	.region_info_4k = pt_4k_region_info_cl3,
#else
	.region_info_4k = NULL,
#endif
};

static uint64_t smmu_l1_pt_base[NUM_OF_1G_REGION + NUM_OF_2M_REGION + NUM_OF_4K_REGION] = {0};
static uint32_t smmu_l1_pt_index[NUM_OF_1G_REGION + NUM_OF_2M_REGION + NUM_OF_4K_REGION] = {0};

static uint64_t smmu_l2_pt_base[NUM_OF_2M_REGION + NUM_OF_4K_REGION] = {0};
static uint32_t smmu_l2_pt_index[NUM_OF_2M_REGION + NUM_OF_4K_REGION] = {0};

#if NUM_OF_4K_REGION == 1
static uint64_t smmu_l3_pt_base[NUM_OF_4K_REGION] = {0};
static uint32_t smmu_l3_pt_index[NUM_OF_4K_REGION] = {0};
#else
static uint64_t *smmu_l3_pt_base;
static uint32_t *smmu_l3_pt_index;
#endif

static void smmu_clear_base_index(void)
{
	uint32_t max_index;
	uint32_t i;

	max_index = NUM_OF_1G_REGION + NUM_OF_2M_REGION + NUM_OF_4K_REGION;
	for (i = 0; i < max_index; i++)	{
		smmu_l1_pt_base[i] = 0;
		smmu_l1_pt_index[i] = 0;
	}

	max_index = NUM_OF_2M_REGION + NUM_OF_4K_REGION;
	for (i = 0; i < max_index; i++)	{
		smmu_l2_pt_base[i] = 0;
		smmu_l2_pt_index[i] = 0;
	}

	smmu_l3_pt_base[0] = 0;
	smmu_l3_pt_index[0] = 0;
}

#ifdef SMMU_CLEAR_TABLE

static void smmu_clear_all_pagetable(struct str_region_info *region, uint64_t tt_base,
									 uint64_t *l1_pt_base, uint64_t *l2_pt_base,
									 uint64_t *l3_pt_base)
{
	uint32_t num_1g = region->region_num_1g;
	uint32_t num_2m = region->region_num_2m;
	uint32_t num_4k = region->region_num_4k;
	uint32_t i;
	uint32_t j;
	uint32_t total_regions;
	uint64_t *addr;

	addr = (uint64_t *)DESCRIPTOR_ADDR_L0(tt_base);
	for (i = 0; i < TABLE_SIZE_4K_BY_64BIT; i++) {
		addr[i] = 0;
	}

	total_regions = num_1g + num_2m + num_4k;
	for (i = 0; i < total_regions; i++) {
		if (l1_pt_base[i]) {
			addr = (uint64_t *)l1_pt_base[i];

			for (j = 0; j < TABLE_SIZE_4K_BY_64BIT; j++) {
				addr[j] = 0;
			}
		}
	}

	total_regions = num_2m + num_4k;
	for (i = 0; i < total_regions; i++) {
		if (l2_pt_base[i]) {
			addr = (uint64_t *)l2_pt_base[i];

			for (j = 0; j < TABLE_SIZE_4K_BY_64BIT; j++) {
				addr[j] = 0;
			}
		}
	}

	total_regions = num_4k;
	for (i = 0; i < total_regions; i++) {
		if (l3_pt_base[i]) {
			addr = (uint64_t *)l3_pt_base[i];

			for (j = 0; j < TABLE_SIZE_4K_BY_64BIT; j++) {
				addr[j] = 0;
			}
		}
	}
}
#endif

static uint64_t smmu_find_number_of_512g_region(struct str_region_info *region)
{
	uint32_t i;
	uint64_t va_min;
	uint64_t va_max;
	uint32_t num_1g = region->region_num_1g;
	uint32_t num_2m = region->region_num_2m;
	uint32_t num_4k = region->region_num_4k;
	struct str_pt *p_1g_info = region->region_info_1g;
	struct str_pt *p_2m_info = region->region_info_2m;
	struct str_pt *p_4k_info = region->region_info_4k;

	va_min = 0;
	va_max = 0;

	for (i = 0; i < num_1g; i++) {
		va_min = MIN(p_1g_info[i].va, va_min);
		va_max = MAX(p_1g_info[i].va, va_max);
	}

	for (i = 0; i < num_2m; i++) {
		va_min = MIN(p_2m_info[i].va, va_min);
		va_max = MAX(p_2m_info[i].va, va_max);
	}

	if (num_4k) {
		for (i = 0; i < num_4k; i++) {
			va_min = MIN(p_4k_info[i].va, va_min);
			va_max = MAX(p_4k_info[i].va, va_max);
		}
	}

	return CALC_NUM_OF_512G(va_max - va_min);
}

static void smmu_make_l1_table_index(struct str_region_info *str_region, uint32_t *l1_pt_index)
{
	uint32_t i;
	uint32_t num_1g = str_region->region_num_1g;
	uint32_t num_2m = str_region->region_num_2m;
	uint32_t num_4k = str_region->region_num_4k;
	struct str_pt *p_1g_info = str_region->region_info_1g;
	struct str_pt *p_2m_info = str_region->region_info_2m;
	struct str_pt *p_4k_info = str_region->region_info_4k;

	for (i = 0; i < num_1g; i++) {
		l1_pt_index[i] = CALC_ADDR_L0_OFFSET(p_1g_info[i].va);
	}

	for (i = 0; i < num_2m; i++) {
		l1_pt_index[num_1g + i] = CALC_ADDR_L0_OFFSET(p_2m_info[i].va);
	}

	if (num_4k)
		l1_pt_index[num_1g + num_2m] = CALC_ADDR_L0_OFFSET(p_4k_info[0].va);
}

static void smmu_make_l2_table_index(struct str_region_info *str_region, uint32_t *l2_pt_index)
{
	uint32_t i;
	uint32_t num_2m = str_region->region_num_2m;
	uint32_t index;
	uint32_t prev_offset;
	uint32_t cur_offset;
	struct str_pt *p_2m_info = str_region->region_info_2m;

	prev_offset = CALC_ADDR_L1_OFFSET(p_2m_info[0].va);
	index = 0;

	for (i = 0; i < num_2m; i++) {
		cur_offset = CALC_ADDR_L1_OFFSET(p_2m_info[i].va);
		if (prev_offset != cur_offset)
			index++;

		l2_pt_index[i] = index;
		prev_offset = cur_offset;
	}
}

static void smmu_make_l3_table_index(struct str_region_info *str_region, uint32_t *l3_pt_index)
{
	uint32_t num_4k = str_region->region_num_4k;

	if (num_4k)
		l3_pt_index[0] = 0;
}

static uint32_t smmu_is_va_diff_over_1g_region(uint64_t va1, uint64_t va2)
{
	uint64_t va1_masked;
	uint64_t va2_masked;

	va1_masked = BLOCK_SIZE_1G_MASK & va1;
	va2_masked = BLOCK_SIZE_1G_MASK & va2;

	if (SMMU_ABS(va1_masked - va2_masked) >= BLOCK_SIZE_1G)
		return true;
	else
		return false;
}

static void smmu_make_table_address(struct str_region_info *str_region,
									uint64_t tt_base, uint32_t count_512g,
									uint32_t *l1_pt_index, uint32_t *l2_pt_index,
									uint32_t *l3_pt_index, uint64_t *l1_pt_base,
									uint64_t *l2_pt_base, uint64_t *l3_pt_base)
{
	uint64_t next_page_addr;
	uint32_t i;
	uint32_t j;
	uint32_t table_count;
	uint64_t count_1g_region;
	uint32_t num_1g = str_region->region_num_1g;
	uint32_t num_2m = str_region->region_num_2m;
	uint32_t num_4k = str_region->region_num_4k;
	struct str_pt *p_2m_info = str_region->region_info_2m;
	struct str_pt *p_4k_info = str_region->region_info_4k;
	uint32_t l2_pt_base_index = 1;

	table_count = 0;

	for (i = 0; i < count_512g; i++) {
		for (j = 0; j < num_1g + num_2m + num_4k; j++) {
			if (l1_pt_index[j] == i) {
				l1_pt_base[i] = CALC_DESCRIPTOR_ADDR(tt_base, table_count);
				table_count++;

				break;
			}
		}
	}

	next_page_addr = l1_pt_base[count_512g - 1] + TABLE_SIZE_4K;

	l2_pt_base[0] = next_page_addr;

	for (i = 1; i < num_2m; i++) {
		if (smmu_is_va_diff_over_1g_region(p_2m_info[i].va, p_2m_info[i - 1].va)) {
			next_page_addr += TABLE_SIZE_4K;
			l2_pt_base[l2_pt_base_index++] = next_page_addr;
		}
	}

	count_1g_region = num_2m;
	table_count = 0;

	if (num_4k) {
		for (i = 0; i < num_2m; i++) {
			if (smmu_is_va_diff_over_1g_region(p_2m_info[i].va, p_4k_info[0].va)) {
				table_count++;
			}
		}

		if (table_count > 0) {
			next_page_addr += TABLE_SIZE_4K;
			l2_pt_base[l2_pt_base_index] = next_page_addr;
			l2_pt_index[count_1g_region] = l2_pt_index[count_1g_region - 1] + 1;
			count_1g_region++;
		}

		next_page_addr += TABLE_SIZE_4K;
		l3_pt_base[0] = next_page_addr;
	}
}

static void smmu_write_l0_table(uint64_t tt_base, uint32_t count_512g, uint64_t *l1_pt_base)
{
	uint32_t i;

	for (i = 0; i < count_512g; i++) {
		if (l1_pt_base[i]) {
			*(uint64_t *)CALC_512G_BLOCK_DESC(tt_base, i) =
											(uint64_t)(l1_pt_base[i] | PT_TABLE_ATTR);
		}
	}
}

static void smmu_write_l1_table(struct str_region_info *str_region,
								uint64_t tt_base, uint32_t count_512g,
								uint32_t *l1_pt_index, uint32_t *l2_pt_index, uint32_t *l3_pt_index,
								uint64_t *l1_pt_base, uint64_t *l2_pt_base, uint64_t *l3_pt_base)
{
	uint64_t desc_val;
	uint64_t vaddr;
	uint64_t paddr;
	uint32_t i;
	uint32_t j;
	uint32_t num_1g = str_region->region_num_1g;
	uint32_t num_2m = str_region->region_num_2m;
	uint32_t num_4k = str_region->region_num_4k;
	struct str_pt *p_1g_info = str_region->region_info_1g;
	struct str_pt *p_2m_info = str_region->region_info_2m;
	struct str_pt *p_4k_info = str_region->region_info_4k;

	for (j = 0; j < num_1g; j++) {
		for (i = 0; i < p_1g_info[j].num; i++) {
			paddr = (uint64_t)(p_1g_info[j].pa + BLOCK_SIZE_1G * i);
			desc_val = (paddr & BLOCK_SIZE_1G_MASK) | PT_BLOCK_ATTR | (MT_C_IS * p_1g_info[j].acp);
			vaddr = p_1g_info[j].va + BLOCK_SIZE_1G * i;
			*(uint64_t *)(l1_pt_base[l1_pt_index[j]] + PT_BLOCK_OFFSET_L1(vaddr)) = desc_val;
		}
	}

	for (j = 0; j < num_2m; j++) {
		vaddr = (uint64_t)(l2_pt_base[l2_pt_index[j]]);
		desc_val = vaddr | PT_TABLE_ATTR;

		*(uint64_t *)(l1_pt_base[l1_pt_index[num_1g + j]] +
					PT_BLOCK_OFFSET_L1(p_2m_info[j].va)) = desc_val;
	}

	if (num_4k) {
		for (j = 0; j < num_4k; j++) {
			vaddr = (uint64_t)(l2_pt_base[l2_pt_index[num_2m + j]]);
			desc_val = vaddr | PT_TABLE_ATTR;

			*(uint64_t *)(l1_pt_base[l1_pt_index[num_1g + num_2m + j]] +
						PT_BLOCK_OFFSET_L1(p_4k_info[j].va)) = desc_val;
		}
	}
}

static void smmu_write_l2_table(struct str_region_info *str_region,
								uint32_t *l1_pt_index, uint32_t *l2_pt_index, uint32_t *l3_pt_index,
								uint64_t *l1_pt_base, uint64_t *l2_pt_base, uint64_t *l3_pt_base)
{
	uint64_t desc_val;
	uint64_t vaddr;
	uint64_t paddr;
	uint32_t i;
	uint32_t j;
	uint32_t num_2m = str_region->region_num_2m;
	uint32_t num_4k = str_region->region_num_4k;
	struct str_pt *p_2m_info = str_region->region_info_2m;
	struct str_pt *p_4k_info = str_region->region_info_4k;

	for (j = 0; j < num_2m; j++) {
		for (i = 0; i < p_2m_info[j].num; i++) {
			paddr = (uint64_t)(p_2m_info[j].pa + BLOCK_SIZE_2M * i);
			desc_val = (paddr & BLOCK_SIZE_2M_MASK) | PT_BLOCK_ATTR | (MT_C_IS * p_2m_info[j].acp);
			vaddr = p_2m_info[j].va + BLOCK_SIZE_2M * i;
			*(uint64_t *)(l2_pt_base[l2_pt_index[j]] + PT_BLOCK_OFFSET_L2(vaddr)) = desc_val;
		}
	}

	if (num_4k) {
		for (i = 0; i < num_4k; i++) {
			vaddr = (uint64_t)(l3_pt_base[i]);
			desc_val = vaddr | PT_TABLE_ATTR;

			*(uint64_t *)(l2_pt_base[l2_pt_index[num_2m + i]] +
						PT_BLOCK_OFFSET_L2(p_4k_info[i].va)) = desc_val;
		}
	}
}

static void smmu_write_l3_table(struct str_region_info *str_region,
								uint32_t *l3_pt_index, uint64_t *l3_pt_base)
{
	uint64_t desc_val;
	uint64_t vaddr;
	uint64_t paddr;
	uint32_t i;
	uint32_t j;
	uint32_t num_4k = str_region->region_num_4k;
	struct str_pt *p_2m_info = str_region->region_info_2m;
	struct str_pt *p_4k_info = str_region->region_info_4k;

	if (num_4k) {
		for (j = 0; j < num_4k; j++) {
			for (i = 0; i < p_4k_info[j].num; i++) {
				paddr = (uint64_t)(p_4k_info[j].pa + PAGE_SIZE_4K * i);
				desc_val = paddr | PT_PAGE_ATTR | (MT_C_IS * p_2m_info[j].acp);
				vaddr = p_4k_info[j].va + PAGE_SIZE_4K * i;
				*(uint64_t *)(l3_pt_base[l3_pt_index[j]] + PT_PAGE_OFFSET_L3(vaddr)) = desc_val;
			}
		}
	}
}

static void smmu_gen_pagetable(uint64_t tt_base, struct str_region_info *str_region)
{
	uint64_t count_512g_region;
	struct str_region_info *p_region = str_region;

	count_512g_region = smmu_find_number_of_512g_region(p_region);

	smmu_make_l1_table_index(p_region, smmu_l1_pt_index);
	smmu_make_l2_table_index(p_region, smmu_l2_pt_index);
	smmu_make_l3_table_index(p_region, smmu_l3_pt_index);

	smmu_make_table_address(p_region, tt_base, count_512g_region,
							smmu_l1_pt_index, smmu_l2_pt_index, smmu_l3_pt_index,
							smmu_l1_pt_base, smmu_l2_pt_base, smmu_l3_pt_base);

#ifdef SMMU_CLEAR_TABLE
	smmu_clear_all_pagetable(p_region, tt_base, smmu_l1_pt_base, smmu_l2_pt_base, smmu_l3_pt_base);
#endif

	smmu_write_l0_table(tt_base, count_512g_region, smmu_l1_pt_base);
	smmu_write_l1_table(p_region, tt_base, count_512g_region,
						smmu_l1_pt_index, smmu_l2_pt_index, smmu_l3_pt_index,
						smmu_l1_pt_base, smmu_l2_pt_base, smmu_l3_pt_base);
	smmu_write_l2_table(p_region,
						smmu_l1_pt_index, smmu_l2_pt_index, smmu_l3_pt_index,
						smmu_l1_pt_base, smmu_l2_pt_base, smmu_l3_pt_base);
	smmu_write_l3_table(p_region, smmu_l3_pt_index, smmu_l3_pt_base);
}

static void __unused smmu_set_priq(uint32_t secondary_chiplet_cnt)
{
	volatile struct smmu600_regs *regs = smmu_regs;
	volatile struct smmu600_regs *regs3 = smmu_regs_chiplet3;

	regs->priq_base = PRIQ_BASE_ADDR | Q_LOG2SIZE;

	if (secondary_chiplet_cnt == CHIPLET_ID3 && GET_REVISION == REVISION_EVT1)
		regs3->priq_base = PRIQ_BASE_ADDR | Q_LOG2SIZE | CHIPLET3_BASE_ADDRESS;
}

static void smmu_set_eventq(uint32_t secondary_chiplet_cnt)
{
	volatile struct smmu600_regs *regs = smmu_regs;
	volatile struct smmu600_regs *regs3 = smmu_regs_chiplet3;

	regs->eventq_base = EVENTQ_BASE_ADDR | Q_LOG2SIZE;

	if (secondary_chiplet_cnt == CHIPLET_ID3 && GET_REVISION == REVISION_EVT1)
		regs3->eventq_base = EVENTQ_BASE_ADDR | Q_LOG2SIZE | CHIPLET3_BASE_ADDRESS;
}

static void __unused smmu_set_cmdq(uint32_t secondary_chiplet_cnt)
{
	volatile struct smmu600_regs *regs = smmu_regs;
	volatile struct smmu600_regs *regs3 = smmu_regs_chiplet3;

	regs->cmdq_base = CMDQ_BASE_ADDR | Q_LOG2SIZE;

	if (secondary_chiplet_cnt == CHIPLET_ID3 && GET_REVISION == REVISION_EVT1)
		regs3->cmdq_base = CMDQ_BASE_ADDR | Q_LOG2SIZE | CHIPLET3_BASE_ADDRESS;
}

static void smmu_set_ste17_cd(uint32_t secondary_chiplet_cnt)
{
	smmu_ste17_cd->word0 = CD_VALID | CD_EPD1_DISABLE | CD_T0SZ;
	smmu_ste17_cd->word1 = CD_R | CD_AA64 | CD_TBI0 | CD_AFF | CD_IPS_40BIT;
	smmu_ste17_cd->word2 = SMMU_PT17_BASE_ADDR;
	smmu_ste17_cd->word3 = 0;
	smmu_ste17_cd->word4 = 0;
	smmu_ste17_cd->word5 = 0;
	smmu_ste17_cd->word6 = CD_MAIR_VALUE;
	smmu_ste17_cd->word7 = CD_MAIR_VALUE;

	smmu_ste17_cd->word8 = 0;
	smmu_ste17_cd->word9 = 0;
	smmu_ste17_cd->word10 = 0;
	smmu_ste17_cd->word11 = 0;
	smmu_ste17_cd->word12 = 0;
	smmu_ste17_cd->word13 = 0;
	smmu_ste17_cd->word14 = 0;
	smmu_ste17_cd->word15 = 0;

	if (secondary_chiplet_cnt == CHIPLET_ID3 && GET_REVISION == REVISION_EVT1) {
		smmu_ste17_cd3->word0 = CD_VALID | CD_EPD1_DISABLE | CD_T0SZ;
		smmu_ste17_cd3->word1 = CD_R | CD_AA64 | CD_TBI0 | CD_AFF | CD_IPS_40BIT;
		smmu_ste17_cd3->word2 = SMMU_PT17_BASE_ADDR;
		smmu_ste17_cd3->word3 = (uint32_t)(CHIPLET3_BASE_ADDRESS >> 32);
		smmu_ste17_cd3->word4 = 0;
		smmu_ste17_cd3->word5 = 0;
		smmu_ste17_cd3->word6 = CD_MAIR_VALUE;
		smmu_ste17_cd3->word7 = CD_MAIR_VALUE;

		smmu_ste17_cd3->word8 = 0;
		smmu_ste17_cd3->word9 = 0;
		smmu_ste17_cd3->word10 = 0;
		smmu_ste17_cd3->word11 = 0;
		smmu_ste17_cd3->word12 = 0;
		smmu_ste17_cd3->word13 = 0;
		smmu_ste17_cd3->word14 = 0;
		smmu_ste17_cd3->word15 = 0;

	}
}

static void smmu_set_ste(uint32_t secondary_chiplet_cnt)
{
	smmu_ste->word0 = (uint64_t)CD_BASE_ADDR(SMMU_SID_NUM, SMMU_SSID_NUM) | STE_CONFIG_STAGE1_VALID;
	smmu_ste->word1 = CD_MAX;
	smmu_ste->word2 = STE_STRW_EL2_E2H | STE_S1DSS_SS0;
	smmu_ste->word3 = STE_SHCFG_USE_INCOMING;
	smmu_ste->word4 = 0;
	smmu_ste->word5 = 0;
	smmu_ste->word6 = 0;
	smmu_ste->word7 = 0;

	if (secondary_chiplet_cnt == CHIPLET_ID3 && GET_REVISION == REVISION_EVT1) {
		smmu_ste3->word0 = (uint32_t)((uint64_t)CD_BASE_ADDR3(SMMU_SID_NUM, SMMU_SSID_NUM) |
							STE_CONFIG_STAGE1_VALID);
		smmu_ste3->word1 = (uint32_t)((uint64_t)CD_BASE_ADDR3(SMMU_SID_NUM, SMMU_SSID_NUM) >> 32) |
							CD_MAX;
		smmu_ste3->word2 = STE_STRW_EL2_E2H | STE_S1DSS_SS0;
		smmu_ste3->word3 = STE_SHCFG_USE_INCOMING;
		smmu_ste3->word4 = 0;
		smmu_ste3->word5 = 0;
		smmu_ste3->word6 = 0;
		smmu_ste3->word7 = 0;

	}
}

static void smmu_set_strtab(uint32_t secondary_chiplet_cnt)
{
	volatile struct smmu600_regs *regs = smmu_regs;
	volatile struct smmu600_regs *regs3 = smmu_regs_chiplet3;

	regs->strtab_base_cfg = STRTAB_CFG_VALUE;
	regs->strtab_base = SMMU_STE_BASE_ADDR;

	if (secondary_chiplet_cnt == CHIPLET_ID3 && GET_REVISION == REVISION_EVT1) {
		regs3->strtab_base_cfg = STRTAB_CFG_VALUE;
		regs3->strtab_base = SMMU_STE_BASE_ADDR | CHIPLET3_BASE_ADDRESS;
	}
}

static void smmu_enable_smmu(uint32_t secondary_chiplet_cnt)
{
	volatile struct smmu600_regs *regs = smmu_regs;
	volatile struct smmu600_regs *regs3 = smmu_regs_chiplet3;

	regs->cr0 = SMMU_EVENTQEN;
	while (!(regs->cr0ack & SMMU_EVENTQEN_MASK))
		;

	regs->cr0 |= SMMU_SMMUEN;
	while (!(regs->cr0ack & SMMU_SMMUEN_MASK))
		;

	if (secondary_chiplet_cnt == CHIPLET_ID3 && GET_REVISION == REVISION_EVT1) {
		regs3->cr0 = SMMU_EVENTQEN;
		while (!(regs3->cr0ack & SMMU_EVENTQEN_MASK))
			;

		regs3->cr0 |= SMMU_SMMUEN;
		while (!(regs3->cr0ack & SMMU_SMMUEN_MASK))
			;
	}
}

static void smmu_set_gbpa(uint32_t secondary_chiplet_cnt)
{
	volatile struct smmu600_regs *regs = smmu_regs;
	volatile struct smmu600_regs *regs3 = smmu_regs_chiplet3;

	regs->gbpa = SMMU_GBPA_COMPLETE | SMMU_GBPA_SHCFG_USEINCOMING;

	while (regs->gbpa & SMMU_GBPA_COMPLETE_MASK)
		;

	if (secondary_chiplet_cnt == CHIPLET_ID3 && GET_REVISION == REVISION_EVT1) {
		regs3->gbpa = SMMU_GBPA_COMPLETE | SMMU_GBPA_SHCFG_USEINCOMING;

		while (regs3->gbpa & SMMU_GBPA_COMPLETE_MASK)
			;
	}
}

static void smmu_set_tcu(uint32_t secondary_chiplet_cnt)
{
	smmu_set_eventq(secondary_chiplet_cnt);
	smmu_set_strtab(secondary_chiplet_cnt);
	smmu_set_gbpa(secondary_chiplet_cnt);
}

static void smmu_wait_a_key(void)
{
	while (!(*(volatile uint32_t *)(UART0_PERI0 + SMMU_UART_LSR) & SMMU_UART_DATA_READY))
		;
	NOTICE("BL2: Key=%c\n", *(volatile uint32_t *)(UART0_PERI0 + SMMU_UART_DATA));
}

static void smmu_flush_all_cache(void)
{
	asm volatile("mov x0, #1");
	asm volatile("MSR S1_1_C15_C14_0, x0");
	asm volatile("DSB sy");

	asm volatile("mov x0, #2");
	asm volatile("MSR S1_1_C15_C14_0, x0");
	asm volatile("DSB sy");
}

static void smmu_flush_l2_cache(void)
{
	asm volatile("mov x0, #2");
	asm volatile("MSR S1_1_C15_C14_0, x0");
	asm volatile("DSB sy");
}

void smmu_test_pcie(void)
{
	NOTICE("BL2: [SMMU] Test PCIe-SMMU\n\n");

	smmu_flush_all_cache();

	NOTICE("BL2: [SMMU] Perform PCIe operations using XTOR and then press any key.\n");
	smmu_wait_a_key();

	smmu_flush_l2_cache();

	NOTICE("BL2: [SMMU] L2$ is cleaned and invalidated.\n");
	NOTICE("BL2: [SMMU] Check the data of physical memory.\n");

	/* Running further codes is blocked because smmu test can modify the contents of a memory. */
	asm("b .");
}

void smmu_early_init(uint32_t secondary_chiplet_cnt)
{
	smmu_gen_pagetable(DESCRIPTOR_ADDR_L0(SMMU_PT17_BASE_ADDR), &region_info);
	if (secondary_chiplet_cnt == CHIPLET_ID3 && GET_REVISION == REVISION_EVT1) {
		smmu_clear_base_index();
		smmu_gen_pagetable(DESCRIPTOR_ADDR_L0(SMMU_PT17_BASE_ADDR + CHIPLET3_BASE_ADDRESS),
						   &region_info_cl3);
	}
	smmu_set_ste(secondary_chiplet_cnt);
	smmu_set_ste17_cd(secondary_chiplet_cnt);
	smmu_set_tcu(secondary_chiplet_cnt);
	smmu_enable_smmu(secondary_chiplet_cnt);
}
