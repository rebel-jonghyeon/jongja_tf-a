/**
 * Copyright (C) 2012-2015 Yecheng Fu <cofyc.jackson at gmail dot com>
 * All rights reserved.
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "argparse.h"

#define OPT_UNSET 1
#define OPT_LONG_NAME  (1 << 1)

static const char *prefix_skip(const char *str, const char *prefix)
{
	size_t len = strlen(prefix);

	return strncmp(str, prefix, len) ? NULL : str + len;
}

static int prefix_cmp(const char *str, const char *prefix)
{
	for (;; str++, prefix++) {
		if (!*prefix)
			return 0;
		else if (*str != *prefix)
			return (unsigned char)*prefix - (unsigned char)*str;
	}
}

void argparse_error(struct argparse *self, const struct argparse_option *opt,
					const char *reason, int flags)
{
	(void)self;

	if (flags & OPT_LONG_NAME)
		RUSH_CLI_MSG(self->msg_buf, "error: option `--%s` %s\r\n", opt->long_name, reason);
	else
		RUSH_CLI_MSG(self->msg_buf, "error: option `-%c` %s\r\n", opt->short_name, reason);
}

static int argparse_getvalue(struct argparse *self, const struct argparse_option *opt, int flags)
{
	char *s = NULL;

	if (!opt->value)
		goto skipped;

	switch (opt->type) {
	case ARGPARSE_OPT_BOOLEAN:
		if (flags & OPT_UNSET)
			*(int *)(opt->value) = *(int *)opt->value - 1;
		else
			*(int *)(opt->value) = *(int *)opt->value + 1;

		if (*(int *)(opt->value) < 0)
			*(int *)(opt->value) = 0;

		break;
	case ARGPARSE_OPT_BIT:
		if (flags & OPT_UNSET)
			*(int *)(opt->value) &= ~opt->data;
		else
			*(int *)(opt->value) |= opt->data;

		break;
	case ARGPARSE_OPT_STRING:
		if (self->optvalue) {
			*(const char **)(opt->value) = self->optvalue;
			self->optvalue = NULL;
		} else if (self->argc > 1) {
			self->argc--;
			*(const char **)(opt->value) = *++self->argv;
		} else {
			argparse_error(self, opt, "requires a value", flags);
			return -EINVAL;
		}

		break;
	case ARGPARSE_OPT_INTEGER:
		errno = 0;
		if (self->optvalue) {
			*(int *)(opt->value) = strtol(self->optvalue, (char **)&s, 0);
			self->optvalue = NULL;
		} else if (self->argc > 1) {
			self->argc--;
			*(int *)(opt->value) = strtol(*++self->argv, (char **)&s, 0);
		} else {
			argparse_error(self, opt, "requires a value", flags);
			return -EINVAL;
		}

		if (errno) {
			argparse_error(self, opt, strerror(errno), flags);
			return -EINVAL;
		}

		if (s[0] != '\0') { // no digits or contains invalid characters
			argparse_error(self, opt, "expects an integer value", flags);
			return -EINVAL;
		}

		break;
	case ARGPARSE_OPT_LONG:
		errno = 0;
		if (self->optvalue) {
			*(long *)(opt->value) = strtoll(self->optvalue, (char **)&s, 0);
			self->optvalue = NULL;
		} else if (self->argc > 1) {
			self->argc--;
			*(long *)(opt->value) = strtoll(*++self->argv, (char **)&s, 0);
		} else {
			argparse_error(self, opt, "requires a value", flags);
			return -EINVAL;
		}

		if (errno) {
			argparse_error(self, opt, strerror(errno), flags);
			return -EINVAL;
		}

		if (s[0] != '\0') { // no digits or contains invalid characters
			argparse_error(self, opt, "expects an long value", flags);
			return -EINVAL;
		}

		break;
	case ARGPARSE_OPT_FLOAT:
		errno = 0;
		if (self->optvalue) {
			*(float *)(opt->value) = strtof(self->optvalue, (char **)&s);
			self->optvalue = NULL;
		} else if (self->argc > 1) {
			self->argc--;
			*(float *)(opt->value) = strtof(*++self->argv, (char **)&s);
		} else {
			argparse_error(self, opt, "requires a value", flags);
			return -EINVAL;
		}

		if (errno) {
			argparse_error(self, opt, strerror(errno), flags);
			return -EINVAL;
		}

		if (s[0] != '\0') { // no digits or contains invalid characters
			argparse_error(self, opt, "expects a numerical value", flags);
			return -EINVAL;
		}

		break;
	default:
		break;
	}

skipped:
	if (opt->callback)
		return opt->callback(self, opt, opt->ctx, flags);

	return 0;
}

static void argparse_options_check(struct argparse *self, const struct argparse_option *options)
{
	for (; options->type != ARGPARSE_OPT_END; options++) {
		switch (options->type) {
		case ARGPARSE_OPT_END:
		case ARGPARSE_OPT_BOOLEAN:
		case ARGPARSE_OPT_BIT:
		case ARGPARSE_OPT_INTEGER:
		case ARGPARSE_OPT_LONG:
		case ARGPARSE_OPT_FLOAT:
		case ARGPARSE_OPT_STRING:
		case ARGPARSE_OPT_GROUP:
			continue;
		default:
			RUSH_CLI_MSG(self->msg_buf, "wrong option type: %d\r\n", options->type);
			break;
		}
	}
}

static int argparse_short_opt(struct argparse *self, const struct argparse_option *options)
{
	for (; options->type != ARGPARSE_OPT_END; options++) {
		if (!options->short_name)
			continue;
		if (options->short_name == *self->optvalue) {
			self->optvalue = self->optvalue[1] ? self->optvalue + 1 : NULL;
			return argparse_getvalue(self, options, 0);
		}
	}

	return -2;
}

static int argparse_long_opt(struct argparse *self, const struct argparse_option *options)
{
	for (; options->type != ARGPARSE_OPT_END; options++) {
		const char *rest;
		int opt_flags = 0;

		if (!options->long_name)
			continue;

		rest = prefix_skip(self->argv[0] + 2, options->long_name);
		if (!rest) {
			// negation disabled?
			if (options->flags & OPT_NONEG)
				continue;

			// only OPT_BOOLEAN/OPT_BIT supports negation
			if (options->type != ARGPARSE_OPT_BOOLEAN && options->type != ARGPARSE_OPT_BIT)
				continue;

			if (prefix_cmp(self->argv[0] + 2, "no-"))
				continue;

			rest = prefix_skip(self->argv[0] + 2 + 3, options->long_name);
			if (!rest)
				continue;
			opt_flags |= OPT_UNSET;
		}
		if (*rest) {
			if (*rest != '=')
				continue;
			self->optvalue = rest + 1;
		}
		return argparse_getvalue(self, options, opt_flags | OPT_LONG_NAME);
	}

	return -2;
}

int argparse_init(struct argparse *self, struct argparse_option *options,
				  const char *const *usages, int flags,
				  struct rush_cli_msg_buf *msg_buf)
{
	memset(self, 0, sizeof(*self));
	self->options = options;
	self->usages = usages;
	self->flags = flags;
	self->description = NULL;
	self->epilog = NULL;

	self->msg_buf = msg_buf;

	return 0;
}

void argparse_describe(struct argparse *self, const char *description, const char *epilog)
{
	self->description = description;
	self->epilog = epilog;
}

int argparse_parse(struct argparse *self, int argc, const char **argv)
{
	self->argc = argc - 1;
	self->argv = argv + 1;
	self->out = argv;

	argparse_options_check(self, self->options);

	for (; self->argc; self->argc--, self->argv++) {
		const char *arg = self->argv[0];

		if (arg[0] != '-' || !arg[1]) {
			if (self->flags & ARGPARSE_STOP_AT_NON_OPTION)
				goto end;

			// if it's not option or is a single char '-', copy verbatim
			self->out[self->cpidx++] = self->argv[0];
			continue;
		}
		// short option
		if (arg[1] != '-') {
			self->optvalue = arg + 1;
			switch (argparse_short_opt(self, self->options)) {
			case -1:
				break;
			case -2:
				goto unknown;
			default:
				break;
			}
			while (self->optvalue) {
				switch (argparse_short_opt(self, self->options)) {
				case -1:
					break;
				case -2:
				default:
					goto unknown;
				}
			}
			continue;
		}
		// if '--' presents
		if (!arg[2]) {
			self->argc--;
			self->argv++;
			break;
		}
		// long option
		switch (argparse_long_opt(self, self->options)) {
		case -1:
			break;
		case -2:
			goto unknown;
		default:
			break;
		}
		continue;

unknown:
		RUSH_CLI_MSG(self->msg_buf, "error: unknown option `%s`\r\n", self->argv[0]);
		argparse_usage(self);
		if (!(self->flags & ARGPARSE_IGNORE_UNKNOWN_ARGS))
			return -EINVAL;
	}

end:
	memmove(self->out + self->cpidx, self->argv, self->argc * sizeof(*self->out));
	self->out[self->cpidx + self->argc] = NULL;

	return self->cpidx + self->argc;
}

void argparse_usage(struct argparse *self)
{
	if (self->usages) {
		const char *const *usages = self->usages;

		RUSH_CLI_MSG(self->msg_buf, "Usage: %s\r\n", *usages++);
		while (*usages && **usages)
			RUSH_CLI_MSG(self->msg_buf, "   or: %s\r\n", *usages++);
	} else {
		RUSH_CLI_MSG(self->msg_buf, "Usage:\r\n");
	}

	// print description
	if (self->description)
		RUSH_CLI_MSG(self->msg_buf, "%s\r\n", self->description);

	RUSH_CLI_MSG(self->msg_buf, "\r\n");

	const struct argparse_option *options;

	// figure out best width
	size_t usage_opts_width = 0;
	size_t len;

	options = self->options;
	for (; options->type != ARGPARSE_OPT_END; options++) {
		len = 0;
		if (options->short_name)
			len += 2;
		if (options->short_name && options->long_name)
			len += 2;           // separator ", "
		if (options->long_name)
			len += strlen(options->long_name) + 2;

		switch (options->type) {
		case ARGPARSE_OPT_INTEGER:
			len += strlen("=<int>");
			break;
		case ARGPARSE_OPT_LONG:
			len += strlen("=<lng>");
			break;
		case ARGPARSE_OPT_FLOAT:
			len += strlen("=<flt>");
			break;
		case ARGPARSE_OPT_STRING:
			len += strlen("=<str>");
			break;
		default:
			break;
		}
		len = (len + 3) - ((len + 3) & 3);
		if (usage_opts_width < len)
			usage_opts_width = len;
	}
	usage_opts_width += 4;      // 4 spaces prefix

	options = self->options;
	for (; options->type != ARGPARSE_OPT_END; options++) {
		size_t pos = 0;
		size_t pad = 0;
		char buf[256];

		if (options->type == ARGPARSE_OPT_GROUP) {
			RUSH_CLI_MSG(self->msg_buf, "\r\n%s\r\n", options->help);
			continue;
		}
		pos = sprintf(buf, "    ");
		if (options->short_name)
			pos += sprintf(buf + pos, "-%c", options->short_name);
		else
			pos += sprintf(buf + pos, "    ");

		if (options->long_name && options->short_name)
			pos += sprintf(buf + pos, ", ");
		if (options->long_name)
			pos += sprintf(buf + pos, "--%s", options->long_name);

		switch (options->type) {
		case ARGPARSE_OPT_INTEGER:
			pos += sprintf(buf + pos, "=<int>");
			break;
		case ARGPARSE_OPT_LONG:
			pos += sprintf(buf + pos, "=<lng>");
			break;
		case ARGPARSE_OPT_FLOAT:
			pos += sprintf(buf + pos, "=<flt>");
			break;
		case ARGPARSE_OPT_STRING:
			pos += sprintf(buf + pos, "=<str>");
			break;
		default:
			break;
		}

		if (pos <= usage_opts_width) {
			pad = usage_opts_width - pos;
		} else {
			pos += sprintf(buf + pos, "\r\n");
			pad = usage_opts_width;
		}
		RUSH_CLI_MSG(self->msg_buf, "%s%*s%s\r\n", buf, (int)pad + 2, "", options->help);
	}

	// print epilog
	if (self->epilog)
		RUSH_CLI_MSG(self->msg_buf, "%s\r\n", self->epilog);
}

int argparse_help_cb_no_exit(struct argparse *self,	const struct argparse_option *option,
							 void *ctx, int flags)
{
	(void)option;
	argparse_usage(self);

	return 0;
}

int argparse_help_cb(struct argparse *self,	const struct argparse_option *option,
					 void *ctx, int flags)
{
	argparse_help_cb_no_exit(self, option, ctx, flags);

	return 0;
}
