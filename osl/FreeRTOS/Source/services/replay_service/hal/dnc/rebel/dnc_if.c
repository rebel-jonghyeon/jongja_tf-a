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

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "system_api.h"	//udelay
#include "rbln/cache.h"
#include "common/profile.h"
#include "common/af_profile.h"
#include "common/debug.h"
#include "common_test.h"
#include "hal/dnc_if.h"
#if EVT_VER == 1
#include "hal/dnc/dnc_if_evt1.h"
#else
#include "hal/dnc/dnc_if_evt0.h"
#endif
#include "rl_errors.h"
#include "rbln/abort.h"
#include "rl_utils.h"
#include "rbln/arm64/io_burst.h"
#include "rbln/log.h"

#include "hal/addr_map.h"
#include "rl_sizes.h"
#include "hal/interrupt.h"

#include "hal/rdsn_if.h"
#if EVT_VER == 1
#include "evt1/dnc_regs.h"
#else
#include "dnc_regs.h"
#endif

#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX g_
#include "external/incbin/incbin.h"
#include "sys_command_line.h"
#include "common/page_table_gen.h"
#include "common/debug.h"
#include "rbln/core.h"
#include "common/autofetch.h"

INCBIN(hc_bin_init, "./hc_data/init.bin");
INCBIN(cs_bin_init, "./cs_data/init.bin");

#define PROFILE_BASE_ADDR	(0x90000000)
#define PROFILE_MSG_SIZE	(0x100000)	//1MB, 16 x num per dnc

#define SKEW_VALUE		(0xFF0)

uint32_t dnc_affinity = 0xffff;     // 1-chiplet
uint32_t dnc_cdump_flag;

struct desc_dnc_task_16B_t {
	union dnc_task16b_cmd		task16b_cmd;
	union dnc_task16b_common	task16b_common;
	union dnc_task16b_addr0		task16b_addr0;
	union dnc_task16b_addr1		task16b_addr1;
} __packed __aligned(4);

void __iomem *dnc_base[HW_SPEC_DNC_COUNT];

static uint64_t dnc_cfg_base[HW_SPEC_DNC_COUNT] = {
	DCL0_DNC0_CFG_BASE,
	DCL0_DNC1_CFG_BASE,
	DCL0_DNC2_CFG_BASE,
	DCL0_DNC3_CFG_BASE,
	DCL0_DNC4_CFG_BASE,
	DCL0_DNC5_CFG_BASE,
	DCL0_DNC6_CFG_BASE,
	DCL0_DNC7_CFG_BASE,
#ifndef DCL_SINGLE
	DCL1_DNC0_CFG_BASE,
	DCL1_DNC1_CFG_BASE,
	DCL1_DNC2_CFG_BASE,
	DCL1_DNC3_CFG_BASE,
	DCL1_DNC4_CFG_BASE,
	DCL1_DNC5_CFG_BASE,
	DCL1_DNC6_CFG_BASE,
	DCL1_DNC7_CFG_BASE,
#endif
};

struct dnc_ops dnc_ops;

#define DNC_CONFIG_READ(id, off)			rl_readl_relaxed(dnc_base[id] + CONFIG + off)
#define DNC_TASK_DONE_READ(id, off)			rl_readl_relaxed(dnc_base[id] + TASK_DONE + off)
#define DNC_TASK_DONE_READQ(id)				rl_readq_relaxed(dnc_base[id] + TASK_DONE)
#define DNC_EXCEPTION_READ(id, off)			rl_readl_relaxed(dnc_base[id] + EXCEPTION + off)
#define DNC_ADDRESS_READ(id, off)			rl_readl_relaxed(dnc_base[id] + ADDRESS + off)
#define DNC_SYNC_READ(id, off)				rl_readl_relaxed(dnc_base[id] + SYNC + off)
#define DNC_UAN_READ(id, off)				rl_readl_relaxed(dnc_base[id] + UAN + off)

#define DNC_CONFIG_WRITE(id, val, off)		rl_writel_relaxed(val, dnc_base[id] + CONFIG + off)
#define DNC_TASK_DONE_WRITE(id, val, off)	rl_writel_relaxed(val, dnc_base[id] + TASK_DONE + off)
#define DNC_EXCEPTION_WRITE(id, val, off)	rl_writel_relaxed(val, dnc_base[id] + EXCEPTION + off)
#define DNC_ADDRESS_WRITE(id, val, off)		rl_writel_relaxed(val, dnc_base[id] + ADDRESS + off)
#define DNC_UAN_WRITE(id, val, off)			rl_writel_relaxed(val, dnc_base[id] + UAN + off)

#define DNC_SYNC_WRITE(id, val, off)		rl_writel_relaxed(val, dnc_base[id] + SYNC + off)
#define DNC_STATUS_READ(id, off)			rl_readl_relaxed(dnc_base[id] + STATUS + off)
#define DNC_STATUS_WRITE(id, val, off)		rl_writel_relaxed(val, dnc_base[id] + STATUS + off)
#define DNC_TASK32_READ(id, off)			rl_readl_relaxed(dnc_base[id] + TASK_32B + off)
#define DNC_TASK32_WRITE(id, val, off, exec_id) rl_writel_relaxed(val, dnc_base[id] + TASK_32B + off)

#define DNC_TASK16_READ(id, off)			rl_readl_relaxed(dnc_base[id] + TASK_16B + off)
#define DNC_TASK16_WRITE(id, val, off)	\
	rl_writel_relaxed(val, (dnc_base[id] + TASK_16B + (off)))

#define DNC_TASK_DESC_CONFIG_WRITE_NORECORD(id, val) \
	rl_writeq_relaxed(val, dnc_base[id] + TASK_32B + TASK_DESC_CFG0)

/* UAN information */
#define CORE_ID_NCORE0						0x0
#define CORE_ID_NCORE1						0x1
#define CORE_ID_NC							0x2
#define CORE_ID_ALL							0x3

#define UNIT_ID_TU							0x0
#define UNIT_ID_VU							0x1
#define UNIT_ID_XVU							0x2
#define UNIT_ID_ABLU						0x3
#define UNIT_ID_ABSU						0x4
#define UNIT_ID_SPLU						0x5
#define UNIT_ID_SPSU						0x6
#define UNIT_ID_ALL							0x7
#define UNIT_ID_NCLU						0x0
#define UNIT_ID_NCSU						0x1
#define UNIT_ID_DMA							0x2

#define SUB_UNIT_ID_TU_ROW_IDX				0x0
#define SUB_UNIT_ID_ABLU_ROW_IDX			0x0
#define SUB_UNIT_ID_DMA_IDX_LDUDMA			0x0
#define SUB_UNIT_ID_DMA_IDX_LPUDMA			0x1
#define SUB_UNIT_ID_DMA_IDX_STUDMA			0x2
#define SUB_UNIT_ID_ALL						0xF

#define NCORE_CNT							2
#define TU_ROW_CNT							8
#define ABLU_ROW_CNT						8
#define UNIT_REG_CNT						33
#define SP_REG_CNT							51
#define NC_REG_CNT							163
#define AB_REG_CNT							48
#define UDMA_REG_CNT						19

void dnc_adjust_base(uint32_t cl_id)
{
	RLOG_DBG("adjust dnc address cl id: %d\r\n", cl_id);
	RLOG_DBG("adjust dnc address cl id: %d\r\n", cl_id);

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_base[i] = (void __iomem *)(cl_base[cl_id] + dnc_cfg_base[i]);
}

/*
 * clear dnc's all status registers
 */
static void dnc_clear_status(int dnc_id)
{
	union dnc_status_trig status_trig = { 0, };

	status_trig.bits = 1;
	DNC_STATUS_WRITE(dnc_id, status_trig.bits, ADDR_OFFSET_DNC_STATUS_TRIG);
}

/*
 * clear dnc's all profile log
 */
void dnc_clear_profile_log(void)
{
	union dnc_task_done_trig done_trig = { 0, };
	uint64_t profile_addr = (DNC_PROFILE_BASE_ADDR_HIGH<<32) | DNC_PROFILE_BASE_ADDR_LOW;

	done_trig.done_chk	= 1;
	done_trig.clr_done_queue	= 1;
	done_trig.clr_profile	= 1;

	for (int i = 0 ; i < HW_SPEC_DNC_COUNT; i++)
		DNC_TASK_DONE_WRITE(i, done_trig.bits, ADDR_OFFSET_DNC_TASK_DONE_TRIG);

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		volatile uint8_t *dump_ptr = (volatile uint8_t *)(uintptr_t)profile_addr + (uintptr_t)(i*DNC_PROFILE_MSG_SIZE);

		cpu_clean_dcache_range((uintptr_t)dump_ptr, DNC_PROFILE_MSG_SIZE);
	}
}

#define DNC_SP_TEST_POLL_TIMEOUT_US	1000
int dnc_run_sp_test(int dnc_id, uint32_t pattern)
{
	union dnc_config_sp_test sp_test = { 0, };
	union dnc_status_sp_status01 sp_status01 = { 0, };
	int timeout_cnt = 0;

	dnc_clear_status(dnc_id);

	sp_test.trig = 1;
	sp_test.pattern = pattern;
	sp_test.log_mode = 0x7;

	DNC_CONFIG_WRITE(dnc_id, sp_test.bits, ADDR_OFFSET_DNC_CONFIG_SP_TEST);

	do {
		udelay(1);	// CPU 100Mhz
		sp_status01.bits = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS01);

		if (sp_status01.test_done == 1)
			return RL_OK;
	} while (timeout_cnt++ < DNC_SP_TEST_POLL_TIMEOUT_US);

	RLOG_ERR("%s: dnc%d sp test is failed. pattern(%#x)\r\n", __func__, dnc_id, pattern);
	print_regs("SP_STATUS",
			   (uint64_t)dnc_base[dnc_id] + STATUS + ADDR_OFFSET_DNC_STATUS_SP_STATUS01, 7);

	return RL_TIMEOUT;
}

/*
 * addr_mode : 00: Full-Interleaving
 *			 01: Half-Interleaving
 *			 10: Bank_Stress
 *			 11: Part-Stress
 */
int dnc_sp_mode_test(uint32_t pattern, uint8_t mode)
{
	union dnc_config_sp_en	sp_en = { 0, };
	union dnc_config_sp_cfg2	cfg = { 0, };
	union dnc_config_sp_test	sp_test = { 0, };
	union dnc_status_sp_status01	sp_status01 = { 0, };
	int timeout_cnt = 0;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_clear_status(i);

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		// sp configration
		sp_en.cfg_sp = 1;
		DNC_CONFIG_WRITE(i, sp_en.bits, ADDR_OFFSET_DNC_CONFIG_SP_EN);
	}
	dsb();

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		cfg.sp_cfg2.addr_mode = mode;
		DNC_CONFIG_WRITE(i, cfg.bits, ADDR_OFFSET_DNC_CONFIG_SP_CFG2);

		// tpg engine
		sp_test.trig = 1;
		sp_test.pattern = pattern;
		sp_test.log_mode = 0x7;
		DNC_CONFIG_WRITE(i, sp_test.bits, ADDR_OFFSET_DNC_CONFIG_SP_TEST);
	}

	do {
		int done_cnt = 0;

		for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
			sp_status01.bits = DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_SP_STATUS01);
			if (sp_status01.test_done == 1)
				done_cnt++;
		}

		if (done_cnt == HW_SPEC_DNC_COUNT) {
			for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
				// back to the default mode
				cfg.sp_cfg2.addr_mode = 0;
				DNC_CONFIG_WRITE(i, cfg.bits, ADDR_OFFSET_DNC_CONFIG_SP_CFG2);
				sp_en.cfg_sp = 0;
				DNC_CONFIG_WRITE(i, sp_en.bits, ADDR_OFFSET_DNC_CONFIG_SP_EN);
			}
			return RL_OK;
		}
		udelay(1);
	} while (timeout_cnt++ < DNC_SP_TEST_POLL_TIMEOUT_US);

	RLOG_ERR("%s() failed. pattern(%#x)\r\n", __func__, pattern);
	printf("%s() failed. pattern(%#x)\r\n", __func__, pattern);

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		// back to the default mode
		cfg.sp_cfg2.addr_mode = 0;
		DNC_CONFIG_WRITE(i, cfg.bits, ADDR_OFFSET_DNC_CONFIG_SP_CFG2);
		sp_en.cfg_sp = 0;
		DNC_CONFIG_WRITE(i, sp_en.bits, ADDR_OFFSET_DNC_CONFIG_SP_EN);
	}
	dsb();

	return RL_TIMEOUT;
}

int dnc_sp_test_mode_trigger(void)
{
	union dnc_config_sp_en sp_en = { 0, };
	union dnc_config_sp_cfg2 cfg = { 0, };
	union dnc_config_sp_test sp_test = { 0, };

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_clear_status(i);

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		// sp configuration
		sp_en.cfg_sp = 1;
		DNC_CONFIG_WRITE(i, sp_en.bits, ADDR_OFFSET_DNC_CONFIG_SP_EN);
	}
	dsb();

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		cfg.sp_cfg2.addr_mode = 0x2;	// bank stress
		DNC_CONFIG_WRITE(i, cfg.bits, ADDR_OFFSET_DNC_CONFIG_SP_CFG2);

		// tpg engine
		sp_test.trig = 1;
		sp_test.pattern = 0x2;	// 1'b10
		sp_test.log_mode = 0x7;
		DNC_CONFIG_WRITE(i, sp_test.bits, ADDR_OFFSET_DNC_CONFIG_SP_TEST);
	}

	return RL_OK;
}

int dnc_sp_test_mode_check(void)
{
	union dnc_config_sp_en	sp_en = { 0, };
	union dnc_config_sp_cfg2	cfg = { 0, };
	union dnc_status_sp_status01	sp_status01 = { 0, };
	int timeout_cnt = 0;

	do {
		int done_cnt = 0;

		for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
			sp_status01.bits = DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_SP_STATUS01);
			if (sp_status01.test_done == 1)
				done_cnt++;
		}

		if (done_cnt == HW_SPEC_DNC_COUNT) {
			for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
				// back to the default mode
				cfg.sp_cfg2.addr_mode = 0;	// default 0:ful linterleaving
				DNC_CONFIG_WRITE(i, cfg.bits, ADDR_OFFSET_DNC_CONFIG_SP_CFG2);
				sp_en.cfg_sp = 0;	// config disable
				DNC_CONFIG_WRITE(i, sp_en.bits, ADDR_OFFSET_DNC_CONFIG_SP_EN);
			}
			return RL_OK;
		}
		udelay(1);
	} while (timeout_cnt++ < DNC_SP_TEST_POLL_TIMEOUT_US);

	printf("%s() has time out\r\n", __func__);

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		// back to the default mode
		cfg.sp_cfg2.addr_mode = 0;
		DNC_CONFIG_WRITE(i, cfg.bits, ADDR_OFFSET_DNC_CONFIG_SP_CFG2);
		sp_en.cfg_sp = 0;
		DNC_CONFIG_WRITE(i, sp_en.bits, ADDR_OFFSET_DNC_CONFIG_SP_EN);
	}
	dsb();

	return RL_TIMEOUT;

}

static void dnc_enable_task_done_fifo(int dnc_id)
{
	union dnc_task_comp_rpt_done1 comp_rpt_done = { 0, };
	union dnc_task_ldudma_rpt_done1 ldudma_rpt_done = { 0, };
	union dnc_task_lpudma_rpt_done1 lpudma_rpt_done = { 0, };
	union dnc_task_studma_rpt_done1 studma_rpt_done = { 0, };

	//25-0813, overwrite issue
	comp_rpt_done.addr		= 0x1f + (cl_base[cur_cl_id]>>32);
	ldudma_rpt_done.addr	= 0x1f + (cl_base[cur_cl_id]>>32);
	lpudma_rpt_done.addr	= 0x1f + (cl_base[cur_cl_id]>>32);
	studma_rpt_done.addr	= 0x1f + (cl_base[cur_cl_id]>>32);

	comp_rpt_done.mode = 0x2;
	DNC_TASK32_WRITE(dnc_id, comp_rpt_done.bits, ADDR_OFFSET_DNC_TASK_COMP_RPT_DONE1, 0);
	ldudma_rpt_done.mode = 0x2;
	DNC_TASK32_WRITE(dnc_id, ldudma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_DONE1, 0);
	lpudma_rpt_done.mode = 0x2;
	DNC_TASK32_WRITE(dnc_id, lpudma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_LPUDMA_RPT_DONE1, 0);
	studma_rpt_done.mode = 0x2;
	DNC_TASK32_WRITE(dnc_id, studma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_STUDMA_RPT_DONE1, 0);

#ifdef TEST_MODE_REPORT_OFF
//--------------------------------------------------------------------------------------------
	// 25,0728 test
	comp_rpt_done.mode = 0;
	DNC_TASK32_WRITE(dnc_id, comp_rpt_done.bits, ADDR_OFFSET_DNC_TASK_COMP_RPT_DONE1, 0);
	ldudma_rpt_done.mode = 0;
	DNC_TASK32_WRITE(dnc_id, ldudma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_DONE1, 0);
	lpudma_rpt_done.mode = 0;
	DNC_TASK32_WRITE(dnc_id, lpudma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_LPUDMA_RPT_DONE1, 0);
	studma_rpt_done.mode = 0;
	DNC_TASK32_WRITE(dnc_id, studma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_STUDMA_RPT_DONE1, 0);
//--------------------------------------------------------------------------------------------
#endif
}

#ifdef ZEBU
static inline void dnc_config_task_timeout(int dnc_id) { }
#else
static void dnc_config_task_timeout(int dnc_id)
{
	const uint32_t atom_dnc_timeout = BIT_MASK(20);
	union dnc_task_timeout0 timeout0 = { 0, };
	union dnc_task_timeout1 timeout1 = { 0, };

	timeout0.threshold = atom_dnc_timeout;
	DNC_TASK32_WRITE(dnc_id, timeout0.bits, ADDR_OFFSET_DNC_TASK_TIMEOUT0, 0);

	timeout1.mode = 0x7;
	timeout1.threshold = 0xFFFF;
	DNC_TASK32_WRITE(dnc_id, timeout1.bits, ADDR_OFFSET_DNC_TASK_TIMEOUT1, 0);
}
#endif

static void dnc_change_tsync_id(int dnc_id)
{
	union dnc_sync_set_my_id my_id = { 0, };

	my_id.tsync = dnc_id;
	DNC_SYNC_WRITE(dnc_id, my_id.bits, ADDR_OFFSET_DNC_SYNC_SET_MY_ID);
}

static void dnc_enable_task_done_irq(uint32_t dnc_id)
{
	union dnc_task_done_do done_do = { 0, };

	done_do.bits = DNC_TASK_DONE_READ(dnc_id, ADDR_OFFSET_DNC_TASK_DONE_DO);

	/* done_do.en_log = 1; enable when feature implemented */
	/* done_do.en_profile = 1; enable only when profile */
	done_do.en_intr = 1;
	done_do.en_measure = 0;
	done_do.en_cdump = 0;
	done_do.en_profile = 0;

#ifdef TEST_MODE_CDUMP_ALL
//--------------------------------------------------------------
	//25,0728 test
	/* done_do.en_log = 1; enable when feature implemented */
	/* done_do.en_profile = 1; enable only when profile */
	done_do.en_intr = 1;
	done_do.en_measure = 0;
	done_do.en_cdump = 1;

	done_do.en_profile = 0;
//--------------------------------------------------------------
#endif
	DNC_TASK_DONE_WRITE(dnc_id, done_do.bits, ADDR_OFFSET_DNC_TASK_DONE_DO);
}

void *dnc_profile_ptr(int dnc_id)
{
	return (void *)((DNC_PROFILE_BASE_ADDR_HIGH << 32) |
		(DNC_PROFILE_BASE_ADDR_LOW + (DNC_PROFILE_MSG_SIZE * dnc_id)));
}

uint32_t dnc_profile_get_count(int dnc_id)
{
	union dnc_task_done_profile_status	stat;

	stat.bits	= DNC_TASK_DONE_READ(dnc_id, ADDR_OFFSET_DNC_TASK_DONE_PROFILE_STATUS);
	return stat.count;
}

static void dnc_enable_profile_mode(uint8_t dnc_id)
{
	union dnc_task_done_profile_mode	profile_mode = {0, };
	union dnc_task_done_profile_dest0	profile_dest0 = {0, };
	union dnc_task_done_profile_dest1	profile_dest1 = {0, };

// Need to separate STC & workload case
	profile_mode.comp = 0;
	profile_mode.ldudma = 0;	//1;
	profile_mode.lpudma = 0;	//1;
	profile_mode.studma = 0;	//1;

	DNC_TASK_DONE_WRITE(dnc_id, profile_mode.bits, ADDR_OFFSET_DNC_TASK_DONE_PROFILE_MODE);

	profile_dest0.addr = DNC_PROFILE_BASE_ADDR_LOW + (DNC_PROFILE_MSG_SIZE*dnc_id);
	DNC_TASK_DONE_WRITE(dnc_id, profile_dest0.bits, ADDR_OFFSET_DNC_TASK_DONE_PROFILE_DEST0);

	profile_dest1.addr	= DNC_PROFILE_BASE_ADDR_HIGH;
	DNC_TASK_DONE_WRITE(dnc_id, profile_dest1.bits, ADDR_OFFSET_DNC_TASK_DONE_PROFILE_DEST1);

	RLOG_DBG("dnc profile enable %d\r\n", dnc_id);
}

static void dnc_enable_exception_irq(int dnc_id)
{
	union dnc_exception_do exception_do = { 0, };

	// This is guide setting!
	DNC_EXCEPTION_WRITE(dnc_id, 0, ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK0);
	DNC_EXCEPTION_WRITE(dnc_id, 0, ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK1);

	// 25-0801, masked sp port timeout error case
	// In the STC vector pattern, even when CDUMP is disabled, an SP timeout occurs, so it was decided to mask it.
#ifdef SORT_MODE
	DNC_EXCEPTION_WRITE(dnc_id, 0x3f0000, ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK2);
#else
	DNC_EXCEPTION_WRITE(dnc_id, 0, ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK2);
#endif

	// 25-0730, suggested by hong-yun
	// Do alarm message from SP_ce, DBUS_ce, CBUS_ce
#ifdef SORT_MODE
	DNC_EXCEPTION_WRITE(dnc_id, 0xfffffff8, ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK3);
#else
	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK3);
#endif

	/* TODO: remove this after false dnc exception is fixed */
#ifndef AUTO_FETCH_ENABLED
	/* TODO: need to check later */
	//DNC_EXCEPTION_WRITE(dnc_id, 0, ADDR_OFFSET_DNC_EXCEPTION_INTR_MASK3);
#endif

#ifdef SORT_MODE
	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK0); // timeout mask
	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK1);
	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK2);
	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK3);

	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK0); // timeout mask
	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK1);
	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK2);
	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK3);
#else
	// abort , 250728 guide
	DNC_EXCEPTION_WRITE(dnc_id, 0x07070707, ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK0); // timeout mask
	DNC_EXCEPTION_WRITE(dnc_id, 0, ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK1);
	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK2);
	DNC_EXCEPTION_WRITE(dnc_id, 0x7fffffff, ADDR_OFFSET_DNC_EXCEPTION_ABORT_MASK3);

	// aeh , 250728 guide
	DNC_EXCEPTION_WRITE(dnc_id, 0x07070707, ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK0); // timeout mask
	DNC_EXCEPTION_WRITE(dnc_id, 0, ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK1);
	DNC_EXCEPTION_WRITE(dnc_id, 0xffffffff, ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK2);
	DNC_EXCEPTION_WRITE(dnc_id, 0x7fffffff, ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK3);
#endif

#ifndef AUTO_FETCH_ENABLED
	//DNC_EXCEPTION_WRITE(dnc_id, 0, ADDR_OFFSET_DNC_EXCEPTION_AEH_MASK3);
#endif

	exception_do.bits = DNC_EXCEPTION_READ(dnc_id, ADDR_OFFSET_DNC_EXCEPTION_DO);
	exception_do.en_intr = 1;
	exception_do.en_auto_pause_comp = 1;
	exception_do.en_auto_pause_ldudma = 1;
	exception_do.en_auto_pause_lpudma = 1;
	exception_do.en_auto_pause_studma = 1;
	exception_do.en_auto_cdump = 0;	/* TODO: auto cdump will be implemented later */
	exception_do.en_implicit_chk = 1;
	DNC_EXCEPTION_WRITE(dnc_id, exception_do.bits, ADDR_OFFSET_DNC_EXCEPTION_DO);
}

static void dnc_enable_acc_regs(int dnc_id)
{
	union dnc_status_do status_do = { 0, };

	status_do.acc_en = 1;
	DNC_STATUS_WRITE(dnc_id, status_do.bits, ADDR_OFFSET_DNC_STATUS_DO);
}

static void dnc_enable_sync_log(int dnc_id)
{
	union dnc_sync_do sync_do = { 0, };

	sync_do.bits = DNC_SYNC_READ(dnc_id, ADDR_OFFSET_DNC_SYNC_DO);

	sync_do.en_passage_log = 1;
	sync_do.en_passage_acc = 1;

	DNC_SYNC_WRITE(dnc_id, sync_do.bits, ADDR_OFFSET_DNC_SYNC_DO);
}

/* dnc skew */
void dnc_skew_delay(uint8_t dnc_id, uint8_t delay)
{
	union dnc_task_delay	task_delay = {0, };
//	union dnc_config_sp_pinit_cfg	sp_pinit_cfg = {0, };

	task_delay.bits = DNC_TASK32_READ(dnc_id, ADDR_OFFSET_DNC_DELAY);
	task_delay.dummy = delay * dnc_id;

	DNC_TASK32_WRITE(dnc_id, task_delay.bits, ADDR_OFFSET_DNC_DELAY, 0);

//	sp_pinit_cfg.skew = delay/2 * dnc_id;
//	DNC_CONFIG_WRITE(dnc_id, sp_pinit_cfg.bits, ADDR_OFFSET_DNC_CONFIG_SP_PINIT_CFG);
}

/* ncore skew */
void ncore_skew_delay(uint8_t dnc_id, uint8_t delay)
{
	union dnc_config_sp_pinit_cfg	sp_pinit_cfg = {0, };

	sp_pinit_cfg.bits = DNC_CONFIG_READ(dnc_id, ADDR_OFFSET_DNC_CONFIG_SP_PINIT_CFG);
	sp_pinit_cfg.skew = delay;

	DNC_CONFIG_WRITE(dnc_id, sp_pinit_cfg.bits, ADDR_OFFSET_DNC_CONFIG_SP_PINIT_CFG);
}

void dnc_sp_test_status(int dnc_id)
{
	union	dnc_status_sp_status01	status01 = {0, };
	union	dnc_status_sp_status03	status03 = {0, };
	union	dnc_status_sp_status04	sp_test_log0 = {0, };
	union	dnc_status_sp_status05	sp_test_log1 = {0, };
	union	dnc_status_sp_status06	sp_test_log2 = {0, };
	union	dnc_status_sp_status07	sp_test_log3 = {0, };

	status01.bits = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS01);
	if (status01.test_cnt_mismatch != 0x0) {
		status03.bits = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS03);
		printf("%20s dnc%02d cnt_ce:%2d cnt_ue:%2d\r\n", "test_cnt_mismatch", dnc_id,
												status03.test_cnt_ce, status03.test_cnt_ue);

		//detail info
		sp_test_log0.bits = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS04);
		if (sp_test_log0.sp_test_log.valid == 0x1) {
			printf("addr:0x%08x ce:%x ue:%x ptm:%x\r\n",
											sp_test_log0.sp_test_log.addr,
											sp_test_log0.sp_test_log.ce,
											sp_test_log0.sp_test_log.ue,
											sp_test_log0.sp_test_log.ptm);
		}
		sp_test_log1.bits = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS05);
		if (sp_test_log1.sp_test_log.valid == 0x1) {
			printf("addr:0x%08x ce:%x ue:%x ptm:%x\r\n",
											sp_test_log1.sp_test_log.addr,
											sp_test_log1.sp_test_log.ce,
											sp_test_log1.sp_test_log.ue,
											sp_test_log1.sp_test_log.ptm);
		}
		sp_test_log2.bits = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS06);
		if (sp_test_log2.sp_test_log.valid == 0x1) {
			printf("addr:0x%08x ce:%x ue:%x ptm:%x\r\n",
											sp_test_log2.sp_test_log.addr,
											sp_test_log2.sp_test_log.ce,
											sp_test_log2.sp_test_log.ue,
											sp_test_log2.sp_test_log.ptm);
		}
		sp_test_log3.bits = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS07);
		if (sp_test_log3.sp_test_log.valid == 0x1) {
			printf("addr:0x%08x ce:%x ue:%x ptm:%x\r\n",
											sp_test_log3.sp_test_log.addr,
											sp_test_log3.sp_test_log.ce,
											sp_test_log3.sp_test_log.ue,
											sp_test_log3.sp_test_log.ptm);
		}
		printf("\r\n");
	}
}

static void dnc_enable_erun_method(uint32_t dnc_id)
{
	union dnc_task_do task_do = { 0, };

	task_do.bits = DNC_TASK32_READ(dnc_id, ADDR_OFFSET_DNC_TASK_DO);

#if EVT_VER == 1
	task_do.en_wait_handle = 0;

	DNC_TASK32_WRITE(dnc_id, task_do.bits, ADDR_OFFSET_DNC_TASK_DO, 0);
#endif
}

static int dnc_reg_init(int dnc_id)
{
	int ret = RL_OK;

//	printf("\r\ndnc_run_sp_test start\r\n");

	ret = dnc_run_sp_test(dnc_id, 0x2);
	if (ret)
		return ret;
	ret = dnc_run_sp_test(dnc_id, 0x0);
	if (ret)
		return ret;

	RLOG_INFO("[dnc%02d] dnc_run_sp_test pass\r\n", dnc_id);

	dnc_sp_test_status(dnc_id);

	/* TODO: Run sanity check workload */
	dnc_enable_acc_regs(dnc_id);
	dnc_enable_task_done_fifo(dnc_id);

	dnc_enable_sync_log(dnc_id);

#ifndef AUTO_FETCH_ENABLED
	/*
	 * Timeout in Pre-Run due to tsync waiting may occur.
	 * If compute chunk's cp dependency is resolved and enqueued to dnc queue,
	 * but tsync is not received from udma, a timeout error may occur.
	 */
	dnc_config_task_timeout(dnc_id);
#endif
	dnc_ops.init(dnc_id);

// This Point cause fail in Silicon. 2025-0717
//	dnc_change_tsync_id(dnc_id);

	dnc_enable_task_done_irq(dnc_id);
	dnc_enable_exception_irq(dnc_id);

	dnc_enable_profile_mode(dnc_id);

	dnc_enable_erun_method(dnc_id);

	return RL_OK;
}

#ifdef ZEBU
#define DNC_COMPUTE_POLL_TIMEOUT_US	1000000
#else
#define DNC_COMPUTE_POLL_TIMEOUT_US	1000
#endif
#define DNC_COMPUTE_POLL_INTERVAL_US 1

int dnc_compute(int dnc_id, uint64_t addr, uint32_t sp_size)
{
	uint64_t spm_base_addr = cl_base[cur_cl_id] + SP_SHM_PHYSICAL_START + SZ_4M * dnc_id;
	union dnc_config_sp_pinit sp_pinit = { 0, };
	union dnc_status_sp_status00 sp_status00;
	uint32_t timeout_cnt = DNC_COMPUTE_POLL_TIMEOUT_US / DNC_COMPUTE_POLL_INTERVAL_US;

	memcpy((void *)spm_base_addr, (const void *)addr, sp_size);

	sp_pinit.trig = 1;
	sp_pinit.size = sp_size >> BIT_WIDTH_128B;
	DNC_CONFIG_WRITE(dnc_id, sp_pinit.bits, ADDR_OFFSET_DNC_CONFIG_SP_PINIT);

	do {
		udelay(1);
		sp_status00.bits = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS00);
		if (sp_status00.bits == 0)
			return RL_OK;
	} while (timeout_cnt--);

	return RL_TIMEOUT;
}

#define HC_SIZE	4352
static int dnc_hc(int dnc_id)
{
	int ret = RL_OK;

	RLOG_DBG("dnc %d %s\r\n", dnc_id, __func__);
	ret = dnc_compute(dnc_id, (uint64_t)g_hc_bin_init_data, HC_SIZE);
	if (ret) {
		RLOG_ERR("dnc %d HC failed\r\n", dnc_id);
		return ret;
	}

	return ret;
}

#define CS_BIN_SIZE	1920
int dnc_checksum(int dnc_id, uint32_t addr, uint32_t size)
{
	union dnc_uan_base_unit_info info = { 0, };
	int ret = RL_OK;

	RLOG_DBG("dnc %d %s\r\n", dnc_id, __func__);

	info.core_id = CORE_ID_NCORE0;
	info.unit_id = UNIT_ID_SPLU;	// SPLU
	info.sub_unit_id = SUB_UNIT_ID_TU_ROW_IDX; // don't care
	DNC_UAN_WRITE(dnc_id, info.bits, ADDR_OFFSET_DNC_UAN_BASE_UNIT_INFO);

	// SP offset
	DNC_UAN_WRITE(dnc_id, addr, ADDR_OFFSET_DNC_UAN_SP_LRF_0);

	// if set JCR[0] = 0x10, 4Kbyte	(256bytes * JCR[0])
	DNC_UAN_WRITE(dnc_id, (size>>8), ADDR_OFFSET_DNC_UAN_SP_JCR_0);


	info.core_id = CORE_ID_NCORE0;
	info.unit_id = UNIT_ID_VU;	// VU
	info.sub_unit_id = SUB_UNIT_ID_TU_ROW_IDX; // don't care
	DNC_UAN_WRITE(dnc_id, info.bits, ADDR_OFFSET_DNC_UAN_BASE_UNIT_INFO);

	// if set JCR[0] = 0x10, 4Kbyte	(256bytes * JCR[0])
	DNC_UAN_WRITE(dnc_id, (size>>8), ADDR_OFFSET_DNC_UAN_UNIT_JCR_0);

	ret = dnc_compute(dnc_id, (uint64_t)g_cs_bin_init_data, CS_BIN_SIZE);
	if (ret) {
		RLOG_ERR("dnc %d checksum bin failed\r\n", dnc_id);
		return ret;
	}

	return ret;
}

static void clear_status(uint32_t start, uint32_t num)
{
	/* clear acc regs */
	for (uint32_t i = start; i < start + num; i++)
		dnc_clear_status(i);
}

static char *uan_unit_name(uint32_t core_id, uint32_t unit_id)
{
	static char ncore_unit_name[][16] = {
		"TU", "VU", "XVU", "ABLU", "ABSU", "SPLU", "SPSU", "ALL",
	};
	static char nc_unit_name[][16] = {
		"NCLU", "NCSU", "DMA", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "ALL",
	};
	static char unknown[16] = "UNKNOWN";

	if ((core_id == CORE_ID_NCORE0) || (core_id == CORE_ID_NCORE1))
		return ncore_unit_name[unit_id];
	else if (core_id == CORE_ID_NC)
		return nc_unit_name[unit_id];
	else
		return unknown;
}

static char *uan_sub_unit_name(uint32_t core_id, uint32_t unit_id, uint32_t sub_unit_id)
{
	static char tu_sub_unit_name[][16] = {
		"TU0", "TU1", "TU2", "TU3", "TU4", "TU5", "TU6", "TU7",
	};
	static char ablu_sub_unit_name[][16] = {
		"ABLU0", "ABLU1", "ABLU2", "ABLU3", "ABLU4", "ABLU5", "ABLU6", "ABLU7",
	};
	static char dma_sub_unit_name[][16] = {
		"LDuDMA", "LPuDMA", "STuDMA",
	};
	static char unknown[16] = "UNKNOWN";

	if ((core_id == CORE_ID_NCORE0 || core_id == CORE_ID_NCORE1) && unit_id == UNIT_ID_TU)
		return tu_sub_unit_name[sub_unit_id];
	else if ((core_id == CORE_ID_NCORE0 || core_id == CORE_ID_NCORE1) && unit_id == UNIT_ID_ABLU)
		return ablu_sub_unit_name[sub_unit_id];
	else if ((core_id == CORE_ID_NC) && (unit_id == UNIT_ID_DMA))
		return dma_sub_unit_name[sub_unit_id];
	else
		return unknown;
}

static char *uan_name(uint32_t core_id, uint32_t unit_id, uint32_t sub_unit_id)
{
	static char name[256];
	static char core_name[][16] = {
		"NCORE0", "NCORE1", "NC", "ALL",
	};

	memset(name, 0, sizeof(name));

	sprintf(name, "%s/%s/%s", core_name[core_id], uan_unit_name(core_id, unit_id),
			uan_sub_unit_name(core_id, unit_id, sub_unit_id));

	return name;
}

/* CE/UE bit masks for exception abort decision.
 * reg3 bits[2:0] (sp_ce, dbus_ce, cbus_ce)
 * reg1 sp_ue(bit18), ext_dbus_ue(bit24), ext_cbus_ue(bit25)
 * reg0 (timeout), reg2 (AXI resp) are always non-CE/UE.
 */
#define DNC_REG1_UE_MASK	((1u << 18) | (1u << 19) | (1u << 24) | (1u << 25))
#define DNC_REG3_CE_MASK	(0x7u)

static bool g_dnc_should_abort;

//#define HBM_CSR_READ(addr)		rl_readl_relaxed((void *)(addr))

static void dnc_get_exception_intrpt_status(int dnc_id)
{
//	uint32_t reg;

	test_exception_mark();
	g_dnc_should_abort = false;

#if defined(INDICATOR_DEBUG_MODE)
	TEST_GPD2_DAT |= 0x1;	// trigger GPD2[0]
//	GPIO_SET_DAT()
#endif /* #if defined(INDICATOR_DEBUG_MODE) */

	abort_other_cores();

	/*
	 * If en_implicit_chk is enabled, it becomes a pending clear as soon as the exception(0xC)
	 * register is read
	 */

#ifdef SORT_MODE
	uint32_t reg0, reg1, reg2, reg3;
	union dnc_status_sp_status08	sp_status = {0, };
	union err_exception1	err_exception1 = {0, };
	union err_exception2	err_exception2 = {0, };
	union err_exception3	err_exception3 = {0, };

	RLOG_ERR("%s\r\n", "DNC_EXCEPTION");
	printf("%s\r\n", "DNC_EXCEPTION");

	reg0 = rl_readl((void __iomem *)((uint64_t)dnc_base[dnc_id] + EXCEPTION));
	reg1 = rl_readl((void __iomem *)((uint64_t)dnc_base[dnc_id] + EXCEPTION + 0x4));
	reg2 = rl_readl((void __iomem *)((uint64_t)dnc_base[dnc_id] + EXCEPTION + 0x8));
	reg3 = rl_readl((void __iomem *)((uint64_t)dnc_base[dnc_id] + EXCEPTION + 0xC));
	dsb();

	err_exception1.bits = reg1;
	if (err_exception1.bits & 0xff) {
		RLOG_ERR("\r\n[FAIL]ncore0 exception\r\n");
		printf("\r\n[FAIL]ncore0 exception\r\n");
	}
	dsb();
	if (err_exception1.bits & 0xff00) {
		RLOG_ERR("\r\n[FAIL]ncore1 exception\r\n");
		printf("\r\n[FAIL]ncore1 exception\r\n");
	}
	dsb();
	if (err_exception1.ex_nclu) {
		RLOG_ERR("\r\n[FAIL]Exception in NCLU\r\n");
		printf("\r\n[FAIL]Exception in NCLU\r\n");
	}
	dsb();
	if (err_exception1.ex_ncsu) {
		RLOG_ERR("\r\n[FAIL]Exception in NCSU\r\n");
		printf("\r\n[FAIL]Exception in NCSU\r\n");
	}
	dsb();
	if (err_exception1.sp_ue) {
		RLOG_ERR("\r\n[FAIL]Exception in Scratch-Pad(UE)\r\n");
		printf("\r\n[FAIL]Exception in Scratch-Pad(UE)\r\n");
	}
	dsb();
	if (err_exception1.sp_perr) {
		RLOG_ERR("\r\n[FAIL]Exception in Scratch-Pad(PE)\r\n");
		printf("\r\n[FAIL]Exception in Scratch-Pad(PE)\r\n");
	}
	dsb();
	if (err_exception1.ext_dbus_ue) {
		RLOG_ERR("\r\n[FAIL]Exception from External Memory(DBUS,UE)\r\n");
		printf("\r\n[FAIL]Exception from External Memory(DBUS,UE)\r\n");
	}
	dsb();
	if (err_exception1.ext_cbus_ue) {
		RLOG_ERR("\r\n[FAIL]Exception from External Memory(CBUS,UE)\r\n");
		printf("\r\n[FAIL]Exception from External Memory(CBUS,UE)\r\n");
	}
	dsb();
	if (err_exception1.pwr_single_only_vio) {
		RLOG_ERR("\r\n[FAIL]Exception Posted Write(PWR)\r\n");
		printf("\r\n[FAIL]Exception Posted Write(PWR)\r\n");
	}
	dsb();
	if (err_exception1.tsync_token_ovf) {
		RLOG_ERR("\r\n[FAIL]Exception in TSYNC\r\n");
		printf("\r\n[FAIL]Exception in TSYNC\r\n");
	}
	dsb();

	err_exception2.bits = reg2;
	if (err_exception2.ext_dbus_rd_resp0) {
		RLOG_ERR("\r\n[FAIL]AXI Response Error on DBUS-RD[0]\r\n");
		printf("\r\n[FAIL]AXI Response Error on DBUS-RD[0]\r\n");
	}
	dsb();
	if (err_exception2.ext_dbus_rd_resp1) {
		RLOG_ERR("\r\n[FAIL]AXI Response Error on DBUS-RD[1]\r\n");
		printf("\r\n[FAIL]AXI Response Error on DBUS-RD[1]\r\n");
	}
	dsb();
	if (err_exception2.ext_dbus_wr_resp0) {
		RLOG_ERR("\r\n[FAIL]AXI Response Error on DBUS-WR[0]\r\n");
		printf("\r\n[FAIL]AXI Response Error on DBUS-WR[0]\r\n");
	}
	dsb();
	if (err_exception2.ext_dbus_wr_resp1) {
		RLOG_ERR("\r\n[FAIL]AXI Response Error on DBUS-WR[1]\r\n");
		printf("\r\n[FAIL]AXI Response Error on DBUS-WR[1]\r\n");
	}
	dsb();
	if (err_exception2.ext_cbus_rd_resp0) {
		RLOG_ERR("\r\n[FAIL]AXI Response Error on CBUS-RD[0]\r\n");
		printf("\r\n[FAIL]AXI Response Error on CBUS-RD[0]\r\n");
	}
	dsb();
	if (err_exception2.ext_cbus_rd_resp1) {
		RLOG_ERR("\r\n[FAIL]AXI Response Error on CBUS-RD[1]\r\n");
		printf("\r\n[FAIL]AXI Response Error on CBUS-RD[1]\r\n");
	}
	dsb();
	if (err_exception2.ext_cbus_wr_resp0) {
		RLOG_ERR("\r\n[FAIL]AXI Response Error on CBUS-WR[0]\r\n");
		printf("\r\n[FAIL]AXI Response Error on CBUS-WR[0]\r\n");
	}
	dsb();
	if (err_exception2.ext_cbus_wr_resp1) {
		RLOG_ERR("\r\n[FAIL]AXI Response Error on CBUS-WR[1]\r\n");
		printf("\r\n[FAIL]AXI Response Error on CBUS-WR[1]\r\n");
	}
	dsb();

	err_exception3.bits = reg3;
	if (err_exception3.sp_ce) {
		RLOG_ERR("\r\n[FAIL]Exception in Scratch-Pad(CE)\r\n");
		printf("\r\n[FAIL]Exception in Scratch-Pad(CE)\r\n");
	}
	dsb();
	if (err_exception3.dbus_ce) {
		RLOG_ERR("\r\n[FAIL]Exception from External Memory(DBUS,CE)\r\n");
		printf("\r\n[FAIL]Exception from External Memory(DBUS,CE)\r\n");
	}
	dsb();
	if (err_exception3.cbus_ce) {
		RLOG_ERR("\r\n[FAIL]Exception from External Memory(CBUS,CE)\r\n");
		printf("\r\n[FAIL]Exception from External Memory(CBUS,CE)\r\n");
	}
	dsb();

	RLOG_ERR("[%#lx] %#x %#x %#x %#x\r\n",
		(uint64_t)dnc_base[dnc_id] + EXCEPTION,
		reg0, reg1, reg2, reg3);

	dsb();

	printf("[%#lx] %#x %#x %#x %#x\r\n",
		(uint64_t)dnc_base[dnc_id] + EXCEPTION,
		reg0, reg1, reg2, reg3);

	dsb();

	if (reg3 & 0x7) {
		sp_status.bits = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS08);
		printf("dnc%02d, tot_ce:%-8d, tot_ue:%-8d\r\n\r\n", dnc_id, sp_status.tot_ce, sp_status.tot_ue);

		union dnc_status_sp_status04	test_log0 = {0, };
		union dnc_status_sp_status05	test_log1 = {0, };
		union dnc_status_sp_status06	test_log2 = {0, };
		union dnc_status_sp_status07	test_log3 = {0, };

		test_log0.bits	= DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS04);
		if (test_log0.sp_test_log.addr != 0 && test_log0.sp_test_log.valid == 1) {
			printf("0x%lx ", test_log0.sp_test_log.addr<<7);
			if (test_log0.sp_test_log.ce)
				printf("CE ");
			if (test_log0.sp_test_log.ue)
				printf("UE ");
			if (test_log0.sp_test_log.ptm)
				printf("PTM ");
			if (test_log0.sp_test_log.valid)
				printf("VALID ");
			printf("\r\n");
		}
		test_log1.bits	= DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS05);
		if (test_log1.sp_test_log.addr != 0 && test_log0.sp_test_log.valid == 1) {
			printf("0x%lx ", test_log1.sp_test_log.addr<<7);
			if (test_log1.sp_test_log.ce)
				printf("CE ");
			if (test_log1.sp_test_log.ue)
				printf("UE ");
			if (test_log1.sp_test_log.ptm)
				printf("PTM ");
			if (test_log1.sp_test_log.valid)
				printf("VALID ");
			printf("\r\n");
		}
		test_log2.bits	= DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS06);
		if (test_log2.sp_test_log.addr != 0 && test_log0.sp_test_log.valid == 1) {
			printf("0x%lx ", test_log2.sp_test_log.addr<<7);
			if (test_log2.sp_test_log.ce)
				printf("CE ");
			if (test_log2.sp_test_log.ue)
				printf("UE ");
			if (test_log2.sp_test_log.ptm)
				printf("PTM ");
			if (test_log2.sp_test_log.valid)
				printf("VALID ");
			printf("\r\n");
		}
		test_log3.bits	= DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_SP_STATUS07);
		if (test_log3.sp_test_log.addr != 0 && test_log0.sp_test_log.valid == 1) {
			printf("0x%lx ", test_log3.sp_test_log.addr<<7);
			if (test_log3.sp_test_log.ce)
				printf("CE ");
			if (test_log3.sp_test_log.ue)
				printf("UE ");
			if (test_log3.sp_test_log.ptm)
				printf("PTM ");
			if (test_log3.sp_test_log.valid)
				printf("VALID ");
			printf("\r\n");
		}
		dsb();
	}

	/* non-CE/UE error exists → should abort */
	if (reg0 || reg2 || (reg1 & ~DNC_REG1_UE_MASK) || (reg3 & ~DNC_REG3_CE_MASK))
		g_dnc_should_abort = true;
#else
	{
		uint32_t r0, r1, r2, r3;

		r0 = rl_readl((void __iomem *)((uint64_t)dnc_base[dnc_id] + EXCEPTION));
		r1 = rl_readl((void __iomem *)((uint64_t)dnc_base[dnc_id] + EXCEPTION + 0x4));
		r2 = rl_readl((void __iomem *)((uint64_t)dnc_base[dnc_id] + EXCEPTION + 0x8));
		r3 = rl_readl((void __iomem *)((uint64_t)dnc_base[dnc_id] + EXCEPTION + 0xC));
		dsb();

		printf("\r\n[%#lx] %#x %#x %#x %#x\r\n",
			(uint64_t)dnc_base[dnc_id] + EXCEPTION, r0, r1, r2, r3);

		if (r0 || r2 || (r1 & ~DNC_REG1_UE_MASK) || (r3 & ~DNC_REG3_CE_MASK))
			g_dnc_should_abort = true;
	}
#endif

// too many info, Do make cdump path
#ifdef TEST_MODE_ALL_CDUMP
	print_regs("DNC_STATUS", (uint64_t)dnc_base[dnc_id] + STATUS, 240);
	print_regs("DNC_TASK32", (uint64_t)dnc_base[dnc_id] + TASK_32B, 64);
	print_regs("DNC_SYNC", (uint64_t)dnc_base[dnc_id] + SYNC, 128);
#endif
}


/* DNC exception interrupt handler
 * CE/UE only → flag only (test_exception_mark).
 * Non-CE/UE  → abort via rl_abort_cur_ctx.
 */
#define DEFINE_DNC_EXCEPTION_IRQ_HANDLER(x)	\
void dnc_ ## x ##_exception_handler(void *data) \
{	\
	RLOG_ERR("DNC %d exception!\r\n", x); \
	dnc_get_exception_intrpt_status(x); \
	if (g_dnc_should_abort) \
		rl_abort_cur_ctx(ERR_DNC); \
}

DEFINE_DNC_EXCEPTION_IRQ_HANDLER(0)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(1)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(2)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(3)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(4)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(5)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(6)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(7)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(8)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(9)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(10)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(11)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(12)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(13)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(14)
DEFINE_DNC_EXCEPTION_IRQ_HANDLER(15)

/* DNC done interrupt handler */
#define DEFINE_DNC_DONE_IRQ_HANDLER(x)	\
void dnc_ ## x ##_done_handler(void *data) \
{	\
	union irq_info irq_data; \
	union dnc_reg_done_passage dnc_exec_done_passage; \
	rl_profile_log_start(HANDLER); \
	dnc_exec_done_passage.bits = DNC_TASK_DONE_READQ(x); \
	irq_data.bits = dnc_ops.get_irq_status(x, (void *)&dnc_exec_done_passage); \
	rl_profile_log(HANDLER, irq_data.exec_id.cmd_id, irq_data.cmd_type); \
}

DEFINE_DNC_DONE_IRQ_HANDLER(0)
DEFINE_DNC_DONE_IRQ_HANDLER(1)
DEFINE_DNC_DONE_IRQ_HANDLER(2)
DEFINE_DNC_DONE_IRQ_HANDLER(3)
DEFINE_DNC_DONE_IRQ_HANDLER(4)
DEFINE_DNC_DONE_IRQ_HANDLER(5)
DEFINE_DNC_DONE_IRQ_HANDLER(6)
DEFINE_DNC_DONE_IRQ_HANDLER(7)
DEFINE_DNC_DONE_IRQ_HANDLER(8)
DEFINE_DNC_DONE_IRQ_HANDLER(9)
DEFINE_DNC_DONE_IRQ_HANDLER(10)
DEFINE_DNC_DONE_IRQ_HANDLER(11)
DEFINE_DNC_DONE_IRQ_HANDLER(12)
DEFINE_DNC_DONE_IRQ_HANDLER(13)
DEFINE_DNC_DONE_IRQ_HANDLER(14)
DEFINE_DNC_DONE_IRQ_HANDLER(15)


static uint32_t dnc_get_ip_ver(void)
{
	union dnc_config_ip_info1 ip_info1;
	union dnc_config_ip_info3 ip_info3;

	ip_info1.bits = DNC_CONFIG_READ(0, ADDR_OFFSET_DNC_CONFIG_IP_INFO1);
	ip_info3.bits = DNC_CONFIG_READ(0, ADDR_OFFSET_DNC_CONFIG_IP_INFO3);

	RLOG_DBG("DNC HW INFO: rel_date %#lx, ML%u DEV%u, IP ver %u, MRV ver %u.%u\r\n",
			 DNC_CONFIG_READ(0, ADDR_OFFSET_DNC_CONFIG_IP_INFO0),
			 ip_info1.maj_ver, ip_info1.min_ver, ip_info1.ip_ver,
			 ip_info3.regmap_maj_ver, ip_info3.regmap_min_ver);

	return ip_info1.ip_ver;
}

static void dnc_register_ops(void)
{
	uint32_t ip_ver = dnc_get_ip_ver();

	if (ip_ver == DNC_V1_0)
		printf("[DNC] SoC: REBELQ_EVT0, (DNC IP v1.0)\r\n", ip_ver);
	else if (ip_ver == DNC_V1_1)
		printf("[DNC] SoC: REBELQ_EVT1, (DNC IP v1.1)\r\n", ip_ver);

	if (ip_ver == DNC_V1_0 || ip_ver == DNC_V1_1) {
		evt_dnc_register_ops(&dnc_ops);
	} else {
		RLOG_ERR("This IP version (%d) is not supported\r\n", ip_ver);
		rl_abort_event(ERR_DNC);
	}
}

static inline void dnc_generate_comp_spm_tlb(int dnc_id, int vpn,
											 enum comp_tlb_table_type table_type)
{
	union dnc_task_desc_cfg0 cfg0 = {0, };
	union dnc_task_desc_cfg1 cfg1 = {0, };
	uint64_t pkt, pa = 0;
	uint64_t spm_base_dcl0 = (cl_base[cur_cl_id] + DCL0_SP_MEM_BASE);
	uint64_t spm_base_dcl1 = (cl_base[cur_cl_id] + DCL1_SP_MEM_BASE);

	if (table_type == COMP_TLB_TABLE_TYPE_DCL01_2_CROSS) {
		if (dnc_id < HW_SPEC_HALF_DNC_COUNT) {
			pa = spm_base_dcl0 + SZ_2M * vpn;
		} else {
			if (vpn < 16) {
				pa = spm_base_dcl1 + SZ_2M * vpn;
			} else {
				//RLOG_ERR("%s vpn < 16 but %d\r\n", comp_tlb_table_type_str[table_type], vpn);
				rl_abort_cur_ctx(ERR_TLB_PRELOAD);
			}
		}
	} else if (table_type == COMP_TLB_TABLE_TYPE_DCL1_1_CROSS) {
		if (dnc_id >= HW_SPEC_HALF_DNC_COUNT) {
			if (vpn < 16) {
				pa = spm_base_dcl1 + SZ_2M * vpn;
			} else {
				//RLOG_ERR("%s vpn < 16 but %d\r\n", comp_tlb_table_type_str[table_type], vpn);
				rl_abort_cur_ctx(ERR_TLB_PRELOAD);
			}
		} else {
			//RLOG_ERR("%s support dcl1 only\r\n", comp_tlb_table_type_str[table_type]);
			rl_abort_cur_ctx(ERR_TLB_PRELOAD);
		}
	} else {
		pa = spm_base_dcl0 + SZ_2M * vpn;
	}

	cfg1.general_config_mode_1.queue = COMMON_CMD_TYPE_COMPUTE;
	cfg1.general_config_mode_1.mode = 1; /* General configuration */
	cfg1.general_config_mode_1.sole = 1;
	cfg1.general_config_mode_1.itdone = 1;
	cfg1.general_config_mode_1.auto_fetch_pfix = 0;

	cfg0.general_cofig_mode_1.config_data = pa >> 8;
	cfg1.general_config_mode_1.addr = (UAN + ADDR_OFFSET_DNC_UAN_NC_TLB_0) + (vpn << 2);
	cfg1.general_config_mode_1.data = (SUB_UNIT_ID_ALL << 8 | UNIT_ID_NCLU << 4 | CORE_ID_NC);
	pkt = cfg0.bits | (uint64_t)cfg1.bits << 32;
	DNC_TASK_DESC_CONFIG_WRITE_NORECORD(dnc_id, pkt);

	/* if NCSU access remote SHM, burst length has to be 8 */
	if (dnc_id < HW_SPEC_HALF_DNC_COUNT && (pa >= spm_base_dcl1))
		cfg0.general_cofig_mode_1.config_data |= 0x30;
	else if (dnc_id >= HW_SPEC_HALF_DNC_COUNT && (pa < spm_base_dcl1))
		cfg0.general_cofig_mode_1.config_data |= 0x30;

	cfg1.general_config_mode_1.data = (SUB_UNIT_ID_ALL << 8 | UNIT_ID_NCSU << 4 | CORE_ID_NC);
	pkt = cfg0.bits | (uint64_t)cfg1.bits << 32;
	DNC_TASK_DESC_CONFIG_WRITE_NORECORD(dnc_id, pkt);
}

#define NC_TLB_NUM (((ADDR_OFFSET_DNC_UAN_NC_TLB_63 - ADDR_OFFSET_DNC_UAN_NC_TLB_0) >> 2) + 1)
static inline void dnc_generate_comp_shm_tlb(int dnc_id, int vpn, uint64_t ptaddr,
											 union proc_exec_id *id_info,
											 enum comp_tlb_table_type table_type)
{
#ifdef TEST_MODE_NORMAL_PAGE_TABLE
	union dnc_task_desc_cfg0 cfg0 = {0, };
	union dnc_task_desc_cfg1 cfg1 = {0, };
	uint64_t pkt, ppn;
	uint64_t dcl1_shm_start_ppn = (cl_base[cur_cl_id] + DCL1_SH_MEM_BASE) >> BIT_WIDTH_PAGE;
	int global_vpn = vpn + NC_TLB_NUM * cur_cl_id;

	if (table_type == COMP_TLB_TABLE_TYPE_DCL1_1_CROSS) {
		if (dnc_id >= HW_SPEC_HALF_DNC_COUNT) {
			if (vpn < 48) {
				global_vpn += 16;
			} else {
				//RLOG_ERR("%s vpn < 48 but %d\r\n", comp_tlb_table_type_str[table_type], vpn);
				rl_abort_cur_ctx(ERR_TLB_PRELOAD);
			}
		} else {
			//RLOG_ERR("%s supported from dcl1 only\r\n", comp_tlb_table_type_str[table_type]);
			rl_abort_cur_ctx(ERR_TLB_PRELOAD);
		}
	}

	/* page table based on global VA, so do ptw using that. and primitive use tlb based on local
	 * VA, so when setting tlb entry use local VA.
	 */
	ppn = ptw_vpn_to_ppn((uint32_t)global_vpn, (uint64_t *)ptaddr, id_info).ppn;

	cfg1.general_config_mode_1.queue = COMMON_CMD_TYPE_COMPUTE;
	cfg1.general_config_mode_1.mode = 1; /* General configuration */
	cfg1.general_config_mode_1.sole = 1;
	cfg1.general_config_mode_1.itdone = 1;
	cfg1.general_config_mode_1.auto_fetch_pfix = 0;

	cfg0.general_cofig_mode_1.config_data = ppn << 13;

	cfg1.general_config_mode_1.addr = (UAN + ADDR_OFFSET_DNC_UAN_NC_TLB_0) + (vpn << 2);
	cfg1.general_config_mode_1.data = (SUB_UNIT_ID_ALL << 8 | UNIT_ID_NCLU << 4 | CORE_ID_NC);
	pkt = cfg0.bits | (uint64_t)cfg1.bits << 32;
	DNC_TASK_DESC_CONFIG_WRITE_NORECORD(dnc_id, pkt);

	/* if NCSU access remote SHM, burst length has to be 8 */
	if (dnc_id < HW_SPEC_HALF_DNC_COUNT && (ppn >= dcl1_shm_start_ppn))
		cfg0.general_cofig_mode_1.config_data |= 0x30;
	else if (dnc_id >= HW_SPEC_HALF_DNC_COUNT && (ppn < dcl1_shm_start_ppn))
		cfg0.general_cofig_mode_1.config_data |= 0x30;

	cfg1.general_config_mode_1.data = (SUB_UNIT_ID_ALL << 8 | UNIT_ID_NCSU << 4 | CORE_ID_NC);
	pkt = cfg0.bits | (uint64_t)cfg1.bits << 32;
	DNC_TASK_DESC_CONFIG_WRITE_NORECORD(dnc_id, pkt);
#else
	/* This code is intended to forcibly configure the SHM interleaving mode of
	 * the NC table per chiplet without using a page table preset.
	 */
	uint32_t preset_nc_tlb[32] = {0x1fe40000, 0x1fe60000, 0x1fe42000, 0x1fe62000,
								0x1fe44000, 0x1fe64000, 0x1fe46000, 0x1fe66000,
								0x1fe48000, 0x1fe68000, 0x1fe4a000, 0x1fe6a000,
								0x1fe4c000, 0x1fe6c000, 0x1fe4e000, 0x1fe6e000,
								0x1fe50000, 0x1fe70000, 0x1fe52000, 0x1fe72000,
								0x1fe54000, 0x1fe74000, 0x1fe56000, 0x1fe76000,
								0x1fe58000, 0x1fe78000, 0x1fe5a000, 0x1fe7a000,
								0x1fe5c000, 0x1fe7c000, 0x1fe5e000, 0x1fe7e000};
	union dnc_task_desc_cfg0 cfg0 = {0, };
	union dnc_task_desc_cfg1 cfg1 = {0, };
	uint64_t pkt = 0;

	cfg1.general_config_mode_1.queue = COMMON_CMD_TYPE_COMPUTE;
	cfg1.general_config_mode_1.mode = 1; /* General configuration */
	cfg1.general_config_mode_1.sole = 1;
	cfg1.general_config_mode_1.itdone = 1;
	cfg1.general_config_mode_1.auto_fetch_pfix = 0;

	if (vpn >= 32)
		cfg0.general_cofig_mode_1.config_data = preset_nc_tlb[vpn-32] + (0x20000000 * cur_cl_id);
	else
		rl_abort_cur_ctx(ERR_TLB_PRELOAD);

	cfg1.general_config_mode_1.addr = (UAN + ADDR_OFFSET_DNC_UAN_NC_TLB_0) + (vpn << 2);
	cfg1.general_config_mode_1.data = (SUB_UNIT_ID_ALL << 8 | UNIT_ID_NCLU << 4 | CORE_ID_NC);
	pkt = cfg0.bits | (uint64_t)cfg1.bits << 32;
	DNC_TASK_DESC_CONFIG_WRITE_NORECORD(dnc_id, pkt);

	/* if NCSU access remote SHM, burst length has to be 8 */
	if (dnc_id < HW_SPEC_HALF_DNC_COUNT && (preset_nc_tlb[vpn-32] > 0x1fe5e000))
		cfg0.general_cofig_mode_1.config_data |= 0x30;
	else if (dnc_id >= HW_SPEC_HALF_DNC_COUNT && (preset_nc_tlb[vpn-32] < 0x1fe60000))
		cfg0.general_cofig_mode_1.config_data |= 0x30;

	cfg1.general_config_mode_1.data = (SUB_UNIT_ID_ALL << 8 | UNIT_ID_NCSU << 4 | CORE_ID_NC);
	pkt = cfg0.bits | (uint64_t)cfg1.bits << 32;
	DNC_TASK_DESC_CONFIG_WRITE_NORECORD(dnc_id, pkt);
#endif
}

void dnc_generate_comp_tlb(enum comp_tlb_table_type table_type, uint64_t ptaddr,
						   union proc_exec_id *id_info)
{
	/* vpn of spm and shm */
	int vpn_base;
	int vpn_end_spm, vpn_end_shm;
	uint32_t dnc_id;
	uint32_t dnc_start, dnc_end;

	RLOG_DBG("set comp tlb: tbl_type:%u\r\n", table_type);
//	printf("set comp tlb: tbl_type:%u\r\n", table_type);

	if (table_type == COMP_TLB_TABLE_TYPE_DCL01_2_NORMAL) {
		dnc_start = 0;
		dnc_end = dnc_start + HW_SPEC_DNC_COUNT;
		vpn_end_spm = 32;
		vpn_end_shm = 64;
	} else if (table_type == COMP_TLB_TABLE_TYPE_DCL01_2_CROSS) {
		dnc_start = 0;
		dnc_end = dnc_start + HW_SPEC_DNC_COUNT;
		vpn_end_spm = 16;
		vpn_end_shm = 64;
	} else if (table_type == COMP_TLB_TABLE_TYPE_DCL0_1_NORMAL) {
		dnc_start = 0;
		dnc_end = dnc_start + HW_SPEC_HALF_DNC_COUNT;
		vpn_end_spm = 16;
		vpn_end_shm = 48;
	} else if (table_type == COMP_TLB_TABLE_TYPE_DCL1_1_CROSS) {
		dnc_start = HW_SPEC_HALF_DNC_COUNT;
		dnc_end = dnc_start + HW_SPEC_HALF_DNC_COUNT;
		vpn_end_spm = 16;
		vpn_end_shm = 48;
	} else {
		RLOG_ERR("invalid tbl_type %d\r\n", table_type);
		rl_abort_cur_ctx(ERR_TLB_PRELOAD);
		return;
	}

	for (vpn_base = 0; vpn_base < vpn_end_spm; vpn_base++)
		for (dnc_id = dnc_start; dnc_id < dnc_end; dnc_id++)
			dnc_generate_comp_spm_tlb(dnc_id, vpn_base, table_type);

	for (vpn_base = 32; vpn_base < vpn_end_shm; vpn_base++)
		for (dnc_id = dnc_start; dnc_id < dnc_end; dnc_id++)
			dnc_generate_comp_shm_tlb(dnc_id, vpn_base, ptaddr, id_info, table_type);
}

static void dnc_set_myid(int dnc_id, int target_id)
{
	union dnc_sync_set_my_id my_id;

	my_id.tsync = target_id;
	my_id.isync = target_id;
	my_id.wsync = target_id;

	DNC_SYNC_WRITE(dnc_id, my_id.bits, ADDR_OFFSET_DNC_SYNC_SET_MY_ID);
}

static void dnc_set_tsync_map(uint32_t dnc_id, uint32_t src_id, uint32_t target_id)
{
	assert(src_id % 4 == 0 && target_id % 4 == 0);

	union dnc_sync_tsync_map00 tsync_map;
	uint64_t tsync_map_addr = ADDR_OFFSET_DNC_SYNC_TSYNC_MAP00 + src_id;

	tsync_map.dnc_00 = target_id;
	tsync_map.dnc_01 = target_id + 1;
	tsync_map.dnc_02 = target_id + 2;
	tsync_map.dnc_03 = target_id + 3;

	DNC_SYNC_WRITE(dnc_id, tsync_map.bits, tsync_map_addr);
}

static void dnc_set_isync_map(uint32_t dnc_id, uint32_t src_id, uint32_t target_id)
{
	assert(src_id % 4 == 0 && target_id % 4 == 0);

	union dnc_sync_isync_map00 isync_map;
	uint64_t isync_map_addr = ADDR_OFFSET_DNC_SYNC_ISYNC_MAP00 + src_id;

	isync_map.idx_00 = target_id;
	isync_map.idx_01 = target_id + 1;
	isync_map.idx_02 = target_id + 2;
	isync_map.idx_03 = target_id + 3;

	DNC_SYNC_WRITE(dnc_id, isync_map.bits, isync_map_addr);
}

static void dnc_set_wsync_map(uint32_t dnc_id, uint32_t src_id, uint32_t target_id)
{
	assert(src_id % 4 == 0 && target_id % 4 == 0);

	union dnc_sync_wsync_map00 wsync_map;
	uint64_t wsync_map_addr = ADDR_OFFSET_DNC_SYNC_WSYNC_MAP00 + src_id;

	wsync_map.sig_00 = target_id;
	wsync_map.sig_01 = target_id + 1;
	wsync_map.sig_02 = target_id + 2;
	wsync_map.sig_03 = target_id + 3;

	DNC_SYNC_WRITE(dnc_id, wsync_map.bits, wsync_map_addr);
}


/*
 * static void evt0_dnc_set_wsync_map(uint32_t set_num, uint32_t set_base)
 * {
 *	uint32_t wsync_base = HW_SPEC_DNC_COUNT * cur_cl_id;	// HW_SPEC_DNC_COUNT * 0
 *	//25-0813, for setting local chiplet base
 *	//uint32_t wsync_base = 0;
 *	for (uint32_t i = 0; i < set_num; i++) {
 *		for (uint32_t j = 0; j < set_num; j += 4)
 *			dnc_set_wsync_map(set_base + i, j, wsync_base + set_base + j);
 *	}
 * }
 */

static int dnc_init_pidmap(void)
{
	/* Todo: need to map depending on rsrc->cl_id */

	uint32_t set_num = HW_SPEC_DNC_COUNT;
	uint32_t set_base = 0;
	uint32_t wsync_base = HW_SPEC_DNC_COUNT * cur_cl_id;

	/* clear status registers for dncs to be used now */
	clear_status(set_base, set_num);

	/* set my id */
	for (uint32_t i = 0; i < set_num; i++)
		dnc_set_myid(set_base + i, i);

	/* set id map */
	for (uint32_t i = 0; i < set_num; i++) {
		for (uint32_t j = 0; j < set_num; j += 4) {
			dnc_set_tsync_map(set_base + i, j, set_base + j);
			dnc_set_isync_map(set_base + i, j, set_base + j);
			dnc_set_wsync_map(set_base + i, j, wsync_base + set_base + j);
		}
	}
//	evt0_dnc_set_wsync_map(set_num, set_base);
	return RL_OK;
}

int dnc_init(uint32_t cl_id)
{
	int ret;

	ret = rdsn_init(cl_id);
	if (ret)
		return ret;

	gic_irq_connect(INT_ID_DNC0_EXCEPTION, dnc_0_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC1_EXCEPTION, dnc_1_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC2_EXCEPTION, dnc_2_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC3_EXCEPTION, dnc_3_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC4_EXCEPTION, dnc_4_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC5_EXCEPTION, dnc_5_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC6_EXCEPTION, dnc_6_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC7_EXCEPTION, dnc_7_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC8_EXCEPTION, dnc_8_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC9_EXCEPTION, dnc_9_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC10_EXCEPTION, dnc_10_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC11_EXCEPTION, dnc_11_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC12_EXCEPTION, dnc_12_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC13_EXCEPTION, dnc_13_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC14_EXCEPTION, dnc_14_exception_handler, 0);
	gic_irq_connect(INT_ID_DNC15_EXCEPTION, dnc_15_exception_handler, 0);

	for (int i = 1; i < HW_SPEC_DNC_IRQ_NUM; i++) {
		gic_irq_connect(INT_ID_DNC0_EXCEPTION + i, dnc_0_done_handler, 0);
		gic_irq_connect(INT_ID_DNC1_EXCEPTION + i, dnc_1_done_handler, 0);
		gic_irq_connect(INT_ID_DNC2_EXCEPTION + i, dnc_2_done_handler, 0);
		gic_irq_connect(INT_ID_DNC3_EXCEPTION + i, dnc_3_done_handler, 0);
		gic_irq_connect(INT_ID_DNC4_EXCEPTION + i, dnc_4_done_handler, 0);
		gic_irq_connect(INT_ID_DNC5_EXCEPTION + i, dnc_5_done_handler, 0);
		gic_irq_connect(INT_ID_DNC6_EXCEPTION + i, dnc_6_done_handler, 0);
		gic_irq_connect(INT_ID_DNC7_EXCEPTION + i, dnc_7_done_handler, 0);
		gic_irq_connect(INT_ID_DNC8_EXCEPTION + i, dnc_8_done_handler, 0);
		gic_irq_connect(INT_ID_DNC9_EXCEPTION + i, dnc_9_done_handler, 0);
		gic_irq_connect(INT_ID_DNC10_EXCEPTION + i, dnc_10_done_handler, 0);
		gic_irq_connect(INT_ID_DNC11_EXCEPTION + i, dnc_11_done_handler, 0);
		gic_irq_connect(INT_ID_DNC12_EXCEPTION + i, dnc_12_done_handler, 0);
		gic_irq_connect(INT_ID_DNC13_EXCEPTION + i, dnc_13_done_handler, 0);
		gic_irq_connect(INT_ID_DNC14_EXCEPTION + i, dnc_14_done_handler, 0);
		gic_irq_connect(INT_ID_DNC15_EXCEPTION + i, dnc_15_done_handler, 0);
	}

	for (int i = 0; i < HW_SPEC_DNC_IRQ_NUM; i++) {
		gic_irq_enable_dedicated_core(0, INT_ID_DNC0_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC1_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC2_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC3_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC4_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC5_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC6_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC7_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC8_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC9_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC10_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC11_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC12_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC13_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC14_EXCEPTION + i);
		gic_irq_enable_dedicated_core(0, INT_ID_DNC15_EXCEPTION + i);
	}

	dnc_adjust_base(cl_id);
	dnc_register_ops();

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (dnc_reg_init(i)) {
			RLOG_ERR("dnc %d init failed\r\n", i);
			return RL_ERROR;
		}
	//	printf("[dnc%02d] dnc_reg_init\r\n", i);
		if (dnc_hc(i))
			return RL_ERROR;
#ifdef SECDED_TEST	// trial condition opt
	//just SECDEC error test
	//	apply_multicyle(i);
#endif
	}
#ifdef SECDED_TEST
	//printf("apply_multicyle()\r\n");
#endif
	union proc_exec_id id_info = { .bits = 0 };

#ifdef REBEL_H_EVT1
	dnc_wr_arbitration_config();
#endif

	dnc_init_pidmap();
	dnc_generate_comp_tlb(COMP_TLB_TABLE_TYPE_DCL01_2_NORMAL, page_table_get(), &id_info);

	return RL_OK;
}

static void dnc_print_nc_tlb(int dnc_id)
{
	union dnc_uan_base_unit_info info = { 0, };
	uint64_t uan_base = (uint64_t)dnc_base[dnc_id] + UAN;

	RLOG_DBG("---- DNC %d tlb -----\r\n", dnc_id);
	info.core_id = CORE_ID_NC;
	info.sub_unit_id = SUB_UNIT_ID_ALL;

	info.unit_id = UNIT_ID_NCSU;
	DNC_UAN_WRITE(dnc_id, info.bits, ADDR_OFFSET_DNC_UAN_BASE_UNIT_INFO);
	print_regs("ncsu tlb", uan_base + ADDR_OFFSET_DNC_UAN_NC_TLB_0, 64);

	info.unit_id = UNIT_ID_NCLU;
	DNC_UAN_WRITE(dnc_id, info.bits, ADDR_OFFSET_DNC_UAN_BASE_UNIT_INFO);
	print_regs("nclu tlb", uan_base + ADDR_OFFSET_DNC_UAN_NC_TLB_0, 64);
}

static uint8_t nc_tlb_show(int argc, char *argv[])
{
	int dnc_id = 0;

	if (argc != 1) {
		RLOG_ERR("%s {dnc_id}, show tlb for n-core\r\n", __func__);
		return false;
	}

	dnc_id = atoi(argv[0]);

	dnc_print_nc_tlb(dnc_id);

	return true;
}

// print sync log
static void dnc_print_sync(int dnc_id)
{
#ifndef SORT_MODE
	uint64_t sync_base = (uint64_t)dnc_base[dnc_id] + SYNC;
#endif

	RLOG_DBG("\r\ndnc%02d TSYNC Passage -----\r\n", dnc_id);
#ifndef SORT_MODE
	printf("\r\n[dnc%02d] TSYNC Passage -----", dnc_id);
	print_regs("\r\ntsync_log0", sync_base + ADDR_OFFSET_DNC_SYNC_TSYNC_LOG0, 8);

	RLOG_DBG("dnc%02d PSYNC Passage -----\r\n", dnc_id);
	print_regs("psync_log0", sync_base + ADDR_OFFSET_DNC_SYNC_PSYNC_LOG0, 8);

	RLOG_DBG("dnc%02d Accumulation Counter TSYNC Passage QbyQ -----\r\n", dnc_id);
	print_regs("acc_tsync_passage0", sync_base + ADDR_OFFSET_DNC_SYNC_ACC_TSYNC_PASSAGE0, 1);
	RLOG_DBG("dnc%02d Accumulation Counter TSYNC Passage Token -----\r\n", dnc_id);
	print_regs("acc_tsync_passage1", sync_base + ADDR_OFFSET_DNC_SYNC_ACC_TSYNC_PASSAGE1, 1);

	RLOG_DBG("dnc%02d Accumulation Counter PSYNC Passage Wsync -----\r\n", dnc_id);
	print_regs("acc_psync_passage0", sync_base + ADDR_OFFSET_DNC_SYNC_ACC_PSYNC_PASSAGE0, 1);
	RLOG_DBG("dnc%02d Accumulation Counter PSYNC Passage Isync -----\r\n", dnc_id);
	print_regs("acc_psync_passage1", sync_base + ADDR_OFFSET_DNC_SYNC_ACC_PSYNC_PASSAGE1, 1);
#endif
}

static uint8_t sync_unit_show(int argc, char *argv[])
{
	int dnc_id = 0;

	if (argc != 1) {
		RLOG_ERR("%s {dnc_id}, show sync for dnc\r\n", __func__);
		return false;
	}

	dnc_id = atoi(argv[0]);

	dnc_print_sync(dnc_id);

	return true;
}

static void dnc_print_compute_unit(int dnc_id)
{
	union dnc_uan_base_unit_info info = { 0, };
	uint64_t uan_base = (uint64_t)dnc_base[dnc_id] + UAN;

	RLOG_DBG("\r\n---- DNC%02d NCORE0-----\r\n", dnc_id);
	printf("\r\n---- DNC%02d NCORE0-----\r\n", dnc_id);
	info.core_id = CORE_ID_NCORE0;
	info.sub_unit_id = SUB_UNIT_ID_TU_ROW_IDX;

	info.unit_id = UNIT_ID_TU;
	DNC_UAN_WRITE(dnc_id, info.bits, ADDR_OFFSET_DNC_UAN_BASE_UNIT_INFO);
	print_regs("spr_0123", uan_base + ADDR_OFFSET_DNC_UAN_UNIT_SPR_0123, 1);
	print_regs("jcr", uan_base + ADDR_OFFSET_DNC_UAN_UNIT_JCR_0, 16);

	RLOG_DBG("---- DNC%02d NCORE1-----\r\n", dnc_id);
	printf("---- DNC%02d NCORE1-----\r\n", dnc_id);
	info.core_id = CORE_ID_NCORE1;
	info.sub_unit_id = SUB_UNIT_ID_TU_ROW_IDX;

	info.unit_id = UNIT_ID_TU;
	DNC_UAN_WRITE(dnc_id, info.bits, ADDR_OFFSET_DNC_UAN_BASE_UNIT_INFO);
	print_regs("spr_0123", uan_base + ADDR_OFFSET_DNC_UAN_UNIT_SPR_0123, 1);
	print_regs("jcr", uan_base + ADDR_OFFSET_DNC_UAN_UNIT_JCR_0, 16);
}

static uint8_t comp_unit_show(int argc, char *argv[])
{
	int dnc_id = 0;

	if (argc != 1) {
		RLOG_ERR("%s {dnc_id}\r\n", __func__);
		return false;
	}

	dnc_id = atoi(argv[0]);

	dnc_print_compute_unit(dnc_id);

	return true;
}

void dnc_done_acc_count_all_clear(uint8_t cl_id)
{
//	dnc_adjust_base(cl_id);

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_done_acc_count_clear(i);
}

void dnc_done_acc_count_clear(uint8_t dnc_id)
{
	union dnc_status_trig   status_trig = {0};

	status_trig.clear_status	= 1;
	status_trig.clear_fetch		= 1;
	status_trig.clear_acc		= 1;
	status_trig.clear_fetch_cnt_comp	= 1;
	status_trig.clear_fetch_cnt_ldudma	= 1;
	status_trig.clear_fetch_cnt_lpudma	= 1;
	status_trig.clear_fetch_cnt_studma	= 1;

	DNC_STATUS_WRITE(dnc_id, status_trig.bits, ADDR_OFFSET_DNC_STATUS_TRIG);
	RLOG_INFO("DNC[%02d] done accumulate counter cleared : 0x%x\r\n", dnc_id, status_trig.bits);
}

#ifdef TEST_MODE_NO_TIMEOUT
void dnc_done_accumulate_count(int dnc_id, uint32_t cmd, uint32_t count)
{
	uint32_t	reg2 = 0;
	uint32_t	reg5 = 0;
	uint32_t	reg = 0;
	uint32_t	status = 1;

	switch (cmd) {
	case 0:
		do {
			reg2 = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_COMP_ACC2);
			//reg5 = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_COMP_ACC5);
			reg = reg2;
			if (reg == count)
				status = 0;
		} while (status);
		break;

	case 1:
		do {
			reg2 = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC2);
			reg5 = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC5);
			reg = reg2 + reg5;
			if (reg == count)
				status = 0;
		} while (status);
		break;

	case 2:
		do {
			reg2 = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC2);
			reg5 = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC5);
			reg = reg2 + reg5;
			if (reg == count)
				status = 0;
		} while (status);
		break;

	case 3:
		do {
			reg2 = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_STUDMA_ACC2);
			reg5 = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_STUDMA_ACC5);
			reg = reg2 + reg5;
			if (reg == count)
				status = 0;
		} while (status);
		break;

	default:
		break;
	}
/*
 * if (cmd == 0) {
 *		//RLOG_INFO("DNC[%02d] CMD:[%02x] ACC2#:[%d]\r\n",
 *			dnc_id, cmd, reg2);
 *		printf("DNC[%02d] CMD:[%02x] ACC2#:[%d]\r\n",
 *			dnc_id, cmd, reg2);
 *	} else {
 *		//RLOG_INFO("DNC[%02d] CMD:[%02x] ACC2#:[%d] ACC5#:[%d]\r\n",
 *			 dnc_id, cmd, reg2, reg5);
 *		printf("DNC[%02d] CMD:[%02x] ACC2#:[%d] ACC5#:[%d]\r\n",
 *			dnc_id, cmd, reg2, reg5);
 *	}
 */
}
#else
#define TIMEOUT_THRESHOLD 3000000

void dnc_done_accumulate_count(int dnc_id, uint32_t cmd, uint32_t count)
{
	uint32_t reg2 = 0, reg5 = 0, reg = 0;
	uint32_t	timeout;
	uint32_t	status = 1;

	uint32_t addr_acc2 = 0, addr_acc5 = 0;

	switch (cmd) {
	case 0:
		addr_acc2 = ADDR_OFFSET_DNC_STATUS_COMP_ACC2;
		addr_acc5 = 0;  // comp tlb not use
		break;

	case 1:
		addr_acc2 = ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC2;
		addr_acc5 = ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC5;
		break;

	case 2:
		addr_acc2 = ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC2;
		addr_acc5 = ADDR_OFFSET_DNC_STATUS_LPUDMA_ACC5;
		break;

	case 3:
		addr_acc2 = ADDR_OFFSET_DNC_STATUS_STUDMA_ACC2;
		addr_acc5 = ADDR_OFFSET_DNC_STATUS_STUDMA_ACC5;
		break;

	default:
		RLOG_ERR("DNC[%02d] Invalid CMD:[%02x]\r\n", dnc_id, cmd);
		return;
	}

	timeout	= 0;
	do {
		reg2 = DNC_STATUS_READ(dnc_id, addr_acc2);
		reg5 = (addr_acc5) ? DNC_STATUS_READ(dnc_id, addr_acc5) : 0;
		reg = reg2 + reg5;

		if (reg == count)
			status = 0;

		if (++timeout > TIMEOUT_THRESHOLD) {
			RLOG_ERR("DNC[%02d] CMD:[%02x] Timeout Error! ACC2#:[%d] ACC5#:[%d]\r\n",
				dnc_id, cmd, reg2, reg5);
			// logging status
			if (cmd == COMMON_CMD_TYPE_COMPUTE)
				reg = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_Q_STATUS_COMP);
			else if (cmd == COMMON_CMD_TYPE_UDMA)
				reg = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_Q_STATUS_LDUDMA);
			else if (cmd == COMMON_CMD_TYPE_UDMA_LP)
				reg = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_Q_STATUS_LPUDMA);
			else if (cmd == COMMON_CMD_TYPE_UDMA_ST)
				reg = DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_Q_STATUS_STUDMA);

			RLOG_ERR("%-18s : [dnc%02d][cmd:%x] 0x%08x\r\n", "q_status", dnc_id, cmd, reg);

			return;
		}
		udelay(1);
	} while (status);
}
#endif

static uint8_t sp_all_clear(int argc, char *argv[])
{
	int ret = RL_ERROR;

	// sp clear
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		ret = dnc_run_sp_test(i, 0x0);
		if (ret < 0) {
			RLOG_ERR("sp_clear dnc%02d ERROR IS (%d)\r\n", i, ret);
			printf("sp_clear dnc%02d ERROR IS (%d)\r\n", i, ret);
			return ret;
		}
	}
	RLOG_INFO("\r\nsp_all_clear done\r\n");
	printf("\r\nsp_all_clear done\r\n");

	return true;
}

void dnc_sync_passage_reg_clear(uint8_t dnc_id)
{
	union dnc_sync_trig	sync_trig = {0};

	sync_trig.clr_tsync	= 1;
	sync_trig.clr_psync	= 1;
	sync_trig.clr_passage_log = 1;
	sync_trig.clr_passage_acc = 1;

	DNC_SYNC_WRITE(dnc_id, sync_trig.bits, ADDR_OFFSET_DNC_SYNC_TRIG);
}

static uint8_t sync_passage_all_clear(int argc, char *argv[])
{
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_sync_passage_reg_clear(i);
	RLOG_INFO("\r\nsync_passage_all_clear done\r\n");

	return true;
}

static uint8_t sv_init(int argc, char *argv[])
{
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		if (dnc_hc(i)) {
			printf("%s dnc%02d failed\r\n", __func__, i);
			return false;
		}
	}
	printf("\r\nThe sanity init vector has been completed\r\n");

	return true;
}

uint8_t comp_tlb_interleaving(int argc, char *argv[])
{
	union proc_exec_id id_info = { .bits = 0 };

	dnc_generate_comp_tlb(COMP_TLB_TABLE_TYPE_DCL01_2_NORMAL, page_table_get(), &id_info);
	printf("\r\nThe interleaving comp table has been set\r\n");

	return true;
}

static uint8_t dnc_affinity_mask(int argc, char *argv[])
{
	if (argc != 1) {
		RLOG_ERR("\r\ndnc_affinity_mask {dnc_mask_value}\r\n");
		printf("\r\ndnc_affinity_mask {dnc_mask_value}\r\n");
		return false;
	}
	dnc_affinity = strtol(argv[0], NULL, 16);
	printf("\r\ndnc affinity mask value is [");
	for (int i = 15; i >= 0; i--) {
		printf("%d", (dnc_affinity >> i) & 1);
		if (i % 4 == 0)
			printf(" ");
		printf("]\r\n");
	}
	return true;
}

static uint8_t dnc_cdump_mode_set(int argc, char *argv[])
{
	uint32_t tmp;

	if (argc != 1) {
		RLOG_ERR("\r\ndnc_cdump_mode on|off\r\n");
		printf("\r\ndnc_cdump_mode on|off\r\n");
		return false;
	}
	tmp = strtol(argv[0], NULL, 16);
	if (tmp == 1) {
		dnc_cdump_flag	= tmp;
		printf("\r\ndnc cdump mode is on\r\n");
	} else if (tmp == 0) {
		dnc_cdump_flag	= tmp;
		printf("\r\ndnc cdump mode is off\r\n");
	} else {
		printf("\r\nwrong dnc cdump mode is (%d) ???\r\n", tmp);
	}
	printf("\r\n");

	return true;
}

int dnc_check_slot_mask(int slot)
{
	uint32_t mask = 0;

	if (slot >= 0 && slot < HW_SPEC_DNC_COUNT) {
		mask = 1<<slot;
		if (mask & dnc_affinity)
			return RL_OK;
		return RL_ERROR;
	}
	return RL_ERROR;
}

int dnc_detect_slot(uint64_t address)
{
	uint64_t base1 = cl_base[cur_cl_id] + 0x1FF2000000;
	uint64_t base2 = cl_base[cur_cl_id] + 0x1FF2800000;
	uint64_t offsets[] = {0x0800, 0x2800, 0x4800, 0x6800, 0x8800, 0xA800, 0xC800, 0xE800};
	int slot_mapping[] = {0, 1, 2, 3, 4, 5, 6, 7};
	int slot_mapping2[] = {8, 9, 10, 11, 12, 13, 14, 15};

    // Check dcl0
	/* DCL0 : 0x1ff2000000 ~ 0x1ff200FFFC */
	if (address >= base1 && address < base1 + 0x10000) {
		for (int i = 0; i < 8; i++) {
			//250320, fixed uan address range
			if (address >= base1 + offsets[i] && address <= base1 + offsets[i] + 0x101C)
				return slot_mapping[i];
		}
	}
    // Check dcl1
	/* DCL1 : 0x1ff2800000 ~ 0x1ff280FFFC */
	else if (address >= base2 && address < base2 + 0x10000) {
		for (int i = 0; i < 8; i++) {
			if (address >= base2 + offsets[i] && address <= base2 + offsets[i] + 0x101C)
				return slot_mapping2[i];
		}
	}
	return RL_ERROR; // Not found
}

// dnc x16
void dnc_display_profile(uint8_t dnc_id)
{
	uint8_t	buf[16];
	profile_time_t	info;
	uint64_t profile_addr = (DNC_PROFILE_BASE_ADDR_HIGH<<32) | DNC_PROFILE_BASE_ADDR_LOW;
	uint8_t *dump_ptr = (uint8_t *)(uintptr_t)profile_addr
		+ (uintptr_t)(dnc_id*DNC_PROFILE_MSG_SIZE) + 0x10;
	uint32_t max_entries = DNC_PROFILE_MSG_SIZE / 16;	// Maximum number of 16-byte entries
	uint32_t task_id;

	cpu_inv_dcache_range((uintptr_t)dump_ptr, DNC_PROFILE_MSG_SIZE);

	for (uint32_t offset = 0; offset < max_entries; offset++) {
		uint8_t *current_ptr = dump_ptr + (offset * 16);

		// Check if first 4 bytes (task_id) is non-zero
		task_id = (uint32_t)(current_ptr[0] | (current_ptr[1] << 8) |
					(current_ptr[2] << 16) | (current_ptr[3] << 24));
		if (task_id == 0) {
			// First 4 bytes are 0, no more dump data
			break;
		}

		// Read 16 bytes from current offset
		for (int i = 0; i < 16; i++)
			buf[i] = current_ptr[i];

		info.task_id	= task_id;
	info.queuing_time	= (uint16_t)(buf[4] | buf[5] << 8);

	uint64_t pre_time = (uint64_t)buf[6] | ((uint64_t)buf[7] << 8) |
								((uint64_t)buf[8] << 16) | ((uint64_t)buf[9] << 24) |
								((uint64_t)(buf[10] << 0x0F) << 32);
	info.pre_time = pre_time;

	uint64_t run_time = ((uint64_t)(buf[10] >> 4) & 0x0F) | ((uint64_t)buf[11] << 4) |
		((uint64_t)buf[12] << 12) | ((uint64_t)buf[13] << 20) |
		((uint64_t)buf[14] << 28) | ((uint64_t)buf[15] << 36);

	info.run_time = run_time;
#ifdef DNC_DISPLAY_DEBUG
	printf("* %7d %9x %15d %15d %15d\r\n",
								dnc_id,
								info.task_id,
								info.queuing_time,
									info.pre_time * 16,
									info.run_time * 16);
#endif
		// clear current block
		memset((void *)current_ptr, 0x0, sizeof(uint8_t) * 16);
	}
}

uint8_t dnc_skew_set(int argc, char *argv[])
{
	int cycle = 0;

	if (argc != 1) {
		RLOG_ERR("%s {delay}\r\n * delay value is decimal\r\n", __func__);
		printf("%s {delay}\r\n * delay value is decimal\r\n", __func__);
		printf("delay has 8bit-range\r\n");
		return false;
	}
	cycle = atoi(argv[0]);
	if (cycle > 0xFF) {
		RLOG_ERR("delay range error (%d)\r\n", cycle);
		printf("delay range error (%d)\r\n", cycle);
		return false;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_skew_delay(i, cycle);

	return true;
}

static uint8_t dnc_skew_show(int argc, char *argv[])
{
	union dnc_task_delay	task_delay = {0, };

	printf("\r\ndnc_id\tskew_value\r\n");

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		task_delay.bits = DNC_TASK32_READ(i, ADDR_OFFSET_DNC_DELAY);
		printf("%02d\t%x(%d)\r\n", i, task_delay.dummy, task_delay.dummy);
	}
	return true;
}

static uint8_t ncore_skew_set(int argc, char *argv[])
{
	int cycle = 0;

	if (argc != 1) {
		RLOG_ERR("%s {delay}\r\n * delay value is decimal\r\n", __func__);
		printf("%s {delay}\r\n * delay value is decimal\r\n", __func__);
		printf("delay has 8bit-range\r\n");
		return false;
	}
	cycle = atoi(argv[0]);
	if (cycle > 0xFF) {
		RLOG_ERR("delay range error (%d)\r\n", cycle);
		printf("delay range error (%d)\r\n", cycle);
		return false;
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		ncore_skew_delay(i, cycle);

	return true;
}

static uint8_t ncore_skew_show(int argc, char *argv[])
{
	union dnc_config_sp_pinit_cfg	sp_pinit_cfg = {0, };

	printf("\r\ndnc_id\tncore_skew_value\r\n");

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		sp_pinit_cfg.bits = DNC_CONFIG_READ(i, ADDR_OFFSET_DNC_CONFIG_SP_PINIT_CFG);
		printf("dnc%02d ncore1's\t%x(%d)\r\n", i, sp_pinit_cfg.skew, sp_pinit_cfg.skew);
	}
	return true;
}

#ifdef TEST_MODE_NCORE_SKEW_DELAY
/* compute unit skew XVU,TU */
static void comp_unit_skew_delay(uint8_t dnc_id)
{
	union dnc_uan_base_unit_info info = { 0, };
	uint64_t uan_base = (uint64_t)dnc_base[dnc_id] + UAN;

	RLOG_DBG("---- DNC %d TU config -----\r\n", dnc_id);
	info.core_id = CORE_ID_NCORE1;
	info.unit_id = UNIT_ID_TU;
	info.sub_unit_id = SUB_UNIT_ID_ALL;
	//TU

	RLOG_DBG("---- DNC %d XVU config -----\r\n", dnc_id);
	info.core_id = CORE_ID_NCORE1;
	info.unit_id = UNIT_ID_XVU;
	info.sub_unit_id = SUB_UNIT_ID_ALL;

	RLOG_DBG("---- DNC %d VU config -----\r\n", dnc_id);
	info.core_id = CORE_ID_NCORE1;
	info.unit_id = UNIT_ID_VU;
	info.sub_unit_id = SUB_UNIT_ID_ALL;
	//VU
}
#endif

void pwr_config(uint8_t dnc_id, uint64_t addr, uint32_t data)
{
	struct desc_dnc_task_16B_t		desc;
	uint32_t	pck[4] = {0};
	uint64_t	tmp_addr;

	memset(&desc, 0x0, sizeof(struct desc_dnc_task_16B_t));

	desc.task16b_cmd.type	= (enum task16b_type)PWR;
	desc.task16b_cmd.intr	= 0;
	desc.task16b_cmd.tid	= dnc_id;
	desc.task16b_common.bits	= data;

	tmp_addr = addr>>2;		//4B align
	desc.task16b_addr0.bits	= (uint32_t)tmp_addr & 0xffffffff;
	desc.task16b_addr1.ext	= tmp_addr>>32;
	desc.task16b_addr1.itdone	= 1;

	memcpy(&pck[0], &desc, sizeof(struct desc_dnc_task_16B_t));

	for (int i = 0; i < 4; i++)
		DNC_TASK16_WRITE(dnc_id, pck[i], ADDR_OFFSET_DNC_TASK16B_CMD + i*4);
}

#define PASSAGE_COUNT 8
int posted_write_test(uint32_t cl_id)
{
	union dnc_task16b_en	task_en = {0};
	uint32_t	send_pck = 0xd17c0000;
	uint32_t	rcv_pck[16] = {0xd17c8000, 0xd17c9000, 0xd17ca000, 0xd17cb000,
								0xd17cc000, 0xd17cd000, 0xd17ce000, 0xd17cf000,
								0xd17c0000, 0xd17c1000, 0xd17c2000, 0xd17c3000,
								0xd17c4000, 0xd17c5000, 0xd17c6000, 0xd17c7000};
	uint32_t	reg;

	RLOG_INFO("%s\r\n", "posted_write_test()");

	dnc_adjust_base(cl_id);

	sync_passage_all_clear(0, NULL);

	//enable 16B-Task Path
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		task_en.task16b	= 1;
		DNC_TASK16_WRITE(i, task_en.bits, ADDR_OFFSET_DNC_TASK16B_EN);
	}

	//push
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		for (int cnt = 0; cnt < 8; cnt++) {
			if (i < 8)
				pwr_config(i,
					(uint64_t)(dnc_base[i+8]) + SYNC,
					(send_pck | i<<12 | cnt));
			else
				pwr_config(i,
					(uint64_t)(dnc_base[i-8]) + SYNC,
					(send_pck | i<<12 | cnt));
		}
	}

	udelay(1);

	// check & clear
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		dnc_print_sync(i);

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		reg = DNC_SYNC_READ(i, ADDR_OFFSET_DNC_SYNC_TSYNC_LOG0);
		reg = reg & 0xfffffff0;
		if (reg != rcv_pck[i]) {
			RLOG_INFO("This test has failed. dnc%02d (0x%08x - 0x%08x)\r\n", i, reg, rcv_pck[i]);
			return false;
		}
	}

	//disable 16B-Task Path
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		task_en.task16b	= 0;
		DNC_TASK16_WRITE(i, task_en.bits, ADDR_OFFSET_DNC_TASK16B_EN);
	}

	sync_passage_all_clear(0, NULL);

	return true;
}

void dnc_tlb_update(uint8_t dnc_id, uint8_t tlb_idx, uint8_t cmd, uint64_t addr, uint8_t bl)
{
	union dnc_task_desc_cfg0	desc_cfg0	= {0, };
	union dnc_task_desc_cfg1	desc_cfg1	= {0, };

	desc_cfg0.tlb_setting_mode_2.paddr	= (addr >> 21);	//19
	desc_cfg0.tlb_setting_mode_2.vaddr_l	= (addr >> 21) & 0x1fff;;	//13
	desc_cfg1.tlb_setting_mode_2.vaddr_h	= ((addr >> 21) & 0x7e000)>>13;	//6

	desc_cfg1.tlb_setting_mode_2.tlb_idx	= tlb_idx;	//8
	desc_cfg1.tlb_setting_mode_2.tlb_valid	= 1;	//1
	desc_cfg1.tlb_setting_mode_2.page_size	= 0;	//4
	desc_cfg1.tlb_setting_mode_2.burst_length	= bl;	//2
//	desc_cfg1.tlb_setting_mode_2.tlb_clr_mode	= tlb_cfg->tlb_setting_mode_2.tlb_clr_mode;	//2
//  desc_cfg1.tlb_setting_mode_2.tlb_clr_type	= tlb_cfg->tlb_setting_mode_2.tlb_clr_type;	//1

	desc_cfg1.tlb_setting_mode_2.mode	= 2;	// tlb mode
	desc_cfg1.tlb_setting_mode_2.queue	= cmd;
	desc_cfg1.tlb_setting_mode_2.sole	= 1;	// sole mode
	desc_cfg1.tlb_setting_mode_2.itdone	= 1;

	RLOG_DBG("\r\n[DNC%02d]\r\n", dnc_id);
	RLOG_DBG("%-15s : 0x%08x\r\n", "desc_cfg0", desc_cfg0.bits);
	DNC_TASK32_WRITE(dnc_id, desc_cfg0.bits, ADDR_OFFSET_DNC_TASK_DESC_CFG0, 0);

	RLOG_DBG("%-15s : 0x%08x (bl:%d)\r\n", "desc_cfg1", desc_cfg1.bits, bl);
	DNC_TASK32_WRITE(dnc_id, desc_cfg1.bits, ADDR_OFFSET_DNC_TASK_DESC_CFG1, 0);
}

void generate_udma_task(uint8_t dnc_id, uint8_t cmd, uint64_t src_addr, uint64_t dst_addr, uint32_t trs_size)
{
	struct dnc_reg_task_passage		pck_passage;
	uint64_t tmp_addr;
	uint32_t task_data[8];

	volatile uint32_t __iomem *task_base;

	memset(&pck_passage, 0x0, sizeof(struct dnc_reg_task_passage));

	pck_passage.desc_id.bits = cmd<<16;

	pck_passage.desc_mode.done_rpt	= 1;
	pck_passage.desc_mode.tochk	= 1;

	if (dnc_cdump_flag == 1)
		pck_passage.desc_mode.cdump	= 1;
	else
		pck_passage.desc_mode.cdump	= 0;

	if ((cmd == (enum common_cmd_type)COMMON_CMD_TYPE_UDMA) ||
		(cmd == (enum common_cmd_type)COMMON_CMD_TYPE_UDMA_LP)) {
		pck_passage.desc_prog0.ldudma.csize	= trs_size>>7;        // chunk size
		pck_passage.desc_prog0.ldudma.psize	= 0;    // padding size
		pck_passage.desc_prog0.ldudma.noch	= 1;    // #chunk

		tmp_addr = src_addr>>7;
		pck_passage.desc_prog1.ldudma.src		= (unsigned int)tmp_addr;
		pck_passage.desc_prog2.addr_ext			= (unsigned int)(tmp_addr>>32);
	    pck_passage.desc_prog2.addr_sp			= dst_addr>>7;
	} else if (cmd == (enum common_cmd_type)COMMON_CMD_TYPE_UDMA_ST) {
		pck_passage.desc_prog0.studma.csize	= trs_size>>7;	// chunk size
		pck_passage.desc_prog0.studma.psize	= 0;    // padding size
		pck_passage.desc_prog0.studma.noch	= 1;    // #chunk

		tmp_addr = dst_addr>>7;
		pck_passage.desc_prog1.studma.dst	= (unsigned int)tmp_addr;
		pck_passage.desc_prog2.addr_ext	= (unsigned int)(tmp_addr>>32);
	    pck_passage.desc_prog2.addr_sp	= src_addr>>7;
	}

	/* for quad_replay */
	pck_passage.desc_prog2.tlb_miss_rpt	= 0;

	pck_passage.desc_cfg1.tlb_setting_mode_2.mode	= 0;	//no configure
	pck_passage.desc_cfg1.tlb_setting_mode_2.queue	= cmd;	//cmd
	pck_passage.desc_cfg1.tlb_setting_mode_2.sole	= 0;
	pck_passage.desc_cfg1.tlb_setting_mode_2.itdone	= 1;

	// Prepare all 8 values in array for burst write
	task_data[0] = pck_passage.desc_id.bits;
	task_data[1] = pck_passage.desc_mode.bits;
	task_data[2] = pck_passage.desc_prog0.bits;
	task_data[3] = pck_passage.desc_prog1.bits;
	task_data[4] = pck_passage.desc_prog2.bits;
	task_data[5] = pck_passage.desc_tsync.bits;
	task_data[6] = pck_passage.desc_cfg0.bits;
	task_data[7] = pck_passage.desc_cfg1.bits;

	/*
	 * volatile required for hardware memory-mapped I/O access
	 * Burst write to consecutive addresses for CA73 optimization
	 */
	task_base = (volatile uint32_t __iomem *)(dnc_base[dnc_id] + TASK_32B + ADDR_OFFSET_DNC_TASK_DESC_ID);

	/* evt1 PushIn feature */
//	task_base = (volatile uint32_t __iomem *)(dnc_base[dnc_id] + TASK_32B_ALI0 + ADDR_OFFSET_DNC_TASK_DESC_ID);
//	task_base = (volatile uint32_t __iomem *)(dnc_base[dnc_id] + TASK_32B_ALI1 + ADDR_OFFSET_DNC_TASK_DESC_ID);
//	task_base = (volatile uint32_t __iomem *)(dnc_base[dnc_id] + TASK_32B_ALI2 + ADDR_OFFSET_DNC_TASK_DESC_ID);

	/* Use burst write (stp) for optimal CA73 performance - 32 bytes in 2 instructions */
	rl_write32b_burst(task_data, task_base);

#ifdef TASK_DEBUG
	RLOG_DBG("\r\n[DNC%02d]\r\n", dnc_id);
	RLOG_DBG("%-15s : 0x%08x\r\n", "desc_id", pck_passage.desc_id.bits);
	RLOG_DBG("%-15s : 0x%08x\r\n", "desc_mode", pck_passage.desc_mode.bits);
	RLOG_DBG("%-15s : 0x%08x\r\n", "desc_prog0", pck_passage.desc_prog0.bits);
	RLOG_DBG("%-15s : 0x%08x\r\n", "desc_prog1", pck_passage.desc_prog1.bits);
	RLOG_DBG("%-15s : 0x%08x\r\n", "desc_prog2", pck_passage.desc_prog2.bits);
	RLOG_DBG("%-15s : 0x%08x\r\n", "desc_tsync", pck_passage.desc_tsync.bits);
	RLOG_DBG("%-15s : 0x%08x\r\n", "desc_cfg0", pck_passage.desc_cfg0.bits);
	RLOG_DBG("%-15s : 0x%08x\r\n", "desc_cfg1", pck_passage.desc_cfg1.bits);
#endif
}

void timeout_config(uint8_t dnc_id, uint8_t mode, uint64_t threshold)
{
	union dnc_task_timeout0 timeout0 = {0,};
	union dnc_task_timeout1 timeout1 = {0,};

	timeout0.bits = threshold & 0xffffffff;
	DNC_TASK32_WRITE(dnc_id, timeout0.bits, ADDR_OFFSET_DNC_TASK_TIMEOUT0, 0);
	timeout1.threshold = threshold >> 32;
	timeout1.mode = 1;
	DNC_TASK32_WRITE(dnc_id, timeout1.bits, ADDR_OFFSET_DNC_TASK_TIMEOUT1, 0);

}

void dnc_get_status_registers(void)
{
	char id[10] = {0,};

	RLOG_DBG("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\r\n", "COMMAND", "#TaskEnq", "#TaskDeq", "#TaskDone", "TaskEnq", "TaskRun", "TaskDone");
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		sprintf(id, "COMP_%02d", i);
		RLOG_DBG("%-10s %-10d %-10d %-10d %-10x %-10x %-10x\r\n",
			id,
			DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_COMP_ACC0),
			DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_COMP_ACC1),
			DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_COMP_ACC2),
			DNC_TASK32_READ(i, ADDR_OFFSET_DNC_TASK_ENQ_TASK0),
			DNC_TASK32_READ(i, ADDR_OFFSET_DNC_TASK_RUN_TASK0),
			DNC_TASK32_READ(i, ADDR_OFFSET_DNC_TASK_DONE_TASK0)
		);
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		sprintf(id, "LD_%02d", i);
		RLOG_DBG("%-10s %-10d %-10d %-10d %-10x %-10x %-10x\r\n",
			id,
			DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC0),
			DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC1),
			DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC2),
			DNC_TASK32_READ(i, ADDR_OFFSET_DNC_TASK_ENQ_TASK1),
			DNC_TASK32_READ(i, ADDR_OFFSET_DNC_TASK_RUN_TASK1),
			DNC_TASK32_READ(i, ADDR_OFFSET_DNC_TASK_DONE_TASK1)
		);
	}

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		sprintf(id, "ST_%02d", i);
		RLOG_DBG("%-10s %-10d %-10d %-10d %-10x %-10x %-10x\r\n",
			id,
			DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_STUDMA_ACC1),
			DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_STUDMA_ACC2),
			DNC_TASK32_READ(i, ADDR_OFFSET_DNC_TASK_ENQ_TASK3),
			DNC_TASK32_READ(i, ADDR_OFFSET_DNC_TASK_RUN_TASK3),
			DNC_TASK32_READ(i, ADDR_OFFSET_DNC_TASK_DONE_TASK3)
		);
	}
}

void dnc_comp_rpt_mode_config(int mode)
{
	union dnc_task_comp_rpt_done1 comp_rpt_done = { 0, };

	if (mode == 0x1)
		comp_rpt_done.addr	= 0x1f;

	comp_rpt_done.mode		= mode;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		DNC_TASK32_WRITE(i, comp_rpt_done.bits, ADDR_OFFSET_DNC_TASK_COMP_RPT_DONE1, 0);
}

void dnc_ldudma_rpt_mode_config(int mode)
{
	union dnc_task_ldudma_rpt_done1 ldudma_rpt_done = { 0, };

	if (mode == 0x1)
		ldudma_rpt_done.addr	= 0x1f;

	ldudma_rpt_done.mode		= mode;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++)
		DNC_TASK32_WRITE(i, ldudma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_DONE1, 0);
}

void dnc_rpt_mode_config(int mode)
{
	union dnc_task_comp_rpt_done1 comp_rpt_done = { 0, };
	union dnc_task_ldudma_rpt_done1 ldudma_rpt_done = { 0, };
	union dnc_task_lpudma_rpt_done1 lpudma_rpt_done = { 0, };
	union dnc_task_studma_rpt_done1 studma_rpt_done = { 0, };

	if (mode == 0x1) {
		comp_rpt_done.addr	= 0x1f + (cl_base[cur_cl_id]>>32);
		ldudma_rpt_done.addr	= 0x1f + (cl_base[cur_cl_id]>>32);
		lpudma_rpt_done.addr	= 0x1f + (cl_base[cur_cl_id]>>32);
		studma_rpt_done.addr	= 0x1f + (cl_base[cur_cl_id]>>32);
	}
	comp_rpt_done.mode	= mode;
	ldudma_rpt_done.mode	= mode;
	lpudma_rpt_done.mode	= mode;
	studma_rpt_done.mode	= mode;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		DNC_TASK32_WRITE(i, comp_rpt_done.bits, ADDR_OFFSET_DNC_TASK_COMP_RPT_DONE1, 0);
		DNC_TASK32_WRITE(i, ldudma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_DONE1, 0);
		DNC_TASK32_WRITE(i, lpudma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_LPUDMA_RPT_DONE1, 0);
		DNC_TASK32_WRITE(i, studma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_STUDMA_RPT_DONE1, 0);
	}
}

void dnc_cdump_mode(CdumpInfo_t	cinfo)
{
	union dnc_task_done_cdump_mode	cdump_mode = {0, };
	union dnc_task_done_cdump_size	cdump_size = {0, };
	union dnc_task_done_cdump_dest0	cdump_dest0 = {0, };
	union dnc_task_done_cdump_dest1 cdump_dest1 = {0, };
	union dnc_task_done_cdump_src	cdump_src = {0, };
	union dnc_task_done_cdump_uan	cdump_uan = {0, };
	uint64_t	dest_addr;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		printf("\r\n[DNC%02d]\r\n", i);

		cdump_mode.bits	= DNC_TASK_DONE_READ(i, ADDR_OFFSET_DNC_TASK_DONE_CDUMP_MODE);
		cdump_mode.done_policy	= cinfo.done_policy;
		DNC_TASK_DONE_WRITE(i, cdump_mode.bits, ADDR_OFFSET_DNC_TASK_DONE_CDUMP_MODE);
		printf("%-15s : 0x%08x\r\n", "cdump_mode", cdump_mode.bits);

		cdump_size.dcrn = cinfo.dcrn_size;	//16;	//20-4;  ldudma acc5x4
		cdump_size.uan	= cinfo.uan_size;	//252;	//256-4; tlb 64x4
		DNC_TASK_DONE_WRITE(i, cdump_size.bits, ADDR_OFFSET_DNC_TASK_DONE_CDUMP_SIZE);
		printf("%-15s : 0x%08x\r\n", "cdump_size", cdump_size.bits);

		dest_addr	= cinfo.dest_addr;
//		cdump_dest0.bits = dest_addr & 0xffffffff;	//0x90000000;
		cdump_dest0.bits    = dest_addr & 0xffffffff;
		cdump_dest0.bits	+= i * 0x1000;
		DNC_TASK_DONE_WRITE(i, cdump_dest0.bits, ADDR_OFFSET_DNC_TASK_DONE_CDUMP_DEST0);
		printf("%-15s : 0x%08x\r\n", "cdump_dest0", cdump_dest0.bits);

		cdump_dest1.addr = dest_addr>>32;	//0;
		cdump_dest1.stride = cinfo.stride;	//0;
		DNC_TASK_DONE_WRITE(i, cdump_dest1.bits, ADDR_OFFSET_DNC_TASK_DONE_CDUMP_DEST1);
		printf("%-15s : 0x%08x\r\n", "cdump_dest1", cdump_dest1.bits);

		cdump_src.dcrn	= cinfo.dcrn_offset_addr;	//0x4E0;	//ldudma acc0
		cdump_src.uan	= cinfo.uan_offset_addr;	//0x500;	//nc tlb0
		DNC_TASK_DONE_WRITE(i, cdump_src.bits, ADDR_OFFSET_DNC_TASK_DONE_CDUMP_SRC);
		printf("%-15s : 0x%08x\r\n", "cdump_src", cdump_src.bits);

	//	cdump_uan.nclu	= 1;
	//	cdump_uan.ncsu	= 1;
		cdump_uan.bits	= cinfo.cdump_component;
		DNC_TASK_DONE_WRITE(i, cdump_uan.bits, ADDR_OFFSET_DNC_TASK_DONE_CDUMP_UAN);
		printf("%-15s : 0x%08x\r\n", "cdump_uan", cdump_uan.bits);

	}
}

void generate_udma_task_opt(uint8_t dnc_id, uint8_t cmd, uint64_t src_addr, uint64_t dst_addr, uint32_t trs_size, DescTsyncInfo *tsync_info)
{
	struct dnc_reg_task_passage		pck_passage;
	uint64_t tmp_addr;
	uint32_t task_data[8];
	volatile uint32_t __iomem *task_base;

	memset(&pck_passage, 0x0, sizeof(struct dnc_reg_task_passage));

	pck_passage.desc_id.bits = cmd<<16;

	pck_passage.desc_mode.done_rpt	= 1;
	pck_passage.desc_mode.tochk	= 1;

	if (dnc_cdump_flag == 1)
		pck_passage.desc_mode.cdump	= 1;
	else
		pck_passage.desc_mode.cdump	= 0;

	if( (cmd == (enum common_cmd_type)COMMON_CMD_TYPE_UDMA) || (cmd == (enum common_cmd_type)COMMON_CMD_TYPE_UDMA_LP) ){
        pck_passage.desc_prog0.ldudma.csize     = trs_size>>7;        // chunk size
        pck_passage.desc_prog0.ldudma.psize 	= 0;    // padding size
        pck_passage.desc_prog0.ldudma.noch		= 1;    // #chunk 

		tmp_addr = src_addr>>7;
		pck_passage.desc_prog1.ldudma.src		= (unsigned int)tmp_addr;
		pck_passage.desc_prog2.addr_ext			= (unsigned int)(tmp_addr>>32);
	    pck_passage.desc_prog2.addr_sp			= dst_addr>>7;
	}else if(cmd == (enum common_cmd_type)COMMON_CMD_TYPE_UDMA_ST){
	    pck_passage.desc_prog0.studma.csize     = trs_size>>7;        // chunk size
        pck_passage.desc_prog0.studma.psize 	= 0;    // padding size
        pck_passage.desc_prog0.studma.noch		= 1;    // #chunk 
		
		tmp_addr = dst_addr>>7;
		pck_passage.desc_prog1.studma.dst		= (unsigned int)tmp_addr;
		pck_passage.desc_prog2.addr_ext			= (unsigned int)(tmp_addr>>32);
	    pck_passage.desc_prog2.addr_sp			= src_addr>>7;
	}

	//desc_tsync
	pck_passage.desc_mode.tsync_chk_clr		= tsync_info->tsync_chk_clr;
	pck_passage.desc_mode.tsync_chk 		= tsync_info->tsync_chk_mode;
	pck_passage.desc_mode.tsync_set 		= tsync_info->tsync_set_mode;
	pck_passage.desc_tsync.chk_code 		= tsync_info->tsync_chk_code | (tsync_info->tsync_chk_group<<4);
	pck_passage.desc_tsync.set_code 		= tsync_info->tsync_set_code | (tsync_info->tsync_set_group<<4);
	pck_passage.desc_tsync.set_dest 		= tsync_info->target_dnc_id;

    pck_passage.desc_prog2.tlb_miss_rpt		= 1;

	pck_passage.desc_cfg1.tlb_setting_mode_2.mode 		= 0;	//no configure
	pck_passage.desc_cfg1.tlb_setting_mode_2.queue      = cmd;	//cmd
	pck_passage.desc_cfg1.tlb_setting_mode_2.sole		= 0;
	pck_passage.desc_cfg1.tlb_setting_mode_2.itdone  	= 1;

	// Prepare all 8 values in array for burst write
	task_data[0] = pck_passage.desc_id.bits;
	task_data[1] = pck_passage.desc_mode.bits;
	task_data[2] = pck_passage.desc_prog0.bits;
	task_data[3] = pck_passage.desc_prog1.bits;
	task_data[4] = pck_passage.desc_prog2.bits;
	task_data[5] = pck_passage.desc_tsync.bits;
	task_data[6] = pck_passage.desc_cfg0.bits;
	task_data[7] = pck_passage.desc_cfg1.bits;

	/*
	 * volatile required for hardware memory-mapped I/O access
	 * Burst write to consecutive addresses for CA73 optimization
	 */
	task_base = (volatile uint32_t __iomem *)(dnc_base[dnc_id] + TASK_32B + ADDR_OFFSET_DNC_TASK_DESC_ID);
	/* Use burst write (stp) for optimal CA73 performance - 32 bytes in 2 instructions */
	rl_write32b_burst(task_data, task_base);

#ifdef TASK_DEBUG
	RLOG_INFO("\r\n[DNC%02d]\r\n", dnc_id);
	RLOG_INFO("%-15s : 0x%08x\r\n", "desc_id", pck_passage.desc_id.bits);
	RLOG_INFO("%-15s : 0x%08x\r\n", "desc_mode", pck_passage.desc_mode.bits);
	RLOG_INFO("%-15s : 0x%08x\r\n", "desc_prog0", pck_passage.desc_prog0.bits);
	RLOG_INFO("%-15s : 0x%08x\r\n", "desc_prog1", pck_passage.desc_prog1.bits);
	RLOG_INFO("%-15s : 0x%08x\r\n", "desc_prog2", pck_passage.desc_prog2.bits);
	RLOG_INFO("%-15s : 0x%08x\r\n", "desc_tsync", pck_passage.desc_tsync.bits);
	RLOG_INFO("%-15s : 0x%08x\r\n", "desc_cfg0", pck_passage.desc_cfg0.bits);
	RLOG_INFO("%-15s : 0x%08x\r\n", "desc_cfg1", pck_passage.desc_cfg1.bits);
#endif
}

uint32_t dnc_comp_done_count(int dnc_id){
    return DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_COMP_ACC2);
}
uint32_t dnc_ldudma_done_count(int dnc_id){
    return DNC_STATUS_READ(dnc_id, ADDR_OFFSET_DNC_STATUS_LDUDMA_ACC2);
}

uint32_t dnc_get_q_status()
{
	uint32_t dnc_status = 0;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		dnc_status |= DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_Q_STATUS_COMP);
		dnc_status |= DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_Q_STATUS_LDUDMA);
	}

	return dnc_status;
}
  
/* This function is just Action Item for tracking SECDED Issue */
void apply_multicyle(int dnc_id)
{
	union dnc_config_sp_en		sp_en = {0, };
	union dnc_config_sp_cfg0 	cfg0 = {0, };
	union dnc_config_sp_cfg1 	cfg1 = {0, };

	sp_en.cfg_sp = 1;
	DNC_CONFIG_WRITE(dnc_id, sp_en.bits, ADDR_OFFSET_DNC_CONFIG_SP_EN);	

	cfg0.bits = DNC_CONFIG_READ(dnc_id, ADDR_OFFSET_DNC_CONFIG_SP_CFG0);
	cfg0.sp_cfg0.ba0_mcyc = 0x2;
	cfg0.sp_cfg0.ba1_mcyc = 0x2;
	cfg0.sp_cfg0.ba2_mcyc = 0x2;
	cfg0.sp_cfg0.ba3_mcyc = 0x2;
	DNC_CONFIG_WRITE(dnc_id, cfg0.bits, ADDR_OFFSET_DNC_CONFIG_SP_CFG0);	

	cfg1.bits = DNC_CONFIG_READ(dnc_id, ADDR_OFFSET_DNC_CONFIG_SP_CFG1);
	cfg1.sp_cfg1.ba4_mcyc = 0x2;
	cfg1.sp_cfg1.ba5_mcyc = 0x2;
	cfg1.sp_cfg1.ba6_mcyc = 0x2;
	cfg1.sp_cfg1.ba7_mcyc = 0x2;
	DNC_CONFIG_WRITE(dnc_id, cfg1.bits, ADDR_OFFSET_DNC_CONFIG_SP_CFG1);

	sp_en.cfg_sp = 0;
	DNC_CONFIG_WRITE(dnc_id, sp_en.bits, ADDR_OFFSET_DNC_CONFIG_SP_EN);	
}

void read_secded_status(void)
{
	union dnc_status_sp_status08	sp_status = {0, };

	printf("DNC | CE | UE\r\n");
	printf("-----------------\r\n");
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		sp_status.bits = DNC_STATUS_READ(i, ADDR_OFFSET_DNC_STATUS_SP_STATUS08);
		printf("%02d  | %02d | %02d\r\n", i, sp_status.tot_ce, sp_status.tot_ue);
	}
}

//---------------------------------------------------------------------------------------------
// 25-0728 , test
void measure_backpressue(int dnc_id)
{
	union dnc_task_done_measure0	measure = {0, };

	measure.bits = DNC_TASK_DONE_READ(dnc_id, ADDR_OFFSET_DNC_TASK_DONE_MEASURE0);
	printf("dnc%02d, time:%08x\r\n", dnc_id, measure.bits);
}

void test_cdump_mode(void)
{
	union dnc_task_done_cdump_mode	cdump_mode = {0, };

	printf("\r\n[DNC]\r\n");
	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		cdump_mode.bits 		= DNC_TASK_DONE_READ(i, ADDR_OFFSET_DNC_TASK_DONE_CDUMP_MODE);
		cdump_mode.trigger	= 0x2;
		DNC_TASK_DONE_WRITE(i, cdump_mode.bits, ADDR_OFFSET_DNC_TASK_DONE_CDUMP_MODE);
		printf("%-15s : 0x%08x\r\n", "cdump_mode", cdump_mode.bits);
	}
}
//----------------------------------------------------------------------------------------------

/**
 * @brief Enable or disable DNC autofetch CMGR mode
 * @param mode report mode: 0=report off, 1=mode1, 2=mode2
 */
void dnc_autofetch_cmgr(enum dnc_autofetch_cmgr_mode rpt_mode)
{
	union dnc_task_comp_rpt_done1 comp_rpt_done = {0, };
	union dnc_task_ldudma_rpt_done1 ldudma_rpt_done = {0, };
	union dnc_task_lpudma_rpt_done1 lpudma_rpt_done = {0, };
	union dnc_task_studma_rpt_done1 studma_rpt_done = {0, };

	comp_rpt_done.addr = 0x1f;
	ldudma_rpt_done.addr = 0x1f;
	lpudma_rpt_done.addr = 0x1f;
	studma_rpt_done.addr = 0x1f;

	switch (rpt_mode) {
	case DNC_AUTOFETCH_MODE_REPORT_OFF:
	case DNC_AUTOFETCH_MODE_1:
	case DNC_AUTOFETCH_MODE_2:
		break;
	default:
		RLOG_ERR("%s: invalid rpt_mode(%d), fallback to REPORT_OFF\r\n",
			__func__, (int)rpt_mode);
			rpt_mode = DNC_AUTOFETCH_MODE_REPORT_OFF;
		break;
	}

	comp_rpt_done.mode = (uint32_t)rpt_mode;
	ldudma_rpt_done.mode = (uint32_t)rpt_mode;
	lpudma_rpt_done.mode = (uint32_t)rpt_mode;
	studma_rpt_done.mode = (uint32_t)rpt_mode;

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		DNC_TASK32_WRITE(i, comp_rpt_done.bits, ADDR_OFFSET_DNC_TASK_COMP_RPT_DONE1, 0);
		DNC_TASK32_WRITE(i, ldudma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_LDUDMA_RPT_DONE1, 0);
		DNC_TASK32_WRITE(i, lpudma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_LPUDMA_RPT_DONE1, 0);
		DNC_TASK32_WRITE(i, studma_rpt_done.bits, ADDR_OFFSET_DNC_TASK_STUDMA_RPT_DONE1, 0);
	}
}

void dnc_selffetch_config(enum dnc_autofetch_task_fetch_mode mode, uint8_t cmd_type, uint32_t task_count)
{
	union dnc_task_comp_task_fetch0	comp_task_fetch0 = {0, };
	union dnc_task_comp_task_fetch1	comp_task_fetch1 = {0, };
	union dnc_task_ldudma_task_fetch0 ldudma_task_fetch0 = {0, };
	union dnc_task_ldudma_task_fetch1 ldudma_task_fetch1 = {0, };
	union dnc_task_lpudma_task_fetch0 lpudma_task_fetch0 = {0, };
	union dnc_task_lpudma_task_fetch1 lpudma_task_fetch1 = {0, };
	union dnc_task_studma_task_fetch0 studma_task_fetch0 = {0, };
	union dnc_task_studma_task_fetch1 studma_task_fetch1 = {0, };

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		switch (cmd_type) {
		case COMMON_CMD_TYPE_COMPUTE:
			comp_task_fetch0.bits = (uint32_t)(AF_COMP_BASE_ADDR_CL(cur_cl_id, i) & 0xffffffff);
			comp_task_fetch1.mode = (uint32_t)mode;
			comp_task_fetch1.addr =
				(uint32_t)((AF_COMP_BASE_ADDR_CL(cur_cl_id, i) & 0xff00000000) >> 32);
		#if EVT_VER == 1
			comp_task_fetch1.size = (uint32_t)task_count + 1;
			DNC_TASK32_WRITE(i, comp_task_fetch0.bits, ADDR_OFFSET_DNC_TASK_COMP_TASK_FETCH0, 0);
			DNC_TASK32_WRITE(i, comp_task_fetch1.bits, ADDR_OFFSET_DNC_TASK_COMP_TASK_FETCH1, 0);
		#endif
			break;
		case COMMON_CMD_TYPE_UDMA:
			ldudma_task_fetch0.bits = (uint32_t)(AF_LDUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xffffffff);
			ldudma_task_fetch1.mode = (uint32_t)mode;
			ldudma_task_fetch1.addr =
				(uint32_t)((AF_LDUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xff00000000) >> 32);
		#if EVT_VER == 1
			ldudma_task_fetch1.size = 1; //(uint32_t)task_count + 1;
		#endif
			DNC_TASK32_WRITE(i, ldudma_task_fetch0.bits, ADDR_OFFSET_DNC_TASK_LDUDMA_TASK_FETCH0, 0);
			DNC_TASK32_WRITE(i, ldudma_task_fetch1.bits, ADDR_OFFSET_DNC_TASK_LDUDMA_TASK_FETCH1, 0);
			break;
		case COMMON_CMD_TYPE_UDMA_LP:
			lpudma_task_fetch0.bits = (uint32_t)(AF_LPUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xffffffff);
			lpudma_task_fetch1.mode = (uint32_t)mode;
			lpudma_task_fetch1.addr =
				(uint32_t)((AF_LPUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xff00000000) >> 32);
		#if EVT_VER == 1
			lpudma_task_fetch1.size = 1; //(uint32_t)task_count + 1;
			DNC_TASK32_WRITE(i, lpudma_task_fetch0.bits, ADDR_OFFSET_DNC_TASK_LPUDMA_TASK_FETCH0, 0);
			DNC_TASK32_WRITE(i, lpudma_task_fetch1.bits, ADDR_OFFSET_DNC_TASK_LPUDMA_TASK_FETCH1, 0);
		#endif
			break;
		case COMMON_CMD_TYPE_UDMA_ST:
			studma_task_fetch0.bits = (uint32_t)(AF_STUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xffffffff);
			studma_task_fetch1.mode = (uint32_t)mode;
			studma_task_fetch1.addr =
				(uint32_t)((AF_STUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xff00000000) >> 32);
		#if EVT_VER == 1
			studma_task_fetch1.size = 1; //(uint32_t)task_count + 1;
			DNC_TASK32_WRITE(i, studma_task_fetch0.bits, ADDR_OFFSET_DNC_TASK_STUDMA_TASK_FETCH0, 0);
			DNC_TASK32_WRITE(i, studma_task_fetch1.bits, ADDR_OFFSET_DNC_TASK_STUDMA_TASK_FETCH1, 0);
		#endif
			break;
		}
	}
}

void dnc_autofetch_config(enum dnc_autofetch_task_fetch_mode mode)
{
	union dnc_task_comp_task_fetch0	comp_task_fetch0 = {0, };
	union dnc_task_comp_task_fetch1	comp_task_fetch1 = {0, };
	union dnc_task_ldudma_task_fetch0 ldudma_task_fetch0 = {0, };
	union dnc_task_ldudma_task_fetch1 ldudma_task_fetch1 = {0, };
	union dnc_task_lpudma_task_fetch0 lpudma_task_fetch0 = {0, };
	union dnc_task_lpudma_task_fetch1 lpudma_task_fetch1 = {0, };
	union dnc_task_studma_task_fetch0 studma_task_fetch0 = {0, };
	union dnc_task_studma_task_fetch1 studma_task_fetch1 = {0, };

	for (int i = 0; i < HW_SPEC_DNC_COUNT; i++) {
		comp_task_fetch0.bits = (uint32_t)(AF_COMP_BASE_ADDR_CL(cur_cl_id, i) & 0xffffffff);
		comp_task_fetch1.mode = (uint32_t)mode;
		comp_task_fetch1.addr = (uint32_t)((AF_COMP_BASE_ADDR_CL(cur_cl_id, i) & 0xff00000000) >> 32);

		DNC_TASK32_WRITE(i, comp_task_fetch0.bits, ADDR_OFFSET_DNC_TASK_COMP_TASK_FETCH0, 0);
		DNC_TASK32_WRITE(i, comp_task_fetch1.bits, ADDR_OFFSET_DNC_TASK_COMP_TASK_FETCH1, 0);

		ldudma_task_fetch0.bits = (uint32_t)(AF_LDUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xffffffff);
		ldudma_task_fetch1.mode = (uint32_t)mode;
		ldudma_task_fetch1.addr = (uint32_t)((AF_LDUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xff00000000) >> 32);

		DNC_TASK32_WRITE(i, ldudma_task_fetch0.bits, ADDR_OFFSET_DNC_TASK_LDUDMA_TASK_FETCH0, 0);
		DNC_TASK32_WRITE(i, ldudma_task_fetch1.bits, ADDR_OFFSET_DNC_TASK_LDUDMA_TASK_FETCH1, 0);

		lpudma_task_fetch0.bits = (uint32_t)(AF_LPUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xffffffff);
		lpudma_task_fetch1.mode = (uint32_t)mode;
		lpudma_task_fetch1.addr = (uint32_t)((AF_LPUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xff00000000) >> 32);

		DNC_TASK32_WRITE(i, lpudma_task_fetch0.bits, ADDR_OFFSET_DNC_TASK_LPUDMA_TASK_FETCH0, 0);
		DNC_TASK32_WRITE(i, lpudma_task_fetch1.bits, ADDR_OFFSET_DNC_TASK_LPUDMA_TASK_FETCH1, 0);

		studma_task_fetch0.bits = (uint32_t)(AF_STUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xffffffff);
		studma_task_fetch1.mode = (uint32_t)mode;
		studma_task_fetch1.addr = (uint32_t)((AF_STUDMA_BASE_ADDR_CL(cur_cl_id, i) & 0xff00000000) >> 32);

		DNC_TASK32_WRITE(i, studma_task_fetch0.bits, ADDR_OFFSET_DNC_TASK_STUDMA_TASK_FETCH0, 0);
		DNC_TASK32_WRITE(i, studma_task_fetch1.bits, ADDR_OFFSET_DNC_TASK_STUDMA_TASK_FETCH1, 0);
	}
}

void dnc_autofetch_invoke(int cmd)
{
	struct dnc_reg_task_passage		pck_passage;
	uint32_t task_data[8];

	/*
	 * volatile required for hardware memory-mapped I/O access
	 * checkpatch: ignore volatile warning - hardware register access
	 */

	volatile uint32_t __iomem *task_base;
	int dnc_id;

	memset(&pck_passage, 0x0, sizeof(struct dnc_reg_task_passage));

	pck_passage.desc_prog2.prog_off = 1;

	pck_passage.desc_cfg1.tlb_setting_mode_2.auto_fetch_pfix = 1;
	pck_passage.desc_cfg1.tlb_setting_mode_2.mode = 0;
	pck_passage.desc_cfg1.tlb_setting_mode_2.queue = cmd;
	pck_passage.desc_cfg1.tlb_setting_mode_2.itdone = 1;

	// Prepare all 8 values in array for burst write
	task_data[0] = pck_passage.desc_id.bits;
	task_data[1] = pck_passage.desc_mode.bits;
	task_data[2] = pck_passage.desc_prog0.bits;
	task_data[3] = pck_passage.desc_prog1.bits;
	task_data[4] = pck_passage.desc_prog2.bits;
	task_data[5] = pck_passage.desc_tsync.bits;
	task_data[6] = pck_passage.desc_cfg0.bits;
	task_data[7] = pck_passage.desc_cfg1.bits;

	/*
	 * volatile required for hardware memory-mapped I/O access
	 * Burst write to consecutive addresses for CA73 optimization
	 * checkpatch: ignore volatile warning - hardware register access
	 */
	uint8_t dnc_order[HW_SPEC_DNC_COUNT] = {5, 13, 4, 12, 7, 15, 6, 14, 1, 9, 0, 8, 3, 11, 2, 10};

	for (dnc_id = 0; dnc_id < HW_SPEC_DNC_COUNT; dnc_id++) {
		/* checkpatch: ignore volatile warning - hardware register access */
		task_base = (volatile uint32_t __iomem *)(dnc_base[dnc_order[dnc_id]]
			+ TASK_32B + ADDR_OFFSET_DNC_TASK_DESC_ID);
		/* Use burst write (stp) for optimal CA73 performance - 32 bytes in 2 instructions */
		rl_write32b_burst(task_data, task_base);
	}
}

void dnc_selffetch_invoke(int cmd)
{
#if EVT_VER == 1
	union dnc_task_trig trig = {0, };

	switch (cmd) {
	case COMMON_CMD_TYPE_COMPUTE:
		trig.start_fetch_comp = 1;
		break;
	case COMMON_CMD_TYPE_UDMA:
		trig.start_fetch_ldudma = 1;
		break;
	case COMMON_CMD_TYPE_UDMA_LP:
		trig.start_fetch_lpudma = 1;
		break;
	case COMMON_CMD_TYPE_UDMA_ST:
		trig.start_fetch_studma = 1;
		break;
	default:
		RLOG_ERR("%s: invalid cmd(%d), fallback to COMPUTE\r\n",
			__func__, (int)cmd);
		break;
	}

	for (int dnc_id = 0; dnc_id < HW_SPEC_DNC_COUNT; dnc_id++)
		DNC_TASK32_WRITE(dnc_id, trig.bits, ADDR_OFFSET_DNC_TASK_TRIG, 0);
#endif
}

void preload_comp_task(int iter)
{
	struct dnc_reg_task_passage		pck_passage;
	uint32_t task_data[8];

	memset(&pck_passage, 0x0, sizeof(struct dnc_reg_task_passage));

	pck_passage.desc_id.bits = 0x00041000;	// thread_id =1, cmd_id = 4

	pck_passage.desc_mode.done_rpt = 1;
	pck_passage.desc_mode.tochk = 1;
	pck_passage.desc_prog0.comp.isize = PRELOAD_COMP_TASK_ISIZE >> 7;
	pck_passage.desc_prog1.bits = 0x00000000;	// addr_ext = 0

	pck_passage.desc_prog2.addr_ext = 0x1;
	pck_passage.desc_prog2.addr_sp = 0x3F8000 >> 7;
	pck_passage.desc_prog2.option = 1;
	pck_passage.desc_prog2.tlb_miss_rpt = 1;

	pck_passage.desc_tsync.bits = 0x00000000;
	pck_passage.desc_cfg0.bits = 0x00000000;

	// Common cfg1 settings (only auto_fetch_pfix changes per task)
	pck_passage.desc_cfg1.tlb_setting_mode_2.mode = 0;
	pck_passage.desc_cfg1.tlb_setting_mode_2.queue = COMMON_CMD_TYPE_COMPUTE;
	pck_passage.desc_cfg1.tlb_setting_mode_2.itdone = 1;

	for (int dnc_id = 0; dnc_id < HW_SPEC_DNC_COUNT; dnc_id++) {
		for (int loop = 0; loop < iter; loop++) {
			// Set auto_fetch_pfix: 1 for normal tasks, 0 for EOF task
			pck_passage.desc_cfg1.tlb_setting_mode_2.auto_fetch_pfix = (loop < iter - 1) ? 1 : 0;

			// Prepare task_data
			task_data[0] = pck_passage.desc_id.bits;
			task_data[1] = pck_passage.desc_mode.bits;
			task_data[2] = pck_passage.desc_prog0.bits;
			task_data[3] = pck_passage.desc_prog1.bits;
			task_data[4] = pck_passage.desc_prog2.bits;
			task_data[5] = pck_passage.desc_tsync.bits;
			task_data[6] = pck_passage.desc_cfg0.bits;
			task_data[7] = pck_passage.desc_cfg1.bits;

			// Write to DRAM
			uintptr_t dram_addr = (uintptr_t)AF_COMP_BASE_ADDR_CL(cur_cl_id, dnc_id) +
						loop * 8 * sizeof(uint32_t);

			memcpy((void *)dram_addr, task_data, sizeof(task_data));
			cpu_flush_dcache_range(dram_addr, sizeof(task_data));
		}
	}
}

void dnc_autofetch_addr_reset(void)
{
	union dnc_task_trig trig = {0, };

	trig.reset_fetch_addr_comp = 1;

	for (int dnc_id = 0; dnc_id < HW_SPEC_DNC_COUNT; dnc_id++)
		DNC_TASK32_WRITE(dnc_id, trig.bits, ADDR_OFFSET_DNC_TASK_TRIG, 0);
}

/*
 * The SP bank uses single-port SRAM, so simultaneous rd & wr op are not supported
 * In EVT0, the write-to-read ratio is 2:1, while in EVT1, default setting is 1:1
 * External SP read/write is insist(external)
 * The wr:rd ratio is adjusted to 2:1 at the front end of the SP bank
 * For EVT1, configuration is required to enable SHM read-cache
 */
void dnc_wr_arbitration_config(void)
{
	union dnc_config_sp_en sp_en = {0, };
	uint8_t dnc_id;

	sp_en.cfg_sp = 1;

	for (dnc_id = 0; dnc_id < HW_SPEC_DNC_COUNT; dnc_id++) {
		DNC_CONFIG_WRITE(dnc_id, 0x1, ADDR_OFFSET_DNC_CONFIG_SP_EN);

		DNC_CONFIG_WRITE(dnc_id, 0x51515151, ADDR_OFFSET_DNC_CONFIG_SP_CFG0);
		DNC_CONFIG_WRITE(dnc_id, 0x51515151, ADDR_OFFSET_DNC_CONFIG_SP_CFG1);
		DNC_CONFIG_WRITE(dnc_id, 0x4020A, ADDR_OFFSET_DNC_CONFIG_SP_CFG3);
	}
}

#define TLB_PRESET_TABLE_SIZE 5
#define TLB_PRESET_VALUES_PER_MODE 2

void dnc_tlb_preload(uint8_t dnc_id, uint8_t clr_type, uint32_t value)
{
	union dnc_task_desc_cfg1 desc_cfg1 = { .bits = 0 };
	uint32_t tlb_ctrl;

	tlb_ctrl = value | (cur_cl_id << 6); /* chiplet id [7:6] */
	DNC_CONFIG_WRITE(dnc_id, tlb_ctrl, ADDR_OFFSET_DNC_CONFIG_COMP_TLB1);
	dsb();

	desc_cfg1.tlb_setting_mode_2.sole = 1;
	desc_cfg1.tlb_setting_mode_2.mode = 2;

	desc_cfg1.tlb_setting_mode_2.tlb_valid = 1;
	desc_cfg1.tlb_setting_mode_2.tlb_clr_mode = 1; /* all clear */
	desc_cfg1.tlb_setting_mode_2.tlb_clr_type = clr_type; /* clear type */
	desc_cfg1.tlb_setting_mode_2.queue = COMMON_CMD_TYPE_COMPUTE;
	desc_cfg1.tlb_setting_mode_2.itdone = 1;

	DNC_TASK32_WRITE(dnc_id, desc_cfg1.bits, ADDR_OFFSET_DNC_TASK_DESC_CFG1, 0);
}

static uint8_t dnc_tlb_preset(int argc, char *argv[])
{
	uint32_t preset_table[TLB_PRESET_TABLE_SIZE][TLB_PRESET_VALUES_PER_MODE] = {
		{0x1, 0x21}, /* linear mode */
		{0x1001, 0x1021}, /* interleaving mode */
		{0x201, 0x121}, /* 8dnc linear mode*/
		{0x1201, 0x1121}, /* 8dnc interleaving mode */
		{0xa01, 0x521} /* 8dnc interleaving inverse mode */
	};

	const uint8_t MAX_MODE = TLB_PRESET_TABLE_SIZE - 1;

	if (argc != 1) {
		printf("Usage: %s {mode}\r\n", argv[0]);
		return 0;
	}

	int mode = atoi(argv[0]);

	if (mode < 0 || mode > MAX_MODE) {
		printf("Error: mode must be between 0 and %d\r\n", MAX_MODE);
		return 0;
	}

	for (int dnc_id = 0; dnc_id < HW_SPEC_DNC_COUNT; dnc_id++) {
		uint32_t preset_value = (dnc_id < HW_SPEC_HALF_DNC_COUNT) ?
			preset_table[mode][0] : preset_table[mode][1];
		dnc_tlb_preload(dnc_id, 0x0, preset_value);
	}

	dnc_done_acc_count_all_clear(cur_cl_id);

	return 1;
}

void dnc_update_credit(int dnc_id, uint8_t *comp_credits, uint8_t *udma_credits,
					   uint8_t *lpudma_credits, uint8_t *studma_credits)
{
	union dnc_task_q_credit credit;

	dmb();
	credit.bits = DNC_TASK32_READ(dnc_id, ADDR_OFFSET_DNC_TASK_Q_CREDIT);

	*comp_credits = credit.comp;
	*udma_credits = credit.ldudma;
	*lpudma_credits = credit.lpudma;
	*studma_credits = credit.studma;
}

CLI_REGISTER(nc_tlb_show, NULL, nc_tlb_show, "[nc_tlb_show] {dnc_id}\r\n * show tlb for n-core\r\n\r\n");
CLI_REGISTER(comp_unit_show, NULL, comp_unit_show, "[comp_unit_show] {dnc_id}\r\n * show for compute_unit (SPR, JCR, ...)\r\n\r\n");
CLI_REGISTER(sync_unit_show, NULL, sync_unit_show, "[sync_unit_show] {dnc_id}\r\n * show sync for dnc\r\n\r\n");

CLI_REGISTER(dnc_cdump_mode_set, NULL, dnc_cdump_mode_set, "[dnc_cdump_mode on|off]\r\n * cdump on : 1\r\n * cdump off 0\r\n\r\n");
CLI_REGISTER(dnc_affinity_mask, NULL, dnc_affinity_mask, "[dnc_affinity_mask] {dnc mask value}\r\n * dnc0 only case : dnc_affinity_mask 1\r\n\r\n");
CLI_REGISTER(comp_tlb_interleaving, NULL, comp_tlb_interleaving, "[comp_tlb_interleaving]\r\n * comp tlb interleaving mode\r\n\r\n");
CLI_REGISTER(sv_init, NULL, sv_init, "[sv_init]\r\n * sanity init vector injection\r\n\r\n");
CLI_REGISTER(dnc_skew_set, NULL, dnc_skew_set, "[dnc_skew_set]\r\n * dnc_skew_set\r\n\r\n");
CLI_REGISTER(ncore_skew_set, NULL, ncore_skew_set, "[ncore_skew_set]\r\n * ncore_skew_set\r\n\r\n");

CLI_REGISTER(sp_all_clear, NULL, sp_all_clear, "[sp_all_clear]\r\n * scratch pad memory all clear\r\n\r\n");
CLI_REGISTER(sync_passage_all_clear, NULL, sync_passage_all_clear, "[sync_passage_all_clear]\r\n * sync passage all clear\r\n\r\n");
CLI_REGISTER(dnc_skew_show, NULL, dnc_skew_show, "[dnc_skew_show]\r\n * dnc_skew_show all\r\n\r\n");
CLI_REGISTER(ncore_skew_show,
	NULL, ncore_skew_show,
	"[ncore_skew_show]\r\n * ncore_skew_show all\r\n\r\n");
CLI_REGISTER(dnc_tlb_preset, NULL, dnc_tlb_preset, "[dnc_tlb_preset] {mode}\r\n * dnc_tlb_preset\r\n\r\n");
