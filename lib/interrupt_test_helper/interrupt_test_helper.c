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

#include "interrupt.h"
#include "interrupt_test_helper.h"
#include "stdio.h"

#if defined(__TARGET_PCIE)
static bool int_ctrl_backup[32];
static uint32_t int_priority_backup[32];
static uint32_t int_vetors[32];

static bool is_interrupt_idle(const int32_t intid)
{
	return !(NVIC_GetActive(intid) || NVIC_GetPendingIRQ(intid));
}

bool interrupt_test_init(const int32_t intid)
{
	if (is_interrupt_idle(intid) == false)
		return false;

	int_ctrl_backup[intid] = NVIC_GetEnableIRQ(intid);
	int_priority_backup[intid] = NVIC_GetPriority(intid);
	int_vetors[intid] = NVIC_GetVector(intid);
	NVIC_EnableIRQ(intid);

	return true;
}

void interrupt_set_pending(const int32_t intid)
{
	NVIC_SetPendingIRQ(intid);
}

void interrupt_clear_pending(const int32_t intid)
{
	NVIC_ClearPendingIRQ(intid);
}

bool interrupt_test_end(const int32_t intid)
{
	if (is_interrupt_idle(intid) == false)
		return false;

	NVIC_SetVector(intid, int_vetors[intid]);
	NVIC_SetPriority(intid, int_priority_backup[intid]);

	if (int_ctrl_backup[intid] == true)
		NVIC_EnableIRQ(intid);
	else
		NVIC_DisableIRQ(intid);

	return true;
}
#elif defined(__TARGET_CP)
#include "gic.h"

static bool int_ctrl_backup[1024];
static uint8_t int_priority_backup[1024];
static _isr_table int_vetors[1024];

extern _isr_table isr_table[];

static uint8_t get_spi_priority(const int32_t intid)
{
	uint32_t reg_offset = (4 * ((uint64_t)intid / 4));
	uint32_t gicd_ipriority_n = *(uint32_t *)(GICD_IPRIORITYRn + reg_offset);

	return (uint8_t)0xff & (gicd_ipriority_n >> (((intid % 4) * 8)));
}

static bool is_interrupt_idle(const int32_t intid)
{
	uint32_t reg_offset = (4 * ((uint64_t)intid / 32));

	return sys_test_bit(GICD_ISACTIVERn + reg_offset, intid % 32) == 0 &&
			sys_test_bit(GICD_ISPENDRn + reg_offset, intid % 32) == 0;
}

bool interrupt_test_init(const int32_t intid)
{
	if (is_interrupt_idle(intid) == false)
		return false;

	int_ctrl_backup[intid] = gic_irq_is_enabled(intid);
	int_priority_backup[intid] = get_spi_priority(intid);
	int_vetors[intid] = isr_table[intid];
	gic_irq_enable(intid);

	return true;
}

void interrupt_set_pending(const int32_t intid)
{
	uint32_t reg_offset = (4 * (intid / 32));
	uint32_t gicd_ispend_n = sys_read32(GICD_ISPENDRn + reg_offset);

	sys_write32(gicd_ispend_n | BIT(intid % 32), GICD_ISPENDRn + reg_offset);
}

void interrupt_clear_pending(const int32_t intid)
{
	uint32_t reg_offset = (4 * (intid / 32));
	uint32_t gicd_icpend_n = sys_read32(GICD_ICPENDRn + reg_offset);

	sys_write32(gicd_icpend_n | BIT(intid % 32), GICD_ICPENDRn + reg_offset);
}

bool interrupt_test_end(const int32_t intid)
{
	if (is_interrupt_idle(intid) == false)
		return false;

	isr_table[intid] = int_vetors[intid];
	gic_irq_set_priority(intid, int_priority_backup[intid], IRQ_TYPE_LEVEL);

	if (int_ctrl_backup[intid] == true)
		gic_irq_enable(intid);
	else
		gic_irq_disable(intid);

	return true;
}
#endif

