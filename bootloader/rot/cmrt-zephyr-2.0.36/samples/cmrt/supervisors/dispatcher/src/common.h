/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef COMMON_H
#define COMMON_H

#include <zephyr.h>
#include <cri/cmrt.h>

typedef struct {
	unsigned int id;
	char *name;
	char *info; /* description */
	int (*run)(void *input, u32_t in_used,
		   void *output, u32_t *out_used, u32_t out_size);
} cmd_t;

enum {
	CMDID_BASE         = 0xa5415400,
	CMDID_LIST         = 0xa5415401,
	CMDID_ECHO         = 0xa5415402,
	CMDID_SHA2         = 0xa5415403,
	CMDID_ECDSA        = 0xa5415404,
	CMDID_AES          = 0xa5415405,
	CMDID_FLASH        = 0xa5415406,
	CMDID_SID          = 0xa5415407,
	CMDID_FFDH         = 0xa5415408,
	CMDID_RSA          = 0xa5415409,
	CMDID_UART         = 0xa541540a,
	CMDID_ECIES        = 0xa541540b,
	CMDID_OTP          = 0xa541540c,
	CMDID_ECDH         = 0xa541540d,
	CMDID_SHA3         = 0xa541540e,
	CMDID_RANDOM       = 0xa541540f,
	CMDID_RSA_KEY_EXCH = 0xa5415410,
	CMDID_HMAC         = 0xa5415411,
	CMDID_CCP          = 0xa5415412,
	CMDID_HSDH         = 0xa5415413,
	CMDID_KDC          = 0xa5415414,
	CMDID_FMC          = 0xa5415415,
	CMDID_SET_DEBUG    = 0xa5415416,
	CMDID_PERF         = 0xa5415417
};

extern const cmd_t cmd_list;
extern const cmd_t cmd_echo;
extern const cmd_t cmd_enable_debug;
extern const cmd_t cmd_sha2;
extern const cmd_t cmd_ecdsa;
extern const cmd_t cmd_aes;
extern const cmd_t cmd_fmc;
extern const cmd_t cmd_kdc;
extern const cmd_t cmd_random;
#ifdef CONFIG_CMRT_AXI
extern const cmd_t cmd_flash;
#endif
#ifdef CONFIG_CMRT_SID
extern const cmd_t cmd_sid;
#endif
#ifdef CONFIG_CMRT_FFDH
extern const cmd_t cmd_ffdh;
#endif
extern const cmd_t cmd_rsa;
extern const cmd_t cmd_rsa_key_exch;
#ifdef CONFIG_UART_NS16550
extern const cmd_t cmd_uart;
#endif
#ifdef CONFIG_CMRT_ECIES
extern const cmd_t cmd_ecies;
#endif
#ifdef CONFIG_CRI_OMC_EMULATED_OTP
extern const cmd_t cmd_otp;
#endif
extern const cmd_t cmd_ecdh;
#if defined(CONFIG_CMRT_S3HC) || defined(CONFIG_CMRT_S3HC2)
extern const cmd_t cmd_sha3;
#endif
extern const cmd_t cmd_hmac;
#ifdef CONFIG_CMRT_CCP
extern const cmd_t cmd_ccp;
#endif
#ifdef CONFIG_SV_PERF_MEAS
extern const cmd_t cmd_perf;
#endif

extern const cmd_t *const cmds[];
extern const u32_t nr_cmds;

typedef struct {
	u32_t offset;
	u32_t size;
	u32_t used;
} memory_range_t;

typedef struct {
	memory_range_t to_esw;
	memory_range_t to_hlos;
} buffer_ctrl_t;

extern buffer_ctrl_t *sac_buffers;

char *sac_write_msg(char *output, char *end, int log, const char *format, ...);

#ifdef CONFIG_SV_PERF_MEAS
/* For Performance measures log */
int plog_reset(void);
void plog_set_ref(void);
u32_t plog_get_cycles(void);
u8_t *plog_log_at (void);
#define plog(fmt, ...) sprintf(plog_log_at(), fmt, ##__VA_ARGS__)
#endif

#ifdef DEBUG
#define debug(fmt, ...) printk("Debug: %s:%d " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define debug(fmt, ...) do {} while (0)
#endif

#define info(fmt, ...) printk("%s:%d " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define err(fmt, ...) do { \
	char *_head = (char *) (sac_buffers->to_hlos.offset + CONFIG_RISCV_SAC_BASE_ADDR); \
	char *_end = _head + sac_buffers->to_hlos.size; \
	char *_last = sac_write_msg(_head, _end, 1, "Err: %s:%d " fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
	sac_buffers->to_hlos.used = _last - _head; \
} while (0)


void hexdump_var(const char *name, const void *var, size_t len);

#define HEXDUMP_VAR(var, len) hexdump_var(#var, (var), (len))
#ifdef DEBUG
void debug_hexdump_var(const char *file, int line,
		       const char *name, const void *var, size_t len);
#define DEBUG_HEXDUMP_VAR(var, len) \
	debug_hexdump_var(__FILE__, __LINE__, #var, (var), (len))
#else
#define DEBUG_HEXDUMP_VAR(var, len) do { } while (0)
#endif
#endif
