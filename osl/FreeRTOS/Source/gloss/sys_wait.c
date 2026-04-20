#include <freedom_metal.h>
#include <errno.h>

int _wait(int *status) {
	errno = ENOSYS;
	return -1;
}
