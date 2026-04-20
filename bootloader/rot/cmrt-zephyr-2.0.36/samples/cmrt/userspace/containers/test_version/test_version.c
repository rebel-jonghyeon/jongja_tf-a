/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief User container that provides binary version identifiers.
 */

#include <errno.h>
#include <container.h>
#include <logging/log.h>

#include <drivers/cmrt/fboot.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>


#define CMRT_FBOOT_IMAGE_VERSION 0x10001
#define CMRT_SBOOT_IMAGE_VERSION 0x10002
#define CMRT_TBOOT_IMAGE_VERSION 0x10003
#define CMRT_SUPERVISOR_IMAGE_VERSION 0x10004


static int process_data(char *buffer, size_t maxlen)
{
	char cmd = buffer[0];
	size_t size = maxlen;
	int res;
	switch (cmd) {
	case 'f':
		res = fboot_get_image_version(CMRT_FBOOT_IMAGE_VERSION,
					      buffer, &size);
		if (res)
			LOG_ERR("Get fboot version failed: %d", res);
		else
			LOG_INF("Fboot version: %.*s", size, buffer);
		break;
	case 's':
		res = fboot_get_image_version(CMRT_SBOOT_IMAGE_VERSION,
					      buffer, &size);
		if (res)
			LOG_ERR("Get sboot version failed: %d", res);
		else
			LOG_INF("Sboot version: %.*s", size, buffer);
		break;
	case 'm':
		res = fboot_get_image_version(CMRT_SUPERVISOR_IMAGE_VERSION,
					      buffer, &size);
		if (res)
			LOG_ERR("Get supervisor version failed: %d", res);
		else
			LOG_INF("Supervisor version: %.*s", size, buffer);
		break;
	case 't':
		res = fboot_get_image_version(CMRT_TBOOT_IMAGE_VERSION,
					      buffer, &size);
		if (res)
			LOG_ERR("Get tboot version failed: %d", res);
		else
			LOG_INF("Tboot version: %.*s", size, buffer);
		break;
	default:
		LOG_ERR("Invalid command '%c'", cmd);
		res = -EINVAL;
		break;
	}
	if (res) {
		return snprintf(buffer, maxlen, "Failed: res %d", res);
	} else {
		return size;
	}
}

static int main_loop(uint32_t flowid)
{
	LOG_INF("test_version user container starting...");

	cmrt_sic_t sic = cmrt_sic_open(CMRT_O_SYNC, flowid);
	if (!cmrt_is_valid(sic)) {
		LOG_INF("Cannot open SIC");
		return -ENODEV;
	}
	LOG_INF("Waiting for SIC input on flow 0x%x...", (unsigned int)flowid);

	int res;
	while (true) {
		char buffer[256];
		size_t buflen = sizeof(buffer);
		uint32_t peerid = 0;
		res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_INF("Failed to read from HLOS: %d!", res);
			break;
		}
		LOG_INF("Received sic message from 0x%x", (int)peerid);
		int reslen = process_data(buffer, sizeof(buffer));
		LOG_INF("Sending sic message to 0x%x", (int)peerid);
		res = cmrt_sic_write(sic, buffer, reslen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			break;
		}
	}
	cmrt_sic_close(sic);
	return res;
}

void container(void *p1, void *p2, void *p3)
{
	(void)p2;
	(void)p3;
	int res = main_loop((uint32_t)p1);
	LOG_ERR("Container main_loop exited with %d!", res);
}
