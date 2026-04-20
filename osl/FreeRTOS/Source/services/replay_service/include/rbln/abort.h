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

#ifndef _RL_ABORT_H_
#define _RL_ABORT_H_

#include "cpu.h"
#include <stdbool.h>
#ifdef GCOV_ENABLED
#include "gcov_public.h"
#endif

/* for custom abort function */
#define SGI_TARGET_AFF 0
#define SGI_TARGET_LIST 15
#define INVALID_CORE_ID 0xFFFFFFFF

void abort_other_cores(void);
void rl_hang(bool halt_device);
void rl_abort_event(uint32_t event);
void rl_abort_guilty_ctx(uint32_t func_id, uint32_t ctx_id, uint32_t err_code);
void rl_abort_cur_ctx(uint32_t err_code);
bool is_abort_event(void);

#ifdef TRACE_ENABLED
uint64_t xTraceDisable(void);
#endif

static inline void __attribute__((noreturn)) rl_shutdown(int code)
{
#if defined(GCOV_ENABLED) || defined(TRACE_ENABLED)
	uint64_t core_id = get_current_cpuid();
#endif

#ifdef GCOV_ENABLED
	if (core_id == 0)
		__gcov_exit();
#endif

#ifdef TRACE_ENABLED
	if (core_id == 0)
		xTraceDisable();
#endif

	while (1) {
		__asm__ volatile("nop");
	}
}

void enable_abort_interrupt(uint32_t core_id);
uint64_t get_current_el(void);
#endif /* _RL_ABORT_H_ */
