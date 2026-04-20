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

//#include "rbln/utils.h"
#include "rl_utils.h"
#include "cpu.h"
#include "rbln/core.h"
#include "rbln/spinlock.h"
#include "system_api.h"
#include "rbln/cache.h"
#include "gic.h"
#include "rbln/sgi.h"

#define ARMV8_PMCR_MASK			0x3f
#define ARMV8_PMCR_E			(1 << 0)	/*  Enable all counters */
#define ARMV8_PMCR_P			(1 << 1)	/*  Reset all counters */
#define ARMV8_PMCR_C			(1 << 2)	/*  Cycle counter reset */
#define ARMV8_PMCR_N_MASK		0x1f

#define ARMV8_PMUSERENR_EN_EL0	(1 << 0)	/*  EL0 access enable */
#define ARMV8_PMUSERENR_CR		(1 << 2)	/*  Cycle counter read enable */
#define ARMV8_PMUSERENR_ER		(1 << 3)	/*  Event counter read enable */

#define ARMV8_PMCNTENSET_EL0_ENABLE (1<<31)	/* *< Enable Perf count reg */

#define PERF_DEF_OPTS (1 | 16)

static volatile uint32_t cpu_core_status;
static spinlock_t core_status_lock = { 0, };

void rl_cpu_set_core_ready_status(const enum rl_cpu_hart id)
{
	spin_lock(&core_status_lock);
	RL_SET_BIT(cpu_core_status, id);
	spin_unlock(&core_status_lock);
}

uint32_t rl_cpu_get_core_ready_status(void)
{
	return cpu_core_status;
}

void rl_cpu_reset_ready_status(void)
{
	cpu_core_status = 0;
}

void rl_cpu_wait_core_ready(const enum rl_cpu_hart id)
{
	while (!(cpu_core_status & RL_BIT(id)))
		udelay(5);
}

bool rl_cpu_is_all_core_ready(void)
{
	return cpu_core_status == RL_CPU_ALL_CORE_MASK;
}

static inline uint32_t armv8pmu_read(void)
{
	uint64_t val = 0;

	asm volatile("MRS %0, pmcr_el0" : "=r" (val));
	return (uint32_t)val;
}

static inline void armv8pmu_write(uint32_t val)
{
	val &= ARMV8_PMCR_MASK;
	asm volatile("isb" : : : "memory");
	asm volatile("MSR pmcr_el0, %0" : : "r" ((uint64_t)val));
}

void rl_cpu_reset_timer(void)
{
	armv8pmu_write(armv8pmu_read() | ARMV8_PMCR_C);
}

void rl_cpu_enable_cycle(void)
{
	uint64_t val;

	/* Enable user-mode access to counters. */
	val = ARMV8_PMUSERENR_EN_EL0|ARMV8_PMUSERENR_CR;
	asm volatile("MSR pmuserenr_el0, %0" : : "r"((uint64_t)val));

	/* Initialize & Reset PMNC: C and P bits. */
	armv8pmu_write(ARMV8_PMCR_P | ARMV8_PMCR_C);
	asm volatile("MSR pmintenset_el1, %0" : : "r" ((uint64_t)(0 << 31)));

	/* Count Enable Set register bit  31 enable */
	asm volatile("MSR pmcntenset_el0, %0" : : "r" (ARMV8_PMCNTENSET_EL0_ENABLE));
	armv8pmu_write(armv8pmu_read() | ARMV8_PMCR_E);
}

void rl_cpu_disable_cycle(void)
{
	/*  Performance Monitors Count Enable Set register bit 31:0 disable */
	asm volatile("MSR pmcntenset_el0, %0" : : "r" (0<<31));

	/*  Disable all counters and user-mode access to counters. */
	armv8pmu_write(armv8pmu_read() | ~ARMV8_PMCR_E);
	asm volatile("MSR pmuserenr_el0, %0" : : "r"((uint64_t)0));
}

void cpu_flush_dcache_range(uintptr_t addr, size_t size)
{
	flush_dcache_range(addr, size);
}

void cpu_clean_dcache_range(uintptr_t addr, size_t size)
{
	clean_dcache_range(addr, size);
}

void cpu_inv_dcache_range(uintptr_t addr, size_t size)
{
	inv_dcache_range(addr, size);
}

static void clksync_handler(void *irq_data)
{
	rl_cpu_enable_cycle();
}

void cpu_enable_clksync_interrupt(uint32_t core_id)
{
	gic_irq_set_priority(SGI_ID_CLKSYNC, 0, IRQ_TYPE_LEVEL);
	gic_irq_enable_dedicated_core(core_id, SGI_ID_CLKSYNC);
	gic_irq_connect(SGI_ID_CLKSYNC, clksync_handler, NULL);
}

void cpu_raise_clksync_interrupt(void)
{
	gic_raise_sgi(SGI_ID_CLKSYNC, 0, 0xf);
}
