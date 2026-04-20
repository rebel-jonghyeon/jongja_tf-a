/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdio.h>
#include <string.h>

#include <zephyr.h>
#include <device.h>
#include <flash.h>
#include <cri/cmrt/axi_flash.h>

#include "common.h"

/* Sample command to demonstrate Flash API. */

enum {
	FLASH_CMD_READ = 1,
	FLASH_CMD_WRITE = 2,
};

struct flash_command {
	u32_t cmd; /* FLASH_CMD_READ or FLASH_CMD_WRITE */
	u32_t offs;
	u32_t len;
	u8_t data[0];
};

static int flash_run(void *input, u32_t in_used,
		     void *output, u32_t *out_used, u32_t out_size)
{
	struct flash_command *fc = (struct flash_command *)input;
	info("Flash command: cmd = %d, offs = %u, len = %u\n",
	     fc->cmd, fc->offs, fc->len);

	if (in_used > out_size) {
		err("Output buffer is too small %u vs %u\n",
		    in_used, *out_used);
		return -ENOSPC;
	}
	if (fc->cmd != FLASH_CMD_READ && fc->cmd != FLASH_CMD_WRITE) {
		err("Unknown command\n");
		return -ENOTSUP;
	}
	if (fc->len > 0x1000) {
		err("Unsupported length\n");
		return -ENOTSUP;
	}

	struct device *dev = device_get_binding(DT_FLASH_DEV_NAME);

	if (!dev || flash_open(dev)) {
		err("Device I/O error\n");
		return -EIO;
	}

	int ret = 0;
	struct flash_command *fout = output;

	*fout = *fc;

	if (fc->cmd == FLASH_CMD_WRITE) {
		ret = flash_write_protection_set(dev, false);
		if (ret != 0) {
			err("Set Write Enable failure\n");
			return -EIO;
		}
		/* page size is 0x1000 */
		ret = flash_erase(dev, fc->offs, 0x1000);
		if (ret != 0) {
			err("Erase failure\n");
			return -EIO;
		}
		ret = flash_write(dev, fc->offs, &fc->data[0], fc->len);
		if (ret != 0) {
			err("Write failure\n");
			return -EIO;
		}
		ret = flash_write_protection_set(dev, true);
		if (ret != 0) {
			err("Set Write Disable failure\n");
			return -EIO;
		}
		*out_used = sizeof(struct flash_command);
	} else {
		ret = flash_read(dev, fc->offs, &fout->data[0], fc->len);
		if (ret != 0) {
			err("Read failure\n");
			return -EIO;
		}
		*out_used = sizeof(struct flash_command) + fc->len;
	}

	flash_close(dev);

	return 0;
}

const cmd_t cmd_flash = { CMDID_FLASH, "Flash",
			  "Sample Flash API", flash_run };
