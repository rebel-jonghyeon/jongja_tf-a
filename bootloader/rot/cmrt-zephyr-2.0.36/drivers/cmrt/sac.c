/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_sac

#include <device.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <sys/__assert.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/sac.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_SAC_BASE); /* device tree must match headers */
#define CMRT_SAC_NUM_SEGMENTS DT_INST_PROP(0, num_segments)
#define CMRT_SAC_SEGMENT0_DEFAULT DT_INST_PROP(0, segment0_default)

__weak bool cmrt_sac_has_access(const k_tid_t thread, uint64_t addr, size_t size, bool write)
{
	ARG_UNUSED(thread);
	ARG_UNUSED(addr);
	ARG_UNUSED(size);
	ARG_UNUSED(write);
	return true;
}

#ifndef CONFIG_SUPERVISOR_MODE
static inline uint32_t sac_status(void)
{
	uint32_t status = cmrt_core_status(R_BASE);
	return status & HWC_STATUS_STATUS_MASK;
}

int cmrt_sac_set_config(uint32_t value, uint32_t index)
{
	if (index >= CMRT_SAC_NUM_SEGMENTS) {
		return -EINVAL;
	}

	sys_write32(value, (mm_reg_t)(R_BASE+R_SEGMENT_CONFIG_0 +
				      index * (sizeof(uint32_t) * 2u)));

	return sac_status() != 0u ? -EIO : 0;
}
#endif

int cmrt_sac_set_base(k_tid_t thread, uint64_t base)
{
	ARG_UNUSED(thread);
	ARG_UNUSED(base);
	return 0;
}

uint64_t cmrt_sac_get_base(k_tid_t thread)
{
	ARG_UNUSED(thread);
	return SAC_MEMORY_BASE;
}

uint8_t z_impl_cmrt_sac_read8(uintptr_t addr)
{
	return sys_read8(addr);
}

void z_impl_cmrt_sac_write8(uint8_t data, uintptr_t addr)
{
	sys_write8(data, addr);
}

uint32_t z_impl_cmrt_sac_read32(uintptr_t addr)
{
	return sys_read32(addr);
}

void z_impl_cmrt_sac_write32(uint32_t data, uintptr_t addr)
{
	sys_write32(data, addr);
}

void *z_impl_cmrt_sac_memcpy(void *dst, const void *src, size_t num)
{
	return memcpy(dst, src, num);
}

void cmrt_sac_init_early(void)
{
	/* Set fixed segment config here for DMAC to work later on. */
#if CMRT_SAC_NUM_SEGMENTS > 0
	sys_write32(CMRT_SAC_SEGMENT0_DEFAULT, (mm_reg_t)(R_BASE+R_SEGMENT_CONFIG_0));
#endif
}

#if CMRT_SAC_NUM_SEGMENTS > 0
static int cmrt_sac_init(const struct device *dev)
{
	ARG_UNUSED(dev);
#ifndef CONFIG_SUPERVISOR_MODE
	cmrt_sac_init_early();
#endif
	return 0;
}
SYS_INIT(cmrt_sac_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
#endif

#ifdef CONFIG_CMRT_SAC_CONSOLE
/* Console buffers are at the end of the FPGA SAC memory. */
#ifdef CONFIG_SUPERVISOR_MODE
#define SAC_CONSOLE_BUFFER_BASE (SAC_MEMORY_BASE + CONFIG_FPGA_EXTMEM_SIZE - 2 * CONFIG_RAM_CONSOLE_BUFFER_SIZE)
#else
#define SAC_CONSOLE_BUFFER_BASE (SAC_MEMORY_BASE + CONFIG_FPGA_EXTMEM_SIZE - CONFIG_RAM_CONSOLE_BUFFER_SIZE)
#endif

int cmrt_sac_set_console_base(uint64_t base)
{
	ARG_UNUSED(base);
	return 0;
}

uint64_t cmrt_sac_get_console_base(void)
{
	return SAC_MEMORY_BASE;
}

extern void ram_console_copy(void *buffer);
void cmrt_sac_console_copy(void)
{
	unsigned int key = irq_lock();
	ram_console_copy((void *)(uintptr_t)SAC_CONSOLE_BUFFER_BASE);
	irq_unlock(key);
}
#endif

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline uint32_t z_vrfy_cmrt_sac_read32(mem_addr_t addr)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(addr, sizeof(uint32_t)));
	return z_impl_cmrt_sac_read32(addr);
}
#include <syscalls/cmrt_sac_read32_mrsh.c>

static inline void z_vrfy_cmrt_sac_write32(uint32_t data, mem_addr_t addr)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(addr, sizeof(uint32_t)));
	return z_impl_cmrt_sac_write32(data, addr);
}
#include <syscalls/cmrt_sac_write32_mrsh.c>

static inline void *z_vrfy_cmrt_sac_memcpy(void *dst, const void *src, size_t num)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(dst, num));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(src, num));
	return z_impl_cmrt_sac_memcpy(dst, src, num);
}
#include <syscalls/cmrt_sac_memcpy_mrsh.c>

#endif /* CONFIG_USERSPACE */
