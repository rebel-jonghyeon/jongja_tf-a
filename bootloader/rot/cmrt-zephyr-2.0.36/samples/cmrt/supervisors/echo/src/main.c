/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <zephyr.h>
#include <device.h>
#include <string.h>
#include <sys/util.h>
#include <app_memory/app_memdomain.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/util.h>
#include <drivers/cmrt/fboot.h>
#include <cmrt/fboot/fboot_config.h>

#ifdef CONFIG_CMRT_PMU
#include <drivers/cmrt/pmu.h>
#endif

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

/*
 * Example monolithic container that runs in supervisor mode.
 */

const static char version_info[] __version = SUPERVISOR_VERSION_INFO;

/* Same stack size in all three cases. */
#define STACK_SIZE CONFIG_MAIN_STACK_SIZE

#ifdef CONFIG_TEST_USER_THREADS
struct k_thread user_thread;
K_THREAD_STACK_DEFINE(user_stack, STACK_SIZE);
#endif

/* The same buffer is used by the main supervisor thread and user thread. */
K_APPMEM_PARTITION_DEFINE(shared_partition);
K_APP_DMEM(shared_partition) alignas(4) uint8_t buffer[1024];

#ifdef CONFIG_TEST_USER_CONTAINERS
struct k_thread container_thread;
K_THREAD_STACK_DEFINE(container_stack, STACK_SIZE);

#include <linker/linker-defs.h>

static void load_container(void)
{
	uint8_t *buffer = (uint8_t *)ROUND_UP(_image_ram_end, sizeof(uint32_t));
	cmrt_sic_t sic = cmrt_sic_open(CMRT_O_SYNC, 0);
	if (!cmrt_is_valid(sic)) {
		LOG_INF("Cannot open SIC");
		return;
	}
	LOG_INF("Waiting for user container on 0x0...");
	size_t buflen = 32 * 1024;
	uint32_t peerid;
	int res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
	if (res < 0) {
		LOG_INF("Failed to read from HLOS: %d!", res);
		return;
	}
	LOG_INF("Loaded %d bytes from 0x%x", buflen, (unsigned int)peerid);
	cmrt_sic_close(sic);
}
#endif

static void echo_function(void *p1, void *p2, void *p3)
{
	uint32_t flowid = (uint32_t)p1;
	uint8_t *buffer = (uint8_t *)p2;
	size_t bufmax = (size_t)p3;

#ifdef CONFIG_TEST_INVALID_SYSCALL
	if (flowid > 0) {
		/* Make an invalid syscall. Thread dies... */
		arch_syscall_invoke0(UINT_MAX);
	}
#endif
	cmrt_sic_t sic = cmrt_sic_open(CMRT_O_SYNC, flowid);
	if (!cmrt_is_valid(sic)) {
		LOG_INF("Cannot open SIC");
		return;
	}
	LOG_INF("Waiting for SIC input on 0x%x...", (unsigned int)flowid);
	for (;;) {
#ifdef CONFIG_CMRT_PMU
		/* Advertise low power before wait. */
		(void)cmrt_pmu_low_power(true);
#endif
		size_t buflen = bufmax;
		uint32_t peerid;
		int res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_INF("Failed to read from HLOS: %d!", res);
			return;
		}

		LOG_INF("Echoing %d bytes from 0x%x to 0x%x",
			buflen, (unsigned int)flowid, (unsigned int)peerid);

		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			return;
		}
	}
}

#if 1 /* samples may have its own code, 0x5fXX, to be recognized from HLOS */
#define SUPERVISOR_SAMPLE_STARTED 0x5f010000
#endif

int main(void)
{
	int res = 0;
	cmrt_set_boot_status(SUPERVISOR_RUNNING_ID, SUPERVISOR_RUNNING_ID);
#ifdef SUPERVISOR_SAMPLE_STARTED
	cmrt_write_reg(CMRT_SIC_BASE, R_SCRATCH_0, SUPERVISOR_SAMPLE_STARTED);
#endif
	/* Running in supervisor mode here. */
	LOG_INF("Supervisor (echo) %s running...", version_info);
#ifdef CONFIG_CMRT_PMU
	/* Make it possible to go to low power mode. */
	cmrt_pmu_low_power(true);
#endif
#ifdef CONFIG_TEST_USER_THREADS
	/* Add the buffer to the default domain. */
	k_mem_domain_add_partition(&k_mem_domain_default, &shared_partition);
	/* Inherit perms to allow user thread to use the supervisor buffer. */
	(void)k_thread_create(&user_thread, user_stack, STACK_SIZE,
			      echo_function, (void *)1, buffer, (void *)sizeof(buffer),
			      -1, K_USER | K_INHERIT_PERMS, K_MSEC(0));
#endif
#ifdef CONFIG_TEST_USER_CONTAINERS
	load_container();
	(void)k_thread_create(&container_thread, container_stack, STACK_SIZE,
			      (k_thread_entry_t)_image_ram_end, (void *)2,
			      NULL, NULL, -1, K_USER | K_CONTAINER, K_FOREVER);
	k_thread_start(&container_thread);
#endif
	echo_function((void *)0, (void *)buffer, (void *)sizeof(buffer));
	cmrt_set_boot_status(0, SUPERVISOR_RUNNING_ID);
	return res;
}
