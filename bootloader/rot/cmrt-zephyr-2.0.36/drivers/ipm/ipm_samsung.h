/*
 * Copyright (c) 2019 Linaro Limited
 * Copyright (c) 2024 Samsung Electronics Co, Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_IPM_IPM_SAMSUNG_H_
#define ZEPHYR_DRIVERS_IPM_IPM_SAMSUNG_H_

#include <kernel.h>
#include <drivers/ipm.h>
#include <device.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Mailbox Channel number */
#define PCIE_IDE_FROM_ROT_CHANNEL	(21)
#define PCIE_IDE_FROM_CM7_CHANNEL	(22)

enum {
	CPU0,
	CPU1
};

typedef void (*ipm_samsung_callback_t)(const struct device *ipmdev, const int chan);
typedef int (*ipm_samsung_send_t)(const struct device *ipmdev, const uint32_t target_id,
								  const int channel, const uint32_t cpu_id);
typedef int (*ipm_samsung_write_t)(const struct device *ipmdev, const uint32_t target_id,
								   const void *data, const int size,
								   const int issr_index);
typedef int (*ipm_samsung_receive_t)(const struct device *ipmdev, void *data, const int size,
									 const int issr_index);
typedef void (*ipm_samsung_register_callback_t)(const struct device *ipmdev,
												ipm_samsung_callback_t cb);

struct ipm_samsung_api {
	struct ipm_driver_api api;
	ipm_samsung_send_t send;
	ipm_samsung_write_t write;
	ipm_samsung_receive_t receive;
	ipm_samsung_register_callback_t register_callback;
};

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_DRIVERS_IPM_IPM_SAMSUNG_H_ */
