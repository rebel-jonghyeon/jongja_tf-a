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

#ifndef _CP_ADDR_MAP_H_
#define _CP_ADDR_MAP_H_

#include "hal/hw_spec.h"
#include "rbln/rebel.h"

/* TO DO: System Address will be assigned */

/* CP_FW address map */
/* ----------------- Reserved Region ----------------- */
#define BASE_ADDR_MDA_SYNC_BARRIER				0xB3EC000
#define SZ_MDA_SYNC_BARRIER						0x4000

/* ----------------- System spec. ----------------- */
#define BASE_ADDR_VA_DRAM_LOCAL					0x0100000000
#define BASE_ADDR_VA_SP_LOCAL					0x0000000000
#define BASE_ADDR_VA_SHM						0x0002000000

#define	CFG_REG_SIZE_DNC						0x2000			/* 0x0100 */

/* ----------------- DNC / TM ----------------- */
#define BIT_WIDTH_128B							7

#define	ADDR_OFFSET_SPR_IRQ_STATUS				0x0
#define	ADDR_OFFSET_SPR_PKT_HDR0				0x4
#define	ADDR_OFFSET_SPR_PKT_HDR1				0x8
#define	ADDR_OFFSET_SPR_PKT_PLD					0xc

#define CTRL_ENDPOINT_ID_DNC0					0x0
#define CTRL_ENDPOINT_ID_DNC1					0x1
#define CTRL_ENDPOINT_ID_DNC2					0x2
#define CTRL_ENDPOINT_ID_DNC3					0x3
#define CTRL_ENDPOINT_ID_DNC4					0x4
#define CTRL_ENDPOINT_ID_DNC5					0x5
#define CTRL_ENDPOINT_ID_DNC6					0x6
#define CTRL_ENDPOINT_ID_DNC7					0x7

#define CTRL_ENDPOINT_ID_DDMA					0x8
#define CTRL_ENDPOINT_ID_HDMA					0x9

/* System Manager */
#define ADDR_OFFSET_SYSTEM_MANAGER				0x0000

/* Clock control */
#define ADDR_OFFSET_SM_POWER_ON					0x0000
#define ADDR_OFFSET_SM_ARCH_CLOCK_GATING		0x0004
#define ADDR_OFFSET_SM_CLOCK_OVERRIDE			0x0008

/* Reset */
#define ADDR_OFFSET_SM_RESET_SW					0x000c

/* IRQs */
#define ADDR_OFFSET_SM_INT_IRQ_SOURCE			0x0010

#define ADDR_OFFSET_SM_INT_IRQ_STATUS_CP		0x0014
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_DNC0		0x0018
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_DNC1		0x001c
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_DNC2		0x0020
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_DNC3		0x0024
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_DNC4		0x0028
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_DNC5		0x002c
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_DNC6		0x0030
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_DNC7		0x0034
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_DDMA		0x0038
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_HDMA		0x003c
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_SHM0		0x0040
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_SHM1		0x0044
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_SHM2		0x0048
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_SHM3		0x004c
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_MC0		0x0050
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_MC1		0x0050
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_CMU		0x0054
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_RMU		0x0058
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_CBUS0		0x005c
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_CBUS1		0x0060
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_DBUS0		0x0064
#define ADDR_OFFSET_SM_INT_IRQ_STATUS_PCIE		0x0068

/* IRQ IDs */
#define INT_IRQ_ID_CP							0x00
#define INT_IRQ_ID_DNC0							0x01
#define INT_IRQ_ID_DNC1							0x02
#define INT_IRQ_ID_DNC2							0x03
#define INT_IRQ_ID_DNC3							0x04
#define INT_IRQ_ID_DNC4							0x05
#define INT_IRQ_ID_DNC5							0x06
#define INT_IRQ_ID_DNC6							0x07
#define INT_IRQ_ID_DNC7							0x08
#define INT_IRQ_ID_DDMA							0x09
#define INT_IRQ_ID_HDMA							0x0a
#define INT_IRQ_ID_SHM0							0x0b
#define INT_IRQ_ID_SHM1							0x0c
#define INT_IRQ_ID_SHM2							0x0d
#define INT_IRQ_ID_SHM3							0x0e
#define INT_IRQ_ID_MC0							0x0f
#define INT_IRQ_ID_MC1							0x10
#define INT_IRQ_ID_CMU							0x11
#define INT_IRQ_ID_RMU							0x12
#define INT_IRQ_ID_CBUS0						0x13
#define INT_IRQ_ID_CBUS1						0x14
#define INT_IRQ_ID_DBUS0						0x15
#define INT_IRQ_ID_PCIE							0x16
#define INT_IRQ_ID_NUM							(INT_IRQ_ID_PCIE + 0x1)

/* Context Manager */
#define ADDR_OFFSET_CONTEXT_MANAGER				0x0200
#define ADDR_OFFSET_CONTEXT						0x0300
#define ADDR_OFFSET_CONTEXT0					ADDR_OFFSET_CONTEXT
#define CFG_REG_SIZE_CONTEXT					0x0500	/* in Bytes */

#define ADDR_OFFSET_PROCESS						0x0080
#define ADDR_OFFSET_PROCESS0					ADDR_OFFSET_PROCESS
#define CFG_REG_SIZE_PROCESS					0x0080	/* 32 DWORDs */
#define ADDR_OFFSET_LOGBUF_INFO					0x1000
#define ADDR_OFFSET_LOGBUF_MAGIC				ADDR_OFFSET_LOGBUF_INFO
#define ADDR_OFFSET_LOGBUF_BASE_ADDR			0x1004
#define ADDR_OFFSET_LOGBUF_ITEM_CNT				0x1008
#define ADDR_OFFSET_LOGBUF_ITEM_SIZE			0x100C
#define ADDR_OFFSET_LOGBUF_WI					0x1010
#define ADDR_OFFSET_LOGBUF_RI					0x1014

#define ADDR_OFFSET_CTX_IRQ_STATUS				0x00
#define ADDR_OFFSET_CTX_STATE					0x04
#define ADDR_OFFSET_CTX_ADDR_TRANS_MODE			0x08
#define ADDR_OFFSET_CTX_PT_ADDR_L			    0x0c
#define ADDR_OFFSET_CTX_PT_ADDR_H			    0x10
#define ADDR_OFFSET_CTX_DNC_MODE				0x14
#define ADDR_OFFSET_CTX_IO_BUF_CNT				0x18
#define ADDR_OFFSET_CTX_CMD_DESCR_ADDR_L		0x1c
#define ADDR_OFFSET_CTX_CMD_DESCR_ADDR_H		0x20
#define ADDR_OFFSET_CTX_STORAGE_ADDR_L		    0x24
#define ADDR_OFFSET_CTX_STORAGE_ADDR_H		    0x28
#define ADDR_OFFSET_CTX_RUN						0x2c
#define ADDR_OFFSET_CTX_STOP					0x30

#define ADDR_OFFSET_CTX_PAGETABLE_SIZE			0x54
#define ADDR_OFFSET_CTX_USER_FLAG				0x60

#define ADDR_CTX_RUN	\
	(ADDR_OFFSET_CONTEXT + ADDR_OFFSET_CTX_RUN)

#define ADDR_OFFSET_PROC_IRQ_STATUS			    0x00
#define ADDR_OFFSET_PROC_INFO					0x04
#define ADDR_OFFSET_PROC_STATE				    0x08
#define ADDR_OFFSET_PROC_ADDR_TRANS_MODE		0x0c
#define ADDR_OFFSET_PROC_PT_ADDR_L			    0x10
#define ADDR_OFFSET_PROC_PT_ADDR_H			    0x14
#define ADDR_OFFSET_PROC_CMD_DESCR_ADDR_L		0x18
#define ADDR_OFFSET_PROC_CMD_DESCR_ADDR_H		0x1c
#define ADDR_OFFSET_PROC_STORAGE_ADDR_L		    0x20
#define ADDR_OFFSET_PROC_STORAGE_ADDR_H		    0x24
#define ADDR_OFFSET_PROC_PERF_MONITOR_ENABLE	0x28
#define ADDR_OFFSET_PROC_PERF_DUMP_ADDR_L	    0x2c
#define ADDR_OFFSET_PROC_PERF_DUMP_ADDR_H	    0x30
#define ADDR_OFFSET_PROC_SYS_MONITOR_ENABLE		0x34
#define ADDR_OFFSET_PROC_SYS_DUMP_ADDR_L	    0x38
#define ADDR_OFFSET_PROC_SYS_DUMP_ADDR_H	    0x3c
#define ADDR_OFFSET_PROC_RUN					0x40
#define ADDR_OFFSET_PROC_STOP					0x44

#define ADDR_PROC_RUN	\
	(ADDR_OFFSET_CONTEXT + ADDR_OFFSET_PROCESS + ADDR_OFFSET_PROC_RUN)

#define BIT_INDEX_PROC_INFO_EXEC_MODE			27
#define BIT_INDEX_PROC_INFO_DEBUG_MODE			28

#define BIT_INDEX_CTX_USER_FLAG_TM_MODE			31
#endif /* _CP_ADDR_MAP_H_ */
