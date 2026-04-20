/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */
#include <lib/libc/stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <platform_def.h>
#include <common/debug.h>
#include <drivers/hbm3/hbm3_init.h>
#include <drivers/delay_timer.h>
#include "memtest.h"

#define OFFSET_MIN  -50
#define OFFSET_MAX  50
#define OFFSET_FLAG(x) ((x) << 9)

/* VREF Training */
#define VREF_REF_NUM            5
#define PHY_MAX_VREF            0x3f
#define DRAM_MAX_VREF           0x3f
#define VREF_FROM           0
#define VREF_STEP           4
#define MAX_DQ				0x40
#define OFFSET_STEP 4

unsigned int ephy_lock_value(volatile struct hbm3ephy *ephy)
{
	return (ephy->mdll_con1.ctrl_lock_value & 0x3ff);
}

void ephy_dll_off(volatile struct hbm3ephy *ephy)
{
	ephy->mdll_con0.clkm_cg_en_sw = 0x1;

	ephy->cal_con0.cal_vtc_en = 0x0;
}

void set_phy_offsetw(volatile struct hbm3ephy *ephy, int offset)
{
	int flag;

	if (offset < 0) {
		flag = 1;
		offset = offset * (-1);
	} else {
		flag = 0;
	}

	ephy->offsetw_con0.ctrl_offsetw0 = (OFFSET_FLAG(flag) | offset);
	ephy->offsetw_con0.ctrl_offsetw1 = (OFFSET_FLAG(flag) | offset);

	ephy->offsetd_con0.ctrl_resync = 0x1;
	udelay(1);
	ephy->offsetd_con0.ctrl_resync = 0x0;
}

void set_phy_offsetr(volatile struct hbm3ephy *ephy, int offset)
{
	int flag;

	if (offset < 0) {
		flag = 1;
		offset = offset * -1;
	} else {
		flag = 0;
	}

	ephy->offsetr_con0.ctrl_offsetr0 = (OFFSET_FLAG(flag) | offset);
	ephy->offsetr_con0.ctrl_offsetr1 = (OFFSET_FLAG(flag) | offset);

	ephy->offsetd_con0.ctrl_resync = 0x1;
	udelay(1);
	ephy->offsetd_con0.ctrl_resync = 0x0;
}

int vwm_offsetr_looptest_dq(uint32_t chiplet_id, unsigned int ch, volatile struct hbm3ephy *ephy,
							int step, uint64_t addr, size_t size, uint8_t dq)
{
	int offset;

	for (offset = OFFSET_MIN; offset <= OFFSET_MAX; offset += step)	{
		set_phy_offsetr(ephy, offset);

		if (mt_alg_dq_eom(chiplet_id, ch, dq))
			printf("_ ");
		else
			printf("O ");
	}

	set_phy_offsetr(ephy, 0);

	return 0;
}

int vwm_offsetw_looptest_dq(uint32_t chiplet_id, uint32_t ch, volatile struct hbm3ephy *ephy, int step, uint64_t addr,
							size_t size, uint8_t dq)
{
	int offset;

	for (offset = OFFSET_MIN; offset <= OFFSET_MAX; offset += step)	{
		set_phy_offsetw(ephy, offset);

		if (mt_alg_dq_eom(chiplet_id, ch, dq))
			printf("_ ");
		else
			printf("O ");
	}

	set_phy_offsetw(ephy, 0);

	return 0;
}

int vwm_offsetr_looptest(uint32_t chiplet_id, uint32_t ch, volatile struct hbm3ephy *ephy,
						 int step, uint64_t addr, size_t size)
{
	int offset;

	for (offset = OFFSET_MIN; offset <= OFFSET_MAX; offset += step)	{
		set_phy_offsetr(ephy, offset);

		if (mt_alg_channel_eom(chiplet_id, ch))
			printf("_ ");
		else
			printf("O ");
	}

	set_phy_offsetr(ephy, 0);

	return 0;
}

int vwm_offsetw_looptest(uint32_t chiplet_id, uint32_t ch, volatile struct hbm3ephy *ephy,
						 int step, uint64_t addr, size_t size)
{
	int offset;

	for (offset = OFFSET_MIN; offset <= OFFSET_MAX; offset += step)	{
		set_phy_offsetw(ephy, offset);

		if (mt_alg_channel_eom(chiplet_id, ch))
		//if (do_memtest(0x0 + (ch * 0x400), 0x800))
			printf("_ ");
		else
			printf("O ");
	}

	set_phy_offsetw(ephy, 0);

	return 0;
}

unsigned int get_phy_vref(volatile struct hbm3ephy *ephy)
{
	unsigned int vref0 = HBM3_GET_VREF(ephy->io_vref_con1.zq_dword0_vref);
	unsigned int vref1 = HBM3_GET_VREF(ephy->io_vref_con2.zq_dword1_vref);

	printf("get_phy_vref0 : 0x%x\n", vref0);
	printf("get_phy_vref1 : 0x%x\n", vref1);

	return ((vref1 << 6) | vref0);
}

unsigned char get_dram_vref(uint32_t chiplet_id, unsigned int ch)
{
	volatile struct ieee1500_icon *icon = get_hbm_cfg(chiplet_id)->icon_base;
	uint32_t rdata;
	unsigned char vref;

	icon->icon_ctrl_con0.ctrl_wrck_en = 0x1;
	icon->test_instruction_req1.ch_select = ch;

	icon->test_instruction_req0.mr_dump_set_read_req = 0x1;
	udelay(1);

	do {
		rdata = icon->test_instruction_req1.test_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x1);

	icon->test_instruction_req0.mr_dump_set_read_req = 0x0;

	udelay(1);
	do {
		rdata = icon->test_instruction_req1.test_done;
		udelay(1);
	} while ((rdata & 0x1) != 0x0);

	rdata = RD_WDR_CH(icon, 3, ch);

	vref = ((rdata >> 24) & 0x7E) >> 1;
	printf("get_dram_vref : 0x%x\n", vref);

	return vref;
}

void set_phy_vref(volatile struct hbm3ephy *ephy, unsigned int vref0, unsigned int vref1)
{
	ephy->io_vref_con1.zq_dword0_vref = HBM3_SET_VREF(vref0);
	ephy->io_vref_con2.zq_dword1_vref = HBM3_SET_VREF(vref1);
}

void set_dram_vref(volatile struct hbm3ephy *ephy, unsigned char vref)
{
	uint32_t rdata;

	ephy->scheduler_mode.sw_cmd_start = 0x1;
	ephy->scheduler_mode.scheduler_sw_mode = 0x1;
	ephy->scheduler_con5.op_code_apb = vref << 1;
	if (GET_REVISION == REVISION_EVT0)
		ephy->scheduler_con3.evt0_ma_code_apb = 0xf; // MR15
	else
		ephy->scheduler_con3.evt1_ma_code_apb = 0xf; // MR15
	ephy->direct_cmd_con_0.cmd_mrs_req = 0x1;
	udelay(1);
	ephy->direct_cmd_con_0.cmd_mrs_req = 0x0;
	ephy->scheduler_mode.sw_cmd_start = 0x1;

	do {
		rdata = ephy->scheduler_state.schd_fifo_empty_status;
	} while ((rdata & 0x1) != 0x1);

	ephy->scheduler_mode.scheduler_sw_mode = 0x0;
}

void vwm_get_read(uint32_t chiplet_id, uint32_t ch, volatile struct hbm3ephy *ephy,
				  uint64_t addr, size_t size, uint8_t dq)
{
	unsigned int vref;
	unsigned int dword, dword0_vref, dword1_vref;
	unsigned int saved_vref;
	int vref_idx;
	int step = OFFSET_STEP;

	saved_vref = get_phy_vref(ephy);
	dword0_vref = saved_vref & 0x3f;
	dword1_vref = (saved_vref >> 6) & 0x3f;

	if (dq == MAX_DQ) {
		printf("\n\n *** CH[%d] ***\n", ch);
		for (dword = 0; dword < 2; dword++) {
			printf("\n *** dword[%d] ***\n", dword);
			for (vref_idx = PHY_MAX_VREF; vref_idx > 0 ; vref_idx -= VREF_STEP) {
				vref = vref_idx;

				if (dword == 0) {
					set_phy_vref(ephy, vref, dword1_vref);
				} else if (dword == 1) {
					set_phy_vref(ephy, dword0_vref, vref);
				} else { // dword all
					set_phy_vref(ephy, vref, vref);
				}
				printf("vref_0x%02x ", vref);

				vwm_offsetr_looptest(chiplet_id, ch, ephy, step, addr, size);
				printf("\n");
			}
		}
	} else {
		printf("\n\n *** CH[%d]: DQ[%d] ***\n", ch, dq);
		for (vref_idx = PHY_MAX_VREF; vref_idx > 0; vref_idx -= VREF_STEP)	{
			vref = vref_idx;
			set_phy_vref(ephy, vref, vref);

			printf("vref_0x%02x ", vref);

			vwm_offsetr_looptest_dq(chiplet_id, ch, ephy, step, addr, size, dq);
			printf("\n");
		}
	}

	set_phy_vref(ephy, (saved_vref & 0x3F), (saved_vref >> 6) & 0x3F);
	set_phy_offsetr(ephy, 0);

	printf("\n");
}

void vwm_get_write(uint32_t chiplet_id, uint32_t ch, volatile struct hbm3ephy *ephy,
				   uint64_t addr, size_t size, uint8_t dq)
{
	unsigned int vref;
	unsigned char saved_vref;
	int step = OFFSET_STEP;
	int vref_idx;

	saved_vref = get_dram_vref(chiplet_id, ch);

	if (dq == MAX_DQ) {
		printf("\n\n *** CH[%d] ***\n", ch);
		for (vref_idx = DRAM_MAX_VREF; vref_idx > 0; vref_idx -= VREF_STEP) {
			vref = vref_idx;
			set_dram_vref(ephy, vref);

			printf("vref_0x%02x ", vref);

			vwm_offsetw_looptest(chiplet_id, ch, ephy, step, addr, size);
			printf("\n");
		}
	} else {
		printf("\n\n *** CH[%d]: DQ[%d] ***\n", ch, dq);
		for (vref_idx = DRAM_MAX_VREF; vref_idx > 0; vref_idx -= VREF_STEP) {
			vref = vref_idx;
			set_dram_vref(ephy, vref);

			printf("vref_0x%02x ", vref);

			vwm_offsetw_looptest_dq(chiplet_id, ch, ephy, step, addr, size, dq);
			printf("\n");
		}
	}

	set_dram_vref(ephy, saved_vref);
	set_phy_offsetw(ephy, 0);

	printf("\n");
}

void vwm_vref_dqmargin_matrix(uint32_t chiplet_id, uint32_t ch, uint64_t addr, size_t size, uint8_t dq)
{
	if (dq > MAX_DQ) {
		printf("dq out of range\n");
		return;
	}

	volatile struct hbm3ephy *ephy = get_hbm_cfg(chiplet_id)->phy_base[ch];

	printf("ch %d ephy lock value = %d\n", ch, ephy_lock_value(ephy));
	ephy_dll_off(ephy);

	vwm_get_read(chiplet_id, ch, ephy, addr, size, dq);

	vwm_get_write(chiplet_id, ch, ephy, addr, size, dq);

	printf("\nch%d EOM End\n", ch);
}

void run_eom_dq(uint32_t chiplet_id, uint32_t ch)
{
	uint64_t addr = 0x0;
	size_t size = 0;
	uint8_t dq = 0;	// DQ : 0 ~ 63

	mt_alg_pre(chiplet_id, ch);

	for (; dq < MAX_DQ ; dq++) {
		printf("\r\nEOM channel : %u, addr : 0x%lx, size : 0x%lx, dq : %d\r\n", ch, addr, size, dq);

		vwm_vref_dqmargin_matrix(chiplet_id, ch, addr, size, dq);
	}

	mt_alg_post(chiplet_id, ch);
}

void run_eom(uint32_t chiplet_id)
{
	uint32_t ch;
	uint64_t addr = 0x0;
	size_t size = 0;

	for (ch = 0; ch < HBM3_NUM_CH; ch++) {
		printf("\r\nEOM channel : %u, addr : 0x%lx, size : 0x%lx\r\n", ch, addr, size);

		mt_alg_pre(chiplet_id, ch);

		vwm_vref_dqmargin_matrix(chiplet_id, ch, addr, size, MAX_DQ);

		mt_alg_post(chiplet_id, ch);
	}
}
