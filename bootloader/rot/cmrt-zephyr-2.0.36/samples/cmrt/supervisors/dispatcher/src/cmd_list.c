/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdio.h>
#include <string.h>

#include "common.h"

static char buf[256];
static int command_list(void *input, u32_t in_used, void *output,
			u32_t *out_used, u32_t out_size)
{
	/* All function parameters points into SAC memory. */
	ARG_UNUSED(input), ARG_UNUSED(in_used);

	/* A record in command list. */
	struct r {
		u32_t id;
		char name[16];
		u32_t length; /* Size of info. */
		char info[0];
	};

	char *head = output;
	struct r *r = (void *) buf;
	for (int i = 0; i < nr_cmds; i++)  {
		u32_t size;

/* Fill one record. */
		const cmd_t *cmd = cmds[i];

/* ... command ID */
		r->id = cmd->id;

/* ... command name */
		size = strlen(cmd->name) + 1;
		strncpy(r->name, cmd->name, sizeof(r->name));
		if (sizeof(r->name) < size)
			r->name[sizeof(r->name) - 1] = '\0';

/* ... command info */
		r->length = strlen(cmd->info) + 1;
		size = ROUND_UP(sizeof(struct r) + r->length, 4);
		if (size > sizeof(buf)) {
			err("Out of memory\n");
			return -ENOMEM;
		}

		memcpy(r->info, cmd->info, r->length);

/* Copy to SAC and move head forward. */
		if (head + size - ((char *) output) > out_size) {
			err("Out of memory\n");
			return -ENOMEM;
		}
		memcpy(head, r, size);
		head += size;
	}

/* Update output size in SAC buffer header. */
	*out_used = head - (char *) output;
	return 0;
}

const cmd_t cmd_list = { CMDID_LIST, "List",
			 "Return list of available commands", command_list };
