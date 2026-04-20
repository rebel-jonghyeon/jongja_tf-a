/* Copyright 2024 Samsung Electronics Co., Ltd All Rights Reserved */

	.syntax unified
	.arch   armv7e-m

	.global _vector_table

	.equ STACK_TOP,					_stack_top
	.equ ADDR_NMI_HANDLER,			_temp_nmi_handler
	.equ ADDR_HARD_FAULT_HANDLER,	_temp_hard_fault_handler
	.equ ADDR_MEM_FAULT_HANDLER,	_temp_mem_fault_handler
	.equ ADDR_BUS_FAULT_HANDLER,	_temp_bus_fault_handler
	.equ ADDR_USAGE_FAULT_HANDLER,	_temp_usage_fault_handler
	.equ ADDR_RSV0_HANDLER,			_temp_exception_handler		/* Exception number 8 */
	.equ ADDR_RSV1_HANDLER,			_temp_exception_handler		/* Exception number 9 */
	.equ ADDR_RSV2_HANDLER,			_temp_exception_handler		/* Exception number 10 */
	.equ ADDR_RSV3_HANDLER,			_temp_exception_handler		/* Exception number 11 */
	.equ ADDR_DEBUG_MON_HANDLER,	_temp_exception_handler
	.equ ADDR_RSV4_HANDLER,			_temp_exception_handler

	.section .vector
_vector_table:
	.word STACK_TOP
	.word _start + 1				/* Start address of Code. Add one to mark thumb mode */
	.word ADDR_NMI_HANDLER
	.word ADDR_HARD_FAULT_HANDLER
	.word ADDR_MEM_FAULT_HANDLER
	.word ADDR_BUS_FAULT_HANDLER
	.word ADDR_USAGE_FAULT_HANDLER
	.word ADDR_RSV0_HANDLER
	.word ADDR_RSV1_HANDLER
	.word ADDR_RSV2_HANDLER
	.word ADDR_RSV3_HANDLER
	.word SVC_Handler
	.word ADDR_DEBUG_MON_HANDLER
	.word ADDR_RSV4_HANDLER
	.word PendSV_Handler
	.word SysTick_Handler

	.section .text.VectorHandlers
	.align 2
_temp_nmi_handler:
	b . /* Do nothing just stop */

	.align 2
_temp_hard_fault_handler:
	b . /* Do nothing just stop */

	.align 2
_temp_mem_fault_handler:
	b . /* Do nothing just stop */

	.align 2
_temp_bus_fault_handler:
	b . /* Do nothing just stop */

	.align 2
_temp_usage_fault_handler:
	b . /* Do nothing just stop */

	.align 2
_temp_exception_handler:
	b . /* Do nothing just stop */

	.section .text.Start
	.align 2
_start:
	/* Setting HW related */
	bl system_init
	b main

_deadend:
	b   _deadend
	.section .interrupt

.end
