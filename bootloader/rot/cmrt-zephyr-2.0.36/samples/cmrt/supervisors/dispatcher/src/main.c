/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <zephyr.h>
#include <stdio.h>
#include <string.h>
#include <linker/linker-defs.h>

#include <fs/teefs.h>
#ifdef CONFIG_CMRT_TEEDEV_FLASH
#include <cri/cmrt/teedev_flash.h>
#else
#include <cri/cmrt/teedev_dmac.h>
#endif

#include <uart.h>
#ifdef CONFIG_UART_NS16550
#include <drivers/serial/uart_ns16550.h>
#endif
#include <cri/cmrt/dd.h>
#include <cri/cmrt/sic.h>
#include "common.h"

#ifdef CONFIG_CMRT_NETWORKING
#include <cri/cmrt/networking.h>
/* Network config. */
static netx_config_t netx_cfg;
#endif

#include <cri/cmrt/scratchpad.h>
#include <cri/cmrt/axi_flash_layout.h>
/*
 * Sample dispatcher monolithic supervisor
 */

#ifdef CONFIG_CMRT_TEEDEV_FLASH
#define TEEFS_BASE AXI_FLASH_TEEFS_BASE
/*
 * DEMO_FS_BLOCKS = log2(number_of_blocks
 *                = log2(teefs_size / (4 * 1024)
 *                = __builtin_ctz(teefs_size >> 12)
 */
#define TEEFS_BLOCKS (__builtin_ctz(AXI_FLASH_TEEFS_SZ >> 12))
#else
/* 512KB SAC: 0x2F800 reserves 190kB for os.img, 64KB teefs and 2kB for logs */
#define TEEFS_BASE (CONFIG_RISCV_SAC_BASE_ADDR +		\
		    (CONFIG_FPGA_SAC_SIZE / 2) + 0x2F800)
#define TEEFS_BLOCKS 4 /* 1 << 4 = 16 blocks of 4k each, 64KB in total. */
#endif
#define TEEFS_MP "" /* mount point */
#define TEEFS_MPLEN (sizeof(TEEFS_MP) - 1)

#ifdef CONFIG_CMRT_AXI
#define SCRATCHPAD_START AXI_DDR_FILE_XFER_START
#define SCRATCHPAD_END (AXI_DDR_FILE_XFER_START + AXI_DDR_FILE_XFER_SIZE)
#else
#define SCRATCHPAD_START ((u32_t)&_image_ram_end)
#define SCRATCHPAD_END (CONFIG_RISCV_RAM_BASE_ADDR + KB(CONFIG_RISCV_RAM_SIZE_KB))
#endif
#define SCRATCHPAD_SIZE (SCRATCHPAD_END - SCRATCHPAD_START)

#define NO_ENCRYPTION

const static char version_info[] __used = SUPERVISOR_VERSION_INFO;

/* Update SIC.SW_BOOT_STATUS register. */
static void set_boot_status(u32_t bits, u32_t mask)
{
	u32_t value = cri_read_reg(CMRT_SIC_BASE, R_SW_BOOT_STATUS);
	value &= ~mask;
	value |= bits & mask;
	cri_write_reg(CMRT_SIC_BASE, R_SW_BOOT_STATUS, value);
}

/* The command array. */
const cmd_t *const cmds[] = {
	&cmd_list,
	&cmd_echo,
	&cmd_sha2,
	&cmd_ecdsa,
	&cmd_aes,
#ifdef CONFIG_CMRT_SID
	&cmd_sid,
#endif
#ifdef CONFIG_CMRT_FFDH
	&cmd_ffdh,
#endif
	&cmd_rsa,
#ifdef CONFIG_UART_NS16550
	&cmd_uart,
#endif
#ifdef CONFIG_CMRT_ECIES
	&cmd_ecies,
#endif
#ifdef CONFIG_CRI_OMC_EMULATED_OTP
	&cmd_otp,
#endif
	&cmd_ecdh,
#if defined(CONFIG_CMRT_S3HC) || defined (CONFIG_CMRT_S3HC2)
	&cmd_sha3,
#endif
	&cmd_random,
	&cmd_rsa_key_exch,
	&cmd_hmac,
#ifdef CONFIG_CMRT_CCP
	&cmd_ccp,
#endif
	&cmd_kdc,
	&cmd_fmc,
	&cmd_enable_debug,
#ifdef CONFIG_SV_PERF_MEAS
	&cmd_perf,
#endif
};
const u32_t nr_cmds = (sizeof(cmds) / sizeof(cmds[0]));

/* Input output buffer headers are located at the start of SAC memory. */
buffer_ctrl_t *sac_buffers = (buffer_ctrl_t *)CONFIG_RISCV_SAC_BASE_ADDR;

/*
 * Initialize SAC buffer headers.
 * Use first half for input parameters and other half for output parameters.
 */
static void init_sac_buffer_headers(void)
{
	u32_t usable_sac = (CONFIG_FPGA_SAC_SIZE/2) - sizeof(buffer_ctrl_t);
	*sac_buffers = (buffer_ctrl_t) {
		{sizeof(buffer_ctrl_t), usable_sac/2},
		{sizeof(buffer_ctrl_t) + (usable_sac/2), usable_sac/2}
	};
};

/* Return pointers to SAC buffer header fields. */
static void set_buffer_pointers(u8_t **in, u32_t **i_used, u32_t **i_size,
				u8_t **out, u32_t **o_used, u32_t **o_size)
{
	*in = (u8_t *) (CONFIG_RISCV_SAC_BASE_ADDR + sac_buffers->to_esw.offset);
	*out = (u8_t *) (CONFIG_RISCV_SAC_BASE_ADDR + sac_buffers->to_hlos.offset);
	*i_used = &sac_buffers->to_esw.used;
	*i_size = &sac_buffers->to_esw.size;
	*o_used = &sac_buffers->to_hlos.used;
	*o_size = &sac_buffers->to_hlos.size;
}

#define PRINT_BUF_CTRL() \
	printk("in 0x%8x %u/%u, out 0x%8x %u/%u\n", \
		CONFIG_RISCV_SAC_BASE_ADDR + sac_buffers->to_esw.offset, \
		sac_buffers->to_esw.used, \
		sac_buffers->to_esw.size, \
		CONFIG_RISCV_SAC_BASE_ADDR + sac_buffers->to_hlos.offset, \
		sac_buffers->to_hlos.used, \
		sac_buffers->to_hlos.size)

/* Create initial files to an empty TEEFS filesystem. */
static int create_initial_files(void)
{
	int res = 0;
#ifdef CONFIG_UART_NS16550
#define UART_CONFIG "uart_config"

	/* Initial UART configuration. */
	static const struct uart_config uc = {
		.baudrate = 115200,
		.parity = UART_CFG_PARITY_NONE,
		.stop_bits = UART_CFG_STOP_BITS_1,
		.data_bits = UART_CFG_DATA_BITS_8,
		.flow_ctrl = UART_CFG_FLOW_CTRL_NONE,
	};
	int fd1 = teefs_create(UART_CONFIG, sizeof(UART_CONFIG) - 1,
			       &uc, sizeof(uc));
	teefs_close(fd1);
	if (fd1 < 0) res = fd1;
#endif
#ifdef CONFIG_CMRT_NETWORKING
	/* Initial NETX configuration. */
	netx_cfg_set_default(&netx_cfg);
	int fd2 = teefs_create(NETX_CONFIG, sizeof(NETX_CONFIG) - 1,
			       &netx_cfg, sizeof(netx_cfg));
	teefs_close(fd2);
	if (fd2 < 0) res = fd2;
#endif
	return res;
}

#ifdef CONFIG_UART_NS16550
/* Setup configuration based on files in TEEFS filesystem. */
static int initial_uart_config(bool disable)
{
	const struct device *uart = device_get_binding("uart0");
	if (!uart) return -ENODEV;

	int res = teefs_open(UART_CONFIG, sizeof(UART_CONFIG) - 1, 0);
	if (res >= 0) {
		/* File exists, configure UART. */
		int fd = res;
		struct uart_config uc;
		size_t len = sizeof(uc);
		int res = teefs_read(fd, &uc, &len);
		teefs_close(fd);
		if ((res >= 0) && (len == sizeof(uc))) {
			res = uart_configure(uart, &uc);
			if (!res) res = uart_drv_cmd(uart, CMD_SET_NOP, 0);
			return res;
		}
	}
	if (disable) {
		printk("Disable UART due to error :%d\n", res);
		/* No file or error above, disable UART. */
		uart_drv_cmd(uart, CMD_SET_NOP, 1);
	}
	return res;
}
#endif

#ifdef CONFIG_CMRT_NETWORKING
static int initial_netx_config(void)
{
	netx_cfg_set_default(&netx_cfg);

	netx_config_t teefs_cfg;
	int res = teefs_open(NETX_CONFIG, sizeof(NETX_CONFIG) - 1, 0);
	if (res >= 0) {
		/* File exists, configure netx. */
		int fd = res;
		size_t size = sizeof(teefs_cfg);
		res = teefs_read(fd, &teefs_cfg, &size);
		(void)teefs_close(fd);
		if ((res >= 0) && (size == sizeof(teefs_cfg))) {
			printk("Setting netx config from TEEFS\n");
			memcpy(&netx_cfg, &teefs_cfg, sizeof(netx_cfg));
		}
	}
	cri_network_init_from_cfg(&netx_cfg);
	return res;
}
#endif

/*
 * Process incoming request.
 * Lookup command and call requested operation.
 */
int process_request(u32_t cmd_id,
		    u8_t *in, u32_t *i_used, u32_t *i_size,
		    u8_t *out, u32_t *o_used, u32_t *o_size)
{
	int ret = EINVAL;

	/* Forget past output. */
	*o_used = 0;
	PRINT_BUF_CTRL();

	u32_t cmd_num = cmd_id - CMDID_BASE;
	printk("cmd %d:...\n", cmd_num);
	if (*i_size < *i_used) {
		printk("Input buffer overflow!\n");
		return ret;
	}
	for (int i = 0; i < nr_cmds; i++) {
		if (cmds[i]->id == cmd_id) {
			const cmd_t *cmd = cmds[i];
			ret = cmd->run(in, *i_used, out, o_used, *o_size);
			break;
		}
	}
	printk("cmd %d: ret: %s (%d)\n", cmd_num, ret ? "Err" : "OK", ret);
	PRINT_BUF_CTRL();
	return ret;
}

static int create_filesystem(tee_device_t *dev)
{
	printk("Creating filesystem\n");
	int res = teefs_mkfs(dev, 0);
	if (res < 0) {
		printk("teefs_mkfs failed: %d!\n", res);
		return res;
	}
	res = teefs_mount(TEEFS_MP, TEEFS_MPLEN, dev, TEEFS_FLAG_AUTOSYNC);
	if (res < 0) {
		printk("teefs_mount failed: %d!\n", res);
		return res;
	}
	res = create_initial_files();
	if (res < 0) {
		printk("Failed to create initial files: %d!\n", res);
	}
	return res;
}

#define FREE_RAM_START ((u32_t)&_image_ram_end)
#define FREE_RAM_END (CONFIG_RISCV_RAM_BASE_ADDR + KB(CONFIG_RISCV_RAM_SIZE_KB))

#if 1 /* samples may have its own code, 0x5fXX, to be recognized from HLOS */
#include <drivers/cmrt/cmrt.h>
#define SUPERVISOR_SAMPLE_STARTED 0x5f020000
#endif

int main(void)
{
/* Write buffer headers to the start of SAC, client program will read it
 * before sending messages. */
	init_sac_buffer_headers();

/* Update SIC.SW_BOOT_STATUS register. */
	set_boot_status(SUPERVISOR_RUNNING_ID, SUPERVISOR_RUNNING_ID);
#ifdef SUPERVISOR_SAMPLE_STARTED
	cmrt_write_reg(CMRT_SIC_BASE, R_SCRATCH_0, SUPERVISOR_SAMPLE_STARTED);
#endif
	printk("Supervisor (dispatcher) %s running...\n", version_info);

	printk("SRAM left: %u bytes\n", FREE_RAM_END - FREE_RAM_START);

	/* Create and mount filesystem. */
#ifdef NO_ENCRYPTION
	const u8_t *path = NULL;
	size_t pathlen = 0;
#else
	const u8_t *path = "secret pin";
	size_t pathlen = strlen(path);
#endif
	tee_device_t *dev;
#ifdef CONFIG_CMRT_TEEDEV_FLASH
	dev = teedev_flash_open(TEEFS_BASE, TEEFS_BLOCKS, path, pathlen);
#else
	dev = teedev_dmac_open(TEEFS_BASE, TEEFS_BLOCKS, path, pathlen);
#endif
	if (dev == NULL) {
		printk("teedev open failed!\n");
		return -ENODEV;
	}
	int res = teefs_mount(TEEFS_MP, TEEFS_MPLEN, dev, TEEFS_FLAG_AUTOSYNC);
	if (res < 0) {
		printk("no teefs found to be mounted: %d\n", res);
		res = create_filesystem(dev);
	}
	if (res < 0) {
		printk("teefs mkfs failed: %d!\n", res);
		return -EFAULT;
	}
	printk("Filesystem mounted\n");

#ifdef CONFIG_UART_NS16550
	res = initial_uart_config(false);
	if (res < 0) {
		printk("Failed to setup initial UART config: %d!\n", res);
		/* might be intentional, just continue */
	}
#endif
#ifdef CONFIG_CMRT_NETWORKING
	res = initial_netx_config();
	if (res < 0) {
		printk("Failed to setup initial NETX config: %d!\n", res);
		/* might be intentional, just continue */
	}
#endif
	cri_scratchpad_open((void *)SCRATCHPAD_START, SCRATCHPAD_SIZE);

	u8_t *in, *out;
	u32_t *i_used, *i_size, *o_used, *o_size;
	set_buffer_pointers(&in, &i_used, &i_size, &out, &o_used, &o_size);

/* Open a SIC flow 0. */
	cri_sic_t sic = cri_sic_open(0, 0);
	if (!cri_is_valid(sic)) {
		printk("Cannot open SIC\n");
		return -ENODEV;
	}

	for (;;) {
		static alignas(4) u8_t buffer[16];
		size_t buflen = sizeof(buffer);
		u32_t peerid;

/* Set SIC receive buffer. */
		int res = cri_sic_read(sic, buffer, &buflen, &peerid);
		if (res < 0) {
			printk("Failed to setup SIC read from HLOS: %d!\n", res);
			continue;
		}

/* Wait for command from HLOS over SIC. */
		printk("Waiting for SIC command...\n");
		cri_handle_t handles = sic;
		cri_wait(1, &handles, CRI_FOREVER);
		res = cri_sic_sync(sic);
		if (res < 0) {
			printk("Failed to read from HLOS: %d!\n", res);
			continue;
		}

/* Process command. */
		printk("New command...\n");
		const struct {
			u32_t cmd_id;
		} *const r = (void *)buffer;

		if (buflen < sizeof(*r)) {
			printk("Invalid command\n");
			continue;
		}

		int rsp = process_request(r->cmd_id,
					  in, i_used, i_size,
					  out, o_used, o_size);

/* Send return code over SIC to HLOS. */
		res = cri_sic_write(sic, (u8_t *)&rsp, sizeof(rsp), peerid);
		if (res < 0) {
			printk("Failed to setup SIC write to HLOS: %d!\n", res);
			continue;
		}
	}
	return 0; /* Never reached */
}
