/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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
#include <interrupt.h>
#include <driver.h>
#include <rebel_h_platform.h>
#include "dw_apb_wdt_reg.h"
#include "dw_apb_wdt.h"

/* SFR setting */
#define DW_APB_WDT_RESTART			(0x76U)
#define DW_APB_WDT_ENABLE			(1U)
#define DW_APB_WDT_RMOD_INTERRUPT	(1U)
#define DW_APB_WDT_RMOD_RESET		(0U)

/* Glue logic to support a pause */
#define	SYSREG_WDT_CONTROL_PUASE	BIT(1)
#define SYSREG_WDT0_PERI0_CONTROL	(SYSREG_PERI0 + 0x108)
#define SYSREG_WDT1_PERI0_CONTROL	(SYSREG_PERI0 + 0x10C)
#define SYSREG_WDT0_PERI1_CONTROL	(SYSREG_PERI1 + 0x108)
#define SYSREG_WDT1_PERI1_CONTROL	(SYSREG_PERI1 + 0x10C)
#define SYSREG_WDT_PCIE_CONTROL		(SYSREG_PCIE_PRIVATE + 0x304)

/* Counter base clock of WDT instance */
#define	FREQUENCY_500MHZ			(500U)
#define	FREQUENCY_250MHZ			(250U)
#define TIMEOUT_MAX					(0xFU)

struct wdt_dev {
	uintptr_t reg_base;
	uintptr_t sys_ctrl;	/* glue logic for pause */
	uint32_t irq_num;
	uint32_t clk;		/* counter reference clock in MHz */
	uint32_t rmod;		/* response mode */
};

static struct wdt_dev wdt_dev_plat[] = {
#if defined(__TARGET_PCIE)
	{WDT_PCIE_PRIVATE, SYSREG_WDT_PCIE_CONTROL, 31, FREQUENCY_500MHZ, DW_APB_WDT_RMOD_INTERRUPT},
#else
	{WDT0_PERI0, SYSREG_WDT0_PERI0_CONTROL, 214, FREQUENCY_250MHZ, DW_APB_WDT_RMOD_INTERRUPT},
	{WDT1_PERI0, SYSREG_WDT1_PERI0_CONTROL, 215, FREQUENCY_250MHZ, DW_APB_WDT_RMOD_INTERRUPT},
	{WDT0_PERI1, SYSREG_WDT0_PERI1_CONTROL, 264, FREQUENCY_250MHZ, DW_APB_WDT_RMOD_INTERRUPT},
	{WDT1_PERI1, SYSREG_WDT1_PERI1_CONTROL, 265, FREQUENCY_250MHZ, DW_APB_WDT_RMOD_INTERRUPT},
#endif
};

uint32_t dw_apb_wdt_get_version(volatile struct wdt_dev *dev)
{
	volatile struct dw_apb_wdt *dw_apb_wdt = (struct dw_apb_wdt *)(dev->reg_base);

	return dw_apb_wdt->wdt_comp_version.val;
}

uint32_t dw_apb_wdt_get_enabled(volatile struct wdt_dev *dev)
{
	volatile struct dw_apb_wdt *dw_apb_wdt = (struct dw_apb_wdt *)(dev->reg_base);

	return dw_apb_wdt->wdt_cr.wdt_en;
}

void dw_apb_wdt_set_timeout(volatile struct wdt_dev *dev, uint32_t timeout)
{
	volatile struct dw_apb_wdt *dw_apb_wdt = (struct dw_apb_wdt *)(dev->reg_base);

	dw_apb_wdt->wdt_torr.top = timeout;
	dw_apb_wdt_kick(dev);
}

void dw_apb_wdt_enable(volatile struct wdt_dev *dev)
{
	volatile struct dw_apb_wdt *dw_apb_wdt = (struct dw_apb_wdt *)(dev->reg_base);

	dw_apb_wdt->wdt_cr.wdt_en = DW_APB_WDT_ENABLE;
}

void dw_apb_wdt_set_rmod(volatile struct wdt_dev *dev, uint32_t rmod)
{
	volatile struct dw_apb_wdt *dw_apb_wdt = (struct dw_apb_wdt *)(dev->reg_base);

	dw_apb_wdt->wdt_cr.rmod = rmod;
}

void dw_apb_wdt_disable(volatile struct wdt_dev *dev)
{
	/*
	 * NOTE: Disabling IP itself is not available
	 *		 Instead, we're using sysreg glue logic to stop counting(pause)
	 */
	volatile uintptr_t *p = (uintptr_t *)(dev->sys_ctrl);

	*p |= SYSREG_WDT_CONTROL_PUASE;
}

void dw_apb_wdt_kick(volatile struct wdt_dev *dev)
{
	volatile struct dw_apb_wdt *dw_apb_wdt = (struct dw_apb_wdt *)(dev->reg_base);

	dw_apb_wdt->wdt_crr.wdt_crr = DW_APB_WDT_RESTART;
}

static void dw_apb_wdt_isr(void *data)
{
	volatile struct wdt_dev *dev = (struct wdt_dev *)data;

	dw_apb_wdt_kick(dev);
	/* NOTE: Add service here */
}

/*
 * NOTE: Same driver used for both FreeRTOS_CP/PCIE and,
 *		 only one instance will be used both for FreeRTOS_CP/PCIE
 */
int dw_apb_wdt_init(void)
{
	volatile struct dw_apb_wdt *wdt = (struct dw_apb_wdt *)wdt_dev_plat[0].reg_base;

	if (!wdt)
		return -1;

	connect_interrupt_with_handler(wdt_dev_plat[0].irq_num, 2, IRQ_TYPE_LEVEL,
								   dw_apb_wdt_isr, (void *)&wdt_dev_plat[0]);

	/* NOTE: Pass max timeout condition not to make a kind of too early reset/interrupt */
	dw_apb_wdt_set_timeout(&wdt_dev_plat[0], TIMEOUT_MAX);

	dw_apb_wdt_set_rmod(&wdt_dev_plat[0], DW_APB_WDT_RMOD_INTERRUPT);

	/*
	 * TODO: Enable/Start WDT itself when a wdt scenario is fully ready
	 * dw_apb_wdt_enable(&wdt_dev_plat[0]);
	 */

	return 0;
}

#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(5, dw_apb_wdt_init);
#endif
