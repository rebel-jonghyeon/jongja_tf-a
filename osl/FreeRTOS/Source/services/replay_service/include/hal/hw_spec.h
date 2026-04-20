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

#ifndef _CP_HW_SPEC_H_
#define _CP_HW_SPEC_H_

#include <stdint.h>

#ifndef MAX_CHIPLET_COUNT
#define MAX_CHIPLET_COUNT   (4)
#endif
extern const uint64_t cl_base[];      /* per-chiplet base address */
extern uint32_t cur_cl_id;      /* current chiplet id global var */

#define BIT_WIDTH_DWORD							32	/* DATA WORD = 32-bit (4B) */
#define DWORD_IN_BYTE							(BIT_WIDTH_DWORD/8)	/* DATA WORD = 32-bit (4B) */

#define CPU_WRITE_BURST_LENGTH_MAX              8   /* 4Bytes x 8BL @ A53 */
#define BIT_WIDTH_CPU_WRITE_BURST_LENGTH_MAX    3   /* 3bit */

/*
 * System spec for ATOM project
 * up to 8 contexts are processed in a way of time-sliced
 */
#define SYS_SPEC_CONTEXT_NUM					256

/* HW spec for ATOM project */
#ifdef DCL_SINGLE
#define HW_SPEC_DNC_COUNT						8		/* REBEL: 8 x DNCs */
#define HW_SPEC_SHM_COUNT						16
#define HW_SPEC_DC_COUNT						1		/* DCLUSTER count */
#else
#define HW_SPEC_DNC_COUNT						16		/* REBEL: 16 x DNCs */
#define HW_SPEC_HALF_DNC_COUNT					(HW_SPEC_DNC_COUNT >> 1)
#define HW_SPEC_SHM_COUNT						32
#define HW_SPEC_DC_COUNT						2		/* DCLUSTER count */
#endif
#define HW_SPEC_DDMA_COUNT						1		/* ATOM: 1 x dDMA */
#define HW_SPEC_HDMA_COUNT						1		/* ATOM: 1 x hDMA */
#define HW_SPEC_GDDR_COUNT						4
#define HW_SPEC_BUS_COUNT						3
#define HW_SPEC_CP_MAX_CONTEXT_ID_NUM			8       /* up to 8 context id */

#define HW_SPEC_BIT_WIDTH_VA					37      /* 37bits for 127GB-virtual space */
#define HW_SPEC_BIT_WIDTH_PA					40      /* 40bits for 1TB-physical space */
#define HW_SPEC_BIT_WIDTH_DATA_SPR				32      /* 32-bit DATA WORD for SPR */

#define HW_SPEC_CFG_REG_SIZE					65536   /* 64KB: 64 x 1024 */
#define HW_SPEC_CFG_REG_NUM						(HW_SPEC_CFG_REG_SIZE/4) /* 16K Regs = 64KB/4B */
#define HW_SPEC_CFG_CTX_INFO_SIZE				32		/* Context: 32 DWs + Process: 32 DWs */
#define HW_SPEC_CFG_PROC_INFO_SIZE				32		/* Context: 32 DWs + Process: 32 DWs */
#define HW_SPEC_CFG_CTX_INFO_SIZE_TOTAL			64		/* Context: 32 DWs + Process: 32 DWs */

/* TSYNC */
#define HW_SPEC_TSYNC_GROUP_COUNT				64

/* SR-IOV*/
#define HW_SPEC_DRAM_SIZE_PER_VF                (0x400000000 >> 4) /* 1GB; 16GB/# of VF */

/* HDR1 */
#define BIT_WIDTH_PACKET_HDR_OPCODE				5	/* to support 32 different opcodes */
#define NUM_TRANSACTIONS_PACKET_HDR				2	/* to support 4B-BL32 long transaction */
#define NUM_TRANSACTIONS_PACKET					32	/* to support 4B-BL32 long transaction */

/* DNC / SP */
#define HW_SPEC_DNC_IRQ_NUM 6

#define HW_SPEC_DNC_SP_ADDRESS_RANGE            (1 << 22)  /* 4MB per DNC */

#define HW_SPEC_DNC_SUPPORTED_CREDIT_COMP		74
#define HW_SPEC_DNC_SUPPORTED_CREDIT_LDUDMA		74
#define HW_SPEC_DNC_SUPPORTED_CREDIT_LPUDMA		74
#define HW_SPEC_DNC_SUPPORTED_CREDIT_STUDMA		74
#define HW_SPEC_DNC_SUPPORTED_CREDIT			74

#define HW_SPEC_DNC_TM_TASK_PASSAGE_SIZE        0x8     /* 256bits = 32bit x 8BL */

#define HW_SPEC_DNC_TLB_QUEUE_ENTRIES_MAX_NC            32
#define HW_SPEC_DNC_TLB_QUEUE_ENTRIES_MAX_UDMA          8
#define HW_SPEC_DNC_TLB_QUEUE_ENTRIES_MAX_JCR_TABLE     16

/* dDMA */
#define HW_SPEC_DDMA_TASK_EXECUTOR_NUM  8
#define HW_SPEC_RBDMA_HALF_EXECUTOR_NUM 4
#define HW_SPEC_DDMA_IRQ_NUM            2

/* Staging buffer to receive Passage from CP */
#define HW_SPEC_RBDMA_TURQ_QUEUE_ENTRY_NUM		128
#define HW_SPEC_RBDMA_MAX_BLK_SIZE_128B			(126 << 13)	/* 126MB, unit:128B */

/* System Manager */
#define DWORD_SIZE                              4       /* 4Bytes */
#define HW_SPEC_CP_EXT_IRQ_QUEUE_SIZE           4       /* 4Bytes */
#define HW_SPEC_CP_INT_IRQ_QUEUE_SIZE           4       /* 4Bytes */

#define HW_SPEC_CP_INT_IRQ_SOURCE_NUM			32
#define HW_SPEC_CP_EXT_IRQ_SOURCE_NUM			SYS_SPEC_CONTEXT_NUM

#define HW_SPEC_BD_SIZE_IN_WORD					8		/* 256bit = 32bit x 8WORDs */
#define HW_SPEC_BD_NUM_PER_CONTEXT				1024	/* MAX: 1K */

#define HW_SPEC_CMD_QUEUE_CLUSTER_NUM			9	/* 8DNC + dDMA */
#define HW_SPEC_CMD_QUEUE_NUM_IN_DNC			4	/* Compute, uDMA, uDMA_LowP, uDMA_ST */
#define HW_SPEC_CMD_QUEUE_NUM_IN_DDMA			2	/* dDMA, dDMA_HighP */


#define HW_SPEC_CMD_DESCR_DWORD_NUM				16		/* 512-bit = 32-bit x 16 DWs */

#define HW_SPEC_DEP_MASK_BIT_WIDTH				64		/* 64 dependency slots */
#define HW_SPEC_DEP_MASK_REFCNT_BIT_WIDTH		5		/* 32 references per a slot */

#define HW_SPEC_DNC_QUEUE_NUM					4
#define HW_SPEC_DDMA_QUEUE_NUM					2
#ifdef AUTO_FETCH_ENABLED
#define HW_SPEC_DDMA_AF_QUEUE_NUM				1	/* dDMA_HighP is not supported in auto-fetch */
#endif

/* Task Manager: DNC_TM spec. v1.6
 *  - DNC_TM supports up to 32 + 2 task entries, but will be used 32 for a fast-binary search
 */
#define HW_SPEC_TASK_QUEUE_ENTRIES_DNC			32     /* 32 + 2 entries in total */
#define HW_SPEC_TASK_QUEUE_ENTRIES_COMPUTE		32
#define HW_SPEC_TASK_QUEUE_ENTRIES_UDMA			32
#define HW_SPEC_TASK_QUEUE_ENTRIES_UDMA_LOWP	32
#define HW_SPEC_TASK_QUEUE_ENTRIES_UDMA_ST		32
#define HW_SPEC_TASK_QUEUE_ENTRIES_RBDMA		64
#define HW_SPEC_TASK_QUEUE_ENTRIES_RBDMA_HIGHP	8

#define HW_SPEC_TASK_QUEUE_ENTRIES_MAX			HW_SPEC_TASK_QUEUE_ENTRIES_RBDMA

#define HW_SPEC_TLB_ENTRY_NUM_PER_COMMAND		HW_SPEC_DNC_TM_URQ_ENTRIES
#define HW_SPEC_TLB_ENTRY_PER_PROCESS_NUM		HW_SPEC_TLB_ENTRY_NUM_PER_COMMAND

#define HW_SPEC_TLB_SET_NUM_DNC					HW_SPEC_TASK_QUEUE_ENTRIES_DNC
#define HW_SPEC_TLB_SET_NUM_DDMA				HW_SPEC_TASK_QUEUE_ENTRIES_DDMA
#define HW_SPEC_TLB_SET_NUM_DDMA_HIGHP			HW_SPEC_TASK_QUEUE_ENTRIES_DDMA_HIGHP
#define HW_SPEC_COMPUTE_CMD_TLB_SOURCE_NUM		4		/* Init, input, kernel, output */
#define HW_SPEC_COMPUTE_CMD_DATA_SIZE_UNIT		128		/* 128B */
#define HW_SPEC_DMA_CMD_TLB_SOURCE_NUM			2		/* source, destination */

#define	HW_SPEC_BIT_WIDTH_TLB_DATA				(BIT_WIDTH_PA - BIT_WIDTH_PAGE)

#define HW_SPEC_DNC_COMPUTE_TASK_ETNRY_NUM
#define HW_SPEC_DNC_UDMA_TASK_ETNRY_NUM
#define HW_SPEC_DNC_UDMA_LOWP_TASK_ETNRY_NUM

/* DNC x (comp+uDMA)/DNC + dDMA + hDMA:
 * priority queue will not be the major workloads
 */
#define HW_SPEC_CP_PROC_MANAGER_IRQ_SYNC_QUEUE  HW_SPEC_CP_INT_IRQ_SOURCE_NUM

#define BIT_WIDTH_ID_INFO_FUNC_ID       4
#define BIT_WIDTH_ID_INFO_CTX_ID        8
#define BIT_WIDTH_ID_INFO_PROC_ID       4
#define BIT_WIDTH_ID_INFO_CMD_ID        16

// for sorting debug
#define HBM_LOG_START_ADDR ((cur_cl_id * 0x2000000000ULL) + 0x1FF7404930ULL)	//hbm error csr
#define NUM_OF_HBM_CH		(16)
#define HBM_CH_OFFSET		(0x40000ULL)
#define CSR_SIZE			(0x20ULL)

#define HBM_CSR_READ(addr)		rl_readl_relaxed((void *)(addr))

/*
 * XGPIOB_00 GROUP2, bit 0
 * GPIO_NBUS_L 0x1F_F353_0000 + 0x40
 * 0x1F_F353_0000 + 44
 */
#if defined(INDICATOR_DEBUG_MODE)
#define GPIO_TEST_BASE   ((cur_cl_id * 0x2000000000ULL) + 0x1FF3530000UL)

#define INDICATOR_REG32(addr)   (*(volatile uint32_t *)(uintptr_t)(addr))

#define TEST_GPD2_CON  INDICATOR_REG32(GPIO_TEST_BASE + 0x40)
#define TEST_GPD2_DAT  INDICATOR_REG32(GPIO_TEST_BASE + 0x44)
#endif /* #if defined(INDICATOR_DEBUG_MODE) */

#endif /* _CP_HW_SPEC_H_ */
