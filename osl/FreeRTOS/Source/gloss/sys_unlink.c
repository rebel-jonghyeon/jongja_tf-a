#include <freedom_metal.h>
#include <errno.h>

int _unlink(const char *name) {
	errno = ENOSYS;
	return -1;
}
