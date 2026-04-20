/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. (¡°SAMSUNG¡±).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */

.global GateSmp_tryLock
.type GateSmp_tryLock  , %function

GateSmp_tryLock:
	ldxr    w1, [x0]
	cmp     w1, #1  /* is locked already? */
	beq     1f      /* if so, leave with fail */

	mov     w2, #1  /* locked = 1 */
	stxr    w1, w2, [x0] /* if so attempt to grab it */
	cmp     w1, #0       /* did we get it? zero is yes */
	/* if not, loop while in contention */
	bne     GateSmp_tryLock
1:
	mov     w0, w1
	dmb     sy
	ret

/*
 *  void GateSmp_unlock(uintptr_t gateWord);
 */
.global GateSmp_unlock
.type GateSmp_unlock  , %function

GateSmp_unlock:
	dmb     sy

	mov     w1, #0
	str     w1, [x0]

	dsb     sy
	sev         /* let everyone know */
	ret
