/* ram_console.c - Console messages to a RAM buffer */

/*
 * Copyright (c) 2015 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <kernel.h>
#include <sys/printk.h>
#include <device.h>
#include <init.h>

extern void __printk_hook_install(int (*fn)(int));
extern void __stdout_hook_install(int (*fn)(int));

#ifdef CONFIG_CMRT_SAC_CONSOLE
#include <drivers/cmrt/sac.h>
static bool wrapped;
static int copied;
char ram_console[CONFIG_RAM_CONSOLE_BUFFER_SIZE];
#else
/* Extra byte to ensure we're always NULL-terminated */
char ram_console[CONFIG_RAM_CONSOLE_BUFFER_SIZE + 1];
#endif
static int pos;

static int ram_console_out(int character)
{
	ram_console[pos] = (char)character;
	pos = (pos + 1) % CONFIG_RAM_CONSOLE_BUFFER_SIZE;
#ifdef CONFIG_CMRT_SAC_CONSOLE
	if (pos == 0) {
		wrapped = true;
	}
#endif
	return character;
}

static int ram_console_init(const struct device *d)
{
	ARG_UNUSED(d);
	__printk_hook_install(ram_console_out);
	__stdout_hook_install(ram_console_out);

	return 0;
}

SYS_INIT(ram_console_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);

#ifdef CONFIG_CMRT_SAC_CONSOLE
void ram_console_copy(void *buffer)
{
	if (copied != pos) {
		/* Word align data copy with extra null */
		ram_console[pos] = '\0';
		int wpos = ROUND_UP(pos + 1, sizeof(uint32_t));
		uint8_t *dst = buffer;
		if (wrapped) {
			int size = CONFIG_RAM_CONSOLE_BUFFER_SIZE - wpos;
			if (size > 0) {
				/* Copy oldest first */
				(void)cmrt_sac_memcpy(dst, &ram_console[wpos], size);
				dst += size;
			}
		}
		(void)cmrt_sac_memcpy(dst, ram_console, wpos);
		copied = pos;
	}
}
#endif
