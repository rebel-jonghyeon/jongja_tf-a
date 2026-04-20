/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdalign.h>

#include <smcalls.h>
#include <teedev_dmac.h>
#include <teefs.h>

#include <cri/cmrt/dd.h>
#include <cri/cmrt/aes.h>
#include <cri/cmrt/hc.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/kdc.h>
#include <cri/cmrt/ktc.h>
#include <cri/cmrt/pke.h>
#include <cri/cmrt.h>

#include <tee_client_api.h> /* TEEC_MEMREF values */
#include <tee_client_abi.h>

#include <cri/cmrt/fips/fips_types.h>

#include "fips.h"
#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "cmvp_sw.h"
#include "cri_crypto.h"

extern const char version_info[];

static alignas(4) u8_t buffer[1024];
alignas(4) uint8_t workcontext[MAX_WORKCONTEXT_LEN];
cri_sic_t sic;

static void set_boot_status(u32_t bits, u32_t mask)
{
	u32_t value = cri_read_reg(CMRT_SIC_BASE, R_SW_BOOT_STATUS);
	value &= ~mask;
	value |= bits & mask;
	cri_write_reg(CMRT_SIC_BASE, R_SW_BOOT_STATUS, value);
}

static u32_t get_fips_need(void)
{
	u32_t value = cri_read_reg(CMRT_SIC_BASE, R_FIPS_MODE);
	dprintk("FIPS mode: %i\n", value);
	return value & FIPS_MODE_ENTER_FLAG;
}

static void set_fips_mode(void)
{
	u32_t value = cri_read_reg(CMRT_SIC_BASE, R_FIPS_MODE);
	value |= FIPS_MODE_RUNNING_FLAG;
	cri_write_reg(CMRT_SIC_BASE, R_FIPS_MODE, value);
}

int main(void)
{
	int res;
	fips_state_t state;
	io_t io;
	teec_abi_header_t *h = (teec_abi_header_t *) buffer;

	dprintk("Supervisor CMVP %s running...\n", version_info);

	/* OTP TMC configuration has to be applied before first use of TMC,
	   in mission+fips it is rsa_run_kat() */
	res = init_tmc_with_otp_config();
	if (res < 0) {
		dprintk("Failed to init TMC: %d!\n", res);
		return res;
	}

	if (get_fips_need()) {
		if (run_all_kats()) {
			set_fips_mode();
		}
	}

	io.data = buffer;
	fips_intialize_state(&state);

	/* Running in supervisor mode here. */
	sic = cri_sic_open(CRI_O_SYNC, FIPS_LOCAL_ADDRESS);
	if (!cri_is_valid(sic)) {
		dprintk("Cannot open SIC\n");
		return -ENODEV;
	}
	set_boot_status(SUPERVISOR_RUNNING_ID, SUPERVISOR_RUNNING_ID);
	memset(workcontext, 0x00, MAX_WORKCONTEXT_LEN);

	res = setup_teefs_RAM();
	if (res < 0) {
		dprintk("Failed to setup teefs (RAM): %d!\n", res);
		return res;
	}
#if CONFIG_FIPS_OTP_TEEFS_SIZE > 0
	res = setup_teefs_OTP();
	if (res < 0) {
		dprintk("Failed to setup teefs (OTP): %d!\n", res);
		return res;
	}
#endif
#ifdef CONFIG_DEBUG
	workcontext[MAX_WORKCONTEXT_LEN - 2] = 0xA5;
	workcontext[MAX_WORKCONTEXT_LEN - 1] = 0x5A;
#endif

	while (1) {
		dprintk("Waiting for SIC command ...\n");
		io.size = sizeof(buffer);
		u32_t peerid;
		res = cri_sic_read(sic, io.data, &io.size, &peerid);
		if (res < 0) {
			dprintk("failed to read from HLOS: %d!\n", res);
			continue;
		}

		res = process_tee_message(&state, &io);
		if (res < 0) {
			dprintk("Request failed: %d!\n", res);
		}

#ifdef CONFIG_DEBUG
		if ((workcontext[MAX_WORKCONTEXT_LEN - 1] != 0x5A) ||
			(workcontext[MAX_WORKCONTEXT_LEN - 2] != 0xA5)) {
			dprintk("Work context overflow\n");
			if (!res) {
				res = -EIO;
			}
		}
		if (((uint32_t *)workcontext)[0] == 0) {
			uint32_t addr = 0;
			uint8_t sum = 0;
			for (int i = 1; i < (MAX_WORKCONTEXT_LEN - 2); i++) {
				sum |= workcontext[i];
				if (workcontext[i] != 0) {
					if (i > addr) { addr = i; }
				}
			}
			if (sum != 0) {
				dprintk("Memory not zeroed correctly\n");
				dprintk("Maximum observed index: %i\n", addr);
				dhexdump("Memory", workcontext, addr);
				if (!res) {
					res = -EIO;
				}
			}
		}
#endif

		dprintk("Sending output back\n");
		h->session = state.teec_session;
		if (res < 0) {
			res = -res;
		}
		h->cmdres = res | (state.approved_mode << 31);
		state.approved_mode = 0;
		res = cri_sic_write(sic, io.data, io.size, peerid);
		if (res < 0) {
			dprintk("failed to write to HLOS: %d!\n", res);
			continue;
		}

		if (state.do_reset == true) {
			state.do_reset = false;
			cri_mcall_soft_reset();
		}
	}

	return 0;
}
