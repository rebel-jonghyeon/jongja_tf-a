/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef TEEFS_CMVP_H
#define TEEFS_CMVP_H

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stddef.h>
#include <ctype.h>

#include <hexutil.h>
#include <teefs.h>

#include <cri/cmrt/fips/fips_types.h>

#include <cri/cmrt/teedev_dmac.h>
#include <cri/cmrt/teedev_otp.h>
#include <cri/cmrt/teedev_ram.h>

#include <drivers/cmrt/omc.h>

#define MAX_TEEFS_BUFFER_LEN 4096
extern uint32_t g_inout_buffer_len;
extern uint8_t g_inout_buffer[MAX_TEEFS_BUFFER_LEN];

typedef enum {
	READ_FILE_RAM = 1,
	WRITE_FILE_RAM,
	READ_FILE_OTP,
	WRITE_FILE_OTP,
	DELETE_RAM,
	DELETE_OTP,
} teefs_command_t;

/*
 * FIPS OTP layout
 *
 *  +------------+  0x0030_0000
 *  | enforced   |
 *  |  region    |
 *  +------------+  0x0030_0218 - eSW region start v3
 *  |  reserved  |  3w
 *  |    words   |
 *  +------------+  0x0030_0224
 *  |   sboot    |
 *  +------------+  0x0030_0224 + header + sboot size
 *  |   empty    |
 *  +------------+  0x0030_0BF8
 *  | TMC params |  2w
 *  +------------+  0x0030_0C00
 *  |  OTP teefs |  1kB
 *  +------------+  0x0030_1000 - end of 4k otp
 *
 *  Note when OTP is bigger TMC config and OTP teefs are in the end
 *  of OTP and available space is used for sboot.
 */

#define FIPS_OTP_TEEFS_OFFSET (CMRT_OTP_SIZE - CONFIG_FIPS_OTP_TEEFS_SIZE)
#define FIPS_OTP_TMC_PARAM_OFFSET (FIPS_OTP_TEEFS_OFFSET - CONFIG_FIPS_OTP_TMC_PARAM_SIZE)

int process_teefs_request(teefs_command_t cmd, uint32_t namelen, uint8_t *namebuffer, uint8_t *inout_buffer, uint32_t *inout_buffer_len);
int setup_teefs_RAM(void);
int dismantle_teefs_RAM(void);
#if CONFIG_FIPS_OTP_TEEFS_SIZE > 0
int setup_teefs_OTP(void);
int dismantle_teefs_OTP(void);
#endif
int fips_list_assets_loc(uint8_t *buffer, uint32_t maxbufferlen, uint32_t *found, fips_asset_location loc);

#endif
