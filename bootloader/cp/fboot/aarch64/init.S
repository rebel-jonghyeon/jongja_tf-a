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
#include <rebel_h_platform.h>
	.section	.text.startup
	.align	3

	.global	_start
	.global	safe_zone

_start:
	bl init_boot_log
	/*
	 * In case of secondary die's fboot_n,
	 * it goes to 'safe_zone'
	 */
	cmp	w0, #ID0
	beq	check_bootmode

	/* step 1 for debug */
	mov w0,	#0x1
	bl	set_boot_log
	b	safe_zone

check_bootmode:
	/* step 2 for debug */
	mov w0,	#0x2
	bl	set_boot_log

	/*
	 * Normal bootmode only can go foward
	 * Other(WFD/Secure bootmode/Un-defined) cases go to 'safe_zone'
	 */
	ldr	x0, =CPMU_PRIVATE
	ldr	w0, [x0, #OM_STAT]
	and	w0, w0, #OM_MASK
	cmp	w0, #NORMAL_BOOT
	beq	normal_boot
	/* step 3 for debug */
	mov w0,	#0x3
	bl	set_boot_log

safe_zone:
	wfi
	b	safe_zone

normal_boot:
	/* step 4 for debug */
	mov w0,	#0x4
	bl	set_boot_log

	/*
	 * Initialize GPR, SP, ELR and SPSR for RTL simulation.
	 * These registers should be initialized by 0 for RTL simulation.
	 */
	mov	x30, #0
	bl	initialize_cpu_regs

	/*
	 * Initialize cpu common settings. In this function, vector table is updated to
	 * VBAR_EL3 and I-CACHE is enabled.
	 */
	bl	initialize_cpu

	/* Set stack pointer here. Stack area is INTMEM_BASE + stack_top. */
	ldr	x0, =stack_top
	mov	sp, x0

	ldr	x1, =data_reloc_start
	ldr	x2, =data_start
	ldr	x3, =data_end
	cmp	x1, x2
	beq	89f
	bl	relocate_data_section

89:
	/* code initializes BSS area(ZERO initialized area). */
	ldr	x1, =bss_start
	ldr	x2, =bss_end
	bl	initialize_zero_section

	/* step 5 for debug */
	mov w0,	#0x5
	bl	set_boot_log

	/* Jump to main routine */
	bl	__main

	/* Never reach here. */
	wfi
	b	.

	.ltorg
	.size	_start, . - _start

	.section .text
	.globl initialize_cpu
/**
 *	CPU initialization routine
 *
 *	It contains vector table initialization end enable I-CACHE
 *
 *	@fn			void initialize_cpu(void)
 */

initialize_cpu:
	/* Save link register (X30) to allow BL instruction */
	mov	x15, x30

	/*
	 * Set vector base address to VBAR_EL3 to point vector table. Vector tables
	 * are implemented in vectors.S.
	 */
	ldr	x0, =vectors
	bl	initialize_vector_table

	/* Restore link register (X30) */
99:
	mov	x30, x15
	ret

	.ltorg
	.size	initialize_cpu, . - initialize_cpu

/**
 *	section relocate data
 *
 *	It relocate ROM API area and data area.
 *
 *	@fn			void relocate_data_section(void)
 */
relocate_data_section:
	cmp	x2, x3
	beq	1f
relocate_data:
	ldp	x4, x5, [x1], #16
	stp	x4, x5, [x2], #16
	cmp	x3, x2
	b.gt	relocate_data

1:
	ret

	.size	relocate_data_section, . - relocate_data_section

/**
 *	section initialization bss area
 *
 *	It initialize BSS area and dma buffers.
 *
 *	@fn			void initialize_zero_section(void)
 */
initialize_zero_section:
	cmp	x1, x2
	beq	2f
relocate_zero:
	stp	xzr, xzr, [x1], #16
	cmp	x2, x1
	b.gt	relocate_zero

2:
	ret
	.size	initialize_zero_section, . - initialize_zero_section

#define CP0_BIN_MASK    0xFFF8FFFFU
#define CP0_STEP_MASK   0xFFFFFFE0U
#define CHIPLET_MASK    0x3FFFFFFFU
#define CHIPLET_ID_BIT	30
#define CP0_FBOOT_N_BIN	0x10000

/**
 *	init boot-log sfr and flag sfr for cp0 fboot_n
 *	it returns chiplet-id (0,1,2,3)
 *
 *	@fn			uint32_t init_boot_log(void)
 */
init_boot_log:
	ldr	x0, =BOOT_FLAG_ADDR

	/* init flag to 0 */
	mov w1, #0
	str w1, [x0]

	/* read BOOT_LOG_ADDR sfr */
	ldr	x2, =BOOT_LOG_ADDR
	ldr	w3, [x2]

	/* init BOOT_LOG value
	 * CHIPLET_MASK : chiplet id [31:30]
	 * CP0_BIN_MASK : cp0 binary [18:16]
	 * CP0_STEP_MASK : cp0 step	[4:0]
	 */
	and w3, w3, #CP0_BIN_MASK
	and w3, w3, #CP0_STEP_MASK
	and w3, w3, #CHIPLET_MASK

	/* load chiplet id */
	ldr	x4, =SYSREG_SYSREMAP_PRIVATE
	ldr	w1, [x4, #CHIPLET]
	and w1, w1, #ID_MASK
	/* backup chiplet id to return */
	mov w4, w1

	lsl w1, w1, #CHIPLET_ID_BIT
	orr w3, w1, w3

	orr w3, w3, #CP0_FBOOT_N_BIN

	/* write BOOT_LOG_ADDR */
	str w3, [x2]

	mov w0, w4
	ret

/**
 *	set boot-log sfr
 *
 *  this function only changes 'step' field
 *
 *	@fn			void write_boot_log(uint32_t step)
 */
set_boot_log:
	/* read BOOT_LOG_ADDR sfr */
	ldr	x2, =BOOT_LOG_ADDR
	ldr	w3, [x2]

	/* init step field and set step value */
	and w3, w3, #CP0_STEP_MASK
	/* w0 contains step value */
	orr w3, w3, w0

	/* set BOOT_LOG value */
	str w3, [x2]

	ret
