#include <freedom_metal.h>
#include <errno.h>

int _faccessat(int dirfd, const char *file, int mode, int flags) {
	errno = ENOSYS;
	return -1;
}
