#include <freedom_metal.h>
#include <errno.h>

int _fork() {
	errno = ENOSYS;
	return -1;
}
