#include <stdint.h>
#include <drivers/cmrt/sac_reg.h>
#include "sac_custom.h"

void sac_set_config(uint32_t value)
{
	sys_write32(value, (mm_reg_t)(SAC_BASE + R_SAC_EXT_ADDR_WIDTH_HI));
}

void sboot_sac_write8(uint8_t data, uintptr_t addr)
{
	if (is_sac_ptr(addr)) {
		uint64_t real = cmrt_sac_translate(addr);
		uint32_t cpu_addr_hi = (uint32_t)(real >> 32);
		uint32_t cpu_addr_lo = (uint32_t)real & CPU_ADDR_LO_MASK;
		uint32_t offset = (uint32_t)real & ~CPU_ADDR_LO_MASK;
		uint32_t aligned_offset = offset & (~FOUR_BYTE_ALIGN_MASK);
		unsigned int key = irq_lock();
		/* Save current base. */
		uint32_t cur_addr_hi = sys_read32((mm_reg_t)(SAC_BASE + R_CPU_ADDR_HI));
		uint32_t cur_addr_lo = sys_read32((mm_reg_t)(SAC_BASE + R_CPU_ADDR_LO));
		/* Set new base and write data. */
		sys_write32(cpu_addr_hi, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_HI));
		sys_write32(cpu_addr_lo, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_LO));

		uint32_t value = sys_read32((mm_reg_t)(SAC_BASE + R_CPU_DATA + aligned_offset));

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

		sys_write32(value, (mm_reg_t)(SAC_BASE + R_CPU_DATA + aligned_offset));
		/* Reset current base. */
		sys_write32(cur_addr_hi, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_HI));
		sys_write32(cur_addr_lo, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_LO));
		irq_unlock(key);
		return;
	}
	sys_write8(data, addr);
}

uint8_t sboot_sac_read8(uintptr_t addr)
{
	if (is_sac_ptr(addr)) {
		uint64_t real = cmrt_sac_translate(addr);
		uint32_t cpu_addr_hi = (uint32_t)(real >> 32);
		uint32_t cpu_addr_lo = (uint32_t)real & CPU_ADDR_LO_MASK;
		uint32_t offset = (uint32_t)real & ~CPU_ADDR_LO_MASK;
		uint32_t aligned_offset = offset & (~FOUR_BYTE_ALIGN_MASK);
		unsigned int key = irq_lock();
		/* Save current base. */
		uint32_t cur_addr_hi = sys_read32((mm_reg_t)(SAC_BASE + R_CPU_ADDR_HI));
		uint32_t cur_addr_lo = sys_read32((mm_reg_t)(SAC_BASE + R_CPU_ADDR_LO));
		/* Set new base and read data. */
		sys_write32(cpu_addr_hi, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_HI));
		sys_write32(cpu_addr_lo, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_LO));
		uint32_t data = sys_read32((mm_reg_t)(SAC_BASE + R_CPU_DATA + aligned_offset));
		/* Reset current base. */
		sys_write32(cur_addr_hi, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_HI));
		sys_write32(cur_addr_lo, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_LO));
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

uint32_t sboot_sac_read32(uintptr_t addr)
{
	if (is_sac_ptr(addr)) {
		/* Unaligned address will trap! */
		uint64_t real = cmrt_sac_translate(addr);
		uint32_t cpu_addr_hi = (uint32_t)(real >> 32);
		uint32_t cpu_addr_lo = (uint32_t)real & CPU_ADDR_LO_MASK;
		uint32_t offset = (uint32_t)real & ~CPU_ADDR_LO_MASK;
		unsigned int key = irq_lock();
		/* Save current base. */
		uint32_t cur_addr_hi = sys_read32((mm_reg_t)(SAC_BASE + R_CPU_ADDR_HI));
		uint32_t cur_addr_lo = sys_read32((mm_reg_t)(SAC_BASE + R_CPU_ADDR_LO));
		/* Set new base and read data. */
		sys_write32(cpu_addr_hi, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_HI));
		sys_write32(cpu_addr_lo, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_LO));
		uint32_t data = sys_read32((mm_reg_t)(SAC_BASE + R_CPU_DATA + offset));
		/* Reset current base. */
		sys_write32(cur_addr_hi, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_HI));
		sys_write32(cur_addr_lo, (mm_reg_t)(SAC_BASE + R_CPU_ADDR_LO));
		irq_unlock(key);
		return data;
	}
	return sys_read32(addr);
}
