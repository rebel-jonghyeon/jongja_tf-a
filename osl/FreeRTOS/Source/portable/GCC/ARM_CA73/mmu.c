/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */

#include "FreeRTOS.h"
#include <stdint.h>
#include <stdbool.h>
#include "rl_errors.h"
#include "rl_utils.h"
#include "mmu_table.h"
#include "cpu.h"

/* TODO : remove below util marcro after include glibc */
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(A)			(sizeof(A) / sizeof((A)[0]))
#endif /* ARRAY_SIZE */

#ifndef MAX
#define MAX(a, b)				(((a) > (b)) ? (a) : (b))
#endif /* MAX */

#ifndef MIN
#define MIN(a, b)				(((a) < (b)) ? (a) : (b))
#endif /* MIN */

enum mmu_boot_sequence {
	NOT_STARTED,
	START_MMU_INIT,
	SET_STACK_POINTER,
};

static uint64_t xlat_tables[MAX_XLAT_TABLES * Ln_NUM_ENTRIES]
__attribute__((aligned(Ln_NUM_ENTRIES * sizeof(uint64_t))));
static uint16_t xlat_use_count[MAX_XLAT_TABLES];

static struct mmu_ptables mmu_ptables;

static void invalidate_tlb_all(void)
{
	__asm__ volatile ("dsb ishst; tlbi vmalle1; dsb ish; isb" : : : "memory");
}

static inline unsigned int table_index(struct mmu_ptables *ptables, uint64_t *pte)
{
	unsigned int i = (pte - ptables->base_xlat_table) / ptables->xlat_table_size;

	return i;
}

static int table_usage(struct mmu_ptables *ptables, uint64_t *table, int adjustment)
{
	unsigned int i = table_index(ptables, table);

	ptables->xlat_use_count[i] += adjustment;
	return ptables->xlat_use_count[i];
}

static void set_pte_table_desc(uint64_t *pte, uint64_t *table, unsigned int level)
{
	/* Point pte to new table */
	*pte = PTE_TABLE_DESC | (uint64_t)table;
}

static void set_pte_block_desc(uint64_t *pte, uint64_t desc, unsigned int level)
{
	if (desc) {
		desc |= (level == LAST_LEVEL) ? PTE_PAGE_DESC : PTE_BLOCK_DESC;
	}
	*pte = desc;
}

static inline bool is_desc_block_aligned(uint64_t desc, unsigned int level_size)
{
	uint64_t mask = RL_GENMASK64(47, PAGE_SIZE_SHIFT);
	bool aligned = !((desc & mask) & (level_size - 1));

	return aligned;
}

static inline bool is_desc_superset(uint64_t desc1, uint64_t desc2,	unsigned int level)
{
	uint64_t mask = DESC_ATTRS_MASK | RL_GENMASK64(47, LEVEL_TO_VA_SIZE_SHIFT(level));

	return (desc1 & mask) == (desc2 & mask);
}

static inline bool is_table_unused(struct mmu_ptables *ptables, uint64_t *table)
{
	return table_usage(ptables, table, 0) == 1;
}

static inline bool is_free_desc(uint64_t desc)
{
	return (desc & PTE_DESC_TYPE_MASK) == PTE_INVALID_DESC;
}

static inline bool is_table_desc(uint64_t desc, unsigned int level)
{
	return level != LAST_LEVEL &&
		   (desc & PTE_DESC_TYPE_MASK) == PTE_TABLE_DESC;
}

static inline uint64_t *pte_desc_table(uint64_t desc)
{
	uint64_t address = desc & RL_GENMASK64(47, PAGE_SIZE_SHIFT);

	return (uint64_t *)address;
}

static void free_table(struct mmu_ptables *ptables, uint64_t *table)
{
	unsigned int i = table_index(ptables, table);

	xlat_use_count[i] = 0U;
}

uint64_t *new_table(struct mmu_ptables *ptables)
{
	uint64_t *table;
	uint32_t i;

	for (i = 0U; i < ptables->xlat_table_count; i++) {
		if (ptables->xlat_use_count[i] == 0U) {
			table = &ptables->base_xlat_table[i * ptables->xlat_table_size];
			ptables->xlat_use_count[i] = 1U;
			return table;
		}
	}

	return NULL;
}

static uint64_t get_region_desc(uint32_t attrs, bool s2)
{
	unsigned int mem_type;
	uint64_t desc = 0U;

	/* NS bit for security memory access from secure state */
	if (!s2)
		desc |= (attrs & MT_NS) ? PTE_BLOCK_DESC_NS : 0;
	else
		desc |= (attrs & MT_NS) ? PTE_BLOCK_DESC_S2NS : 0;

	/*
	 * AP bits for EL0 / ELh Data access permission
	 *
	 *   AP[2:1]   ELh  EL0
	 * +--------------------+
	 *     00      RW   NA
	 *     01      RW   RW
	 *     10      RO   NA
	 *     11      RO   RO
	 */

	if (!s2) {
	/* AP bits for Data access permission */
		desc |= (attrs & MT_RW) ? PTE_BLOCK_DESC_AP_RW : PTE_BLOCK_DESC_AP_RO;
	/* Mirror permissions to EL0 */
		desc |= (attrs & MT_RW_AP_ELx) ?
			 PTE_BLOCK_DESC_AP_ELx : PTE_BLOCK_DESC_AP_EL_HIGHER;
	} else {
		desc |= (attrs & MT_RW) ? PTE_BLOCK_DESC_S2AP_RW : PTE_BLOCK_DESC_S2AP_NONE;
	}

	/* the access flag */
	desc |= PTE_BLOCK_DESC_AF;

	/* memory attribute index field */
	mem_type = MT_TYPE(attrs);
	desc |= PTE_BLOCK_DESC_MEMTYPE(mem_type);

	switch (mem_type) {
	case MT_DEVICE_nGnRnE:
	case MT_DEVICE_nGnRE:
	case MT_DEVICE_GRE:
		/* Access to Device memory and non-cacheable memory are coherent
		 * for all observers in the system and are treated as
		 * Outer shareable, so, for these 2 types of memory,
		 * it is not strictly needed to set shareability field
		 */
		desc |= PTE_BLOCK_DESC_OUTER_SHARE;
		/* Map device memory as execute-never */
		desc |= PTE_BLOCK_DESC_PXN;
		desc |= PTE_BLOCK_DESC_UXN;
		break;
	case MT_NORMAL_NC:
	case MT_NORMAL:
		/* Make Normal RW memory as execute never */
		if (attrs & MT_P_EXECUTE_NEVER)
			desc |= PTE_BLOCK_DESC_PXN;

		if (attrs & MT_U_EXECUTE_NEVER)
			desc |= PTE_BLOCK_DESC_UXN;

		desc |= PTE_BLOCK_DESC_INNER_SHARE;
	}

	/* non-Global bit */
	if (attrs & MT_NG) {
		desc |= PTE_BLOCK_DESC_NG;
	}

	return desc;
}

static uint64_t *expand_to_table(struct mmu_ptables *ptables, uint64_t *pte, unsigned int level)
{
	uint64_t *table;

	table = new_table(ptables);
	if (!table) {
		return NULL;
	}

	if (!is_free_desc(*pte)) {
		/*
		 * If entry at current level was already populated
		 * then we need to reflect that in the new table.
		 */
		uint64_t desc = *pte;
		unsigned int i, stride_shift;

		if (level + 1 == LAST_LEVEL) {
			desc |= PTE_PAGE_DESC;
		}

		stride_shift = LEVEL_TO_VA_SIZE_SHIFT(level + 1);
		for (i = 0U; i < ptables->xlat_table_size; i++) {
			table[i] = desc | (i << stride_shift);
		}
		table_usage(ptables, table, ptables->xlat_table_size);
	} else {
		/*
		 * Adjust usage count for parent table's entry
		 * that will no longer be free.
		 */
		table_usage(ptables, pte, 1);
	}

	/* Link the new table in place of the pte it replaces */
	set_pte_table_desc(pte, table, level);
	table_usage(ptables, table, 1);

	return table;
}

static int set_mapping(struct mmu_ptables *ptables, uintptr_t virt, size_t size,
					   uint64_t desc, bool may_overwrite)
{
	uint64_t *pte, *ptes[LAST_LEVEL + 1];
	uint64_t level_size;
	uint64_t *table = ptables->base_xlat_table;
	unsigned int level = BASE_XLAT_LEVEL;
	int ret = 0;

	while (size) {
		pte = (uint64_t *)&table[XLAT_TABLE_VA_IDX(virt, level)];
		ptes[level] = pte;

		if (is_table_desc(*pte, level)) {
			level++;
			table = pte_desc_table(*pte);
			continue;
		}

		if (!may_overwrite && !is_free_desc(*pte)) {
			ret = RL_BUSY;
			break;
		}

		level_size = 1ULL << LEVEL_TO_VA_SIZE_SHIFT(level);

		if (is_desc_superset(*pte, desc, level)) {
			level_size -= (virt & (level_size - 1));
			if (level_size > size) {
				level_size = size;
			}
			goto move_on;
		}

		if (size < level_size || (virt & (level_size - 1)) ||
			!is_desc_block_aligned(desc, level_size)) {
			table = expand_to_table(ptables, pte, level);
			if (!table) {
				ret = RL_NOMEM;
				break;
			}
			level++;
			continue;
		}
		if (is_free_desc(*pte)) {
			table_usage(ptables, pte, 1);
		}
		if (!desc) {
			table_usage(ptables, pte, -1);
		}
		set_pte_block_desc(pte, desc, level);

		while (level != BASE_XLAT_LEVEL &&
			   is_table_unused(ptables, pte)) {
			free_table(ptables, pte);
			pte = ptes[--level];
			set_pte_block_desc(pte, 0, level);
			table_usage(ptables, pte, -1);
		}

move_on:
		virt += level_size;
		desc += desc ? level_size : 0;
		size -= level_size;

		table = ptables->base_xlat_table;
		level = BASE_XLAT_LEVEL;
	}

	return ret;
}

static int __add_map(struct mmu_ptables *ptables, const char *name, uintptr_t phys, uintptr_t virt,
					 size_t size, uint32_t attrs)
{
	uint64_t desc = get_region_desc(attrs, ptables->s2);
	bool may_overwrite = !(attrs & MT_NO_OVERWRITE);

	desc |= phys;

	return set_mapping(ptables, virt, size, desc, may_overwrite);
}

static inline void add_mmu_flat_range(struct mmu_ptables *ptables,
									  const struct mmu_flat_range *range, uint32_t extra_flags)
{
	uintptr_t address = (uintptr_t)range->start;
	size_t size = (uintptr_t)range->end - address;

	if (size) {
		/* MMU not yet active: must use unlocked version */
		__add_map(ptables, range->name, address, address, size, range->attrs | extra_flags);
	}
}

static inline void add_mmu_flat_range_offset(struct mmu_ptables *ptables,
											 const struct mmu_flat_range *range, uint32_t extra_flags,
											 uint64_t offset)
{
	uintptr_t address = (uintptr_t)range->start;
	size_t size = (uintptr_t)range->end - address;

	if (size) {
		/* MMU not yet active: must use unlocked version */
		__add_map(ptables, range->name, address + offset, address, size, range->attrs | extra_flags);
	}
}

static inline void add_mmu_region(struct mmu_ptables *ptables, const struct mmu_region *region,
								  uint32_t extra_flags)
{
	if (region->size || region->attrs) {
		__add_map(ptables, region->name, region->base_pa, region->base_va, region->size,
				  region->attrs | extra_flags);
	}
}

void setup_page_tables(struct mmu_ptables *ptables)
{
	unsigned int index;
	struct mmu_flat_range range;
	struct mmu_region region;
	uint64_t chiplet_lbound = CHIPLET_ID * 0x02000000000ULL;
	uint64_t chiplet_rbound = (CHIPLET_ID + 1) * 0x02000000000ULL;

	if (ptables->flag == REBELH_MMU) {
		for (index = 0U; index < ptables->mmu_flat_range_size; index++) {
			range = ptables->mmu_flat_range[index];
			/* Chiplet x */
			add_mmu_flat_range_offset(ptables, &range, 0, -0x10000000000ULL + chiplet_lbound);
			/* Chiplet 0 */
			range.start -= 0x10000000000ULL;
			range.end -= 0x10000000000ULL;
			add_mmu_flat_range(ptables, &range, 0);
			/* Chiplet 1 */
			range.start += 0x2000000000ULL;
			range.end += 0x2000000000ULL;
			add_mmu_flat_range(ptables, &range, 0);
			/* Chiplet 2 */
			range.start += 0x2000000000ULL;
			range.end += 0x2000000000ULL;
			add_mmu_flat_range(ptables, &range, 0);
			/* Chiplet 3 */
			range.start += 0x2000000000ULL;
			range.end += 0x2000000000ULL;
			add_mmu_flat_range(ptables, &range, 0);
		}

		for (index = 0U; index < ptables->mmu_region_size; index++) {
			region = ptables->mmu_region[index];
			/* Mapping phyiscal address for Chiplet x region */
			if (region.base_va >= 0x10000000000ULL) {
				region.base_pa += CHIPLET_ID * 0x2000000000ULL;
			/* Own chiplet = Cacheable, the other chiplets = Non-cacheable */
			} else if ((region.base_pa < chiplet_lbound || region.base_pa >= chiplet_rbound) &&
					   (region.attrs & 0x7U) == MT_NORMAL) {
				region.attrs ^= MT_NORMAL ^ MT_NORMAL_NC;
			}
			add_mmu_region(ptables, &region, MT_NO_OVERWRITE);
		}

		invalidate_tlb_all();
	} else {
		for (index = 0U; index < ptables->mmu_flat_range_size; index++) {
			range = ptables->mmu_flat_range[index];
			if ((uint64_t)range.start >= 0x10000000000ULL) {
				add_mmu_flat_range_offset(ptables, &range, 0, -0x10000000000ULL + chiplet_lbound);
			} else {
				add_mmu_flat_range(ptables, &range, 0);
			}
		}

		for (index = 0U; index < ptables->mmu_region_size; index++) {
			region = ptables->mmu_region[index];
			add_mmu_region(ptables, &region, MT_NO_OVERWRITE);
		}
	}
}

static uint64_t get_tcr(int el)
{
	uint64_t tcr;
	uint64_t va_bits = VA_BITS;
	uint64_t tcr_ps_bits;

	tcr_ps_bits = TCR_PS_BITS;

	if (el == 1) {
		tcr = (tcr_ps_bits << TCR_EL1_IPS_SHIFT);
		/*
		 * TCR_EL1.EPD1: Disable translation table walk for addresses
		 * that are translated using TTBR1_EL1.
		 */
		tcr |= TCR_EPD1_DISABLE;
	} else {
		tcr = (tcr_ps_bits << TCR_EL3_PS_SHIFT);
	}

	tcr |= TCR_T0SZ(va_bits);

	/*
	 * Translation table walk is cacheable, inner/outer WBWA and
	 * inner shareable.  Due to Cortex-A57 erratum #822227 we must
	 * set TG1[1] = 4KB.
	 */
	tcr |= TCR_TG1_4K | TCR_TG0_4K | TCR_SHARED_INNER |
		   TCR_ORGN_WBWA | TCR_IRGN_WBWA;

	return tcr;
}

static inline __attribute__((always_inline)) void enable_mmu_el1(void)
{
	uint64_t register val;
	/* Set MAIR, TCR and TBBR registers */
	uint64_t register mair = MEMORY_ATTRIBUTES;

	__asm__ volatile ("msr mair_el1, %[i]" :: [i] "r" (mair));
	__asm__ volatile ("msr tcr_el1, %[i]" :: [i] "r" (get_tcr(1)));
	__asm__ volatile ("msr ttbr0_el1, %[i]" :: [i] "r" ((uint64_t)xlat_tables));
	isb();

	/* TODO: Invalidate all data caches before enable them */

	/* Enable the MMU and data cache */
	__asm__ volatile ("mrs %[r], sctlr_el1" : [r] "=r" (val));
	__asm__ volatile ("msr sctlr_el1, %[i]" :: [i] "r" (val | SCTLR_M_BIT | SCTLR_C_BIT));

	/* Ensure the MMU enable takes effect immediately */
	isb();
}

#define DESCRIPTOR_MASK			(0x3ULL)
#define PAGE_DESCRIPTOR			(0x3ULL)
#define BLOCK_DESCRIPTOR		(0x1ULL)
#define CHECK_NEXT_TABLE		(-2)
#define CHECK_FAIL				(-1)

static inline uint64_t check_table(struct mmu_ptables *ptables, uint64_t va, uint64_t *table_addr, uint32_t offset)
{
	uint32_t index = (va >> offset) & (ptables->xlat_table_size - 1);
	uint64_t *table = (uint64_t *)*table_addr;

	if (offset > 12 && ((table[index] & DESCRIPTOR_MASK) == PAGE_DESCRIPTOR)) {
		/* if PAGE_DESCRIPTOR, check next table */
		*table_addr = table[index] & 0x7FFFFFF000ULL;
		return CHECK_NEXT_TABLE;
	} else if (offset == 12 || ((table[index] & DESCRIPTOR_MASK) == BLOCK_DESCRIPTOR)) {
		/* PA[41:offset] + VA[offset-1:0] */
		return (((table[index] & 0x7FFFFFF000ULL) >> offset) << offset) |
			   ((va << (64 - offset)) >> (64 - offset));
	} else {
		/* Ignore unknown attributes */
		return CHECK_FAIL;
	}
}

uint64_t va_to_pa(struct mmu_ptables *ptables, uint64_t va)
{
	uint64_t pa;
	uint64_t table_ptr;

	if (ptables == NULL) {
		table_ptr = (uint64_t)mmu_ptables.base_xlat_table;
		ptables = &mmu_ptables;
	} else {
		table_ptr = (uint64_t)ptables->base_xlat_table;
	}

	/* Level0 */
	pa = check_table(ptables, va, &table_ptr, L0_VA_SIZE_SHIFT);
	if (pa == CHECK_FAIL)
		return CHECK_FAIL;
	else if (pa != CHECK_NEXT_TABLE)
		return pa;

	/* Level1 */
	pa = check_table(ptables, va, &table_ptr, L1_VA_SIZE_SHIFT);
	if (pa == CHECK_FAIL)
		return CHECK_FAIL;
	else if (pa != CHECK_NEXT_TABLE)
		return pa;

	/* Level2 */
	pa = check_table(ptables, va, &table_ptr, L2_VA_SIZE_SHIFT);
	if (pa == CHECK_FAIL)
		return CHECK_FAIL;
	else if (pa != CHECK_NEXT_TABLE)
		return pa;

	/* Leve3 */
	pa = check_table(ptables, va, &table_ptr, L3_VA_SIZE_SHIFT);
	if (pa == CHECK_FAIL || pa == CHECK_NEXT_TABLE)
		return CHECK_FAIL;
	else
		return pa;
}

#define CONTINUOUS		(1)
#define NOT_CONTINUOUS	(0)

static inline uint32_t check_continuous(struct mmu_ptables *ptables, uint64_t *va_start, uint64_t *va_end,
										uint64_t table_addr, uint32_t offset)
{
	uint32_t index_start = (*va_start >> offset) & (ptables->xlat_table_size - 1);
	uint32_t index_end = (*va_end >> offset) & (ptables->xlat_table_size - 1);
	uint64_t *table = (uint64_t *)table_addr;
	uint64_t temp_start;
	uint64_t temp_end;
	uint64_t first_addr = 0;
	uint64_t last_addr = 0;

	if (offset < 12) {
		return NOT_CONTINUOUS;
	}

	if (index_start == index_end) {
		temp_start = table[index_start] & 0x7FFFFFF000ULL;
		if (offset > 12 && ((table[index_start] & DESCRIPTOR_MASK) == PAGE_DESCRIPTOR)) {
			/* if PAGE_DESCRIPTOR, check next table */
			table_addr = temp_start;
			return check_continuous(ptables, va_start, va_end, table_addr, offset - 9);
		} else if ((offset == 12) || ((table[index_start] & DESCRIPTOR_MASK) == BLOCK_DESCRIPTOR)) {
			/* Same entry = Continuous physical address */
			*va_start = ((temp_start >> offset) << offset) |
						((*va_start << (64 - offset)) >> (64 - offset));
			*va_end = ((temp_start >> offset) << offset) |
					  ((*va_end << (64 - offset)) >> (64 - offset));
			return CONTINUOUS;
		} else {
			/* Ignore unknown attributes */
			return NOT_CONTINUOUS;
		}
	} else {
		/* All entries between 'index_start' & 'index_end' must be continuous */
		for (uint32_t i = index_start; i <= index_end; ++i) {
			if (i == index_start) {
				temp_start = *va_start;
				temp_end = ((i + 1) * (1ULL << offset)) - 1ULL;
			} else if (i == index_end) {
				temp_start = i * (1ULL << offset);
				temp_end = *va_end;
			} else {
				temp_start = i * (1ULL << offset);
				temp_end = ((i + 1) * (1ULL << offset)) - 1ULL;
			}

			if (check_continuous(ptables, &temp_start, &temp_end, table_addr, offset) == NOT_CONTINUOUS) {
				return NOT_CONTINUOUS;
			}

			if (i == index_start) {
				first_addr = temp_start;
				last_addr = temp_end;
			} else if ((last_addr + 1) != temp_start) {
				return NOT_CONTINUOUS;
			} else {
				last_addr = temp_end;
			}
		}

		*va_start = first_addr;
		*va_end = last_addr;
		return CONTINUOUS;
	}
}

uint32_t is_pa_continuous(struct mmu_ptables *ptables, uint64_t va_start, uint64_t va_end)
{
	uint64_t table_addr;
	uint32_t ret;

	/* MMU case */
	if (ptables == NULL) {
		table_addr = (uint64_t)mmu_ptables.base_xlat_table;
		ptables = &mmu_ptables;
	} else {
		/* SMMU case */
		table_addr = (uint64_t)ptables->base_xlat_table;
	}

	ret = check_continuous(ptables, &va_start, &va_end, table_addr, 39);

	return ret;
}

#define TABLE_ADDRESS(level0, level1, level2, level3)	\
	((0x08000000000ULL * (level0)) +					\
	 (0x00040000000ULL * (level1)) +					\
	 (0x00000200000ULL * (level2)) +					\
	 (0x00000001000ULL * (level3)))

#define PAGE_DESCRIPTOR			(0x3ULL)
#define EXECUTABLE_RW_CACHE		(0x731ULL)
#define DEVICE_RW_NON_CACHE		(0x761ULL)

void mmu_init(void)
{
	uint32_t chiplet_id = CHIPLET_ID;
	uint64_t register chiplet_offset;
	uint64_t register temp;

#if (__TARGET_CP == 0)
	BOOT_LOG(CP0, CP0_FREERTOS, START_MMU_INIT);
#else
	BOOT_LOG(CP1, CP1_FREERTOS, START_MMU_INIT);
#endif
	chiplet_offset = 0x10000000000ULL - (chiplet_id * 0x2000000000ULL);

	if (portGET_CORE_ID() == 0) {
		mmu_ptables.mmu_flat_range = (struct mmu_flat_range *)mmu_os_ranges;
		mmu_ptables.mmu_flat_range_size = ARRAY_SIZE(mmu_os_ranges);
		mmu_ptables.mmu_region = (struct mmu_region *)mmu_regions;
		mmu_ptables.mmu_region_size = ARRAY_SIZE(mmu_regions);
		mmu_ptables.base_xlat_table = xlat_tables;
		mmu_ptables.xlat_use_count = xlat_use_count;
		mmu_ptables.xlat_table_count = MAX_XLAT_TABLES;
		mmu_ptables.xlat_table_size = Ln_NUM_ENTRIES;
		mmu_ptables.flag = REBELH_MMU;

		new_table(&mmu_ptables);
		setup_page_tables(&mmu_ptables);
	}

	/* Inside 'enable_mmu_el1', chiplet_offset (x0) is changed */
	chiplet_offset = 0x10000000000ULL - (chiplet_id * 0x2000000000ULL);

	/* Vector Table + chiplet_offset  */
	__asm__ volatile ("ldr %x0, =_freertos_vector_table\n"
					  "msr vbar_el1, %x0" : "=r"(temp) : : "memory");
#ifdef ZEBU_POC
	/* LR + chiplet_offset */
	__asm__ volatile ("ldr %x0, [sp, 0x8]\n"
			"add %x0, %x0, %x1\n"
			"str %x0, [sp, 0x8]" : "+r"(temp) : "r"(chiplet_offset) : "memory");
#endif /* ZEBU_POC */

	isb();
	dmb();

	enable_mmu_el1();
#if (__TARGET_CP == 0)
	BOOT_LOG(CP0, CP0_FREERTOS, SET_STACK_POINTER);
#else
	BOOT_LOG(CP1, CP1_FREERTOS, SET_STACK_POINTER);
#endif

	/* SP + chiplet_offset */
	__asm__ volatile ("mov %x0, sp\n"
					  "add %x0, %x0, %x1\n"
					  "mov sp, %x0" : "+r"(temp) : "r"(chiplet_offset) : "memory");

	isb();
}
