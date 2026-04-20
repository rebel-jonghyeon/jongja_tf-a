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


#ifndef _ATOM_H
#define _ATOM_H

//#include "rbln/utils.h"
#include "rl_utils.h"
#include "g_sysfw_addrmap.h"
#include "g_sys_addrmap.h"

/*
 * ATOM physical memory map
 *
 * 0x0 ~ 0x3F_FFFF_FFFF (16GB)	: DRAM
 *   - 0x0010_0000 ~ 0x0FFF_FFFF (255MB): FW image
 *   - 0x1000_0000 ~ 0x121F_FFFF (34MB)	: MMU page tables
 *   - 0x1220_0000 ~ 0x123F_FFFF (2MB)	: CTX_CFG
 *   - 0x1240_0000 ~ 0x3F_FFFF_FFFF	: DRAM user base
 *
 * 0x1F_E000_0000 ~ 0x1F_E1FF_FFFF (32MB) : SP_MEM_BASE (Scratch Pad)
 *
 * 0x1F_E400_0000 ~ 0x1F_E5FF_FFFF (32MB) : SH_MEM_BASE (Shared Memory)
 *
 * 0x1F_F400_0000 ~ 0x1F_F7FF_FFFF (64MB) : ATOM_CFG_PHYSICAL_START
 *   - 0x1F_F441_1000 : PF_DOORBELL_BASE
 *   - 0x1F_F442_0000 : VF_DOORBELL_BASE
 *
 * 0x80_0000_0000 (512GB) : HOST_PHY_BASE
 */

#define DRAM_PHYS_BASE		DEVICE_DRAM_PHYSICAL_START
#define RL_DRAM_SIZE		0x2400000000ull		/* 144GB */
#define DRAM_VA_START_ADDR	0x100000000

/* SRAM */
#define RL_SPM_VA_BASE_ADDR	0
#define RL_SPM_SIZE			0x0004000000ull		/* 64MB */

#define RL_SHM_VA_BASE_ADDR	0x0004000000ull
#define RL_SHM_SIZE			0x0004000000ull		/* 64MB */

#define VA_DDR_SPACE_START	0x800000000ull		/* 32GB */
#define VA_DDR_SPACE_END	0x2000000000ull		/* 128GB */
#define VA_DDR_SPACE_SIZE	(VA_DDR_SPACE_END - VA_DDR_SPACE_START)

#define ATOM_MSIX_ENTRIES	32u

#define MAX_ASID			255
#define MAX_HTID			4
#define MAX_VF_CNT			16
#define MAX_FUNC_CNT		(MAX_VF_CNT + 1)
#define MAX_PROC_CNT		8

#define CPU_FW_IMAGE_SIZE			0xFF00000u		/* 255MB */
#define CPU_SP_DUMP					0xB600000u		/* 182MB - 214MB */
#define CPU_SHM_DUMP				0xD600000u		/* 214MB - 246MB */
#define	IMAGE_LOAD_REGION			0xF600000u		/* 246MB - 248MB */
#define CPU_DUMMY_PRIM_OFFSET		0xF700000u		/* 247MB - 248MB */
#define MMU_PAGE_TABLES_SIZE		0x01e00000u		/* 30MB */
#define MMU_DRAM_DEFAULT_PAGE_SIZE	0x00200000u		/* 2MB */
#define CTX_CFG_SIZE				0x00200000u		/* 2MB */

/*
 * PCIe BAR configuration
 *
 * BAR01
 *	DRAM: 0x0 ~ 0x3_ffff_ffff(16GB)
 *
 * BAR23
 *	SHM : 0x1f_e400_0000 ~ 0x1f_e5ff_ffff(32MB)
 *
 * BAR4
 *	CFG : 0x1f_f400_0000 ~ 0x1f_f47f_ffff (8MB)
 *	      0x1f_f400_0000 : ATOM_CFG_PHYSICAL_START
 *	      0x1f_f440_0000 : PCIE_SUBSYS_CFG_BASE
 *	      0x1f_f441_0000 : PCIE_PFCSR_0_CFG_BASE
 *	      0x1f_f441_1000 : PCIE_PF_DOORBELL_BASE
 *	      0x1f_f442_0000 : PCIE_VFCSR_0_CFG_BASE(PCIE_VF_DOORBELL_BASE)
 *
 * BAR5
 *	Port logic : 0x0_0700 ~ 0x0_0fff
 *	MIS-X Table : 0x0_2000 ~ 0x0_21ff
 *	MSI-X PBA : 0x0_3000 ~ 0x0_3007
 *	iATU : 0x4_0000 ~ 0x4_ffff
 *	HDMA : 0x8_0000 ~ 0x9_ffff
 */

/*
 * PCIe Queues - Command Queue(QM), Event Queue(EQ), and Message Queue(MQ)
 */
#define FW_SHA						0x00E0
#define FW_MAJOR					0x00E4
#define FW_MINOR					0x00E8
#define FW_PATCH					0x00EC

#define UUID1						0x00F0
#define UUID2						0x00F4
#define UUID3						0x00F8
#define UUID4						0x00FC

#define QM_GLBL_CFG					0x0100
#define QM_GLBL_CFG_CQ_VALIDITY		RL_BIT(0)
#define QM_GLBL_CFG_EQ_VALIDITY		RL_BIT(1)
#define QM_GLBL_CFG_MQ_VALIDITY		RL_BIT(2)
#define QM_GLBL_CFG_INITIALIZED		RL_BIT(31)

#define QM_CQ_BASE_LO				0x0104
#define QM_CQ_BASE_HI				0x0108
#define QM_CQ_SIZE					0x010C
#define QM_CQ_PI					0x0110
#define QM_CQ_CI					0x0114
#define QM_CQ_SCRATCH				0x0118

#define QM_EQ_BASE_LO				0x0124
#define QM_EQ_BASE_HI				0x0128
#define QM_EQ_SIZE					0x012C
#define QM_EQ_PI					0x0130
#define QM_EQ_CI					0x0134

#define PF_INFO						0x0140

#define QM_MQ_BASE_LO				0x0144
#define QM_MQ_BASE_HI				0x0148
#define QM_MQ_SIZE					0x014C
#define QM_MQ_PI					0x0150
#define QM_MQ_CI					0x0154

#define VF_HOST_BASE				0x0158
#define VF_DRAM_BASE				0x015C
#define VF_INFO						0x0160
#define VF_NUM_BITMASK				RL_GENMASK(31, 24)
#define VF_SIZE_BITMASK				RL_GENMASK(23, 0)
#define VF_INFO_SET(d, s)			((((d) << 24) & RL_GENMASK(31, 24)) |	\
									((s) & RL_GENMASK(23, 0)))

#define GUILTY_CONTEXT_FLAG			RL_BIT(31)
#define GUILTY_CONTEXT_GET_FUNC(v)	(((v) & RL_GENMASK(30, 16)) >> 16)
#define GUILTY_CONTEXT_SET(g, f, a)	(((g) << 31) | (((f) << 16) & RL_GENMASK(30, 16)) |	\
									((a) & RL_GENMASK(15, 0)))

#define ERR_NO_MEM					RL_BIT(0)
#define ERR_QUEUE_FULL				RL_BIT(1)
#define ERR_RDSN					RL_BIT(2)	//ERR_FORCE
#define ERR_HIGH_TEMP				RL_BIT(3)
#define ERR_PCIE_LINK				RL_BIT(4)
#define ERR_CORE_EXCEPTION			RL_BIT(5)
#define ERR_TLB_PRELOAD				RL_BIT(6)
#define ERR_DNC						RL_BIT(7)
#define ERR_RBDMA					RL_BIT(8)
#define ERR_HDMA					RL_BIT(9)
#define ERR_UNKNOWN					RL_BIT(10)
#define ERR_EMPTY_CB				RL_BIT(11)
#define ERR_INVALID_HDMA_PKT		RL_BIT(12)
#define ERR_NOT_SUPPORTED_PKT		RL_BIT(13)
#define ERR_HOST_ABORT_EVENT		RL_BIT(14)
#define ERR_NOT_SUPPORTED_PKT_POST	RL_BIT(15)
#define ERR_INVALID_PKT				RL_BIT(16)
#define ERR_PAGE_FAULT				RL_BIT(17)
#define ERR_NOT_SUPPORTED_CMD		RL_BIT(18)
#define ERR_FAILED_TLB_GEN			RL_BIT(19)
#define ERR_SHM						RL_BIT(20)
#define ERR_INVALID_TASK			RL_BIT(21)
#define ERR_CPU_NOTREADY			RL_BIT(22)
#define ERR_QUEUE_INIT				RL_BIT(23)
#define ERR_WATCHDOG				RL_BIT(24)
#define ERR_GDDR6					RL_BIT(25)
#define ERR_TASK					RL_BIT(26)
#define ERR_INVALID_CTX				RL_BIT(27)
#define ERR_INVALID_CP_CFG			RL_BIT(28)
#define ERR_INVALID_CMD				RL_BIT(29)
#define ERR_RESET_NOTIFICATION		RL_BIT(30)
#define ERR_TDR_OFF					RL_BIT(31)

/* CRC error per channel */
#define GDDR6_READ_CRC_ERR_CNT				0x174		// 16B
#define GDDR6_WRITE_CRC_ERR_CNT				0x184		// 16B

/* PCIe information, provided by host driver in queue init*/
#define HOST_PCIE_SPEED_WIDTH_CAP			0x194

#define VSERIAL_FIFO_SIZE	0x10000     // 16 KB
#define VSERIAL_D2H_PI		0x2FF0      // Device to Host Producer Index
#define VSERIAL_D2H_CI		0x2FF4      // Device to Host Consumer Index
#define VSERIAL_H2D_PI		0x2FF8      // Host to Device Producer Index
#define VSERIAL_H2D_CI		0x2FFC      // Host to Device Consumer Index
#define VSERIAL_H2D_FIFO	0x3000
#define VSERIAL_D2H_FIFO	(VSERIAL_H2D_FIFO + VSERIAL_FIFO_SIZE)

/* SRAM dump region */
#define BL_LOGBUF_START				0x1FF415E000
#define BL_LOGBUF_SIZE				0x1000
#define BL_LOGBUF_MAGIC				0xCAFEF00D
#define BL33_DUMP_START				0x1FF415F000

/* FWLOAD REG INFO
 *
 * ATOM_MAIN_SYSTEM_CONF_BASE + 0x010 (16bit : 0x1 ~ 0x3)
 * 0x1 ~ 0x2 : H2D 8b
 * 0x2 ~ 0x3 : D2H 8b
 */
#define ATOM_MAIN_SYSTEM_CONF_BASE  0x1ff4601000ull
#define REG_FWLOAD_OFFSET           (ATOM_MAIN_SYSTEM_CONF_BASE + 0x010ull)
#define FW_LOAD_MASK				0x0000ffff
#define FW_BOOT_DONE                0xFB0D	/* D2H */

/* PCIe doorbell */
#define PCIE_PF_DOORBELL_BASE_ADDR_EVT0	METAL_SYNOPSYS_PCIE_DOORBELL_PF_BASE_ADDRESS
#define PCIE_VF_DOORBELL_BASE_ADDR_EVT0	METAL_SYNOPSYS_PCIE_DOORBELL_VF_BASE_ADDRESS

#define PCIE_PF_DOORBELL_BASE_ADDR_EVT1	METAL_SYNOPSYS_PCIE_PFMSG_BASE_ADDRESS
#define PCIE_VF_DOORBELL_BASE_ADDR_EVT1	METAL_SYNOPSYS_PCIE_VFMSG_BASE_ADDRESS

#define PCIE_DOORBELL_SIZE			0x1000u

#define PCIE_MAILBOX_0				0x420
#define PCIE_MAILBOX_1				0x424
#define PCIE_MAILBOX_2				0x428
#define PCIE_MAILBOX_3				0x42C
#define PCIE_MAILBOX_4				0x430
#define PCIE_MAILBOX_5				0x434
#define PCIE_MAILBOX_6				0x438
#define PCIE_MAILBOX_7				0x43C
#define PCIE_MAILBOX_SIZE			0x1000u

/* PCIe mailbox */
#define PCIE_PF_MAILBOX_BASE_ADDR(addr)	((addr) + PCIE_MAILBOX_0)
#define PCIE_VF_MAILBOX_BASE_ADDR(addr)	((addr) + PCIE_MAILBOX_0)

#define PCI_ATU_SEPARATE_OFFSET 0x100000000ull

/* MSIx vector number for event handling between driver and firmware */
#define ATOM_EVENT_IRQ_NUMBER   0x8

/* MSIx vector number for virtual serial Device-to-Host TX */
#define VSERIAL_IRQ_NUMBER		0x7

#endif /* _ATOM_H */
