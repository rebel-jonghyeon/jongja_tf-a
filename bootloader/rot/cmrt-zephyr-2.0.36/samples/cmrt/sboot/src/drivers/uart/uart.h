#pragma once

void uart_init(void);
int poll_rx_fifo(unsigned char *c);
void push_tx_fifo(unsigned char c);
int read_data_in_fifo(unsigned char *rx_data, const int size);
void flush_rx_fifo(void);

#define RX_FIFO_NO_DATA     (0x0)
#define RX_FIFO_HAS_DATA    (0x1)
