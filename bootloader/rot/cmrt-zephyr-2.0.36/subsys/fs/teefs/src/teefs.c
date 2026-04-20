/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "teeint.h"

#undef VERBOSE_DEBUG
#ifdef VERBOSE_DEBUG
#define debug(fmt, ...) do { printf("%s: ", __func__); printf(fmt, ##__VA_ARGS__); } while (0)
#else
#define debug(fmt, ...) do { } while (0)
#endif

static inline tee_page_t *cache_page(tee_fs_t *fs, int index)
{
	return fs->dev->impl->cache(fs->dev, index);
}

static inline tee_root_page_t *cache_root(tee_fs_t *fs, int index)
{
	return fs->dev->impl->cache(fs->dev, index);
}

static inline tee_file_page_t *cache_file(tee_fs_t *fs, int index)
{
	return fs->dev->impl->cache(fs->dev, index);
}

static inline unsigned dev_pagesinblock(tee_device_t *dev)
{
	return 1u << (dev->impl->block_size - dev->impl->page_size);
}

static unsigned dev_badpages(tee_device_t *dev)
{
	unsigned pages_in_block = dev_pagesinblock(dev);
	return pages_in_block * CONFIG_TEEFS_MAX_BAD_BLOCKS;
}

static inline unsigned dev_numblocks(tee_device_t *dev)
{
	return 1u << dev->impl->blocks(dev);
}

static unsigned dev_numpages(tee_device_t *dev)
{
	return dev_numblocks(dev) << (dev->impl->block_size - dev->impl->page_size);
}

static tee_id_t dev_page(tee_device_t *dev, tee_id_t page_id)
{
	tee_id_t page_id_mask = dev_numpages(dev) - 1;
	return page_id & page_id_mask;
}

static inline tee_id_t dev_block2page(tee_device_t *dev, tee_id_t block)
{
	return block << (dev->impl->block_size - dev->impl->page_size);
}

static inline tee_id_t dev_page2block(tee_device_t *dev, tee_id_t page)
{
	return page >> (dev->impl->block_size - dev->impl->page_size);
}

static inline size_t dev_pagesize(tee_device_t *dev)
{
	return 1 << dev->impl->page_size;
}
static inline size_t dev_filespace(tee_device_t *dev)
{
	/* Number of bytes for file data in a page. */
	return dev_pagesize(dev) - sizeof(tee_file_page_t);
}

#define NULL_ID  (fs->first_id - 1)

static inline int cache_pages(tee_fs_t *fs)
{
	return fs->dev->impl->cache_pages < CONFIG_TEEFS_MAX_CACHE_PAGES ?
		fs->dev->impl->cache_pages : CONFIG_TEEFS_MAX_CACHE_PAGES;
}

static int cache_scan(tee_fs_t *fs, tee_type_t type, bool dirty)
{
	for (int i = 0; i < cache_pages(fs); i++) {
		if ((fs->cache[i].type == type) &&
		    (fs->cache[i].dirty == dirty)) {
			return i;
		}
	}
	return -ENOENT;
}

static int cache_prog(tee_fs_t *fs, int index, tee_id_t page_id, tee_type_t type)
{
	if (IS_LARGER(page_id, fs->prog_id)) {
		/* Mark id as the last one programmed, even if we fail. */
		fs->prog_id = page_id;
	}
	fs->cache[index].id = page_id;
	fs->cache[index].type = type;
	tee_id_t page = dev_page(fs->dev, page_id);
	tee_id_t block = dev_page2block(fs->dev, page);
	if (fs->dev->impl->block_isbad(fs->dev, block)) {
		if (fs->errors < dev_badpages(fs->dev)) {
			fs->errors++;
			return -EBADF;
		}
		return -EFAULT;
	}
	tee_id_t pages_in_block_mask = dev_pagesinblock(fs->dev) - 1;
	if (!(page & pages_in_block_mask) && IS_LARGER_EQ(page_id, fs->prog_id)) {
		/* Make next block available. */
		if (fs->dev->impl->block_erase(fs->dev, block)) {
			if (fs->errors < dev_badpages(fs->dev)) {
				fs->errors++;
				return -EBADF;
			}
			return -EFAULT;
		}
	}
	if (fs->dev->impl->page_prog(fs->dev, page, index)) {
		if (fs->errors < dev_badpages(fs->dev)) {
			fs->errors++;
			return -EBADF;
		}
		return -EFAULT;
	}
	fs->stats.dev_progs++;
	fs->cache[index].dirty = false;

	return index;
}

static void cache_update(tee_fs_t *fs, int index, tee_id_t page_id, tee_type_t type)
{
	for (int i = 0; i < cache_pages(fs); i++) {
		if (fs->cache[i].id == page_id && fs->cache[i].type) {
			/* This page id can be there only once. */
			fs->cache[i].id = 0;
			fs->cache[i].type = 0;
			fs->cache[i].dirty = false;
		}
	}
	fs->cache[index].id = page_id;
	fs->cache[index].type = type;
	fs->cache[index].dirty = true;
	fs->stats.cache_progs++;
}

static void update_root(tee_fs_t *fs, int index)
{
	tee_root_page_t *r = cache_root(fs, index);
	cache_update(fs, index, r->page.id, TEEFS_PAGE_ROOT);
	fs->head_id = r->page.id;
	if (r->roots == 1) fs->tail_id = r->page.id;
}

static void commit_root(tee_fs_t *fs, int index)
{
	tee_root_page_t *r = cache_root(fs, index);
	if (IS_LARGER(fs->first_id, r->page.id)) {
		r->page.id = ++fs->last_id;
		r->page.type = TEEFS_PAGE_ROOT;
		r->first_id = r->page.id;
		for (unsigned i = 0; i < r->infos; i++) {
			/* The first added/updated file sets root's first id. */
			if (IS_LARGER_EQ(r->info[i].new_id, fs->first_id)) {
				r->first_id = r->info[i].new_id;
				break;
			}
		}
		update_root(fs, index);
	}
}

static int cache_purge(tee_fs_t *fs)
{
	int index = -ENOENT;
	tee_id_t page_id = fs->prog_id + 1;
	/* Find the next page to program in cache. */
	for (int i = 0; i < cache_pages(fs); i++) {
		if (fs->cache[i].type && fs->cache[i].dirty &&
		    fs->cache[i].id == page_id) {
			index = i;
			break;
		}
	}
	if (index < 0) {
		/* Find the possible head root page and purge it. */
		index = cache_scan(fs, TEEFS_PAGE_ROOT, true);
		if (index < 0) return index;
		commit_root(fs, index);
	}
	/* Write the page to make this cache entry free. */
	int res = index;
	tee_type_t type = fs->cache[index].type;
	while ((res = cache_prog(fs, index, page_id, type)) == -EBADF) {
		/* Bad block/page, fix the page ids for all cached writes. */
		for (int i = 0; i < cache_pages(fs); i++) {
			if (fs->cache[i].type && fs->cache[i].dirty) {
				tee_page_t *p = cache_page(fs, i);
				if (p->type == TEEFS_PAGE_ROOT) {
					/* Fix references to the page id. */
					tee_root_page_t *r = cache_root(fs, i);
					if (r->first_id == page_id) r->first_id++;
					if (r->prev_id == page_id) r->prev_id++;
					for (int j = 0; j < r->infos; j++) {
						if (r->info[j].old_id == page_id)
							r->info[j].old_id++;
						if (r->info[j].new_id == page_id)
							r->info[j].new_id++;
					}
				}
				if (IS_LARGER_EQ(fs->cache[i].id, page_id)) {
					fs->cache[i].id = ++p->id;
				}
			}
		}
		if (IS_LARGER_EQ(fs->head_id, page_id)) fs->head_id++;
		if (IS_LARGER_EQ(fs->tail_id, page_id)) fs->tail_id++;
		if (IS_LARGER_EQ(fs->start_id, page_id)) fs->start_id++;
		fs->last_id++;
		page_id++;
	}
	return res;
}

static int cache_read(tee_fs_t *fs, tee_id_t page_id, tee_type_t type)
{
	fs->stats.cache_reads++;
	int index = -ENOENT;
	for (int i = 0; i < cache_pages(fs); i++) {
		/* First try to find it in cache. */
		if (fs->cache[i].id == page_id && fs->cache[i].type == type) {
			/* It's there, just return it. */
			return i;
		}
		if (!fs->cache[i].type) index = i; /* free */
	}
	if (index < 0) {
		/* Not found, take a file page into use. */
		index = cache_scan(fs, TEEFS_PAGE_FILE, false);
		if (index < 0) {
			/* Not found, take a root page into use. */
			index = cache_scan(fs, TEEFS_PAGE_ROOT, false);
			if (index < 0) {
				/* Cannot find a page to take, make room. */
				index = cache_purge(fs);
				if (index < 0) return index;
			}
		}
	}
	fs->cache[index].id = 0;
	fs->cache[index].type = 0;
	fs->cache[index].dirty = false;
	if (IS_LARGER_EQ(page_id, fs->first_id)) {
		tee_id_t page = dev_page(fs->dev, page_id);
		tee_id_t block = dev_page2block(fs->dev, page);
		if (fs->dev->impl->block_isbad(fs->dev, block)) {
			if (fs->errors < dev_badpages(fs->dev)) {
				fs->errors++;
				return -EBADF;
			}
			return -EFAULT;
		}
		int res = fs->dev->impl->page_read(fs->dev, page, index);
		if (res < 0) return res;
		fs->stats.dev_reads++;
		tee_page_t *p = cache_page(fs, index);
		/* Page must match to what we read. */
		if (p->id != page_id) return -ESRCH;
		if (p->type != type) return -ENXIO;
	} else {
		/* New page, clear it. */
		tee_page_t *p = cache_page(fs, index);
		memset(p, 0, dev_pagesize(fs->dev));
		p->id = page_id;
		p->type = type;
	}
	fs->cache[index].id = page_id;
	fs->cache[index].type = type;

	return index;
}

static void first_root(tee_device_t *dev, int index, tee_id_t page)
{
	tee_root_page_t *r = dev->impl->cache(dev, index);
	r->page.id = page;
	r->page.type = TEEFS_PAGE_ROOT;
	r->blocks = dev->impl->blocks(dev);
	r->block_size = dev->impl->block_size;
	r->page_size = dev->impl->page_size;
	r->state = TEEFS_STATE_OK;
	r->first_id = page;
	r->prev_id = page;
	r->roots = 1;
	r->infos = 0;
}

int teefs_mkfs(tee_device_t *dev, int flags)
{
	(void)flags;

	if (dev_numblocks(dev) <= CONFIG_TEEFS_MAX_BAD_BLOCKS)
		return -EINVAL;

	if (dev_numpages(dev) > (1u << CONFIG_TEEFS_MAX_PAGES)) {
		/* To be able to compare page ids with wrapping the number of
		 * pages can be at most half of what we have bits in tee_id_t.
		 * For example, at most 32768 pages with 16bit tee_id_t. */
		return -EINVAL;
	}
	/*
	 * Clear all the blocks to make sure teefs_mount will work correctly
	 * in the case we wrote the root on top of an existing filesystem.
	 */
	unsigned errors = 0;
	bool created = false;
	for (tee_id_t block = 0; block < dev_numblocks(dev); block++) {
		tee_id_t page = dev_block2page(dev, block);
		if (!dev->impl->block_isbad(dev, block)) {
			if (dev->impl->block_erase(dev, block)) {
				/* Erase failed, must be bad block. */
				if (errors < CONFIG_TEEFS_MAX_BAD_BLOCKS) {
					errors++;
					continue;
				}
				return -EFAULT;
			}
		}
		if (!created) {
			/* Successful erase, create root here. */
			first_root(dev, 0, page);
			int res = dev->impl->page_prog(dev, page, 0);
			if (res < 0) return res;
			created = true;
		}
	}
	return created ? 0 : -EFAULT;
}

static int scan_roots(tee_fs_t *fs)
{
	int res = cache_read(fs, fs->head_id, TEEFS_PAGE_ROOT);
	if (res < 0) return res;
	tee_root_page_t *r = cache_root(fs, res);
	uint16_t roots = r->roots;
	tee_id_t root_id = r->page.id;
	for (int i = 0; i < roots; i++) {
		int res = cache_read(fs, root_id, TEEFS_PAGE_ROOT);
		if (res < 0) return res;
		r = cache_root(fs, res);
		root_id = fs->first_id = r->prev_id;
	}
	fs->first_id = r->first_id;
	fs->tail_id = r->page.id;

	debug("Scanned first_id %08X\n", fs->first_id);

	return 0;
}

static int mount_fs(tee_fs_t *fs, int flags)
{
	int res = 0;
	fs->flags = flags;

	/* Find the newest block by scanning first pages in each block. */
	tee_id_t pages = 0;
	bool found = false;
	for (tee_id_t block = 0; block < dev_numblocks(fs->dev); block++) {
		pages += dev_pagesinblock(fs->dev);
		if (fs->dev->impl->block_isbad(fs->dev, block)) continue;
		tee_id_t page = dev_block2page(fs->dev, block);
		res = fs->dev->impl->page_read(fs->dev, page, 0);
		if (res == -EBADF) continue; /* bad block */
		if (res < 0) return res; /* other error */
		tee_page_t *p = cache_page(fs, res);
		if (!((dev_page(fs->dev, p->id) == page) &&
		      (p->type == TEEFS_PAGE_ROOT ||
		       p->type == TEEFS_PAGE_FILE))) {
			/* Not a valid page. */
			if (!found) continue;
			break;
		}
		if (!found) {
			found = true;
			fs->first_id = fs->last_id = p->id;
			pages = 0;
			continue;
		} else if (p->id == fs->last_id + pages) {
			/* This looks good, go for the next block. */
			fs->first_id = fs->last_id = p->id;
			pages = 0;
			continue;
		}
		break;
	}
	if (!found) {
		if (flags & TEEFS_FLAG_CREATE) {
			/* Create the first root entry. */
			int index = cache_read(fs, NULL_ID, TEEFS_PAGE_ROOT);
			if (index < 0) return index;
			first_root(fs->dev, index, NULL_ID);
			fs->state = TEEFS_STATE_OK;
			fs->first_id = 0;
			fs->last_id = fs->prog_id = NULL_ID;
			update_root(fs, index);
			return 0;
		}
		return -ENOENT; /* no fs to mount */
	}
	/* Now get the newest page within the block. */
	for (unsigned i = 1; i < dev_pagesinblock(fs->dev); i++) {
		res = cache_read(fs, fs->last_id + 1, TEEFS_PAGE_ROOT);
		if (res == -ESRCH) break; /* not a valid page */
		if (res < 0 && res != -ENXIO) return res;
		/* Cache read validated page id, this is good. */
		fs->first_id = ++fs->last_id;
	}

	/* This page is the newest, scan backwards for the root. */
	for (unsigned i = 0; i < dev_numpages(fs->dev); i++) {
		while ((res = cache_read(fs, fs->first_id--, TEEFS_PAGE_ROOT)) == -EBADF);
		if (res == -ENXIO) continue; /* valid but not root */
		if (res < 0) return res;
		/* Got the newest root, validate it. */
		tee_root_page_t *r = cache_root(fs, res);
		if (r->blocks != fs->dev->impl->blocks(fs->dev) ||
		    r->block_size != fs->dev->impl->block_size ||
		    r->page_size != fs->dev->impl->page_size ||
		    r->page_size > CONFIG_TEEFS_MAX_PAGE_SIZE) {
			/* Different fs? */
			return -EFAULT;
		}
		fs->first_id = fs->head_id = r->page.id;
		fs->state = r->state;
		break;
	}

	/* Update first id and tail id. */
	res = scan_roots(fs);
	if (res < 0) return res;

	/* Sanity check for the calculated values. */
	unsigned num_pages = dev_numpages(fs->dev);
	if (num_pages < (tee_id_t)(fs->last_id - fs->first_id))
		return -EFAULT;

	fs->prog_id = fs->last_id;
	if (fs->state != TEEFS_STATE_OK) return -EROFS; /* TODO recover... */

	return 0;
}

int teefs_mount(const void *mp, size_t mplen, tee_device_t *dev, int flags)
{
	if (dev_numblocks(dev) <= CONFIG_TEEFS_MAX_BAD_BLOCKS)
		return -EINVAL;

	if (dev_numpages(dev) > (1u << CONFIG_TEEFS_MAX_PAGES)) {
		/* To be able to compare page ids with wrapping the number of
		 * pages can be at most half of what we have bits in tee_id_t.
		 * For example, at most 32768 pages with 16bit tee_id_t. */
		return -EINVAL;
	}
	lock_teefs();
	/* First mount the device. */
	int res = 0;
	int index = teedev_mount(mp, mplen, dev);
	if (index < 0) goto out;

	/* Then mount the fs. */
	res = -ENODEV;
	tee_fs_t *fs = open_mp(mp, mplen, true);
	if (!fs) goto out;
	res = mount_fs(fs, flags);
	if (res < 0) {
		/* Failed, umount the device. */
		(void)teedev_umount(mp, mplen, NULL);
	}
	close_mp(fs);
 out:
	unlock_teefs();
	return res < 0 ? res : index;
}

static void get_utilization(tee_fs_t *fs, tee_stats_t *stats)
{
	/* See has_space for these. */
	unsigned long num_pages = dev_numpages(fs->dev);
	stats->used_pages = (tee_id_t)(fs->last_id + 1 - fs->first_id);
	stats->rsvd_pages = 0;
	if (!fs->dev->impl->write_once) {
		/* Reservation to go around bad blocks. */
		stats->rsvd_pages += dev_badpages(fs->dev);
		/* Space for garbage collection to work.*/
		stats->rsvd_pages += 2 * dev_pagesinblock(fs->dev);
		/* Always make sure to have one extra block. */
		stats->rsvd_pages += dev_pagesinblock(fs->dev);
	}
	stats->free_pages = num_pages - stats->used_pages - stats->rsvd_pages;
	if (stats->free_pages > num_pages) stats->free_pages = 0;
}

int teefs_mp(int index, void *mp, size_t *mplen, tee_stats_t *stats)
{
	if (!mp || !mplen || *mplen > CONFIG_TEEFS_MAX_NAMELEN ||
	    index >= CONFIG_TEEFS_MAX_INSTANCES) return -EINVAL;

	if (index >= 0 && *mplen != CONFIG_TEEFS_MAX_NAMELEN) return -EINVAL;

	lock_teefs();
	/* Open fs to increase reference count. */
	int res = -ENODEV;
	tee_fs_t *fs = index < 0 ?
		open_mp(mp, *mplen, true) : open_mp_at(index, mp, mplen, stats);
	if (!fs) goto out;

	/* Update stats if given. */
	if (stats) {
		memcpy(stats, &fs->stats, sizeof(tee_stats_t));
		get_utilization(fs, stats);
	}
	/* And remove our reference. */
	close_mp(fs);
 out:
	unlock_teefs();
	return res;
}

static int sync_fs(tee_fs_t *fs)
{
	if (fs->state != TEEFS_STATE_OK) return -EROFS;
	while (true) {
		int res = cache_purge(fs);
		if (res == -ENOENT) break;
		if (res < 0) return res;
	}
	return 0;
}

int teefs_umount(const void *mp, size_t mplen, int flags, tee_stats_t *stats)
{
	(void)flags;

	lock_teefs();
	/* Open fs to increase reference count. */
	int res = -ENODEV;
	tee_fs_t *fs = open_mp(mp, mplen, true);
	if (!fs) goto out;

	res = sync_fs(fs);
	if (res < 0) goto out2;
	if (stats) get_utilization(fs, stats);

	/* Device umount will clear the fs instance. */
	res = teedev_umount(mp, mplen, stats);
 out2:
	close_mp(fs);
 out:
	unlock_teefs();
	return res;
}

static fnv_hash_t fnv_hash(const uint8_t *name, size_t namelen)
{
	/* See http://www.isthe.com/chongo/tech/comp/fnv/ */
	uint32_t hash = 2166136261U;
	for (uint32_t i = 0; i < namelen; i++)
		hash = (hash ^ name[i]) * 0x01000193;

	return (fnv_hash_t)hash ? (fnv_hash_t)hash :
		(fnv_hash_t)2166136261U; /* never return zero */
}

static size_t dev_namelen(tee_device_t *dev)
{
	/* Maximum number of bytes for the file name. */
	size_t file_space = dev_filespace(dev);
	return CONFIG_TEEFS_MAX_NAMELEN < file_space ?
		CONFIG_TEEFS_MAX_NAMELEN : file_space;
}

static bool has_space(tee_fs_t *fs, size_t size, bool delete)
{
	/* Make sure to have enough space for GC to work. */
	if (!delete) size += dev_namelen(fs->dev);
	tee_id_t num_pages = dev_numpages(fs->dev);
	tee_id_t free_pages = num_pages - (fs->last_id + 1 - fs->first_id);
	if (!fs->dev->impl->write_once) {
		/* Keep space for possible bad blocks. */
		free_pages -= dev_badpages(fs->dev);
	}
	if (fs->state != TEEFS_STATE_GC) {
		/* In gc we can use whatever we have, but not now. */
		if (!fs->dev->impl->write_once) {
			/* Keep space for garbage collection to work.*/
			free_pages -= 2 * dev_pagesinblock(fs->dev);
		}
		if (size) {
			/*
			 * Only teefs_unlink can have zero size here.
			 * Normally free_pages must include bad block
			 * reservation but not for delete so that we are
			 * able to remove files in a full filesystem.
			 */
			size_t space = dev_filespace(fs->dev);
			tee_id_t file_pages = (size + space) / space;
			free_pages -= file_pages;
		}
		free_pages--; /* space for root */
	}
	if (!fs->dev->impl->write_once) {
		/* Always make sure to have one extra block. */
		free_pages -= dev_pagesinblock(fs->dev);
	}
	/* Not enough space if free_pages wrapped. */
	return free_pages < num_pages;
}

static inline size_t dev_rootspace(tee_device_t *dev)
{
	/* Number of bytes for root file infos in a page. */
	return (1 << dev->impl->page_size) - sizeof(tee_root_page_t);
}

static uint16_t dev_numinfos(tee_device_t *dev)
{
	/* Maximum number of file entries in one root. */
	size_t root_space = dev_rootspace(dev);
	return root_space / sizeof(tee_file_info_t);
}

static void cache_clean_higher(tee_fs_t *fs, tee_id_t page_id)
{
	/* Invalidate all pages higher than the argument. */
	for (int i = 0; i < cache_pages(fs); i++) {
		if (IS_LARGER(fs->cache[i].id, page_id)) {
			fs->cache[i].id = 0;
			fs->cache[i].type = 0;
			fs->cache[i].dirty = false;
		}
	}
}

static int cache_purge_lower(tee_fs_t *fs, tee_id_t page_id)
{
	/* Program all pages lower that the argument. */
	while (IS_LARGER(page_id - 1, fs->prog_id)) {
		int res = cache_purge(fs);
		if (res == -ENOENT) break;
		if (res < 0) return res;
	}
	return 0;
}

static int prog_root(tee_fs_t *fs, fnv_hash_t fnv_hash, tee_id_t start_id)
{
	int index = cache_read(fs, fs->head_id, TEEFS_PAGE_ROOT);
	if (index < 0) return index;
	tee_root_page_t *r = cache_root(fs, index);

	uint16_t num_infos = dev_numinfos(fs->dev);
	bool full_root = r->infos == num_infos;
	bool add_root = !fnv_hash && fs->state == TEEFS_STATE_GC;
	bool del_root = !fnv_hash && fs->state != TEEFS_STATE_GC;

	if (full_root || add_root) {
		commit_root(fs, index);
		int res = cache_purge_lower(fs, r->page.id);
		if (res < 0) return res;
		/* Copy params from the previous root. */
		if ((r->roots + 1) == MAX_ROOTS) return -ENOSPC;
		uint8_t blocks = r->blocks;
		uint8_t block_size = r->block_size;
		uint8_t page_size = r->page_size;
		tee_id_t prev_id = r->page.id;
		uint16_t roots = r->roots + 1;
		/* Get space for the new root. */
		index = cache_read(fs, NULL_ID, TEEFS_PAGE_ROOT);
		if (index < 0) return index;
		r = cache_root(fs, index);
		/* Add new empty root page. */
		r->blocks = blocks;
		r->block_size = block_size;
		r->page_size = page_size;
		r->first_id = NULL_ID;
		r->prev_id = prev_id;
		r->roots = roots;
		r->infos = 0;
	}
	if (fnv_hash) {
		/* File operation. */
		if ((r->infos + 1) == MAX_INFOS) return -ENOSPC;
		r->info[r->infos].fnv_hash = fnv_hash;
		r->info[r->infos].old_id = start_id;
		r->info[r->infos].new_id = fs->start_id;
		r->infos++;
	} else if (del_root) {
		/* Delete root. */
		r->roots--;
	}
	r->state = fs->state;
	r->page.id = NULL_ID;
	update_root(fs, index);
	return 0;
}

static void reset_errors(tee_fs_t *fs)
{
	fs->stats.dev_errors += fs->errors;
	fs->errors = 0;
}

static int read_file(tee_file_t *file, uint8_t *data, size_t *datalen)
{
	tee_fs_t *fs = file->fs;
	reset_errors(fs);

	size_t max_namelen = dev_namelen(fs->dev);
	size_t readlen = 0;
	uint32_t offset = 0;
	tee_id_t page_id = file->start_id;
	size_t file_space = dev_filespace(fs->dev);

	size_t file_offset = file->offset;
	if (*datalen > file->datalen - file_offset)
		*datalen = file->datalen - file_offset;

	while (readlen < *datalen && file_offset < file->datalen) {
		int index;
		while ((index = cache_read(fs, page_id++, TEEFS_PAGE_FILE)) == -EBADF);
		if (index < 0) ERR_RET(index);
		tee_file_page_t *f = cache_file(fs, index);
		if (f->fnv_hash != file->fnv_hash) ERR_RET(-EFAULT);
		size_t file_namelen = f->contentlen >> NAMELEN_SHIFT;
		size_t file_datalen = f->contentlen & DATALEN_MASK;
		uint8_t *content = f->content;
		if (file_namelen) {
			/* First page. */
			if (file_namelen != file->namelen) ERR_RET(-EFAULT);
			if (file_datalen != file->datalen) ERR_RET(-EFAULT);
			content += max_namelen;
			offset = file_space - max_namelen;
		} else {
			/* Next pages. */
			if (file_namelen) ERR_RET(-EFAULT);
			if (file->datalen - offset != file_datalen)
				ERR_RET(-EFAULT);
			offset += file_space;
		}
		if (offset > file_offset) {
			/* Read data from file offset. */
			size_t len = offset - file_offset;
			if (offset < file_space) content += offset - len;
			else content += file_space - len;
			if (file_datalen < len) len = file_datalen;
			if (*datalen < readlen + len) len = *datalen - readlen;
			if (data) {
				/* Called from teefs_read. */
				memcpy(data, content, len);
				data += len;
			} else {
				/* Called from teefs_obliterate. */
				memset(content, 0xff, len);
				if (IS_LARGER_EQ(fs->prog_id, f->page.id)) {
					/* Overwrite the disk page. */
					cache_prog(fs, index, f->page.id, f->page.type);
				}
			}
			file_offset += len;
			readlen += len;
		}
	}
	*datalen = readlen;

	file->offset = file_offset;

	return (int)readlen;
}

static inline void update_first(tee_fs_t *fs, tee_id_t page_id)
{
	/* First id must be programmed. */
	if (IS_LARGER(fs->prog_id, page_id)) {
		fs->first_id = page_id;
	}
}

static int prog_file(tee_file_t *file, const uint8_t *name, size_t namelen, const uint8_t *data, size_t datalen)
{
	tee_fs_t *fs = file->fs;
	reset_errors(fs);

	/* Name must always fit to the first page. */
	size_t max_namelen = dev_namelen(fs->dev);
	if (namelen > max_namelen) namelen = max_namelen; /* truncate it */
	uint32_t old_namelen = file->namelen;
	uint32_t new_namelen = file->namelen;
	if (name && namelen) new_namelen = namelen; /* teefs_create, teefs_rename */

	uint32_t old_datalen = file->datalen;
	uint32_t new_datalen = file->datalen; /* teefs_rename, teefs_gc */
	if (data && datalen) /* teefs_write */
		if (file->offset + datalen > file->datalen)
			new_datalen = file->offset + datalen;
	if (!data && datalen) /* teefs_truncate */
		new_datalen = datalen;
	if (!name && !namelen && !data && !datalen) /* teefs_gc */
		new_datalen = file->offset;
	fnv_hash_t new_hash = file->fnv_hash;
	fnv_hash_t old_hash = file->fnv_hash;

	size_t file_space = dev_filespace(fs->dev);

	uint32_t offset = 0;
	tee_id_t page_id = file->start_id;
	bool all_cached = IS_LARGER(file->start_id, fs->prog_id);
	fs->start_id = file->start_id;

	size_t file_datalen = new_datalen;
	size_t file_namelen = new_namelen;
	size_t file_offset = file->offset;

	while (new_namelen || offset < new_datalen) {
		int index;
		tee_file_page_t *f;
		if (old_datalen || old_namelen) {
			/* Read old content. */
			while ((index = cache_read(fs, page_id++, TEEFS_PAGE_FILE)) == -EBADF);
			if (index < 0) ERR_RET(index);
			f = cache_file(fs, index);
			if (name) { /* teefs_rename */
				old_hash = f->fnv_hash;
				f->fnv_hash = new_hash;
			}
			if (!old_datalen) { /* teefs_truncate */
				memset(f->content + max_namelen, 0, file_space - max_namelen);
			}
		} else {
			/* Setup content for new data. */
			index = cache_read(fs, NULL_ID, TEEFS_PAGE_FILE);
			if (index < 0) ERR_RET(index);
			f = cache_file(fs, index);
			f->fnv_hash = new_hash;
			f->contentlen = 0;
		}
		if (f->fnv_hash != file->fnv_hash) ERR_RET(-EFAULT);
		if (!all_cached || !IS_LARGER(f->page.id, fs->prog_id)) {
			/* Cannot update, get the next page id. */
			f->page.id = ++fs->last_id;
		}
		cache_update(fs, index, f->page.id, TEEFS_PAGE_FILE);
		fs->last_id = f->page.id;
		size_t disk_namelen = f->contentlen >> NAMELEN_SHIFT;
		size_t disk_datalen = f->contentlen & DATALEN_MASK;
		f->contentlen = 0 | (new_namelen << NAMELEN_SHIFT) |
			(new_datalen - offset);
		uint8_t *content = f->content;
		if (new_namelen) {
			/* First page. */
			int res = cache_purge_lower(fs, f->page.id);
			if (res < 0) ERR_RET(res);
			fs->start_id = f->page.id;
			if (old_namelen) {
				if (disk_namelen != file->namelen)
					ERR_RET(-EFAULT);
				if (disk_datalen != file->datalen)
					ERR_RET(-EFAULT);
				old_namelen = 0;
			}
			if (name && namelen) memcpy(content, name, namelen);
			new_namelen = 0;
			content += max_namelen;
			offset = file_space - max_namelen;
		} else {
			/* Next pages. */
			if (old_datalen) {
				if (disk_namelen) ERR_RET(-EFAULT);
				if (old_datalen - offset != disk_datalen)
					ERR_RET(-EFAULT);
			}
			offset += file_space;
		}
		if (offset >= old_datalen) {
			/* Last old page. */
			old_datalen = 0;
		}
		if (offset > file_offset) {
			/* Write new data from file offset. */
			size_t len = offset - file_offset;
			if (offset < file_space) content += offset - len;
			else content += file_space - len;
			if (datalen) {
				if (data) {
					/* teefs_create, teefs_write */
					if (datalen < len) len = datalen;
					memcpy(content, data, len);
					file_offset += len;
					datalen -= len;
					data += len;
				} else {
					/* teefs_truncate */
					memset(content, 0, len);
					datalen = 0;
				}
			}
		}
		if (fs->state == TEEFS_STATE_GC) {
			/* Make room as we go. */
			update_first(fs, page_id);
		}
	}
	cache_clean_higher(fs, fs->last_id); /* teefs_truncate */
	if (!all_cached || old_hash != new_hash) {
		/* Possibly obliterate old version of the file. */
		if (fs->dev->impl->auto_obliterate &&
		    (file->namelen || file->datalen)) {
			file->offset = 0;
			file->fnv_hash = old_hash;
			size_t datalen = file->datalen;
			(void)read_file(file, NULL, &datalen);
			file->fnv_hash = new_hash;
		}
		/* Need a new root info for the file. */
		if (IS_LARGER(fs->first_id, file->start_id)) {
			file->start_id = fs->start_id; /* teefs_create */
		}
		int res = prog_root(fs, file->fnv_hash, file->start_id);
		if (res < 0) ERR_RET(res);
	}
	/* Update caller file object. */
	file->datalen = file_datalen;
	file->namelen = file_namelen;
	file->offset = file_offset;
	file->start_id = fs->start_id;
	file->dirty = true;

	return 0;
}

static bool is_deleted(tee_id_t start_id, tee_deleted_t *d)
{
	for (unsigned i = 0; i < d->num; i++)
		if (start_id == d->ids[i]) return true;
	return false;
}

static void add_deleted(tee_fs_t *fs, tee_id_t start_id, tee_deleted_t *d)
{
	/* As we go down the root chain we are interested in page ids smaller
	 * than the scanned root, which always follows the (deleted) files. */
	if (IS_LARGER_EQ(start_id, fs->first_id)) {
		if (d->num < NUM_INFOS) {
			/* Just page id add to the end. */
			debug("adding %08X\n", start_id);
			d->ids[d->num] = start_id;
			if (IS_LARGER(start_id, d->ids[d->highest_id])) {
				/* Keep track of the highest index. */
				d->highest_id = d->num;
			}
			d->num++;
		} else if (IS_LARGER(d->ids[d->highest_id], start_id)) {
			/* Replace the highest page id. */
			debug("%08X replaces %08X\n", start_id,
			      d->ids[d->highest_id]);
			d->ids[d->highest_id] = start_id;
			/* Find the new highest index. */
			d->highest_id = 0;
			for (unsigned i = 0; i < NUM_INFOS; i++) {
				if (IS_LARGER(d->ids[i], d->ids[d->highest_id])) {
					d->highest_id = i;
				}
			}
		}
	}
}

static int scan_deleted(tee_fs_t *fs)
{
	memset(&fs->deleted, 0, sizeof(tee_deleted_t));

	int res = cache_read(fs, fs->head_id, TEEFS_PAGE_ROOT);
	if (res < 0) return res;
	tee_root_page_t *r = cache_root(fs, res);
	uint16_t roots = r->roots;

	/* Scan through the root chain. */
	tee_id_t root_id = r->page.id;
	for (int i = 0; i < roots; i++) {
		int res = cache_read(fs, root_id, TEEFS_PAGE_ROOT);
		if (res < 0) return res;
		r = cache_root(fs, res);
		/* Scan the infos backwards for deleted ids. */
		debug("for root %08X\n", root_id);
		for (int i = r->infos - 1; i >= 0; i--) {
			if (r->page.id == fs->tail_id) {
				/* This is the bottom root. */
				if (find_fd(fs, r->info[i].old_id) >= 0 ||
				    find_fd(fs, r->info[i].new_id) >= 0) {
					/* There's an open fd for this root. */
					return -EBUSY;
				}
			}
			if (r->info[i].old_id != r->info[i].new_id) {
				/* Candidate for garbage collecting. */
				add_deleted(fs, r->info[i].old_id, &fs->deleted);
			}
		}
		root_id = r->prev_id;
	}
	debug("%d/%d deleted ids\n", (int)fs->deleted.num, (int)NUM_INFOS);
	return 0;
}

static int garbage_collect(tee_fs_t *fs)
{
	if (fs->dev->impl->write_once) return -ENOTSUP;

	/* Update deleted files for gc. */
	int res = scan_deleted(fs);
	if (res < 0) return res;
	if (!fs->deleted.num) return 0; /* nothing to do */

	fs->state = TEEFS_STATE_GC;

	res = cache_read(fs, fs->head_id, TEEFS_PAGE_ROOT);
	if (res < 0) return res;
	tee_root_page_t *r = cache_root(fs, res);
	if (r->roots == 1) {
		/* Only one root, create new one for gc. */
		res = prog_root(fs, 0, 0);
		if (res < 0) return res;
	}
	/* Get the bottom root. */
	res = cache_read(fs, fs->tail_id, TEEFS_PAGE_ROOT);
	if (res < 0) return res;
	r = cache_root(fs, res);

	/* Move its files to new root. */
	for (int i = 0; i < r->infos; i++) {
		if (IS_LARGER_EQ(r->info[i].new_id, fs->first_id) &&
		    !is_deleted(r->info[i].new_id, &fs->deleted)) {
			fnv_hash_t fnv_hash = r->info[i].fnv_hash;
			tee_id_t start_id = r->info[i].new_id;
			res = cache_read(fs, start_id, TEEFS_PAGE_FILE);
			if (res < 0) return res;
			tee_file_page_t *f = cache_file(fs, res);
			if (f->page.type == TEEFS_PAGE_FILE &&
			    f->fnv_hash == fnv_hash &&
			    f->contentlen >> NAMELEN_SHIFT) {
				tee_file_t file = {
					.fnv_hash = f->fnv_hash,
					.start_id = f->page.id,
					.namelen = f->contentlen >> NAMELEN_SHIFT,
					.datalen = f->contentlen & DATALEN_MASK,
					.offset = f->contentlen & DATALEN_MASK,
					.fs = fs,
				};
				/* Move this file to the top. */
				debug("Moving id %08X (%s) to the top\n",
				      start_id, f->content);
				update_first(fs, start_id); /* make room */
				if (!has_space(fs, file.datalen, false))
					return -ENOSPC;
				res = prog_file(&file, NULL, 0, NULL, 0);
				if (res < 0) return res;
			}
		}
		/* Read back the bottom root. */
		res = cache_read(fs, fs->tail_id, TEEFS_PAGE_ROOT);
		if (res < 0) return res;
		r = cache_root(fs, res);
	}

	/* Write final root with one less roots. */
	fs->state = TEEFS_STATE_OK;
	res = prog_root(fs, 0, 0);
	fs->state = TEEFS_STATE_GC;
	if (res < 0) return res;
	fs->state = TEEFS_STATE_OK;
	res = sync_fs(fs);
	if (res < 0) return res;

	/* Finally update root information. */
	res = scan_roots(fs);
	if (res < 0) return res;

	return fs->deleted.num;
}

static int make_space(tee_fs_t *fs, size_t size, bool delete)
{
	bool doesfit = has_space(fs, size, delete);
	if (fs->flags & TEEFS_FLAG_AUTOGC) {
		while (!doesfit) {
			int res = garbage_collect(fs);
			if (res == 0) break;
			if (res < 0) return res;
			doesfit = has_space(fs, size, delete);
		}
	}
	return doesfit ? 0 : -ENOSPC;
}

static int namecmp(tee_fs_t *fs, tee_id_t start_id, const void *name, size_t namelen)
{
	int res = cache_read(fs, start_id, TEEFS_PAGE_FILE);
	if (res < 0) return res; /* error */
	tee_file_page_t *f = cache_file(fs, res);

	if (!memcmp(f->content, name, namelen))
		return res; /* return cache index = match */

	return -ENOENT; /* different */
}

static int open_file(tee_file_t *file, const void *name, size_t namelen)
{
	/* Name must always fit to the first page. */
	tee_fs_t *fs = file->fs;
	size_t max_namelen = dev_namelen(fs->dev);
	if (namelen > max_namelen) namelen = max_namelen; /* truncate it */

	int res = cache_read(fs, fs->head_id, TEEFS_PAGE_ROOT);
	if (res < 0) return res;
	tee_root_page_t *r = cache_root(fs, res);
	uint16_t roots = r->roots;
	tee_id_t root_id = fs->head_id;

	/* Scan the roots for the file. */
	for (int i = 0; i < roots; i++) {
		int res = cache_read(fs, root_id, TEEFS_PAGE_ROOT);
		if (res < 0) return res;
		r = cache_root(fs, res);
		/* Scan the infos backwards for the hash. */
		for (int i = r->infos - 1; i >= 0; i--) {
			if (r->info[i].fnv_hash == file->fnv_hash) {
				/* Matching hash, compare name. */
				tee_id_t start_id = r->info[i].new_id;
				if (IS_LARGER(fs->first_id, start_id)) {
					/* Deleted but check the name. */
					start_id = r->info[i].old_id;
				}
				res = namecmp(fs, start_id, name, namelen);
				if (res == -ENOENT) {
					/* Different name, read root again. */
					int res = cache_read(fs, root_id, TEEFS_PAGE_ROOT);
					if (res < 0) return res;
					r = cache_root(fs, res);
					continue;
				}
				if (res < 0) return res;
				/* Matching name, cache has the file. */
				if (IS_LARGER(fs->first_id, start_id)) {
					/* But it's deleted. */
					return -ENOENT;
				}
				tee_file_page_t *f = cache_file(fs, res);
				file->start_id = f->page.id;
				file->namelen = f->contentlen >> NAMELEN_SHIFT;
				file->datalen = f->contentlen & DATALEN_MASK;
				file->offset = 0;
				return 0;
			}
		}
		root_id = r->prev_id;
	}
	return -ENOENT;
}

static int obliterate_file(tee_file_t *file)
{
	tee_fs_t *fs = file->fs;
	if (!fs->dev->impl->write_over) return -ENOTSUP;

	file->offset = 0;
	size_t datalen = file->datalen;
	return read_file(file, NULL, &datalen);
}

static int unlink_file(tee_file_t *file)
{
	tee_fs_t *fs = file->fs;
	if (fs->state != TEEFS_STATE_OK) return -EROFS;

	/* Check and possibly make space. */
	int res = make_space(fs, 0, true);
	if (res) return res;
	/* Program the root entry for delete. */
	fs->start_id = NULL_ID;
	res = prog_root(fs, file->fnv_hash, file->start_id);
	if (res == 0 && fs->dev->impl->auto_obliterate) {
		/* Possibly obliterate automatically. */
		(void)obliterate_file(file);
	}
	return res;
}

int teefs_create(const void *name, size_t namelen, const void *data, size_t datalen)
{
	if (!name || !namelen || (!data && datalen) ||
	    namelen > CONFIG_TEEFS_MAX_NAMELEN || datalen > TEEFS_MAX_DATALEN)
		return -EINVAL;

	lock_teefs();
	/* Open fs to increase reference count. */
	int res = -ENODEV;
	tee_fs_t *fs = open_mp(name, namelen, false);
	if (!fs) goto out;

	/* Get fd which also increases fs refcount. */
	int fd = res = open_fd(fs, name, namelen, true);
	if (fd < 0) goto out2;

	res = -EROFS;
	if (fs->state != TEEFS_STATE_OK) goto out2;

	/* The file cannot exist already. */
	res = -EEXIST;
	tee_file_t *file = fd2file(fd);
	if (file->refs != 1) goto out2;
	file->fnv_hash = fnv_hash(name, namelen);
	if (open_file(file, name, namelen) == 0) {
		file->fnv_hash = 0;
		goto out2;
	}
	/* Check and possibly make space. */
	res = make_space(fs, datalen, false);
	if (res < 0) goto out2;

	/* Create the file. */
	file->start_id = NULL_ID;
	res = prog_file(file, name, namelen, data, datalen);
	if (res < 0) goto out2;
	res = fd;
 out2:
	/* Release the fd if something failed. */
	if (res < 0) (void)close_fd(fd);
	/* Close fs to decrease reference count. */
	close_mp(fs);
 out:
	unlock_teefs();
	return res;
}

int teefs_open(const void *name, size_t namelen, int flags)
{
	if (!name || !namelen) return -EINVAL;

	lock_teefs();
	/* Open fs to increase reference count. */
	int res = -ENODEV;
	tee_fs_t *fs = open_mp(name, namelen, false);
	if (!fs) goto out;

	/* Get fd which also increases fs refcount. */
	int fd = res = open_fd(fs, name, namelen, true);
	if (fd < 0) goto out2;

	/* Open or possibly create the file. */
	tee_file_t *file = fd2file(fd);
	if (file->refs == 1) {
		file->fnv_hash = fnv_hash(name, namelen);
		res = open_file(file, name, namelen);
		if ((res == -ENOENT) && (flags & TEEFS_FLAG_CREATE)) {
			/* Check and possibly make space. */
			res = make_space(fs, 0, false);
			if (res < 0) goto out2;
			/* Create zero length file. */
			file->start_id = NULL_ID;
			res = prog_file(file, name, namelen, NULL, 0);
		}
	}
	if (res < 0) goto out2;
	res = fd;
 out2:
	/* Release the fd if something failed. */
	if (res < 0) (void)close_fd(fd);
	/* Close fs to decrease reference count. */
	close_mp(fs);
 out:
	unlock_teefs();
	return res;
}

int teefs_close(int fd)
{
	tee_file_t *file = fd2file(fd);
	if (!file) return -EINVAL;

	lock_teefs();
	tee_fs_t *fs = file->fs;
	if (file->dirty && (fs->flags & TEEFS_FLAG_AUTOSYNC)) {
		(void)sync_fs(fs);
	}
	int res = close_fd(fd);
	unlock_teefs();
	return res;
}

int teefs_unlink(int fd)
{
	tee_file_t *file = fd2file(fd);
	if (!file) return -EINVAL;

	lock_teefs();
	int res = unlink_file(file);
	unlock_teefs();
	return res;
}

int teefs_rename(int fd, const void *name, size_t namelen)
{
	tee_file_t *file = fd2file(fd);
	if (!file || !name || !namelen || namelen > CONFIG_TEEFS_MAX_NAMELEN)
		return -EINVAL;

	lock_teefs();
	/* Source and target must be on the same fs. */
	tee_fs_t *fs = open_mp(name, namelen, false);
	bool is_same_fs = (fs == file->fs);
	close_mp(fs);
	int res = -EXDEV;
	if (!is_same_fs) goto out;

	res = -EROFS;
	if (fs->state != TEEFS_STATE_OK) goto out;

	/* Is there a file with the same target name. */
	res = -EBUSY;
	int fd2 = open_fd(fs, name, namelen, false);
	if (fd2 >= 0) {
		/* Yes, and it's currently opened. */
		close_fd(fd2);
		goto out;
	}
	tee_file_t file2;
	file2.fs = fs;
	file2.fnv_hash = fnv_hash(name, namelen);
	if (open_file(&file2, name, namelen) == 0) {
		/* Delete the file with the same name. */
		(void)unlink_file(&file2);
	}
	/* Check and possibly make space. */
	res = make_space(fs, file->datalen, false);
	if (res < 0) goto out;
	/* Reprogram the file with the new name. */
	fnv_hash_t old_hash = file->fnv_hash;
	file->fnv_hash = fnv_hash(name, namelen);
	res = prog_file(file, name, namelen, NULL, 0);
	if (res < 0) {
		file->fnv_hash = old_hash;
		goto out;
	}
	/* Update fd for the new name. */
	rename_fd(fd, name, namelen);
 out:
	unlock_teefs();
	return res;
}

int teefs_read(int fd, void *data, size_t *datalen)
{
	tee_file_t *file = fd2file(fd);
	if (!file || !data || !datalen) return -EINVAL;

	lock_teefs();
	int res = read_file(file, data, datalen);
	unlock_teefs();
	return res;
}

int teefs_write(int fd, const void *data, size_t datalen)
{
	tee_file_t *file = fd2file(fd);
	if (!file || !data) return -EINVAL;
	if (!datalen) return 0; /* see write(2) with zero count */

	/* Lock the fs for actual operations. */
	lock_teefs();
	int res = -EROFS;
	tee_fs_t *fs = file->fs;
	if (fs->state != TEEFS_STATE_OK) goto out;
	res = -EINVAL;
	if (file->offset + datalen > TEEFS_MAX_DATALEN) goto out;

	/* Check and possibly make space. */
	res = make_space(fs, file->offset + datalen, false);
	if (res < 0) goto out;
	/* Reprogram the file with new contents. */
	res = prog_file(file, NULL, 0, data, datalen);
	if (res == 0) res = (int)datalen;
 out:
	unlock_teefs();
	return res;
}

int teefs_obliterate(int fd)
{
	tee_file_t *file = fd2file(fd);
	if (!file) return -EINVAL;

	lock_teefs();
	int res = obliterate_file(file);
	unlock_teefs();
	return res;
}

int teefs_truncate(int fd, size_t datalen)
{
	tee_file_t *file = fd2file(fd);
	if (!file) return -EINVAL;

	lock_teefs();
	int res = -EROFS;
	tee_fs_t *fs = file->fs;
	if (fs->state != TEEFS_STATE_OK) goto out;

	/* Check and possibly make space. */
	res = make_space(fs, datalen, false);
	if (res < 0) goto out;
	/* Reprogram the file with truncated contents. */
	file->offset = datalen;
	res = prog_file(file, NULL, 0, NULL, datalen);
 out:
	unlock_teefs();
	return res;
}

int teefs_seek(int fd, int offset, int whence)
{
	tee_file_t *file = fd2file(fd);
	if (!file) return -EINVAL;

	switch (whence) {
	case TEEFS_SEEK_SET:
		if (offset >= 0 &&
		    (offset + file->offset < TEEFS_MAX_DATALEN)) {
			file->offset = offset;
			return 0;
		}
		break;
	case TEEFS_SEEK_CUR:
		if ((offset >= 0 &&
		     (offset + file->offset < TEEFS_MAX_DATALEN)) ||
		    (offset < 0 && (size_t)offset <= file->offset)) {
			file->offset += offset;
			return 0;
		}
		break;
	case TEEFS_SEEK_END:
		if ((offset >= 0 &&
		     (offset + file->offset < TEEFS_MAX_DATALEN)) ||
		    (offset < 0 && (size_t)offset <= file->datalen)) {
			file->offset = file->datalen + offset;
			return 0;
		}
		break;
	}
	return -EINVAL;
}

size_t teefs_tell(int fd)
{
	tee_file_t *file = fd2file(fd);
	if (!file) return 0;
	return file->offset;
}

size_t teefs_stat(int fd)
{
	tee_file_t *file = fd2file(fd);
	if (!file) return 0;
	return file->datalen;
}

int teefs_error(int fd, const char **func, unsigned *line, unsigned *hash, unsigned *page)
{
	tee_file_t *file = fd2file(fd);
	if (!file) return 0;
	*func = file->func;
	*line = file->line;
	*hash = file->fnv_hash;
	*page = file->start_id;
	return file->error;
}

int teefs_opendir(const void *path, size_t pathlen)
{
	if (!path) return -EINVAL;

	lock_teefs();
	/* Open fs to increase reference count. */
	int res = -ENODEV;
	tee_fs_t *fs = open_mp(path, pathlen, false);
	if (!fs) goto out;

	/* Get dd which also increases fs refcount. */
	int dd = res = open_dd(fs);
	if (dd < 0) goto out2;

	/* Sync first to make sure possible new files added while
	 * running through teefs_readdir do not change our results. */
	res = sync_fs(fs);
	if (res < 0) goto out2;

	tee_dir_t *dir = dd2file(dd);
	res = cache_read(fs, fs->head_id, TEEFS_PAGE_ROOT);
	if (res < 0) goto out2;
	tee_root_page_t *r = cache_root(fs, res);
	dir->roots = r->roots;
	dir->infos = r->infos;
	dir->root_id = fs->head_id;
	memcpy(dir->path, path, pathlen);
	dir->pathlen = pathlen;
	res = dd;
 out2:
	/* Close fs to decrease reference count. */
	close_mp(fs);
	/* Release the dd if something failed. */
	if (res < 0) (void)close_dd(dd);
 out:
	unlock_teefs();
	return res;
}

int teefs_readdir(int dd, tee_dirent_t *entry)
{
	tee_dir_t *dir = dd2file(dd);
	if (!dir || !entry) return -EINVAL;

	/* Lock the fs for actual operations. */
	lock_teefs();
	int res = -ENOENT;

	uint16_t roots = dir->roots;
	for (int i = 0; i < roots; i++) {
		tee_fs_t *fs = dir->fs;
		res = cache_read(fs, dir->root_id, TEEFS_PAGE_ROOT);
		if (res < 0) goto out;
		tee_root_page_t *r = cache_root(fs, res);
		int infos = dir->infos ? dir->infos : r->infos;
		if (!infos) {
			/* Prepare for the next root. */
			dir->root_id = r->prev_id;
			dir->roots--;
			continue;
		}
		/* Scan the infos backwards for the files. */
		for (int i = infos - 1; i >= 0; i--) {
			dir->infos = i;
			if (!dir->infos) {
				/* Prepare for the next root. */
				dir->root_id = r->prev_id;
				dir->roots--;
			}
			if (r->info[i].old_id != r->info[i].new_id) {
				/* Make sure not to get this one later on. */
				add_deleted(fs, r->info[i].old_id, &dir->deleted);
			}
			if (IS_LARGER(fs->first_id, r->info[i].new_id)) {
				/* Skip delete entries. */
				continue;
			}
			if (IS_LARGER_EQ(r->info[i].new_id, fs->first_id) &&
			    !is_deleted(r->info[i].new_id, &dir->deleted)) {
				/* Potential candidate, check the name. */
				fnv_hash_t fnv_hash = r->info[i].fnv_hash;
				tee_id_t start_id = r->info[i].new_id;
				res = cache_read(fs, start_id, TEEFS_PAGE_FILE);
				if (res < 0) goto out;
				tee_file_page_t *f = cache_file(fs, res);
				if (f->fnv_hash == fnv_hash &&
				    f->contentlen >> NAMELEN_SHIFT) {
					size_t namelen = f->contentlen >> NAMELEN_SHIFT;
					size_t datalen = f->contentlen & DATALEN_MASK;
					res = namecmp(fs, start_id, dir->path, dir->pathlen);
					if (res == -ENOENT) continue;
					if (res < 0) goto out;
					/* Path matches, return entry. */
					memset(entry->name, 0, CONFIG_TEEFS_MAX_NAMELEN);
					memcpy(entry->name, f->content, namelen);
					entry->name[CONFIG_TEEFS_MAX_NAMELEN] = '\0';
					entry->namelen = namelen;
					entry->datalen = datalen;
					/* Return ENOSPC if gc is required. */
					res = dir->deleted.num == NUM_INFOS ?
						-ENOSPC : 0; /* zero is ok */
					goto out;
				}
				/* Restore the root. */
				res = cache_read(fs, dir->root_id, TEEFS_PAGE_ROOT);
				if (res < 0) goto out;
				r = cache_root(fs, res);
			}
		}
	}
	res = -ENOENT;
 out:
	unlock_teefs();
	return res;
}

int teefs_closedir(int dd)
{
	/* Closing the dd decrements fs refcount. */
	return close_dd(dd);
}

int teefs_gc(const void *mp, size_t mplen)
{
	lock_teefs();
	/* Open fs to increase reference count. */
	int res = -ENODEV;
	tee_fs_t *fs = open_mp(mp, mplen, true);
	if (!fs) goto out;

	res = -EROFS;
	if (fs->state != TEEFS_STATE_OK) goto out2;
	res = garbage_collect(fs);
 out2:
	close_mp(fs);
 out:
	unlock_teefs();
	return res;
}

int teefs_sync(const void *mp, size_t mplen)
{
	lock_teefs();
	tee_fs_t *fs = open_mp(mp, mplen, true);
	int res = -ENODEV;
	if (!fs) goto out;
	res = sync_fs(fs);
	close_mp(fs);
 out:
	unlock_teefs();
	return res;
}
