/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>

 * Copyright 2024 Samsung Electronics Co., Ltd All Rights Reserved
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#ifndef configINTERRUPT_CONTROLLER_BASE_ADDRESS
	#error configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html
#endif

#ifndef configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET
	#error configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html
#endif

#ifndef configUNIQUE_INTERRUPT_PRIORITIES
	#error configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html
#endif

#ifndef configSETUP_TICK_INTERRUPT
	#error configSETUP_TICK_INTERRUPT() must be defined.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html
#endif /* configSETUP_TICK_INTERRUPT */

#ifndef configMAX_API_CALL_INTERRUPT_PRIORITY
	#error configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See https://www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html
#endif

#if configMAX_API_CALL_INTERRUPT_PRIORITY == 0
	#error configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0
#endif

#if configMAX_API_CALL_INTERRUPT_PRIORITY > configUNIQUE_INTERRUPT_PRIORITIES
	#error configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority
#endif

#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
	/* Check the configuration. */
	#if (configMAX_PRIORITIES > 32)
		#error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
	#endif
#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#if configMAX_API_CALL_INTERRUPT_PRIORITY <= (configUNIQUE_INTERRUPT_PRIORITIES / 2)
	#error configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )
#endif

/* Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h.
 */
#ifndef configCLEAR_TICK_INTERRUPT
	#define configCLEAR_TICK_INTERRUPT()
#endif

/* A critical section is exited when the critical section nesting count reaches
 * this value.
 */
#define portNO_CRITICAL_NESTING			((size_t) 0)

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority.
 */
#define portUNMASK_VALUE				(0xFFUL)

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context.
 */
#define portNO_FLOATING_POINT_CONTEXT	((StackType_t) 0)

/* Constants required to setup the initial task context. */
#define portSP_ELx						((StackType_t) 0x01)
#define portSP_EL0						((StackType_t) 0x00)

	#define portEL1						((StackType_t) 0x04)
	#define portINITIAL_PSTATE				(portEL1 | portSP_EL0)

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero.
 */
#define portBINARY_POINT_BITS			((uint8_t) 0x03)

/* Masks all bits in the APSR other than the mode bits. */
#define portAPSR_MODE_BITS_MASK			(0x0C)

/* The I bit in the DAIF bits. */
#define portDAIF_I						(0x80)

/* Hardware specifics used when sanity checking the configuration. */
#define portINTERRUPT_PRIORITY_REGISTER_OFFSET		0x400UL
#define portMAX_8_BIT_VALUE							((uint8_t) 0xff)
#define portBIT_0_SET								((uint8_t) 0x01)

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit registers.
 */
#define portFPU_REGISTER_WORDS		(32 * 2)

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
extern void vPortRestoreTaskContext(void);

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started.
 */
volatile uint64_t ullCriticalNesting = 9999ULL;

/* Saved as part of the task context.  If ullPortTaskHasFPUContext is non-zero
 * then floating point context must be saved and restored for the task.
 */
uint64_t ullPortTaskHasFPUContext[configNUMBER_OF_CORES] = {pdFALSE};

/* Set to 1 to pend a context switch from an ISR. */
uint64_t ullPortYieldRequired[configNUMBER_OF_CORES] = {pdFALSE};

/* Counts the interrupt nesting depth.  A context switch is only performed
 * if the nesting depth is 0.
 */
uint64_t ullPortInterruptNesting[configNUMBER_OF_CORES] = {0};

volatile uint64_t ullPortSchedularRunning = pdFALSE;

/* Used in the ASM code. */
__attribute__((used)) const uint64_t ullMaxAPIPriorityMask = (configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT);

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
StackType_t *pxPortInitialiseStack(StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters)
{
	/* Setup the initial stack of the task.  The stack is set exactly as
	 * expected by the portRESTORE_CONTEXT() macro.
	 */

	/* First all the general purpose registers. */
	pxTopOfStack--;
	*pxTopOfStack = 0x0101010101010101ULL;	/* R1 */
	pxTopOfStack--;
	*pxTopOfStack = (StackType_t) pvParameters; /* R0 */
	pxTopOfStack--;
	*pxTopOfStack = 0x0303030303030303ULL;	/* R3 */
	pxTopOfStack--;
	*pxTopOfStack = 0x0202020202020202ULL;	/* R2 */
	pxTopOfStack--;
	*pxTopOfStack = 0x0505050505050505ULL;	/* R5 */
	pxTopOfStack--;
	*pxTopOfStack = 0x0404040404040404ULL;	/* R4 */
	pxTopOfStack--;
	*pxTopOfStack = 0x0707070707070707ULL;	/* R7 */
	pxTopOfStack--;
	*pxTopOfStack = 0x0606060606060606ULL;	/* R6 */
	pxTopOfStack--;
	*pxTopOfStack = 0x0909090909090909ULL;	/* R9 */
	pxTopOfStack--;
	*pxTopOfStack = 0x0808080808080808ULL;	/* R8 */
	pxTopOfStack--;
	*pxTopOfStack = 0x1111111111111111ULL;	/* R11 */
	pxTopOfStack--;
	*pxTopOfStack = 0x1010101010101010ULL;	/* R10 */
	pxTopOfStack--;
	*pxTopOfStack = 0x1313131313131313ULL;	/* R13 */
	pxTopOfStack--;
	*pxTopOfStack = 0x1212121212121212ULL;	/* R12 */
	pxTopOfStack--;
	*pxTopOfStack = 0x1515151515151515ULL;	/* R15 */
	pxTopOfStack--;
	*pxTopOfStack = 0x1414141414141414ULL;	/* R14 */
	pxTopOfStack--;
	*pxTopOfStack = 0x1717171717171717ULL;	/* R17 */
	pxTopOfStack--;
	*pxTopOfStack = 0x1616161616161616ULL;	/* R16 */
	pxTopOfStack--;
	*pxTopOfStack = 0x1919191919191919ULL;	/* R19 */
	pxTopOfStack--;
	*pxTopOfStack = 0x1818181818181818ULL;	/* R18 */
	pxTopOfStack--;
	*pxTopOfStack = 0x2121212121212121ULL;	/* R21 */
	pxTopOfStack--;
	*pxTopOfStack = 0x2020202020202020ULL;	/* R20 */
	pxTopOfStack--;
	*pxTopOfStack = 0x2323232323232323ULL;	/* R23 */
	pxTopOfStack--;
	*pxTopOfStack = 0x2222222222222222ULL;	/* R22 */
	pxTopOfStack--;
	*pxTopOfStack = 0x2525252525252525ULL;	/* R25 */
	pxTopOfStack--;
	*pxTopOfStack = 0x2424242424242424ULL;	/* R24 */
	pxTopOfStack--;
	*pxTopOfStack = 0x2727272727272727ULL;	/* R27 */
	pxTopOfStack--;
	*pxTopOfStack = 0x2626262626262626ULL;	/* R26 */
	pxTopOfStack--;
	*pxTopOfStack = 0x2929292929292929ULL;	/* R29 */
	pxTopOfStack--;
	*pxTopOfStack = 0x2828282828282828ULL;	/* R28 */
	pxTopOfStack--;
	*pxTopOfStack = (StackType_t) 0x00;	/* XZR - has no effect, used so there are an even number of registers. */
	pxTopOfStack--;
	*pxTopOfStack = (StackType_t) 0x00;	/* R30 - procedure call link register. */

	pxTopOfStack--;
	*pxTopOfStack = portINITIAL_PSTATE;

	pxTopOfStack--;
	*pxTopOfStack = (StackType_t) pxCode; /* Exception return address. */

	#if ( configUSE_TASK_FPU_SUPPORT == 1 )
	{
		/* The task will start with a critical nesting count of 0 as interrupts are
		 * enabled.
		 */
		pxTopOfStack--;
		*pxTopOfStack = portNO_CRITICAL_NESTING;

		/* The task will start without a floating point context.  A task that
		 * uses the floating point hardware must call vPortTaskUsesFPU() before
		 * executing any floating point instructions.
		 */
		pxTopOfStack--;
		*pxTopOfStack = portNO_FLOATING_POINT_CONTEXT;
	}
	#elif ( configUSE_TASK_FPU_SUPPORT == 2 )
	{
		/* The task will start with a floating point context.  Leave enough
		 * space for the registers - and ensure they are initialised to 0.
		 */
		pxTopOfStack -= portFPU_REGISTER_WORDS;
		memset( pxTopOfStack, 0x00, portFPU_REGISTER_WORDS * sizeof( StackType_t ) );

		/* The task will start with a critical nesting count of 0 as interrupts are
		 * enabled.
		 */
		pxTopOfStack--;
		*pxTopOfStack = portNO_CRITICAL_NESTING;

		pxTopOfStack--;
		*pxTopOfStack = pdTRUE;
		ullPortTaskHasFPUContext[portGET_CORE_ID()] = pdTRUE;
	}
	#else /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
	{
		#error "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
	}
	#endif /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

	return pxTopOfStack;
}
/*-----------------------------------------------------------*/

#if (configNUMBER_OF_CORES == 1)
BaseType_t xPortStartScheduler(void)
{
	uint32_t ulAPSR;
	uint32_t bpr;

	/* At the time of writing, the BSP only supports EL3. */
	__asm volatile ("MRS %0, CurrentEL" : "=r" (ulAPSR));
	ulAPSR &= portAPSR_MODE_BITS_MASK;

	configASSERT(ulAPSR == portEL1);

	if (ulAPSR == portEL1)
	{
		/* Only continue if the binary point value is set to its lowest possible
		 * setting.  See the comments in vPortValidateInterruptPriority() below for
		 * more information.
		 */
		__asm volatile ("mrs %0, s3_0_c12_c8_3" : "=r" (bpr));
		configASSERT((bpr & portBINARY_POINT_BITS) <= portMAX_BINARY_POINT_VALUE);

		if ((bpr & portBINARY_POINT_BITS) <= portMAX_BINARY_POINT_VALUE)
		{
			/* Interrupts are turned off in the CPU itself to ensure a tick does
			 * not execute	while the scheduler is being started.  Interrupts are
			 * automatically turned back on in the CPU when the first task starts
			 * executing.
			 */
			portDISABLE_INTERRUPTS();

			/* Start the timer that generates the tick ISR. */
			configSETUP_TICK_INTERRUPT();

			/* Start the first task executing. */
			vPortRestoreTaskContext();
		}
	}

	return 0;
}
#else
BaseType_t xPortStartScheduler(void)
{
	uint32_t ulAPSR;

	__asm volatile ("MRS %0, CurrentEL" : "=r" (ulAPSR));
	ulAPSR &= portAPSR_MODE_BITS_MASK;

	configASSERT(ulAPSR == portEL1);
	if (ulAPSR == portEL1)
	{
		/* Interrupts are turned off in the CPU itself to ensure a tick does
		 * not execute while the scheduler is being started.  Interrupts are
		 * automatically turned back on in the CPU when the first task starts
		 * executing.
		 */
		portDISABLE_INTERRUPTS();

#if (configNUMBER_OF_CORES > 1)
		if (portGET_CORE_ID() == 0)
		{
			ullPortSchedularRunning = pdTRUE;
		} else {
			while (ullPortSchedularRunning != pdTRUE)
				;
		}
#endif

		/* Start the timer that generates the tick ISR. */
		configSETUP_TICK_INTERRUPT();

		/* Start the first task executing. */
		vPortRestoreTaskContext();
	}

	return 0;
}
#endif
/*-----------------------------------------------------------*/

void vPortEndScheduler(void)
{
	/* Not implemented in ports where there is nothing to return to.
	 * Artificially force an assert.
	 */
	configASSERT(ullCriticalNesting == 1000ULL);
}
/*-----------------------------------------------------------*/

#if (configNUMBER_OF_CORES == 1)

UBaseType_t uxPortSetInterruptMask(void);

void vPortEnterCritical(void)
{
	/* Mask interrupts up to the max syscall interrupt priority. */
	uxPortSetInterruptMask();

	/* Now interrupts are disabled ullCriticalNesting can be accessed
	 * directly.  Increment ullCriticalNesting to keep a count of how many times
	 * portENTER_CRITICAL() has been called.
	 */
	ullCriticalNesting++;

	/* This is not the interrupt safe version of the enter critical function so
	 * assert() if it is being called from an interrupt context.  Only API
	 * functions that end in "FromISR" can be used in an interrupt.  Only assert if
	 * the critical nesting count is 1 to protect against recursive calls if the
	 * assert function also uses a critical section.
	 */
	if (ullCriticalNesting == 1ULL)
	{
		configASSERT(ullPortInterruptNesting == 0);
	}
}
/*-----------------------------------------------------------*/

void vPortExitCritical(void)
{
	if (ullCriticalNesting > portNO_CRITICAL_NESTING)
	{
		/* Decrement the nesting count as the critical section is being
		 * exited.
		 */
		ullCriticalNesting--;

		/* If the nesting level has reached zero then all interrupt
		 * priorities must be re-enabled.
		 */
		if (ullCriticalNesting == portNO_CRITICAL_NESTING)
		{
			/* Critical nesting has reached zero so all interrupt priorities
			 * should be unmasked.
			 */
			portCLEAR_INTERRUPT_MASK();
		}
	}
}
#endif
/*-----------------------------------------------------------*/

void FreeRTOS_Tick_Handler(void)
{
	uint32_t ulPreviousMask;

	ulPreviousMask = portENTER_CRITICAL_FROM_ISR();

	/* Interrupts should not be enabled before this point. */
	/* Set interrupt mask before altering scheduler structures.   The tick
	 * handler runs at the lowest priority, so interrupts cannot already be masked,
	 * so there is no need to save and restore the current mask value.  It is
	 * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
	 * updated.
	 */
	__asm volatile ("msr S3_0_C4_C6_0, %[i]" :: [i] "r" (configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT));
	__asm volatile ("dsb sy\n"
						"isb sy\n" ::: "memory");

	/* Ok to enable interrupts after the interrupt source has been cleared. */
	configCLEAR_TICK_INTERRUPT();

#if (configNUMBER_OF_CORES > 1)
	if (ullPortSchedularRunning == pdTRUE)
#endif
	{
		/* Increment the RTOS tick. */
		if (xTaskIncrementTick() != pdFALSE)
		{
			ullPortYieldRequired[portGET_CORE_ID()] = pdTRUE;
		}
	}
	__asm volatile ("msr S3_0_C4_C6_0, %[i]" :: [i] "r" (0xFF));
	__asm volatile ("dsb sy\n"
	"isb sy\n" ::: "memory");

#if (__TARGET_CP == 1)
#else
#ifndef ZEBU_POC
	/* Deliver tick interrupt from CP0 to CP1 */
	gic_raise_sgi(SGI_IPI + 1, 0x100, 0x1);
#endif /* ZEBU_POC */
#endif

	portEXIT_CRITICAL_FROM_ISR(ulPreviousMask);
}
/*-----------------------------------------------------------*/

#if ( configUSE_TASK_FPU_SUPPORT != 2 )

	void vPortTaskUsesFPU( void )
	{
		/* A task is registering the fact that it needs an FPU context.  Set the
		 * FPU flag (which is saved as part of the task context).
		 */
		ullPortTaskHasFPUContext[portGET_CORE_ID()] = pdTRUE;

		/* Consider initialising the FPSR here - but probably not necessary in
		 * AArch64.
		 */
	}

#endif /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

#if (configNUMBER_OF_CORES == 1)
void vPortClearInterruptMask(UBaseType_t uxNewMaskValue)
{
	if (uxNewMaskValue == pdFALSE)
	{
		portCLEAR_INTERRUPT_MASK()
	}
}
/*-----------------------------------------------------------*/

UBaseType_t uxPortSetInterruptMask(void)
{
	uint32_t ulReturn = 0;
	uint32_t icc_pmr;

	/* Interrupt in the CPU must be turned off while the ICCPMR is being
	 * updated.
	 */
	portDISABLE_INTERRUPTS();

	__asm volatile ("mrs %[r], S3_0_C4_C6_0" : [r] "=r" (icc_pmr));
	if (icc_pmr == (uint32_t) (configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT))
	{
		/* Interrupts were already masked. */
		ulReturn = pdTRUE;
	} else
	{
		ulReturn = pdFALSE;
		__asm volatile ("msr S3_0_C4_C6_0, %[i]" :: [i] "r" (configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT));
		__asm volatile ("dsb sy\n"
							"isb sy\n" ::: "memory");
	}
	portENABLE_INTERRUPTS();

	return ulReturn;
}
#endif
/*-----------------------------------------------------------*/

#if (configASSERT_DEFINED == 1)

	void vPortValidateInterruptPriority(void)
	{
		/* The following assertion will fail if a service routine (ISR) for
		 * an interrupt that has been assigned a priority above
		 * configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
		 * function.  ISR safe FreeRTOS API functions must *only* be called
		 * from interrupts that have been assigned a priority at or below
		 * configMAX_SYSCALL_INTERRUPT_PRIORITY.

		 * Numerically low interrupt priority numbers represent logically high
		 * interrupt priorities, therefore the priority of the interrupt must
		 * be set to a value equal to or numerically *higher* than
		 * configMAX_SYSCALL_INTERRUPT_PRIORITY.

		 * FreeRTOS maintains separate thread and ISR API functions to ensure
		 * interrupt entry is as fast and simple as possible.
		 */
		/* TODO */
		/* configASSERT( portICCRPR_RUNNING_PRIORITY_REGISTER >= ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) ); */

		/* Priority grouping:  The interrupt controller (GIC) allows the bits
		 * that define each interrupt's priority to be split between bits that
		 * define the interrupt's pre-emption priority bits and bits that define
		 * the interrupt's sub-priority.  For simplicity all bits must be defined
		 * to be pre-emption priority bits.  The following assertion will fail if
		 * this is not the case (if some bits represent a sub-priority).

		 * The priority grouping is configured by the GIC's binary point register
		 * (ICCBPR).  Writting 0 to ICCBPR will ensure it is set to its lowest
		 * possible value (which may be above 0).
		 */
		/* TODO */
		/* configASSERT( ( portICCBPR_BINARY_POINT_REGISTER & portBINARY_POINT_BITS ) <= portMAX_BINARY_POINT_VALUE ); */
	}

#endif /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
	__asm__ volatile ("wfi");
}

void vApplicationPassiveIdleHook(void)
{
	__asm__ volatile ("wfi");
}

void vApplicationTickHook(void)
{
}

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
 * application must provide an implementation of vApplicationGetTimerTaskMemory()
 * to provide the memory that is used by the Timer service task.
 */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
/* If the buffers to be provided to the Timer task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits.
 */
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

	/* Pass out a pointer to the StaticTask_t structure in which the Timer
	 * task's state will be stored.
	 */
	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

	/* Pass out the array that will be used as the Timer task's stack. */
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;

	/* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
	 * Note that, as the array is necessarily of type StackType_t,
	 * configMINIMAL_STACK_SIZE is specified in words, not bytes.
	 */
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task.
 */

/* Read 64b value shared between cores */
uint64_t Get_64(volatile uint64_t *x)
{
	__asm("dsb sy");
	return *x;
}

/* Write 64b value shared between cores */
void Set_64(volatile uint64_t *x, uint64_t value)
{
	*x = value;
	__asm("dsb sy");
}

int32_t GateSmp_tryLock(uint32_t *gateWord);
void GateSmp_unlock(uint32_t *gateWord);

uint64_t Get_64(volatile uint64_t *x);
void Set_64(volatile uint64_t *x, uint64_t value);
uint32_t GateWord[portRTOS_LOCK_COUNT];

volatile uint64_t ucOwnedByCore[portMAX_CORE_COUNT];
volatile uint64_t ucRecursionCountByLock[portRTOS_LOCK_COUNT];

void vPortRecursiveLock(uint32_t ulLockNum, BaseType_t uxAcquire)
{
	uint32_t ulCoreNum = portGET_CORE_ID();
	uint32_t ulLockBit = 1u << ulLockNum;

	/* Lock acquire */
	if (uxAcquire)
	{

		/* Check if spinlock is available */
		/* If spinlock is not available check if the core owns the lock */
		/* If the core owns the lock wait increment the lock count by the core */
		/* If core does not own the lock wait for the spinlock */
		if (GateSmp_tryLock(&GateWord[ulLockNum]) != 0)
		{
			/* Check if the core owns the spinlock */
			if (Get_64(&ucOwnedByCore[ulCoreNum]) & ulLockBit)
			{
				configASSERT(Get_64(&ucRecursionCountByLock[ulLockNum]) != 255u);
				Set_64(&ucRecursionCountByLock[ulLockNum], (Get_64(&ucRecursionCountByLock[ulLockNum])+1));
				return;
			}

			/* Preload the gate word into the cache */
			uint32_t dummy = GateWord[ulLockNum];

			dummy++;

			/* Wait for spinlock */
			while (GateSmp_tryLock(&GateWord[ulLockNum]) != 0) {
				__asm("wfe");
			}
		}

		 /* Add barrier to ensure lock is taken before we proceed */
		__asm__ volatile (
			"dmb sy"
			::: "memory"
		);

		/* Assert the lock count is 0 when the spinlock is free and is acquired */
		configASSERT(Get_64(&ucRecursionCountByLock[ulLockNum]) == 0);

		/* Set lock count as 1 */
		Set_64(&ucRecursionCountByLock[ulLockNum], 1);
		/* Set ucOwnedByCore */
		Set_64(&ucOwnedByCore[ulCoreNum], (Get_64(&ucOwnedByCore[ulCoreNum]) | ulLockBit));
	}
	/* Lock release */
	else
	{
		/* Assert the lock is not free already */
		configASSERT((Get_64(&ucOwnedByCore[ulCoreNum]) & ulLockBit) != 0);
		configASSERT(Get_64(&ucRecursionCountByLock[ulLockNum]) != 0);

		/* Reduce ucRecursionCountByLock by 1 */
		Set_64(&ucRecursionCountByLock[ulLockNum], (Get_64(&ucRecursionCountByLock[ulLockNum]) - 1));

		if (!Get_64(&ucRecursionCountByLock[ulLockNum]))
		{
			Set_64(&ucOwnedByCore[ulCoreNum], (Get_64(&ucOwnedByCore[ulCoreNum]) & ~ulLockBit));
			GateSmp_unlock(&GateWord[ulLockNum]);
			/* Add barrier to ensure lock is taken before we proceed */
			__asm__ __volatile__ (
				"dmb sy"
				::: "memory"
			);
		}
	}
}

uint8_t ucHeap[configTOTAL_HEAP_SIZE] __attribute__((section(".heap")));
