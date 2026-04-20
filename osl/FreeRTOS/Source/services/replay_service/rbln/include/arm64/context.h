/*
 * Copyright (c) 2013-2021, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CONTEXT_H
#define CONTEXT_H

#include "rbln/utils_define.h"

/*******************************************************************************
 * Constants that allow assembler code to access members of and the 'gp_regs'
 * structure at their correct offsets.
 ******************************************************************************/
#define CTX_GPREGS_OFFSET	U(0x0)
#define CTX_GPREG_X0		U(0x0)
#define CTX_GPREG_X1		U(0x8)
#define CTX_GPREG_X2		U(0x10)
#define CTX_GPREG_X3		U(0x18)
#define CTX_GPREG_X4		U(0x20)
#define CTX_GPREG_X5		U(0x28)
#define CTX_GPREG_X6		U(0x30)
#define CTX_GPREG_X7		U(0x38)
#define CTX_GPREG_X8		U(0x40)
#define CTX_GPREG_X9		U(0x48)
#define CTX_GPREG_X10		U(0x50)
#define CTX_GPREG_X11		U(0x58)
#define CTX_GPREG_X12		U(0x60)
#define CTX_GPREG_X13		U(0x68)
#define CTX_GPREG_X14		U(0x70)
#define CTX_GPREG_X15		U(0x78)
#define CTX_GPREG_X16		U(0x80)
#define CTX_GPREG_X17		U(0x88)
#define CTX_GPREG_X18		U(0x90)
#define CTX_GPREG_X19		U(0x98)
#define CTX_GPREG_X20		U(0xa0)
#define CTX_GPREG_X21		U(0xa8)
#define CTX_GPREG_X22		U(0xb0)
#define CTX_GPREG_X23		U(0xb8)
#define CTX_GPREG_X24		U(0xc0)
#define CTX_GPREG_X25		U(0xc8)
#define CTX_GPREG_X26		U(0xd0)
#define CTX_GPREG_X27		U(0xd8)
#define CTX_GPREG_X28		U(0xe0)
#define CTX_GPREG_X29		U(0xe8)
#define CTX_GPREG_LR		U(0xf0)
#define CTX_GPREG_SP_EL0	U(0xf8)
#define CTX_GPREGS_END		U(0x100)

/*******************************************************************************
 * Constants that allow assembler code to access members of and the 'el_state'
 * structure at their correct offsets. Note that some of the registers are only
 * 32-bits wide but are stored as 64-bit values for convenience
 ******************************************************************************/
#define CTX_ELSTATE_OFFSET (CTX_GPREGS_OFFSET + CTX_GPREGS_END)
#define CTX_ESR_EL         U(0x0)
#define CTX_FAR_EL         U(0x8)
#define CTX_SCR_EL3        U(0x10)
#define CTX_SPSR_EL        U(0x18)
#define CTX_ELR_EL         U(0x20)
#define CTX_RUNTIME_SP     U(0x28)
#define CTX_CURRENT_EL     U(0x30)
#define CTX_CPSR_EL        U(0x38)
#define CTX_ELSTATE_END    U(0x40) /* Align to the next 16 byte boundary */


/* FPU registers */
#define CTX_FPUREGS_OFFSET	(CTX_ELSTATE_OFFSET + CTX_ELSTATE_END)
#define CTX_FPUREG_Q0		U(0x0)
#define CTX_FPUREG_Q2		U(0x20)
#define CTX_FPUREG_Q4		U(0x40)
#define CTX_FPUREG_Q6		U(0x40)
#define CTX_FPUREG_Q8		U(0x60)
#define CTX_FPUREG_Q10		U(0x80)
#define CTX_FPUREG_Q12		U(0xA0)
#define CTX_FPUREG_Q14		U(0xC0)
#define CTX_FPUREG_Q16		U(0xE0)
#define CTX_FPUREG_Q18		U(0x100)
#define CTX_FPUREG_Q20		U(0x120)
#define CTX_FPUREG_Q22		U(0x140)
#define CTX_FPUREG_Q24		U(0x160)
#define CTX_FPUREG_Q26		U(0x180)
#define CTX_FPUREG_Q28		U(0x1A0)
#define CTX_FPUREG_Q30		U(0x1C0)
#define CTX_FPUREGS_END		U(0x1E0)
#endif
