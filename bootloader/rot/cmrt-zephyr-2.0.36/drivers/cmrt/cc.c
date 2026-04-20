/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_cc

#include <device.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/cc.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_CC_BASE); /* device tree must match headers */

typedef struct cmrt_cc_context {
	cmrt_dd_context_t ddc;
} cmrt_cc_context_t;

#define CC_CONTEXTS 1
CMRT_DD_CONTEXT static cmrt_cc_context_t contexts[CC_CONTEXTS];

static inline uint32_t cc_status(void)
{
	uint32_t status = cmrt_core_status(R_BASE);
	return status & HWC_STATUS_STATUS_MASK;
}

static inline bool is_cc_ready(void)
{
	return cc_status() == HWC_STATUS_IDLE_LOCKED;
}

static inline int cc_command(uint32_t command)
{
	sys_write32(command, (mm_reg_t)(R_BASE+R_CORE_CONTROL));
	int rv = cmrt_wait_status_from(R_BASE, HWC_STATUS_BUSY);
	if (rv == (int)HWC_STATUS_IDLE_LOCKED) {
		return 0;
	}
	return -EIO;
}

int z_impl_cmrt_cc_assert(cmrt_cc_t context, uint32_t assert0, uint32_t assert1)
{
	if (!cmrt_dd_valid(context)) { return -EINVAL; }

	int rv = -EIO;
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	if (is_cc_ready()) {
		sys_write32(assert0, R_BASE+R_ASSERT_VALUE0);
		sys_write32(assert1, R_BASE+R_ASSERT_VALUE1);
		rv = 0;
	}

	cmrt_dd_unlock(dd, mask);
	return rv;
}

int z_impl_cmrt_cc_mix(cmrt_cc_t context, uint32_t value)
{
	if (!cmrt_dd_valid(context)) { return -EINVAL; }

	int rv = -EIO;
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	if (is_cc_ready()) {
		sys_write32(value, R_BASE+R_DATA_MIX);
		rv = cc_command(CC_CONTROL_MIX);
	}

	cmrt_dd_unlock(dd, mask);
	return rv;
}

static cmrt_dd_t cc_dd = {
	.base = CMRT_CC_BASE,
	.is_locking = 1,
	.context_count = CC_CONTEXTS,
	.context_size = sizeof(cmrt_cc_context_t),
	.irq_mask = 0,
	.contexts = contexts,
};

static const struct cmrt_driver_api cc_driver_api = {
	.open_cb = NULL,
	.find_cb = NULL,
	.poll_cb = NULL,
	.sync_cb = NULL,
	.close_cb = NULL,
};

DEVICE_DT_INST_DEFINE(0, cmrt_dev_init, NULL, &cc_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		      (void *)&cc_driver_api);

cmrt_cc_t z_impl_cmrt_cc_open(void)
{
    return (cmrt_cc_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), 0, NULL);
}

void z_impl_cmrt_cc_close(cmrt_cc_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_cc_sync(cmrt_cc_t context)
{
	int rv = -EIO;
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	if (is_cc_ready()) {
		rv = cc_command(CC_CONTROL_ASSERT);
	}
	cmrt_dd_unlock(dd, mask);
	return rv;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_cc_context(cmrt_cc_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &cc_driver_api);
}

static inline cmrt_cc_t z_vrfy_cmrt_cc_open(void)
{
	return z_impl_cmrt_cc_open();
}
#include <syscalls/cmrt_cc_open_mrsh.c>

static inline void z_vrfy_cmrt_cc_close(cmrt_cc_t context)
{
	z_syscall_verify_cc_context(context);
	z_impl_cmrt_cc_close(context);
}
#include <syscalls/cmrt_cc_close_mrsh.c>

static inline int z_vrfy_cmrt_cc_assert(cmrt_cc_t context, uint32_t assert0, uint32_t assert1)
{
	z_syscall_verify_cc_context(context);
	return z_impl_cmrt_cc_assert(context, assert0, assert1);
}
#include <syscalls/cmrt_cc_assert_mrsh.c>

static inline int z_vrfy_cmrt_cc_mix(cmrt_cc_t context, uint32_t value)
{
	z_syscall_verify_cc_context(context);
	return z_impl_cmrt_cc_mix(context, value);
}
#include <syscalls/cmrt_cc_mix_mrsh.c>

static inline int z_vrfy_cmrt_cc_sync(cmrt_cc_t context)
{
	z_syscall_verify_cc_context(context);
	return z_impl_cmrt_cc_sync(context);
}
#include <syscalls/cmrt_cc_sync_mrsh.c>

#endif /* CONFIG_USERSPACE */
