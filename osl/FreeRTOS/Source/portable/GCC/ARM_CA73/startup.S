/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

#define SCTLR_M_BIT     1 << 0
#define SCTLR_A_BIT     1 << 1
#define SCTLR_C_BIT     1 << 2
#define SCTLR_SA_BIT    1 << 3
#define SCTLR_I_BIT     1 << 12
#define SCTLR_BR_BIT    1 << 17
#define SCTLR_EL1_RES1      (1 << 29 | 1 << 28 | 1 << 23 | 1 << 22 | 1 << 20 | 1 << 11)
#define CPACR_FPEN      0x3 << 20
#define STACK_OFFSET    0x1000
#define ECTLR_SMPEN           1 < 6
#define ECTLR_STXEN           1 < 9

#define SYSREG_SYSREMAP_CHIPLET		0x1E00220444
#define CHIPLET_OFFSET				0x2000000000
#define FREERTOS_BASE_ADDR			0x10000000000

.section .text.startup
.align 3
.global _start

.extern _freertos_vector_table

_start:
	/**
	 * x21	= chiplet_id
	 * x22	= chiplet_offset
	 * x23	= chiplet_diff
	 *		= (base_addr - 0x100_0000_0000) + (chiplet_id * chiplet_offset)
	 *		= base_addr - 0x100_0000_0000 + (x21[chiplet_id] * x22[chiplet_offset])
	 *		= base_addr - (0x100_0000_0000 - (x21 * x22))
	 *		= x22
	 * Example of same binary approach
	 *	chiplet0 : 0x100_0020_0000 -> 0x000_0020_0000
	 *	chiplet1 : 0x100_0020_0000 -> 0x020_0020_0000
	 *	chiplet2 : 0x100_0020_0000 -> 0x040_0020_0000
	 *	chiplet3 : 0x100_0020_0000 -> 0x060_0020_0000
	 */
	ldr x21, =0x1E00220444
	ldr w21, [x21]
	and x21, x21, 0x3				/* chiplet_id */
#if (CHIPLET_COUNT == 1)
	mov x21, 0x0
#endif /* CHIPLET_COUNT */
	mov x22, CHIPLET_OFFSET
	mul x22, x22, x21				/* chiplet_offset */

	mov x23, FREERTOS_BASE_ADDR
	sub x23, x23, x22				/* chiplet_diff */
	mov x22, x23

	ldr x1, =_freertos_vector_table
	sub x1, x1, x22
	msr vbar_el1, x1

	msr daifclr, 0xc
	isb

    mrs x0, s3_1_c15_c2_1
    ldr x1, =(ECTLR_SMPEN | ECTLR_STXEN)
    orr x0, x0, x1
    msr s3_1_c15_c2_1, x0

	ldr x23, =_stack_top
	ldr x24, =isr_stack_top
	sub x24, x24, x22		/* isr_stack_top - chiplet_diff */

	mrs x0, mpidr_el1
	and x0, x0, #0xFF
	cmp x0, #0
	beq primary_core

	sub x23, x23, x0, lsl #12
	sub x24, x24, x0, lsl #12
	ldr x25, =secondary_prep_c
	b 1f

primary_core:
	ldr x25, =primary_prep_c

1:
	sub x25, x25, x22	/* (primary_prep_c - chiplet_diff) or (secondary_prep_c - chiplet_diff) */
	mrs x0, sctlr_el1
	bic x0, x0, SCTLR_A_BIT

	ldr x1, =(SCTLR_EL1_RES1 | SCTLR_SA_BIT | SCTLR_I_BIT)
	orr x0, x0, x1

	msr sctlr_el1, x0
	isb

	msr sp_el0, x23

	msr spsel, #1
	mov sp, x24

	mov x0, CPACR_FPEN
	msr cpacr_el1, x0

	mov x0, #7
	msr s3_0_c12_c12_5, x0

	ret x25

	/* Never reach here */
	b .
