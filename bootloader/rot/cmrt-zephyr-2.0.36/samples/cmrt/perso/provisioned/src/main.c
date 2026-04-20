/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <string.h>
#include <stdalign.h>
#include <sys/types.h>
#include <sys/util.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/util.h>
#include <drivers/cmrt/fboot.h>
#include <cmrt/fboot/fboot_config.h>

#ifdef CONFIG_SOC_FLASH_M25P80
#include <drivers/cmrt/axi_flash.h>
#define ERASE_BLOCK_SIZE AXI_FLASH_ERASE_SZ
#else
#include <drivers/cmrt/dmac.h>
#define ERASE_BLOCK_SIZE 0x1000
#endif

#include "os_img.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define PERSO_STATUS_STARTED  0x930300ff
#define PERSO_STATUS_DONE     0x93030000
#define PERSO_STATUS_ERROR    0x93030100

const static char version_info[] __version = PERSO_VERSION_INFO;

#ifdef CONFIG_SOC_FLASH_M25P80
static int burn_to_flash(off_t offset, const void *data, size_t len)
{
	struct device *dev = device_get_binding(DT_FLASH_DEV_NAME);

	LOG_INF("Burn OS at flash offset 0x%x with %u bytes", offset, len);
	if (!dev || flash_open(dev)) {
		LOG_INF("Cannot open flash: %s", DT_FLASH_DEV_NAME);
		return -EIO;
	}
	int ret = flash_write_protection_set(dev, false);
	if (ret != 0) {
		LOG_INF("Cannot set write enable: %d", ret);
		goto out;
	}
	ret = flash_erase(dev, offset, ROUND_UP(len, ERASE_BLOCK_SIZE));
	if (ret != 0) {
		LOG_INF("Cannot erase: %d", ret);
		goto out;
	}
	ret = flash_write(dev, offset, data, len);
	if (ret != 0) {
		LOG_INF("Cannot burn: %d", ret);
		goto out;
	}
	ret = flash_write_protection_set(dev, true);
	if (ret != 0) {
		LOG_INF("Cannot set write disable: %d", ret);
		goto out;
	}
	/* some sanity check */
	u32_t buf = 0;

	ret = flash_read(dev, offset, &buf, sizeof(buf));
	if (ret != 0) {
		LOG_INF("Cannot read: %d", ret);
		goto out;
	}
	if (memcmp(&buf, data, 4) != 0) {
		LOG_INF("Head broken: %08x", buf);
		goto out;
	}
	LOG_INF("head is %08x", buf);
	ret = flash_read(dev, offset + len - 4, &buf, sizeof(buf));
	if (ret != 0) {
		LOG_INF("Cannot read: %d", ret);
		goto out;
	}
	if (memcmp(&buf, data + len - 4, 4) != 0) {
		LOG_INF("Tail broken: %08x", buf);
		goto out;
	}
	LOG_INF("tail is %08x", buf);
out:
	flash_close(dev);
	return ret;
}
#else
static int burn_to_flash(off_t offset, const void *data, size_t len)
{
	cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(dmac)) return -ENODEV;

	LOG_INF("Burn OS at 0x%x with %d bytes", offset, len);
	int res = cmrt_dmac_data(dmac, (uint32_t)data, (uint32_t)offset, len, 0);
	cmrt_dmac_close(dmac);

	return res;
}
#endif

int main(void)
{
	cmrt_set_boot_status(CONTAINER_RUNNING_ID, CONTAINER_RUNNING_ID);
	uint32_t lifecycle = cmrt_read_reg(CMRT_SIC_BASE, R_SCRATCH_0);
	if (lifecycle == 0 || lifecycle == 0xffffffff) {
	    lifecycle = DLC_MISSION;
	}
	cmrt_set_perso_status(PERSO_STATUS_STARTED);
	LOG_INF("Provisioned perso %s starting up", version_info);

	int res;
	/* Primary location will have flash header + primary image. */
	uint32_t location = OS_LOCATION_A;
#ifdef CONFIG_CMRT_AB_IMAGE_SUPPORT
	/* Define a 'standard' flash header where primary image starts
	 * at next erase block, without secondary image.
	 * .primary and .secondary values are "offsets" relative to the
	 * locations of the respective flash headers. */
	cmrt_flash_header_t fhdr = {
		.magic = CMRT_FHDR_MAGIC,
		.flags = 0,
		.primary = ERASE_BLOCK_SIZE,
		.secondary = 0,
	};
	/* Burn primary location flash header. */
	res = burn_to_flash(location, &fhdr, sizeof(fhdr));
	if (res) goto out;
	location += ERASE_BLOCK_SIZE;
#endif
	/* Burn the image to the primary location. */
	res = burn_to_flash(location, os_img, os_img_len);
	if (res) goto out;

#ifdef CONFIG_CMRT_AB_LOCATION_SUPPORT
	/* Secondary location will have flash header + secondary image. */
	location = OS_LOCATION_B;
	/* If A doesn't fit we need to sacrifice B location,
	 * if that is the case, OS_LOCATION_B will contain
	 * part of the A image, so do not touch it
	 */
	if (OS_LOCATION_B >= (OS_LOCATION_A + os_img_len)) {
#ifdef CONFIG_CMRT_AB_IMAGE_SUPPORT
		/* Burn secondary location flash header. */
		res = burn_to_flash(location, &fhdr, sizeof(fhdr));
		if (res) goto out;
		location += ERASE_BLOCK_SIZE;
#endif
		/* Burn the actual image to the secondary location */
		res = burn_to_flash(location, os_img, os_img_len);
		if (res) goto out;
	}
#endif
	res = cmrt_set_lifecycle(lifecycle);
	if (res) goto out;

	LOG_INF("All done for provisioned perso");

out:
	cmrt_set_boot_status(0, CONTAINER_RUNNING_ID);
	cmrt_set_perso_status((res < 0) ? PERSO_STATUS_ERROR : PERSO_STATUS_DONE);

	return fboot_halt(-EFAULT, res);
}
