/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef FBOOT_SUPERVISOR_H
#define FBOOT_SUPERVISOR_H

#include <stdint.h>
#include <stdbool.h>

#include <cmrt/fboot/img_format.h>
#include <cmrt/fboot/img_version.h>

#include <device.h>

#define CMRT_SOG_BASE DT_REG_ADDR(DT_CHOSEN(zephyr_flash))
#define CMRT_SOG_SIZE DT_REG_SIZE(DT_CHOSEN(zephyr_flash))

#define ROM_BASE CMRT_SOG_BASE
#if defined(CONFIG_CMRT_SBOOT_IN_ROM) || defined(CONFIG_CMRT_SUPERVISOR_IN_ROM)
#define ROM_END (RISCV_ROM_BASE + RISCV_ROM_SIZE)
#define MACHINE_ROM_END (RISCV_ROM_BASE + CONFIG_CMRT_MACHINE_ROM_SIZE)
#else
#define ROM_END (CMRT_SOG_BASE + CMRT_SOG_SIZE)
#define MACHINE_ROM_END ROM_END
#endif
#define RAM_BASE CONFIG_SRAM_BASE_ADDRESS
#define RAM_END (CONFIG_SRAM_BASE_ADDRESS + KB(CONFIG_SRAM_SIZE))

#define IS_IN_ROM(a) ((a) > (uint32_t)ROM_BASE && (a) < (uint32_t)ROM_END)
#define IS_IN_RAM(a) ((a) > (uint32_t)RAM_BASE && (a) < (uint32_t)RAM_END)

/**
 * @brief Check for supervisor
 *
 * @return True if supervisor exists
 */
bool has_supervisor(void);

/**
 * @brief Return supervisor root id
 *
 * @return Supervisor root id or NULL
 */
cmrt_omc_root_id_t *supervisor_root(void);

/**
 * @brief Check for tboot
 *
 * @return True if tboot exists
 */
bool has_tboot(void);

/**
 * @brief Execute supervisor mode software.
 *
 * Drops current privilege level to supervisor mode and start executing
 * at @p startaddr with interrupts disabled.
 *
 * @param startaddr Pointer to supervisor entry point.
 * @return Does not return.
 */
int start_supervisor(void *startaddr);

/**
 * @brief Update supervisor settings.
 *
 * @param size Image size.
 * @param footer Parsed image footer.
 * @param raw Parsed raw footer.
 */
void supervisor_update(size_t size, cmrt_img_footer_t *footer, const cmrt_raw_footer_t *raw);

/**
 * @brief Get image start.
 *
 * @param image CMRT_TBOOT_VERSION or CMRT_SUPERVISOR_VERSION
 * @return Pointer to image version start.
 */
uint32_t *supervisor_image(enum cmrt_image_version_id image);

/**
 * @brief Start supervisor when waking up from sleep.
 *
 * @param bbv Boot bypass vector
 * @return Zero on success, -ERRNO on error.
 */
int supervisor_bootbypass(void *bbv);

/**
 * @brief Set temporary MPU rules for sboot execution.
 *
 * @param raw Sboot raw footer
 */
void sboot_bootstrap(const cmrt_raw_footer_t *raw);

/**
 * @brief Revert temporary MPU rules for sboot execution.
 */
void undo_sboot_bootstrap(void);

#endif
