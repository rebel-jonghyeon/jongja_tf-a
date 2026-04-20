#include <ipm_samsung.h>
#include <drivers/cmrt/sac.h>
#include <rebel_h.h>
#include "test_main.h"

LOG_MODULE_DECLARE(test_mailbox, CONFIG_CMRT_LOG_LEVEL);

struct test_data {
	char str[10];
	int size;
	int channel;
	int index;
};

struct test_data arr[] = {
	{"ZERO", 4, 1, 1},
	{"A", 1, 5, 5},
	{"BB", 2, 10, 10},
	{"CCC", 3, 16, 16},
	{"DDDD", 4, 30, 31},
	{"EEEEE", 5, 24, 32},
	{"FFFFFF", 6, 22, 34},
	{"GGGGGGG", 7, 11, 60},
};

static void test_cb(const struct device *ipmdev, const int chan)
{
	struct ipm_samsung_api *api = (struct ipm_samsung_api *)ipmdev->api;
	char data[10] = {0};

	api->receive(ipmdev, data, arr[chan].size, arr[chan].index);

	LOG_INF("========integrated test start=========\n");

	test_external_ip(chan);

	LOG_INF("========integrated test done=========\n");
	LOG_INF("integrated test list:\n");
	LOG_INF("\t test_mailbox\n");
}

void register_test_cb(void)
{
	const struct device *d = device_get_binding("MAILBOX_M0");
	struct ipm_samsung_api *api = (struct ipm_samsung_api *)d->api;

	LOG_INF("%s(%s) ", __func__, "MAILBOX_M0");
	api->register_callback(d, test_cb);
}

void cb(const struct device *ipmdev, const int chan)
{
	char data[10] = {0};

	struct ipm_samsung_api *api = (struct ipm_samsung_api *)ipmdev->api;

	LOG_INF("Enter %s chan: %d\n", __func__, chan);
	api->receive(ipmdev, data, arr[chan].size, arr[chan].index);

	for (int i = 0; i < arr[chan].size; ++i) {
		printf("%c", data[i]);
	}
	LOG_INF("\n");
}

int test_mailbox_loopback(const char *label, int chan, int cpu)
{
	const struct device *d = device_get_binding(label);
	uint32_t target_id = get_chiplet_id();

	if (!d) {
		LOG_INF("Missing %s ------------- %s", label, __func__);
		return -ENXIO;
	}

	struct ipm_samsung_api *api = (struct ipm_samsung_api *)d->api;

	if (!api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d, __func__);
		return -EFAULT;
	}

	LOG_INF("\n%s(%s) ", __func__, label);
	api->register_callback(d, cb);
	api->write(d, target_id, arr[chan].str, arr[chan].size, arr[chan].index);
	api->send(d, target_id, chan, cpu);

	return 0;
}

int test_mailbox_inter_chiplet(const char *label, uint32_t target_id, int chan, int cpu)
{
	const struct device *d = device_get_binding(label);

	if (!d) {
		LOG_INF("Missing %s ------------- %s", label, __func__);
		return -ENXIO;
	}

	struct ipm_samsung_api *api = (struct ipm_samsung_api *)d->api;

	if (!api) {
		LOG_INF("Missing %s api %p------------- %s", label, &d, __func__);
		return -EFAULT;
	}

	LOG_INF("\n%s(%s) ", __func__, label);
	api->register_callback(d, cb);
	api->write(d, target_id, arr[chan].str, arr[chan].size, arr[chan].index);
	api->send(d, target_id, chan, cpu);

	return 0;
}

int test_mailbox(void)
{
	uint32_t chiplet_cnt = get_chiplet_cnt();

	test_mailbox_loopback("MAILBOX_M0", 0, CPU0);
	test_mailbox_loopback("MAILBOX_M1", 1, CPU0);
	test_mailbox_loopback("MAILBOX_M2", 2, CPU0);
	test_mailbox_loopback("MAILBOX_P0_M5", 3, CPU0);
	test_mailbox_loopback("MAILBOX_P0_M6", 4, CPU0);
	test_mailbox_loopback("MAILBOX_P1_M5_0", 5, CPU0);
	test_mailbox_loopback("MAILBOX_P1_M5_1", 6, CPU0);
	test_mailbox_loopback("MAILBOX_P1_M6_0", 7, CPU0);
	test_mailbox_loopback("MAILBOX_P1_M6_1", 8, CPU0);

	switch (get_chiplet_id()) {
	case 0:	/* from C0_ROT */
		for (int i = 0; i < chiplet_cnt; i++) {
			test_mailbox_inter_chiplet("MAILBOX_P1_M5_0", i, 0, CPU0);
		}
		break;
	case 1: /* from C1_ROT */
		for (int i = 0; i < chiplet_cnt; i++) {
			test_mailbox_inter_chiplet("MAILBOX_P1_M5_1", i, 0, CPU1);
		}
		break;
	case 2: /* from C2_ROT */
		for (int i = 0; i < chiplet_cnt; i++) {
			test_mailbox_inter_chiplet("MAILBOX_P1_M6_0", i, 0, CPU0);
		}
		break;
	case 3: /* from C3_ROT */
		for (int i = 0; i < chiplet_cnt; i++) {
			test_mailbox_inter_chiplet("MAILBOX_P1_M6_1", i, 0, CPU1);
		}
		break;
	default:
		break;
	}

	return 0;
}
