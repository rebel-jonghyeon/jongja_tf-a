#pragma once

#include "dma_reg.h"

int sboot_dma_init(void);

void sboot_dma_config(struct dma_block_config *dma_block_cfg);
void sboot_dma_xfer_done(void);
int sboot_dma_start(void);
