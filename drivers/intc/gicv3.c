/*
 * Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
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

#include <util.h>
#include "gic.h"
#include "cpu.h"
#include <driver.h>
#include <assert.h>
#include "FreeRTOSConfig.h"
#include <bakery_lock.h>

#define IGROUPR_VAL 0xFFFFFFFFU
#define IGRPMODR_VAL 0x0U
#define RDIST_OFFEST_PER_CPU    0x20000

#ifndef portGET_CORE_ID
#define portGET_CORE_ID() get_current_cpuid()
#endif

mem_addr_t gic_rdists[configNUMBER_OF_CORES];
_isr_table isr_table[GIC_INT_NUM] = {0};

extern uint32_t isr_flag[];

static inline mem_addr_t gic_get_rdist(void)
{
	return gic_rdists[portGET_CORE_ID()];
}

static int gic_wait_rwp(uint32_t intid)
{
	uint32_t rwp_mask;
	mem_addr_t base;

	if (intid < GIC_SPI_INT_BASE) {
		base = (gic_get_rdist() + GICR_CTLR);
		rwp_mask = BIT(GICR_CTLR_RWP);
	} else {
		base = GICD_CTLR;
		rwp_mask = BIT(GICD_CTLR_RWP);
	}

	while (sys_read32(base) & rwp_mask)
		;

	return 0;
}

unsigned int gic_get_active(void)
{
	int intid;

	__asm__ volatile ("mrs %[r], S3_0_C12_C12_0" : [r] "=r" (intid));

	return intid;
}

void gic_eoi(unsigned int intid)
{
	__DSB();

	__asm__ volatile ("msr S3_0_C12_C12_1, %[i]" :: [i] "r" (intid));
}

void gic_raise_sgi(unsigned int sgi_id, uint64_t target_aff, uint16_t target_list)
{
	uint32_t aff3, aff2, aff1;
	uint64_t sgi_val;

#if (__TARGET_CP == 1)
	target_aff |= 0x100;
#endif

	aff1 = MPIDR_AFFLVL(target_aff, 1);
	aff2 = MPIDR_AFFLVL(target_aff, 2);
	aff3 = MPIDR_AFFLVL(target_aff, 3);
	sgi_val = GICV3_SGIR_VALUE(aff3, aff2, aff1, sgi_id, SGIR_IRM_TO_AFF, target_list);

	dsb();
	__asm__ volatile ("msr S3_0_C12_C11_5, %[i]" :: [i] "r" (sgi_val));
	isb();
}

void gic_irq_set_priority(unsigned int intid, unsigned int prio, uint32_t flags)
{
	uint32_t mask = BIT(intid & (GIC_NUM_INTR_PER_REG - 1));
	uint32_t idx = intid / GIC_NUM_INTR_PER_REG;
	uint32_t shift;
	uint32_t val;

	mem_addr_t base = GET_DIST_BASE(intid);

	sys_write32(mask, ICENABLER(base, idx));
	gic_wait_rwp(intid);

	sys_write8(prio & GIC_PRI_MASK, IPRIORITYR(base, intid));

	if (!GIC_IS_SGI(intid)) {
		idx = intid / GIC_NUM_CFG_PER_REG;
		shift = (intid & (GIC_NUM_CFG_PER_REG - 1)) * 2;

		val = sys_read32(ICFGR(base, idx));
		val &= ~(GICD_ICFGR_MASK << shift);

		if (flags & IRQ_TYPE_EDGE) {
			val |= (GICD_ICFGR_TYPE << shift);
		}
		sys_write32(val, ICFGR(base, idx));
	}
}

void gic_irq_route_dedicated_core(unsigned int core_id, unsigned int intid)
{
	if (GIC_IS_SPI(intid)) {
#if (__TARGET_CP == 1)
		sys_write64(0x100U | core_id, IROUTER(GET_DIST_BASE(intid), intid));
#else
		sys_write64(core_id, IROUTER(GET_DIST_BASE(intid), intid));
#endif
		gic_wait_rwp(intid);
	}
}

void gic_irq_enable(unsigned int intid)
{
	uint32_t mask = BIT(intid & (GIC_NUM_INTR_PER_REG - 1));
	uint32_t idx = intid / GIC_NUM_INTR_PER_REG;

	sys_write32(mask, ISENABLER(GET_DIST_BASE(intid), idx));
}

void gic_irq_enable_dedicated_core(unsigned int core_id, unsigned int intid)
{
	gic_irq_route_dedicated_core(core_id, intid);

	gic_irq_enable(intid);
}

void gic_irq_disable(unsigned int intid)
{
	uint32_t mask = BIT(intid & (GIC_NUM_INTR_PER_REG - 1));
	uint32_t idx = intid / GIC_NUM_INTR_PER_REG;

	sys_write32(mask, ICENABLER(GET_DIST_BASE(intid), idx));
	gic_wait_rwp(intid);
}

int gic_irq_is_enabled(unsigned int intid)
{
	uint32_t mask = BIT(intid & (GIC_NUM_INTR_PER_REG - 1));
	uint32_t idx = intid / GIC_NUM_INTR_PER_REG;
	uint32_t val;

	val = sys_read32(ISENABLER(GET_DIST_BASE(intid), idx));

	return (val & mask) != 0;
}

void gic_irq_connect(uint32_t intid, isr_handler callback, void *cb_ref)
{
	isr_table[intid].isr = callback;
	isr_table[intid].cb_ref = cb_ref;
}

void cpuif_init(void)
{
	uint32_t icc_sre;
	uint32_t intid;

	mem_addr_t base = gic_get_rdist() + GICR_SGI_BASE_OFF;

	/* Disable all sgi ppi */
	sys_write32(BIT_MASK(GIC_NUM_INTR_PER_REG), ICENABLER(base, 0));
	/* Any sgi/ppi intid ie. 0-31 will select GICR_CTRL */
	gic_wait_rwp(0);

	/* Clear pending */
	sys_write32(BIT_MASK(GIC_NUM_INTR_PER_REG), ICPENDR(base, 0));

	/* Configure all SGIs/PPIs as G1S or G1NS depending on Zephyr
	 * is run in EL1S or EL1NS respectively.
	 * All interrupts will be delivered as irq
	 */
//	sys_write32(IGROUPR_VAL, IGROUPR(base, 0));
//	sys_write32(IGRPMODR_VAL, IGROUPMODR(base, 0));

	/*
	 * Configure default priorities for SGI 0:15 and PPI 0:15.
	 */
	for (intid = 0; intid < GIC_SPI_INT_BASE;
			intid += GIC_NUM_PRI_PER_REG) {
		sys_write32(GIC_INT_DEF_PRI_X4, IPRIORITYR(base, intid));
	}

	/* Configure PPIs as level triggered */
	sys_write32(0, ICFGR(base, 1));
	gic_wait_rwp(0);

	/*
	 * Check if system interface can be enabled.
	 * 'icc_sre_el3' needs to be configured at 'EL3'
	 * to allow access to 'icc_sre_el1' at 'EL1'
	 * eg: z_arch_el3_plat_init can be used by platform.
	 */

	__asm__ volatile ("mrs %[r], S3_0_C12_C12_5" : [r] "=r" (icc_sre));

	if (!(icc_sre & ICC_SRE_ELx_SRE_BIT)) {
		icc_sre = (icc_sre | ICC_SRE_ELx_SRE_BIT |
				ICC_SRE_ELx_DIB_BIT | ICC_SRE_ELx_DFB_BIT);
		__asm__ volatile ("msr S3_0_C12_C12_5, %[i]" :: [i] "r" (icc_sre));
	}

	__asm__ volatile ("msr S3_0_C4_C6_0, %[i]" :: [i] "r" (GIC_IDLE_PRIO));

	__asm__ volatile ("msr S3_0_C12_C12_7, %[i]" :: [i] "r" (icc_sre));
}

void rdist_init(uint64_t rdist)
{
	uint32_t val;

	if (!(sys_read32(rdist + GICR_WAKER) & BIT(GICR_WAKER_CA)))
		return;

	val = sys_read32(rdist + GICR_WAKER);
	val &= ~(BIT(GICR_WAKER_PS));
	sys_write32(val, rdist + GICR_WAKER);
	sys_clear_bit(rdist + GICR_WAKER, GICR_WAKER_PS);
	while (sys_read32(rdist + GICR_WAKER) & BIT(GICR_WAKER_CA))
		;
}

void dist_init(void)
{
	unsigned int num_ints;
	unsigned int intid;
	unsigned int idx;
	unsigned int val;
	mem_addr_t base = GIC_DIST_BASE;

	num_ints = sys_read32(GICD_TYPER) & GICD_TYPER_ITLINESNUM_MASK;
	num_ints = (num_ints + 1) << 5;

	/* Disable the distributor */
	sys_write32(0, GICD_CTLR);
	gic_wait_rwp(GIC_SPI_INT_BASE);

	/*
	 * Default configuration of all SPIs
	 */
	for (intid = GIC_SPI_INT_BASE; intid < num_ints; intid += GIC_NUM_INTR_PER_REG) {
		idx = intid / GIC_NUM_INTR_PER_REG;
		/* Disable interrupt */
		sys_write32(BIT_MASK(GIC_NUM_INTR_PER_REG), ICENABLER(base, idx));
		/* Clear pending */
		sys_write32(BIT_MASK(GIC_NUM_INTR_PER_REG), ICPENDR(base, idx));
//		sys_write32(IGROUPR_VAL, IGROUPR(base, idx));
//		sys_write32(IGRPMODR_VAL, IGROUPMODR(base, idx));
	}

	for (intid = GIC_SPI_INT_BASE; intid < num_ints; intid++) {
		/* Route all SPI to cpu0 */
		sys_write32((0U << 31) | (0U << 16) | (0U << 8) | (0U << 0), IROUTER(base, intid));
		/* IRQ, aff2, aff1, aff0 */
		sys_write32(0U, IROUTER(base, intid) + 4);
		/* aff3 */
	}

	/* Configure default priorities for all SPIs. */
	for (intid = GIC_SPI_INT_BASE; intid < num_ints;
			intid += GIC_NUM_PRI_PER_REG) {
		sys_write32(GIC_INT_DEF_PRI_X4, IPRIORITYR(base, intid));
	}

	/* Configure all SPIs as active low, level triggered by default */
	for (intid = GIC_SPI_INT_BASE; intid < num_ints;
			intid += GIC_NUM_CFG_PER_REG) {
		idx = intid / GIC_NUM_CFG_PER_REG;
		sys_write32(0, ICFGR(base, idx));
	}

	/* wait for rwp on GICD */
	gic_wait_rwp(GIC_SPI_INT_BASE);

	/* enable Group 1 Non-secure interrupts */
	val = sys_read32(GICD_CTLR);
	val |= GICD_CTLR_ARE_NS_IN_NS;

	sys_write32(val, GICD_CTLR);

	/* wait for rwp on GICD */
	gic_wait_rwp(GIC_SPI_INT_BASE);

	val = sys_read32(GICD_CTLR);
	val |= GICD_CTLR_ENABLE_G1NS;
	sys_write32(val, GICD_CTLR);

	/* wait for rwp on GICD */
	gic_wait_rwp(GIC_SPI_INT_BASE);
}

uint32_t gic_in_isr(void)
{
	return isr_flag[portGET_CORE_ID()] == 0 ? 0 : 1;
}

int gic_init(void)
{
	uint8_t core_id = portGET_CORE_ID();
	mem_addr_t base;
	uint32_t val;

#ifndef ZEBU_POC
#if (__TARGET_CP == 0)
	rebel_bakery_lock_acquire(BAKERY_ID_CP0);
#elif (__TARGET_CP == 1)
	rebel_bakery_lock_acquire(BAKERY_ID_CP1);
#endif
#endif /* ZEBU_POC */

#if (__TARGET_CP == 0)
	/**
	 * Check GICR_MISCSTATUSR of CP1[0]
	 * GICRsgi0_GICR0_MISCSTATUSR	0x1F_F385_C000
	 * GICRsgi1_GICR1_MISCSTATUSR	0x1F_F387_C000
	 * GICRsgi2_GICR2_MISCSTATUSR	0x1F_F389_C000
	 * GICRsgi3_GICR3_MISCSTATUSR	0x1F_F38B_C000
	 */
	base = GIC_DIST_BASE + 0x40000ULL + (4 * RDIST_OFFEST_PER_CPU)
			 + GICR_SGI_BASE_OFF + GICR_MISCSTATUSR;
	val = sys_read32(base);
#elif (__TARGET_CP == 1)
	/**
	 * Check GICR_MISCSTATUSR of CP0[0]
	 * GICRsgi4_GICR4_MISCSTATUSR	0x1F_F38D_C000
	 * GICRsgi5_GICR5_MISCSTATUSR	0x1F_F38F_C000
	 * GICRsgi6_GICR6_MISCSTATUSR	0x1F_F391_C000
	 * GICRsgi7_GICR7_MISCSTATUSR	0x1F_F393_C000
	 */
	base = GIC_DIST_BASE + 0x40000ULL + GICR_SGI_BASE_OFF + GICR_MISCSTATUSR;
	val = sys_read32(base);
#endif

	if (core_id == 0 && (val & 0x7) == 0x0) {
		dist_init();
	}

	gic_rdists[core_id] = GIC_RDIST_BASE + (core_id * RDIST_OFFEST_PER_CPU);

	rdist_init(gic_rdists[core_id]);

	cpuif_init();

#ifndef ZEBU_POC
#if (__TARGET_CP == 0)
	rebel_bakery_lock_release(BAKERY_ID_CP0);
#elif (__TARGET_CP == 1)
	rebel_bakery_lock_release(BAKERY_ID_CP1);
#endif
#endif /* ZEBU_POC */

	return 0;
}

#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(0, gic_init);
#endif
