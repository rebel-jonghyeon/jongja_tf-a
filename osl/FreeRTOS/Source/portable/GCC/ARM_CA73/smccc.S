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

.align 8
.global arm_smccc_smc
.type arm_smccc_smc, %function

#define SMC_ARG0_OFFSET 0x0
#define SMC_ARG2_OFFSET 0x10
#define SMC_ARG4_OFFSET 0x20
#define SMC_ARG6_OFFSET 0x30

arm_smccc_smc:
	smc #0

	ldr x4, [sp]
	stp x0, x1, [x4, SMC_ARG0_OFFSET]
	stp x2, x3, [x4, SMC_ARG2_OFFSET]
	stp x4, x5, [x4, SMC_ARG4_OFFSET]
	stp x6, x7, [x4, SMC_ARG6_OFFSET]
	ret
