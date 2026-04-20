#pragma once

#include <stdint.h>
#include <drivers/cmrt/sac.h>

#define SAC_BASE	(0x60000U)

void sac_set_config(uint32_t value);
void sboot_sac_write8(uint8_t val, uintptr_t addr);
uint8_t sboot_sac_read8(uintptr_t addr);
uint32_t sboot_sac_read32(uintptr_t addr);
