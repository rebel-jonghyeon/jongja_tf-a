/*
 * Copyright (c) 2008-2015 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#pragma once

#include "printf.h"
#include "typedef.h"

#define putc(c, fp) fputc(c, fp)
int putchar(int c);

int puts(const char *str);

int getchar(void);

int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list ap);

int _fprintf_output_func(const char *str, size_t len, void *state);

int sprintf(char *str, const char *fmt, ...);
int snprintf(char *str, size_t len, const char *fmt, ...);
int vsprintf(char *str, const char *fmt, va_list ap);
int vsnprintf(char *str, size_t len, const char *fmt, va_list ap);
