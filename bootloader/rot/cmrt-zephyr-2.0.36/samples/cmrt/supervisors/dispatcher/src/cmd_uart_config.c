/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdio.h>
#include <string.h>

#include <zephyr.h>
#include <device.h>
#include <teefs.h>
#ifdef CONFIG_CMRT_TEEDEV_FLASH
#include <teedev_flash.h>
#else
#include <teedev_dmac.h>
#endif

#include <uart.h>
#ifdef CONFIG_UART_NS16550
#include <drivers/serial/uart_ns16550.h>
#endif

#define UART_CONFIG "uart_config"
#include "common.h"

enum {
	UART_SET_CONFIG = 1,
	UART_RESET_DEFAULT_CONFIG = 2,
	UART_ENABLE = 3,
	UART_DISABLE = 4,
	UART_GET_CONFIG = 5,
};

typedef struct {
	u32_t cmd;
	u32_t baudrate;
	u8_t parity;
	u8_t stop_bits;
	u8_t data_bits;
	u8_t flow_ctrl;
} uart_args;

static int uart_config_set(void *input, u32_t in_used, void *output,
			   u32_t *out_used, u32_t out_size)
{
	uart_args *ucc = (uart_args *)input;
	uart_args *argsout = (uart_args *)output;
	info("UART Command: cmd = %d\n", ucc->cmd);

	if (out_size < sizeof(*argsout)) {
		err("output buffer too small\n");
		return -ENOSPC;
	}

	if (in_used > out_size) {
		err("Output buffer is too small %u vs %u\n", in_used, *out_used);
		return -ENOSPC;
	}
	switch (ucc->cmd) {
	case UART_SET_CONFIG:
	case UART_GET_CONFIG:
	case UART_RESET_DEFAULT_CONFIG:
	case UART_ENABLE:
	case UART_DISABLE:
		break;
	default:
		err("Unknown command : %d\n", ucc->cmd);
		return -ENOTSUP;
	}

	const struct device *uart = device_get_binding("uart0");
	if (!uart) {
		err("Device I/O error\n");
		return -ENODEV;
	}
	int res = 0;
	*argsout = *ucc;

	if (ucc->cmd == UART_SET_CONFIG) {
		info("UART set config baudrate = %d, parity = %hu\n", ucc->baudrate, ucc->parity);
		info("UART set config stopbits = %d, databits = %hu\n", ucc->stop_bits, ucc->data_bits);
		info("UART set config flowcontrol = %hu\n", ucc->flow_ctrl);
		switch (ucc->baudrate) {
		/* case 4800: */
		case 9600:
		/* case 19200: */
		case 38400:
		case 115200:
			break;
		default:
			err("%d: unsupported baud rate\n", ucc->baudrate);
			return -ENOTSUP;
		}
		if (ucc->parity > 4) {
			err("%d: unsupported parity\n", ucc->parity);
			return -ENOTSUP;
		}
		if (ucc->stop_bits > 3) {
			err("%d: unsupported stop bits\n", ucc->stop_bits);
			return -ENOTSUP;
		}
		if (ucc->data_bits > 3) {
			err("%d: unsupported data bits\n", ucc->data_bits);
			return -ENOTSUP;
		}
		if (ucc->flow_ctrl > 2) {
			err("%d: unsupported flow control\n", ucc->flow_ctrl);
			return -ENOTSUP;
		}
		struct uart_config uc = {
			.baudrate = ucc->baudrate,
			.parity = ucc->parity,
			.stop_bits = ucc->stop_bits,
			.data_bits = ucc->data_bits,
			.flow_ctrl = ucc->flow_ctrl,
		};
#ifdef CONFIG_UART_NS16550
		res = uart_configure(uart, &uc);
		if (!res) res = uart_drv_cmd(uart, CMD_SET_NOP, 0);
		struct uart_config tmp;
		res = uart_config_get(uart, &tmp);
		if (res) {
			err("uart_config_get failed: %d\n", res);
			return -1;
		}
		if (memcmp(&tmp, &uc, sizeof(struct uart_config))) {
			err("uart_config_get returned different data!\n");
			res = -2;
			return res;
		} else
			info("UART configuration updated successfully\n");
#endif
	}
	if (ucc->cmd == UART_RESET_DEFAULT_CONFIG) {
		info("UART: reset configuration from file stored in teefs\n");
		res = teefs_open(UART_CONFIG, sizeof(UART_CONFIG)-1, 0);
		if (res >= 0) {
			int fd = res;
			struct uart_config uc;
			size_t len = sizeof(uc);
			res = teefs_read(fd, &uc, &len);
			teefs_close(fd);
			if ((res >= 0) && (len == sizeof(uc))) {
				res = uart_configure(uart, &uc);
				if (!res) res = uart_drv_cmd(uart, CMD_SET_NOP, 0);
			}
		}
	}
	if (ucc->cmd == UART_ENABLE) {
		info("Enable UART\n");
		uart_drv_cmd(uart, CMD_SET_NOP, 0);
	}
	if (ucc->cmd == UART_DISABLE) {
		info("Disable UART\n");
		uart_drv_cmd(uart, CMD_SET_NOP, 1);
	}
	if (ucc->cmd == UART_GET_CONFIG) {
		info("Get UART Config\n");
		struct uart_config conf;
		res = uart_config_get(uart, &conf);
		if (res) {
			err("uart_config_get failed: %d\n", res);
			return -1;
		}
		argsout->cmd = ucc->cmd;
		argsout->baudrate = conf.baudrate;
		argsout->parity = conf.parity;
		argsout->stop_bits = conf.stop_bits;
		argsout->data_bits = conf.data_bits;
		argsout->flow_ctrl = conf.flow_ctrl;
	}
	*out_used = sizeof(*argsout);
	return res;
}

const cmd_t cmd_uart = { CMDID_UART,
			"UART", "Change UART config", uart_config_set };
