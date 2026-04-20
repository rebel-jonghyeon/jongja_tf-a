/*
 * HLOS API definitions for CMRT.
 *
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_SYSCTL_EXT_H
#define CMRT_SYSCTL_EXT_H

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/ioctl.h>
#else
#include <stdint.h>
#include <stdarg.h>

#ifndef __MINGW32__
#include <sys/ioctl.h>
#endif

#endif

/*
 * Protocol packet definitions for QEMU.
 */
#define CMRT_READ  0x10000UL
#define CMRT_WRITE 0x20000UL
#define CMRT_COMMAND_MASK 0xFFFF0000UL
#define CMRT_STATUS_MASK 0x0000FFFFUL

typedef struct {
	uint64_t offset;        /* CMRT address is 32bit but SAC can be 64bit */
	uint32_t count;         /* 0x4 for registers, word aligned for memory */
	uint32_t command;       /* CMRT_READ/WRITE, response status in low 16bits */
	/* Input/output data follow the packet header. */
} cmrt_packet_t;

/*
 * Max data size is limited by Unix domain socket payload size.
 * Currently with Ubuntu 18.04 it is 212992 bytes by default.
 */
#define CMRT_MAX_PACKET (200 * 1024)
#define CMRT_MAX_DATA (CMRT_MAX_PACKET - sizeof(cmrt_packet_t))

/*
 * Definitions for FPGA driver.
 */
#define CMRT_DEVICE "/dev/cmrt2"
#define CMRT_MAJORNO 123UL

/*
 * Definitions for QEMU driver.
 */
#define CMRT_SERVER_MAIN "cmrt_server.main"

/*
 * API to access the FPGA device driver or QEMU server socket.
 * The main purpose of this API is to hide the differences in FPGA and QEMU.
 * The API or the library can have static variables, and it's not thread
 * protected.
 */

/**
 * @brief Open CMRT device, see open(2) for the FPGA.
 *
 * Open connection to the device driver controlling access to SIC registers,
 * SAC memory and backdoor memories. Open can be called many times but typically
 * one would call it once in a process.
 *
 * @param pathname Device name, use CMRT_DEVICE.
 * @param flags O_RDWR for normal operation.
 * @retval File descriptor on success. Can be used in poll(2) for irq mode.
 * @retval -1 on error with errno set.
 */
int cmrt_open(const char *pathname, int flags);

/**
 * @brief Close CMRT device, see close(2) for the FPGA.
 *
 * Reverse of open. Note that possible register mmaps need to be closed
 * separately using munmap(2).
 *
 * @param fd File descriptor from open.
 * @retval Zero on success.
 * @retval -1 on error with errno set.
 */
int cmrt_close(int fd);


/**
 * @brief Read CMRT memory, see pread(2) for the FPGA.
 *
 * CMRT has 32bit internal addresses but the SAC memory can be 64bit.
 *
 * Reading R_SYSCTL_SOC_INTERRUPT_OUT blocks until there's an interrupt.
 *
 * @param fd File descriptor from open.
 * @param buf Pointer to the buffer to read to.
 * @param count Number of bytes to read.
 * @param offset The memory address in CMRT from where to read.
 * @retval Number of bytes read.
 * @retval -1 on error with errno set.
 */
ssize_t cmrt_pread(int fd, void *buf, size_t count, off_t offset);

/**
 * @brief Write CMRT memory, see pwrite(2) for the FPGA.
 *
 * CMRT has 32bit internal addresses but the SAC memory can be 64bit.
 *
 * Writing R_SYSCTL_SOC_INTERRUPT_OUT sets an interrupt mask for the
 * process. One can use poll(2) or select(2) on the device fd to wait
 * for an active interrupt.
 *
 * @param fd File descriptor from open.
 * @param buf Pointer to the buffer to write from.
 * @param count Number of bytes to write.
 * @param offset The memory address in CMRT where to write.
 * @retval Number of bytes written.
 * @retval -1 on error with errno set.
 */
ssize_t cmrt_pwrite(int fd, const void *buf, size_t count, off_t offset);

/**
 * @brief Memory map CMRT address space, see mmap(2) for the FPGA.
 *
 * Caller should prepare for not getting the mmap, because the driver may
 * not support it.
 *
 * @param addr Typically NULL.
 * @param length Size of mapping, sysconf(_SC_PAGE_SIZE) for registers.
 * @param prot Typically PROT_READ | PROT_WRITE.
 * @param flags Typically MAP_SHARED.
 * @param fd File descriptor from open.
 * @param offset CMRT register or memory base.
 * @retval Pointer to the CMRT register or memory base.
 * @retval MAP_FAILED on error with errno set.
 */
void *cmrt_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

/**
 * @brief The reverse of mmap, see munmap(2) for the FPGA.
 *
 * @param addr Retured pointer from mmap.
 * @param length Size of mapping, sysconf(_SC_PAGE_SIZE) for registers.
 * @retval 0 on success.
 * @retval -1 on error with errno set.
 */
int cmrt_munmap(void *addr, size_t length);

#ifndef CMRT_QEMU
#define cmrt_open open
#define cmrt_close close
#define cmrt_lseek lseek
#define cmrt_pread pread
#define cmrt_pwrite pwrite
#define cmrt_mmap mmap
#define cmrt_munmap munmap
#endif

#endif
