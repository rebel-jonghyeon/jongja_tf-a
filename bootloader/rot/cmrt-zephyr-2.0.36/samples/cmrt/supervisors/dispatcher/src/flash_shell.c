/*
 * Copyright (c) 2020 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <flash.h>
#include <stdlib.h>
#include <string.h>
#include <shell/shell.h>

#include <cri/cmrt.h>
#include <cri/cmrt/axi_flash.h>

#define FLASH_SHELL_MODULE "flash"

#define BLOCK_SIZE 0x1000
#define BLOCK_ROUND_DOWN(x) (((uint32_t)(x)) & (~(BLOCK_SIZE-1)))
#define BLOCK_ROUND_UP(len) (((len) + (BLOCK_SIZE-1)) & (~(BLOCK_SIZE-1)))

static int cmd_read(const struct shell *shell, size_t argc, char *argv[])
{
	struct device *flash_dev;
	u32_t addr;
	int cnt;

	if (argc < 2) {
		shell_error(shell, "wrong input");
		return -EINVAL;
	}

	flash_dev = device_get_binding(DT_FLASH_DEV_NAME);
	if (!flash_dev || flash_open(flash_dev)) {
		shell_error(shell, "Flash driver was not found!");
		return -ENODEV;
	}

	addr = strtoul(argv[1], NULL, 16);

	if (argc > 2) {
		cnt = strtoul(argv[2], NULL, 10);
	} else {
		cnt = 1;
	}

	while (cnt--) {
		u32_t data;

		flash_read(flash_dev, addr, &data, sizeof(data));
		shell_print(shell, "0x%08x ", data);
		addr += sizeof(data);
	}
	flash_close(flash_dev);
	shell_print(shell, "");

	return 0;
}

static int cmd_erase(const struct shell *shell, size_t argc, char *argv[])
{
	struct device *flash_dev;
	u32_t addr, size;
	int ret;

	if (argc < 2) {
		shell_error(shell, "wrong input");
		return -EINVAL;
	}

	flash_dev = device_get_binding(DT_FLASH_DEV_NAME);
	if (!flash_dev || flash_open(flash_dev)) {
		shell_error(shell, "Flash driver was not found!");
		return -ENODEV;
	}
	ret = flash_write_protection_set(flash_dev, false);
	if (ret != 0) {
		goto out;
	}

	addr = strtoul(argv[1], NULL, 16);
	size = strtoul(argv[2], NULL, 10);
	addr = BLOCK_ROUND_DOWN(addr);
	size = BLOCK_ROUND_UP(size);

	ret = flash_erase(flash_dev, addr, size);
	if (ret != 0) {
		goto out;
	}
	flash_write_protection_set(flash_dev, true);
	shell_print(shell, "erased %u bytes from 0x%08x", size, addr);

out:
	shell_print(shell, "");
	flash_close(flash_dev);
	return ret;
}

static int cmd_write(const struct shell *shell, size_t argc, char *argv[])
{
#define WRITE_BUF_WORDS (128/4)

	static u32_t wbuf[WRITE_BUF_WORDS];
	struct device *flash_dev;
	u32_t addr, size, start;
	int ret, w = 0;

	if (argc < 2) {
		shell_error(shell, "wrong input");
		return -EINVAL;
	}

	flash_dev = device_get_binding(DT_FLASH_DEV_NAME);
	if (!flash_dev || flash_open(flash_dev)) {
		shell_error(shell, "Flash driver was not found!");
		return -ENODEV;
	}
	ret = flash_write_protection_set(flash_dev, false);
	if (ret != 0) {
		goto out;
	}
	start = addr = strtoul(argv[1], NULL, 16);
	size = (argc - 2) << 2;
	size = BLOCK_ROUND_UP(size);

	ret = flash_erase(flash_dev, BLOCK_ROUND_DOWN(addr), size);
	if (ret != 0) {
		goto out;
	}

	shell_print(shell, "erased %u bytes from 0x%08x", size, BLOCK_ROUND_DOWN(addr));

	for (int i = 2; i < argc; i++) {
		wbuf[w++] = strtoul(argv[i], NULL, 16);
		if (w == WRITE_BUF_WORDS) {
			ret = flash_write(flash_dev, addr, (u8_t *)wbuf, sizeof(wbuf));
			if (ret != 0) {
				goto out;
			}
			addr += sizeof(wbuf);
			w = 0;
		}
	}
	if (w > 0) {
		ret = flash_write(flash_dev, addr, (u8_t *)wbuf, w << 2);
		if (ret != 0) {
			goto out;
		}
	}

	size = (argc - 2) << 2;
	shell_print(shell, "wrote %u bytes to 0x%08x", size, start);

	flash_write_protection_set(flash_dev, true);
out:
	shell_print(shell, "");
	flash_close(flash_dev);
	return ret;
}

SHELL_STATIC_SUBCMD_SET_CREATE(flash_cmds,
	SHELL_CMD(erase, NULL, "<0xaddress> <bytes>", cmd_erase),
	SHELL_CMD(read, NULL, "<0xaddress> <word count>", cmd_read),
	SHELL_CMD(write, NULL, "<0xaddress> <0xdword> <0xdword>...", cmd_write),
	SHELL_SUBCMD_SET_END
);

static int cmd_flash(const struct shell *shell, size_t argc, char **argv)
{
	shell_error(shell, "%s:unknown parameter: %s", argv[0], argv[1]);
	return -EINVAL;
}

SHELL_CMD_ARG_REGISTER(flash, &flash_cmds, "Flash shell commands",
		       cmd_flash, 2, 0);
