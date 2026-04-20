#include <drivers/cmrt/sac.h>
#include <rebel_h.h>
#include "qspi.h"
#include "test_main.h"

LOG_MODULE_DECLARE(test_qspi, CONFIG_CMRT_LOG_LEVEL);

int test_qspi(void)
{
	const struct device *d = device_get_binding("QSPI");
	struct qspi_samsung_api *api = (struct qspi_samsung_api *)d->api;

	LOG_INF("%s(%s)\n", __func__, "QSPI");

	static uint32_t data[1024] = {0};
	static uint32_t diff_data[1024] = {0};

	api->read(d, NOR_CMD_QAUD_IO_WORD_READ, 0, (void *)&data, 4096);
	api->erase(d, ERASE_4KB_COMMAND, 0);

	for (int i = 0; i < 16; i++) {
		api->write(d, PROGRAM_COMMAND, i * 256, (void *)&data[i * 64], 256);
	}

	api->read(d, NOR_CMD_QAUD_IO_WORD_READ, 0, (void *)&diff_data, 4096);

	uint32_t cnt = 0;

	for (int j = 0; j < 1024; j++) {
		if (data[j] == diff_data[j])
			cnt++;
		else
			LOG_INF("index: %d, data: %x, diff_data: %x\n", j, data[j], diff_data[j]);
	}

	LOG_INF("qspi test success cnt: %d\n", cnt);

	return 0;
}
