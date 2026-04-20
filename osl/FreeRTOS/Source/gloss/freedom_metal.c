#include <freedom_metal.h>
#if (__TARGET_CP != 1)
#include <uart.h>
#endif

int metal_cpu_get_current_hartid(void) {
	return 1;
}
int metal_timer_get_timebase_frequency(int hartid, unsigned long long *timebase) {
	return 1;
}
int metal_timer_get_cyclecount(int hartid, unsigned long long *mcc) {
	return 1;
}
int metal_shutdown(int exit_status) {
	return 1;
}
int metal_mem_scrub(char *old, ptrdiff_t incr) {
	for (int i = 0; i < incr; ++i)
		old[i] = 0;
	return 1;
}
int metal_tty_putc(int c) {
	/* Need to be changed after uart drivers is fixed. */
#if (__TARGET_CP != 1)
	uart_putc(c);
#endif
	return 1;
}
