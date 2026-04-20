/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to advance lifecycle.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <cri/cmrt.h>
#include "crisyscall-user.h"
#include "crilog-user.h"
#include <cri/cmrt/sic.h>
#include <cri/cmrt/omc.h>

enum commands {
	CMD_SET_LC_PROVISIONED    = 1,
	CMD_SET_LC_MISSION        = 2,
	CMD_SET_LC_FRA            = 3,
	CMD_SET_LC_DECOMMISSIONED = 4,
};

#define BUFSIZE 256
typedef struct {
	uint32_t peer;
	size_t bufsize;
	char buf[BUFSIZE];
} conn_t;

static int set_lifecycle(uint32_t lc)
{
	int res = -1;
	cri_otp_t omc = cri_otp_open(CRI_O_SYNC);
	if (cri_is_valid(omc)) {
		res = cri_otp_set_lifecycle(omc, lc);
		if (res) {
			c_error("LC set failed %d\n", res);
		} else {
			c_log("LC 0x%x written to OTP\n", lc);
		}
		cri_otp_close(omc);
	}
	return res;
}

static int runcmd(const char *buffer, size_t size)
{
	int res = -EINVAL;
	if (size < 4) {
		return res;
	}

	uint32_t cmd = *(uint32_t *)buffer;

	c_log("cmd 0x%x\n", cmd);

	switch (cmd) {
	case CMD_SET_LC_PROVISIONED:
		res = set_lifecycle(0x00010D01);
		break;
	case CMD_SET_LC_MISSION:
		res = set_lifecycle(0x20010D03);
		break;
	case CMD_SET_LC_FRA:
		res = set_lifecycle(0x70010DA3);
		break;
	case CMD_SET_LC_DECOMMISSIONED:
		res = set_lifecycle(0x7C034DA3);
		break;
	default:
		c_error("Unknown command 0x%x\n", cmd);
		break;
	}

	return res;
}

static void write_sic_reply(cri_sic_t sic, int errcode, conn_t *conn)
{
	c_log("Container sending sic reply to %u: %d\n",
	      conn->peer, errcode);

	int res = cri_sic_write(sic, &errcode, sizeof(errcode), conn->peer);
	if (res != 0) {
		c_error("cri_sic_write() failed: peer %u, res %d\n",
			conn->peer, res);
		cri_exit(1);
	}
}

static int recv_sic_data(cri_sic_t sic, conn_t *conn)
{
	/* Free the receive buffer */
	int sic_res = cri_sic_sync(sic);
	if (sic_res) {
		c_log("cri_sic_sync() returned %d\n", sic_res);
		return sic_res;
	}
	c_log("Received sic message from %u, len %d\n", conn->peer,
	      conn->bufsize);

	/* All OK */
	int res = runcmd(conn->buf, conn->bufsize);
	write_sic_reply(sic, res, conn);

	/* Restore the buffer */
	conn->bufsize = sizeof(conn->buf);
	return cri_sic_read(sic, conn->buf, &conn->bufsize, &conn->peer);
}

int main(void)
{
	c_log("Test (lifecycle) container starting...\n");

	const cri_sic_t sic = cri_sic_open(0, CRI_UNIT_CONTAINER_SAMPLE);
	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}

	conn_t conn = { .bufsize = sizeof(conn.buf),
			.peer = 0 };

	/* Mark where to receive the data */
	int res = cri_sic_read(sic, conn.buf, &conn.bufsize, &conn.peer);
	if (res) {
		c_error("SIC read failed: %d\n", res);
		return 1;
	}

	do {
		const int fout = cri_wait(1, &sic, CRI_SECONDS(30));

		if ((fout > 0) && (fout & 1)) {
			recv_sic_data(sic, &conn);
		} else if (res == 0) {
			c_log("cri_wait() timeout\n");
		} else {
			c_log("cri_wait() error\n");
			return -1;
		}
	} while (1);
}
