#pragma once

#include <logging/log.h>
#include "test_mailbox.h"

#define TEST_CHANNEL		(31)
#define TEST_BUF			(63)
#define TEST_CMD			("TEST")
#define CMD_SIZE			(sizeof(TEST_CMD) - 1)

int test_external_ip(int ch);
void register_test_cb(void);
