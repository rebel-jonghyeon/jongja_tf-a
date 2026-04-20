/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2025 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#ifndef _RL_IO_BURST_H_
#define _RL_IO_BURST_H_

#include <stdint.h>

#ifndef __iomem
#define __iomem
#endif

/*
 * @brief Write 32 bytes (8 x 32-bit values) using CA73 burst write (stp instruction)
 * @param src Pointer to source data (8 x uint32_t, must be 8-byte aligned)
 * @param dst Pointer to destination I/O memory (must be 8-byte aligned)
 *
 * Uses ARM64 stp (Store Pair) instruction for optimal burst write performance.
 * Each stp writes 16 bytes (2 x 64-bit registers), so 2 stp instructions write 32 bytes.
 * This function uses inline assembly to ensure stp instructions are generated.
 */
static inline void rl_write32b_burst(const uint32_t *src, volatile void __iomem *dst)
{
	volatile uint64_t __iomem *dst64 = (volatile uint64_t __iomem *)dst;
	uint64_t val0, val1, val2, val3;

	/* Load 4 x 64-bit values from source (combine 2 x 32-bit into 1 x 64-bit) */
	val0 = ((uint64_t)src[1] << 32) | (uint64_t)src[0];
	val1 = ((uint64_t)src[3] << 32) | (uint64_t)src[2];
	val2 = ((uint64_t)src[5] << 32) | (uint64_t)src[4];
	val3 = ((uint64_t)src[7] << 32) | (uint64_t)src[6];

	/* Use stp (Store Pair) for burst write - 16 bytes per instruction */
	__asm__ volatile(
		"stp %0, %1, [%4]\n\t"
		"stp %2, %3, [%4, #16]\n\t"
		:
		: "r" (val0), "r" (val1), "r" (val2), "r" (val3), "r" (dst64)
		: "memory"
	);
}

#endif /* _RL_IO_BURST_H_ */
