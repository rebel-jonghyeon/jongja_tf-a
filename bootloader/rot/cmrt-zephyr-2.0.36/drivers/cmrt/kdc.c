/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_kdc

#include <device.h>
#include <init.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/kdc.h>
#include <drivers/cmrt/hc_reg.h>
#include <drivers/cmrt/omc_reg.h>
#include <drivers/cmrt/sic_reg.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
#include "kat/kdc_kat.h"
#endif

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_KDC_BASE); /* device tree must match headers */
#define CMRT_KDC_IRQ DT_INST_IRQN(0)

/* Do not interrupt on KDC_DGOK_READY_IRQ.
 * This interrupt is triggered if cmd is BURN_DGOK,
 * and when KDC has key ready for eSW. But first of all,
 * sw is not interested in the key when burning DGOK,
 * and secondly sw will always have to wait for OTP
 * write to finish. Therefore, it is meanlingless to
 * enable this interrupt.
 * The E stands for Effective.
 */
#define EKDC_IRQ_MASK (KDC_IRQ_MASK & (~KDC_DGOK_READY_IRQ))

typedef struct cmrt_kdc_context {
	cmrt_dd_context_t ddc;
	cmrt_kdc_cmd_t *cmd;
} cmrt_kdc_context_t;

#define KDC_CONTEXTS 1
CMRT_DD_CONTEXT static cmrt_kdc_context_t contexts[KDC_CONTEXTS];

#ifdef CONFIG_MULTITHREADING
static void kdc_irq_handler(void *arg)
{
	ARG_UNUSED(arg);

	/* Get and clear interrupt, first internal interrupt. */
	uint32_t pending = sys_read32(R_BASE+R_CORE_INTERRUPT);
	sys_write32(pending, R_BASE+R_CORE_INTERRUPT);

	k_sem_give(&contexts[0].ddc.sem);
}
#endif

static inline uint32_t kdc_status(void)
{
	uint32_t status = cmrt_core_status(R_BASE);
	return status & HWC_STATUS_STATUS_MASK;
}

static int issue_kdc_command(cmrt_kdc_context_t *context,
			     uint32_t corectl, uint32_t keyctl, uint32_t dest,
			     uint32_t command0, uint32_t command1, cmrt_kdc_cmd_t *cmd)
{
#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&context->ddc.sem);
#endif
	uint32_t *p = cmd->diversify_path;
	for (size_t i = 0; i < KDC_DIVERSIFY_PATH_WORDS; ++i) {
		sys_write32(*p, R_BASE+R_DIVERSIFY_PATH0 + i * 4u);
		++p;
	}

	sys_write32(command0, R_BASE+R_DEST_COMMAND0);
	sys_write32(command1, R_BASE+R_DEST_COMMAND1);
	sys_write32(dest, R_BASE+R_KDC_DEST);
	sys_write32(keyctl, R_BASE+R_KDC_KEY_CONTROL);

	cmd->ctrl = corectl;
	/*
	 * Save a reference to the caller-specified `cmd` structure
	 * for the sync operation.
	 */
	context->cmd = cmd;

	sys_write32(corectl, R_BASE+R_CORE_CONTROL);

	return IS_HWC_ERROR(kdc_status()) ? -EIO : 0;
}

int cmrt_kdc_burn_dgok(cmrt_kdc_t context, cmrt_kdc_cmd_t *cmd)
{
	int ret = -EIO;
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	uint32_t corectl = KDC_CTRL_BURN_DGOK;
	kdc_key_ctrl_t keyctl = { .val = 0 };
	kdc_dest_t dest = { .val = 0 };
	uint32_t command0 = 0;
	uint32_t command1 = 0;

	keyctl.s.base_key_id = KEY_ID_DGOK;
	keyctl.s.path_len = (uint8_t)cmd->diversify_len + 1;
	dest.s.dest = KDC_DEST_SW;
	dest.s.size = KDC_SIZE_256;

	ret = issue_kdc_command(context, corectl, keyctl.val, dest.val,
				command0, command1, cmd);

	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&context->ddc, ret);
}

static int kdc_otp_key_programmed(uint32_t key_id)
{
	uint32_t ks_status = cmrt_read_reg(CMRT_SIC_BASE, R_DEVICE_KEYS_PERSO_STATUS);
	if ((ks_status & DEVICE_KEYS_PERSO_STATUS_MASK) != DEVICE_KEYS_PERSO_STATUS_VALID) {
		return -EBUSY; /* SIC status is not ready, device reset is needed. */
	}

	ks_status &= ~DEVICE_KEYS_PERSO_STATUS_MASK;
	key_id &= KEY_ID_OTP_KPMASK;
	if ((ks_status & (1UL << (key_id+1u))) == 0u) {
		return -EIO; /* Keysplit/DGOK is unprogrammed. */
	}
	return 0;
}

static int kdc_derive_diversify(cmrt_kdc_t context, cmrt_kdc_cmd_t *cmd, uint32_t corectl)
{
	if (!cmrt_dd_valid(context) || cmd == NULL) { return -EINVAL; }

	int ret = -EIO;
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	kdc_key_ctrl_t keyctl = { .val = 0 };
	kdc_dest_t dest = { .val = 0 };
	uint32_t command0 = 0;
	uint32_t command1 = 0;

	if (cmd->base_key_id == KEY_ID_DGOK ||
	    !is_invalid_kdc_keysplit_id(cmd->base_key_id)) {
		/*
		 * Base key is a keysplit or the DGOK. To avoid device
		 * crash do not use it if it is unprogrammed.
		 */
		ret = kdc_otp_key_programmed(cmd->base_key_id);
		if (ret != 0) {
			goto out;
		}
#ifdef CONFIG_CMRT_FBOOT
		/* Check OMC to avoid freeze in security monitor. */
		uint32_t omc_status = cmrt_core_status(CMRT_OMC_BASE) & HWC_STATUS_STATUS_MASK;
		if (omc_status != HWC_STATUS_AVAILABLE) {
			return -EBUSY;
		}
#endif
	}
#ifdef CONFIG_CMRT_FBOOT
	if (cmd->dest != KDC_DEST_HMAC) {
		/* Check HC to avoid freeze in security monitor. */
		uint32_t hc_status = cmrt_core_status(CMRT_HC_BASE) & HWC_STATUS_STATUS_MASK;
		if (hc_status != HWC_STATUS_AVAILABLE) {
			return -EBUSY;
		}
	}
#endif
	keyctl.s.base_key_id = (uint8_t)cmd->base_key_id;
	keyctl.s.path_len = (uint8_t)cmd->diversify_len + 1;
	dest.s.dest = (uint8_t)cmd->dest;
	dest.s.size = (uint8_t)cmd->key_size;

	switch (cmd->dest) {
	case KDC_DEST_HMAC:
	case KDC_DEST_HMAC2:
	case KDC_DEST_AES:
		/* KDC will shift it left. */
		command0 = cmd->command0 >> HC_HASH_ALGO_SHIFT;
		command1 = cmd->command1;
		break;
	default:
		if ((cmd->dest & KDC_DEST_KEYBUS_MASK) != 0u) {
			command0 = cmd->command0;
			command1 = cmd->command1;
		}
		break;
	}
	ret = issue_kdc_command(context, corectl, keyctl.val, dest.val,
				command0, command1, cmd);
out:
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&context->ddc, ret);
}

int z_impl_cmrt_kdc_derive_key(cmrt_kdc_t context, cmrt_kdc_cmd_t *cmd)
{
	return kdc_derive_diversify(context, cmd, KDC_CTRL_DERIVE);
}

int z_impl_cmrt_kdc_diversify_key(cmrt_kdc_t context, cmrt_kdc_cmd_t *cmd)
{
	return kdc_derive_diversify(context, cmd, KDC_CTRL_DIVERSIFY);
}

static int kdc_sync_cb(cmrt_dd_context_t *ddc, uint32_t *mask)
{
	ARG_UNUSED(mask);
	cmrt_kdc_context_t *context = (cmrt_kdc_context_t *)ddc;

	/*
	 * Drop our reference to caller-specified data as it might not
	 * live after this call.  This should be done even in case of
	 * an error, so we take a copy.
	 */
	cmrt_kdc_cmd_t *cmd = context->cmd;
	context->cmd = NULL;

	if (kdc_status() != HWC_STATUS_SUCCESS) {
		return -EIO;
	}
	/* Now everything is fine. If eSW is waiting for key, copy it to cmd. */
	if (cmd == NULL) {
		return -EINVAL;
	}
	if (cmd->dest == KDC_DEST_SW) {
		uint32_t *p = cmd->key;
		for (uint32_t i = 0; i < 8u; ++i) {
			p[i] = sys_read32((mm_reg_t)(R_BASE+R_KDC_KEY0 + i * 4u));
		}
	}
	return 0;
}

int cmrt_kdc_set_derive_path(cmrt_kdc_t context, const cmrt_kdc_drv_path_t *drv_path)
{
#ifdef CONFIG_SUPERVISOR_MODE
	ARG_UNUSED(context);
	ARG_UNUSED(drv_path);
	return -EPERM;
#else
	if (!cmrt_dd_valid(context) || drv_path == NULL) { return -EINVAL; }

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	const uint32_t *p = drv_path->path;
	/* R_DERIVE_PATH is write-once until CCC/reset */
	for (size_t i = 0; i < KDC_DERIVE_PATH_WORDS; ++i) {
		sys_write32(*p, R_BASE+R_DERIVE_PATH0 + i * 4u);
		++p;
	}
	cmrt_dd_unlock(dd, mask);
	return 0;
#endif
}

static int kdc_poll_cb(cmrt_dd_context_t *ddc)
{
	ARG_UNUSED(ddc);
	uint32_t status = kdc_status();
	return ((status != HWC_STATUS_BUSY) &&
		(status != KDC_STATUS_DGOKSW_READY)) ? 0 : 1;
}

int cmrt_kdc_permissions(cmrt_kdc_t context, const cmrt_omc_key_perm_t *perm)
{
#ifdef CONFIG_SUPERVISOR_MODE
	ARG_UNUSED(context);
	ARG_UNUSED(perm);
	return -EPERM;
#else
	if (!cmrt_dd_valid(context) || perm == NULL) { return -EINVAL; }

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	sys_write32(perm->val & 0xFFFFUL, R_BASE+R_OTP_USE_KEYS);

	cmrt_dd_unlock(dd, mask);
	return 0;
#endif
}

void cmrt_kdc_disable(void)
{
	sys_write32(DISABLE_KDC, R_BASE+R_DISABLE_KDC);
}

int cmrt_kdc_set_hw_state(cmrt_kdc_t context, uint8_t hw_state)
{
#ifdef CONFIG_SUPERVISOR_MODE
	ARG_UNUSED(context);
	ARG_UNUSED(hw_state);
	return -EPERM;
#else
	if (!cmrt_dd_valid(context)) { return -EINVAL; }

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	sys_write32(hw_state, R_BASE+R_KDC_HW_STATE);

	cmrt_dd_unlock(dd, mask);
	return 0;
#endif
}

static int cmrt_kdc_init(const struct device *dev)
{
	cmrt_dd_t *dd = dev->data;
	cmrt_dd_init(dd, dev);

#ifdef CONFIG_MULTITHREADING
	/* Setup IRQ handler for the driver. */
	IRQ_CONNECT(CMRT_KDC_IRQ, 0, kdc_irq_handler, NULL, 0);
#endif

	return 0;
}

static cmrt_dd_t kdc_dd = {
	.base = CMRT_KDC_BASE,
	.is_locking = 1,
	.context_count = KDC_CONTEXTS,
	.context_size = sizeof(cmrt_kdc_context_t),
#ifdef CONFIG_MULTITHREADING
	.irq_mask = EKDC_IRQ_MASK,
#else
	.irq_mask = 0,
#endif
	.contexts = contexts,
};

static const struct cmrt_driver_api kdc_driver_api = {
	.open_cb = NULL,
#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
#ifdef CONFIG_CMRT_FBOOT
	.open_kat = NULL,
#else
	.open_kat = kdc_open_kat,
#endif
#endif
	.find_cb = NULL,
	.poll_cb = kdc_poll_cb,
	.sync_cb = kdc_sync_cb,
	.close_cb = NULL,
};

DEVICE_DT_INST_DEFINE(0, cmrt_kdc_init, NULL, &kdc_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &kdc_driver_api);

#if defined(CONFIG_CMRT_ASIL_B_MODE)
SYS_INIT(kdc_init_kat, POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY);
#endif

cmrt_kdc_t z_impl_cmrt_kdc_open(uint32_t flags)
{
	return (cmrt_kdc_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, NULL);
}

void z_impl_cmrt_kdc_close(cmrt_kdc_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_kdc_sync(cmrt_kdc_t context)
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

static inline void z_syscall_verify_kdc_context(cmrt_kdc_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &kdc_driver_api);
}

static inline cmrt_kdc_t z_vrfy_cmrt_kdc_open(uint32_t flags)
{
	return z_impl_cmrt_kdc_open(flags);
}
#include <syscalls/cmrt_kdc_open_mrsh.c>

static inline void z_vrfy_cmrt_kdc_close(cmrt_kdc_t context)
{
	z_syscall_verify_kdc_context(context);
	z_impl_cmrt_kdc_close(context);
}
#include <syscalls/cmrt_kdc_close_mrsh.c>

static inline int z_vrfy_cmrt_kdc_derive_key(cmrt_kdc_t context, cmrt_kdc_cmd_t *cmd)
{
	z_syscall_verify_kdc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(cmd, sizeof(*cmd)));
	return z_impl_cmrt_kdc_derive_key(context, cmd);
}
#include <syscalls/cmrt_kdc_derive_key_mrsh.c>

static inline int z_vrfy_cmrt_kdc_diversify_key(cmrt_kdc_t context, cmrt_kdc_cmd_t *cmd)
{
	z_syscall_verify_kdc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(cmd, sizeof(*cmd)));
	return z_impl_cmrt_kdc_diversify_key(context, cmd);
}
#include <syscalls/cmrt_kdc_diversify_key_mrsh.c>

static inline int z_vrfy_cmrt_kdc_sync(cmrt_kdc_t context)
{
	z_syscall_verify_kdc_context(context);
	return z_impl_cmrt_kdc_sync(context);
}
#include <syscalls/cmrt_kdc_sync_mrsh.c>

#endif /* CONFIG_USERSPACE */
