#include <assert.h>

void assert(int expression)
{
#if defined(__RUN_RTOS)
	configASSERT(expression);
#else
	/* TODO: implement for baremetal */
#endif
}

void assert_with_message(char *file, unsigned int line)
{
	printf("Assertion failed at %s: %d-line\r\n", file, line);
#if defined(__RUN_RTOS)
	configASSERT(0);
#else
	/* TODO: implement for baremetal */
#endif
}

void conditional_assert(int x)
{
#if defined(__RUN_RTOS)
	configASSERT(x);
#else
	/* TODO: implement for baremetal */
#endif
}

void conditional_assert_with_message(int x, char *file, unsigned int line)
{
	printf("Assertion failed at %s: %d-line\r\n", file, line);
#if defined(__RUN_RTOS)
	configASSERT(x);
#else
	/* TODO: implement for baremetal */
#endif
}
