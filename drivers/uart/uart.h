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

#define DW_APB_UART_FIFO_SIZE	(32)
#define DW_APB_UART_DLF_SIZE	(4U)

#define IER_RXRDY				(0x01U)
#define IER_TBE					(0x02U)
#define IER_LSR					(0x04U)
#define IER_MSI					(0x08U)
#define IER_PTIME				(0x80U)
#define IER_PTIME_MASK			(0x80U)

#define IIR_MSTAT				(0x00U)
#define IIR_NIP					(0x01U)
#define IIR_THRE				(0x02U)
#define IIR_THRE_MASK			(0x02U)
#define IIR_RBRF				(0x04U)
#define IIR_RBRF_MASK			(0x04U)
#define IIR_LS					(0x06U)
#define IIR_MASK				(0x07U)
#define IIR_ID					(0x06U)
#define IIR_CTIMEOUT			(0x0CU)
#define IIR_CTIMEOUT_ONLY		(0x08U)
#define IIR_CTIMEOUT_ONLY_MASK	(0x08U)

#define FCR_FIFO				(0x01U)
#define FCR_RCVRCLR				(0x02U)
#define FCR_XMITCLR				(0x04U)

#define PCP_UPDATE				(0x80000000U)
#define PCP_EN					(0x00000001U)

#define FCR_MODE0				(0x00U)
#define FCR_MODE1				(0x08U)

#define FCR_FIFO_1				(0x00U)
#define FCR_FIFO_4				(0x40U)
#define FCR_FIFO_8				(0x80U)
#define FCR_FIFO_14				(0xC0U)

#define FCR_FIFO_64				(0x20U)

#define MCR_DTR					(0x01U)
#define MCR_RTS					(0x02U)
#define MCR_OUT1				(0x04U)
#define MCR_OUT2				(0x08U)
#define MCR_LOOP				(0x10U)
#define MCR_AFCE				(0x20U)

#define LSR_RXRDY				(0x01U)
#define LSR_OE					(0x02U)
#define LSR_PE					(0x04U)
#define LSR_FE					(0x08U)
#define LSR_BI					(0x10U)
#define LSR_EOB_MASK			(0x1EU)
#define LSR_THRE				(0x20U)
#define LSR_THRE_MASK			(0x20U)
#define LSR_TEMT				(0x40U)
#define LSR_TEMT_MASK			(0x40U)

#define MSR_DCTS				(0x01U)
#define MSR_DDSR				(0x02U)
#define MSR_DRI					(0x04U)
#define MSR_DDCD				(0x08U)
#define MSR_CTS					(0x10U)
#define MSR_DSR					(0x20U)
#define MSR_RI					(0x40U)
#define MSR_DCD					(0x80U)

#define DLL_SET(x)				((x) << 0)
#define DLH_SET(x)				((x) << 0)

#define FCR_RT_MASK				(0x3 << 6)
#define FCR_RT_SET(x)			((x) << 6)
#define FCR_FIFO_CAHR_1			(0x0)
#define FCR_FIFO_QUARTER_FULL	(0x1)
#define FCR_FIFO_HALF_FULL		(0x2)
#define FCR_FIFO_FULL_2			(0x3)

#define FCR_TET_MASK			(0x3 << 4)
#define FCR_TET_SET(x)			((x) << 4)
#define FCR_FIFOE				(0x1)

#define IER_ERBFI				(0x1)
#define IER_ETBEI				(0x2)
#define IER_ELSI				(0x4)
#define IER_EDSSI				(0x8)
#define IER_EELCOLR				(0x10)

#define LCR_DLS_MASK			(0x3U << 0)
#define LCR_DLS_(x)				((x) << 0)
#define LCR_CS5					(0U)
#define LCR_CS6					(1U)
#define LCR_CS7					(2U)
#define LCR_CS8					(3U)
#define LCR_STOP_MASK			BIT(2)
#define LCR_STOP_(x)			((x) << 2)
#define LCR_1_STB				(0U)
#define LCR_2_STB				(1U)
#define LCR_PEN_MASK			BIT(3)
#define LCR_PEN_(x)				((x) << 3)
#define LCR_PDIS				(0U)
#define LCR_PEN					(1U)
#define LCR_EPS_MASK			BIT(4)
#define LCR_EPS_(x)				((x) << 4)
#define LCR_EPS_ODD				(0U)
#define LCR_EPS_EVEN			(1U)
#define LCR_SP					BIT(5)
#define LCR_SP_MASK				BIT(5)
#define LCR_BC					BIT(6)
#define LCR_BC_MASK				BIT(6)
#define LCR_DLAB				BIT(7)

#define DIVISOR_MASK_BYTE		(0xFF)
#define DLH_SHIFT				(8)

#define TRUE					(1)
#define FALSE					(0)

struct dw_apb_uart_regs {
	union {
		volatile const uint32_t rbr;
		volatile uint32_t thr;
		volatile uint32_t dll;
	};
	union {
		volatile uint32_t ier;
		volatile uint32_t dlh;
	};
	union {
		volatile const uint32_t iir;
		volatile uint32_t fcr;
	};
	volatile uint32_t lcr;

	/* Offset: 0x10 */
	volatile uint32_t mcr;
	volatile const uint32_t lsr;
	volatile const uint32_t msr;
	volatile uint32_t scr;

	/* Offset: 0x20 */
	volatile uint32_t lpdll;
	volatile uint32_t lpdlh;
	volatile uint32_t reserved0[2];

	/* Offset: 0x30 */
	union {
		volatile const uint32_t srbr[16];
		volatile uint32_t sthr[16];
	};

	/* Offset: 0x70 */
	volatile uint32_t far;
	volatile const uint32_t tfr;
	volatile uint32_t rfw;
	volatile const uint32_t usr;

	/* Offset: 0x80 */
	volatile const uint32_t tfl;
	volatile const uint32_t rfl;
	volatile uint32_t srr;
	volatile uint32_t srts;

	/* Offset: 0x90 */
	volatile uint32_t sbcr;
	volatile uint32_t sdmam;
	volatile uint32_t sfe;
	volatile uint32_t srt;

	/* Offset: 0xa0 */
	volatile uint32_t stet;
	volatile uint32_t htx;
	volatile uint32_t dmasa;
	volatile uint32_t tcr;

	/* Offset: 0xb0 */
	volatile uint32_t de_en;
	volatile uint32_t re_en;
	volatile uint32_t det;
	volatile uint32_t tat;

	/* Offset: 0xc0 */
	volatile uint32_t dlf;
	volatile uint32_t rar;
	volatile uint32_t tar;
	volatile uint32_t lcr_ext;

	/* Offset: 0xd0 */
	volatile uint32_t UART_PROT_LEVEL;
	volatile uint32_t REG_TIMEOUT_RST;
	volatile uint32_t reserved1[7];

	/* Offset: 0xf4 */
	volatile const uint32_t cpr;
	volatile const uint32_t ucv;
	volatile const uint32_t ctr;
};

struct dw_apb_uart_config {
	struct dw_apb_uart_regs *regs;
	uint32_t sys_clk_freq;
	uint32_t baud_rate;
	uint32_t irq_number;
	uint32_t irq_prio;
};

#define UART_USE_FIFO	0
#define UART_USE_POLL	1
#define UART_USE_INT	0
#define UART_USE_DMA	0

#define UART_BUFFER_SIZE	 32

#define RX_STATE_BUSY	0
#define RX_STATE_READY	1
#define TX_STATE_BUSY	0
#define TX_STATE_READY	1

struct uart_rx_str {
	char *rxdata;
	int32_t index;
	void (*rx_callback)(void);
};

struct uart_tx_str {
	char *txdata;
	int32_t head;
	void (*tx_callback)(void);
};

/**
 * @fn		void uart_putc(char c)
 * @brief	Send a data byte
 * @param	c: data to be sent out
 * @return	none
 */
void uart_putc(char c);

/**
 * @fn		void uart_puts(char *str)
 * @brief	Send data bytes in the buffer
 * @param	str: buffer pointer containing data bytes to be sent out
 * @return	none
 */
void uart_puts(char *str);

/**
 * @fn		uint32_t uart_getc(char *c)
 * @brief	Get one character(byte)
 * @param	c: buffer pointer to be saved
 * @return	Number of byte, always 1
 */
uint32_t uart_getc(char *c);

/**
 * @fn		void uart_irq_rx_disable(void)
 * @brief	Disable rx interrupt
 * @param	none
 * @return	none
 */
void uart_irq_rx_disable(void);

/**
 * @fn		void uart_int_config(void)
 * @brief	Config to enable rx interrupt
 * @param	none
 * @return	none
 */
void uart_int_config(void);

/**
 * @fn		int32_t uart_is_tx_fifo_empty(void)
 * @brief	Return the status of tx fifo empty
 * @param	none
 * @return	1 on empty, 0 on not empty
 */
int32_t uart_is_tx_fifo_empty(void);

/**
 * @fn		void uart_out_all_fifo(void)
 * @brief	Write all data in buffer to uart fifo
 * @param	none
 * @return	none
 */
void uart_out_all_fifo(void);

/**
 * @fn		void uart_register_rx_callback(void *func, char *buf)
 * @brief	Register rx callback function and buffer
 * @param	func: callback function pointer
 * @param	buf: buffer pointer
 * @return	none
 */
void uart_register_rx_callback(void *func, char *buf);

/**
 * @fn		void uart_register_tx_callback(void *func, char *buf)
 * @brief	Register tx callback function and buffer
 * @param	func: callback function pointer
 * @param	buf: buffer pointer
 * @return	none
 */
void uart_register_tx_callback(void *func, char *buf);

/**
 * @fn		int uart_init(void)
 * @brief	Perform uart initialization
 * @param	none
 * @return	0 only
 */
int uart_init(void);
