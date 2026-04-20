/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2024 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#include <string.h>
#include "hal/ptw.h"
#include "hal/rbdma_if.h"
#include "rbln/cache.h"
#include "rl_errors.h"
#include "rl_sizes.h"
#include "g_sysfw_addrmap.h"
#include "assert.h"
#include "runtime_pt.h"
#include "smmu.h"

/* CHIPLET_ID macro - use get_chiplet_id() function if available */
#ifndef CHIPLET_ID
extern uint32_t get_chiplet_id(void);
#define CHIPLET_ID get_chiplet_id()
#endif

#include "rbln/log.h"

#define BIT_WIDTH_PT_L1		16	/* L1 have 65536 entries */
#define BIT_MASK_PAGE		BIT64_MASK(BIT_WIDTH_PAGE)
#define BIT_MASK_PA			GENMASK64(BIT_WIDTH_PA_MAX - 1, BIT_WIDTH_PAGE)
#define PAGE_SIZE			(1 << BIT_WIDTH_PAGE)

#define CHIPLET_BASE(n)		(CHIPLET_INTERVAL * n)

#ifndef IPA_DISABLED
/* callback function for stage 2 translation */
typedef uint64_t (*s2t_callback)(uint64_t ipa, int fid);


/* GADDR (IPA) refers to the physical memory region viewed by each VF */
#define PAGE_TABLE_GADDR			0x0
#define USER_MEMORY_GADDR			0x040000000
#define DCL_SHM_GADDR_1				0x3FC0000000
#define DCL_SHM_GADDR_2				0x1FC0000000
#define DCL_SHM_GADDR_4				0xFC0000000

#define PAGE_TABLE_SIZE_1			0x3C00000		/* 60 MB */
#define PAGE_TABLE_SIZE_2			0x3C00000		/* 60 MB */
#define PAGE_TABLE_SIZE_4			0x3C00000		/* 60 MB */

#define USER_MEMORY_SIZE_1			0x2300000000	/* 140GB */
#define USER_MEMORY_SIZE_2			0x1180000000	/* 70GB */
#define USER_MEMORY_SIZE_4			0x8C0000000		/* 35GB */
#define USER_MEMORY_PADDR_1			0x040000000

#define DCL_SHM_SIZE_1				0x010000000		/* 256MB */
#define DCL_SHM_SIZE_2				0x8000000		/* 128MB */
#define DCL_SHM_SIZE_4				0x4000000		/* 64MB */

#define USER_MEMORY_SIZE_CHIP		0x8C0000000		/* 35GB */
#define USER_MEMORY_OFF_CHIP		0x040000000

#define DCL_SHM_SIZE_CHIP			0x4000000		/* 64MB */
#define DCL_SHM_OFF_CHIP			0x1FE4000000

static s2t_callback handler;

uint64_t ptw_ipa_to_pa_1(uint64_t ipa, int fid)
{
	uint64_t pa = ipa;
	uint32_t chip_num = 0;

	if (CONFIGURATION_BASE + CONFIGURATION_SIZE > ipa && ipa >= CONFIGURATION_BASE) {
		pa -= CONFIGURATION_BASE;
		pa += BOOTLOADER_LOG_DUMP - CONFIGURATION_SIZE * fid;
	} else if (SYNC_BASE + SYNC_SIZE + PT_SIZE > ipa && ipa >= SYNC_BASE) {
		pa -= SYNC_BASE;
		pa += MMU_PT_BASE;
	} else if (USER_MEMORY_GADDR + USER_MEMORY_SIZE_1 > ipa && ipa >= USER_MEMORY_GADDR) {
		pa -= USER_MEMORY_GADDR;
		while (pa >= USER_MEMORY_SIZE_CHIP) {
			pa -= USER_MEMORY_SIZE_CHIP;
			chip_num++;
		}
		pa += USER_MEMORY_OFF_CHIP;
	} else if (DCL_SHM_GADDR_1 + DCL_SHM_SIZE_1 > ipa && ipa >= DCL_SHM_GADDR_1) {
		pa -= DCL_SHM_GADDR_1;
		while (pa >= DCL_SHM_SIZE_CHIP) {
			pa -= DCL_SHM_SIZE_CHIP;
			chip_num++;
		}
		pa += DCL_SHM_OFF_CHIP;
	} else {
		FLOG_ERR(fid, "Permission fault. FUNC%d can't access 0x%lx.\n", fid, ipa);
		return 0;
	}

	pa += CHIPLET_BASE(chip_num);

	return pa;
}

uint64_t ptw_ipa_to_pa_2(uint64_t ipa, int fid)
{
	uint64_t pa = ipa;
	uint32_t chip_num = (fid - 1) * 2;

	if (CONFIGURATION_BASE + CONFIGURATION_SIZE > ipa && ipa >= CONFIGURATION_BASE) {
		pa -= CONFIGURATION_BASE;
		pa += BOOTLOADER_LOG_DUMP - CONFIGURATION_SIZE * fid;
		chip_num = 0;
	} else if (SYNC_BASE + SYNC_SIZE + PT_SIZE > ipa && ipa >= SYNC_BASE) {
		pa -= SYNC_BASE;
		pa += MMU_PT_BASE;
	} else if (USER_MEMORY_GADDR + USER_MEMORY_SIZE_2 > ipa && ipa >= USER_MEMORY_GADDR) {
		pa -= USER_MEMORY_GADDR;
		while (pa >= USER_MEMORY_SIZE_CHIP) {
			pa -= USER_MEMORY_SIZE_CHIP;
			chip_num++;
		}
		pa += USER_MEMORY_OFF_CHIP;
	} else if (DCL_SHM_GADDR_2 + DCL_SHM_SIZE_2 > ipa && ipa >= DCL_SHM_GADDR_2) {
		pa -= DCL_SHM_GADDR_2;
		while (pa >= DCL_SHM_SIZE_CHIP) {
			pa -= DCL_SHM_SIZE_CHIP;
			chip_num++;
		}
		pa += DCL_SHM_OFF_CHIP;
	} else {
		FLOG_ERR(fid, "Permission fault. FUNC%d can't access 0x%lx.\n", fid, ipa);
		return 0;
	}

	pa += CHIPLET_BASE(chip_num);

	return pa;
}

uint64_t ptw_ipa_to_pa_4(uint64_t ipa, int fid)
{
	uint64_t pa = ipa;
	uint32_t chip_num = fid - 1;

	if (CONFIGURATION_BASE + CONFIGURATION_SIZE > ipa && ipa >= CONFIGURATION_BASE) {
		pa -= CONFIGURATION_BASE;
		pa += BOOTLOADER_LOG_DUMP - CONFIGURATION_SIZE * fid;
		chip_num = 0;
	} else if (SYNC_BASE + SYNC_SIZE + PT_SIZE > ipa && ipa >= SYNC_BASE) {
		pa -= SYNC_BASE;
		pa += MMU_PT_BASE;
	} else if (USER_MEMORY_GADDR + USER_MEMORY_SIZE_4 > ipa && ipa >= USER_MEMORY_GADDR) {
	/* Nothing */
	} else if (DCL_SHM_GADDR_4 + DCL_SHM_SIZE_4 > ipa && ipa >= DCL_SHM_GADDR_4) {
		pa -= DCL_SHM_GADDR_4;
		pa += DCL_SHM_OFF_CHIP;
	} else {
		FLOG_ERR(fid, "Permission fault. FUNC%d can't access 0x%lx.\n", fid, ipa);
		return 0;
	}

	pa += CHIPLET_BASE(chip_num);

	return pa;
}

int ptw_register_s2t_handler(int num_vf)
{
	if (num_vf == 1)
		handler = ptw_ipa_to_pa_1;
	else if (num_vf == 2)
		handler = ptw_ipa_to_pa_2;
	else if (num_vf == 4)
		handler = ptw_ipa_to_pa_4;
	else if (num_vf != 0)
		RLOG_ERR("Invalid number of VFs (%d)\n", num_vf);

	return handler ? RL_OK : RL_ERROR;
}

#if (CHIPLET_COUNT > 1)
#define USER_MEMORY_IPA_CHIP0	0x140000000 // 5GB
#define USER_MEMORY_IPA_CHIP1	0xA00000000 // 40GB
#define USER_MEMORY_IPA_CHIP2	0x12C0000000 // 75GB
#define USER_MEMORY_IPA_CHIP3	0x1B80000000 // 110GB
#define USER_MEMORY_END_IPA		0x2440000000 // 145GB

#define SCRATCH_PAD_IPA_CHIP0	0x3F80000000 // 254GB
#define SCRATCH_PAD_IPA_CHIP1	0x3F84000000
#define SCRATCH_PAD_IPA_CHIP2	0x3F88000000
#define SCRATCH_PAD_IPA_CHIP3	0x3F8C000000
#define SCRATCH_PAD_END_IPA		0x3F90000000

#define SHARED_MEM_IPA_CHIP0	0x3FC0000000 // 255GB
#define SHARED_MEM_IPA_CHIP1	0x3FC4000000
#define SHARED_MEM_IPA_CHIP2	0x3FC8000000
#define SHARED_MEM_IPA_CHIP3	0x3FCC000000
#define SHARED_MEM_END_IPA		0x3FD0000000

#define PERIPHERAL_IPA_CHIP0	0x00000000 // 0GB
#define PERIPHERAL_IPA_CHIP1	0x10000000
#define PERIPHERAL_IPA_CHIP2	0x20000000
#define PERIPHERAL_IPA_CHIP3	0x30000000
#define PERIPHERAL_END_IPA		0x40000000

#define SCRATCH_PAD_PA			0x1FE0000000
#define SHARED_MEMORY_PA		0x1FE4000000
#define PERIPHERAL_PA			0x1FF0000000

static uint64_t ptw_pf_ipa_to_pa(uint64_t ipa)
{
	uint64_t pa;
	uint32_t chip_num;

	pa = ipa;

	if (pa < PERIPHERAL_END_IPA) {
		RLOG_DBG("CP doesn't have any case to access this region. (ipa: 0x%#lx)\r\n", ipa);
		return 0;
	} else if (pa < USER_MEMORY_IPA_CHIP0) {
		pa -= PERIPHERAL_END_IPA;
		chip_num = pa / SZ_1G;
		pa = pa & (SZ_1G - 1);
	} else if (pa < USER_MEMORY_END_IPA) {
		if (pa < USER_MEMORY_IPA_CHIP1) {
			chip_num = 0;
			pa -= USER_MEMORY_IPA_CHIP0;
		} else if (pa < USER_MEMORY_IPA_CHIP2) {
			chip_num = 1;
			pa -= USER_MEMORY_IPA_CHIP1;
		} else if (pa < USER_MEMORY_IPA_CHIP3) {
			chip_num = 2;
			pa -= USER_MEMORY_IPA_CHIP2;
		} else {
			chip_num = 3;
			pa -= USER_MEMORY_IPA_CHIP3;
		}
		pa += SZ_1G;
#ifdef SMMU_FORCE
	} else if (pa < SHARED_MEM_IPA_CHIP0) {
		RLOG_DBG("Not allowed to access (ipa: 0x%#lx)\r\n", ipa);
		return 0;
#else
	} else if (pa < SCRATCH_PAD_END_IPA) {
		if (pa < SCRATCH_PAD_IPA_CHIP1) {
			chip_num = 0;
			pa -= SCRATCH_PAD_IPA_CHIP0;
		} else if (pa < SCRATCH_PAD_IPA_CHIP2) {
			chip_num = 1;
			pa -= SCRATCH_PAD_IPA_CHIP1;
		} else if (pa < SCRATCH_PAD_IPA_CHIP3) {
			chip_num = 2;
			pa -= SCRATCH_PAD_IPA_CHIP2;
		} else {
			chip_num = 3;
			pa -= SCRATCH_PAD_IPA_CHIP3;
		}
		pa += SCRATCH_PAD_PA;
	} else if (pa < SHARED_MEM_IPA_CHIP0) {
		RLOG_DBG("Not allowed to access (ipa: 0x%#lx)\r\n", ipa);
		return 0;
#endif
	} else if (pa < SHARED_MEM_END_IPA) {
		if (pa < SHARED_MEM_IPA_CHIP1) {
			chip_num = 0;
			pa -= SHARED_MEM_IPA_CHIP0;
		} else if (pa < SHARED_MEM_IPA_CHIP2) {
			chip_num = 1;
			pa -= SHARED_MEM_IPA_CHIP1;
		} else if (pa < SHARED_MEM_IPA_CHIP3) {
			chip_num = 2;
			pa -= SHARED_MEM_IPA_CHIP2;
		} else {
			chip_num = 3;
			pa -= SHARED_MEM_IPA_CHIP3;
		}
		pa += SHARED_MEMORY_PA;
	} else {
		RLOG_DBG("Not allowed to access (ipa: 0x%#lx)\r\n", ipa);
		return 0;
	}

	pa += CHIPLET_BASE(chip_num);
	return pa;
}

#else /* CHIPLET_COUNT == 1 */
#define DRAM_END_GADDR			0x900000000 /* 36GB */
#define SCRATCH_PAD_GADDR		0xF40000000 /* 61GB */
#define SCRATCH_PAD_END_GADDR	0xF44000000
#define SHARED_MEM_GADDR		0xF80000000 /* 62GB */
#define SHARED_MEM_END_GADDR	0xF84000000
#define PERIPHERAL_GADDR		0xFC0000000 /* 63GB */
#define PERIPHERAL_END_GADDR	0xFD0000000

static uint64_t ptw_pf_ipa_to_pa(uint64_t ipa)
{
	uint64_t pa;

	pa = ipa;

	if (pa < DRAM_END_GADDR) {
		return pa;
	} else if (pa < SHARED_MEM_GADDR) {
		RLOG_DBG("Not allowed to access (ipa: 0x%#lx)\r\n", ipa);
		return 0;
	} else if (pa < SHARED_MEM_END_GADDR) {
		pa -= SHARED_MEM_GADDR;
		pa += DCL0_SH_MEM_BASE;
	} else {
		RLOG_DBG("Not allowed to access (ipa: 0x%#lx)\r\n", ipa);
		return 0;
	}

	return pa;
}
#endif

uint64_t ptw_ipa_to_pa(uint64_t ipa, int fid)
{
	if (!fid)
		return ptw_pf_ipa_to_pa(ipa);

	if (handler)
		return handler(ipa, fid);
	else
		FLOG_ERR(fid, "ptw_ipa_to_pa function was not registered.\n");

	return 0;
}
#else /* IPA disabled */
int ptw_register_s2t_handler(int num_vf) { return RL_OK; }

uint64_t ptw_ipa_to_pa(uint64_t ipa, int fid)
{
	return ipa;
}
#endif
static uint32_t running_func;

static uint8_t get_pageattr(uint64_t pte)
{
	uint8_t page_mapping_type = (pte >> BIT_POS_PTE_PAGE_MAPPING_TYPE) & 0x3;

	return page_mapping_type;
}

#if !defined(MMU_V1)
#define MMU2_LAST_HOP			2
#define MMU2_HOP_SHIFT			9
#define MMU2_PT_ENTRY			512
#define MMU2_IDX_MASK			BIT64_MASK(MMU2_HOP_SHIFT)
#define MMU2_VALID_MASK			PAGE_PRESENT_MASK
#define MMU2_HOP_MASK			0x0000000000002ull
#define MMU2_UPPER_ATTR_WIDTH	14
#define MMU2_LOWER_ATTR_WIDTH	12
#define MMU2_NEXT_ADDR_MASK		GENMASK64(63 - MMU2_UPPER_ATTR_WIDTH, MMU2_LOWER_ATTR_WIDTH)

static inline bool is_shm_va(uint64_t va)
{
	const uint64_t chiplet_offset = SZ_128M;
	uint64_t base_addr;

	va = va & ((1ULL << MMU2_TASK_SHIFT) - 1);

	for (uint32_t chiplet_id = 0; chiplet_id < MAX_CHIPLET_COUNT; chiplet_id++) {
		base_addr = RL_SHM_VA_BASE_ADDR + (chiplet_id * chiplet_offset);
		if (va >= base_addr && va < (base_addr + RL_SHM_SIZE))
			return true;
	}

	return false;
}

uint64_t *ptw_get_pte(uint64_t *base, int hop, uint64_t va)
{
	int idx, shift;
	uint64_t *ptr, *next_base;
	uint64_t entry;

	shift = BIT_WIDTH_PAGE + MMU2_HOP_SHIFT * (MMU2_LAST_HOP - hop);
	idx = (va >> shift) & MMU2_IDX_MASK;

	if (idx > MMU2_PT_ENTRY) {
		RLOG_DBG("%s: addr %lx hop %d idx %x\r\n", __func__, va, hop, idx);
		return NULL;
	}

	base = (uint64_t *)ptw_ipa_to_pa((uint64_t)base, running_func);
	ptr = (uint64_t *)PA_TO_CPVA((uint64_t)base) + idx;
	entry = *ptr;

	if (!(entry & MMU2_VALID_MASK)) {
		if (is_shm_va(va)) {
			RLOG_DBG("%s: pte not valid for shm addr %lx hop %d idx %x entry %lx\r\n",
				__func__, va, hop, idx, entry);
			return NULL;
		}
		RLOG_ERR("%s: Page fault! entry invalid addr %lx hop %d idx %x entry %lx\r\n",
			__func__, va, hop, idx, entry);
		inv_dcache_range((uintptr_t)ptr, sizeof(uint64_t));
		RLOG_ERR("%s: After inv_dcache entry %lx\r\n", __func__, *ptr);
		return NULL;
	}

	if (hop == MMU2_LAST_HOP)
		return ptr;

	if (!(entry & MMU2_HOP_MASK))
		return ptr;

	RLOG_VER("%s: addr %lx hop %d idx %x entry %lx in pt %lx\r\n",
			 __func__, va, hop, idx, entry, base);

	next_base = (uint64_t *)(entry & MMU2_NEXT_ADDR_MASK);
	return ptw_get_pte(next_base, hop + 1, va);
}
#else
uint64_t *ptw_get_pte(uint64_t *base, int lvl, uint64_t va)
{
	int l1_offset;

	l1_offset = (va >> BIT_WIDTH_PAGE) & BIT_MASK(BIT_WIDTH_PT_L1);
	return base + l1_offset;
}
#endif

uint64_t ptw_va_to_ipa(uint64_t va, uint64_t *ttb, const union proc_exec_id *id_info)
{
	uint64_t ipa;
	uint64_t pte;
	uint64_t *pte_paddr;
	uint64_t htid, func_id, proc_id;

	htid = id_info->htid;
	func_id = id_info->func_id;
	proc_id = id_info->proc_id;

#if !defined(MMU_V1)
	va |= (uint64_t) htid << MMU2_TASK_SHIFT;
#endif
	pte_paddr = ptw_get_pte(ttb, 0, va);

	if (!pte_paddr)
		return 0;

	pte = *pte_paddr;
	ipa = pte & BIT_MASK_PA;

	return ipa | (va & BIT_MASK_PAGE);
}

uint64_t ptw_virt_to_phys(uint64_t va, uint64_t *ttb, const union proc_exec_id *id_info)
{
	uint64_t pa;

	pa = ptw_va_to_ipa(va, ttb, id_info);

#ifndef IPA_DISABLED
	pa = ptw_ipa_to_pa(pa, id_info->func_id);
#endif

	return pa | (va & BIT_MASK_PAGE);
}

/* Note that it returns ppn padded by page attribute in msb */
union ptw_pn ptw_vpn_to_ppn(uint32_t vpn, uint64_t *ttb, const union proc_exec_id *id_info)
{
	uint64_t pa, va;
	uint64_t pte;
	uint64_t *pte_paddr;
	uint64_t htid, func_id, proc_id;
	union ptw_pn pn = { 0 };

	htid = id_info->htid;
	func_id = id_info->func_id;
	proc_id = id_info->proc_id;

	va = (uint64_t)vpn << BIT_WIDTH_PAGE;
#if !defined(MMU_V1)
	va |= (uint64_t)htid << MMU2_TASK_SHIFT;
#endif
	pte_paddr = ptw_get_pte(ttb, 0, va);

	if (!pte_paddr)
		return pn;

	pte = *pte_paddr;
	pn.mapping_type = get_pageattr(pte);
	pa = pte & BIT_MASK_PA;
#ifndef IPA_DISABLED
	pa = ptw_ipa_to_pa(pa, func_id);
#endif

	pn.ppn = pa >> BIT_WIDTH_PAGE;

	return pn;
}

uint32_t ptw_flush_page_tables(uint64_t l0addr, bool flush)
{
	uint32_t flush_count = 0;
	uint32_t size = SZ_4K;

	void (*dcache_op)(uintptr_t, size_t) = flush ? flush_dcache_range : inv_dcache_range;

	l0addr = ptw_ipa_to_pa(l0addr, running_func);
	l0addr = PA_TO_CPVA(l0addr);

	dcache_op(l0addr, size);
	flush_count++;
#if !defined(MMU_V1)
	uint64_t entry;
	uint64_t l1addr, l2addr;

	for (uint32_t idx0 = 0; idx0 < MMU2_PT_ENTRY; idx0++) {
		entry = *(uint64_t *)l0addr;

		if (entry & MMU2_VALID_MASK) {
			l1addr = ptw_ipa_to_pa(entry & MMU2_NEXT_ADDR_MASK, running_func);
			l1addr = PA_TO_CPVA(l1addr);

			dcache_op(l1addr, size);
			flush_count++;
			for (uint32_t idx1 = 0; idx1 < MMU2_PT_ENTRY; idx1++) {
				entry = *(uint64_t *)l1addr;

				if (entry & MMU2_VALID_MASK) {
					l2addr = ptw_ipa_to_pa(entry & MMU2_NEXT_ADDR_MASK, running_func);
					l2addr = PA_TO_CPVA(l2addr);

					dcache_op(l2addr, size);
					flush_count++;
				}
				l1addr += sizeof(uint64_t);
			}
		}
		l0addr += sizeof(uint64_t);
	}
#endif

	RLOG_DBG("%d page tables %s \r\n", flush_count, flush ? "flushed" : "invalidated");

	return flush_count;
}

#define _FIRST_BIT_POS(x) ((x) ? (31 - __builtin_clz(x)) : -1)
#define PF_S2TT_ADDR (0x14080000ULL)

static int ptw_init_smmu_s2_vf(uint32_t vf, uint32_t num_vfs, uint64_t *tt_base, uint32_t cl_id)
{
	assert(num_vfs > 0);

	struct mmu_region *vf_mmu_region;
	uint32_t i = _FIRST_BIT_POS(num_vfs);
	uint16_t ptw_xlat_use_count[MAX_XLAT_TABLES];
	uint64_t l1base;

	vf_mmu_region = *(vf_mmu_regions[i] + vf);

	struct mmu_ptables ptw_smmu_s2tables = {
		.mmu_flat_range = NULL,
		.mmu_flat_range_size = 0,
		.mmu_region = vf_mmu_region,
		.mmu_region_size = size_vf_region_array[i],
		.base_xlat_table = (uint64_t *)*tt_base,
		.xlat_use_count = ptw_xlat_use_count,
		.xlat_table_count = MAX_XLAT_TABLES,
		.xlat_table_size = Ln_NUM_ENTRIES,
		.flag = 0,
		.s2 = true,
	};

	/*
	 * Page table mapping policy:
	 *
	 * - Chiplet0 (Primary chiplet):
	 *   Holds the page tables for all VFs.
	 *   The system memory region for each VF is mapped to the physical address
	 *   of the logical primary chiplet where that VF is actually running.
	 *
	 * - Secondary chiplets:
	 *   Hold only the page tables for the VFs assigned to them.
	 *   The system memory region is mapped to their own chiplet’s physical address.
	 */
	if (strcmp(vf_mmu_region[0].name, "PAGE TABLE") == 0)
		vf_mmu_region[0].base_pa += CHIPLET_BASE(cl_id);
	else
		RLOG_ERR("The first index of the MMU region array must be the page table mapping.\r\n");

	for (uint32_t j = 0; j < MAX_XLAT_TABLES; j++)
		ptw_xlat_use_count[j] = 0;

	new_table(&ptw_smmu_s2tables);
	setup_page_tables(&ptw_smmu_s2tables);

	l1base = *(uint64_t *)(*tt_base) & MMU2_NEXT_ADDR_MASK;
	smmu_s2_enable(vf + 1, l1base);

	RLOG_DBG("Stage 2 page table generated for VF%d (tt_base: 0x%lx)\n", vf, *tt_base);

	for (uint32_t j = 0; j < MAX_XLAT_TABLES; j++)
		if (ptw_xlat_use_count[j])
			*tt_base += SZ_4K;

	/* ToDo: Need to verify that tt_base does not exceed the SMMU memory region. */
	return 0;
}

void ptw_init_smmu_s2(uint32_t num_vfs)
{
	uint32_t cl_id = CHIPLET_ID;
	uint64_t tt_base = PF_S2TT_ADDR + CHIPLET_BASE(cl_id);
	uint64_t l1base;
	uint16_t ptw_xlat_use_count[MAX_XLAT_TABLES];

	for (uint32_t i = 0; i < MAX_XLAT_TABLES; i++)
		ptw_xlat_use_count[i] = 0;

	if (num_vfs) {
		uint32_t vf = cl_id * num_vfs / CHIPLET_COUNT;

		ptw_init_smmu_s2_vf(vf, num_vfs, &tt_base, cl_id);
		running_func = vf + 1;

		if (cl_id == 0)
			for (vf = 1; vf < num_vfs; vf++)
				ptw_init_smmu_s2_vf(vf, num_vfs, &tt_base, cl_id);

		return;
	}

	struct mmu_ptables ptw_smmu_s2tables = {
		.mmu_flat_range = NULL,
		.mmu_flat_range_size = 0,
		.mmu_region = ptw_s2t_pf,
		.mmu_region_size = (sizeof(ptw_s2t_pf) / sizeof((ptw_s2t_pf)[0])),
		.base_xlat_table = (uint64_t *)tt_base,
		.xlat_use_count = ptw_xlat_use_count,
		.xlat_table_count = MAX_XLAT_TABLES,
		.xlat_table_size = Ln_NUM_ENTRIES,
		.flag = 0,
		.s2 = true,
	};

	ptw_s2t_pf[0].base_pa |= CHIPLET_BASE(cl_id);

	new_table(&ptw_smmu_s2tables);
	setup_page_tables(&ptw_smmu_s2tables);

/*
 * SMMU stage 2 translation is configured to start at level-1, whereas
 * the MMU driver generates translation table which starts at level-0.
 * The starting address of the level-1 page table is obtained from the level-0
 * page table and used as S2TT.
 */
	l1base = *(uint64_t *)tt_base & GENMASK64(50, 12);

	smmu_s2_enable(0, l1base);
	running_func = 0;
}

#ifdef __TARGET_DEBUG__
void ptw_check_addr_valid(uint64_t va, uint64_t pa, const union proc_exec_id *id_info)
{
	uint64_t masked_va = va & MMU2_TASK_SHIFT;
	uint32_t func_id = id_info->func_id;
	uint32_t ctx_id = id_info->ctx_id;
	uint32_t cl_id = CHIPLET_ID;

	if (masked_va >= SHM_VA_START(cl_id) && masked_va < SHM_VA_START(cl_id) + RL_SHM_SIZE) {
		if (pa < SHM_PA_START(cl_id) || pa >= SHM_PA_START(cl_id) + RL_SHM_SIZE) {
			RLOG_ERR("%s: va(%#lx) is in shm range but pa(%#lx) is not in shm range\r\n",
					 __func__, masked_va, pa);
			abort_guilty_ctx(func_id, ctx_id, ERR_INVALID_SHM_ADDR);
		}
	} else if (masked_va >= DRAM_VA_START_ADDR && masked_va < DRAM_VA_END_ADDR) {
		if (pa < DRAM_PA_START(cl_id) || pa >= DRAM_PA_START(cl_id) + DRAM_SIZE_PER_CL) {
			RLOG_ERR("%s: va(%#lx) is in dram range but pa(%#lx) is not in dram range\r\n",
					 __func__, masked_va, pa);
			abort_guilty_ctx(func_id, ctx_id, ERR_INVALID_DRAM_ADDR);
		}
	}
}
#endif
