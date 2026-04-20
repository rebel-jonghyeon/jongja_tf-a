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

#include <assert.h>
#include <errno.h>
#include <string.h>
#include <arch.h>
#include <arch_helpers.h>
#include <common/debug.h>
#include <drivers/synopsys/dw_wdt.h>
#include <lib/utils_def.h>
#include <lib/mmio.h>

/* Control Register */
#define DWWDT_CR				(0x00)
#define CR_WDT_EN				BIT(0)

/* Timeout Range Register */
#define DWWDT_TORR				(0x04)
#define TORR_TIMEOUT_MAX		U(0xF)

/* Current Counter Value Register */
#define DWWDT_CCVR				(0x08)

/* Counter Restart Register */
#define DWWDT_CRR				(0x0C)
#define CRR_CMD_RESTART			(0x76)

static void dw_wdt_enable(dw_wdt_params_t *params)
{
	uint32_t val;

	val = mmio_read_32(params->reg_base + DWWDT_CR);

	mmio_write_32(params->reg_base + DWWDT_CR, val | CR_WDT_EN);
}

static void dw_wdt_set_timeout(dw_wdt_params_t *params)
{
	mmio_write_32(params->reg_base + DWWDT_TORR, TORR_TIMEOUT_MAX);
}

void dw_wdt_init(dw_wdt_params_t *params)
{
	dw_wdt_set_timeout(params);

	dw_wdt_enable(params);
}

void dw_wdt_kick(dw_wdt_params_t *params)
{
	mmio_write_32(params->reg_base + DWWDT_CRR, CRR_CMD_RESTART);
}
