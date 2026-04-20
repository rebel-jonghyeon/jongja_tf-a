/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_sac2

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
	if (index > 0) {
		return -EINVAL;
	}

	sys_write32(value, (mm_reg_t)(R_BASE + R_SAC_EXT_ADDR_WIDTH_HI));

	return sac_status() != 0u ? -EIO : 0;
}
#endif

#ifndef CONFIG_MULTITHREADING
static uint64_t sac_cpu_base;
#endif

int cmrt_sac_set_base(k_tid_t thread, uint64_t base)
{
	if ((base & ~CPU_ADDR_LO_MASK) != 0) {
		/* Base must be aligned to 2K boundary. */
		return -EINVAL;
	}
	if (thread == NULL) {
		thread = K_CURRENT_GET();
	}
	unsigned int key = irq_lock();
#ifdef CONFIG_MULTITHREADING
	thread->sac_cpu_base = base;
#else
	sac_cpu_base = base;
#endif
	sys_write32(base >> 32, (mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
	sys_write32(base & CPU_ADDR_LO_MASK, (mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
	irq_unlock(key);
	return 0;
}

uint64_t cmrt_sac_get_base(k_tid_t thread)
{
#ifdef CONFIG_MULTITHREADING
	if (thread == NULL) {
		thread = K_CURRENT_GET();
	}
	return thread->sac_cpu_base;
#else
	ARG_UNUSED(thread);
	return sac_cpu_base;
#endif
}

uint8_t z_impl_cmrt_sac_read8(uintptr_t addr)
{
	if (is_sac_ptr(addr)) {
		uint64_t real = cmrt_sac_translate(addr);            // addr
		uint32_t cpu_addr_hi = (uint32_t)(real >> 32);           // hi
		uint32_t cpu_addr_lo = (uint32_t)real & CPU_ADDR_LO_MASK; // lo
		uint32_t offset = (uint32_t)real & ~CPU_ADDR_LO_MASK;    // al  // 7ff
		uint32_t aligned_offset = offset & (~FOUR_BYTE_ALIGN_MASK);
		unsigned int key = irq_lock();
		/* Save current base. */
		uint32_t cur_addr_hi = sys_read32((mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		uint32_t cur_addr_lo = sys_read32((mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		/* Set new base and read data. */
		sys_write32(cpu_addr_hi, (mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		sys_write32(cpu_addr_lo, (mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		uint32_t data = sys_read32((mm_reg_t)(R_BASE + R_CPU_DATA + aligned_offset));
		/* Reset current base. */
		sys_write32(cur_addr_hi, (mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		sys_write32(cur_addr_lo, (mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		irq_unlock(key);

		uint8_t res = 0;

		if ((offset & FOUR_BYTE_ALIGN_MASK) == 0x0)
			res = data & 0xff;
		else if ((offset & FOUR_BYTE_ALIGN_MASK) == 0x1)
			res = (data >> 8) & 0xff;
		else if ((offset & FOUR_BYTE_ALIGN_MASK) == 0x2)
			res = (data >> 16) & 0xff;
		else if ((offset & FOUR_BYTE_ALIGN_MASK) == 0x3)
			res = (data >> 24) & 0xff;

		return res;
	}
	return sys_read8(addr);
}

void z_impl_cmrt_sac_write8(uint8_t data, uintptr_t addr)
{
	if (is_sac_ptr(addr)) {
		uint64_t real = cmrt_sac_translate(addr);
		uint32_t cpu_addr_hi = (uint32_t)(real >> 32);
		uint32_t cpu_addr_lo = (uint32_t)real & CPU_ADDR_LO_MASK;
		uint32_t offset = (uint32_t)real & ~CPU_ADDR_LO_MASK;
		uint32_t aligned_offset = offset & (~FOUR_BYTE_ALIGN_MASK);
		unsigned int key = irq_lock();
		/* Save current base. */
		uint32_t cur_addr_hi = sys_read32((mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		uint32_t cur_addr_lo = sys_read32((mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		/* Set new base and write data. */
		sys_write32(cpu_addr_hi, (mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		sys_write32(cpu_addr_lo, (mm_reg_t)(R_BASE + R_CPU_ADDR_LO));

		uint32_t value = sys_read32((mm_reg_t)(R_BASE + R_CPU_DATA + aligned_offset));

		if ((offset & FOUR_BYTE_ALIGN_MASK) == 0x0) {
			value &= ~BYTE_MASK;
			value |= data;
		} else if ((offset & FOUR_BYTE_ALIGN_MASK) == 0x1) {
			value &= ~(BYTE_MASK << 8);
			value |= (data << 8);
		} else if ((offset & FOUR_BYTE_ALIGN_MASK) == 0x2) {
			value &= ~(BYTE_MASK << 16);
			value |= (data << 16);
		} else if ((offset & FOUR_BYTE_ALIGN_MASK) == 0x3) {
			value &= ~(BYTE_MASK << 24);
			value |= (data << 24);
		}

		sys_write32(value, (mm_reg_t)(R_BASE + R_CPU_DATA + aligned_offset));
		/* Reset current base. */
		sys_write32(cur_addr_hi, (mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		sys_write32(cur_addr_lo, (mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		irq_unlock(key);
		return;
	}
	sys_write8(data, addr);
}

uint32_t z_impl_cmrt_sac_read32(uintptr_t addr)
{
	if (is_sac_ptr(addr)) {
		/* Unaligned address will trap! */
		uint64_t real = cmrt_sac_translate(addr);
		uint32_t cpu_addr_hi = (uint32_t)(real >> 32);
		uint32_t cpu_addr_lo = (uint32_t)real & CPU_ADDR_LO_MASK;
		uint32_t offset = (uint32_t)real & ~CPU_ADDR_LO_MASK;
		unsigned int key = irq_lock();
		/* Save current base. */
		uint32_t cur_addr_hi = sys_read32((mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		uint32_t cur_addr_lo = sys_read32((mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		/* Set new base and read data. */
		sys_write32(cpu_addr_hi, (mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		sys_write32(cpu_addr_lo, (mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		uint32_t data = sys_read32((mm_reg_t)(R_BASE + R_CPU_DATA + offset));
		/* Reset current base. */
		sys_write32(cur_addr_hi, (mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		sys_write32(cur_addr_lo, (mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		irq_unlock(key);
		return data;
	}
	return sys_read32(addr);
}

void z_impl_cmrt_sac_write32(uint32_t data, uintptr_t addr)
{
	if (is_sac_ptr(addr)) {
		/* Unaligned address will trap! */
		uint64_t real = cmrt_sac_translate(addr);
		uint32_t cpu_addr_hi = (uint32_t)(real >> 32);
		uint32_t cpu_addr_lo = (uint32_t)real & CPU_ADDR_LO_MASK;
		uint32_t offset = (uint32_t)real & ~CPU_ADDR_LO_MASK;
		unsigned int key = irq_lock();
		/* Save current base. */
		uint32_t cur_addr_hi = sys_read32((mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		uint32_t cur_addr_lo = sys_read32((mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		/* Set new base and write data. */
		sys_write32(cpu_addr_hi, (mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		sys_write32(cpu_addr_lo, (mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		sys_write32(data, (mm_reg_t)(R_BASE + R_CPU_DATA + offset));
		/* Reset current base. */
		sys_write32(cur_addr_hi, (mm_reg_t)(R_BASE + R_CPU_ADDR_HI));
		sys_write32(cur_addr_lo, (mm_reg_t)(R_BASE + R_CPU_ADDR_LO));
		irq_unlock(key);
		return;
	}
	sys_write32(data, addr);
}

void *z_impl_cmrt_sac_memcpy(void *dst, const void *src, size_t num)
{
	if (!is_sac_ptr((uintptr_t)dst) && !is_sac_ptr((uintptr_t)src)) {
		return memcpy(dst, src, num);
	}
	/* Copy also the last possibly uneven data as a full word. */
	uint32_t *d = (uint32_t *)dst;
	const uint32_t *s = (const uint32_t *)src;
	for (int i = (num + sizeof(uint32_t) - 1) >> 2; i > 0; i--) {
		uint32_t data = cmrt_read32(s++);
		cmrt_write32(data, d++);
	}
	return dst;
}

#ifdef CONFIG_CMRT_SAC_CONSOLE
/* Console buffers are at the end of the FPGA SAC memory. */
#ifdef CONFIG_SUPERVISOR_MODE
#define SAC_CONSOLE_BUFFER_BASE (SAC_MEMORY_BASE + CONFIG_FPGA_EXTMEM_SIZE - 2 * CONFIG_RAM_CONSOLE_BUFFER_SIZE)
#else
#define SAC_CONSOLE_BUFFER_BASE (SAC_MEMORY_BASE + CONFIG_FPGA_EXTMEM_SIZE - CONFIG_RAM_CONSOLE_BUFFER_SIZE)
#endif

static uint64_t sac_console_base;
int cmrt_sac_set_console_base(uint64_t base)
{
	if ((base & ~CPU_ADDR_LO_MASK) != 0) {
		/* Base must be aligned to 2K boundary. */
		return -EINVAL;
	}
	sac_console_base = base;
	return 0;
}

uint64_t cmrt_sac_get_console_base(void)
{
	return sac_console_base;
}

extern void ram_console_copy(void *buffer);
void cmrt_sac_console_copy(void)
{
	unsigned int key = irq_lock();
	uint64_t current_base = cmrt_sac_get_base(NULL);
	cmrt_sac_set_base(NULL, cmrt_sac_get_console_base());
	ram_console_copy((void *)(uintptr_t)SAC_CONSOLE_BUFFER_BASE);
	cmrt_sac_set_base(NULL, current_base);
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

static inline uint8_t z_vrfy_cmrt_sac_read8(mem_addr_t addr)
{
	Z_OOPS(Z_SYSCALL_MEMORY_READ(addr, sizeof(uint8_t)));
	return z_impl_cmrt_sac_read8(addr);
}

#include <syscalls/cmrt_sac_read8_mrsh.c>

static inline void z_vrfy_cmrt_sac_write8(uint8_t data, mem_addr_t addr)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(addr, sizeof(uint8_t)));
	return z_impl_cmrt_sac_write8(data, addr);
}

#include <syscalls/cmrt_sac_write8_mrsh.c>

#endif /* CONFIG_USERSPACE */
