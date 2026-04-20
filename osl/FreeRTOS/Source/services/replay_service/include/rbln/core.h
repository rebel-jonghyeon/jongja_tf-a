/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2024 [Rebellions Inc.], All Rights Reserved.
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


#ifndef _RL_CPU_H
#define _RL_CPU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

enum rl_cpu_hart {
	HART_ID_0,
	HART_ID_1,
	HART_ID_2,
	HART_ID_3
};

#define RL_CPU_CORE_NUM			4

#define RL_CPU_ALL_CORE_MASK	RL_GENMASK(RL_CPU_CORE_NUM - 1, 0)

void rl_cpu_set_core_ready_status(const enum rl_cpu_hart id);
uint32_t rl_cpu_get_core_ready_status(void);
void rl_cpu_reset_ready_status(void);
void rl_cpu_reset_timer(void);

void rl_cpu_wait_core_ready(const enum rl_cpu_hart id);
bool rl_cpu_is_all_core_ready(void);

void rl_cpu_enable_cycle(void);
void rl_cpu_disable_cycle(void);

static inline uint64_t rl_cpu_read_cycle(void)
{
	uint64_t val = 0;

	asm volatile("MRS %0, pmccntr_el0" : "=r"(val));
	return val;
}

void cpu_flush_dcache_range(uintptr_t addr, size_t size);
void cpu_clean_dcache_range(uintptr_t addr, size_t size);
void cpu_inv_dcache_range(uintptr_t addr, size_t size);

void cpu_enable_clksync_interrupt(uint32_t core_id);
void cpu_raise_clksync_interrupt(void);
#endif /* _RL_CPU_H */
