/*
 * Copyright (c) 2019-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef TEEINT_H
#define TEEINT_H

#include <stdint.h>
#include <stddef.h>

#include <fs/teefs.h>
#include <fs/teedev.h>

#ifdef CONFIG_TEEFS_MULTITHREADING
#ifdef __ZEPHYR__
#include <zephyr.h>
#endif
#endif

#if CONFIG_TEEFS_MAX_PAGES == 7
#define TEEFS_PAGE_ROOT 0x52  /* 'R' in hexdump */
#define TEEFS_PAGE_FILE 0x46  /* 'F' in hexdump */
typedef uint8_t tee_id_t;
typedef uint8_t tee_type_t;
typedef uint16_t fnv_hash_t;
#define IS_LARGER(id1, id2) ((int8_t)((id1) - (id2)) > 0)
#define IS_LARGER_EQ(id1, id2) ((int8_t)((id1) - (id2)) >= 0)
#elif CONFIG_TEEFS_MAX_PAGES == 15
#define TEEFS_PAGE_ROOT 0x5452  /* 'RT' in hexdump */
#define TEEFS_PAGE_FILE 0x4C46  /* 'FL' in hexdump */
typedef uint16_t tee_id_t;
typedef uint16_t tee_type_t;
typedef uint32_t fnv_hash_t;
#define IS_LARGER(id1, id2) ((int16_t)((id1) - (id2)) > 0)
#define IS_LARGER_EQ(id1, id2) ((int16_t)((id1) - (id2)) >= 0)
#else /* CONFIG_TEEFS_MAX_PAGES == 31 */
#define TEEFS_PAGE_ROOT 0x544F4F52  /* 'ROOT' in hexdump */
#define TEEFS_PAGE_FILE 0x454C4946  /* 'FILE' in hexdump */
typedef uint32_t tee_id_t;
typedef uint32_t tee_type_t;
typedef uint32_t fnv_hash_t;
#define IS_LARGER(id1, id2) ((int32_t)((id1) - (id2)) > 0)
#define IS_LARGER_EQ(id1, id2) ((int32_t)((id1) - (id2)) >= 0)
#endif

#define TEEFS_MAX_NAMELEN ((1 << 8) - 1)  /* implementation limit */
#define TEEFS_MAX_DATALEN ((1 << 24) - 1) /* implementation limit */
#if CONFIG_TEEFS_MAX_NAMELEN > TEEFS_MAX_NAMELEN
#error "CONFIG_TEEFS_MAX_NAMELEN cannot be larger than 255"
#endif

/* Structures are word aligned for all three configurations. */

typedef struct tee_page {
	tee_id_t id;            /* running page id */
	tee_type_t type;        /* ROOT or FILE */
} tee_page_t;

typedef struct tee_file_info {
	fnv_hash_t fnv_hash;    /* file name hash */
	tee_id_t old_id;        /* old starting page id */
	tee_id_t new_id;        /* new starting page id */
} tee_file_info_t;

#define MAX_ROOTS ((uint16_t)-1)
#define MAX_INFOS ((uint16_t)-1)

typedef struct tee_root_page {
	tee_page_t page;        /* page id and type */
	uint8_t blocks;         /* log2 of blocks */
	uint8_t block_size;     /* log2 of block size */
	uint8_t page_size;      /* log2 of page size */
	uint8_t state;          /* running state */
	tee_id_t first_id;      /* first page id */
	tee_id_t prev_id;       /* previous root */
	uint16_t roots;         /* number of roots */
	uint16_t infos;         /* nr of infos */
	tee_file_info_t info[]; /* added and deleted infos */
} tee_root_page_t;

#define TEEFS_STATE_OK 0x4F /* normal operation, 'O' in hexdump */
#define TEEFS_STATE_GC 0x47 /* garbage collecting, 'G' in hexdump */

typedef struct tee_file_page {
	tee_page_t page;        /* page id and type */
	fnv_hash_t fnv_hash;    /* file name hash */
	uint32_t contentlen;    /* file name and data lengths */
	uint8_t content[];      /* file name (first page) and data */
} tee_file_page_t;

#define NAMELEN_SHIFT (24)
#define DATALEN_MASK (0x00FFFFFF)

#define ROOT_SPACE ((1u << CONFIG_TEEFS_MAX_PAGE_SIZE) - sizeof(tee_root_page_t))
#define NUM_INFOS (ROOT_SPACE / sizeof(tee_file_info_t))
#define CACHE_PAGES CONFIG_TEEFS_MAX_CACHE_PAGES

/* The filesystem structures and internal functions. */

typedef struct tee_cache {
	tee_id_t id;             /* page id in cache index */
	tee_type_t type;         /* page type in cache index */
	bool dirty;              /* is the index not written */
} tee_cache_t;

typedef struct tee_deleted {
	unsigned num;            /* number of deleted ids */
	unsigned highest_id;     /* index of highest page id in deleted ids */
	tee_id_t ids[NUM_INFOS]; /* deleted ids for gc and ls */
} tee_deleted_t;

typedef struct tee_fs {
	int state;               /* running state */
	int flags;               /* mount flags */
	tee_id_t head_id;        /* topmost root */
	tee_id_t tail_id;        /* bottom root */
	tee_id_t first_id;       /* lowest page id in bottom root */
	tee_id_t last_id;        /* newest page id */
	tee_id_t prog_id;        /* last programmed page id */
	tee_id_t start_id;       /* last start id for a file */
	tee_device_t *dev;       /* pointer to device */
	unsigned refs;           /* internal reference counter */
	unsigned errors;         /* internal error counter */
	tee_stats_t stats;       /* statistics counters */
	tee_deleted_t deleted;   /* deleted ids for gc */
	tee_cache_t cache[CACHE_PAGES];  /* cache for page reads and writes */
} tee_fs_t;

typedef struct tee_file {
	tee_fs_t *fs;           /* pointer to fs */
	fnv_hash_t fnv_hash;    /* file name hash */
	tee_id_t start_id;      /* starting page id */
	size_t namelen;         /* file name length */
	size_t datalen;         /* file data length */
	size_t offset;          /* file data offset */
	bool dirty;             /* autosync in close */
	char path[CONFIG_TEEFS_MAX_NAMELEN]; /* name to look for in open_fd */
	size_t pathlen;         /* name len for internal references */
	unsigned refs;          /* internal reference counter */
	int error;              /* see ERR_RET and teefs_error */
	const char *func;       /* see ERR_RET and teefs_error */
	unsigned line;          /* see ERR_RET and teefs_error */
} tee_file_t;

typedef struct tee_dir {
	tee_fs_t *fs;           /* pointer to fs */
	uint16_t roots;         /* roots left to scan */
	uint16_t infos;         /* current index in root */
	tee_id_t root_id;       /* current root page id */
	tee_deleted_t deleted;  /* deleted ids so far */
	char path[CONFIG_TEEFS_MAX_NAMELEN]; /* prefix to look for */
	size_t pathlen;         /* prefix len */
} tee_dir_t;

#define ERR_RET(e) {				\
		file->error = (e);		\
		file->func = __func__;		\
		file->line = __LINE__;		\
		return (e);			\
	}

int teedev_mount(const void *mp, size_t mplen, tee_device_t *dev);
int teedev_umount(const void *mp, size_t mplen, tee_stats_t *stats);

tee_fs_t *open_mp(const void *mp, size_t mplen, bool ismp);
tee_fs_t *open_mp_at(int index, void *mp, size_t *mplen, tee_stats_t *stats);
void close_mp(tee_fs_t *fs);
int open_fd(tee_fs_t *fs, const void *name, size_t namelen, bool reserve);
void rename_fd(int fd, const void *name, size_t namelen);
int find_fd(tee_fs_t *fs, tee_id_t id);
int close_fd(int fd);
tee_file_t *fd2file(int fd);
int open_dd(tee_fs_t *fs);
int close_dd(int dd);
tee_dir_t *dd2file(int dd);

#ifdef CONFIG_TEEFS_MULTITHREADING
void lock_teefs(void);
void unlock_teefs(void);
#else
#define lock_teefs() do { } while (0)
#define unlock_teefs() do { } while (0)
#endif

#endif
