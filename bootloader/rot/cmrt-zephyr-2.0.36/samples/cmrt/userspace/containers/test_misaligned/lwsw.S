    .globl lw
	.globl lw_c
	.globl lh
	.globl lhu
	.globl lwsp
	.globl sw
	.globl sw_c
	.globl sh
	.globl swsp

/* load word */
lw:
	/*
	 * The assembler can emit a compressed lw if the destination register
	 * is one of { s0, s1, a0 ... a5 }. By using t0 here, we make sure
	 * that a long instruction is used.
	 */

	beq a1, zero, lw_neg
	lw t0, 4(a0)
	j lw_ret
lw_neg:
	lw t0, -4(a0)
lw_ret:
	mv a0, t0
	ret

/* load word, compressed instruction */
lw_c:
	beq a1, zero, lw_c_neg
	lw a0, 4(a0)
	ret
lw_c_neg:
	addi a0, a0, -4
	lw a0, (a0)
	ret

/* load half-word signed */
lh:
	beq a1, zero, lh_neg
	lh a0, 4(a0)
	ret
lh_neg:
	lh a0, -4(a0)
	ret

/* load half-word unsigned */
lhu:
	beq a1, zero, lhu_neg
	lhu a0, 4(a0)
	ret
lhu_neg:
	lhu a0, -4(a0)
	ret

/* load word sp-relative, compressed instruction */
lwsp:
	/*
	 * Load word via sp and restore sp.
	 */
	mv t0, sp
	mv sp, a0
	beq a1, zero, lwsp_neg
	lw a0, 4(sp)
	j lwsp_ret
lwsp_neg:
	addi sp, sp, -4
	lw a0, (sp)
lwsp_ret:
	mv sp, t0
	ret

/* store word */
sw:
	/*
	 * The assembler can emit a compressed sw if the source register
	 * is one of { s0, s1, a0 ... a5 }. By using t0 here, we make sure
	 * that a long instruction is used.
	 */
	mv t0, a1
	beq a2, zero, sw_neg
	sw t0, 4(a0)
	ret
sw_neg:
	sw t0, -4(a0)
	ret

/* store word, compressed instruction */
sw_c:
	beq a2, zero, sw_c_neg
	sw a1, 4(a0)
	ret
sw_c_neg:
	addi a0, a0, -4
	sw a1, (a0)
	ret

/* store half-word */
sh:
	beq a2, zero, sh_neg
	sh a1, 4(a0)
	ret
sh_neg:
	sh a1, -4(a0)
	ret

/* store word sp-relative, compressed instruction */
swsp:
	/*
	 * Store word via sp and restore sp.
	 */
	mv t0, sp
	mv sp, a0
	beq a2, zero, swsp_neg
	sw a1, 4(sp)
	j swsp_ret
swsp_neg:
	addi sp, sp, -4
	sw a1, (sp)
swsp_ret:
	mv sp, t0
	ret
