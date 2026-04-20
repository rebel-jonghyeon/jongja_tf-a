#include <driver.h>
#include <uart.h>

/* PL011 Registers */
#define UARTDR                    0x000
#define UARTRSR                   0x004
#define UARTECR                   0x004
#define UARTFR                    0x018
#define UARTIMSC                  0x038
#define UARTRIS                   0x03C
#define UARTICR                   0x044

/* PL011 registers (out of the SBSA specification) */
#if !PL011_GENERIC_UART
#define UARTILPR                  0x020
#define UARTIBRD                  0x024
#define UARTFBRD                  0x028
#define UARTLCR_H                 0x02C
#define UARTCR                    0x030
#define UARTIFLS                  0x034
#define UARTMIS                   0x040
#define UARTDMACR                 0x048
#endif /* !PL011_GENERIC_UART */

/* Data status bits */
#define UART_DATA_ERROR_MASK      0x0F00

/* Status reg bits */
#define UART_STATUS_ERROR_MASK    0x0F

/* Flag reg bits */
#define PL011_UARTFR_RI           (1 << 8)	/* Ring indicator */
#define PL011_UARTFR_TXFE         (1 << 7)	/* Transmit FIFO empty */
#define PL011_UARTFR_RXFF         (1 << 6)	/* Receive  FIFO full */
#define PL011_UARTFR_TXFF         (1 << 5)	/* Transmit FIFO full */
#define PL011_UARTFR_RXFE         (1 << 4)	/* Receive  FIFO empty */
#define PL011_UARTFR_BUSY         (1 << 3)	/* UART busy */
#define PL011_UARTFR_DCD          (1 << 2)	/* Data carrier detect */
#define PL011_UARTFR_DSR          (1 << 1)	/* Data set ready */
#define PL011_UARTFR_CTS          (1 << 0)	/* Clear to send */

#define PL011_UARTFR_TXFF_BIT	5	/* Transmit FIFO full bit in UARTFR register */
#define PL011_UARTFR_RXFE_BIT	4	/* Receive FIFO empty bit in UARTFR register */
#define PL011_UARTFR_BUSY_BIT	3	/* UART busy bit in UARTFR register */

#define UART_PL011_BASE 0x1ff9040000
#define PL011_REG(a, b) *(volatile uint32_t *)((uint64_t)a + b)
#define ERROR_NO_PENDING_CHAR (-1)

bool uart_is_tx_fifo_empty(void)
{
	return !!(PL011_REG(UART_PL011_BASE, UARTFR) & PL011_UARTFR_TXFE);
}

bool uart_is_rx_fifo_empty(void)
{
	return !!(PL011_REG(UART_PL011_BASE, UARTFR) & PL011_UARTFR_RXFE);
}

static void reset_fifo(void)
{
	while (!uart_is_rx_fifo_empty())
	{
		uart_getc();
	}
}

void uart_enable_interrupts(void)
{
	PL011_REG(UART_PL011_BASE, UARTIMSC) = PL011_REG(UART_PL011_BASE, UARTIMSC) & ~(
						(1 << 6) |	// Receive timeout
						(1 << 4)	// Receive
						);
}

void uart_clear_interrupts(void)
{
	PL011_REG(UART_PL011_BASE, UARTICR) = 0x7FF;
}

int uart_init(void)
{
	/* TODO: Enabling interrupts */
	PL011_REG(UART_PL011_BASE, UARTCR) = 0x0;

	PL011_REG(UART_PL011_BASE, UARTIBRD) = 0x10f;
	PL011_REG(UART_PL011_BASE, UARTFBRD) = 0x11;

	PL011_REG(UART_PL011_BASE, UARTLCR_H) = 0x70;

	PL011_REG(UART_PL011_BASE, UARTIMSC) = 0x7ff;
	PL011_REG(UART_PL011_BASE, UARTDMACR) = 0x0;

	PL011_REG(UART_PL011_BASE, UARTCR) = 0x301;

	PL011_REG(UART_PL011_BASE, UARTIFLS) = 0;	// 1/8 full

	reset_fifo();
	return 0;
}

static void __uart_putc(char c)
{
	/* Write single byte for Tx */

	/* TODO: Add spin-lock for CA73 */

	/* Check if the transmit FIFO is full */
	while (PL011_REG(UART_PL011_BASE, UARTFR) & PL011_UARTFR_TXFF)
		;
	PL011_REG(UART_PL011_BASE, UARTDR) = c;
}

void uart_putc(char c)
{
	/* Send CR character if current input is LF */
	if (c == '\n')
		__uart_putc('\r');

	/* Send character */
	__uart_putc(c);
}


void uart_puts(char *str)
{
	if (!str || !*str)
		return;

	/* Send string to UART */
	do {
		uart_putc(*str);
	} while (*++str);
}

int _puts(const char *s)
{
	uint32_t i;

	for (i = 0; s[i] != '\0'; i++)
		uart_putc(s[i]);

	return i;
}

int uart_poll_out(char c)
{
	int result = 0;

	while (uart_is_tx_fifo_empty())
		;

	__uart_putc(c);

	return result;
}

char uart_getc(void)
{
	return  PL011_REG(UART_PL011_BASE, UARTDR);
}

#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(level0, 0, uart_init)
#endif
