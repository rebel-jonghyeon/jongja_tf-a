#include "test_main.h"
#include "test_mailbox.h"
#include "test_pvt_con.h"
#include "test_crypto.h"
#include "test_qspi.h"
#include "test_otp.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(test_crypto, CONFIG_CMRT_LOG_LEVEL);
#include <zephyr.h>

struct k_thread thread_data1;
struct k_thread thread_data2;
static K_KERNEL_STACK_DEFINE(stack_area1, 8192);
static K_KERNEL_STACK_DEFINE(stack_area2, 8192);

#define PRIORITY	(5)
int test_external_ip(int chan)
{
	int res = 0;

/* TODO:
 * testing pvt code stays in irq.
 * need to fix
 *
 *	res = test_pvt_con();
 */

	LOG_INF("test_external_ip is called, chan : %d", chan);

	if (chan == 31) {
		res += test_otp_main();
	}

	if (chan == 5) {
		k_thread_create(&thread_data1, stack_area1,
						K_THREAD_STACK_SIZEOF(stack_area1),
						test_crypto_hc_ec, NULL, NULL, NULL,
						PRIORITY, 0, K_NO_WAIT);
		k_thread_create(&thread_data2, stack_area2,
						K_THREAD_STACK_SIZEOF(stack_area2),
						test_crypto_aes, NULL, NULL, NULL,
						PRIORITY, 0, K_NO_WAIT);
	}

	if (chan == 0) {
		res += test_qspi();
	}

	return res;
}
