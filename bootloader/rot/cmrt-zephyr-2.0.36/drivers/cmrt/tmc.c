/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_tmc

#include <device.h>
#include <init.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/tmc.h>
#include <drivers/cmrt/eac.h>
#include <drivers/cmrt/util.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_TMC_BASE); /* device tree must match headers */
#define CMRT_TMC_EIP76_FROS DT_INST_PROP(0, eip76_fros)

#if IS_ENABLED(CMRT_TMC_EIP76_TRNG)
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/omc.h>
#define TMC_TRNG_STATUS_ERROR_SHUTDOWN_OFLO (1UL << 1)
#define TMC_STATUS_ERROR_TRNG 0x85UL
#endif

typedef struct cmrt_tmc_context {
	cmrt_dd_context_t ddc;
	void *buffer;
	size_t buflen;
	uint32_t command;
#if IS_ENABLED(CMRT_TMC_EXT_ENTROPY)
	cmrt_tmc_get_entropy_t get_ext_entropy;
#endif
} cmrt_tmc_context_t;

#define TMC_CONTEXTS 1
CMRT_DD_CONTEXT static cmrt_tmc_context_t contexts[TMC_CONTEXTS];

#if IS_ENABLED(CMRT_TMC_EIP76_TRNG)
static uint32_t detune_limit;
static uint32_t eip76_detune_counter(bool clear)
{
	uint32_t options = sys_read32((mm_reg_t)(R_BASE+R_TRNG2_OPTIONS));
	uint32_t counter = options >> 24; /* high byte has the counter value */
	if (clear) {
		options |= 0xFF000000UL; /* clear the counter by writing 0xFF */
		sys_write32(options, (mm_reg_t)(R_BASE+R_TRNG2_OPTIONS));
	}
	return counter;
}
#endif

static inline uint32_t tmc_status(void)
{
	uint32_t status = cmrt_core_status(R_BASE);
	return status & HWC_STATUS_STATUS_MASK;
}

static inline bool is_tmc_success(uint32_t status)
{
	return ((status == HWC_STATUS_IDLE_LOCKED) ||
		(status == HWC_STATUS_SUCCESS) ||
		(status == HWC_TMC_STATUS_SUCCESS_TEST));
}

static inline bool wait_tmc_ready(void)
{
	int status = cmrt_wait_status_from(R_BASE, HWC_STATUS_BUSY);
	return is_tmc_success(status);
}

static int tmc_command(uint32_t cmd)
{
	if (!wait_tmc_ready()) { return -EIO; }
	sys_write32(cmd, (mm_reg_t)(R_BASE+R_CORE_CONTROL));
	return 0;
}

static void tmc_close_cb(cmrt_dd_context_t *ddc)
{
	if ((ddc->flags & CMRT_O_TMC_KDC) == CMRT_O_TMC_KDC) {
		/* Opened for KDC. Need to lock the core in order to flush. */
		(void)cmrt_lock_core(R_BASE);
	}
	cmrt_tmc_context_t *context = (cmrt_tmc_context_t *)ddc;
	context->buffer = NULL;
	context->buflen = 0;
	context->command = 0;
}

#if IS_ENABLED(CMRT_TMC_EIP76_TRNG)
static bool trng_is_configured(void)
{
	/* EIP76 must be configured to not shutdown in case number of FROs that
	 * have shutdown exceeds threshold value, which clears the bit that is
	 * used below to determine if TRNG is configured. */
	static_assert(((TRNG2_ALARMCNT_8_FRO | TRNG2_ALARMCNT_24_FRO) & 0x800000) == 0,
		      "TRNG_ALARMCNT.shutdown_fatal must be clear");

	/* Check enable_trng bit. */
	uint32_t trng_enabled = sys_read32((mm_reg_t)(R_BASE+R_TRNG2_CONTROL)) & 0x400;
	return trng_enabled != 0;
}
#endif

#if IS_ENABLED(CMRT_TMC_EIP76_TRNG)

/* TMC with EIP76a. */
static int tmc_open_cb(cmrt_dd_context_t *ddc, void *arg)
{
	int res = 0;

	/* TRNG can be configured only once. DRBG instantiation take long time
	 * to complete, so it is also done once. */
	if (!trng_is_configured()) {
		cmrt_tmc_init_params_t params, *p = arg;
		if (p == NULL) {
			/* Use default parameters. */
			cmrt_init_tmc_config(&params);
			p = &params;
		}
		LOG_DBG("TMC config 0x%x, control 0x%x, detune limit 0x%x", p->config, p->control, p->detune_limit);

		/* Sequence and values from CMRT v2.0 TMC MAS. */
		sys_write32(p->control, (mm_reg_t)(R_BASE+R_DRBG2_CONTROL));
		/* To ensure TRNG is idle, write zero twice to control register. */
		sys_write32(0x0, (mm_reg_t)(R_BASE+R_TRNG2_CONTROL));
		sys_write32(0x0, (mm_reg_t)(R_BASE+R_TRNG2_CONTROL));
		sys_write32(0xA90600, (mm_reg_t)(R_BASE+R_TRNG2_OPTIONS));
		sys_write32(0x0, (mm_reg_t)(R_BASE+R_TRNG2_FRODETUNE));
		sys_write32(p->config, (mm_reg_t)(R_BASE+R_TRNG2_CONFIG));
#if CMRT_TMC_EIP76_FROS == 8
		sys_write32(TRNG2_ALARMCNT_8_FRO, (mm_reg_t)(R_BASE+R_TRNG2_ALARMCNT));
		sys_write32(TRNG2_FROENABLE_8_FRO, (mm_reg_t)(R_BASE+R_TRNG2_FROENABLE));
#elif CMRT_TMC_EIP76_FROS == 24
		sys_write32(TRNG2_ALARMCNT_24_FRO, (mm_reg_t)(R_BASE+R_TRNG2_ALARMCNT));
		sys_write32(TRNG2_FROENABLE_24_FRO, (mm_reg_t)(R_BASE+R_TRNG2_FROENABLE));
#else
#error unsupported configuration
#endif
		sys_write32(0x66FD, (mm_reg_t)(R_BASE+R_TRNG2_CONTROL));
		detune_limit = p->detune_limit;

		/* TRNG is configured. Now instantiate DRBG. */
		res = tmc_command(TMC_CONTROL_INSTANTIATE);

		/* Wait for instantiation to complete, if explicitly asked to
		 * sync or if KDC is going to use TMC. */
		if (res == 0 &&
		    ((ddc->flags & CMRT_O_ASYNC) == 0 ||
		     (ddc->flags & CMRT_O_TMC_KDC) == CMRT_O_TMC_KDC)) {
#ifdef CONFIG_MULTITHREADING
			k_sem_reset(&ddc->sem);
			k_sem_give(&ddc->sem);
#endif
			cmrt_dd_unlock(ddc->dd, 0);
			res = cmrt_dd_sync(ddc);
			(void)cmrt_dd_lock(ddc->dd);
		}

	}
	if (res == 0 &&
	    (ddc->flags & CMRT_O_TMC_KDC) == CMRT_O_TMC_KDC) {
		/* KDC *core* will use TMC; flush to release HWC lock. */
		return cmrt_flush_core(R_BASE);
	}
	return res;
}

#else

/* TMC with CRNG. */
static int tmc_open_cb(cmrt_dd_context_t *ddc, void *arg)
{
	int res = 0;

	/* Do one time DRBG instantiation. */
	static bool instantiate_drbg = true;
	if (instantiate_drbg &&
	    (ddc->flags & CMRT_O_TMC_INSTANTIATED) == 0) {
		/* DRBG instantiate will fail if it is already
		 * instantiated. But state of DRBG can't be checked, so we first
		 * uninstantiate it, which will not cause an issue, even if it
		 * was not instantiated. */
		res = tmc_command(TMC_CONTROL_UNINSTANTIATE);
		if (res == 0) {
			res = tmc_command(TMC_CONTROL_INSTANTIATE);
		}

		/* Wait for instantiation to complete, if explicitly asked to
		 * sync or if KDC is going to use TMC. */
		if (res == 0 &&
		    ((ddc->flags & CMRT_O_ASYNC) == 0 ||
		     (ddc->flags & CMRT_O_TMC_KDC) == CMRT_O_TMC_KDC)) {
#ifdef CONFIG_MULTITHREADING
			k_sem_reset(&ddc->sem);
			k_sem_give(&ddc->sem);
#endif
			cmrt_dd_unlock(ddc->dd, 0);
			res = cmrt_dd_sync(ddc);
			(void)cmrt_dd_lock(ddc->dd);
		}
	}
	instantiate_drbg = false;
	if (res == 0 &&
	    (ddc->flags & CMRT_O_TMC_KDC) == CMRT_O_TMC_KDC) {
		/* KDC *core* is going to use TMC; TMC should be ready and
		 * unlocked. */
		if (!wait_tmc_ready()) {
			return -EIO;
		}
		return cmrt_flush_core(R_BASE);
	}
	return res;
}
#endif

int z_impl_cmrt_tmc_command(cmrt_tmc_t context, uint32_t command, void *buffer, size_t buflen)
{
	switch (command) {
	case CMRT_TMC_INSTANTIATE:
	case CMRT_TMC_UNINSTANTIATE:
	case CMRT_TMC_RESEED:
	case CMRT_TMC_HEALTH_CHECK:
		if ((buffer != NULL) || (buflen != 0)) {
			return -EINVAL;
		}
		/* fall through */
	case CMRT_TMC_GENERATE:
	case CMRT_TMC_RESEED_GENERATE:
		break;
	default:
		return -EINVAL;
	}
	if (!cmrt_dd_valid(context) || buflen > TMC_OUTPUT_SIZE) {
		return -EINVAL;
	}
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&context->ddc.sem);
	k_sem_give(&context->ddc.sem);
#endif
#if IS_ENABLED(CMRT_TMC_EIP76_TRNG)
	if (context->command == 0) {
		/* First command after open and instantiate. EIP76 is seeded
		 * automatically and fails if reseed is called first. */
		if (command == CMRT_TMC_RESEED_GENERATE) {
			command = CMRT_TMC_GENERATE;
		} else if (command == CMRT_TMC_RESEED) {
			command = CMRT_TMC_HEALTH_CHECK;
		}
	}
	/* Clear the detune counter. */
	(void)eip76_detune_counter(true);
#endif
	context->buffer = buffer;
	context->buflen = buflen;
	context->command = command;
	int rv = tmc_command(command);

	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&context->ddc, rv);
}

#if IS_ENABLED(CMRT_TMC_EXT_ENTROPY)
static void tmc_ext_reseed(cmrt_tmc_context_t *context)
{
	cmrt_tmc_get_entropy_t cb = context->get_ext_entropy;

	if (cb == NULL) {
		return;
	}

	uint32_t ext_st = cmrt_read_reg(CMRT_TMC_BASE, R_TRNG2_EXTERNAL_ENTROPY_STATUS);

	while (TMC_EXT_NEED_DATA(ext_st)) {
		uint32_t rngbits = cb();

		sys_write32(rngbits, (mm_reg_t)(R_BASE + R_TRNG2_EXTERNAL_ENTROPY_DATA));
		ext_st = cmrt_read_reg(CMRT_TMC_BASE, R_TRNG2_EXTERNAL_ENTROPY_STATUS);
	}
}
#endif

static int tmc_poll_cb(cmrt_dd_context_t *ddc)
{
	uint32_t status = tmc_status();
	if (IS_HWC_ERROR(status)) { return -EIO; }

#if IS_ENABLED(CMRT_TMC_EXT_ENTROPY)
	cmrt_tmc_context_t *context = (cmrt_tmc_context_t *)ddc;
	tmc_ext_reseed(context);
#endif

#if IS_ENABLED(CMRT_TMC_EIP76_TRNG)
	uint32_t counter = eip76_detune_counter(false);
	if (counter > detune_limit) {
		/* Too many detunes, this is fatal. */
		LOG_ERR("EIP-76 detune limit exceeded %d > %d!",
			counter, detune_limit);
		cmrt_eac_halt(CORE_ID_CPU, -EIO, -EMLINK);
	}
	if (status == TMC_STATUS_ERROR_TRNG) { return -EIO; }
#endif

	return status != HWC_STATUS_BUSY ? 0 : 1;
}

static int tmc_sync_cb(cmrt_dd_context_t *ddc, uint32_t *mask)
{
	ARG_UNUSED(mask);

	cmrt_tmc_context_t *context = (cmrt_tmc_context_t *)ddc;
	if (is_tmc_success(tmc_status())) {
		if ((context->command == CMRT_TMC_GENERATE ||
		     context->command == CMRT_TMC_RESEED_GENERATE) &&
		    (context->buffer != NULL)) {
			uint32_t buffer[TMC_OUTPUT_REGS];
			for (size_t i = 0; i < TMC_OUTPUT_REGS; i++) {
				/* Copy full words to a temp buffer. */
				buffer[i] = sys_read32((mm_reg_t)(R_BASE+R_CORE_OUTPUT+i*4u));
			}
			/* Then copy exact number of bytes to caller buffer. */
			(void)memcpy(context->buffer, buffer, context->buflen);
		}
		return 0;
	}
	return -EIO;
}

static cmrt_dd_t tmc_dd = {
	.base = CMRT_TMC_BASE,
	.is_locking = 1,
	.context_count = TMC_CONTEXTS,
	.context_size = sizeof(cmrt_tmc_context_t),
	.irq_mask = 0,
	.contexts = contexts,
};

static const struct cmrt_driver_api tmc_driver_api = {
	.open_cb = tmc_open_cb,
	.find_cb = NULL,
	.poll_cb = tmc_poll_cb,
	.sync_cb = tmc_sync_cb,
	.close_cb = tmc_close_cb,
};

DEVICE_DT_INST_DEFINE(0, cmrt_dev_init, NULL, &tmc_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		      (void *)&tmc_driver_api);

cmrt_tmc_t z_impl_cmrt_tmc_open(uint32_t flags, void *arg)
{
	return (cmrt_tmc_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, arg);
}

void z_impl_cmrt_tmc_close(cmrt_tmc_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_tmc_sync(cmrt_tmc_t context)
{
	if (!cmrt_dd_valid(context)) {
		return -EINVAL;
	}
	if ((context->ddc.flags & CMRT_O_SYNC) != 0u) {
		/* Already synced internally. */
		return 0;
	}
	return cmrt_dd_sync((cmrt_dd_context_t *)context);
}

#if IS_ENABLED(CMRT_TMC_EXT_ENTROPY)
int cmrt_tmc_set_ext_entropy(cmrt_tmc_t context, uint32_t type, cmrt_tmc_get_entropy_t cb)
{
	if (!cmrt_dd_valid(context)) {
		return -EINVAL;
	}

	switch (type) {
	case TMC_EXT_CTRL_EXT_ONLY: /* FALL-THRU */
	case TMC_EXT_CTRL_MIXED:
		if (cb == NULL) {
			return -EINVAL;
		}
		context->get_ext_entropy = cb;
		/* FALL-THRU */
	case TMC_EXT_CTRL_NRBG_ONLY:
		sys_write32(type, (mm_reg_t)(R_BASE + R_TRNG2_EXTERNAL_ENTROPY_CONTROL));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
#endif


#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_tmc_context(cmrt_tmc_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &tmc_driver_api);
}

static inline cmrt_tmc_t z_vrfy_cmrt_tmc_open(uint32_t flags, void *arg)
{
	if (arg != NULL) {
		Z_OOPS(Z_SYSCALL_MEMORY_READ(arg, sizeof(cmrt_tmc_init_params_t)));
	}
	return z_impl_cmrt_tmc_open(flags, arg);
}
#include <syscalls/cmrt_tmc_open_mrsh.c>

static inline void z_vrfy_cmrt_tmc_close(cmrt_tmc_t context)
{
	z_syscall_verify_tmc_context(context);
	z_impl_cmrt_tmc_close(context);
}
#include <syscalls/cmrt_tmc_close_mrsh.c>

static inline int z_vrfy_cmrt_tmc_command(cmrt_tmc_t context, cmrt_tmc_command_t command, void *buffer, size_t size)
{
	z_syscall_verify_tmc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buffer, size));
	return z_impl_cmrt_tmc_command(context, command, buffer, size);
}
#include <syscalls/cmrt_tmc_command_mrsh.c>

static inline int z_vrfy_cmrt_tmc_sync(cmrt_tmc_t context)
{
	z_syscall_verify_tmc_context(context);
	return z_impl_cmrt_tmc_sync(context);
}
#include <syscalls/cmrt_tmc_sync_mrsh.c>

#endif /* CONFIG_USERSPACE */
