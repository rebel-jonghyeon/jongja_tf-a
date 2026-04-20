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

#pragma once

#include <rebel_h_platform.h>
#include "gic_spi_num.h"

#define GIC_INT_NUM 991
#define GIC_RDIST_BASE	(BLK_CP_GIC_RDIST_BASE)
#define GIC_DIST_BASE	(BLK_CP_GIC_DIST_BASE)

typedef void (*isr_handler)(void *data);
typedef struct {
	isr_handler isr;
	void *cb_ref;
} _isr_table;

/* SGI base is at 64K offset from Redistributor */
#define GICR_SGI_BASE_OFF       0x10000

/* Offsets from GICD base or GICR(n) SGI_base */
#define GIC_DIST_IGROUPR        0x0080
#define GIC_DIST_ISENABLER      0x0100
#define GIC_DIST_ICENABLER      0x0180
#define GIC_DIST_ISPENDR        0x0200
#define GIC_DIST_ICPENDR        0x0280
#define GIC_DIST_ISACTIVER      0x0300
#define GIC_DIST_ICACTIVER      0x0380
#define GIC_DIST_IPRIORITYR     0x0400
#define GIC_DIST_ITARGETSR      0x0800
#define GIC_DIST_ICFGR          0x0c00
#define GIC_DIST_IGROUPMODR     0x0d00
#define GIC_DIST_SGIR           0x0f00
#define GIC_DIST_IROUTER        0x6000

/* GICR registers offset from RD_base(n) */
#define GICR_CTLR           0x0000
#define GICR_IIDR           0x0004
#define GICR_TYPER          0x0008
#define GICR_STATUSR        0x0010
#define GICR_WAKER          0x0014

/* GICR registers offset from SGI base */
#define GICR_MISCSTATUSR    0xC000

/* GICD GICR common access macros */
#define IGROUPR(base, n)        (uint64_t)((base) + GIC_DIST_IGROUPR + (n) * 4)
#define ISENABLER(base, n)      (uint64_t)((base) + GIC_DIST_ISENABLER + (n) * 4)
#define ICENABLER(base, n)      (uint64_t)((base) + GIC_DIST_ICENABLER + (n) * 4)
#define ISPENDR(base, n)        (uint64_t)((base) + GIC_DIST_ISPENDR + (n) * 4)
#define ICPENDR(base, n)        (uint64_t)((base) + GIC_DIST_ICPENDR + (n) * 4)
#define IPRIORITYR(base, n)     (uint64_t)((base) + GIC_DIST_IPRIORITYR + (n))
#define ITARGETSR(base, n)      (uint64_t)((base) + GIC_DIST_ITARGETSR + (n) * 4)
#define ICFGR(base, n)          (uint64_t)((base) + GIC_DIST_ICFGR + (n) * 4)
#define IGROUPMODR(base, n)     (uint64_t)((base) + GIC_DIST_IGROUPMODR + (n) * 4)
#define IROUTER(base, n)        (uint64_t)((base) + GIC_DIST_IROUTER + (n) * 8)

/* GICD_CTLR Interrupt group definitions */
#define GICD_CTLR_ENABLE_G0     (0x1 << 0)
#define GICD_CTLR_ENABLE_G1NS   (0x1 << 1)
#define GICD_CTLR_ENABLE_G1S    (0x1 << 2)
#define GICD_CTLR_ARE_S         (0x1 << 4)
#define GICD_CTLR_ARE_NS        (0x1 << 5)
#define GICD_CTLR_ARE_NS_IN_NS  (0x1 << 4)
#define GICD_CTLR_NS            (0x1 << 6)
#define GICD_CTLR_E1NWF         (0x1 << 7)

/* GICD_CTLR Register write progress bit */
#define GICD_CTLR_RWP           31

/* GICR_CTLR */
#define GICR_CTLR_RWP           3

/* GICR_WAKER */
#define GICR_WAKER_PS           1
#define GICR_WAKER_CA           2

static const uint64_t GICD_CTLR        =  (GIC_DIST_BASE +   0x0);
static const uint64_t GICD_TYPER       =  (GIC_DIST_BASE +   0x4);
static const uint64_t GICD_IIDR        =  (GIC_DIST_BASE +   0x8);
static const uint64_t GICD_IGROUPRn    =  (GIC_DIST_BASE +  0x80);
static const uint64_t GICD_ISENABLERn  =  (GIC_DIST_BASE + 0x100);
static const uint64_t GICD_ICENABLERn  =  (GIC_DIST_BASE + 0x180);
static const uint64_t GICD_ISPENDRn    =  (GIC_DIST_BASE + 0x200);
static const uint64_t GICD_ICPENDRn    =  (GIC_DIST_BASE + 0x280);
static const uint64_t GICD_ISACTIVERn  =  (GIC_DIST_BASE + 0x300);
static const uint64_t GICD_ICACTIVERn  =  (GIC_DIST_BASE + 0x380);
static const uint64_t GICD_IPRIORITYRn =  (GIC_DIST_BASE + 0x400);
static const uint64_t GICD_ITARGETSRn  =  (GIC_DIST_BASE + 0x800);
static const uint64_t GICD_ICFGRn      =  (GIC_DIST_BASE + 0xc00);
static const uint64_t GICD_SGIR        =  (GIC_DIST_BASE + 0xf00);

#define GICD_ICFGR_MASK         BIT_MASK(2)
#define GICD_ICFGR_TYPE         BIT(1)
#define GICD_TYPER_ITLINESNUM_MASK  0x1f

#define GIC_SGI_INT_BASE        0
#define GIC_PPI_INT_BASE        16
#define GIC_IS_SGI(intid)       (((intid) >= GIC_SGI_INT_BASE) && ((intid) < GIC_PPI_INT_BASE))
#define GIC_SPI_INT_BASE        32
#define GIC_SPI_MAX_INTID       991
#define GIC_IS_SPI(intid)       (((intid) >= GIC_SPI_INT_BASE) && ((intid) <= GIC_SPI_MAX_INTID))
#define GIC_NUM_INTR_PER_REG    32
#define GIC_NUM_CFG_PER_REG     16
#define GIC_NUM_PRI_PER_REG     4
#define GIC_IDLE_PRIO           0xff
#define GIC_PRI_MASK            0xff
/* Kernel-independent Interrupt Priority */
#define GIC_PRI_0               0x00
#define GIC_PRI_2               0x20
#define GIC_PRI_4               0x40
#define GIC_PRI_6               0x60
#define GIC_PRI_8               0x80
#define GIC_PRI_9               0x90
#define GIC_PRI_DEF             0xC0
#define GIC_PRI_E               0xE0
#define GIC_INT_DEF_PRI_X4      0xa0a0a0a0
#define GIC_INTID_SPURIOUS      1023

#define GET_DIST_BASE(intid)    ((intid < GIC_SPI_INT_BASE) ? (gic_get_rdist() + GICR_SGI_BASE_OFF) : GIC_DIST_BASE)

#define IRQ_TYPE_LEVEL      BIT(1)
#define IRQ_TYPE_EDGE       BIT(2)

#define GIC_SPI         0x0
#define GIC_PPI         0x1

#define GIC_INT_VIRT_MAINT      25
#define GIC_INT_HYP_TIMER       26
#define GIC_INT_VIRT_TIMER      27
#define GIC_INT_LEGACY_FIQ      28
#define GIC_INT_PHYS_TIMER      29
#define GIC_INT_NS_PHYS_TIMER   30
#define GIC_INT_LEGACY_IRQ      31

int gic_init(void);
unsigned int gic_get_active(void);
void gic_eoi(unsigned int intid);
void gic_raise_sgi(unsigned int sgi_id, uint64_t target_aff, uint16_t target_list);
void gic_irq_route_dedicated_core(unsigned int core_id, unsigned int intid);
void gic_irq_enable(unsigned int intid);
void gic_irq_enable_dedicated_core(unsigned int core_id, unsigned int intid);
void gic_irq_disable(unsigned int intid);
void gic_irq_set_priority(unsigned int intid, unsigned int prio, uint32_t flags);
int gic_irq_is_enabled(unsigned int intid);
void gic_irq_connect(uint32_t intid, isr_handler isr_func, void *cb_ref);
uint32_t gic_in_isr(void);
