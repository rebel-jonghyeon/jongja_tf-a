#include <stdint.h>
#include <cmrt/fboot/img_format.h>
#include "drivers/dma.h"

#define PHY0_APB2CR_PARA_PCIE		(0x1FF8200000ULL)
#define MUX_SWITCH					(0x404)
#define MUX_VALUE					(0x2)

#define TBOOT_P1_SRAM_MAX			(0x10000)
#define TBOOT_U_SRAM_MAX			(0x20000)
#define FOOTER_SIZE					(0x120)

#define DMAC_MAX_SIZE				(0x3FFFC)

int start_image(uint32_t img_type,
				int (*copy_image)(uint32_t img_type, uint32_t length,
								  struct dma_block_config img_info[]),
				struct dma_block_config img_info[],
				uint32_t (*fboot_supervisor_clear)(void),
				int (*fboot_supervisor_start)(void));
int img_footer_parse(void *blob, size_t size, cmrt_img_footer_t *footer);
