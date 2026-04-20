/*
 * Copyright 2025 Samsung Electronics Co, Ltd. All Rights Reserved.
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
#include <interrupt.h>
#include <driver.h>
#include <rebel_h_platform.h>
#include "noc_logger.h"

static const char * const flexnoc_error_opcodes[] = {
	[0] = "RD",
	[1] = "RDW",
	[2] = "RDL",
	[3] = "RDX",
	[4] = "WR",
	[5] = "WRW",
	[6] = "WRC",
	[7] = "Reserved",
	[8] = "PRE",
	[9] = "URG",
};

static const char * const flexnoc_error_errcodes[] = {
	[0] = "SLV",
	[1] = "DEC",
	[2] = "UNS",
	[3] = "DISC",
	[4] = "SEC",
	[5] = "HIDE",
	[6] = "TMO",
	[7] = "RSV",
};

struct flexnoc {
	uintptr_t base;		/* Base address */
	const char *name;
	const char *grp;	/* Group information based on BUS implementation */
	uint32_t irq_num;	/* INTID */
};

static struct flexnoc flexnoc_rebelh[] = {
	{NOC_PCIE_DBG,		"NOC_PCIE_DBG",		"6) PCIE Bus",			198},
	{NOC_SHBUS_EU_R,	"NOC_SHBUS_EU_R",	"3) SHM Bus Read",		668},
	{NOC_SHBUS_EU_W,	"NOC_SHBUS_EU_W",	"4) SHM Bus Write",		669},
	{NOC_C_EBUS_U_DBG,	"NOC_C_EBUS_U_DBG",	"5) Control Bus",		677},
	{NOC_C_EBUS_D_DBG,	"NOC_C_EBUS_D_DBG", "5) Control Bus",		689},
	{NOC_SHBUS_ED_R,	"NOC_SHBUS_ED_R",	"3) SHM Bus Read",		704},
	{NOC_SHBUS_ED_W,	"NOC_SHBUS_ED_W",	"4) SHM Bus Write",		705},
	{NOC_D_EBUS_D_R,	"NOC_D_EBUS_D_R",	"1) Main Bus Read",		712},
	{NOC_D_EBUS_D_W,	"NOC_D_EBUS_D_W",	"2) Main Bus Write",	713},
	{NOC_C_EBUS_R_DBG,	"NOC_C_EBUS_R_DBG",	"5) Control Bus",		738},
	{NOC_D_EBUS_R_R,	"NOC_D_EBUS_R_R",	"1) Main Bus Read",		739},
	{NOC_D_EBUS_R_W,	"NOC_D_EBUS_R_W",	"2) Main Bus Write",	740},
	{NOC_D_WBUS_U_R,	"NOC_D_WBUS_U_R",	"1) Main Bus Read",		776},
	{NOC_D_WBUS_U_W,	"NOC_D_WBUS_U_W",	"2) Main Bus Write",	777},
	{NOC_DBUS_SBUS_U_R,	"NOC_DBUS_SBUS_U_R", "1) Main Bus Read",	813},
	{NOC_DBUS_SBUS_U_W,	"NOC_DBUS_SBUS_U_W", "2) Main Bus Write",	815},
	{NOC_C_SBUS_D_DBG,	"NOC_C_SBUS_D_DBG",	"5) Control Bus",		832},
	{NOC_D_NBUS_U_R,	"NOC_D_NBUS_U_R",	"1) Main Bus Read",		900},
	{NOC_D_NBUS_U_W,	"NOC_D_NBUS_U_W",	"2) Main Bus Write",	908},
	{NOC_C_NBUS_U_DBG,	"NOC_C_NBUS_U_DBG",	"5) Control Bus",		909},
	{NOC_D_NBUS_D_W,	"NOC_D_NBUS_D_W",	"2) Main Bus Write",	931},
	{NOC_D_NBUS_D_R,	"NOC_D_NBUS_D_R",	"1) Main Bus Read",		939},
	{NOC_C_NBUS_L_DBG,	"NOC_C_NBUS_L_DBG",	"5) Control Bus",		979},
	{NOC_C_NBUS_D_DBG,	"NOC_C_NBUS_D_DBG",	"5) Control Bus",		936},
};

static void noc_logger_enable(struct noc_logger *nl)
{
	nl->faulten.faulten = 1;
}

static void noc_logger_irq_handler(void *data)
{
	volatile struct flexnoc *fn = (struct flexnoc *)data;
	volatile struct noc_logger *nl = (struct noc_logger *)(fn->base);

	if (!nl->errvld.errvld)
		return;

	printf("\nNOC Error detected: %s, irq: %d\n", fn->name, fn->irq_num);

	printf("ErrLog raw data\n");
	printf("  Group: %s\n", fn->grp);
	printf("  ErrLog0: 0x%08lx\n", nl->errlog0.val);
	printf("  ErrLog1: 0x%08lx\n", nl->errlog1.val);
	printf("  ErrLog3: 0x%08lx\n", nl->errlog3.val);
	printf("  ErrLog4: 0x%08lx\n", nl->errlog4.val);
	printf("  ErrLog5: 0x%08lx\n", nl->errlog5.val);
	printf("  ErrLog6: 0x%08lx\n", nl->errlog6.val);

	printf("\nErrLog0 data\n");
	printf("  lock   : %s (0x%lx)\n", nl->errlog0.lock ? "LOCK" : "NOLOCK", nl->errlog0.lock);
	printf("  opcode : %s (0x%lx)\n", flexnoc_error_opcodes[nl->errlog0.opc], nl->errlog0.opc);
	printf("  errcode: %s (0x%lx)\n", flexnoc_error_errcodes[nl->errlog0.errcode],
		   nl->errlog0.errcode);
	printf("  length : %d Bytes\n", nl->errlog0.len1 + 1);

	nl->errclr.errclr = 1;
}

int noc_logger_init(void)
{
	uint32_t rev = GET_REVISION;
	uint32_t chiplet_id = CHIPLET_ID;

	for (uint32_t i = 0; i < sizeof(flexnoc_rebelh) / sizeof(struct flexnoc); i++) {

		struct flexnoc *fn = &flexnoc_rebelh[i];

		/* For PCIe block, only EVT0 & CHIPLET0 and EVT1 & CHIPLET0/3 available */
		if (fn->base == NOC_PCIE_DBG &&
			((rev == REVISION_EVT0 && chiplet_id != CHIPLET_ID0) ||
			(rev == REVISION_EVT1 && (chiplet_id != CHIPLET_ID0 && chiplet_id != CHIPLET_ID3))
			))
			continue;

		struct noc_logger *nl = (struct noc_logger *)(fn->base);

		connect_interrupt_with_handler(fn->irq_num, 2, IRQ_TYPE_LEVEL, noc_logger_irq_handler, fn);

		noc_logger_enable(nl);
	}

	return 0;
}

#ifndef ZEBU_POC
#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(5, noc_logger_init);
#endif
#endif /* ZEBU_POC */
