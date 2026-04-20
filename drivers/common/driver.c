#include <driver.h>
#include "assert.h"

/* TODO: Refactoring */

extern struct init_entry start_init_func[];
extern struct init_entry end_init_func[];

void init_drivers_by_calling_init_entry(void)
{
	struct init_entry *entry = start_init_func;

	int i;
	int ret;

	for (i = 0; &entry[i] < end_init_func; ++i) {

		if (!entry[i].init) {
			printf("ERROR!! Priority %d, NULL init func!!\r\n", i);
			assert_with_message(__FILE__, __LINE__);
		}

		ret = entry[i].init();
		if (ret != 0) {
			printf("ERROR!! Priority %d, Init failed!! Reason: %d\r\n", i, ret);
			assert_with_message(__FILE__, __LINE__);
		}
	}
}
