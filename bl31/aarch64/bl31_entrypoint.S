/*
 * Copyright (c) 2013-2025, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <platform_def.h>

#include <arch.h>
#include <common/bl_common.h>
#include <el3_common_macros.S>
#include <lib/pmf/aarch64/pmf_asm_macros.S>
#include <lib/runtime_instr.h>
#include <lib/xlat_tables/xlat_mmu_helpers.h>

	.globl	bl31_entrypoint
	.globl	bl31_warm_entrypoint
	.globl	bl31_coherent_area

	/* -----------------------------------------------------
	 * bl31_entrypoint() is the cold boot entrypoint,
	 * executed only by the primary cpu.
	 * -----------------------------------------------------
	 */

func bl31_entrypoint
	/* ---------------------------------------------------------------
	 * Stash the previous bootloader arguments x0 - x3 for later use.
	 * ---------------------------------------------------------------
	 */
	mov	x20, x0
	mov	x21, x1
	mov	x22, x2
	mov	x23, x3

	mov_imm	x0, (SCTLR_RESET_VAL | SCTLR_I_BIT & ~(SCTLR_EE_BIT | SCTLR_WXN_BIT \
			| SCTLR_SA_BIT | SCTLR_A_BIT | SCTLR_DSSBS_BIT))
	msr	sctlr_el3, x0
	isb

	/* set pointer, x6==tt base, x7== 512G trans table start */
	ldr x4, =__BASE_XLAT_TABLE_START__
	ldr x5, =__XLAT_TABLE_START__

	ldr x15, =bl31_coherent_area
	ldr x16, [x15]			/* PA */
	ldr x17, [x15, #8]		/* VA */
	ldr x18, [x15, #16]		/* SIZE */
	ldr x19, =__BL31_END__

	/* b . */

	/* x11 = chiplet id * 0x20_0000_0000 */
	/* chiplet id register = 0x1E00220444 */
	ldr x12, =0x1E00220444
	ldr w13, [x12]

	ldr x14, =3
	and x13, x13, x14
	ldr x14, =0x2000000000

	/* x11 = base addr for each chiplet */
	mul x11, x13, x14

	add x6, x4, x11
	add x7, x5, x11

	/* write 512G table desc = PA | 0x3 */
	orr x8, x7, #0x3
	str x8, [x6]

	adr x9, bl31_entrypoint
	and x9, x9, #0xF0000000
	cbnz x9, for_chiplet123
	cbnz x11, for_chiplet123
	/* b for_chiplet123 */

for_chiplet0:
	/* backup x7 */
	mov x10, x7

	/* write 1G table desc = PA | 0x3 */
	ldr x9, =0x1000
	add x8, x8, x9
	str x8, [x7]

	/* write 1G table desc(2M table location) for coherent area */
	lsr x3, x17, #30
	and x3, x3, #0x1FF
	cbz x3, skip_1g

	mov x1, x7
	mov x2, x7
	add x2, x2, #0x3000

	lsl x3, x3, #3
	add x1, x1, x3
	orr x2, x2, #3
	str x2, [x1]

	ldr x3, =0x1000
	b from_1g

skip_1g:
	ldr x3, =0x0000

from_1g:
	/* write 2M table desc = PA | 0x3 */
	add x8, x8, x9
	add x7, x7, x9
	str x8, [x7]

	/* write 2M block desc for coherent area & size */
	mov x1, x7
	mov x2, x7
	add x2, x2, x3

	lsr x3, x17, #21
	and x3, x3, #0x1FF
	lsl x3, x3, #3
	add x1, x2, x3	/* head addr to write block desc in 2M table */

	mov x2, x18		/* copy size */
	lsr x2, x2, #21	/* 2M unit = # of loop */

	and x6, x16, #0xffffffffffe00000
	add x6, x6, #0x449

_2m_loop:
	str x6, [x1]
	add x1, x1, #8			/* offset inc */
	add x6, x6, #0x200000	/* PA inc */
	sub x2, x2, #1			/* loops dec */
	cbnz x2, _2m_loop

_4k_loop:
	/* 4K table desc write as much as __BL31_END__ = x19 */
	ldr x6, =8
	lsr x19, x19, #12
	mov x8, x11
	add x8, x8, #0x443
	add x7, x7, x9

w_loop:
	str x8, [x7]
	add x8, x8, x9
	add x7, x7, x6
	sub x19, x19, #1
	cbnz x19, w_loop

	/* restore x7 for 1G table, set x10 */
	mov x7, x10

	b set_ip_area

for_chiplet123:
	/* write 1G block desc = PA | 0x441 */
	add x8, x11, #0x441
	str x8, [x7]

set_ip_area:
	ldr x10, =0x40000000

	/* 1G NC desc for IP, page table offset = 0x3c0, PA | 0x445 */
	/* Do not add the chiplet offset(0x20_0000_0000) to any private area, 1E_xxxx_xxxx */
	ldr x8, =0x1e00000445
	str x8, [x7, #0x3c0]

	/* Add 1G addr offset and write desc for IP */
	add x8, x8, x10
	str x8, [x7, #0x3c8]

	add x8, x8, x10
	str x8, [x7, #0x3d0]

	add x8, x8, x10
	str x8, [x7, #0x3d8]

	/* 1G NC desc for IP, page table offset = 0x3e0, PA | 0x445 */
	ldr x8, =0x1f00000445

	/* add chiplet offset to the area, 0x1F_xxxx_xxxx */
	add x8, x8, x11
	str x8, [x7, #0x3e0]

	add x8, x8, x10
	str x8, [x7, #0x3e8]

	add x8, x8, x10
	str x8, [x7, #0x3f0]

	add x8, x8, x10
	str x8, [x7, #0x3f8]

	mov x0, x13
	bl enable_mmu_direct_el3_bl31

#if !RESET_TO_BL31
	/* ---------------------------------------------------------------------
	 * For !RESET_TO_BL31 systems, only the primary CPU ever reaches
	 * bl31_entrypoint() during the cold boot flow, so the cold/warm boot
	 * and primary/secondary CPU logic should not be executed in this case.
	 *
	 * Also, assume that the previous bootloader has already initialised the
	 * SCTLR_EL3, including the endianness, and has initialised the memory.
	 * ---------------------------------------------------------------------
	 */
	el3_entrypoint_common					\
		_init_sctlr=0					\
		_warm_boot_mailbox=0				\
		_secondary_cold_boot=0				\
		_init_memory=0					\
		_init_c_runtime=1				\
		_exception_vectors=runtime_exceptions		\
		_pie_fixup_size=BL31_LIMIT - BL31_BASE
#else

	/* ---------------------------------------------------------------------
	 * For RESET_TO_BL31 systems which have a programmable reset address,
	 * bl31_entrypoint() is executed only on the cold boot path so we can
	 * skip the warm boot mailbox mechanism.
	 * ---------------------------------------------------------------------
	 */

	/* changed _init_sctlr=1 to 0 due to enabling MMU at the beginning */
	el3_entrypoint_common					\
		_init_sctlr=0					\
		_warm_boot_mailbox=!PROGRAMMABLE_RESET_ADDRESS	\
		_secondary_cold_boot=!COLD_BOOT_SINGLE_CPU	\
		_init_memory=1					\
		_init_c_runtime=1				\
		_exception_vectors=runtime_exceptions		\
		_pie_fixup_size=BL31_LIMIT - BL31_BASE

#endif /* RESET_TO_BL31 */

	/* --------------------------------------------------------------------
	 * Perform BL31 setup
	 * --------------------------------------------------------------------
	 */
	mov	x0, x20
	mov	x1, x21
	mov	x2, x22
	mov	x3, x23

	/* --------------------------------------------------------------------
	 * Jump to main function
	 * --------------------------------------------------------------------
	 */
	bl	bl31_main

	/* --------------------------------------------------------------------
	 * Clean the .data & .bss sections to main memory. This ensures
	 * that any global data which was initialised by the primary CPU
	 * is visible to secondary CPUs before they enable their data
	 * caches and participate in coherency.
	 * --------------------------------------------------------------------
	 */
	adrp	x0, __DATA_START__
	add	x0, x0, :lo12:__DATA_START__
	adrp	x1, __DATA_END__
	add	x1, x1, :lo12:__DATA_END__
	sub	x1, x1, x0
	bl	clean_dcache_range

	adrp	x0, __BSS_START__
	add	x0, x0, :lo12:__BSS_START__
	adrp	x1, __BSS_END__
	add	x1, x1, :lo12:__BSS_END__
	sub	x1, x1, x0
	bl	clean_dcache_range

	adrp	x0, __PER_CPU_START__
	add	x0, x0, :lo12:__PER_CPU_START__
	adrp	x1, __PER_CPU_END__
	add	x1, x1, :lo12:__PER_CPU_END__
	sub	x1, x1, x0
	bl	clean_dcache_range

#if (PLATFORM_NODE_COUNT > 1)
	/*
	 * dcache clean per-cpu sections defined by the platform.
	 * Care must be taken to preserve and retain the clobbered
	 * registers. A standard around the container for per-cpu nodes
	 * is not yet defined.
	 */

	bl	plat_per_cpu_dcache_clean
#endif /* (PLATFORM_NODE_COUNT > 1) */
	b	el3_exit
endfunc bl31_entrypoint

	/* --------------------------------------------------------------------
	 * This CPU has been physically powered up. It is either resuming from
	 * suspend or has simply been turned on. In both cases, call the BL31
	 * warmboot entrypoint
	 * --------------------------------------------------------------------
	 */
func bl31_warm_entrypoint
#if ENABLE_RUNTIME_INSTRUMENTATION

	/*
	 * This timestamp update happens with cache off.  The next
	 * timestamp collection will need to do cache maintenance prior
	 * to timestamp update.
	 */
	pmf_calc_timestamp_addr rt_instr_svc, RT_INSTR_EXIT_HW_LOW_PWR
	mrs	x1, cntpct_el0
	str	x1, [x0]
#endif

	/* NOTE: REBEL-H specific early MMU workaround */
	mov_imm	x0, (SCTLR_RESET_VAL | SCTLR_I_BIT & ~(SCTLR_EE_BIT | SCTLR_WXN_BIT \
			| SCTLR_SA_BIT | SCTLR_A_BIT | SCTLR_DSSBS_BIT))
	msr	sctlr_el3, x0
	isb

	/* set pointer, x6==tt base, x7== 512G trans table start */
	ldr x4, =__BASE_XLAT_TABLE_START__
	ldr x5, =__XLAT_TABLE_START__

	/* change x11 = 0x4000_0000 to x11 = chiplet id * 0x20_0000_0000 */
	/* chiplet id addr = 0x1E00220444 */
	ldr x12, =0x1E00220444
	ldr w13, [x12]

	ldr x14, =3
	and x13, x13, x14
	mov x0, x13
	bl enable_mmu_direct_el3_bl31

	/*
	 * On the warm boot path, most of the EL3 initialisations performed by
	 * 'el3_entrypoint_common' must be skipped:
	 *
	 *  - Only when the platform bypasses the BL1/BL31 entrypoint by
	 *    programming the reset address do we need to initialise SCTLR_EL3.
	 *    In other cases, we assume this has been taken care by the
	 *    entrypoint code.
	 *
	 *  - No need to determine the type of boot, we know it is a warm boot.
	 *
	 *  - Do not try to distinguish between primary and secondary CPUs, this
	 *    notion only exists for a cold boot.
	 *
	 *  - No need to initialise the memory or the C runtime environment,
	 *    it has been done once and for all on the cold boot path.
	 */
	el3_entrypoint_common					\
		_init_sctlr=0		\
		_warm_boot_mailbox=0				\
		_secondary_cold_boot=0				\
		_init_memory=0					\
		_init_c_runtime=0				\
		_exception_vectors=runtime_exceptions		\
		_pie_fixup_size=0

<<<<<<< HEAD
	/*
	 * We're about to enable MMU and participate in PSCI state coordination.
	 *
	 * The PSCI implementation invokes platform routines that enable CPUs to
	 * participate in coherency. On a system where CPUs are not
	 * cache-coherent without appropriate platform specific programming,
	 * having caches enabled until such time might lead to coherency issues
	 * (resulting from stale data getting speculatively fetched, among
	 * others). Therefore we keep data caches disabled even after enabling
	 * the MMU for such platforms.
	 *
	 * On systems with hardware-assisted coherency, or on single cluster
	 * platforms, such platform specific programming is not required to
	 * enter coherency (as CPUs already are); and there's no reason to have
	 * caches disabled either.
	 */
#if HW_ASSISTED_COHERENCY || WARMBOOT_ENABLE_DCACHE_EARLY
	mov	x0, xzr
#else
	mov	x0, #DISABLE_DCACHE
#endif

	/* NOTE: REBEL-H specific mmu is already enabled */
	/* bl	bl31_plat_enable_mmu */

#if ENABLE_RME
	/*
	 * At warm boot GPT data structures have already been initialized in RAM
	 * but the sysregs for this CPU need to be initialized. Note that the GPT
	 * accesses are controlled attributes in GPCCR and do not depend on the
	 * SCR_EL3.C bit.
	 */
	bl	gpt_enable
	cbz	x0, 1f
	no_ret plat_panic_handler
1:
#endif

#if ENABLE_PAUTH
	/* --------------------------------------------------------------------
	 * Program APIAKey_EL1 and enable pointer authentication
	 * --------------------------------------------------------------------
	 */
	bl	pauth_init_enable_el3
#endif /* ENABLE_PAUTH */

	bl	psci_warmboot_entrypoint
=======
	bl	bl31_warmboot
>>>>>>> upstream_import/upstream_v2_14_1

#if ENABLE_RUNTIME_INSTRUMENTATION
	pmf_calc_timestamp_addr rt_instr_svc, RT_INSTR_EXIT_PSCI
	mov	x19, x0

	/*
	 * Invalidate before updating timestamp to ensure previous timestamp
	 * updates on the same cache line with caches disabled are properly
	 * seen by the same core. Without the cache invalidate, the core might
	 * write into a stale cache line.
	 */
	mov	x1, #PMF_TS_SIZE
	mov	x20, x30
	bl	inv_dcache_range
	mov	x30, x20

	mrs	x0, cntpct_el0
	str	x0, [x19]
#endif

    mrs x0, actlr_el3
    orr x0, x0, #0x2
    msr actlr_el3, x0

    mrs x0, actlr_el2
    orr x0, x0, #0x2
    msr actlr_el2, x0

	b	el3_exit
endfunc bl31_warm_entrypoint
