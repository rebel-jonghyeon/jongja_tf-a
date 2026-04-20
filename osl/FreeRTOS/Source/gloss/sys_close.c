#include <freedom_metal.h>
#include <errno.h>

int _close(int file) {
	errno = ENOSYS;
	return -1;
}
