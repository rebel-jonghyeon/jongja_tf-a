/*
 * Copyright (c) 2023-2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <platform_def.h>
#include <arch_helpers.h>
#include <common/debug.h>
#include <drivers/arm/gicv3.h>
#include <drivers/console.h>
#include <lib/mmio.h>
#include <lib/psci/psci.h>
#include <plat/arm/common/plat_arm.h>
#include <plat/common/platform.h>

static uintptr_t plat_sec_entrypoint;

/*******************************************************************************
 * Platform handler called to check the validity of the power state
 * parameter. The power state parameter has to be a composite power state.
 ******************************************************************************/
static int rebel_h_validate_power_state(unsigned int power_state,
										psci_power_state_t *req_state)
{
	return PSCI_E_SUCCESS;
}

/*******************************************************************************
 * Platform handler called when a CPU is about to enter standby.
 ******************************************************************************/
static void rebel_h_cpu_standby(plat_local_state_t cpu_state)
{
}

static void set_rvbar(uint32_t cpuid, uintptr_t entrypoint)
{
#ifndef ZEBU_POC
	uintptr_t shift_ep = (entrypoint & ~((uintptr_t)0x3ULL));

	uint32_t addr_l = (uint32_t)(shift_ep);
	uint32_t addr_h = (uint32_t)(shift_ep >> 32);

#if (__TARGET_CP == 1)
	mmio_write_32(SYSREG_CP1 + RVBARADDR0_LOW + (PERCPU_RVBARADDR_OFFSET * cpuid), addr_l);
	mmio_write_32(SYSREG_CP1 + RVBARADDR0_HIGH + (PERCPU_RVBARADDR_OFFSET * cpuid), addr_h);
#else
	mmio_write_32(SYSREG_CP0 + RVBARADDR0_LOW + (PERCPU_RVBARADDR_OFFSET * cpuid), addr_l);
	mmio_write_32(SYSREG_CP0 + RVBARADDR0_HIGH + (PERCPU_RVBARADDR_OFFSET * cpuid), addr_h);
#endif
#endif /* ZEBU_POC */
}

static void pmu_cpu_on(uint32_t cpuid)
{
#ifndef ZEBU_POC
	uint32_t val;

#if (__TARGET_CP == 1)
	mmio_write_32(PMU_BASE + CPU0_CONFIGURATION + PERCLUSTER_OFFSET + (PERCPU_OFFSET * cpuid),
				  CPU_ON_WITH_INITIATE_WAKEUP);

	/* HLOS would check if PSCI(cpu_on)'s call returns on time with a timeout condition */
	do {
		val = mmio_read_32(PMU_BASE + CPU0_STATUS + PERCLUSTER_OFFSET + (PERCPU_OFFSET * cpuid));
	} while ((val & CPU_STATUS_MASK) != CPU_STATUS_ON);
#else
	mmio_write_32(PMU_BASE + CPU0_CONFIGURATION + (PERCPU_OFFSET * cpuid),
				  CPU_ON_WITH_INITIATE_WAKEUP);

	/* HLOS would check if PSCI(cpu_on)'s call returns on time with a timeout condition */
	do {
		val = mmio_read_32(PMU_BASE + CPU0_STATUS + (PERCPU_OFFSET * cpuid));
	} while ((val & CPU_STATUS_MASK) != CPU_STATUS_ON);
#endif
#else
	mmio_write_64(PLAT_SEC_ENTRY, 0x1);

	mmio_write_64(PLAT_CPUID_RELEASE, (uint64_t)cpuid);
	dmbst();
#endif /* ZEBU_POC */
}

static void pmu_cpu_off(uint32_t cpuid)
{
#ifndef ZEBU_POC
#if (__TARGET_CP == 1)
	mmio_write_32(PMU_BASE + CPU0_CONFIGURATION + PERCLUSTER_OFFSET + (PERCPU_OFFSET * cpuid),
				  CPU_OFF_WITH_INITIATE_WAKEUP);

#else
	mmio_write_32(PMU_BASE + CPU0_CONFIGURATION + (PERCPU_OFFSET * cpuid),
				  CPU_OFF_WITH_INITIATE_WAKEUP);
#endif
#endif /* ZEBU_POC */
}

/*******************************************************************************
 * Platform handler called when a power domain is about to be turned on. The
 * mpidr determines the CPU to be turned on.
 ******************************************************************************/
static int rebel_h_pwr_domain_on(u_register_t mpidr)
{
	/* Get a platform level cpuid from mpidr */
	uint32_t cpuid = plat_core_pos_by_mpidr(mpidr);

	INFO("cpuid: %d, cpu_on requested\n", cpuid);

	/* Set RVBARADDR for given cpuid via SYSREG_CP H/W */
	set_rvbar(cpuid, plat_sec_entrypoint);

	/* Release a reset of a core via PMU H/W */
	pmu_cpu_on(cpuid);

	return PSCI_E_SUCCESS;
}

/*******************************************************************************
 * Platform handler called when a power domain has just been powered on after
 * being turned off earlier. The target_state encodes the low power state that
 * each level has woken up from.
 ******************************************************************************/
static void rebel_h_pwr_domain_on_finish(const psci_power_state_t *target_state)
{
#ifdef ZEBU_POC
	mmio_write_64(PLAT_CPUID_RELEASE, 0x0);
	dmbst();
#endif /* ZEBU_POC */
}

/*******************************************************************************
 * Platform handler called when a power domain has just been powered on and the cpu
 * and its cluster are fully participating in coherent transaction on the
 * interconnect. Data cache must be enabled for CPU at this point.
 ******************************************************************************/
static void rebel_h_pwr_domain_on_finish_late(const psci_power_state_t *target_state)
{
	/* Program GIC per-cpu distributor or re-distributor interface */
	plat_arm_gic_pcpu_init();

	/* Enable GIC CPU interface */
	plat_arm_gic_cpuif_enable();
}

/*******************************************************************************
 * Platform handler called when a power domain is about to be turned off.
 ******************************************************************************/
static void rebel_h_pwr_domain_off(const psci_power_state_t *target_state)
{
	uint32_t cpuid = plat_my_core_pos();

	/*
	 * TODO: power level can be cpu or cluster via target_state.
	 *		 Currently, it's implemented for each core-level only.
	 */

	INFO("cpuid: %d, cpu_off requested\n", cpuid);

	plat_arm_gic_cpuif_disable();

	pmu_cpu_off(cpuid);
}

/*******************************************************************************
 * Platform handlers and setup function.
 ******************************************************************************/
static const plat_psci_ops_t plat_rebel_h_psci_pm_ops = {
	.cpu_standby				= rebel_h_cpu_standby,
	.pwr_domain_on				= rebel_h_pwr_domain_on,
	.pwr_domain_on_finish		= rebel_h_pwr_domain_on_finish,
	.pwr_domain_on_finish_late	= rebel_h_pwr_domain_on_finish_late,
	.pwr_domain_off				= rebel_h_pwr_domain_off,
	.validate_power_state		= rebel_h_validate_power_state,
};

int __init plat_setup_psci_ops(uintptr_t sec_entrypoint,
							   const plat_psci_ops_t **psci_ops)
{
	plat_sec_entrypoint = sec_entrypoint;
	*psci_ops = &plat_rebel_h_psci_pm_ops;

	return 0;
}
