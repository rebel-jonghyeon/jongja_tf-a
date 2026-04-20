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

	.section .vectors
	.align 11
	.global vectors
/**
 *	Exception Vector
 *
 *	This routine is exception vector. VBAR_EL3[10:0] is reserved bit, so it
 *	should be aligned 2048 (2^11) bytes. Start address of this routine is set
 *	to VBAR_EL3 in startup routine.
 *
 *	63                                              11 10              0
 *	--------------------------------------------------------------------
 *	|               Vector Base Address               |      RES0      |
 *	--------------------------------------------------------------------
 */
vectors:
/*
 * Vector tables for event from current EL with SP0
 */
//-------------------------------------------Synchronous------------
	.align   7
	B       .
//-------------------------------------------IRQ/vIRQ---------------
	.align   7
	B       .
//-------------------------------------------FIQ/vFIQ---------------
	.align   7
	B       .
//-------------------------------------------SError/vSError---------
	.align   7
	B       .

/*
 * Vector tables for event from current EL with SP3
 */
//-------------------------------------------Synchronous------------
	.align   7
	B       .
//-------------------------------------------IRQ/vIRQ---------------
	.align   7
	B       .
//-------------------------------------------FIQ/vFIQ---------------
	.align   7
	B       .
//-------------------------------------------SError/vSError---------
	.align   7
	B       .

/*
 * Vector tables for event from lower EL using AArch64. This routine may not
 * be needed because Level1 is still running on EL3 mode. We can remove this
 * routine to reduce ROM code size.
 */
//-------------------------------------------Synchronous------------
	.align   7
	B       .
//-------------------------------------------IRQ/vIRQ---------------
	.align   7
	B       .
//-------------------------------------------FIQ/vFIQ---------------
	.align   7
	B       .
//-------------------------------------------SError/vSError---------
	.align   7
	B       .

/*
 * Vector tables for event from lower EL using AArch32. This routine may not
 * be needed because Level1 is still running on EL3 mode. We can remove this
 * routine to reduce ROM code size.
 */
//-------------------------------------------Synchronous------------
	.align   7
	B       .
//-------------------------------------------IRQ/vIRQ---------------
	.align   7
	B       .
//-------------------------------------------FIQ/vFIQ---------------
	.align   7
	B       .
//-------------------------------------------SError/vSError---------
	.align   7
	B       .

	.size	vectors, . - vectors
