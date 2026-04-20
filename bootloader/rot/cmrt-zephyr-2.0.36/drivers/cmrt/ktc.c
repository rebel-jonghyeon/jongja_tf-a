/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_ktc

#include <device.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/ktc.h>
#include <drivers/cmrt/util.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_KTC_BASE); /* device tree must match headers */

typedef struct cmrt_ktc_context {
	/* ddc shall be first element because we don't use contain_of */
	cmrt_dd_context_t ddc;
	uint32_t block;
	uint32_t blocks;
	uint32_t *key;
	uint32_t timeout;
	uint64_t uptime;
} cmrt_ktc_context_t;

#define KTC_CONTEXTS 1
CMRT_DD_CONTEXT static cmrt_ktc_context_t contexts[KTC_CONTEXTS];

static inline uint32_t ktc_status(void)
{
	uint32_t status = cmrt_core_status(R_BASE);
	return status & HWC_STATUS_STATUS_MASK;
}

static int ktc_open_cb(cmrt_dd_context_t *ddc, void *arg)
{
	cmrt_ktc_context_t *context = (cmrt_ktc_context_t *)ddc;
	context->timeout = (uint32_t)(uintptr_t)arg;
	return 0;
}

static int ktc_poll_cb(cmrt_dd_context_t *ddc)
{
	cmrt_ktc_context_t *context = (cmrt_ktc_context_t *)ddc;
	uint32_t status = ktc_status();
	if (IS_HWC_ERROR(status)) { return -EIO; }
	if (status == KTC_STATUS_READY_FOR_NEXT) {
		if (context->block >= context->blocks) { return -EIO; }
		uint32_t index = context->block * KTC_KEY_DATA_WORDS;
		for (int i = 0; i < KTC_KEY_DATA_WORDS; i++) {
			uint32_t word = context->key[index++];
			sys_write32(word, (mm_reg_t)(R_BASE+R_KTC_KEY_DATA0+4*i));
		}
		sys_write32(KTC_CONTROL_UPDATE, (mm_reg_t)(R_BASE+R_CORE_CONTROL));
		context->block++;
	} else if (context->timeout != 0) {
		/* Monitor HLOS slowness. */
		uint64_t uptime = cmrt_uptime_get();
		if (context->uptime == 0) {
			/* Set reference time. */
			context->uptime = uptime;
		} else if (context->uptime + context->timeout < uptime) {
			/* HLOS is too slow! */
			return -ETIMEDOUT;
		}
	}
	return (status == HWC_STATUS_SUCCESS &&
		context->block == context->blocks) ? 0 : 1;
}

int z_impl_cmrt_ktc_export(cmrt_ktc_t context, const cmrt_ktc_cmd_t *cmd)
{
	if (!cmrt_dd_valid(context) || cmd == NULL || cmd->key == NULL ||
	    !is_aligned(cmd->key_size, 16u) || cmd->key_size > (unsigned)KTC_MAX_KEY_SIZE) {
		return -EINVAL;
	}
	if (ktc_status() != HWC_STATUS_IDLE_LOCKED) { return -EIO; }

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	sys_write32(cmd->metadata[0], (mm_reg_t)(R_BASE+R_KTC_KEY_METADATA0));
	sys_write32(cmd->metadata[1], (mm_reg_t)(R_BASE+R_KTC_KEY_METADATA1));
	sys_write32(cmd->destination & 0x0fU, (mm_reg_t)(R_BASE+R_KTC_KEY_DESTINATION));
	context->blocks = cmd->key_size >> 4;
	sys_write32(context->blocks, (mm_reg_t)(R_BASE+R_KTC_BLOCK_TOTAL_NUM));
	context->key = cmd->key;
	context->block = 0;
	context->uptime = 0;
#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&context->ddc.sem);
	k_sem_give(&context->ddc.sem);
#endif
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&context->ddc, 0);
}

int cmrt_ktc_permissions(cmrt_ktc_t context, const cmrt_omc_key_perm_t *perm)
{

#ifdef CONFIG_SUPERVISOR_MODE
	ARG_UNUSED(context);
	ARG_UNUSED(perm);
	return -EPERM;
#else
	if (!cmrt_dd_valid(context) || perm == NULL) { return -EINVAL; }

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	sys_write32(perm->s.key_destinations, R_BASE+R_KTC_ALLOWED_DESTINATONS);
	cmrt_dd_unlock(dd, mask);
	return 0;
#endif
}

static cmrt_dd_t ktc_dd = {
	.base = CMRT_KTC_BASE,
	.is_locking = 1,
	.context_count = KTC_CONTEXTS,
	.context_size = sizeof(cmrt_ktc_context_t),
	.irq_mask = 0,
	.contexts = contexts,
};

static const struct cmrt_driver_api ktc_driver_api = {
	.open_cb = ktc_open_cb,
	.find_cb = NULL,
	.poll_cb = ktc_poll_cb,
	.sync_cb = NULL,
	.close_cb = NULL,
};

DEVICE_DT_INST_DEFINE(0, cmrt_dev_init, NULL, &ktc_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &ktc_driver_api);

cmrt_ktc_t z_impl_cmrt_ktc_open(uint32_t flags, uint32_t timeout)
{
	return (cmrt_ktc_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, (void *)(uintptr_t)timeout);
}

void z_impl_cmrt_ktc_close(cmrt_ktc_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_ktc_sync(cmrt_ktc_t context)
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

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_ktc_context(cmrt_ktc_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &ktc_driver_api);
}

static inline cmrt_ktc_t z_vrfy_cmrt_ktc_open(uint32_t flags, uint32_t timeout)
{
	return z_impl_cmrt_ktc_open(flags, timeout);
}
#include <syscalls/cmrt_ktc_open_mrsh.c>

static inline void z_vrfy_cmrt_ktc_close(cmrt_ktc_t context)
{
	z_syscall_verify_ktc_context(context);
	z_impl_cmrt_ktc_close(context);
}
#include <syscalls/cmrt_ktc_close_mrsh.c>

static inline int z_vrfy_cmrt_ktc_export(cmrt_ktc_t context, const cmrt_ktc_cmd_t *cmd)
{
	z_syscall_verify_ktc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(cmd, sizeof(*cmd)));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(cmd->key, cmd->key_size));
	return z_impl_cmrt_ktc_export(context, cmd);
}
#include <syscalls/cmrt_ktc_export_mrsh.c>

static inline int z_vrfy_cmrt_ktc_sync(cmrt_ktc_t context)
{
	z_syscall_verify_ktc_context(context);
	return z_impl_cmrt_ktc_sync(context);
}
#include <syscalls/cmrt_ktc_sync_mrsh.c>

#endif /* CONFIG_USERSPACE */
