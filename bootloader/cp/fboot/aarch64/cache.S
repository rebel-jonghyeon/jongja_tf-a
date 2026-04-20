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

#define ICACHE_CONTROL		(12)
#define DCACHE_CONTROL		(2)
#define MMU_CONTROL			(0)

	.align	3
/**
 *	Enable I-Cache
 *
 *	This function enables I-Cache to speed up code running. Just in case, D/M bits
 *	are cleared.
 *
 *	@fn		void enable_icache(void)
 */
	.globl	enable_icache
enable_icache:
	mrs	x0, sctlr_el3
	bic	x0, x0, #(1 << DCACHE_CONTROL)
	bic	x0, x0, #(1 << MMU_CONTROL)
	orr	x0, x0, #(1 << ICACHE_CONTROL)
	msr	sctlr_el3, x0
	isb
	ret

	.size	enable_icache, . - enable_icache
