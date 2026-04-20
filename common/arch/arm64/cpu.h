#pragma once

#include "util.h"

/* DAIF */
#define DAIFSET_FIQ_BIT     BIT(0)
#define DAIFSET_IRQ_BIT     BIT(1)
#define DAIFCLR_FIQ_BIT     BIT(0)
#define DAIFCLR_IRQ_BIT     BIT(1)

#define sev()   __asm__ volatile("sev" : : : "memory")
#define wfe()   __asm__ volatile("wfe" : : : "memory")
#define wfi()   __asm__ volatile("wfi" : : : "memory")
#define nop()   __asm__ volatile("nop" : : : "memory")

/* Barrier */
#define dsb()   __asm__ volatile ("dsb sy" ::: "memory")
#define dmb()   __asm__ volatile ("dmb sy" ::: "memory")
#define isb()   __asm__ volatile ("isb" ::: "memory")

#define __ISB() isb()
#define __DMB() dmb()
#define __DSB() dsb()

/* Generic timer */
#define CNTV_CTL_ENABLE_BIT BIT(0)
#define CNTV_CTL_IMASK_BIT  BIT(1)
#define CNTP_CTL_ENABLE_BIT BIT(0)
#define CNTP_CTL_IMASK_BIT  BIT(1)

/* Generic timer interrupt */
#define CNTHVSIRQ (19U) /* S.EL2 not implemented but ARM v9 */
#define CNTHPSIRQ (20U) /* S.EL2 not implemented but ARM v9 */
#define CNTHPIRQ  (26U) /* NS.EL2 */
#define CNTVIRQ   (27U) /* EL0, EL1 */
#define CNTHVIRQ  (28U) /* NS.EL2 */
#define CNTPSIRQ  (29U) /* S.EL1, EL3 */
#define CNTPIRQ   (30U) /* EL0, EL1 */

/* System register interface to GICv3 */
#define ICC_IGRPEN1_EL1     S3_0_C12_C12_7
#define ICC_SGI1R       S3_0_C12_C11_5
#define ICC_SRE_EL1     S3_0_C12_C12_5
#define ICC_SRE_EL2     S3_4_C12_C9_5
#define ICC_SRE_EL3     S3_6_C12_C12_5
#define ICC_CTLR_EL1        S3_0_C12_C12_4
#define ICC_CTLR_EL3        S3_6_C12_C12_4
#define ICC_PMR_EL1     S3_0_C4_C6_0
#define ICC_RPR_EL1     S3_0_C12_C11_3
#define ICC_IGRPEN1_EL3     S3_6_C12_C12_7
#define ICC_IGRPEN0_EL1     S3_0_C12_C12_6
#define ICC_HPPIR0_EL1      S3_0_C12_C8_2
#define ICC_HPPIR1_EL1      S3_0_C12_C12_2
#define ICC_IAR0_EL1        S3_0_C12_C8_0
#define ICC_IAR1_EL1        S3_0_C12_C12_0
#define ICC_EOIR0_EL1       S3_0_C12_C8_1
#define ICC_EOIR1_EL1       S3_0_C12_C12_1
#define ICC_SGI0R_EL1       S3_0_C12_C11_7
#define ICC_BPR0_EL1        S3_0_C12_C8_3
#define ICC_BPR1_EL1        S3_0_C12_C12_3

/* register constants */
#define ICC_SRE_ELx_SRE_BIT BIT(0)
#define ICC_SRE_ELx_DFB_BIT BIT(1)
#define ICC_SRE_ELx_DIB_BIT BIT(2)
#define ICC_SRE_EL3_EN_BIT  BIT(3)

/* ICC SGI macros */
#define SGIR_TGT_MASK       (0xffff)
#define SGIR_AFF1_SHIFT     (16)
#define SGIR_AFF2_SHIFT     (32)
#define SGIR_AFF3_SHIFT     (48)
#define SGIR_AFF_MASK       (0xf)
#define SGIR_INTID_SHIFT    (24)
#define SGIR_INTID_MASK     (0xf)
#define SGIR_IRM_SHIFT      (40)
#define SGIR_IRM_MASK       (0x1)
#define SGIR_IRM_TO_AFF     (0)

#define GICV3_SGIR_VALUE(_aff3, _aff2, _aff1, _intid, _irm, _tgt)   \
	((((uint64_t) (_aff3) & SGIR_AFF_MASK) << SGIR_AFF3_SHIFT) |    \
	 (((uint64_t) (_irm) & SGIR_IRM_MASK) << SGIR_IRM_SHIFT) |  \
	 (((uint64_t) (_aff2) & SGIR_AFF_MASK) << SGIR_AFF2_SHIFT) |    \
	 (((_intid) & SGIR_INTID_MASK) << SGIR_INTID_SHIFT) |       \
	 (((_aff1) & SGIR_AFF_MASK) << SGIR_AFF1_SHIFT) |       \
	 ((_tgt) & SGIR_TGT_MASK))

/* MPIDR */
#define MPIDR_AFFLVL_MASK   (0xffULL)
#define MPIDR_AFF0_SHIFT    (0)
#define MPIDR_AFF1_SHIFT    (8)
#define MPIDR_AFF2_SHIFT    (16)
#define MPIDR_AFF3_SHIFT    (32)

#define MPIDR_AFF_MASK      (GENMASK(23, 0) | GENMASK(39, 32))
#define MPIDR_AFFLVL(mpidr, aff_level) \
	(((mpidr) >> MPIDR_AFF##aff_level##_SHIFT) & MPIDR_AFFLVL_MASK)

/* SCTLR */
#define SCTLR_M_BIT     1 << 0
#define SCTLR_A_BIT     1 << 1
#define SCTLR_C_BIT     1 << 2


static inline void enable_irq(void)
{
	__asm__ volatile ("msr DAIFClr, %0"
			  :: "i" (DAIFCLR_IRQ_BIT) : "memory");
}

static inline void disable_irq(void)
{
	__asm__ volatile ("msr DAIFSet, %0"
			  :: "i" (DAIFSET_IRQ_BIT) : "memory");
}

static inline void enable_fiq(void)
{
	__asm__ volatile ("msr DAIFClr, %0"
			  :: "i" (DAIFCLR_FIQ_BIT) : "memory");
}

static inline void disable_fiq(void)
{
	__asm__ volatile ("msr DAIFSet, %0"
			  :: "i" (DAIFSET_FIQ_BIT) : "memory");
}

static inline uint64_t get_current_cpuid(void)
{
	uint64_t cpu;

	__asm__ volatile ("mrs %[r], mpidr_el1" : [r] "=r" (cpu));

	return cpu & 0x0000000f;
}
