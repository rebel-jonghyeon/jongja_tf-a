/*
<<<<<<< HEAD
 * Copyright (c) 2023, Advanced Micro Devices, Inc. All rights reserved.
=======
 * Copyright (c) 2023-2025, Advanced Micro Devices, Inc. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <common/debug.h>
#include <common/fdt_fixup.h>
#include <common/fdt_wrappers.h>
#include <drivers/arm/dcc.h>
#include <drivers/arm/pl011.h>
#include <drivers/cadence/cdns_uart.h>
#include <drivers/console.h>
#include <libfdt.h>
#include <plat_console.h>
<<<<<<< HEAD
=======
#include <plat_fdt.h>
>>>>>>> upstream_import/upstream_v2_14_1

#include <platform_def.h>
#include <plat_private.h>

<<<<<<< HEAD
static console_t console;

#if (defined(XILINX_OF_BOARD_DTB_ADDR) && !IS_TFA_IN_OCM(BL31_BASE))
=======
#if !(CONSOLE_IS(none))
static console_t boot_console;
static console_holder boot_hd_console;
#if defined(CONSOLE_RUNTIME)
static console_t runtime_console;
static console_holder rt_hd_console;
#endif

#if ((CONSOLE_IS(dtb) || RT_CONSOLE_IS(dtb)) && (XLNX_DT_CFG == 1))
static dt_uart_info_t dt_uart_info;
#endif

/**
 * register_console() - Registers the uart with console list.
 * @consoleh: Console holder structure with UART base address,
 *  UART clock, UART buad rate, flags & console type
 * @console: Pointer to the console information structure.
 */
static void register_console(const console_holder *consoleh, console_t *console)
{
	int32_t rc = 0;

	switch (consoleh->console_type) {
#if defined(PLAT_zynqmp)
	case CONSOLE_CDNS:
		rc = console_cdns_register(consoleh->base,
				consoleh->clk,
				consoleh->baud_rate,
				console);
		break;
#else
	case CONSOLE_PL011:
		rc = console_pl011_register(consoleh->base,
				consoleh->clk,
				consoleh->baud_rate,
				console);
		break;
#endif
	case CONSOLE_DCC:
		rc = console_dcc_register(console);
		break;
	default:
		INFO("Invalid console type\n");
		break;
	}

	if (rc == 0) {
		panic();
	}

	console_set_scope(console, consoleh->console_scope);
}

#if ((CONSOLE_IS(dtb) || RT_CONSOLE_IS(dtb)) && (XLNX_DT_CFG == 1))
>>>>>>> upstream_import/upstream_v2_14_1
/**
 * get_baudrate() - Get the baudrate form DTB.
 * @dtb: Address of the Device Tree Blob (DTB).
 *
 * Return: On success returns the baudrate; on failure returns an error.
 */
static int32_t get_baudrate(void *dtb)
{
	int node;
	int32_t ret = 0;
	const char *prop, *path;
	char *end;
	int32_t baud_rate = 0;

	node = fdt_path_offset(dtb, "/secure-chosen");
	if (node < 0) {
		node = fdt_path_offset(dtb, "/chosen");
		if (node < 0) {
			ret = -FDT_ERR_NOTFOUND;
			goto error;
		}
	}

	prop = fdt_getprop(dtb, node, "stdout-path", NULL);
	if (prop == NULL) {
		ret = -FDT_ERR_NOTFOUND;
		goto error;
	}

	/* Parse string serial0:115200n8 */
	path = strchr(prop, ':');
	if (!path) {
		ret = -FDT_ERR_NOTFOUND;
		goto error;
	} else {

		baud_rate = strtoul(path + 1, &end, 10);
		if (baud_rate == 0 && end == path) {
			ERROR("Conversion error occurred: %d\n", baud_rate);
			ret = -FDT_ERR_NOTFOUND;
			goto error;
		}
		ret = baud_rate;
	}

error:
	return ret;
}

/**
 * get_node_status() - Get the DTB node status.
 * @dtb: Address of the Device Tree Blob (DTB).
 * @node: Node address in the device tree.
 *
 * Return: On success, it returns 1; on failure, it returns an 0.
 */
static uint32_t get_node_status(void *dtb, int node)
{
	const char *status_cell;
	uint32_t status = 0;

	status_cell = fdt_getprop(dtb, node, "status", NULL);
	if (!status_cell || strcmp(status_cell, "okay") == 0) {
		status = 1;
	} else {
		status = 0;
	}

	return status;
}

/**
 * fdt_add_uart_info() - Add DTB information to a UART structure.
 * @info: Pointer to the UART information structure.
 * @node: Node address in the device tree.
 * @dtb: Address of the Device Tree Blob(DTB).
 *
<<<<<<< HEAD
 * Return: On success, it returns 1; on failure, it returns an 0.
 */
static uint32_t fdt_add_uart_info(dt_uart_info_t *info, int node, void *dtb)
{
	uintptr_t base_addr;
	const char *com;
	uint32_t ret = 0;
=======
 * Return: On success, it returns 0; on failure, it returns -1 or -FDT_ERR_NOTFOUND.
 */
static int32_t fdt_add_uart_info(dt_uart_info_t *info, int node, void *dtb)
{
	uintptr_t base_addr;
	const char *com;
	int32_t ret = 0;
	uint32_t status;
>>>>>>> upstream_import/upstream_v2_14_1

	com = fdt_getprop(dtb, node, "compatible", NULL);
	if (com != NULL) {
		strlcpy(info->compatible, com, sizeof(info->compatible));
	} else {
		ERROR("Compatible property not found in DTB node\n");
<<<<<<< HEAD
		ret  = -FDT_ERR_NOTFOUND;
		goto error;
	}

	ret = fdt_get_reg_props_by_index(dtb, node, 0, &base_addr, NULL);
	if (ret >= 0) {
		info->base = base_addr;
	} else {
		ERROR("Failed to retrieve base address. Error code: %d\n", ret);
		ret  = -FDT_ERR_NOTFOUND;
		goto error;
	}

	info->status = get_node_status(dtb, node);
	info->baud_rate = get_baudrate(dtb);

=======
		ret = -FDT_ERR_NOTFOUND;
		goto error;
	}

	status = get_node_status(dtb, node);
	if (status == 0) {
		ERROR("Uart node is disabled in DTB\n");
		ret = -FDT_ERR_NOTFOUND;
		goto error;
	}

	if (strncmp(info->compatible, DT_UART_DCC_COMPAT, strlen(DT_UART_DCC_COMPAT)) != 0) {
		ret = fdt_get_reg_props_by_index(dtb, node, 0, &base_addr, NULL);
		if (ret >= 0) {
			info->base = base_addr;
		} else {
			ERROR("Failed to retrieve base address. Error code: %d\n", ret);
			ret = -FDT_ERR_NOTFOUND;
			goto error;
		}

		info->baud_rate = get_baudrate(dtb);

		if (strncmp(info->compatible, DT_UART_CAD_COMPAT,
					strlen(DT_UART_CAD_COMPAT)) == 0) {
			info->console_type = CONSOLE_CDNS;
		} else if (strncmp(info->compatible, DT_UART_PL011_COMPAT,
					strlen(DT_UART_PL011_COMPAT)) == 0) {
			info->console_type = CONSOLE_PL011;
		} else {
			ERROR("Incompatible uart node in DTB\n");
			ret = -FDT_ERR_NOTFOUND;
		}
	} else {
		info->console_type = CONSOLE_DCC;
	}

>>>>>>> upstream_import/upstream_v2_14_1
error:
	return ret;
}

/**
 * fdt_get_uart_info() - Get the uart information form DTB.
 * @info: Pointer to the UART information structure.
 *
 * Return: On success, it returns 0; on failure, it returns an error+reason.
 */
static int fdt_get_uart_info(dt_uart_info_t *info)
{
<<<<<<< HEAD
	int node, ret = 0;
	void *dtb = (void *)XILINX_OF_BOARD_DTB_ADDR;

	if (fdt_check_header(dtb) != 0) {
		ERROR("Can't read DT at %p\n", dtb);
		ret  = -FDT_ERR_NOTFOUND;
		goto error;
	}

	ret = fdt_open_into(dtb, dtb, XILINX_OF_BOARD_DTB_MAX_SIZE);
	if (ret < 0) {
		ERROR("Invalid Device Tree at %p: error %d\n", dtb, ret);
		ret  = -FDT_ERR_NOTFOUND;
=======
	int node = 0, ret = 0;
	void *dtb = (void *)plat_retrieve_dt_addr();

	ret = is_valid_dtb(dtb);
	if (ret < 0) {
		ERROR("Invalid Device Tree at %p: error %d\n", dtb, ret);
>>>>>>> upstream_import/upstream_v2_14_1
		goto error;
	}

	node = fdt_get_stdout_node_offset(dtb);
	if (node < 0) {
		ERROR("DT get stdout node failed : %d\n", node);
<<<<<<< HEAD
		ret  = -FDT_ERR_NOTFOUND;
=======
>>>>>>> upstream_import/upstream_v2_14_1
		goto error;
	}

	ret = fdt_add_uart_info(info, node, dtb);
	if (ret < 0) {
		ERROR("Failed to add DT UART info: %d\n", ret);
<<<<<<< HEAD
		ret  = -FDT_ERR_NOTFOUND;
=======
>>>>>>> upstream_import/upstream_v2_14_1
		goto error;
	}

error:
	return ret;
}
<<<<<<< HEAD

/**
 * check_fdt_uart_info() - Check early uart info with DTB uart info.
 * @info: Pointer to the UART information structure.
 *
 * Return: On success, it returns 0; on failure, it returns an error+reason.
 */
static int check_fdt_uart_info(dt_uart_info_t *info)
{
	uint32_t ret = 0;

	if (info->status == 0) {
		ret = -ENODEV;
		goto error;
	}

	if ((info->base == console.base) &&
	   (info->baud_rate == UART_BAUDRATE) && !CONSOLE_IS(dcc)) {
		ret = -ENODEV;
		goto error;
	}

error:
	return ret;
}

/**
 * console_boot_end() - Unregister the console_t instance form the console list.
 * @boot_console: Pointer to the console information structure.
 */
static void console_boot_end(console_t *boot_console)
{
	if (CONSOLE_IS(dcc)) {
		console_dcc_unregister();
	} else {
		console_flush();
		(void)console_unregister(boot_console);
	}
}

/**
 * setup_runtime_console() - Registers the runtime uart with console list.
 * @clock: UART clock.
 * @info: Pointer to the UART information structure.
 */
static void setup_runtime_console(uint32_t clock, dt_uart_info_t *info)
{
	static console_t bl31_runtime_console;
	uint32_t rc;

#if defined(PLAT_zynqmp)
	rc = console_cdns_register(info->base,
				   clock,
				   info->baud_rate,
				   &bl31_runtime_console);
#else
	rc = console_pl011_register(info->base,
				    clock,
				    info->baud_rate,
				    &bl31_runtime_console);
#endif
	if (rc == 0) {
		panic();
	}

	console_set_scope(&bl31_runtime_console,
			  CONSOLE_FLAG_BOOT | CONSOLE_FLAG_RUNTIME |
			  CONSOLE_FLAG_CRASH);
}


/**
 * runtime_console_init() - Initializes the run time console information.
 * @uart_info: Pointer to the UART information structure.
 * @bl31_boot_console: Pointer to the console information structure.
 * @clock: UART clock.
 *
 * Return: On success, it returns 0; on failure, it returns an error+reason;
 */
static int32_t runtime_console_init(dt_uart_info_t *uart_info,
			  console_t *bl31_boot_console,
			  uint32_t clock)
{
	int32_t rc = 0;

	/* Parse UART information from Device Tree Blob (DTB) */
	rc = fdt_get_uart_info(uart_info);
	if (rc < 0) {
		rc = -FDT_ERR_NOTFOUND;
	}

	if (strncmp(uart_info->compatible, DT_UART_COMPAT,
		   strlen(DT_UART_COMPAT)) == 0) {

		if (check_fdt_uart_info(uart_info) == 0) {
			setup_runtime_console(clock, uart_info);
			console_boot_end(bl31_boot_console);
			INFO("Runtime console setup\n");
		} else {
			INFO("Early console and DTB console are same\n");
		}
	} else if (strncmp(uart_info->compatible, DT_UART_DCC_COMPAT,
			  strlen(DT_UART_DCC_COMPAT)) == 0) {
		rc = console_dcc_register();
		if (rc == 0) {
			panic();
		}
		console_boot_end(bl31_boot_console);
	} else {
		WARN("BL31: No console device found in DT.\n");
	}

	return rc;
}
=======
>>>>>>> upstream_import/upstream_v2_14_1
#endif

void setup_console(void)
{
<<<<<<< HEAD
	uint32_t rc;
	uint32_t uart_clk = get_uart_clk();

#if defined(PLAT_zynqmp)
	if (CONSOLE_IS(cadence) || (CONSOLE_IS(cadence1))) {
		rc = console_cdns_register(UART_BASE,
					   uart_clk,
					   UART_BAUDRATE,
					   &console);
		if (rc == 0) {
			panic();
		}

		console_set_scope(&console, CONSOLE_FLAG_BOOT |
				  CONSOLE_FLAG_RUNTIME | CONSOLE_FLAG_CRASH);
	}
#else
	if (CONSOLE_IS(pl011) || (CONSOLE_IS(pl011_1))) {
		/* Initialize the console to provide early debug support */
		rc = console_pl011_register((uint32_t)UART_BASE,
					   uart_clk,
					   (uint32_t)UART_BAUDRATE,
					   &console);
		if (rc == 0) {
			panic();
		}

		console_set_scope(&console, CONSOLE_FLAG_BOOT |
				  CONSOLE_FLAG_RUNTIME | CONSOLE_FLAG_CRASH);
	}
#endif
	if (CONSOLE_IS(dcc)) {
		/* Initialize the dcc console for debug */
		rc = console_dcc_register();
		if (rc == 0) {
			panic();
		}
	}
	INFO("BL31: Early console setup\n");

#if (defined(XILINX_OF_BOARD_DTB_ADDR) && !IS_TFA_IN_OCM(BL31_BASE))
	static dt_uart_info_t uart_info = {0};

	/* Initialize the runtime console using UART information from the DTB */
	rc = runtime_console_init(&uart_info, &console, uart_clk);
	if (rc < 0) {
		ERROR("Failed to initialize runtime console: %d\n", rc);
	}
#endif
}
=======
	/* This is hardcoded console setup just in case that DTB console fails */
	boot_hd_console.base = (uintptr_t)UART_BASE;
	boot_hd_console.baud_rate = (uint32_t)UART_BAUDRATE;
	boot_hd_console.clk = get_uart_clk();
	boot_hd_console.console_scope = CONSOLE_FLAG_BOOT | CONSOLE_FLAG_CRASH;
	boot_hd_console.console_type = UART_TYPE;

	/* For DT code decoding uncomment console registration below */
	/* register_console(&boot_hd_console, &boot_console); */

#if ((CONSOLE_IS(dtb) || RT_CONSOLE_IS(dtb)) && (XLNX_DT_CFG == 1))
	/* Parse DTB console for UART information  */
	if (fdt_get_uart_info(&dt_uart_info) == 0) {
		if (CONSOLE_IS(dtb)) {
			boot_hd_console.base = dt_uart_info.base;
			boot_hd_console.baud_rate = dt_uart_info.baud_rate;
			boot_hd_console.console_type = dt_uart_info.console_type;
		}
	} else {
		ERROR("Failed to initialize DT console or console node is disabled\n");
	}
#endif

	/* Initialize the boot console */
	register_console(&boot_hd_console, &boot_console);

	INFO("BL31: Early console setup\n");

#ifdef CONSOLE_RUNTIME
	rt_hd_console.base = (uintptr_t)RT_UART_BASE;
	rt_hd_console.baud_rate = (uint32_t)UART_BAUDRATE;
	rt_hd_console.console_type = RT_UART_TYPE;

#if (RT_CONSOLE_IS(dtb) && (XLNX_DT_CFG == 1))
	if (dt_uart_info.base != 0U) {
		rt_hd_console.base = dt_uart_info.base;
		rt_hd_console.baud_rate = dt_uart_info.baud_rate;
		rt_hd_console.console_type = dt_uart_info.console_type;
	}
#endif

	if ((rt_hd_console.console_type == boot_hd_console.console_type) &&
			(rt_hd_console.base == boot_hd_console.base)) {
		console_set_scope(&boot_console,
				CONSOLE_FLAG_BOOT | CONSOLE_FLAG_CRASH | CONSOLE_FLAG_RUNTIME);
		INFO("Successfully initialized runtime console\n");
	} else {
		rt_hd_console.clk = get_uart_clk();
		rt_hd_console.console_scope = CONSOLE_FLAG_RUNTIME;

		register_console(&rt_hd_console, &runtime_console);
		INFO("Successfully initialized new runtime console\n");
	}
#endif
}
#else
void setup_console(void)
{
}
#endif
>>>>>>> upstream_import/upstream_v2_14_1
