#pragma once

#include <stdint.h>
#include <cmsis_gcc.h>

/* Memory mapped registers I/O functions */

typedef uintptr_t mem_addr_t;

__STATIC_FORCEINLINE uint8_t sys_read8(mem_addr_t addr)
{
    uint8_t val = *(volatile uint8_t *)addr;

    __DMB();
    return val;
}

__STATIC_FORCEINLINE void sys_write8(uint8_t data, mem_addr_t addr)
{
    __DMB();
    *(volatile uint8_t *)addr = data;
}

__STATIC_FORCEINLINE uint16_t sys_read16(mem_addr_t addr)
{
    uint16_t val = *(volatile uint16_t *)addr;

    __DMB();
    return val;
}

__STATIC_FORCEINLINE void sys_write16(uint16_t data, mem_addr_t addr)
{
    __DMB();
    *(volatile uint16_t *)addr = data;
}

__STATIC_FORCEINLINE uint32_t sys_read32(mem_addr_t addr)
{
    uint32_t val = *(volatile uint32_t *)addr;

    __DMB();
    return val;
}

__STATIC_FORCEINLINE void sys_write32(uint32_t data, mem_addr_t addr)
{
    __DMB();
    *(volatile uint32_t *)addr = data;
}
