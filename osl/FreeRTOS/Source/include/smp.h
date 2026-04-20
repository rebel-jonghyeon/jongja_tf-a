#pragma once
#include <stdint.h>

#define SGI_IPI 0

void ipi_handler(void *data);
#if (configNUMBER_OF_CORES > 1)
void init_smp(void);
#endif
