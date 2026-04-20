#include <freedom_metal.h>
#include <errno.h>

#ifdef __TARGET_CP
#include "cpu.h"
#else
int get_current_cpuid(void) { return 1; }
#endif

int _getpid(void) { return get_current_cpuid(); }
