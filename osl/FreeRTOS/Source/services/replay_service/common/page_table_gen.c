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

#include <stdbool.h>
#include "rbln/memory.h"
#include "rl_sizes.h"
#include "rbln/log.h"
#include "rl_utils.h"
#include "rbln/rebel.h"
#include "hal/ptw.h"
#include "rbln/abort.h"
#include "g_sys_addrmap.h"
#include "hal/hw_spec.h"
#include "rbln/core.h"
#include "mmu.h"
#include "common/page_table_gen.h"

const uint64_t page_table_addr = MMU_PT_BASE;

uint64_t page_table_get(void)
{
	return page_table_addr;
}

#if !defined(MMU_V1)
#define MAX_XLAT_TABLES_TEST 256

static uint16_t ut_use_count[MAX_XLAT_TABLES_TEST];

struct mmu_ptables ut_page_tables[] = {
	{
		.mmu_flat_range = NULL,
		.mmu_flat_range_size = 0,
		.mmu_region = NULL,
		.mmu_region_size = 0,
		.base_xlat_table = (void *)MMU_PT_BASE,
		.xlat_use_count = ut_use_count,
		.xlat_table_count = MAX_XLAT_TABLES_TEST,
		.xlat_table_size = Ln_NUM_ENTRIES,
		.flag = 0,
	},
};

#define TABLE_SIZE (Ln_NUM_ENTRIES * sizeof(uint64_t))

/* It generates page tables only with 2MB granule */
void page_table_init(uint64_t dram_va_start, uint64_t dram_size, int cl_affin, bool shm_intlv)
{
	uint64_t cl_id;
	uint64_t offset, remain;
	uint32_t i;

	for (i = 0; i < MAX_XLAT_TABLES_TEST; i++) {
		if (ut_use_count[i]) {
			ut_use_count[i] = 0;
			memset((void *)(MMU_PT_BASE + i * TABLE_SIZE), 0, TABLE_SIZE);
		}
	}

	while (cl_affin) {
		cl_id = __builtin_ffsl(cl_affin) - 1;
		offset = 0;
		remain = dram_size;
		i = 1;

		struct mmu_region ut_regions[128] = {
			MMU_REGION_ENTRY("SP",
				cl_base[cl_id] + DCL0_SP_MEM_BASE,
				cl_id * (RL_SPM_SIZE + RL_SHM_SIZE) + RL_SPM_VA_BASE_ADDR,
				RL_SPM_SIZE,
				MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS | MT_NG),
			MMU_REGION_ENTRY("SHM",
				cl_base[cl_id] + DCL0_SH_MEM_BASE,
				cl_id * (RL_SPM_SIZE + RL_SHM_SIZE) + RL_SHM_VA_BASE_ADDR,
				RL_SHM_SIZE,
				MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS | MT_NG),
		};

		if (shm_intlv) {
			uint32_t num_entry = RL_SHM_SIZE / SZ_2M;
			uint64_t base_va = cl_id * (RL_SPM_SIZE + RL_SHM_SIZE) + RL_SHM_VA_BASE_ADDR;
			uint64_t base_pa;

			for (uint32_t j = 0; j < num_entry; j++) {
				base_pa = cl_base[cl_id] + (j % 2 == 0 ? DCL0_SH_MEM_BASE : DCL1_SH_MEM_BASE);
				ut_regions[i].base_pa = base_pa + SZ_2M * (j >> 1);
				ut_regions[i].base_va = base_va + j * SZ_2M;
				ut_regions[i].size = SZ_2M;
				ut_regions[i].name = "SHM";
				ut_regions[i].attrs = MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS | MT_NG;
				i++;
			}
		} else {
			i++;
		}

		while (remain >= SZ_1G) {
			ut_regions[i].base_pa = cl_base[cl_id] + DRAMUSERREGIONBASE + offset;
			ut_regions[i].base_va = dram_va_start + offset;
			ut_regions[i].size = SZ_512M;
			ut_regions[i].name = "DRAM";
			ut_regions[i].attrs = MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG;
			i++;

			offset += SZ_512M;
			remain -= SZ_512M;
		}
		ut_regions[i].base_pa = cl_base[cl_id] + DRAMUSERREGIONBASE + offset;
		ut_regions[i].base_va = dram_va_start + offset;
		ut_regions[i].size = remain;
		ut_regions[i].name = "DRAM";
		ut_regions[i].attrs = MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG;
		i++;

		ut_page_tables[0].mmu_region = ut_regions;
		ut_page_tables[0].mmu_region_size = i;

		new_table(&ut_page_tables[0]);
		setup_page_tables(&ut_page_tables[0]);

		RL_CLR_BIT(cl_affin, cl_id);
		RLOG_INFO("%s: page table generated for cl%d va%#llx sz%#llx\r\n", __func__, cl_id,
				  dram_va_start, dram_size);
		dram_va_start += dram_size;
	}

	ptw_flush_page_tables((uint64_t)MMU_PT_BASE, true);
}

#define PA_OFFSET_HTID SZ_1G
void page_table_init_mp(struct st_alloc_info *info, int n)
{
	int htid;
	uint64_t va_offset;
	struct mmu_region *region;
	uint64_t private_pa[MAX_HTID] = {DRAMUSERREGIONBASE + PA_OFFSET_HTID * 1ull,
									 DRAMUSERREGIONBASE + PA_OFFSET_HTID * 2ull,
									 DRAMUSERREGIONBASE + PA_OFFSET_HTID * 3ull,
									 DRAMUSERREGIONBASE + PA_OFFSET_HTID * 4ull};
	struct mmu_region ut_regions[128] = {
		MMU_REGION_ENTRY("SP0",
			DCL0_SP_MEM_BASE,
			RL_SPM_VA_BASE_ADDR,
			RL_SPM_SIZE,
			MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS | MT_NG),
		MMU_REGION_ENTRY("SHM0",
			DCL0_SH_MEM_BASE,
			RL_SHM_VA_BASE_ADDR,
			RL_SHM_SIZE,
			MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS | MT_NG),
		/* sp and shm for Process 1 */
		MMU_REGION_ENTRY("SP1",
			DCL0_SP_MEM_BASE,
			RL_SPM_VA_BASE_ADDR | (1ull << MMU2_TASK_SHIFT),
			RL_SPM_SIZE,
			MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS | MT_NG),
		MMU_REGION_ENTRY("SHM1",
			DCL0_SH_MEM_BASE,
			RL_SHM_VA_BASE_ADDR | (1ull << MMU2_TASK_SHIFT),
			RL_SHM_SIZE,
			MT_DEVICE_nGnRnE | MT_P_RW_U_RW | MT_NS | MT_NG),
	};

	for (int i = 0; i < n; i++) {
		region = &ut_regions[4 + i];
		va_offset = info[i].va & BIT64_MASK(MMU2_TASK_SHIFT);

		if (info[i].type == PTW_MAPPING_TYPE_INTERMEDIATE) {
			region->base_va = info[i].va;
			region->base_pa = DRAMUSERREGIONBASE + (va_offset - DRAM_VA_START_ADDR);
			region->size = info[i].size;
		} else if (info[i].type == PTW_MAPPING_TYPE_PRIVATE) {
			htid = info[i].va >> MMU2_TASK_SHIFT;
			region->base_va = info[i].va;
			region->base_pa = private_pa[htid] + (va_offset - DRAM_VA_START_ADDR);
			region->size = info[i].size;
		} else {
			RLOG_ERR("not supported memory type %d\r\n", info[i].type);
			rl_abort_event(ERR_UNKNOWN);
		}

		region->name = "DRAM";
		region->attrs = MT_NORMAL | MT_P_RW_U_RW | MT_NS | MT_NG;
		RLOG_DBG("Region %s %#lx->%#lx(%#lx)\r\n", info[i].name, region->base_va, region->base_pa, region->size);
	}

	ut_page_tables[0].mmu_region = ut_regions;
	ut_page_tables[0].mmu_region_size = n + 4;

	new_table(&ut_page_tables[0]);
	setup_page_tables(&ut_page_tables[0]);
}

#else
static void page_table_generate_spm(uint64_t cl_id)
{
	uint32_t num_entry;
	uint64_t va, pa;
	uint64_t *pte_paddr;
	uint64_t *pte_start;

	/* spm */
	va = cl_id * (RL_SPM_SIZE + RL_SHM_SIZE) + RL_SPM_VA_BASE_ADDR;
	pa = cl_base[cl_id] + DCL0_SP_MEM_BASE;
	num_entry = RL_SPM_SIZE / SZ_2M;
	pte_start = ptw_get_pte((uint64_t *) page_table_addr, 0, va);
	for (uint32_t i = 0; i < num_entry; i++) {
		pte_paddr = ptw_get_pte((uint64_t *) page_table_addr, 0, va);
		*pte_paddr = (pa + SZ_2M * i) | PAGE_PRESENT_MASK;
		va += (1 << BIT_WIDTH_PAGE);
	}

	cpu_flush_dcache_range((uintptr_t)pte_start, num_entry * 8);
}

static void page_table_generate_shm(uint64_t cl_id, bool intlv)
{
	uint32_t num_entry;
	uint64_t va, pa_dcl0, pa_dcl1;
	uint64_t *pte_paddr;
	uint64_t *pte_start;

	/* shm */
	va = cl_id * (RL_SPM_SIZE + RL_SHM_SIZE) + RL_SHM_VA_BASE_ADDR;
	pa_dcl0 = cl_base[cl_id] + DCL0_SH_MEM_BASE;
	pa_dcl1 = cl_base[cl_id] + DCL1_SH_MEM_BASE;
	num_entry = RL_SHM_SIZE / SZ_2M;
	pte_start = ptw_get_pte((uint64_t *) page_table_addr, 0, va);
	for (uint32_t i = 0; i < num_entry; i++) {
		pte_paddr = ptw_get_pte((uint64_t *) page_table_addr, 0, va);
		if (intlv) {
			if (i % 2 == 0)
				*pte_paddr = (pa_dcl0 + SZ_2M * (i >> 1)) | PAGE_PRESENT_MASK;
			else
				*pte_paddr = (pa_dcl1 + SZ_2M * (i >> 1)) | PAGE_PRESENT_MASK;
		} else {
			*pte_paddr = (pa_dcl0 + SZ_2M * i) | PAGE_PRESENT_MASK;
		}
		va += (1 << BIT_WIDTH_PAGE);
	}

	cpu_flush_dcache_range((uintptr_t)pte_start, num_entry * 8);
}

static void page_table_generate_dram(uint64_t cl_id, uint64_t va_start, uint64_t size)
{
	uint64_t num_entry;
	uint64_t va, pa;
	uint64_t *pte_paddr;
	uint64_t *pte_start;

	va = va_start;
	pa = cl_base[cl_id] + DRAMUSERREGIONBASE;
	size = MIN(size, RL_DRAM_SIZE);
	if (size % SZ_2M != 0) {
		RLOG_ERR("%s: size has to be 2MB aligned, %#llx\r\n", __func__, size);
		rl_abort_event(ERR_INVALID_CTX);
	}

	num_entry = size / SZ_2M;

	pte_start = ptw_get_pte((uint64_t *) page_table_addr, 0, va);
	for (uint64_t i = 0; i < num_entry; i++) {
		pte_paddr = ptw_get_pte((uint64_t *) page_table_addr, 0, va);
		*pte_paddr = (pa + SZ_2M * i) | PAGE_PRESENT_MASK;
		va += (1 << BIT_WIDTH_PAGE);
	}

	cpu_flush_dcache_range((uintptr_t)pte_start, num_entry * 8);
}

/*
 * Generate page table for SPM(64MB), SHM(64MB) for each chiplets
 * CL0 VA SPM		[0x0, 0x400_0000)
 * CL0 VA SHM		[0x400_0000, 0x800_0000)
 * CL1 VA SPM		[0x800_0000, 0xc00_0000)
 * CL1 VA SHM		[0xc00_0000, 0x1000_0000)
 * CL2 VA SPM		[0x1000_0000, 0x1400_0000)
 * CL2 VA SHM		[0x1400_0000, 0x1800_0000)
 * CL3 VA SPM		[0x1800_0000, 0x1c00_0000)
 * CL3 VA SHM		[0x1c00_0000, 0x2000_0000)
 *
 * VA USER DRAM	XGB for each chiplets (16GB example)
 * CL0 VA DRAM		[0x1_0000_0000, 0x5_0000_0000)
 * CL1 VA DRAM		[0x5_0000_0000, 0x9_0000_0000)
 * CL2 VA DRAM		[0x9_0000_0000, 0xd_0000_0000)
 * CL3 VA DRAM		[0xd_0000_0000, 0x11_0000_0000)
 * Start address and size of USER DRAM should be received as input.
 */
void page_table_init(uint64_t dram_va_start, uint64_t dram_size, int cl_affin, bool shm_intlv)
{
	uint64_t cl_id;

	while (cl_affin) {
		cl_id = __builtin_ffsl(cl_affin) - 1;
		page_table_generate_spm(cl_id);
		page_table_generate_shm(cl_id, shm_intlv);
		page_table_generate_dram(cl_id, dram_va_start, dram_size);

		RL_CLR_BIT(cl_affin, cl_id);
		RLOG_INFO("%s: page table generated for cl%d va%#llx sz%#llx\r\n", __func__, cl_id,
				  dram_va_start, dram_size);

		dram_va_start += dram_size;
	}
}

void page_table_init_mp(struct st_alloc_info *info, int n)
{
	RLOG_ERR("%s only supported from MMU_V2\r\n", __func__);
	rl_abort_event(ERR_INVALID_CTX);
}

#endif
