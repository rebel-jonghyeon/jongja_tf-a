#include <freedom_metal.h>
#include <errno.h>

int _kill(int pid, int sig) {
	errno = ENOSYS;
	return -1;
}
