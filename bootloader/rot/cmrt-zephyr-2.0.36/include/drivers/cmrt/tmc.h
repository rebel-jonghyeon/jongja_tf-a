/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file tmc.h
 *
 * @brief Public APIs for the TMC driver.
 */

#ifndef CMRT_TMC_H
#define CMRT_TMC_H

/**
 * @brief TMC Interface
 * @defgroup tmc_interface TMC Interface
 * @ingroup io_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <device.h>
#include <drivers/cmrt/tmc_reg.h>

#ifdef __ZEPHYR__
#define CMRT_TMC_EIP76_TRNG DT_PROP(DT_NODELABEL(tmc), eip76_trng)
#define CMRT_TMC_EXT_ENTROPY DT_PROP(DT_NODELABEL(tmc), tmc_ext_entropy)
#endif

typedef struct cmrt_tmc_context *cmrt_tmc_t;

typedef enum cmrt_tmc_command_e {
	CMRT_TMC_GENERATE = TMC_CONTROL_GENERATE,
	CMRT_TMC_INSTANTIATE = TMC_CONTROL_INSTANTIATE,
	CMRT_TMC_RESEED_GENERATE = TMC_CONTROL_RESEED_GENERATE,
	CMRT_TMC_UNINSTANTIATE = TMC_CONTROL_UNINSTANTIATE,
	CMRT_TMC_RESEED = TMC_CONTROL_RESEED,
	CMRT_TMC_HEALTH_CHECK = TMC_CONTROL_HEALTH_CHECK,
} cmrt_tmc_command_t;

typedef struct cmrt_tmc_init_params {
	/** EIP-76 config word written to TRNG_CONFIG
	 *  For example: 0x0002 0102
	 *               Sample Cycles is 0x0002
	 *               Read timeout is 0
	 *               Sample Div is 0x1
	 *               Scale is 0 (no multiplier applied)
	 *               Nosie blocks is 0x2 */
	uint32_t config;
	/** EIP-76 control word written to TRNG_CONTROL
	 *  For example: 0x0000 0400
	 *               Min entropy ratio 2 */
	uint32_t control;
	/** EIP-76 does automatic detuning.
	 * This defines the limit of detunes in one operation.
	 * CMRT will panic if the given limit is exceeded. */
	uint32_t detune_limit;
} cmrt_tmc_init_params_t;

/**
 * @brief Call back function prototype for feeding external entropy.
 *
 * @return 32bits entropy.
 */
typedef uint32_t (*cmrt_tmc_get_entropy_t)(void);

/**
 * @brief Open TMC for subsequent operations.
 *
 * Open and reserve TMC context. May block for it to be available.
 *
 * @param flags Zero to call cmrt_tmc_sync after an operation,
 *              CMRT_O_SYNC to autosync all operations.
 *              CMRT_O_ASYNC may be used in initialization.
 * @param arg Parameters for initialization, NULL otherwise.
 * @return Context handle on success or NULL on error.
 */
__syscall cmrt_tmc_t cmrt_tmc_open(uint32_t flags, void *arg);

/**
 * @brief Close TMC, reverse of open.
 *
 * Close and free previously opened TMC.
 *
 * @param context Pointer to the device.
 */
__syscall void cmrt_tmc_close(cmrt_tmc_t context);

/**
 * @brief Issue TMC command.
 *
 * Typically only CMRT_TMC_GENERATE and CMRT_TMC_RESEED_GENERATE are used,
 * both give 256 bits of output. TMC has an internal entropy source where
 * it gets the new seed.
 *
 * Depending on the command output can be placed into the given buffer.
 * Caller must call cmrt_tmc_sync until the result is valid,
 * or CMRT_O_SYNC must be set in cmrt_tmc_open.
 *
 * @param context Pointer to the device.
 * @param command TMC command to run.
 * @param buffer Output buffer for generated data. For commands without data output must be NULL.
 * @param size Buffer size in bytes, currently max. TMC_OUTPUT_SIZE bytes.
 *             For commands without data output must be 0.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_tmc_command(cmrt_tmc_t context, cmrt_tmc_command_t command, void *buffer, size_t size);

/**
 * @brief Get TMC result.
 *
 * Get TMC result, wait for it to finish.
 *
 * @param context Pointer to the device.
 * @return Zero on success, -ERRNO on error.
 */
__syscall int cmrt_tmc_sync(cmrt_tmc_t context);

/**
 * @brief Set external entropy source.
 *
 * If type is set to TMC_EXT_CTRL_EXT_ONLY or TMC_EXT_CTRL_MIXED, caller
 * should provide an external entropy callback function which returns
 * 32bits of entropy on each call.
 *
 * If type is set to TMC_EXT_CTRL_NRBG_ONLY, the cb parameter is ignored.
 *
 * @param context Pointer to the device.
 * @param type    One of TMC_EXT_CTRL_NRBG_ONLY, TMC_EXT_CTRL_EXT_ONLY,
 *		  and TMC_EXT_CTRL_MIXED.
 *		  TMC_EXT_CTRL_NRBG_ONLY: use NRBG only.
 *		  TMC_EXT_CTRL_EXT_ONLY:  use external entropy only.
 *		  TMC_EXT_CTRL_MIXED:     use mixed entropy source.
 * @param cb	  Callback function, called when external entropy is needed.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_tmc_set_ext_entropy(cmrt_tmc_t context, uint32_t type, cmrt_tmc_get_entropy_t cb);

#ifdef __cplusplus
}
#endif

#include <syscalls/tmc.h>

#endif
/** @}*/
