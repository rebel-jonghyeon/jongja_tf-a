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

	.align	3
	.globl	initialize_vector_table
/**
 *	Exception vector table setting.
 *
 *	VBAR_EL3 has exception vector table base address. VBAR_EL3 is updated
 *	in this routine.
 *
 *	@fn			void initialize_vector_table(void *vector_base)
 *	@param[in]	vector_base	Base address for exception vector table.
 *							It is in X0 register.
 */
initialize_vector_table:
	msr	vbar_el3, x0
	ret

	.size	initialize_vector_table, . - initialize_vector_table

	.global	initialize_cpu_regs
/**
 *	Initialize GPR for RTL simulation
 *
 *	This function is only called in RTL simulation. Simulation hangs if GPR, SP
 *	and ELR_ELx and SPSR_ELx are not initialized.
 *
 *	@fn			void initialize_cpu_regs(void)
 */
initialize_cpu_regs:
	/* Set all GPRs to 0 */
	mov	x0, #0
	mov	x1, #0
	mov	x2, #0
	mov	x3, #0
	mov	x4, #0
	mov	x5, #0
	mov	x6, #0
	mov	x7, #0
	mov	x8, #0
	mov	x9, #0
	mov	x10, #0
	mov	x11, #0
	mov	x12, #0
	mov	x13, #0
	mov	x14, #0
	mov	x15, #0
	mov	x16, #0
	mov	x17, #0
	mov	x18, #0
	mov	x19, #0
	mov	x20, #0
	mov	x21, #0
	mov	x22, #0
	mov	x23, #0
	mov	x24, #0
	mov	x25, #0
	mov	x26, #0
	mov	x27, #0
	mov	x28, #0
	mov	x29, #0

	/* Set all stack pointers to 0 */
	mov	sp, x0
	msr	sp_el0, x0
	msr	sp_el1, x0
	msr	sp_el2, x0

	/* Set all elr_elx registers to 0 */
	msr	elr_el1, x0
	msr	elr_el2, x0
	msr	elr_el3, x0

	/* Set all spsr_elx registers to 0 */
	msr	spsr_el1, x0
	msr	spsr_el2, x0
	msr	spsr_el3, x0

	ret

	.size	initialize_cpu_regs, . - initialize_cpu_regs
