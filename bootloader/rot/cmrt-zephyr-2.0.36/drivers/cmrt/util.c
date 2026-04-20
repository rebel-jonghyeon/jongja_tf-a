/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <kernel.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/cc.h>
#include <drivers/cmrt/plic_reg.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/fmc.h>
#include <drivers/cmrt/kdc.h>
#include <drivers/cmrt/emc.h>
#include <drivers/cmrt/timer_reg.h>
#include <drivers/cmrt/util.h>
#include <cmrt/fboot/img_format.h>
#include <cmrt/fboot/fboot_config.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

void cmrt_clear_container_context(void)
{
	LOG_INF("Clearing HW permissions");
	uint32_t machine_ie = cmrt_read_reg(CMRT_PLIC_BASE, R_PLIC_MACHINE_IE);
	uint32_t supervisor_ie = cmrt_read_reg(CMRT_PLIC_BASE, R_PLIC_SUPERVISOR_IE);
	uint32_t timer_ie = cmrt_read_reg(CMRT_PLIC_BASE, R_PLIC_TIMER_IE);
	uint32_t sic_irq_mask = cmrt_read_reg(CMRT_SIC_BASE, R_CORE_INTERRUPT_MASK);
	uint32_t kernel_version = cmrt_read_reg(CMRT_SIC_BASE, R_KERNEL_VERSION);
	uint32_t sdk_version = cmrt_read_reg(CMRT_SIC_BASE, R_SDK_VERSION);
	uint32_t scratch_0 = cmrt_read_reg(CMRT_SIC_BASE, R_SCRATCH_0);

	uint32_t custom_reg[CMRT_SIC_NUM_CUSTOM];
	for (size_t i = 0; i < CMRT_SIC_NUM_CUSTOM; i++) {
		custom_reg[i] = cmrt_read_reg(CMRT_SIC_BASE, R_CUSTOM_0 + i * 4);
	}

	cmrt_write_reg(CMRT_SIC_BASE, R_HWC_CCC, HWC_CCC_DO);
	while (cmrt_read_reg(CMRT_SIC_BASE, R_HWC_CCC_DONE) != HWC_CCC_DO) {
		arch_nop();
	}
	cmrt_write_reg(CMRT_SIC_BASE, R_HWC_CCC, 0);
	cmrt_write_reg(CMRT_SIC_BASE, R_HWC_CCC_DONE, HWC_CCC_DO);

	cmrt_write_reg(CMRT_SIC_BASE, R_CORE_INTERRUPT_MASK, sic_irq_mask);
	cmrt_write_reg(CMRT_SIC_BASE, R_KERNEL_VERSION, kernel_version);
	cmrt_write_reg(CMRT_SIC_BASE, R_SDK_VERSION, sdk_version);
	cmrt_write_reg(CMRT_SIC_BASE, R_SCRATCH_0, scratch_0);

	for (size_t i = 0; i < CMRT_SIC_NUM_CUSTOM; i++) {
		cmrt_write_reg(CMRT_SIC_BASE, R_CUSTOM_0 + i * 4, custom_reg[i]);
	}

	cmrt_write_reg(CMRT_PLIC_BASE, R_PLIC_MACHINE_IE, machine_ie);
	cmrt_write_reg(CMRT_PLIC_BASE, R_PLIC_SUPERVISOR_IE, supervisor_ie);
	cmrt_write_reg(CMRT_PLIC_BASE, R_PLIC_TIMER_IE, timer_ie);
}

#if defined(CONFIG_CMRT_CC)
#define CASSERT1_INIT (0x4466ca57UL)
#define CASSERT2_INIT (0x20d8c722UL)

int cmrt_assert_canary(void)
{
	cmrt_cc_t cc = cmrt_cc_open();
	if (!cmrt_is_valid(cc)) {
		return -ENODEV;
	}
	(void)cmrt_cc_assert(cc, CASSERT1_INIT, CASSERT2_INIT);
	(void)cmrt_cc_mix(cc, 0xABCDEF12);
	int res = cmrt_cc_sync(cc);
	cmrt_cc_close(cc);
	return res;
}
#endif

int cmrt_debug_mode(uint32_t scratch)
{
	cmrt_fmc_t fmc = cmrt_fmc_open();
	if (!cmrt_is_valid(fmc)) {
		return -ENODEV;
	}
	int res = cmrt_fmc_set_debug_mode(fmc);
	cmrt_fmc_close(fmc);
	if (res) { return res; }

	if (scratch != 0) {
		while (cmrt_read_reg(CMRT_SIC_BASE, R_SCRATCH_0) != scratch) {
			k_busy_wait(0x1000);
		}
	}
	return 0;
}

static int generate_random(cmrt_tmc_t tmc, uint8_t *buf, size_t size)
{
	while (size > 0u) {
		size_t len = (size > TMC_OUTPUT_SIZE) ? TMC_OUTPUT_SIZE : size;
		int res = cmrt_tmc_command(tmc, CMRT_TMC_GENERATE, buf, len);
		if (res != 0) { return res; }
		buf += len;
		size -= len;
	}
	return 0;
}

int cmrt_get_randomv(const struct iov *v, size_t nv)
{
	cmrt_tmc_t tmc = cmrt_tmc_open(CMRT_O_SYNC, NULL);
	if (!cmrt_is_valid(tmc)) { return -ENODEV; }
	int res = 0;
#if !IS_ENABLED(CMRT_TMC_EIP76_TRNG)
	/* Reseed only for the old CRNG. */
	res = cmrt_tmc_command(tmc, CMRT_TMC_RESEED, NULL, 0);
#endif
	if (res == 0) {
		for (size_t i = 0; i < nv; ++i) {
			res = generate_random(tmc, v[i].p, v[i].n);
			if (res != 0) { break; }
		}
	}
	cmrt_tmc_close(tmc);
	return res;
}

int z_impl_cmrt_get_random(void *buf, size_t len)
{
	struct iov v = { buf, len };
	return cmrt_get_randomv(&v, 1);
}

#ifdef CONFIG_CMRT_EMC
int cmrt_get_entropyv(const struct iov *v, size_t nv)
{
	cmrt_emc_t emc = cmrt_emc_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(emc)) { return -ENODEV; }

	int res = 0;
	for (size_t i = 0; i < nv; i++) {
		res = cmrt_emc_read(emc, v[i].p, v[i].n);
		if (res != 0) { break; }
	}
	cmrt_emc_close(emc);
	return res;
}
#endif

int z_impl_cmrt_get_entropy(void *buf, size_t len)
{
	struct iov v = { buf, len };
#ifdef CONFIG_CMRT_EMC
	/* Use EMC since HW has it. */
	return cmrt_get_entropyv(&v, 1);
#else
	/* No EMC, use TMC then. */
	return cmrt_get_randomv(&v, 1);
#endif
}

int cmrt_set_lifecycle(uint32_t value)
{
	LOG_INF("Setting lifecycle to 0x%08x", value);
	cmrt_omc_t omc = cmrt_omc_open(CMRT_O_OTP_COMMIT);
	if (!cmrt_is_valid(omc)) { return -ENODEV; }
	int res = cmrt_omc_write(omc, OTP_LIFECYCLE_OFFSET, &value, sizeof(value));
	if (res == 0) { res = cmrt_omc_sync(omc); }
	cmrt_omc_close(omc);
	return res;
}

int cmrt_burn_dgok(void)
{
	LOG_INF("Burning DGOK to OTP");
	/* Setup TMC, this works for EIP-76 or for the original. */
	cmrt_tmc_init_params_t params;
	cmrt_init_tmc_config(&params);
	cmrt_tmc_t tmc = cmrt_tmc_open(CMRT_O_TMC_KDC, &params);
	if (!cmrt_is_valid(tmc)) { return -ENODEV; }
	cmrt_kdc_t kdc = cmrt_kdc_open(0);
	if (!cmrt_is_valid(kdc)) {
		cmrt_tmc_close(tmc);
		return -ENODEV;
	}
	cmrt_kdc_cmd_t cmd;
	/* No need to derive or diversify here. Leave them as zeros. */
	memset(&cmd, 0, sizeof(cmd));
	cmd.diversify_len = 16;

	int res = cmrt_kdc_burn_dgok(kdc, &cmd);
	if (res == 0) { res = cmrt_kdc_sync(kdc); }
	cmrt_kdc_close(kdc);
	cmrt_tmc_close(tmc);

	return res;
}

#ifdef CONFIG_CMRT_OMC_EMULATED_OTP_INIT
int cmrt_init_oec_version(void)
{
	cmrt_omc_t omc = cmrt_omc_open(0);
	if (!cmrt_is_valid(omc)) { return -ENODEV; }

	LOG_INF("Reading OEC version");
	uint32_t buffer[OEC_MAX_DATA_WORDS] = {0};
	size_t len = CONFIG_CMRT_OMC_VERSION_EFUSES >> 3;
	int res = cmrt_oec_read(omc, OEC_ADDRESS_VERSION_EFUSE, buffer, len);
	if (res != 0 || (res = cmrt_omc_sync(omc)) != 0) goto out;

	/* Check if version needs to be initialized. */
	int init_oec = 1;
	size_t words = len >> 2;
	for (int i = 0; init_oec && i < words; i++) {
		init_oec = !buffer[i];
	}
	if (!init_oec) goto out; /* Version is already initialized. */

	LOG_INF("Initialize OEC version");
	len = 64 >> 3; /* for AES IV only 64 bits are used */
	cmrt_get_entropy(buffer, len);
	LOG_INF("Writing OEC AES IV...");
	res = cmrt_oec_write(omc, OEC_ADDRESS_AES_IV, buffer, len);
	if (res != 0 || (res = cmrt_omc_sync(omc)) != 0) goto out;

	memset(buffer, 0, sizeof(buffer));
	len = CONFIG_CMRT_OMC_VERSION_EFUSES >> 3;
	words = len >> 2;
	buffer[words-1] = 0x00000001; /* set one bit to have valid version */
	LOG_INF("Writing OEC version efuses...");
	res = cmrt_oec_write(omc, OEC_ADDRESS_VERSION_EFUSE, buffer, len);
	if (res == 0) { res = cmrt_omc_sync(omc); }
out:
	if (res) { LOG_INF("Failed to initialize OEC version %d", res); }
	cmrt_omc_close(omc);
	return res;
}
#endif

uint32_t cmrt_otp_app_start(cmrt_omc_t omc)
{
	uint32_t esw_offset = cmrt_otp_esw_start();
#ifndef CONFIG_CMRT_SBOOT_IN_ROM
	if (!cmrt_is_valid(omc)) {
		return 0;
	}
	cmrt_img_header_t hdr;
	int res = cmrt_omc_read(omc, esw_offset, &hdr, sizeof(hdr));
	if (res == 0 && cmrt_is_valid_hdr(&hdr, SBOOT_MAXSIZE)) {
		esw_offset += sizeof(hdr) + hdr.length;
	} else {
		esw_offset = 0; /* return error */
	}
#endif
	return esw_offset;
}

uint64_t z_impl_cmrt_perf_ref(void)
{
	uint32_t ref_high = cmrt_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_HIGH);
	uint32_t ref_low = cmrt_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_LOW);
	uint32_t ref_high2 = cmrt_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_HIGH);

	if (ref_high != ref_high2 && ref_low < (1 << 31)) {
		ref_high = ref_high2;
	}
	return ((uint64_t)ref_high << 32) | (uint64_t)ref_low;
}

uint64_t z_impl_cmrt_uptime_get(void)
{
	return cmrt_perf_ref() * 1000 / sys_clock_hw_cycles_per_sec();
}

void cmrt_wait_cycles(uint32_t cycles)
{
	uint32_t now = cmrt_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_LOW);
	cycles += now; /* the target to reach */
	while (true) {
		now = cmrt_read_reg(CMRT_TIMER_BASE, R_GTIME_COUNT_LOW);
		if ((int32_t)(now - cycles) >= 0) {
			/* Passed the target, return. Note that uint32_t
			 * wrapping is handled by the cast to int32_t. */
			break;
		}
	}
}

void z_impl_cmrt_init_tmc_config(cmrt_tmc_init_params_t *params)
{
	(void)memset(params, 0, sizeof(*params));
#if IS_ENABLED(CMRT_TMC_EIP76_TRNG)
	params->control = cmrt_read_reg(CMRT_SIC_BASE, R_DEFAULT_TMC_TRNG_CTRL);
	params->config = cmrt_read_reg(CMRT_SIC_BASE, R_DEFAULT_TMC_TRNG_CFG);
	params->detune_limit = 8; /* large enough not to fail by accident */
#endif
}


#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

/* This function should go directly to cmrt_mpu_has_access() or
 * cmrt_sac_has_access(), and, check buffers with supervisor access as
 * well.  Now the functino goes through arch_buffer_validate() which is
 * dependent on CONFIG_USERSPACE.
 */
uint32_t z_impl_cmrt_access(uint32_t flags, const void *pbuf, size_t nbuf)
{
	static const uint32_t RW = CMRT_ACCESS_READ | CMRT_ACCESS_WRITE;

	uint32_t res = 0;

	if (flags == 0) {	     /* default, test any */
		flags = 0xffffffffu; /* test any flags present */
	}

	if ((flags & RW) != 0u) {
		void *parg = (void *)pbuf; /* bad signature */
		if (arch_buffer_validate(parg, nbuf,
					 flags & CMRT_ACCESS_WRITE) == 0) {
			res |= flags & RW;
		} else if (flags == RW) {
			/* no write access, test for read however */
			if (arch_buffer_validate(parg, nbuf, 0) == 0) {
				res |= CMRT_ACCESS_READ;
			}
		}
	}

	if ((flags & (CMRT_ACCESS_PRIVATE | CMRT_ACCESS_INTERNAL)) != 0u) {
		/* no memory is shared internally, so these are now the same.
		 */
		if (!IS_SAC_SPACE(pbuf, nbuf)) {
			res |= flags & (CMRT_ACCESS_PRIVATE | CMRT_ACCESS_INTERNAL);
		}
	}

	return res;
}

static inline int z_vrfy_cmrt_get_random(void *buf, size_t len)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buf, len));
	return z_impl_cmrt_get_random(buf, len);
}
#include <syscalls/cmrt_get_random_mrsh.c>

static inline int z_vrfy_cmrt_get_entropy(void *buf, size_t len)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buf, len));
	return z_impl_cmrt_get_entropy(buf, len);
}
#include <syscalls/cmrt_get_entropy_mrsh.c>

static inline void z_vrfy_cmrt_init_tmc_config(cmrt_tmc_init_params_t *params)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(params, sizeof(cmrt_tmc_init_params_t)));
	return z_impl_cmrt_init_tmc_config(params);
}
#include <syscalls/cmrt_init_tmc_config_mrsh.c>

static inline uint64_t z_vrfy_cmrt_perf_ref(void)
{
	return z_impl_cmrt_perf_ref();
}
#include <syscalls/cmrt_perf_ref_mrsh.c>

static inline uint64_t z_vrfy_cmrt_uptime_get(void)
{
	return z_impl_cmrt_uptime_get();
}
#include <syscalls/cmrt_uptime_get_mrsh.c>

static inline uint32_t z_vrfy_cmrt_access(uint32_t flags, const void *pbuf, size_t nbuf)
{
	return z_impl_cmrt_access(flags, pbuf, nbuf);
}
#include <syscalls/cmrt_access_mrsh.c>

void z_impl_cmrt_exit_container(int32_t arg)
{
	ARG_UNUSED(arg);
	LOG_INF("exiting container with %d", arg);
	k_thread_abort(k_current_get());
}

static inline void z_vrfy_cmrt_exit_container(int exitval)
{
	return z_impl_cmrt_exit_container(exitval);
}
#include <syscalls/cmrt_exit_container_mrsh.c>

#endif /* CONFIG_USERSPACE */
