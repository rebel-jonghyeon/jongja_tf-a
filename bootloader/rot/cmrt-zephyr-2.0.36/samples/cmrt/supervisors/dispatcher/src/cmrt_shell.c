/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdlib.h>
#include <stddef.h>
#include <zephyr.h>
#include <shell/shell.h>
#include <misc/util.h>
#include <sys/types.h>
#include <errno.h>
#include <device.h>
#include <flash.h>
#include <smcalls.h>
#include <cri/cmrt.h>
#include <cri/cmrt/omc.h>
#include <cri/cmrt/dmac.h>
#include <cri/cmrt/axi_flash.h>
#include <cri/cmrt/axi_flash_layout.h>
#include <cri/cmrt/img_format.h>
#include <cri/cmrt/img_version.h>
#include <cri/cmrt/scratchpad.h>

/* Define 1020k as image maxsize. */
#define IMG_MAXSIZE (AXI_FLASH_SPV_SZ - AXI_FLASH_ERASE_SZ)

static int flash_burn(struct device *dev, off_t offset, const void *data, size_t len)
{
	int res = flash_write_protection_set(dev, false);
	if (res != 0) {
		return res;
	}
	res = flash_erase(dev, offset, ROUND_UP(len, AXI_FLASH_ERASE_SZ));
	if (res != 0) {
		return res;
	}
	res = flash_write(dev, offset, data, len);
	if (res != 0) {
		return res;
	}
	return flash_write_protection_set(dev, true);
}

static int image_cmd(const struct shell *shell, struct device *dev, off_t offset, bool is_burn)
{
	/* Read image header from scratchpad or Flash. */
	size_t size, left;
	cri_img_header_t *hdr;
	if (is_burn) {
		hdr = cri_scratchpad_data(&size, &left);
		if (size < sizeof(*hdr)) {
			shell_error(shell, "No header in scratchpad!");
			return -ENOEXEC;
		}
	} else { /* copy */
		(void)cri_scratchpad_truncate(0);
		hdr = cri_scratchpad_data(&size, &left);
		int res = flash_read(dev, offset, hdr, sizeof(*hdr));
		if (res != 0) {
			shell_error(shell, "Failed to read header: %d", res);
			return -ENOEXEC;
		}
	}
	if ((hdr->length == 0) || (hdr->length > IMG_MAXSIZE)) {
		shell_error(shell, "Image header missing!\n");
		return -ENOSPC;
	}
	size_t length = sizeof(*hdr) + hdr->length;
	if (is_burn) {
		if (length != size) {
			shell_error(shell, "Image size mismatch, "
				    "header %u, scratchpad %u", length, size);
			return -EFAULT;
		}
		int res = flash_burn(dev, offset, hdr, length);
		if (res != 0) {
			shell_error(shell, "Failed to burn flash: %d", res);
			return res;
		}
		shell_print(shell, "Burned %d bytes to Flash", length);
	} else { /* copy */
		if (length > left) {
			shell_error(shell, "Image size too big, "
				    "header %u, scratchpad %u", length, left);
			return -EFAULT;
		}
		int res = flash_read(dev, offset, hdr, length);
		if (res != 0) {
			shell_error(shell, "Failed to read flash: %d", res);
			return res;
		}
		(void)cri_scratchpad_seek(length, SCRATCHPAD_SEEK_SET);
		shell_print(shell, "Copied %d bytes to scratchpad", length);
	}
	return 0;
}

static int cmrt_image_cmd(const struct shell *shell, size_t argc, char **argv)
{
	if (argc > 2) {
		shell_error(shell, "Too many parameters.");
		return -EINVAL;
	}
	if (argc < 2) {
		shell_error(shell, "A|B location missing");
		return -EINVAL;
	}
	/* Get the A|B location. */
	off_t offset = -1;
	if ((*argv[1] == 'A') || (*argv[1] == 'a')) {
		offset = AXI_FLASH_SPV_A;
#ifdef CONFIG_CRI_AB_LOCATION_SUPPORT
	} else if ((*argv[1] == 'B') || (*argv[1] == 'b')) {
		offset = AXI_FLASH_SPV_B;
#endif
	}
	if (offset == -1) {
		shell_error(shell, "Location %s not supported", argv[1]);
		return -EINVAL;
	}
#ifdef CONFIG_CRI_AB_IMAGE_SUPPORT
	/* Location has the Flash header in first block. */
	offset += AXI_FLASH_ERASE_SZ;
#endif
	struct device *dev = device_get_binding(DT_FLASH_DEV_NAME);
	if ((dev == NULL) || flash_open(dev)) {
		shell_error(shell, "Failed to open flash");
		return -ENODEV;
	}
	/* Copy image data to/from Flash. */
	bool is_burn = !strcmp(argv[0], "burn");

	int res = cri_scratchpad_lock(1000);
	if (res < 0) {
		shell_warn(shell, "cri_scratchpad_lock error %d", res);
		return -ENOEXEC;
	}
	res = image_cmd(shell, dev, offset, is_burn);
	cri_scratchpad_unlock();
	flash_close(dev);

	return res;
}

static int cmrt_version_cmd(const struct shell *shell, size_t argc, char **argv)
{
	if (argc > 2) {
		shell_error(shell, "Too many parameters.");
		return -EINVAL;
	}
	if (argc == 2) {
		if (strcmp(argv[1], "update")) {
			shell_error(shell, "Only 'update' allowed.");
			return -EINVAL;
		}
	}
	u32_t version = 0;
	size_t size = sizeof(u32_t);
	int res = cri_mcall_get_img_version(CMRT_SUPERVISOR_IMG_OTP, &version, &size);
	if (res != 0) {
		shell_error(shell, "Failed to read image version: %d.", res);
		return res;
	}
	if (argc == 2) {
		/* Update version thermometer by setting the next bit. */
		unsigned int bit = find_msb_set(version);
		version |= (1U << bit);
		res = cri_mcall_set_img_version(CMRT_SUPERVISOR_IMG_OTP, &version, size);
		if (res != 0) {
			shell_error(shell, "Failed to update image version: %d.", res);
			return res;
		}
	}
	shell_print(shell, "Minimum accepted image version is 0x%08x", version);
	return 0;
}

static int cmrt_offset_cmd(const struct shell *shell, size_t argc, char **argv)
{
	if (argc > 1) {
		shell_error(shell, "Too many parameters.");
		return -EINVAL;
	}
	u32_t location;
	int res = cri_mcall_img_location(&location, 0);
	if (res != 0) {
		shell_error(shell, "Failed to read image offset: %d.", res);
		return res;
	}
	shell_print(shell, "The next image offset in Flash is 0x%08x", location);
	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(cmrt_image_cmds,
	SHELL_CMD(copy, NULL, "'cmrt image copy <A|B>' from Flash to scratchpad", cmrt_image_cmd),
	SHELL_CMD(burn, NULL, "'cmrt image burn <A|B>' from scratchpad to Flash", cmrt_image_cmd),
	SHELL_CMD(version, NULL, "'cmrt image version <update>' Read or update image version in OTP", cmrt_version_cmd),
	SHELL_CMD(offset, NULL, "'cmrt image offset' Get offset in Flash after bootup", cmrt_offset_cmd),
	SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(cmrt_cmds,
	SHELL_CMD(image, &cmrt_image_cmds, "move CMRT images between scratchpad and Flash", NULL),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(cmrt, &cmrt_cmds, "CMRT system commands", NULL);
