/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdalign.h>

#include <errno.h>
#include <hexutil.h>

#include "cri/cmrt.h"
#include "cri/cmrt/omc.h"
#include "cri/cmrt/fmc.h"

#include "teefs_cmvp.h"

#include "cri_utils.h"
#include "cmvp_sw.h"

tee_device_t *d_otp;
tee_device_t *d_ram;
uint32_t g_inout_buffer_len;
alignas(4) uint8_t g_inout_buffer[MAX_TEEFS_BUFFER_LEN];

#define TEEFS_MP_RAM "/ram/"
#define TEEFS_MP_OTP "/otp/"
#define TEEFS_MP_LEN 5 /* both are 5 bytes */

alignas(4) uint8_t mpname[CONFIG_TEEFS_MAX_NAMELEN]; /* set to 64 + 5 */

static uint8_t *make_mp_name(uint8_t *mp, uint8_t *name, uint32_t *namelen)
{
	/* Add mount point to the name. */
	memcpy(mpname, mp, TEEFS_MP_LEN);
	memcpy(mpname + TEEFS_MP_LEN, name, *namelen);
	*namelen += TEEFS_MP_LEN;
	return mpname;
}

alignas(4) uint8_t ram_buffer[CONFIG_FIPS_RAM_TEEFS_SIZE] = {0};

static int read_file(uint8_t *mp, uint32_t namelen,
		     uint8_t *name, uint8_t *inout_buffer,
		     uint32_t *inout_buffer_len)
{
	int res = -EINVAL;
	if (namelen <= 64) {
		name = make_mp_name(mp, name, &namelen);
		dhexdump("Read file with name", name, namelen);
		int fd = teefs_open(name, namelen, 0);
		if (fd >= 0) {
			*inout_buffer_len = MAX_TEEFS_BUFFER_LEN;
			res = teefs_read(fd, inout_buffer, inout_buffer_len);
			(void)teefs_close(fd);
			if (res >= 0) {
				dhexdump("Read file with data", inout_buffer, *inout_buffer_len);
				res = 0;
			} else {
				dprintk("teefs_read failed %d\n", res);
			}
		} else {
			res = fd;
			printk("teefs_open failed %d\n", res);
		}
	} else {
		printk("TEE object name must be <= 64 bytes\n");
	}
	return res;
}

static int write_file(uint8_t *mp, uint32_t namelen,
		      uint8_t *name, uint8_t *inout_buffer,
		      uint32_t *inout_buffer_len)
{
	int res = -EINVAL;
	if (namelen <= 64) {
		name = make_mp_name(mp, name, &namelen);
		dhexdump("Write file with name", name, namelen);
		int fd = teefs_create(name, namelen, inout_buffer, *inout_buffer_len);
		if (fd >= 0) {
			dhexdump("Wrote file with data", inout_buffer, *inout_buffer_len);
			res = teefs_close(fd);
		} else {
			res = fd;
			printk("teefs_create/write failed %d\n", res);
		}
	} else {
		printk("TEE object name must be <= 64 bytes\n");
	}
	return res;
}

static int delete_file_ram(uint32_t namelen, uint8_t *name)
{
	if (namelen > 64) {
		dprintk("TEE object name must be <= 64 bytes\n");
		return -EINVAL;
	}
	name = make_mp_name(TEEFS_MP_RAM, name, &namelen);

	int fd = teefs_open(name, namelen, 0);
	if (fd < 0) {
		dprintk("Cannot open the file %s %d\n", name, fd);
		return fd;
	}
	int res = teefs_unlink(fd);
	(void)teefs_close(fd);
	if (res < 0) {
		dprintk("Cannot delete file %d\n", res);
		return res;
	}

	while (teefs_gc(TEEFS_MP_RAM, TEEFS_MP_LEN) > 0) {};

	return 0;
}

static int obliterate_file_otp(uint32_t namelen, uint8_t *name)
{
	if (namelen > 64) {
		dprintk("TEE object name must be <= 64 bytes\n");
		return -EINVAL;
	}
	name = make_mp_name(TEEFS_MP_OTP, name, &namelen);

	int fd = teefs_open(name, namelen, 0);
	if (fd < 0) {
		dprintk("Cannot open the file %s %d\n", name, fd);
		return fd;
	}
	int res = teefs_obliterate(fd);
	(void)teefs_close(fd);
	if (res < 0) {
		dprintk("Cannot obliterate file %d\n", res);
		return res;
	}

	return 0;
}


#define NO_ENCRYPTION

int setup_teefs_RAM(void)
{
	/* Create and mount filesystem. */
#ifdef NO_ENCRYPTION
	u8_t *path = NULL;
	size_t pathlen = 0;
#else
	u8_t *path = "secret pin";
	size_t pathlen = strlen(path);
#endif
	u8_t blocks = find_msb_set(CONFIG_FIPS_RAM_TEEFS_SIZE >> CONFIG_TEEDEV_RAM_BLOCK_SIZE) - 1;
	d_ram = teedev_ram_open(&ram_buffer[0], blocks, path, pathlen);
	if (d_ram == NULL) {
		printk("teedev_ram_open failed!\n");
		return -EIO;
	}
	dprintk("teefs_mount: Making teefs ram for %d blocks...\n", (1 << blocks));
	int res = teefs_mkfs(d_ram, 0);
	if (res < 0) {
		printk("teefs_mkfs failed: %d!\n", res);
		return res;
	}
	res = teefs_mount(TEEFS_MP_RAM, TEEFS_MP_LEN, d_ram, 0);
	if (res < 0) {
		printk("teefs_mount failed: %d!\n", res);
		return res;
	}

	return res;
}

int dismantle_teefs_RAM(void)
{
	int res = teefs_umount(TEEFS_MP_RAM, TEEFS_MP_LEN, 0, NULL);
	if (res < 0) {
		printk("Teefs RAM unmounting failed %d\n", res);
		return res;
	}
	teedev_ram_close(d_ram);

	memset(ram_buffer, 0x00, CONFIG_FIPS_RAM_TEEFS_SIZE);

	return res;
}

#if CONFIG_FIPS_OTP_TEEFS_SIZE > 0
int dismantle_teefs_OTP(void)
{
	int res = teefs_umount(TEEFS_MP_OTP, TEEFS_MP_LEN, 0, NULL);
	if (res < 0) {
		printk("Teefs OTP unmounting failed %d\n", res);
		return res;
	}
	teedev_otp_close(d_otp);

	cri_otp_t omc = cri_otp_open(0);
	if (!cri_is_valid(omc)) {
		return -ENOENT;
	}

	memset(cri_otp_layout() + FIPS_OTP_TEEFS_OFFSET, 0xff, CONFIG_FIPS_OTP_TEEFS_SIZE);

	cri_otp_close(omc);

	return res;
}

int setup_teefs_OTP(void)
{
#ifdef NO_ENCRYPTION
	u8_t *path = NULL;
	size_t pathlen = 0;
#else
	u8_t *path = "secret pin";
	size_t pathlen = strlen(path);
#endif
	int res = -EIO;
	dprintk("cri_otp_layout() = %p\n", cri_otp_layout());
	dprintk("offset = %i\n", FIPS_OTP_TEEFS_OFFSET);
	u8_t blocks = find_msb_set(CONFIG_FIPS_OTP_TEEFS_SIZE >> CONFIG_TEEDEV_OTP_BLOCK_SIZE) - 1;
	if ((d_otp = teedev_otp_open(cri_otp_layout() + FIPS_OTP_TEEFS_OFFSET, blocks, path, pathlen)))  {
		dprintk("teefs_mount: Mounting teefs otp for %d blocks...\n", (1 << blocks));
		if ((res = teefs_mount(TEEFS_MP_OTP, TEEFS_MP_LEN, d_otp,
				       TEEFS_FLAG_CREATE | TEEFS_FLAG_AUTOSYNC)) < 0) {
			printk("teefs_mount failed: %d\n", res);
		}
	} else {
		printk("teedev_otp_open failed!\n");
	}
	return res;
}
#endif

int process_teefs_request(teefs_command_t cmd, uint32_t namelen,
		uint8_t *namebuffer, uint8_t *inout_buffer,
		uint32_t *inout_buffer_len)
{
	int res = -EINVAL;
	dprintk("Running TEEFS command %s (%d)\n", fips_command_str(cmd), cmd);

	switch (cmd) {
	case READ_FILE_RAM:
		res = read_file(TEEFS_MP_RAM, namelen, namebuffer, inout_buffer,
				inout_buffer_len);
		break;
	case READ_FILE_OTP:
		res = read_file(TEEFS_MP_OTP, namelen, namebuffer, inout_buffer,
				inout_buffer_len);
		break;
	case WRITE_FILE_RAM:
		res = write_file(TEEFS_MP_RAM, namelen, namebuffer, inout_buffer,
				 inout_buffer_len);
		break;
	case WRITE_FILE_OTP:
		res = write_file(TEEFS_MP_OTP, namelen, namebuffer, inout_buffer,
				 inout_buffer_len);
		break;
	case DELETE_RAM:
		res = delete_file_ram(namelen, namebuffer);
		break;
	case DELETE_OTP:
		res = obliterate_file_otp(namelen, namebuffer);
		break;
	default:
		dprintk("Wrong command 0x%x\n", cmd);
		break;
	}

	return res;
}

int fips_list_assets_loc(uint8_t *buffer, uint32_t maxbufferlen, uint32_t *found, fips_asset_location loc)
{
	fips_asset_list_t local_asset_list;

	int i = 0;
	int res = -EPERM;
	uint8_t *mp;
	switch (loc) {
	case FIPS_ASSET_DYNAMIC:
		mp = TEEFS_MP_RAM;
		break;
	case FIPS_ASSET_STATIC:
		mp = TEEFS_MP_OTP;
		break;
	default:
		goto out;
	}
	res = teefs_opendir(mp, TEEFS_MP_LEN);
	if (res < 0) {
		/* Mount point dismantled. */
		goto out;
	}
	int dd = res;
	while (1) {
		memset(local_asset_list.asset_name, 0x00, sizeof(local_asset_list.asset_name));
		tee_dirent_t entry;
		res = teefs_readdir(dd, &entry);
		if (res < 0) {
			if (res == -ENOENT) {
				/* No more files. */
				res = 0;
			}
			break;
		}
		printk("ls %d name %d %s\n", i, (int)entry.namelen, entry.name);

		memcpy(local_asset_list.asset_name,
		       entry.name + TEEFS_MP_LEN,
		       entry.datalen - TEEFS_MP_LEN);
		local_asset_list.asset_name_length = entry.namelen;

		if (((i + 1) * sizeof(fips_asset_list_t)) < maxbufferlen) {
			memcpy(buffer + i*sizeof(fips_asset_list_t), (uint8_t *) &local_asset_list, sizeof(fips_asset_list_t));
		} else {
			res = -EMSGSIZE;
			break;
		}
		i++;
	}
	(void)teefs_closedir(dd);
out:
	*found = i;
	return res;
}
