#pragma once

#include <stdint.h>
#include "dma_reg.h"

int dma_load(uint64_t src, uint64_t dst, uint32_t size);
