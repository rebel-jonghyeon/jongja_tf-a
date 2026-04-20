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

#include <stdint.h>
#include <stdbool.h>

#define MAX_XLAT_TABLES     40

/*
 * TCR definitions.
 */
#define TCR_EL1_IPS_SHIFT   32U
#define TCR_EL2_PS_SHIFT    16U
#define TCR_EL3_PS_SHIFT    16U

#define TCR_T0SZ_SHIFT      0U
#define TCR_T0SZ(x)     ((64 - (x)) << TCR_T0SZ_SHIFT)

#define TCR_IRGN_NC     (0ULL << 8)
#define TCR_IRGN_WBWA       (1ULL << 8)
#define TCR_IRGN_WT     (2ULL << 8)
#define TCR_IRGN_WBNWA      (3ULL << 8)
#define TCR_IRGN_MASK       (3ULL << 8)
#define TCR_ORGN_NC     (0ULL << 10)
#define TCR_ORGN_WBWA       (1ULL << 10)
#define TCR_ORGN_WT     (2ULL << 10)
#define TCR_ORGN_WBNWA      (3ULL << 10)
#define TCR_ORGN_MASK       (3ULL << 10)
#define TCR_SHARED_NON      (0ULL << 12)
#define TCR_SHARED_OUTER    (2ULL << 12)
#define TCR_SHARED_INNER    (3ULL << 12)
#define TCR_TG0_4K      (0ULL << 14)
#define TCR_TG0_64K     (1ULL << 14)
#define TCR_TG0_16K     (2ULL << 14)
#define TCR_EPD1_DISABLE    (1ULL << 23)
#define TCR_TG1_16K     (1ULL << 30)
#define TCR_TG1_4K      (2ULL << 30)
#define TCR_TG1_64K     (3ULL << 30)

#define TCR_PS_BITS_4GB     0x0ULL
#define TCR_PS_BITS_64GB    0x1ULL
#define TCR_PS_BITS_1TB     0x2ULL
#define TCR_PS_BITS_4TB     0x3ULL
#define TCR_PS_BITS_16TB    0x4ULL
#define TCR_PS_BITS_256TB   0x5ULL

/*
 * Block and Page descriptor attributes fields
 */
#define PTE_BLOCK_DESC_MEMTYPE(x)   (x << 2)
#define PTE_BLOCK_DESC_NS       (1ULL << 5)
#define PTE_BLOCK_DESC_AP_ELx       (1ULL << 6)
#define PTE_BLOCK_DESC_AP_EL_HIGHER (0ULL << 6)
#define PTE_BLOCK_DESC_S2AP_NONE	(0x0ULL << 6)
#define PTE_BLOCK_DESC_S2AP_RO		(0x1ULL << 6)
#define PTE_BLOCK_DESC_S2AP_WO		(0x2ULL << 6)
#define PTE_BLOCK_DESC_S2AP_RW		(0x3ULL << 6)
#define PTE_BLOCK_DESC_AP_RO        (1ULL << 7)
#define PTE_BLOCK_DESC_AP_RW        (0ULL << 7)
#define PTE_BLOCK_DESC_NON_SHARE    (0ULL << 8)
#define PTE_BLOCK_DESC_OUTER_SHARE  (2ULL << 8)
#define PTE_BLOCK_DESC_INNER_SHARE  (3ULL << 8)
#define PTE_BLOCK_DESC_AF       (1ULL << 10)
#define PTE_BLOCK_DESC_NG       (1ULL << 11)
#define PTE_BLOCK_DESC_PXN      (1ULL << 53)
#define PTE_BLOCK_DESC_UXN      (1ULL << 54)
#define PTE_BLOCK_DESC_S2NS		(1ULL << 55)

#define PTE_DESC_TYPE_MASK  3U
#define PTE_BLOCK_DESC      1U
#define PTE_TABLE_DESC      3U
#define PTE_PAGE_DESC       3U
#define PTE_INVALID_DESC    0U

#define MT_TYPE_MASK        0x7U
#define MT_TYPE(attr)       (attr & MT_TYPE_MASK)
#define MT_DEVICE_nGnRnE    0U
#define MT_DEVICE_nGnRE     1U
#define MT_DEVICE_GRE       2U
#define MT_NORMAL_NC        3U
#define MT_NORMAL           4U
#define MT_NORMAL_WT        5U

#define MEMORY_ATTRIBUTES	((0x00ULL << (MT_DEVICE_nGnRnE * 8))	|	\
							 (0x04ULL << (MT_DEVICE_nGnRE * 8))		|	\
							 (0x0CULL << (MT_DEVICE_GRE * 8))		|	\
							 (0x44ULL << (MT_NORMAL_NC * 8))		|	\
							 (0xFFULL << (MT_NORMAL * 8))			|	\
							 (0xBBULL << (MT_NORMAL_WT * 8)))

#define MT_PERM_SHIFT       3U
#define MT_SEC_SHIFT        4U
#define MT_P_EXECUTE_SHIFT  5U
#define MT_U_EXECUTE_SHIFT  6U
#define MT_RW_AP_SHIFT      7U
#define MT_NO_OVERWRITE_SHIFT   8U
#define MT_NON_GLOBAL_SHIFT 9U

#define MT_RO           (0U << MT_PERM_SHIFT)
#define MT_RW           (1U << MT_PERM_SHIFT)

#define MT_RW_AP_ELx        (1U << MT_RW_AP_SHIFT)
#define MT_RW_AP_EL_HIGHER  (0U << MT_RW_AP_SHIFT)

#define MT_SECURE       (0U << MT_SEC_SHIFT)
#define MT_NS           (1U << MT_SEC_SHIFT)

#define MT_P_EXECUTE        (0U << MT_P_EXECUTE_SHIFT)
#define MT_P_EXECUTE_NEVER  (1U << MT_P_EXECUTE_SHIFT)

#define MT_U_EXECUTE        (0U << MT_U_EXECUTE_SHIFT)
#define MT_U_EXECUTE_NEVER  (1U << MT_U_EXECUTE_SHIFT)

#define MT_NO_OVERWRITE     (1U << MT_NO_OVERWRITE_SHIFT)

#define MT_G            (0U << MT_NON_GLOBAL_SHIFT)
#define MT_NG           (1U << MT_NON_GLOBAL_SHIFT)

#define MT_P_RW_U_RW        (MT_RW | MT_RW_AP_ELx | MT_P_EXECUTE_NEVER | MT_U_EXECUTE_NEVER)
#define MT_P_RW_U_NA        (MT_RW | MT_RW_AP_EL_HIGHER  | MT_P_EXECUTE_NEVER | MT_U_EXECUTE_NEVER)
#define MT_P_RWX_U_NA       (MT_RW | MT_RW_AP_EL_HIGHER | MT_P_EXECUTE | MT_U_EXECUTE)
#define MT_P_RO_U_RO        (MT_RO | MT_RW_AP_ELx | MT_P_EXECUTE_NEVER | MT_U_EXECUTE_NEVER)
#define MT_P_RO_U_NA        (MT_RO | MT_RW_AP_EL_HIGHER  | MT_P_EXECUTE_NEVER | MT_U_EXECUTE_NEVER)
#define MT_P_RO_U_RX        (MT_RO | MT_RW_AP_ELx | MT_P_EXECUTE_NEVER | MT_U_EXECUTE)
#define MT_P_RX_U_RX        (MT_RO | MT_RW_AP_ELx | MT_P_EXECUTE | MT_U_EXECUTE)
#define MT_P_RX_U_NA        (MT_RO | MT_RW_AP_EL_HIGHER  | MT_P_EXECUTE | MT_U_EXECUTE_NEVER)

/*
 * 48-bit address with 4KB granule size:
 *
 * +------------+------------+------------+------------+-----------+
 * | VA [47:39] | VA [38:30] | VA [29:21] | VA [20:12] | VA [11:0] |
 * +---------------------------------------------------------------+
 * |     L0     |     L1     |     L2     |     L3     | page off  |
 * +------------+------------+------------+------------+-----------+
 */

#define PAGE_SIZE_SHIFT     12U

#define VA_SIZE_SHIFT_MAX   48U

#define LAST_LEVEL          3U
#define VA_BITS             41

#define L3_VA_SIZE_SHIFT   PAGE_SIZE_SHIFT
#define Ln_VA_SIZE_SHIFT   (PAGE_SIZE_SHIFT - 3)
#define L2_VA_SIZE_SHIFT   (L3_VA_SIZE_SHIFT + Ln_VA_SIZE_SHIFT)
#define L1_VA_SIZE_SHIFT   (L2_VA_SIZE_SHIFT + Ln_VA_SIZE_SHIFT)
#define L0_VA_SIZE_SHIFT   (L1_VA_SIZE_SHIFT + Ln_VA_SIZE_SHIFT)

#define LEVEL_TO_VA_SIZE_SHIFT(level)           \
	(PAGE_SIZE_SHIFT + (Ln_VA_SIZE_SHIFT *      \
	(LAST_LEVEL - (level))))

#define Ln_NUM_ENTRIES ((1U << PAGE_SIZE_SHIFT) / 8U)

#define XLAT_TABLE_VA_IDX(va_addr, level) \
	((va_addr >> LEVEL_TO_VA_SIZE_SHIFT(level)) & (Ln_NUM_ENTRIES - 1))


/*
 * Calculate the initial translation table level from VA_BITS
 * For a 4 KB page size:
 *
 * (va_bits <= 21)   - base level 3
 * (22 <= va_bits <= 30) - base level 2
 * (31 <= va_bits <= 39) - base level 1
 * (40 <= va_bits <= 48) - base level 0
 */

#define GET_BASE_XLAT_LEVEL(va_bits)                \
	 ((va_bits > L0_VA_SIZE_SHIFT) ? 0U        \
	: (va_bits > L1_VA_SIZE_SHIFT) ? 1U        \
	: (va_bits > L2_VA_SIZE_SHIFT) ? 2U : 3U)

/* Level for the base XLAT */
#define BASE_XLAT_LEVEL GET_BASE_XLAT_LEVEL(VA_BITS)

#define TCR_PS_BITS_1TB     0x2ULL
#define TCR_PS_BITS TCR_PS_BITS_1TB

/* Upper and lower attributes mask for page/block descriptor */
#define DESC_ATTRS_UPPER_MASK   RL_GENMASK64(63, 51)
#define DESC_ATTRS_LOWER_MASK   RL_GENMASK64(11, 2)

#define DESC_ATTRS_MASK     (DESC_ATTRS_UPPER_MASK | DESC_ATTRS_LOWER_MASK)

struct mmu_flat_range {
	const char *name;
	void *start;
	void *end;
	uint32_t attrs;
};

struct mmu_region {
	uint64_t base_pa;
	uint64_t base_va;
	uint64_t size;
	const char *name;
	uint32_t attrs;
};

struct mmu_ptables {
	struct mmu_flat_range *mmu_flat_range;
	uint32_t mmu_flat_range_size;
	struct mmu_region *mmu_region;
	uint32_t mmu_region_size;
	uint64_t *base_xlat_table;
	uint16_t *xlat_use_count;
	uint32_t xlat_table_count;
	uint32_t xlat_table_size;
	uint32_t flag;
	bool s2;
};

#define REBELH_MMU	(1U)

#define MMU_REGION_ENTRY(_name, _base_pa, _base_va, _size, _attrs) \
	{\
		.name = _name, \
		.base_pa = _base_pa, \
		.base_va = _base_va, \
		.size = _size, \
		.attrs = _attrs, \
	}

#define MMU_REGION_FLAT_ENTRY(name, adr, sz, attrs) \
	MMU_REGION_ENTRY(name, adr, adr, sz, attrs)

uint64_t *new_table(struct mmu_ptables *ptables);
void setup_page_tables(struct mmu_ptables *ptables);
uint64_t va_to_pa(struct mmu_ptables *ptables, uint64_t va);
uint32_t is_pa_continuous(struct mmu_ptables *ptables, uint64_t va_start, uint64_t va_end);
void mmu_init(void);
