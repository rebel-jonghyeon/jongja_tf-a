/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_LOGGING_LOG_H_
#define ZEPHYR_INCLUDE_LOGGING_LOG_H_

#include <stdio.h>
#include <stdint.h>
#ifdef CONFIG_LOG_TIMESTAMP
#include <drivers/cmrt/util.h>
#endif
void sys_hexdump(const uint8_t *buf, size_t len, const char *msg);

#define LOG_MODULE_DECLARE(m, l)

#ifdef CONFIG_DEBUG
#ifdef CONFIG_LOG_TIMESTAMP
#define LOG_DBG(fmt, ...) do {						\
		fprintf(stdout, "%08d ", (int)cmrt_uptime_get());	\
		fprintf(stdout, "CD: " fmt "\n", ##__VA_ARGS__);	\
	} while(0)
#define LOG_HEXDUMP_DBG(d, l, s) do {					\
		fprintf(stdout, "%08d ", (int)cmrt_uptime_get());	\
		fprintf(stdout, "CD: %s\n", (s));			\
		sys_hexdump((d), (l), "CD:");				\
	} while (0)
#else
#define LOG_DBG(fmt, ...) do { fprintf(stdout, "CD: " fmt "\n", ##__VA_ARGS__); } while(0)
#define LOG_HEXDUMP_DBG(d, l, s) do {			\
		fprintf(stdout, "CD: %s\n", (s));	\
		sys_hexdump((d), (l), "CD:");		\
	} while (0)
#endif
#else
#define LOG_DBG(fmt, ...) do {} while (0)
#define LOG_HEXDUMP_DBG(d, l, s) do {  (void)(d); (void)(l); (void)(s); } while (0)
#endif

#ifdef CONFIG_LOG_TIMESTAMP
#define LOG_INF(fmt, ...) do {						\
		fprintf(stdout, "%08d ", (int)cmrt_uptime_get());	\
		fprintf(stdout, "CI: " fmt "\n", ##__VA_ARGS__);	\
	} while(0)
#define LOG_HEXDUMP_INF(d, l, s) do {					\
		fprintf(stdout, "%08d ", (int)cmrt_uptime_get());	\
		fprintf(stdout, "CI: %s\n", (s));			\
		sys_hexdump((d), (l), "CI:");				\
	} while (0)
#define LOG_WRN(fmt, ...) do {						\
		fprintf(stderr, "%08d ", (int)cmrt_uptime_get());	\
		fprintf(stderr, "CW: " fmt "\n", ##__VA_ARGS__);	\
	} while(0)
#define LOG_ERR(fmt, ...) do {						\
		fprintf(stderr, "%08d ", (int)cmrt_uptime_get());	\
		fprintf(stderr, "CE: " fmt "\n", ##__VA_ARGS__);	\
	} while(0)
#else
#define LOG_INF(fmt, ...) do { fprintf(stdout, "CI: " fmt "\n", ##__VA_ARGS__); } while(0)
#define LOG_HEXDUMP_INF(d, l, s) do {			\
		fprintf(stdout, "CI: %s\n", (s));	\
		sys_hexdump((d), (l), "CI:");		\
	} while (0)
#define LOG_WRN(fmt, ...) do { fprintf(stderr, "CW: " fmt "\n", ##__VA_ARGS__); } while(0)
#define LOG_ERR(fmt, ...) do { fprintf(stderr, "CE: " fmt "\n", ##__VA_ARGS__); } while(0)
#endif

#endif
