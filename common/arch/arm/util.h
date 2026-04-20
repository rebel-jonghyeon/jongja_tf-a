#pragma once

#include <stdint.h>

#ifndef BIT
#define BIT(n)  (1UL << (n))
#endif
#define BIT_MASK(n) (BIT(n) - 1UL)

static inline void sys_set_bit(uint32_t addr, unsigned int bit)
{
    uint32_t temp = *(volatile uint32_t *)addr;

    *(volatile uint32_t *)addr = temp | (1 << bit);
}

static inline void sys_clear_bit(uint32_t addr, unsigned int bit)
{
    uint32_t temp = *(volatile uint32_t *)addr;

    *(volatile uint32_t *)addr = temp & ~(1 << bit);
}

static inline int sys_test_bit(uint32_t addr, unsigned int bit)
{
    uint32_t temp = *(volatile uint32_t *)addr;

    return temp & (1 << bit);
}

static inline void sys_bitfield_set_bit(uint32_t addr, unsigned int bit)
{
    sys_set_bit(addr + ((bit >> 5) << 2), bit & 0x1F);
}

static inline void sys_bitfield_clear_bit(uint32_t addr, unsigned int bit)
{
    sys_clear_bit(addr + ((bit >> 5) << 2), bit & 0x1F);
}

static inline int sys_bitfield_test_bit(uint32_t addr, unsigned int bit)
{
    return sys_test_bit(addr + ((bit >> 5) << 2), bit & 0x1F);
}

static inline int sys_test_and_set_bit(uint32_t addr, unsigned int bit)
{
    int ret;

    ret = sys_test_bit(addr, bit);
    sys_set_bit(addr, bit);

    return ret;
}

static inline int sys_test_and_clear_bit(uint32_t addr, unsigned int bit)
{
    int ret;

    ret = sys_test_bit(addr, bit);
    sys_clear_bit(addr, bit);

    return ret;
}

static inline int sys_bitfield_test_and_set_bit(uint32_t addr, unsigned int bit)
{
    int ret;

    ret = sys_bitfield_test_bit(addr, bit);
    sys_bitfield_set_bit(addr, bit);

    return ret;
}

static inline int sys_bitfield_test_and_clear_bit(uint32_t addr, unsigned int bit)
{
    int ret;

    ret = sys_bitfield_test_bit(addr, bit);
    sys_bitfield_clear_bit(addr, bit);

    return ret;
}
