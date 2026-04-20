/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_fmc

#include <device.h>
#include <sys/sys_io.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/fmc.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_FMC_BASE); /* device tree must match headers */

typedef struct cmrt_fmc_context {
	cmrt_dd_context_t ddc;
} cmrt_fmc_context_t;

#define FMC_CONTEXTS 1 /* only one active at a time */
CMRT_DD_CONTEXT static cmrt_fmc_context_t contexts[FMC_CONTEXTS];

int z_impl_cmrt_fmc_read(cmrt_fmc_t context, uint32_t addr, uint32_t *data)
{
	if (!cmrt_dd_valid(context) || !is_aligned(addr, 4u)) {
		/* Address must be word aligned. */
		return -EINVAL;
	}
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	(void)cmrt_lock_core(R_BASE);
	sys_write32(addr, R_BASE+R_FEATURE_ADDRESS);
	sys_write32(FMC_CONTROL_FEATURE_READ, R_BASE+R_CORE_CONTROL);
	int rc = cmrt_wait_status_from(R_BASE, HWC_STATUS_BUSY);
	switch ((uint32_t)rc) {
	case HWC_STATUS_ERROR:
		rc = -EPERM;
		break;
	case FMC_STATUS_ERROR_DATA:
		rc = -EIO;
		break;
	default:
		*data = sys_read32(R_BASE+R_FEATURE_DATA);
		rc = 0;
		break;
	}
	sys_write32(HWC_CONTROL_FLUSH, R_BASE+R_CORE_CONTROL);

	cmrt_dd_unlock(dd, mask);
	return rc;
}

int z_impl_cmrt_fmc_write(cmrt_fmc_t context, uint32_t addr, uint32_t data, uint32_t data_mask)
{
	if (!cmrt_dd_valid(context) || !is_aligned(addr, 4u)) {
		/* Address must be word aligned. */
		return -EINVAL;
	}
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	(void)cmrt_lock_core(R_BASE);
	sys_write32(addr, R_BASE+R_FEATURE_ADDRESS);
	sys_write32(data, R_BASE+R_FEATURE_DATA);
	sys_write32(data_mask, R_BASE+R_FEATURE_DATA_MASK);
	sys_write32(FMC_CONTROL_FEATURE_WRITE, R_BASE+R_CORE_CONTROL);
	int rc = cmrt_wait_status_from(R_BASE, HWC_STATUS_BUSY);
	switch ((uint32_t)rc) {
	case HWC_STATUS_ERROR:
		rc = -EPERM;
		break;
	case FMC_STATUS_ERROR_DATA:
		rc = -EIO;
		break;
	default:
		rc = 0;
		break;
	}
	sys_write32(HWC_CONTROL_FLUSH, R_BASE+R_CORE_CONTROL);

	cmrt_dd_unlock(dd, mask);
	return rc;
}

int cmrt_fmc_permissions(cmrt_fmc_t context, uint32_t bitmap)
{
#ifdef CONFIG_SUPERVISOR_MODE
	ARG_UNUSED(context);
	ARG_UNUSED(bitmap);
	return -EPERM;
#else
	if (!cmrt_dd_valid(context)) { return -EINVAL; }
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	(void)cmrt_lock_core(R_BASE);
	sys_write32(bitmap, R_BASE+R_OTP_FEATURE_W);
	sys_write32(HWC_CONTROL_FLUSH, R_BASE+R_CORE_CONTROL);

	cmrt_dd_unlock(dd, mask);
	return 0;
#endif
}

int z_impl_cmrt_fmc_set_debug_mode(cmrt_fmc_t context)
{
	uint32_t tdv; /* we only need the first word */
	int rc = cmrt_fmc_read(context, FMC_TDV_OFFSET, &tdv);
	if (rc == 0 && (tdv & FMC_TEST_MODE_BIT) == 0) {
		tdv |= FMC_TEST_MODE_BIT;
		rc = cmrt_fmc_write(context, FMC_TDV_OFFSET, tdv, 0xffffffff);
	}
	return rc;
}

static cmrt_dd_t fmc_dd = {
	.base = CMRT_FMC_BASE,
	.is_locking = 0,
	.context_count = FMC_CONTEXTS,
	.context_size = sizeof(cmrt_fmc_context_t),
	.irq_mask = 0,
	.contexts = contexts,
};

static const struct cmrt_driver_api fmc_driver_api = {
	.open_cb = NULL,
	.find_cb = NULL,
	.poll_cb = NULL,
	.sync_cb = NULL,
	.close_cb = NULL,
};

DEVICE_DT_INST_DEFINE(0, cmrt_dev_init, NULL, &fmc_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      (void *)&fmc_driver_api);

cmrt_fmc_t z_impl_cmrt_fmc_open(void)
{
	return (cmrt_fmc_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), 0, NULL);
}

void z_impl_cmrt_fmc_close(cmrt_fmc_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_fmc_context(cmrt_fmc_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &fmc_driver_api);
}

static inline cmrt_fmc_t z_vrfy_cmrt_fmc_open(void)
{
	return z_impl_cmrt_fmc_open();
}
#include <syscalls/cmrt_fmc_open_mrsh.c>

static inline void z_vrfy_cmrt_fmc_close(cmrt_fmc_t context)
{
	z_syscall_verify_fmc_context(context);
	z_impl_cmrt_fmc_close(context);
}
#include <syscalls/cmrt_fmc_close_mrsh.c>

static inline int z_vrfy_cmrt_fmc_read(cmrt_fmc_t context, uint32_t addr, uint32_t *data)
{
	z_syscall_verify_fmc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(data, sizeof(*data)));
	return z_impl_cmrt_fmc_read(context, addr, data);
}
#include <syscalls/cmrt_fmc_read_mrsh.c>

static inline int z_vrfy_cmrt_fmc_write(cmrt_fmc_t context, uint32_t addr, uint32_t data, uint32_t mask)
{
	z_syscall_verify_fmc_context(context);
	return z_impl_cmrt_fmc_write(context, addr, data, mask);
}
#include <syscalls/cmrt_fmc_write_mrsh.c>

static inline int z_vrfy_cmrt_fmc_set_debug_mode(cmrt_fmc_t context)
{
	z_syscall_verify_fmc_context(context);
	return z_impl_cmrt_fmc_set_debug_mode(context);
}
#include <syscalls/cmrt_fmc_set_debug_mode_mrsh.c>

#endif /* CONFIG_USERSPACE */
