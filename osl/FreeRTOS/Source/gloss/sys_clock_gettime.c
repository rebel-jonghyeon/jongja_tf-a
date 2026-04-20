#define _POSIX_MONOTONIC_CLOCK 200809L
#define _POSIX_TIMERS
#include <freedom_metal.h>
#include <errno.h>
#include <time.h>

#ifdef MTIME_RATE_HZ_DEF
#undef MTIME_RATE_HZ
#define MTIME_RATE_HZ MTIME_RATE_HZ_DEF
#endif

#ifndef MTIME_RATE_HZ
#define MTIME_RATE_HZ 32768
#endif

#if !defined(mtime_interrupt_controller) &&	\
	defined(__METAL_DT_RISCV_CLINT0_HANDLE)
#define mtime_interrupt_controller __METAL_DT_RISCV_CLINT0_HANDLE
#endif

#if !defined(mtime_interrupt_controller) &&	\
	defined(__METAL_DT_SIFIVE_CLIC0_HANDLE)
#define mtime_interrupt_controller __METAL_DT_SIFIVE_CLIC0_HANDLE
#endif

int clock_getres(clockid_t clk_id, struct timespec *res) {
	errno = EINVAL;
	return -1;
}

int clock_gettime(clockid_t clk_id, struct timespec *tp) {
	errno = EINVAL;
	return -1;
}

int clock_settime(clockid_t clk_id, const struct timespec *tp) {
	errno = EINVAL;
	return -1;
}
