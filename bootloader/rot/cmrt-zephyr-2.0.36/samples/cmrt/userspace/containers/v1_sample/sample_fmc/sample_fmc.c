/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to demonstrate use of Feature Management Core (FMC).
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <cri/cmrt.h>
#include "crilog-user.h"
#include "crisyscall-user.h"
#include <cri/cmrt/sic.h>

#include <cri/cmrt/fmc.h>

#define FMC_USER_LED 0x4
#define FMC_USER_GPIO FMC_GPIO_MIN << FMC_FEATURE_REGION_BITS

static int feature_set(uint32_t addr, uint32_t data, uint32_t mask)
{
	cri_fmc_t fmc = cri_fmc_open();
	if (!cri_is_valid(fmc)) {
		c_log("Can't open FMC\n");
		return ENOENT;
	}
	int rc = cri_fmc_feature_write(fmc, addr, data, mask);
	if (rc)
		c_log("I/O error: %d\n", rc);
	cri_fmc_close(fmc);
	return rc;
}

static int feature_get(uint32_t addr, uint32_t *data)
{
	cri_fmc_t fmc = cri_fmc_open();
	if (!cri_is_valid(fmc)) {
		c_log("Can't open FMC\n");
		return ENOENT;
	}
	int rc = cri_fmc_feature_read(fmc, addr, data);
	if (rc)
		c_log("I/O error: %d\n", rc);
	cri_fmc_close(fmc);
	return rc;
}

static int gpio_write(uint32_t addr, uint32_t data, uint32_t mask)
{
	cri_fmc_t fmc = cri_fmc_open();
	if (!cri_is_valid(fmc)) {
		c_log("Can't open FMC\n");
		return ENOENT;
	}
	int rc = cri_fmc_gpio_write(fmc, addr, data, mask);
	if (rc)
		c_log("I/O error: %d\n", rc);
	cri_fmc_close(fmc);
	return rc;
}

static int gpio_read(uint32_t addr, uint32_t *data)
{
	cri_fmc_t fmc = cri_fmc_open();
	if (!cri_is_valid(fmc)) {
		c_log("Can't open FMC\n");
		return ENOENT;
	}
	int rc = cri_fmc_gpio_read(fmc, addr, data);
	if (rc)
		c_log("I/O error: %d\n", rc);
	cri_fmc_close(fmc);
	return rc;
}

#define BUFSIZE 256

static int process_data(uint8_t *input_data, size_t input_size)
{
	(void)input_size;
	int res;
	uint8_t *msg, cmd, arg;
	uint32_t state;

	msg = input_data;
	cmd = *msg++;
	switch (cmd) {
	case '1':
		/*
		 * Set feature bits
		 */
		arg = *msg++;
		if (arg >= 'a')
			state = arg - 'a' + 0xa;

		else
			state = arg - '0';

		res = feature_set(FMC_USER_LED, state, 0xf);
		break;
	case '2':
		res = feature_get(FMC_USER_LED, &state);
		break;
	case '3':
		arg = *msg++;
		if (arg >= 'a')
			state = arg - 'a' + 0xa;

		else
			state = arg - '0';

		res = gpio_write(FMC_USER_GPIO, state, 0xf);
		break;
	case '4':
		res = gpio_read(FMC_USER_GPIO, &state);
		c_log("state %d %u", state, state);
		break;
	case '5':
		res = feature_set(0x10, 0x12345678, 0xffffffff);
		break;
	default:
		c_error("invalid command %x\n", cmd);
		res = EINVAL;
		break;
	}

	if (res) {
		c_error("fmc get/set operation failed: %d\n", res);
		return snprintf((char *)input_data, BUFSIZE, "failed: res %d\n", res);
	}

	else {

		char arr_state[20];

		snprintf(arr_state, sizeof(arr_state), "%s %s %s %s",
			state & 8 ? "ON" : "OFF",
			state & 4 ? "ON" : "OFF",
			state & 2 ? "ON" : "OFF",
			state & 1 ? "ON" : "OFF");

		c_log("LED states: %s\n", arr_state);
		return snprintf((char *)input_data, BUFSIZE, "OK. %s\n", arr_state);
	}
}

int main(void)
{
	c_log("Sample (fmc) container starting...\n");

	const cri_sic_t sic = cri_sic_open(0, CRI_UNIT_CONTAINER_SAMPLE);
	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}

	char buf[BUFSIZE];
	uint32_t peer;
	size_t msglen = sizeof(buf);
	int ret = cri_sic_read(sic, buf, &msglen, &peer);
	if (ret) {
		c_log("cri_sic_read() returned %d\n", ret);
		goto out;
	}
	while (true) {
		const int fout = cri_wait(1, &sic, CRI_SECONDS(30));
		if ((fout > 0) && (fout & 1)) {
			ret = cri_sic_sync(sic);
			if (ret) {
				c_log("cri_sic_sync() returned %d\n", ret);
				break;
			}
			c_log("Received sic message from 0x%x\n", peer);
			msglen = process_data((uint8_t *)buf, msglen);

			c_log("Sending sic message to 0x%x\n", peer);
			ret = cri_sic_write(sic, buf, msglen, peer);
			if (ret) {
				c_log("cri_sic_write() returned %d\n", ret);
				break;
			}
			msglen = sizeof(buf);
			ret = cri_sic_read(sic, buf, &msglen, &peer);
			if (ret) {
				c_log("cri_sic_read() returned %d\n", ret);
				break;
			}
		}
		else if (fout < 0) {
			c_log("cri_wait() returned %d\n", fout);
			break;
		}
		else {
			c_log("No sic messages in 30 seconds...\n");
		}
	}
out:
	cri_sic_close(sic);
	c_log("Sample container exiting.\n");
	return 1;
}
