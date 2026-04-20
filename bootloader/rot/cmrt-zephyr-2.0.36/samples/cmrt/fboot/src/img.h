/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI)
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef FBOOT_IMG_H
#define FBOOT_IMG_H

#include <stdint.h>
#include <stdbool.h>

#include <cmrt/fboot/img_format.h>

/**
 * @brief Parse image footer into given parameter.
 *
 * @param blob Pointer to the image start (start of ELF).
 * @param size Size of the image (ELF + footer).
 * @param footer Pointer to struct that will hold parsed values on return.
 * @return Footer length on success, -ERRNO on error.
 */
int cmrt_img_footer_parse(void *blob, size_t size, cmrt_img_footer_t *footer);

/**
 * @brief Parse binary footer into given parameter.
 *
 * @param blob Pointer to the image start.
 * @param size Size of the image (bin + footer).
 * @param relocate Relocate footer fields.
 * @param footer Pointer to struct that will hold parsed values on return.
 * @return Footer length on success, -ERRNO on error.
 */
int cmrt_raw_footer_parse(void *blob, size_t size, bool relocate, cmrt_raw_footer_t *footer);

/**
 * @brief Clear image BSS section.
 *
 * @param footer Pointer to footer initialized with @ref cmrt_raw_footer_parse.
 */
void cmrt_raw_image_init(const cmrt_raw_footer_t *footer);

/**
 * @brief Parse container footer into given parameter.
 *
 * @param blob Pointer to the image start.
 * @param size Size of the image (bin + footer).
 * @param raw Already parsed raw footer.
 * @param footer Pointer to struct that will hold parsed values on return.
 * @return Footer length on success, -ERRNO on error.
 */
int cmrt_usr_footer_parse(void *blob, size_t size, const cmrt_raw_footer_t *raw, cmrt_usr_footer_t *footer);

#endif
