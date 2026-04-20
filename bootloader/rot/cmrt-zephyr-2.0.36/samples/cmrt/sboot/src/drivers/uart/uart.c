#include <rebel_h.h>
#include <fboot.h>
#include "sac_custom.h"
#include "uart.h"
#include "timer.h"

#define RBR				(0x0)   /* Receive buffer register */
#define THR				(0x0)   /* Transmit holding register */
#define DLL				(0x0)   /* Divisor latch (low) */
#define DLH				(0x4)   /* Divisor latch (high) */
#define IER				(0x4)	/* Interrupt enable register */
#define FCR				(0x8)   /* FIFO control register */
#define FIFOE			(0x1)	/* FIFO enable */
#define RFIFOR			(0x2)	/* RCVR FIFO Reset */
#define XFIFOR			(0x4)	/* XMIT FIFO Reset */
#define RT_HALF			(0x80)	/* RCVR Trigger FIFO 1/2 full */
#define TET				(0x30)	/* TX empty trigger FIFO 1/2 full */
#define LCR				(0xC)   /* Line control register */
#define DLS_8BIT		(0x3)	/* 8 data bits per character */
#define LSR				(0x14)  /* Line status register */
#define DR				(0x1)   /* Data reday bit */
#define THRE			(0x20)  /* Transmit holding register empty bit */
#define DLAB			(0x80)	/* Divisor latch access bit */
#define DLF				(0xC0)  /* Divisor latch frantion register */

#define TIMEOUT_MS		(100)

#define DLL_115200		(0x88)	/* based on input clock 500MHz */
#define DLF_115200		(0x0)	/* based on input clock 500MHz */

#define PERI0_UART1_C0	(0x1FF9050000ULL)
static uint64_t PERI0_UART1_BASE_ADDR;

void uart_init(void)
{
	PERI0_UART1_BASE_ADDR = PERI0_UART1_C0 + (get_chiplet_id() * CHIPLET_BASE_OFFSET);
	cmrt_sac_set_base(NULL, PERI0_UART1_BASE_ADDR);

	sys_write32(DLAB, GET_SAC_R_CPU_DATA(LCR));
	sys_write32(DLL_115200, GET_SAC_R_CPU_DATA(DLL));
	sys_write32(DLF_115200, GET_SAC_R_CPU_DATA(DLF));
	sys_write32(DLS_8BIT, GET_SAC_R_CPU_DATA(LCR));
	sys_write32(FIFOE | RFIFOR | XFIFOR | RT_HALF | TET, GET_SAC_R_CPU_DATA(FCR));
}

int poll_rx_fifo(uint8_t *c)
{
	int ret = RX_FIFO_NO_DATA;

	cmrt_sac_set_base(NULL, PERI0_UART1_BASE_ADDR);
	if ((sboot_sac_read8(LSR + SAC_MEMORY_BASE) & DR) != 0) {
		*c = sboot_sac_read8(RBR + SAC_MEMORY_BASE);
		ret = RX_FIFO_HAS_DATA;
	}

	return ret;
}

void push_tx_fifo(uint8_t c)
{
	cmrt_sac_set_base(NULL, PERI0_UART1_BASE_ADDR);
	while ((sys_read32(GET_SAC_R_CPU_DATA(LSR)) & THRE) == 0)
		;

	sys_write32(c, GET_SAC_R_CPU_DATA(THR));
}

int read_data_in_fifo(uint8_t *rx_data, const int size)
{
	int i = 0;
	uint64_t start_ms = get_uptime_ms();
	uint64_t end_ms;

	for (i = 0; i < size; ) {
		if (poll_rx_fifo(&rx_data[i]) == RX_FIFO_HAS_DATA) {
			i++;
			start_ms = get_uptime_ms();
		} else {
			end_ms = get_uptime_ms();
			if (end_ms - start_ms > TIMEOUT_MS) {
				break;
			}
		}
	}

	return i;
}

void flush_rx_fifo(void)
{
	uint8_t dummy;

	while (poll_rx_fifo(&dummy) != RX_FIFO_NO_DATA)
		;
}
