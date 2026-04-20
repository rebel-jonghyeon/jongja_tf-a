#ifndef __IO_H
#define __IO_H

#include "cpu.h"

typedef uint64_t            mem_addr_t;

static inline uint8_t sys_read8(mem_addr_t addr)
{
    uint8_t val;

    __asm__ volatile("ldrb %w0, [%1]" : "=r" (val) : "r" (addr));

    __DMB();
    return val;
}

static inline void sys_write8(uint8_t data, mem_addr_t addr)
{
    __DMB();
    __asm__ volatile("strb %w0, [%1]" : : "r" (data), "r" (addr));
}

static inline uint16_t sys_read16(mem_addr_t addr)
{
    uint16_t val;

    __asm__ volatile("ldrh %w0, [%1]" : "=r" (val) : "r" (addr));

    __DMB();
    return val;
}

static inline void sys_write16(uint16_t data, mem_addr_t addr)
{
    __DMB();
    __asm__ volatile("strh %w0, [%1]" : : "r" (data), "r" (addr));
}

static inline uint32_t sys_read32(mem_addr_t addr)
{
    uint32_t val;

    __asm__ volatile("ldr %w0, [%1]" : "=r" (val) : "r" (addr));

    __DMB();
    return val;
}

static inline void sys_write32(uint32_t data, mem_addr_t addr)
{
    __DMB();
    __asm__ volatile("str %w0, [%1]" : : "r" (data), "r" (addr));
}

static inline uint64_t sys_read64(mem_addr_t addr)
{
    uint64_t val;

    __asm__ volatile("ldr %x0, [%1]" : "=r" (val) : "r" (addr));

    __DMB();
    return val;
}

static inline void sys_write64(uint64_t data, mem_addr_t addr)
{
    __DMB();
    __asm__ volatile("str %x0, [%1]" : : "r" (data), "r" (addr));
}

#endif  /* __IO_H */
