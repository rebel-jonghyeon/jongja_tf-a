/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
 * PROPRIETARY/CONFIDENTIAL
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it
 * only in accordance with the terms of the license agreement you entered
 * into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR NON-INFRINGEMENT.
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT
 * OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#include <test_common.h>
#include <nor.h>

#define TEST_BUFFER_ADDR		0x3D000000ULL
#define TEST_WRITE_FLASH		(0)

uint8_t test_flash(int argc, char **argv)
{
	uint32_t size;
	uint32_t offset;

	if (argc == 0) {
		printf("need command input\n");
		return false;
	}

	uint32_t *buffer = (uint32_t *)TEST_BUFFER_ADDR;

	if (!(*argv[1] & *argv[2])) {
		printf("\nparam error\n");
		return false;
	}

	offset = (uint32_t)strtol(argv[1], NULL, 0);
	size = (uint32_t)strtol(argv[2], NULL, 0);

	if (strcmp(argv[0], "erase") == 0) {
		printf("\nerase 0x%x 0x%x\n", offset, size);
		erase_flash(offset, size);
	} else if (strcmp(argv[0], "read") == 0) {
		printf("\nread 0x%x 0x%x\n", offset, size);
		read_flash(offset, (void *)buffer, size);
	} else if (strcmp(argv[0], "write") == 0) {
		printf("\nwrite 0x%x 0x%x\n", offset, size);
#if TEST_WRITE_FLASH
		printf("Generating sample data.. remove this after verification.\n");
		for (int i = 0; i < size >> 2; i++)
			buffer[i] = i;
#endif
		write_flash(offset, (void *)buffer, size);
	} else {
		printf("\nparam error\n");
		return false;
	}

	return 1;
}

static const char help_flash[] =
	"[test flash]\n"
	" - [flash erase <offset> <size>]\n"
	" - [flash read <offset> <size>]\n"
	" - [flash write <offset> <size>]\n"
	"	For bulk erase, size should be 0x1000000 or higher.\n"
	"	Offset and size should aligned by 4K(0x1000), 32K(0x8000), 64K(0x10000).\n"
	"\n";

CLI_REGISTER(flash, NULL, test_flash, help_flash);
