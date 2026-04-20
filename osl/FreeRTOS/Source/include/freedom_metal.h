#pragma once

#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>

int metal_cpu_get_current_hartid(void);
int metal_timer_get_timebase_frequency(int hartid, unsigned long long *timebase);
int metal_timer_get_cyclecount(int hartid, unsigned long long *mcc);
int metal_shutdown(int exit_status);
int metal_mem_scrub(char *old, ptrdiff_t incr);
int metal_tty_putc(int c);

struct utimbuf;

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);
int _access(const char *file, int mode);
int _chdir(const char *path);
int _chmod(const char *path, mode_t mode);
int _chown(const char *path, uid_t owner, gid_t group);
int clock_getres(clockid_t clk_id, struct timespec *res);
int clock_gettime(clockid_t clk_id, struct timespec *tp);
int clock_settime(clockid_t clk_id, const struct timespec *tp);
int _close(int file);
int _execve(const char *name, char *const argv[], char *const env[]);
void _exit(int exit_status);
int _faccessat(int dirfd, const char *file, int mode, int flags);
int _fork();
int _fstat(int file, struct stat *st);
int _fstatat(int dirfd, const char *file, struct stat *st, int flags);
int _ftime(struct timeb *tp);
char *_getcwd(char *buf, size_t size);
int _getpid();
int _gettimeofday(struct timeval *tp, void *tzp);
int _isatty(int file);
int _kill(int pid, int sig);
int _link(const char *old_name, const char *new_name);
off_t _lseek(int file, off_t ptr, int dir);
int _lstat(const char *file, struct stat *st);
int _open(const char *name, int flags, int mode);
int _openat(int dirfd, const char *name, int flags, int mode);
ssize_t _read(int file, void *ptr, size_t len);
int _brk(void *addr);
char *_sbrk(ptrdiff_t incr);
int _stat(const char *file, struct stat *st);
long _sysconf(int name);
clock_t _times(struct tms *buf);
int _unlink(const char *name);
int _utime(const char *path, const struct utimbuf *times);
int _wait(int *status);
ssize_t _write(int file, const void *ptr, size_t len);
