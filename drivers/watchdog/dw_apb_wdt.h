/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#pragma once
struct wdt_dev;

/**
 * @fn		uint32_t dw_apb_wdt_get_version(volatile struct wdt_dev *dev)
 * @brief	Get a version of the current wdt IP, will be used to verify whether
 *			IP access is possible or not on the driver level
 * @param	wdt: a structure of wdt device including platform level config
 * @return	an IP version information in 32bit data
 */
uint32_t dw_apb_wdt_get_version(volatile struct wdt_dev *dev);

/**
 * @fn		uint32_t dw_apb_wdt_get_enabled(volatile struct wdt_dev *dev)
 * @brief	Check if wdt was already enabled.
 * @param	wdt: a structure of wdt device including platform level config
 * @return	0 when the wdt was disabled, 1 when the wdt was enabled
 */
uint32_t dw_apb_wdt_get_enabled(volatile struct wdt_dev *dev);

/**
 * @fn		void dw_apb_wdt_set_timeout(volatile struct wdt_dev *dev, uint32_t timeout)
 * @brief	Set a timeout condition for wdt
 * @param	wdt: a structure of wdt device including platform level config
 * @param	timeout: a timeout condition in msec unit
 * @return	None
 */
void dw_apb_wdt_set_timeout(volatile struct wdt_dev *dev, uint32_t timeout);

/**
 * @fn		void dw_apb_wdt_set_rmod(volatile struct wdt_dev *dev, uint32_t rmod)
 * @brief	Set a response mode as reset or interrupt
 * @param	wdt: a structure of wdt device including platform level config
 * @param	rmod: a response mode (0: Reset / 1: Interrupt)
 * @return	None
 */
void dw_apb_wdt_set_rmod(volatile struct wdt_dev *dev, uint32_t rmod);

/**
 * @fn		void dw_apb_wdt_enable(volatile struct wdt_dev *dev)
 * @brief	Enable wdt timer
 * @param	wdt: a structure of wdt device including platform level config
 * @return	None
 */
void dw_apb_wdt_enable(volatile struct wdt_dev *dev);

/**
 * @fn		void dw_apb_wdt_disable(volatile struct wdt_dev *dev)
 * @brief	Pause a timer via a glue logic in order to appear as if it's disabled
 * @param	wdt: a structure of wdt device including platform level config
 * @return	None
 */
void dw_apb_wdt_disable(volatile struct wdt_dev *dev);

/**
 * @fn		void dw_apb_wdt_kick(volatile struct wdt_dev *dev)
 * @brief	Kick(feed) a wdt to re-load a timer value
 * @param	wdt: a structure of wdt device including platform level config
 * @return	None
 */
void dw_apb_wdt_kick(volatile struct wdt_dev *dev);
