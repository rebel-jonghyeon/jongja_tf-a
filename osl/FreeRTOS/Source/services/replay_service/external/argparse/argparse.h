/**
 * Copyright (C) 2012-2015 Yecheng Fu <cofyc.jackson at gmail dot com>
 * All rights reserved.
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 */
#ifndef ARGPARSE_H
#define ARGPARSE_H

/* For c++ compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "rush_cli_msg_buf.h"

struct argparse;
struct argparse_option;

typedef int argparse_callback(struct argparse *self, const struct argparse_option *option,
							  void *ctx, int flags);

enum argparse_flag {
	ARGPARSE_STOP_AT_NON_OPTION  = 1 << 0,
	ARGPARSE_IGNORE_UNKNOWN_ARGS = 1 << 1,
};

enum argparse_option_type {
	/* special */
	ARGPARSE_OPT_END,
	ARGPARSE_OPT_GROUP,
	/* options with no arguments */
	ARGPARSE_OPT_BOOLEAN,
	ARGPARSE_OPT_BIT,
	/* options with arguments (optional or required) */
	ARGPARSE_OPT_INTEGER,
	ARGPARSE_OPT_LONG,
	ARGPARSE_OPT_FLOAT,
	ARGPARSE_OPT_STRING,
};

enum argparse_option_flags {
	OPT_NONEG = 1,              /* disable negation */
};

/**
 *  argparse option
 *
 *  `type`:
 *    holds the type of the option, you must have an ARGPARSE_OPT_END last in your
 *    array.
 *
 *  `short_name`:
 *    the character to use as a short option name, '\0' if none.
 *
 *  `long_name`:
 *    the long option name, without the leading dash, NULL if none.
 *
 *  `value`:
 *    stores pointer to the value to be filled.
 *
 *  `help`:
 *    the short help message associated to what the option does.
 *    Must never be NULL (except for ARGPARSE_OPT_END).
 *
 *  `callback`:
 *    function is called when corresponding argument is parsed.
 *
 *  'ctx':
 *    context for callback.
 *
 *  `data`:
 *    associated data. Callbacks can use it like they want.
 *
 *  `flags`:
 *    option flags.
 */
struct argparse_option {
	enum argparse_option_type type;
	const char short_name;
	const char *long_name;
	void *value;
	const char *help;
	argparse_callback *callback;
	void *ctx;
	intptr_t data;
	int flags;
};

/**
 * argpparse
 */
struct argparse {
	// user supplied
	const struct argparse_option *options;
	const char *const *usages;
	int flags;
	const char *description;    // a description after usage
	const char *epilog;         // a description at the end
								// internal context
	int argc;
	const char **argv;
	const char **out;
	int cpidx;
	const char *optvalue;       // current option value

	struct rush_cli_msg_buf *msg_buf;
};

// built-in callbacks
int argparse_help_cb(struct argparse *self, const struct argparse_option *option,
					 void *ctx, int flags);
int argparse_help_cb_no_exit(struct argparse *self, const struct argparse_option *option,
							 void *ctx, int flags);

// built-in option macros
#define OPT_END()        { ARGPARSE_OPT_END, 0, NULL, NULL, 0, NULL, NULL, 0, 0 }
#define OPT_BOOLEAN(...) { ARGPARSE_OPT_BOOLEAN, __VA_ARGS__ }
#define OPT_BIT(...)     { ARGPARSE_OPT_BIT, __VA_ARGS__ }
#define OPT_INTEGER(...) { ARGPARSE_OPT_INTEGER, __VA_ARGS__ }
#define OPT_LONG(...)    { ARGPARSE_OPT_LONG, __VA_ARGS__ }
#define OPT_FLOAT(...)   { ARGPARSE_OPT_FLOAT, __VA_ARGS__ }
#define OPT_STRING(...)  { ARGPARSE_OPT_STRING, __VA_ARGS__ }
#define OPT_GROUP(h)     { ARGPARSE_OPT_GROUP, 0, NULL, NULL, h, NULL, NULL, 0, 0 }
#define OPT_HELP()       OPT_BOOLEAN('h', "help", NULL,						\
									 "show this help message and exit",		\
									 argparse_help_cb, NULL,				\
									 0, OPT_NONEG)

int argparse_init(struct argparse *self, struct argparse_option *options,
				  const char *const *usages, int flags,
				  struct rush_cli_msg_buf *msg_buf);
void argparse_describe(struct argparse *self, const char *description, const char *epilog);
int argparse_parse(struct argparse *self, int argc, const char **argv);
void argparse_usage(struct argparse *self);
void argparse_error(struct argparse *self, const struct argparse_option *opt,
					const char *reason, int flags);

#ifdef __cplusplus
}
#endif

#endif
