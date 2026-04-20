#include "arm64/context.h"
#include "asm_macros.S"

#define IMAGE_INFO_MAGIC0	0x4F494C4C45424552
#define IMAGE_INFO_MAGIC1	0x49412E534E
#define IMAGE_INFO_VERSION	1

.global save_gp_regs
.global restore_gp_regs
.global dump_gp_regs
.global dump_state_regs_el3
.global dump_state_regs_el1
.global save_fpu_regs
.global restore_fpu_regs

/* ------------------------------------------------------------------
 * The following function is used to save and restore all the general
 * purpose registers.
 *
 * Ideally we would only save and restore the callee saved registers
 * when a world switch occurs but that type of implementation is more
 * complex. So currently we will always save and restore these
 * registers on entry and exit of EL3.
 * These are not macros to ensure their invocation fits within the 32
 * instructions per exception vector.
 * ------------------------------------------------------------------
 */
func save_gp_regs
	stp	x0, x1, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X0]
	stp	x2, x3, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X2]
	stp	x4, x5, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X4]
	stp	x6, x7, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X6]
	stp	x8, x9, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X8]
	stp	x10, x11, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X10]
	stp	x12, x13, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X12]
	stp	x14, x15, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X14]
	stp	x16, x17, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X16]
	stp	x18, x19, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X18]
	stp	x20, x21, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X20]
	stp	x22, x23, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X22]
	stp	x24, x25, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X24]
	stp	x26, x27, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X26]
	stp	x28, x29, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X28]
	ret
endfunc save_gp_regs

/* ------------------------------------------------------------------
 * This function restores all general purpose registers
 * except x30 from the CPU context.
 * x30 register must be explicitly restored by the caller.
 * ------------------------------------------------------------------
 */
func restore_gp_regs
	ldp	x0, x1, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X0]
	ldp	x2, x3, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X2]
	ldp	x4, x5, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X4]
	ldp	x6, x7, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X6]
	ldp	x8, x9, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X8]
	ldp	x10, x11, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X10]
	ldp	x12, x13, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X12]
	ldp	x14, x15, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X14]
	ldp	x16, x17, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X16]
	ldp	x18, x19, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X18]
	ldp	x20, x21, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X20]
	ldp	x22, x23, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X22]
	ldp	x24, x25, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X24]
	ldp	x26, x27, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X26]
	ldp	x28, x29, [sp, #CTX_GPREGS_OFFSET + CTX_GPREG_X28]
	ret
endfunc restore_gp_regs

func dump_gp_regs
	stp	x2, x3, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X2]
	stp	x4, x5, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X4]
	stp	x6, x7, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X6]
	stp	x8, x9, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X8]
	stp	x10, x11, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X10]
	stp	x12, x13, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X12]
	stp	x14, x15, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X14]
	stp	x16, x17, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X16]
	stp	x18, x19, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X18]
	stp	x20, x21, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X20]
	stp	x22, x23, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X22]
	stp	x24, x25, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X24]
	stp	x26, x27, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X26]
	stp	x28, x29, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_X28]
	mrs x2, SPSel
	cbnz x2, 1f
	mov x28, sp
	b 2f
1:
	mrs x28, sp_el0
2:
	stp	x30, x28, [x0, #CTX_GPREGS_OFFSET + CTX_GPREG_LR]
	ret
endfunc dump_gp_regs

func save_fpu_regs
	stp q0, q1, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q0]
	stp q2, q3, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q2]
	stp q4, q5, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q4]
	stp q6, q7, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q6]
	stp q8, q9, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q8]
	stp q10, q11, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q10]
	stp q12, q13, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q12]
	stp q14, q15, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q14]
	stp q16, q17, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q16]
	stp q18, q19, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q18]
	stp q20, q21, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q20]
	stp q22, q23, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q22]
	stp q24, q25, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q24]
	stp q26, q27, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q26]
	stp q28, q29, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q28]
	stp q30, q31, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q30]
	ret
endfunc save_fpu_regs

func restore_fpu_regs
	ldp q0, q1, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q0]
	ldp q2, q3, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q2]
	ldp q4, q5, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q4]
	ldp q6, q7, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q6]
	ldp q8, q9, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q8]
	ldp q10, q11, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q10]
	ldp q12, q13, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q12]
	ldp q14, q15, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q14]
	ldp q16, q17, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q16]
	ldp q18, q19, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q18]
	ldp q20, q21, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q20]
	ldp q22, q23, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q22]
	ldp q24, q25, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q24]
	ldp q26, q27, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q26]
	ldp q28, q29, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q28]
	ldp q30, q31, [sp, #CTX_FPUREGS_OFFSET + CTX_FPUREG_Q30]
	ret
endfunc restore_fpu_regs

.macro define_dump_state_regs el
func dump_state_regs\()_el\el
	_mrs x0, esr ,\el
	_mrs x1, far ,\el

	.if \el == 3
	_mrs x2, scr ,\el
	.else
	mov x2, #0
	.endif

	_mrs x3, spsr ,\el
	_mrs x4, elr ,\el
	mov  x5, sp
	mov  x6, \el

	/* Make CPSR using NZCV, SPSel, DAIF, currentEL registers. */
	mrs x9, NZCV
	mrs x10, SPSel
	mrs x11, DAIF
	mrs x12, CurrentEL
	orr x9, x9, x10
	orr x9, x9, x11
	orr x9, x9, x12

	_mrs x8, tpidr, \el
	stp x0, x1, [x8, #CTX_ELSTATE_OFFSET + CTX_ESR_EL]
	stp x2, x3, [x8, #CTX_ELSTATE_OFFSET + CTX_SCR_EL3]
	stp x4, x5, [x8, #CTX_ELSTATE_OFFSET + CTX_ELR_EL]
	stp x6, xzr, [x8, #CTX_ELSTATE_OFFSET + CTX_CURRENT_EL]
	str x9, [x8, #CTX_ELSTATE_OFFSET + CTX_CPSR_EL]

	ldr x1, =IMAGE_INFO_MAGIC0
	ldr x2, =IMAGE_INFO_MAGIC1
	stp x1, x2, [x8, #CTX_ELSTATE_OFFSET + CTX_ELSTATE_END]

	ret
endfunc dump_state_regs\()_el\el
.endm

define_dump_state_regs 1
define_dump_state_regs 3
