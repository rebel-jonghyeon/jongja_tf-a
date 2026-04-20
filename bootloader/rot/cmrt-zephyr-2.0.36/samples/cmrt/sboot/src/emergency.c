#include <fboot.h>
#include <syscalls.h>
#ifdef CONFIG_WDT_CMRT
#include <drivers/watchdog.h>
#endif
#include "rebel_h.h"
#include "uart.h"
#include "emergency.h"
#include "timer.h"

#define _SOH					(0x01)
#define _STX					(0x02)
#define _EOT					(0x04)
#define _ACK					(0x06)
#define _NAK					(0x15)
#define _CAN					(0x18)
#define IMG_REQUEST				('C')

#define PREAMBLE_SIZE			(1)
#define PKT_NUM_SIZE			(1)
#define CRC_SIZE				(2)

#define START_INDEX_OF_DATA		(PREAMBLE_SIZE + PKT_NUM_SIZE + PKT_NUM_SIZE)

#define E_PKT_NUM				(1) /* Not exptected packet number */
#define E_PKT_NUM_MIRROR		(2) /* Wrong mirror value of packet number */
#define E_LENGTH_UNSUPPORTED	(3) /* Unsupported length */
#define E_CRC					(4) /* CRC fail */

#define SOH_PKT_DATA_SIZE		(128)
#define STX_PKT_DATA_SIZE		(1024)

#define BYTE_MASK				(0xFF)

#define TIMEOUT_MS				(1000)

#define XMODEM_CRC16_INIT_VAL	(0x0000)
#define XMODEM_CRC16_POLY		(0x1021)
#define XMODEM_CRC16_BITMASK	(0x8000)
#define XMODEM_CRC16_WIDTH		(8)

extern int wdt_cmrt_feed(const struct device *dev, int channel_id);

typedef struct __attribute__((__packed__)) xmodem {
	uint8_t preamble;
	uint8_t pkt_num;
	uint8_t pkt_num_reverse;
	/* in case of 128 byte of data(SOH), CRC will be in data[129:128],
	 * in case of 1024 byte of data(STX), CRC will be in data[1025:1024].
	 */
	uint8_t data[STX_PKT_DATA_SIZE + CRC_SIZE];
} xmodem_packet;

uint16_t get_xmodem_crc16(const uint8_t *data, size_t len)
{
	uint16_t crc = XMODEM_CRC16_INIT_VAL;
	const uint16_t poly = XMODEM_CRC16_POLY;

	for (size_t i = 0; i < len; ++i) {
		crc ^= (uint16_t)data[i] << XMODEM_CRC16_WIDTH;
		for (int b = 0; b < XMODEM_CRC16_WIDTH; ++b) {
			if (crc & XMODEM_CRC16_BITMASK)
				crc = (crc << 1) ^ poly;
			else
				crc = (crc << 1);
		}
	}
	return crc;
}

uint32_t verify_packet(xmodem_packet *packet, uint32_t length,
					   uint32_t expected_pkt_num)
{
	if (packet->pkt_num != expected_pkt_num)
		return -E_PKT_NUM;

	if (((uint8_t)~(packet->pkt_num)) != packet->pkt_num_reverse)
		return -E_PKT_NUM_MIRROR;

	/* supported data length is either 128 or 1024 */
	if (!(length == STX_PKT_DATA_SIZE || length == SOH_PKT_DATA_SIZE))
		return -E_LENGTH_UNSUPPORTED;

	uint16_t pkt_crc = ((uint16_t)packet->data[length]) << 8 | packet->data[length + 1];

	if (get_xmodem_crc16(packet->data, length) == pkt_crc)
		return true;
	else
		return -E_CRC;
}

/* note this function should be called after cmu init().
 * exptect UART_PERI 500MHz,
 * and CLK_ROT_ACLK 750MHz
 */
void emergency_download(void)
{
	uart_init();

	/* set default data length as 128B in a packet */
	uint32_t data_length = SOH_PKT_DATA_SIZE;
	uint8_t packet_count;
	uint32_t is_first_pkt;
	uint32_t packet_length;
	uint32_t received_size;

	uint8_t *rx_buf = (uint8_t *)fboot_supervisor_clear();
	uint8_t *rx_buf_backup = rx_buf;

	while (true) {
		xmodem_packet pkt;
		uint32_t img_length = 0;
		int32_t res;
		uint64_t start_uptime_ms;
		uint64_t end_uptime_ms;
img_request:
		is_first_pkt = 1;
		packet_count = 1;
		img_length = 0;
		rx_buf = rx_buf_backup;

		flush_rx_fifo();
		push_tx_fifo(IMG_REQUEST);

receive_packet:
		start_uptime_ms = get_uptime_ms();

		while (1) {
			(void)wdt_cmrt_feed(NULL, 0);

			if (poll_rx_fifo(&pkt.preamble) == RX_FIFO_HAS_DATA) {
				break;
			}
			end_uptime_ms = get_uptime_ms();

			/* timeout 1s, request to start over */
			if (end_uptime_ms - start_uptime_ms > TIMEOUT_MS) {
				goto img_request;
			}
		}

		received_size = 0;

		/* if reached here, UART received a character */
		if (pkt.preamble == _SOH) {
			data_length = SOH_PKT_DATA_SIZE;
		} else if (pkt.preamble == _STX) {
			data_length = STX_PKT_DATA_SIZE;
		} else if (pkt.preamble == _CAN) {
			/* Cancel, make receiver start to request again  */
			goto img_request;
		} else if (pkt.preamble == _EOT) {
			if (pkt.preamble == _EOT) {
				cmrt_raw_footer_t raw;

				res = fboot_load_image((uint32_t *)(uintptr_t)rx_buf_backup,
									   (size_t)img_length, &raw, NULL);
				flush_rx_fifo();
				push_tx_fifo(_ACK);
				if (res < 0) {
					/* verification fail */
					goto img_request;
				}
				fboot_supervisor_start();
			}
		} else {
			flush_rx_fifo();
			push_tx_fifo(_NAK);
			goto receive_packet;
		}

		/* Packet size : preamble(1B) + No.(1B) + Rev.No.(1B), Data(128 or 1024B), CRC(2B) */
		/* below packet_length is the size without preamble */
		packet_length = PKT_NUM_SIZE + PKT_NUM_SIZE + data_length + CRC_SIZE;
		received_size = read_data_in_fifo(&pkt.pkt_num, packet_length);
		if (packet_length == received_size) {
			packet_length += PREAMBLE_SIZE;

			if (verify_packet(&pkt, data_length, packet_count) == true) {
				packet_count++;

				if (is_first_pkt == 1) {
					uint32_t img_hdr_size = sizeof(cmrt_img_header_t);

					for (int i = 0; i < data_length - img_hdr_size; i++)
						*(rx_buf++) = pkt.data[img_hdr_size + i];

					img_length = (uint32_t)pkt.data[0];
					img_length |= (uint32_t)pkt.data[1] << 8;
					img_length |= (uint32_t)pkt.data[2] << 16;
					img_length |= (uint32_t)pkt.data[3] << 24;

					uint32_t mirror;

					mirror = (uint32_t)pkt.data[4];
					mirror |= (uint32_t)pkt.data[5] << 8;
					mirror |= (uint32_t)pkt.data[6] << 16;
					mirror |= (uint32_t)pkt.data[7] << 24;

					cmrt_img_header_t hdr;

					hdr.length = img_length;
					hdr.mirror = mirror;

					if (cmrt_is_valid_hdr(&hdr, MAX_SIZE) == false) {
						flush_rx_fifo();
						push_tx_fifo(_NAK);
						goto receive_packet;
					}

					is_first_pkt = 0;
				} else {
					for (int i = 0; i < data_length; i++) {
						*(rx_buf++) = pkt.data[i];
					}
				}

				flush_rx_fifo();
				push_tx_fifo(_ACK);
			} else {
				flush_rx_fifo();
				push_tx_fifo(_NAK);
			}
		} else {
			/* clear buffer */
			flush_rx_fifo();
			push_tx_fifo(_NAK);
		}

		goto receive_packet;
	}
	/* never reach here */
	__asm__ ("wfi");
}
