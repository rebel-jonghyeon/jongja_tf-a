/*
 * Copyright (c) 2017 Jean-Paul Etienne <fractalclone@gmail.com>
 * Contributors: 2018 Antmicro <www.antmicro.com>
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <toolchain.h>
#include <irq.h>
#include <arch/cpu.h>
#if defined(CONFIG_SUPERVISOR_MODE) && defined(CONFIG_CMRT_PMU)
#include <drivers/cmrt/pmu.h>
#endif
#ifdef CONFIG_CMRT_SAC_CONSOLE
#include <drivers/cmrt/sac.h>
#endif

#include <tracing/tracing.h>

static ALWAYS_INLINE void riscv_idle(unsigned int key)
{
#if defined(CONFIG_SUPERVISOR_MODE) && defined(CONFIG_CMRT_PMU)
	cmrt_pmu_to_idle();
#endif
	sys_trace_idle();
	/* unlock interrupts */
	irq_unlock(key);

#ifdef CONFIG_CMRT_SAC_CONSOLE
	cmrt_sac_console_copy();
#endif
	/* Wait for interrupt */
	arch_wfi();
}

/**
 *
 * @brief Power save idle routine
 *
 * This function will be called by the kernel idle loop or possibly within
 * an implementation of _pm_save_idle in the kernel when the
 * '_pm_save_flag' variable is non-zero.
 *
 * @return N/A
 */
void arch_cpu_idle(void)
{
	riscv_idle(MSTATUS_IEN);
}

/**
 *
 * @brief Atomically re-enable interrupts and enter low power mode
 *
 * INTERNAL
 * The requirements for arch_cpu_atomic_idle() are as follows:
 * 1) The enablement of interrupts and entering a low-power mode needs to be
 *    atomic, i.e. there should be no period of time where interrupts are
 *    enabled before the processor enters a low-power mode.  See the comments
 *    in k_lifo_get(), for example, of the race condition that
 *    occurs if this requirement is not met.
 *
 * 2) After waking up from the low-power mode, the interrupt lockout state
 *    must be restored as indicated in the 'imask' input parameter.
 *
 * @return N/A
 */
void arch_cpu_atomic_idle(unsigned int key)
{
	riscv_idle(key);
}
