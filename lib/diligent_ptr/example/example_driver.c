#include "example_driver.h"
#include "diligent_ptr.h"
#include <stdio.h>

#define USE_DILIGENT_PTR	//It's just for the example. It must be replaced with -D flag.
#ifdef USE_DILIGENT_PTR
	struct diligent_ptr < struct mmio_map > sfr_regs;
#else
	struct mmio_map *sfr_regs;
#endif

int driver_init(void *base_addr)
{
	sfr_regs = (struct mmio_map *)base_addr;

	return 0;
}

int driver_func(void)
{
	printf("%d\n", sfr_regs->a.aaa);
	sfr_regs->b.bb = 1;
	sfr_regs->c.ccc = 2;
	printf("%d %d\n", sfr_regs->b.bb, sfr_regs->c.ccc);

	return 0;
}
