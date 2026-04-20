/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to demonstrate SOC Interrupt Driver (SID) API.
 */

#include <stdio.h>
#include <cri/cmrt.h>
#include <crisyscall-user.h>
#include <cri/cmrt/sid.h>
#include <crilog-user.h>

/*
 * System can support up to 32 interrupts (CONFIG_SOC_NUM_IRQS),
 * IRQs 8 and 9 are reserved for SIC1, IRQs 0 and 1 are reserved for SIC2.
 */
#define CRI_SID_IRQ_MASK 0xfc

static int watch_irqs(cri_sid_t sid)
{
	/*
	 * Note that this example observes only a single occurrence of
	 * each interrupt. To monitor further occurrences of an
	 * interrupt that has been triggered already, the code must
	 * call cri_sid_watch() again to re-register interest.
	 */
	uint32_t irqs = 0;
	int res = cri_sid_watch(sid, CRI_SID_IRQ_MASK, CRI_SID_IRQ_MASK, &irqs);
	if (res) {
		c_error("Failed to enable IRQ monitoring: %d\n", res);
		return 1;
	}
	c_log("IRQs enabled 0x%08X\n", CRI_SID_IRQ_MASK);

	c_log("Start polling\n");
	while (1) {
		/* Wait for an interrupt to occur */
		res = cri_wait(1, &sid, CRI_SECONDS(3));

		if (res > 0) {
			if (res & 1) {
				cri_sid_sync(sid);
				c_log("Triggered IRQs: 0x%08X\n", irqs);
				c_log("...log it again...\n");
				c_log("Triggered IRQs: 0x%08X\n", irqs);
			} else {
				c_log("Unexpected poll event (res: %08x)\n", (uint32_t)res);
			}
		} else if (res == 0) {
			c_log("Poll timeout\n");
		} else {
			c_log("Poll error\n");
			return 1;
		}
	}
}

int main(void)
{
	c_log("Container (watch_irq) starting...\n");

	/* Reserve all SOC IRQs */
	const cri_sid_t sid = cri_sid_open(0, CRI_SID_IRQ_MASK);
	if (!cri_is_valid(sid)) {
		c_error("SID open failed: %d\n", sid);
		return 1;
	}

	int res = watch_irqs(sid);
	cri_sid_close(sid);
	c_log("Container exiting.\n");
	return res;
}
