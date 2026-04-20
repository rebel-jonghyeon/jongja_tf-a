#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "printf.h"

#if defined(__RUN_RTOS)
#include <FreeRTOSConfig.h>
/* TODO: Also include interrutp.h for CA73 */
#if defined(__TARGET_PCIE)
#include <FreeRTOS.h>
#include <task.h>
#endif
#endif

void assert(int);
void assert_with_message(char *file, unsigned int line);
void conditional_assert(int x);
void conditional_assert_with_message(int x, char *file, unsigned int line);
