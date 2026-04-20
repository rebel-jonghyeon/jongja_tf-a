/*
 * Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <device.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/watchdog.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "../timer/cmrt_timer.h"

static volatile wdt_cmrt_t *wdt = WDT;

static void wdt_cmrt_enable(const struct device *dev)
{
	ARG_UNUSED(dev);
	wdt->watchdog_key = WATCHDOG_KEY_VALUE;
	wdt->watchdog_control |= WATCHDOG_CONTROL_WDEN;
}

static int wdt_cmrt_disable(const struct device *dev)
{
	ARG_UNUSED(dev);
	wdt->watchdog_key = WATCHDOG_KEY_VALUE;
	wdt->watchdog_control &= ~WATCHDOG_CONTROL_WDEN;
	return 0;
}

bool wdt_cmrt_ishungry(const struct device *dev, int channel_id)
{
	ARG_UNUSED(dev);

	/* Only a single channel (zero) is supported. */
	if (channel_id != 0) {
		return false;
	}

	/* Return 'yes' if we are over half way on the cycle. */
	return (wdt->watchdog_count << 1) > wdt->watchdog_compare;
}

int wdt_cmrt_feed(const struct device *dev, int channel_id)
{
	ARG_UNUSED(dev);

	/* Only a single channel (zero) is supported. */
	if (channel_id != 0) {
		return -EINVAL;
	}

	if ((wdt->watchdog_control & WATCHDOG_CONTROL_WDEN) != 0) {
		/* Feed only if the watchdog is running. */
		wdt->watchdog_key = WATCHDOG_KEY_VALUE;
		wdt->watchdog_feed = WATCHDOG_FEED_VALUE;
	}
	return 0;
}

static int wdt_cmrt_setup(const struct device *dev, uint8_t options)
{
	if ((wdt->watchdog_control & WATCHDOG_CONTROL_WDEN) != 0u) {
		return -EBUSY;
	}

	/* This is currently hardwired to 1, but let's have it in case
	 * the hardware changes and supports this feature.
	 */
	if ((options & WDT_OPT_PAUSE_IN_SLEEP) != 0u) {
		wdt->watchdog_key = WATCHDOG_KEY_VALUE;
		wdt->watchdog_control |= WATCHDOG_CONTROL_WDENACTIVE;
	}

	wdt_cmrt_enable(dev);
	return 0;
}

/* Maximal values for the prescaler, comparator and additional
 * comparator based on their mask values in timer_reg.h.
 */
#define WATCHDOG_WDSCALE_MAX WATCHDOG_CONTROL_WDSCALE_MASK
#define WATCHDOG_COMPARE_MAX WATCHDOG_COMPARE_MASK
#define WATCHDOG_COMPARE_ADD_MAX WATCHDOG_COMPARE_ADD_MASK

/* A safety net in case the mask doesn't only consist of continuous
 * low bits without gaps (in other words it should be a form of
 * 2^n-1).
 */
#define ASSERT_LSBCONT(n)					\
	static_assert(((n) & ((n) + 1)) == 0,			\
		      "bitmask " #n " is not LSB-continuous")

ASSERT_LSBCONT(WATCHDOG_WDSCALE_MAX);
ASSERT_LSBCONT(WATCHDOG_COMPARE_MAX);
ASSERT_LSBCONT(WATCHDOG_COMPARE_ADD_MAX);

static_assert(WATCHDOG_COMPARE_MAX < 65536, "WATCHDOG_COMPARE_MAX must fit into 16 bits");
static_assert(WATCHDOG_COMPARE_ADD_MAX < 65536, "WATCHDOG_COMPARE_ADD_MAX must fit into 16 bits");

static int wdt_cmrt_calc_prescaler(uint32_t timeout_ms, uint32_t freq,
				   uint16_t *pcmp, uint16_t *ppre)
{
	/* Timeout, in unit of cycles. */
	uint64_t timeout_cyc = (uint64_t)freq * timeout_ms / MSEC_PER_SEC;

	/* Find a prescaler value that brings the comparator under
	 * WATCHDOG_COMPARE_MAX.  The smaller the prescaler the better the
	 * resolution.
	 */
	for (uint16_t pre = 0; pre <= WATCHDOG_WDSCALE_MAX; ++pre) {
		if (timeout_cyc < WATCHDOG_COMPARE_MAX) {
			*pcmp = (uint16_t)timeout_cyc;
			*ppre = pre;
			return 0;
		}
		timeout_cyc >>= 1;
	}
	return -EINVAL;
}

static void wdt_cmrt_configure(uint16_t cmp, uint16_t add, uint16_t pre)
{
	wdt->watchdog_key = WATCHDOG_KEY_VALUE;
	wdt->watchdog_compare = cmp;

	wdt->watchdog_key = WATCHDOG_KEY_VALUE;
	wdt->watchdog_compare_add = add;

	wdt->watchdog_key = WATCHDOG_KEY_VALUE;
	wdt->watchdog_control = pre;
}

static int wdt_cmrt_install_timeout(const struct device *dev,
				    const struct wdt_timeout_cfg *cfg)
{
	ARG_UNUSED(dev);
	uint16_t cmp, pre;

	if (cfg == NULL) {
		return -EINVAL;
	}
	/* We don't support callbacks or windowed mode. */
	if (cfg->callback != NULL) {
		return -EINVAL;
	}
	if (cfg->window.min != 0u) {
		return -EINVAL;
	}

	/* Calculate prescaler and comparator values based on the
	 * requested timeout (in ms).
	 */
	if (wdt_cmrt_calc_prescaler(cfg->window.max,
				    (uint32_t)sys_clock_hw_cycles_per_sec(),
				    &cmp, &pre) != 0) {
		return -EINVAL;
	}

	/* Use maximum additional timeout. There is no way back from
	 * the NMI that the normal watchdog causes. The result is a halt
	 * anyway, but this makes it possible to print logs before halting.
	 */
	wdt_cmrt_configure(cmp, (uint16_t)WATCHDOG_COMPARE_ADD_MAX, pre);

	return 0;
}

static const struct wdt_driver_api wdt_cmrt_api = {
	.setup = wdt_cmrt_setup,
	.disable = wdt_cmrt_disable,
	.install_timeout = wdt_cmrt_install_timeout,
	.feed = wdt_cmrt_feed,
};

static int wdt_cmrt_init(const struct device *dev)
{
	ARG_UNUSED(dev);
	/* Set max NMI timeout to be able to handle expiration in SW. */
	wdt->watchdog_key = WATCHDOG_KEY_VALUE;
	wdt->watchdog_compare_add = WATCHDOG_COMPARE_ADD_MAX;
#ifdef CONFIG_WDT_DISABLE_AT_BOOT
	wdt_cmrt_disable(dev);
#endif
	return 0;
}

/* Initialized watchdog early in the boot. */
DEVICE_DT_DEFINE(DT_ALIAS(watchdog0), wdt_cmrt_init, NULL, NULL, NULL,
		 PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_OBJECTS,
		 &wdt_cmrt_api);
