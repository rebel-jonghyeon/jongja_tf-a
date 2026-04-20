/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef FBOOT_SBOOT_H
#define FBOOT_SBOOT_H

/*
 * Sboot API for machine mode development (sboot).
 */

#include <stdint.h>
#include <drivers/cmrt/omc.h>
#include <drivers/cmrt/cmrt.h>
#ifdef CONFIG_WDT_CMRT
extern int wdt_cmrt_feed(const struct device *dev, int channel_id);
#endif

/**
 * Function to copy images from storage.
 *
 * Sboot implementation can override the default image loading function.
 *
 * @param dst Destination to copy the image.
 * @param src Source from where to copy, depends on the storage.
 * @param len Length of the image.
 * @return Zero on success, -ERRNO on error.
 */
extern int sboot_imgcpy(uint32_t dst, uint32_t src, size_t len);

/**
 * Function to load one image.
 *
 * Sboot implementation can override the default image loading function.
 * Will update parameters location and blob.
 *
 * @param location Location to load, depends on the storage.
 * @param blob Address in SRAM to load to.
 * @return Zero on success, -ERRNO on error.
 */
extern int sboot_load_image(uint32_t *location, uint32_t *blob);

/**
 * Function to load supervisor (tboot/autoload) image.
 *
 * Sboot implementation can override the default image loading function.
 *
 * @param location Location to load, depends on the storage.
 * @param blob Address in SRAM to load to.
 * @return Zero on success, -ERRNO on error.
 */
extern int sboot_load_supervisor(uint32_t location, uint32_t blob);

/**
 * Function to load image bundle from given location.
 *
 * Sboot implementation can override the default image loading function.
 *
 * @param location Location to load, depends on the storage.
 * @return Zero on success, -ERRNO on error.
 */
extern int sboot_load_bundle(uint32_t location);

#endif
