/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2025 [Rebellions Inc.], All Rights Reserved.
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

#include "system_api.h"
#include "hal/shm_if.h"
#include "hal/interrupt.h"
#include "hal/hw_spec.h"
#include "g_sys_addrmap.h"
#include "g_shm_reg.h"
#include "rbln/log.h"
#include "rl_utils.h"
#include "rl_errors.h"
#include "rl_sizes.h"
#include "rbln/rebel.h"
#include "rbln/abort.h"
#include "cpu.h"

#include "common_test.h"	/* test_exception_mark() */

#ifdef DCL_SINGLE
#define SHM_ALL_BITS	0x0000FFFF
#else
#define SHM_ALL_BITS	0xFFFFFFFF
#endif

uint32_t is_tpg_done;

static void __iomem *base[HW_SPEC_SHM_COUNT];

static const uint64_t rdsn_cfg_base[HW_SPEC_SHM_COUNT] = {
	DCL0_SHM0_CFG_BASE,
	DCL0_SHM1_CFG_BASE,
	DCL0_SHM2_CFG_BASE,
	DCL0_SHM3_CFG_BASE,
	DCL0_SHM4_CFG_BASE,
	DCL0_SHM5_CFG_BASE,
	DCL0_SHM6_CFG_BASE,
	DCL0_SHM7_CFG_BASE,
	DCL0_SHM8_CFG_BASE,
	DCL0_SHM9_CFG_BASE,
	DCL0_SHM10_CFG_BASE,
	DCL0_SHM11_CFG_BASE,
	DCL0_SHM12_CFG_BASE,
	DCL0_SHM13_CFG_BASE,
	DCL0_SHM14_CFG_BASE,
	DCL0_SHM15_CFG_BASE,
#ifndef DCL_SINGLE
	DCL1_SHM0_CFG_BASE,
	DCL1_SHM1_CFG_BASE,
	DCL1_SHM2_CFG_BASE,
	DCL1_SHM3_CFG_BASE,
	DCL1_SHM4_CFG_BASE,
	DCL1_SHM5_CFG_BASE,
	DCL1_SHM6_CFG_BASE,
	DCL1_SHM7_CFG_BASE,
	DCL1_SHM8_CFG_BASE,
	DCL1_SHM9_CFG_BASE,
	DCL1_SHM10_CFG_BASE,
	DCL1_SHM11_CFG_BASE,
	DCL1_SHM12_CFG_BASE,
	DCL1_SHM13_CFG_BASE,
	DCL1_SHM14_CFG_BASE,
	DCL1_SHM15_CFG_BASE,
#endif
};

#define SHM_READ(id, offset)		rl_readl_relaxed(base[id] + (offset))
#define SHM_WRITE(id, val, offset)	rl_writel_relaxed(val, base[id] + (offset))

static void shm_adjust_base(uint32_t cl_id)
{
	RLOG_DBG("adjust shm address clid: %d\r\n", cl_id);

	for (int i = 0; i < HW_SPEC_SHM_COUNT; i++) {
		base[i] = (void __iomem *)(cl_base[cl_id] + rdsn_cfg_base[i]);
		RLOG_DBG("shm base[%d] %#lx\r\n", i, base[i]);
	}
}

void shm_randomize_cdp_register(void)
{
	for (int shm_num = 0; shm_num < HW_SPEC_SHM_COUNT; shm_num++)
		for (int i = 0; i < 16; i++)
			SHM_WRITE(shm_num, rand(), 0x7C + 0x4*i); // cdp_burst 0 ~ 15
}

void shm_clear_cdp_register(void)
{
	for (int shm_num = 0; shm_num < HW_SPEC_SHM_COUNT; shm_num++)
		for (int i = 0; i < 16; i++)
			SHM_WRITE(shm_num, 0, 0x7C + 0x4*i); // cdp_burst 0 ~ 15
}

void shm_read_cdp_register(int cl_id)
{
	uint32_t reg = 0;
	uint64_t addr = 0;

	for (int shm_num = 0; shm_num < HW_SPEC_SHM_COUNT; shm_num++) {
		for (int i = 0; i < 16; i++) {
			addr = cl_base[cl_id] + rdsn_cfg_base[shm_num] + 0x7C + 0x4*i;
			reg = rl_readl_relaxed((void *)addr);
		}
	}
}

int shm_check_cdp_register_clear(int cl_id)
{
	uint32_t reg = 0;
	uint64_t addr = 0;

	for (int shm_num = 0; shm_num < HW_SPEC_SHM_COUNT; shm_num++) {
		for (int i = 0; i < 16; i++) {
			addr = cl_base[cl_id] + rdsn_cfg_base[shm_num] + 0x7C + 0x4*i;
			reg = rl_readl_relaxed((void *)addr);
			if (reg != 0)
				return -1;
		}
	}
	return 0;
}

static void shm_info_handler(void *data)
{
	uint32_t id = (uint64_t)data;
	union shm_reg_intr_vec intr_vec;
	union shm_reg_clear clear = { 0, };

	RLOG_DBG("info_handler shm id %u\r\n", id);
	intr_vec.bits = SHM_READ(id, ADDR_OFFSET_SHM_REG_INTR_VEC);

	if (intr_vec.tpg_done) {
		RLOG_DBG("shm%d tpg done\r\n", id);
		RL_SET_BIT(is_tpg_done, id);
	}

	clear.intr_clear = 1;
	clear.tpg = 1;
	SHM_WRITE(id, clear.bits, ADDR_OFFSET_SHM_REG_CLEAR);

	SHM_WRITE(id, 0, ADDR_OFFSET_SHM_REG_ENAB_0);
}

#define SHM_TPG_DONE_INTERVAL_US	1
int wait_for_shm_tpg_done(unsigned long timeout_us)
{
	unsigned long timeout_cnt = timeout_us / SHM_TPG_DONE_INTERVAL_US;

	while (is_tpg_done != SHM_ALL_BITS) {
		udelay(SHM_TPG_DONE_INTERVAL_US);
		if (--timeout_cnt == 0) {
			RLOG_ERR("timeout: waiting for shm tpg done\r\n");
			return RL_TIMEOUT;
		}
	}

	RLOG_DBG("shm tpg is done(zero init)\r\n");
	return RL_OK;
}

int shm_test_mode_trigger(void)
{
	union shm_reg_trig trig = { 0, };
	union shm_reg_enab_0 enab_0 = { 0, };

	for (int i = 0; i < HW_SPEC_SHM_COUNT; i++) {
		enab_0.tpg = 1;
		SHM_WRITE(i, enab_0.bits, ADDR_OFFSET_SHM_REG_ENAB_0);
		dsb();

		trig.tpg_all = 1;
		SHM_WRITE(i, trig.bits, ADDR_OFFSET_SHM_REG_TRIG);
		dsb();
	}

	return RL_OK;
}

//------------------------------------------------------------------------------------------
// This function is intended to verify the interrupt behavior of the sglue error interrupt.
//------------------------------------------------------------------------------------------
static void shm_exception_handler(void *data)
{
	uint32_t id = (uint64_t)data;
	union shm_reg_intr_vec intr_vec;
	union shm_reg_clear clear = { 0, };

	RLOG_DBG("%s shm id %u\r\n", __func__, id);
	intr_vec.bits = SHM_READ(id, ADDR_OFFSET_SHM_REG_INTR_VEC);

	if (intr_vec.intr_serr) {
		RLOG_DBG("shm%d syndrome error\r\n", id);
		printf("shm%d syndrome error\r\n", id);
		clear.eij = 1;	// ecc error injection clear
		clear.eca = 1;	// ecc alert counter clear
//		clear.intr_clear = 1;
		SHM_WRITE(id, clear.bits, ADDR_OFFSET_SHM_REG_CLEAR);
	}
}

static void shm_error_handler(void *data)
{
	uint32_t id = (uint64_t)data;
	union shm_reg_intr_vec intr_vec;
	union shm_reg_clear clear = { 0, };

#if defined(INDICATOR_DEBUG_MODE)
	TEST_GPD2_DAT |= 0x1;	// trigger GPD2[0]
#endif /* #if defined(INDICATOR_DEBUG_MODE) */

	printf("%s addr=0x%lx\r\n", "shm_error_handler", base[0]);
	intr_vec.bits = SHM_READ(id, ADDR_OFFSET_SHM_REG_INTR_VEC);
	RLOG_ERR("shm%d val=0x%08x\r\n", id, intr_vec.bits);
	printf("shm%d val=0x%08x\r\n", id, intr_vec.bits);
	dsb();

	//25-0729 , test
	if (intr_vec.intr_serr) {
		test_exception_mark();
		RLOG_ERR("[FAIL]shm%d single error detected\r\n", id);
		printf("[FAIL]shm%d single error detected\r\n", id);
	}
	dsb();

	if (intr_vec.intr_derr) {
		test_exception_mark();
		RLOG_ERR("[FAIL]shm%d double error detected\r\n", id);
		printf("[FAIL]shm%d double error detected\r\n", id);
	}
	dsb();

	if (intr_vec.intr_wstt) {
		test_exception_mark();
		RLOG_ERR("[FAIL]shm%d wstt error detected\r\n", id);
		printf("[FAIL]shm%d wstt error detected\r\n", id);
	}
	dsb();

	if (intr_vec.intr_rstt) {
		test_exception_mark();
		RLOG_ERR("[FAIL]shm%d rstt error detected\r\n", id);
		printf("[FAIL]shm%d rstt error detected\r\n", id);
	}
	dsb();

	if (intr_vec.intr_malf) {
		test_exception_mark();
		RLOG_ERR("[FAIL]shm%d malf error detected\r\n", id);
		printf("[FAIL]shm%d malf error detected\r\n", id);
	}
	dsb();

	clear.intr_clear = 1;
	clear.eca = 1;
	clear.tot = 1;
	SHM_WRITE(id, clear.bits, ADDR_OFFSET_SHM_REG_CLEAR);
	dsb();

	/* CE(serr)/UE(derr): flag only, no abort.
	 * Non-CE/UE (wstt/rstt/malf): abort
	 */
	if (intr_vec.intr_wstt || intr_vec.intr_rstt || intr_vec.intr_malf)
		rl_abort_event(ERR_SHM);
}

#ifdef SHM_ENABLED
#ifdef ZEBU
#define SHM_TPG_TIMEOUT_US		100000000 /* 100s */
#else
#define SHM_TPG_TIMEOUT_US		1000000 /* 1s */
#endif
int shm_zero_init(uint32_t cl_id)
{
	union shm_reg_trig trig = { 0, };
	union shm_reg_enab_0 enab_0 = { 0, };
	int i, ret;

	shm_adjust_base(cl_id);

	/* SHM zero initialization */
	for (i = 0; i < HW_SPEC_SHM_COUNT; i++) {
		enab_0.tpg = 1;
		SHM_WRITE(i, enab_0.bits, ADDR_OFFSET_SHM_REG_ENAB_0);
		dsb();

		trig.tpg_all = 1;
		SHM_WRITE(i, trig.bits, ADDR_OFFSET_SHM_REG_TRIG);
		dsb();

		//250724 for test
		//SHM_WRITE(i, 0x1e030000, ADDR_OFFSET_SHM_REG_AXI_PORT);	//aruser[0] off
	}

	ret = wait_for_shm_tpg_done(SHM_TPG_TIMEOUT_US);
	if (ret) {
		rl_abort_event(ERR_SHM);
		is_tpg_done = 0;
		return ret;
	}
	return 0;
}

int shm_init(uint32_t cl_id)
{
	const int shm_half_cnt = HW_SPEC_SHM_COUNT / 2;
	int i, ret;

	shm_adjust_base(cl_id);

	is_tpg_done = 0x0;
	RLOG_INFO("shm init start status(%08x)\r\n", is_tpg_done);

#ifdef DCL_SINGLE
	for (i = 0; i < HW_SPEC_SHM_COUNT; i++) {
		gic_irq_connect(INT_ID_SHM0_INFORMATIONAL + i * 2, shm_info_handler, (void *)(uint64_t)i);
		gic_irq_enable_dedicated_core(0, INT_ID_SHM0_INFORMATIONAL + i * 2);
	}
#else
	for (i = 0; i < HW_SPEC_SHM_COUNT >> 1; i++) {
		gic_irq_connect(INT_ID_SHM0_INFORMATIONAL + i * 2, shm_info_handler, (void *)(uint64_t)i);
		gic_irq_enable_dedicated_core(0, INT_ID_SHM0_INFORMATIONAL + i * 2);
	}

	for (i = 0; i < HW_SPEC_SHM_COUNT >> 1; i++) {
		gic_irq_connect(INT_ID_SHM16_INFORMATIONAL + i * 2, shm_info_handler, (void *)(uint64_t)((HW_SPEC_SHM_COUNT >> 1) + i));
		gic_irq_enable_dedicated_core(0, INT_ID_SHM16_INFORMATIONAL + i * 2);
	}
#endif

//250724,
#ifdef DCL_SINGLE
	for (i = 0; i < HW_SPEC_SHM_COUNT; i++) {
		gic_irq_connect(INT_ID_SHM0_EXCEPTION + i * 2, shm_error_handler, (void *)(uint64_t)i);
		gic_irq_enable_dedicated_core(0, INT_ID_SHM0_EXCEPTION + i * 2);
	}
#else
	for (i = 0; i < shm_half_cnt; i++) {
		gic_irq_connect(INT_ID_SHM0_EXCEPTION + i * 2, shm_error_handler, (void *)(uint64_t)i);
		gic_irq_enable_dedicated_core(0, INT_ID_SHM0_EXCEPTION + i * 2);
	}

	for (i = 0; i < shm_half_cnt; i++) {
		gic_irq_connect(INT_ID_SHM16_EXCEPTION + i * 2, shm_error_handler, (void *)(uint64_t)(shm_half_cnt + i));
		gic_irq_enable_dedicated_core(0, INT_ID_SHM16_EXCEPTION + i * 2);
	}
#endif

	ret = shm_zero_init(cl_id);
	if (ret) {
		rl_abort_event(ERR_SHM);
		is_tpg_done = 0;
		return ret;
	}

	RLOG_INFO("shm init end status(%08x)\r\n", is_tpg_done);
	is_tpg_done = 0;

	return RL_OK;
}
#else
int shm_zero_init(uint32_t cl_id) { }
int shm_init(uint32_t cl_id) { }
#endif

int shm_exception_register(uint32_t cl_id)
{
	union shm_reg_enab_0 enab_0 = {0};
	union shm_reg_enab_1 enab_1 = {0};
	union shm_reg_trig trig = {0};
	int ret;
	int i;

	shm_adjust_base(cl_id);

	for (i = 0; i < HW_SPEC_SHM_COUNT; i++) {
		enab_1.bits = SHM_READ(i, ADDR_OFFSET_SHM_REG_ENAB_1);
		enab_1.ecc = 1;	// ecc enable
		enab_1.eca = 1; // ecc alert enable
		SHM_WRITE(i, enab_1.bits, ADDR_OFFSET_SHM_REG_ENAB_1);
	}

	for (i = 0; i < HW_SPEC_SHM_COUNT; i++) {
		enab_0.tpg = 1;
		enab_0.eij = 1;	// ecc error injection
		SHM_WRITE(i, enab_0.bits, ADDR_OFFSET_SHM_REG_ENAB_0);

		SHM_WRITE(i, 0x12010003, ADDR_OFFSET_SHM_REG_FCONF);	// EIJ, 01, error :[1]syndrome, [2]message

		trig.bits = 0;
		trig.tpg = 1;
		SHM_WRITE(i, trig.bits, ADDR_OFFSET_SHM_REG_TRIG);
	}

	ret = wait_for_shm_tpg_done(SHM_TPG_TIMEOUT_US);
	if (ret) {
		rl_abort_event(ERR_SHM);
		is_tpg_done = 0;
		return ret;
	}

	printf("shm init end status(%08x)\r\n", is_tpg_done);
	is_tpg_done = 0;

	return RL_OK;
}
//-------------------------------------------------------------------------------------------------------------

static int shm_check_args(uint64_t shm_addr, uint32_t shm_offset, uint32_t size)
{
	if ((shm_offset + size) > RL_SHM_SIZE) {
		RLOG_ERR("copy region is outside SHM(shm offset: %#x, size: %#x)\r\n", shm_offset, size);
		return RL_BADARG;
	}

	if (!IS_ALIGNED(shm_addr, SZ_128) || !IS_ALIGNED(size, SZ_128)) {
		RLOG_ERR("Not aligned in 128B(shm addr: %#lx, size: %#x)\r\n", shm_addr, size);
		return RL_BADARG;
	}

	return RL_OK;
}

int shm_read(uint32_t shm_offset, void *dst_addr, uint32_t size)
{
	uint64_t shm_addr = DCL0_SH_MEM_BASE + shm_offset;
	int ret;

	ret = shm_check_args(shm_addr, shm_offset, size);
	if (ret)
		return ret;

	memcpy(dst_addr, (void *)shm_addr, size);
	return RL_OK;
}

int shm_write(uint32_t shm_offset, void *src_addr, uint32_t size)
{
	uint64_t shm_addr = DCL0_SH_MEM_BASE + shm_offset;
	int ret;

	ret = shm_check_args(shm_addr, shm_offset, size);
	if (ret)
		return ret;

	memcpy((void *)shm_addr, src_addr, size);
	return RL_OK;
}

int shm_override_reset_value(uint32_t cl_id)
{
	uint64_t sglue_cfg_base;

	sglue_cfg_base = cl_base[cl_id] + DCL0_SGLUE_CFG_BASE;
	/* Write 0x0 to SGLUE_CFG_BASE + 0x20 */
	rl_writel_relaxed(0x0, (void __iomem *)(sglue_cfg_base + 0x20));
	dsb();

	sglue_cfg_base = cl_base[cl_id] + DCL1_SGLUE_CFG_BASE;
	/* Write 0x0 to SGLUE_CFG_BASE + 0x20 */
	rl_writel_relaxed(0x0, (void __iomem *)(sglue_cfg_base + 0x20));
	dsb();

	return RL_OK;
}
