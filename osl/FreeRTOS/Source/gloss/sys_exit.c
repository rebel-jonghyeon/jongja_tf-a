#include <freedom_metal.h>

void _exit(int exit_status) {
	metal_shutdown(exit_status);
	while (1)
		;
}
