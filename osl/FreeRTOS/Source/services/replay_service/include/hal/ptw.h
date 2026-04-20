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

#ifndef _PTW_H_
#define _PTW_H_

#include <stdbool.h>
#include "common/exec_id.h"
#include "hal/addr_map.h"
#include "hal/hw_spec.h"
#include "rebel_h_platform.h"
#include "rl_utils.h"
#include "rbln_memory.h"

/* Map macros from rl_utils.h to match reference code naming */
#ifndef BIT64_MASK
#define BIT64_MASK(n) (BIT64(n) - 1ULL)
#endif
#ifndef GENMASK64
#define GENMASK64(h, l) RL_GENMASK64(h, l)
#endif
#ifndef BIT
#define BIT(n) RL_BIT(n)
#endif
#ifndef BIT_WIDTH_128B
#define BIT_WIDTH_128B 7
#endif

#define CHIPLET_INTERVAL					(0x2000000000ULL)
#define PAGE_PRESENT_MASK					0x0000000000001ull

#define VA_DEV_ID_SHIFT						44
#define VA_DEV_ID_BIT_WIDTH					4
#define BIT_WIDTH_PA_MAX					(VA_DEV_ID_SHIFT + VA_DEV_ID_BIT_WIDTH)
#define BIT_WIDTH_PAGE						21	/* PAGE = 2MB: 2^21*/
#define BIT_WIDTH_L0						39	/* 21 + 9 + 9 */

#define MMU2_TASK_SHIFT						40
#define BIT_MASK_PAGE						BIT64_MASK(BIT_WIDTH_PAGE)
#define BIT_WIDTH_TLB_PAGE_SIZE				(BIT_WIDTH_PAGE - BIT_WIDTH_128B)
#define BIT_POS_PTE_PAGE_MAPPING_TYPE		18

#define VF_SYSTEM_HIDDEN_OFFSET				0x10000000
#define PF_SYSTEM_IPA_BASE					0x40000000

enum ptw_page_type {
	PTW_MAPPING_TYPE_SHARED = 0,
	PTW_MAPPING_TYPE_SHARED_CONTINUOUS,
	PTW_MAPPING_TYPE_PRIVATE,
	PTW_MAPPING_TYPE_INTERMEDIATE
};

union ptw_pn {
	struct __attribute__((packed, aligned(4))) {
		uint32_t ppn : 19;
		uint32_t mapping_type : 2;
		uint32_t reserved : 11;
	};
	uint32_t bits;
};

uint64_t *ptw_get_pte(uint64_t *base, int lvl, uint64_t va);
uint64_t ptw_va_to_ipa(uint64_t va, uint64_t *ttb, const union proc_exec_id *id_info);
uint64_t ptw_virt_to_phys(uint64_t va, uint64_t *ttb, const union proc_exec_id *id_info);
union ptw_pn ptw_vpn_to_ppn(uint32_t vpn, uint64_t *ttb, const union proc_exec_id *id_info);
uint64_t ptw_ipa_to_pa(uint64_t ipa, int fid);
uint32_t ptw_flush_page_tables(uint64_t l0addr, bool flush);
int ptw_register_s2t_handler(int num_vfs);
void ptw_init_smmu_s2(uint32_t num_vfs);

#define IPA_TO_PA(ipa, fid)			(ptw_ipa_to_pa(ipa, fid))
//#define CPVA_TO_PA(cl, va)		(((va) & (FREERTOS_VA_OFFSET - 1)) + (cl) * CHIPLET_INTERVAL)
//#define PA_TO_CPVA(pa)			(((pa) & (CHIPLET_INTERVAL - 1)) | FREERTOS_VA_OFFSET)

#define NODEID_VPN(node_id, vpn)	(((node_id) << (VA_DEV_ID_SHIFT - BIT_WIDTH_PAGE)) | (vpn))
#define NODEID_VA(node_id, va)		((((uint64_t)(node_id)) << VA_DEV_ID_SHIFT) | ((uint64_t)(va)))

#define L0_ENTRY_SZ_PER_NODE	(BIT(VA_DEV_ID_SHIFT - BIT_WIDTH_L0) * sizeof(uint64_t))

#define PTW_VIRT_TO_PHYS(va, ttb, id_info)				\
({								\
	uint64_t pa;						\
	uint64_t temp_va = va;					\
	int node_id = 0;					\
								\
	temp_va = NODEID_VA(node_id, temp_va);			\
	pa = ptw_virt_to_phys(temp_va, (uint64_t *)ttb, id_info); \
	pa;							\
})

#define PTW_VPN_TO_PPN(vpn, ttb, id_info)			\
({								\
	union ptw_pn ppn;					\
	uint64_t temp_vpn = vpn;				\
	int node_id = 0;					\
								\
	temp_vpn = NODEID_VPN(node_id, temp_vpn);		\
	ppn = ptw_vpn_to_ppn(temp_vpn, ttb, id_info);		\
	ppn;							\
})

#endif /* _PTW_H_ */
