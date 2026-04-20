/*
 * Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
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
#include <rebel_h_sic.h>
#include <rebel_h_platform.h>
#include <rl_errors.h>
#include "sic.h"

#define CMRT_SIC_BASE			(0x1E00400000ULL)

#define R_SOC_INTERRUPT_OUT		(0x500UL)

#define R_ESW2HLOS0_D0			(0x600UL)
#define R_ESW2HLOS0_D1			(0x604UL)
#define R_ESW2HLOS0_D2			(0x608UL)
#define R_ESW2HLOS0_D3			(0x60CUL)
#define R_HLOS2ESW0_D0			(0x610UL)
#define R_HLOS2ESW0_D1			(0x614UL)
#define R_HLOS2ESW0_D2			(0x618UL)
#define R_HLOS2ESW0_D3			(0x61CUL)
#define R_HLOS2ESW0_LOCK		(0x620UL)

#define SYS_CM_INTERRUPT		(0x4)

#define SIC_CMD_REQUEST			(0x1)
#define SIC_CMD_RESPONSE		(0x2)
#define SIC_CMD_DATA			(0x3)
#define SIC_CMD_OFFSET			(12)
#define SIC_CMD_MASK			(0x3UL << 12)

#define SMCCC_FAST_CALL			(0x80000000U)
#define SMCCC_SMC64				(0x40000000U)

union sic_head {
	struct {
		uint32_t dest_flow_id : 12;
		uint32_t packet_type : 4;
		uint32_t source_flow_id : 12;
		uint32_t sic_ver : 4;
	};
	uint32_t val;
};

static uint32_t poll_reg_same_val(uint64_t addr, uint32_t val)
{
	volatile uint32_t cur = *(volatile uint32_t *)addr;

	while (cur != val) {
		cur = *(volatile uint32_t *)addr;
	}

	return cur;
}

static uint32_t poll_reg_diff_val(uint64_t addr, uint32_t val)
{
	volatile uint32_t cur = *(volatile uint32_t *)addr;

	while (cur == val) {
		cur = *(volatile uint32_t *)addr;
	}

	return cur;
}

static uint32_t sic_lock_reg(void)
{
	return poll_reg_diff_val(CMRT_SIC_BASE + R_HLOS2ESW0_LOCK, 0);
}

static void sic_clean(void)
{
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_ESW2HLOS0_D0) = 0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_SOC_INTERRUPT_OUT) = 1;
}

#define REBEL_H_SMC_SYS_CM_INTERRUPT  0x82002001
static void sic_send_request(uint32_t sic_id, uint32_t length)
{
	union sic_head head = {
		.dest_flow_id = 0,
		.packet_type = SIC_CMD_REQUEST,
		.source_flow_id = sic_id & 0xfff,
		.sic_ver = 2,
	};

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D1) = length;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D2) = 0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D3) = 0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D0) = head.val;

	struct arm_smccc_res res;

	arm_smccc_smc(REBEL_H_SMC_SYS_CM_INTERRUPT,
				  0, 0, 0, 0,
				  0, 0, 0,
				  &res);

	poll_reg_same_val(CMRT_SIC_BASE + R_HLOS2ESW0_D0, 0);
}

static void sic_send_data(uint32_t sic_id, uint32_t data)
{
	union sic_head head = {
		.dest_flow_id = 0,
		.packet_type = SIC_CMD_DATA,
		.source_flow_id = sic_id & 0xfff,
		.sic_ver = 2,
	};

	poll_reg_same_val(CMRT_SIC_BASE + R_HLOS2ESW0_D0, 0);

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D1) = data;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D2) = 0x0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D3) = 0x0;

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D0) = head.val;

	poll_reg_same_val(CMRT_SIC_BASE + R_HLOS2ESW0_D0, 0);

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D1) = 0x0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D2) = 0x0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D3) = 0x0;

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D0) = head.val;

	poll_reg_same_val(CMRT_SIC_BASE + R_HLOS2ESW0_D0, 0);

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_SOC_INTERRUPT_OUT) = 0;
}

static void sic_release_reg(uint32_t sic_id)
{
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_LOCK) = sic_id;
}

#define RESPONSE_FAIL	(0)
#define RESPONSE_PASS	(1)
static uint32_t handle_request_response(uint32_t expected_value)
{
	poll_reg_diff_val(CMRT_SIC_BASE + R_ESW2HLOS0_D0, 0);

	uint32_t header = *(volatile uint32_t *)(CMRT_SIC_BASE + R_ESW2HLOS0_D0);

	if (((header & SIC_CMD_MASK) >> SIC_CMD_OFFSET) != SIC_CMD_RESPONSE)
		return RESPONSE_FAIL;

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_ESW2HLOS0_D0) = 0x0;
	poll_reg_diff_val(CMRT_SIC_BASE + R_ESW2HLOS0_D0, 0);

	header = *(volatile uint32_t *)(CMRT_SIC_BASE + R_ESW2HLOS0_D0);

	if (((header & SIC_CMD_MASK) >> SIC_CMD_OFFSET) != SIC_CMD_DATA)
		return RESPONSE_FAIL;

	if (*(volatile uint32_t *)(CMRT_SIC_BASE + R_ESW2HLOS0_D2) == expected_value)
		return RESPONSE_PASS;

	return RESPONSE_FAIL;
}

#define CMRT_MW_REQUEST_SIZE	(0x10)
uint32_t request_to_cmrt(uint32_t command)
{
	volatile uint32_t sic_id = sic_lock_reg();

	sic_clean();
	sic_send_request(sic_id, CMRT_MW_REQUEST_SIZE);

	if (command == CMRT_MW_BOOTDONE_CHECK) {
		sic_send_data(sic_id, CMRT_MW_BOOTDONE_CHECK);
	} else if (command == CMRT_MW_LOAD_IMG_FROM_HBM) {
		sic_send_data(sic_id, CMRT_MW_LOAD_IMG_FROM_HBM);
	} else {
		sic_release_reg(sic_id);
		return 0;
	}

	uint32_t result = handle_request_response(command);

	sic_release_reg(sic_id);

	return result;
}
