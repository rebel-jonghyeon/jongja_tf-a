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
#include <rebel_h_platform.h>

#include "uart.h"
#include <interrupt.h>
#include <driver.h>
#include <string.h>
#include <stdint.h>

#if (ZEBU == 1)
#define TARGET_BAUD_RATE	(7812500)
#else
#define TARGET_BAUD_RATE	(115200)
#endif

#if defined(__TARGET_BOOTROM)
struct dw_apb_uart_config uart_cfg = {
	.regs = (struct dw_apb_uart_regs *)UART0_PERI0_BOOTROM,
	.sys_clk_freq = 40 * MHZ,
	.baud_rate = 115200,
};

#elif (__TARGET_CP == 1)
#include "gic.h"

#define UART_CP_IRQ_NUM		(263)
#define UART_CP_IRQ_PRIO	(1)
struct dw_apb_uart_config uart_cfg = {
	.regs = (struct dw_apb_uart_regs *)UART1_PERI1,
	.sys_clk_freq = 250 * MHZ,
	.baud_rate = TARGET_BAUD_RATE,
	.irq_number = UART_CP_IRQ_NUM,
	.irq_prio = UART_CP_IRQ_PRIO,
};

#elif defined(__TARGET_PCIE)
#include "ARMCM7_SP.h"
extern uint32_t INTERRUPT_RESERVED[];

#define UART_PCIE_IRQ_NUM	(24)
#define UART_PCIE_IRQ_PRIO	(5)
struct dw_apb_uart_config uart_cfg = {
	.regs = (struct dw_apb_uart_regs *)UART_PCIE_PRIVATE,
	.sys_clk_freq = 500 * MHZ,
	.baud_rate = TARGET_BAUD_RATE,
	.irq_number = UART_PCIE_IRQ_NUM,
	.irq_prio = UART_PCIE_IRQ_PRIO,
};

#else
#include "gic.h"

#ifndef ZEBU_POC
#define UART_CP_IRQ_NUM		(212)
#else
#define UART_CP_IRQ_NUM		(210)
#endif /* ZEBU_POC */

#define UART_CP_IRQ_PRIO	(1)
struct dw_apb_uart_config uart_cfg = {
	.regs = (struct dw_apb_uart_regs *)UART0_PERI0,
	.sys_clk_freq = 250 * MHZ,
	.baud_rate = TARGET_BAUD_RATE,
	.irq_number = UART_CP_IRQ_NUM,
	.irq_prio = UART_CP_IRQ_PRIO,
};

#endif

char uart_rx_buffer[UART_BUFFER_SIZE];
struct uart_rx_str uart_rx_data = {
	.rxdata = (char *)uart_rx_buffer,
	.index = 0,
	.rx_callback = (void *)NULL,
};

char uart_tx_buffer[UART_BUFFER_SIZE];
struct uart_tx_str uart_tx_data = {
	.txdata = (char *)uart_tx_buffer,
	.head = 0,
	.tx_callback = (void *)NULL,
};

static void uart_clear_rx_buffer(void)
{
	for (int i = 0; i < UART_BUFFER_SIZE; i++)
		uart_rx_data.rxdata[i] = 0;

	uart_rx_data.index = 0;
}

static void uart_clear_tx_buffer(void)
{
	for (int i = 0; i < UART_BUFFER_SIZE; i++)
		uart_tx_data.txdata[i] = 0;

	uart_tx_data.head = 0;
}

void uart_register_rx_callback(void *func, char *buf)
{
	uart_rx_data.rx_callback = func;
	uart_rx_data.rxdata = buf;

	uart_clear_rx_buffer();
}

void uart_register_tx_callback(void *func, char *buf)
{
	uart_tx_data.tx_callback = func;
	uart_tx_data.txdata = buf;

	uart_clear_tx_buffer();
}

static void uart_tx_empty_trigger_disable(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	regs->ier &= ~IER_PTIME;
}

int32_t uart_is_tx_fifo_empty(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	if ((regs->ier & IER_PTIME_MASK) == IER_PTIME) {
		return (regs->lsr & LSR_THRE_MASK) ? TRUE : FALSE;
	} else {
		return (regs->tfl) ? FALSE : TRUE;
	}
}

static void reset_fifo(void)
{
	struct dw_apb_uart_regs *regs = uart_cfg.regs;
	uint32_t val;

	val = regs->fcr;
	val |= FCR_RCVRCLR;
	val |= FCR_XMITCLR;
	regs->fcr = val;
}

static void uart_fifo_enable(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	regs->fcr = FCR_FIFOE;
}

static void __uart_putc(char c)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	while (1) {
		if ((regs->lsr & (LSR_TEMT_MASK | LSR_THRE_MASK)) == (LSR_TEMT | LSR_THRE)) {
			regs->thr = (uint32_t)c;
			break;
		}
	}
}

void uart_putc(char c)
{
	if (c == '\n')
		__uart_putc('\r');

	__uart_putc(c);
}

void uart_puts(char *str)
{
	if (str && *str) {
		do {
			uart_putc(*str);
		} while (*++str);
	}
}

void uart_out_all_fifo(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;
	char *str = uart_tx_data.txdata;

	while (*str != 0) {
		regs->thr = (uint32_t)*str;
		str++;
	};

	uart_clear_tx_buffer();
}

static void uart_poll_in(char *c)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	while ((regs->lsr & LSR_RXRDY) == 0)
		;

	*c = regs->rbr;
}

static uint32_t uart_in_once(char *c)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;
	uint32_t num_of_rxdata = 0;

	if (regs->lsr & LSR_RXRDY) {
		*c = regs->rbr;
		num_of_rxdata = 1;
	}

	return num_of_rxdata;
}

static void uart_in_all_fifo(char *c, int32_t *index)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;
	int32_t *ind = index;

	while (regs->lsr & LSR_RXRDY) {
		c[*ind] = regs->rbr;
		*ind = (*ind + 1) & (UART_BUFFER_SIZE - 1);
	}
}

static uint32_t uart_in_from_buffer(char *c)
{
	uint32_t num_of_rxdata = 0;

	memcpy(c, uart_rx_data.rxdata, uart_rx_data.index);
	num_of_rxdata = uart_rx_data.index;

	uart_clear_rx_buffer();

	return num_of_rxdata;
}

uint32_t uart_getc(char *c)
{
	uint32_t num_of_rxdata = 0;

	if (UART_USE_POLL) {
		uart_poll_in(c);
		num_of_rxdata = 1;
	} else {
		if (UART_USE_INT) {
			num_of_rxdata = uart_in_from_buffer(c);
		} else {
			num_of_rxdata = uart_in_once(c);
		}
	}

	return num_of_rxdata;
}

static uint32_t uart_read_iir(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	return regs->iir;
}

static uint32_t uart_is_iir_rx_ready(uint32_t val)
{
	return (val & IIR_RBRF_MASK) == IIR_RBRF ? TRUE : FALSE;
}

static uint32_t uart_is_iir_tx_empty(uint32_t val)
{
	return (val & IIR_THRE_MASK) == IIR_THRE ? TRUE : FALSE;
}

static uint32_t uart_is_iir_character_timeout(uint32_t val)
{
	return (val & IIR_CTIMEOUT_ONLY_MASK) == IIR_CTIMEOUT_ONLY ? TRUE : FALSE;
}

void uart_irq_rx_enable(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	regs->ier |= IER_RXRDY;
}

void uart_irq_rx_disable(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	regs->ier &= (~IER_RXRDY);
}

void uart_irq_tx_enable(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	regs->ier |= IER_TBE;
}

void uart_irq_tx_disable(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	regs->ier &= (~IER_TBE);
}

uint32_t uart_is_irq_rx_ready(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;

	return (regs->iir & IIR_RBRF) == IIR_RBRF ? 1 : 0;
}

int uart_init(void)
{
	volatile struct dw_apb_uart_regs *regs = uart_cfg.regs;
	uint32_t baud_rate = uart_cfg.baud_rate * 16;
	uint32_t divisor_val;
	uint32_t fraction_val;
	uint32_t lcr_val;

	regs->mcr = 0x0;

	regs->lcr |= LCR_DLAB;

	divisor_val = uart_cfg.sys_clk_freq / baud_rate;
	regs->dll = (divisor_val & DIVISOR_MASK_BYTE);
	regs->dlh = ((divisor_val >> DLH_SHIFT) & DIVISOR_MASK_BYTE);

	fraction_val = uart_cfg.sys_clk_freq % baud_rate;
	regs->dlf = ((fraction_val << DW_APB_UART_DLF_SIZE) / baud_rate);

	regs->lcr &= ~(LCR_DLAB);

	lcr_val = regs->lcr;
	lcr_val &= ~(LCR_BC | LCR_SP | LCR_EPS_MASK | LCR_PEN_MASK | LCR_STOP_MASK | LCR_DLS_MASK);
	lcr_val |= (LCR_DLS_(LCR_CS8) | LCR_STOP_(LCR_1_STB) | LCR_PEN_(LCR_PDIS));
	regs->lcr = lcr_val;

	uart_clear_rx_buffer();
	uart_clear_tx_buffer();

	return 0;
}

static void uart_isr(void)
{
	uint32_t iir_val;

	iir_val = uart_read_iir();

	if (uart_is_iir_rx_ready(iir_val)) {
		uart_in_all_fifo(uart_rx_data.rxdata, &uart_rx_data.index);

		if (uart_rx_data.rx_callback) {
			uart_rx_data.rx_callback();
			uart_clear_rx_buffer();
		}
	}

	if (uart_is_iir_character_timeout(iir_val)) {
		if (uart_tx_data.tx_callback) {
			uart_tx_data.tx_callback();
		}
	}

	if (uart_is_iir_tx_empty(iir_val)) {
		if (uart_tx_data.tx_callback) {
			uart_tx_data.tx_callback();
		}
	}
}

void uart_int_config(void)
{
	reset_fifo();
	uart_fifo_enable();

#if defined(__RUN_RTOS)
	#if (__TARGET_CP == 1)
	/* Register UART interrupt handler, CPU0 of CP1 = CPU4 */
	connect_interrupt_with_core_handler(uart_cfg.irq_number, uart_cfg.irq_prio, IRQ_TYPE_LEVEL,
										0x100, uart_isr, NULL);
	#else
	/* Register UART interrupt handler */
	connect_interrupt_with_handler(uart_cfg.irq_number, uart_cfg.irq_prio, IRQ_TYPE_LEVEL, uart_isr,
								   NULL);
	#endif
#endif

	uart_tx_empty_trigger_disable();
	uart_irq_rx_enable();
}

#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(1, uart_init);
#endif
