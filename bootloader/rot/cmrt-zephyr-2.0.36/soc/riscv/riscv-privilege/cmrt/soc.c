/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief CMRT RISC-V virt machine hardware depended interface
 */

#include <kernel.h>
#include <arch/cpu.h>
#include <drivers/cmrt/eac.h>
#include <logging/log_ctrl.h>
#include <logging/log.h>

LOG_MODULE_DECLARE(os, CONFIG_KERNEL_LOG_LEVEL);

void sys_arch_reboot(int type)
{
	ARG_UNUSED(type);
	cmrt_eac_reboot();
}

FUNC_NORETURN void arch_system_halt(unsigned int reason)
{
	cmrt_eac_halt(CORE_ID_CPU, -EINTR, reason);
}

void k_sys_fatal_error_handler(unsigned int reason, const z_arch_esf_t *esf)
{
	ARG_UNUSED(reason);
	ARG_UNUSED(esf);

	LOG_PANIC();

	struct k_thread *thread = IS_ENABLED(CONFIG_MULTITHREADING) ?
		k_current_get() : NULL;
	/* Halt the system if this is not a user thread. */
	if (thread == NULL || (thread->base.user_options & K_USER) == 0) {
		LOG_ERR("Halting system");
		ulong_t mcause;
#ifndef CONFIG_SUPERVISOR_MODE
		mcause = csr_read(mcause);
#else
		mcause = csr_read(scause);
#endif
		cmrt_eac_set_boot_status(mcause, 0);
		cmrt_eac_halt(0, -EINTR, -EFAULT);
		CODE_UNREACHABLE;
	}
}
