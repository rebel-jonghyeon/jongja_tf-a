/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <kernel.h>
#include <drivers/cmrt/fboot.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/dd.h>
#include <cmrt/fboot/syscall_ids.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

int fboot_load_image(void *blob, size_t size, cmrt_raw_footer_t *raw, cmrt_usr_footer_t *usr)
{
    return arch_syscall_invoke4((uintptr_t)blob, (uintptr_t)size, (uintptr_t)raw, (uintptr_t)usr, (uintptr_t)FBOOT_SYSCALL_LOAD_IMAGE);
}

int z_impl_fboot_create_root(int index, const cmrt_omc_root_t *new_root)
{
	return arch_syscall_invoke2((uintptr_t)index, (uintptr_t)new_root, (uintptr_t)FBOOT_SYSCALL_CREATE_ROOT);
}

int z_impl_fboot_obliterate_root(int index)
{
	return arch_syscall_invoke1((uintptr_t)index, (uintptr_t)FBOOT_SYSCALL_OBLITERATE_ROOT);
}

int z_impl_fboot_halt(int major, int minor)
{
#ifdef CONFIG_CMRT_SAC_CONSOLE
	cmrt_sac_console_copy();
#endif
	return arch_syscall_invoke2((uintptr_t)major, (uintptr_t)minor, (uintptr_t)FBOOT_SYSCALL_HALT);
}

int z_impl_fboot_reboot(void)
{
#ifdef CONFIG_CMRT_SAC_CONSOLE
	cmrt_sac_console_copy();
#endif
	return arch_syscall_invoke0((uintptr_t)FBOOT_SYSCALL_REBOOT);
}

int z_impl_fboot_reset(uint32_t info)
{
#ifdef CONFIG_CMRT_SAC_CONSOLE
	cmrt_sac_console_copy();
#endif
	return arch_syscall_invoke1((uintptr_t)info, (uintptr_t)FBOOT_SYSCALL_RESET);
}

int z_impl_fboot_reset_info(uint32_t *info)
{
	return arch_syscall_invoke1((uintptr_t)info, (uintptr_t)FBOOT_SYSCALL_RESET_INFO);
}

int z_impl_fboot_get_image_version(enum cmrt_image_version_id image, void *version, size_t *size)
{
	return arch_syscall_invoke3((uintptr_t)image, (uintptr_t)version, (uintptr_t)size, (uintptr_t)FBOOT_SYSCALL_GET_IMAGE_VERSION);
}

int z_impl_fboot_get_enforced_version(enum cmrt_enforced_version_id image, uint32_t *version)
{
	return arch_syscall_invoke2((uintptr_t)image, (uintptr_t)version, (uintptr_t)FBOOT_SYSCALL_GET_ENFORCED_VERSION);
}

int z_impl_fboot_set_enforced_version(enum cmrt_enforced_version_id image, uint32_t version)
{
	return arch_syscall_invoke2((uintptr_t)image, (uintptr_t)version, (uintptr_t)FBOOT_SYSCALL_SET_ENFORCED_VERSION);
}

int fboot_prepare_boot_bypass(const void *stack, const void *function)
{
	return arch_syscall_invoke2((uintptr_t)stack, (uintptr_t)function, (uintptr_t)FBOOT_SYSCALL_PREPARE_BOOT_BYPASS);
}

int z_impl_fboot_data_store_read(const void *name, size_t namelen, void *data, size_t *datalen, bool user)
{
	return arch_syscall_invoke5((uintptr_t)name, (uintptr_t)namelen, (uintptr_t)data, (uintptr_t)datalen, (uintptr_t)user, (uintptr_t)FBOOT_SYSCALL_DATA_STORE_READ);
}

int z_impl_fboot_data_store_write(const void *name, size_t namelen, const void *data, size_t datalen, bool user)
{
	return arch_syscall_invoke5((uintptr_t)name, (uintptr_t)namelen, (uintptr_t)data, (uintptr_t)datalen, (uintptr_t)user, (uintptr_t)FBOOT_SYSCALL_DATA_STORE_WRITE);
}

int z_impl_fboot_data_store_grant(const void *name, size_t namelen, uint32_t attributes, int index, bool user)
{
	return arch_syscall_invoke5((uintptr_t)name, (uintptr_t)namelen, (uintptr_t)attributes, (uintptr_t)index, (uintptr_t)user, (uintptr_t)FBOOT_SYSCALL_DATA_STORE_GRANT);
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline int z_vrfy_fboot_create_root(int index, const cmrt_omc_root_t *new_root)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(new_root, sizeof(cmrt_omc_root_t)));
	return z_impl_fboot_create_root(index, new_root);
}
#include <syscalls/fboot_create_root_mrsh.c>

static inline int z_vrfy_fboot_obliterate_root(int index)
{
	return z_impl_fboot_obliterate_root(index);
}
#include <syscalls/fboot_obliterate_root_mrsh.c>

static inline int z_vrfy_fboot_halt(int major, int minor)
{
	return z_impl_fboot_halt(major, minor);
}
#include <syscalls/fboot_halt_mrsh.c>

static inline int z_vrfy_fboot_reboot(void)
{
	return z_impl_fboot_reboot();
}
#include <syscalls/fboot_reboot_mrsh.c>

static inline int z_vrfy_fboot_reset(uint32_t info)
{
	return z_impl_fboot_reset(info);
}
#include <syscalls/fboot_reset_mrsh.c>

static inline int z_vrfy_fboot_get_image_version(enum cmrt_image_version_id image, void *version, size_t *size)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(size, sizeof(size_t)));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(version, *size));
	return z_impl_fboot_get_image_version(image, version, size);
}
#include <syscalls/fboot_get_image_version_mrsh.c>

static inline int z_vrfy_fboot_get_enforced_version(enum cmrt_enforced_version_id image, uint32_t *version)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(version, sizeof(uint32_t)));
	return z_impl_fboot_get_enforced_version(image, version);
}
#include <syscalls/fboot_get_enforced_version_mrsh.c>

static inline int z_vrfy_fboot_set_enforced_version(enum cmrt_enforced_version_id image, uint32_t version)
{
	return z_impl_fboot_set_enforced_version(image, version);
}
#include <syscalls/fboot_set_enforced_version_mrsh.c>

static inline int z_vrfy_fboot_data_store_read(const void *name, size_t namelen, void *data, size_t *datalen, bool user)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(name, namelen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(datalen, sizeof(size_t)));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(data, *datalen));
	ARG_UNUSED(user); /* forced to true */
	return z_impl_fboot_data_store_read(name, namelen, data, datalen, true);
}
#include <syscalls/fboot_data_store_read_mrsh.c>

static inline int z_vrfy_fboot_data_store_write(const void *name, size_t namelen, const void *data, size_t datalen, bool user)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(name, namelen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(data, datalen));
	ARG_UNUSED(user); /* forced to true */
	return z_impl_fboot_data_store_write(name, namelen, data, datalen, true);
}
#include <syscalls/fboot_data_store_write_mrsh.c>

static inline int z_vrfy_fboot_data_store_grant(const void *name, size_t namelen, uint32_t attributes, int index, bool user)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(name, namelen));
	ARG_UNUSED(user); /* forced to true */
	return z_impl_fboot_data_store_grant(name, namelen, attributes, index, true);
}
#include <syscalls/fboot_data_store_grant_mrsh.c>

#endif /* CONFIG_USERSPACE */
