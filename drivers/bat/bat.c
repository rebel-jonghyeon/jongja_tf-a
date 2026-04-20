#include "sys_io.h"
#include "bat.h"

void bat_set_page(uint32_t page_id, uint32_t src, uint64_t dst, uint32_t mask)
{
	uint32_t val;

	/* NOTE: To be sure, read-back the written value */
	WR_REG(BAT_PAGE_SRC(page_id), BAT_MASK(src));
	do {
		val = RD_REG(BAT_PAGE_SRC(page_id));
	} while (val != BAT_MASK(src));

	WR_REG(BAT_PAGE_DST(page_id), BAT_MASK(dst));
	do {
		val = RD_REG(BAT_PAGE_DST(page_id));
	} while (val != BAT_MASK(dst));

	WR_REG(BAT_PAGE_MASK(page_id), mask);
	do {
		val = RD_REG(BAT_PAGE_MASK(page_id));
	} while (val != mask);
}
