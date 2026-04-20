#include <freedom_metal.h>
#include <errno.h>

int _link(const char *old_name, const char *new_name) {
	errno = ENOSYS;
	return -1;
}
