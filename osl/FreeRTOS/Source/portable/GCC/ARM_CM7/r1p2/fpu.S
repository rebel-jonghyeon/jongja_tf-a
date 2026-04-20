/* Copyright 2024 Samsung Electronics Co., Ltd All Rights Reserved */

	.syntax unified
	.arch armv7e-m

	.section .text
	.global fpu_enable
	.type fpu_enable, %function
fpu_enable:
	ldr.w r0, =0xE000ED88
	ldr r1, [r0]

	orr r1, r1, #(0xf << 20)
	str r1, [r0]
	bx lr

.end
