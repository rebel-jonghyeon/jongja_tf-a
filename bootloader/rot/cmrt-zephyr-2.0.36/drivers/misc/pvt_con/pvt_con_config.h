/*
 * Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */

#pragma once

/* Hardware Configurations */
#define PVT_N_INSTANCE	(5)
	/* Voltage */
#define PVT_VOLTAGE_N_SENSOR	(16)
#define PVT_VOLTAGE_N_BIT		(12)
#define PVT_VOLTAGE_N_PAST		(16)
#define PVT_VOLTAGE_OFFSET		(0x40U)
	/* Temperature */
#define PVT_TEMPERATURE_N_RISE		(8)
#define PVT_TEMPERATURE_N_FALL		(8)
#define PVT_TEMPERATURE_N_RISE_FALL	(PVT_TEMPERATURE_N_RISE + PVT_TEMPERATURE_N_FALL)
#define PVT_TEMPERATURE_N_SENSOR	(16)
#define PVT_TEMPERATURE_N			(12)
#define PVT_TEMPERATURE_N_PAST		(16)
#define PVT_TEMPERATURE_OFFSET		(0x80U)
#define PVT_TEMPERATURE_N_CALLBACKS	(PVT_N_INSTANCE * \
				PVT_TEMPERATURE_N_SENSOR * PVT_TEMPERATURE_N_RISE_FALL)
	/* Process */
#define PVT_PROCESS_N_SENSOR	(32)
#define PVT_PROCESS_N			(12)
#define PVT_PROCESS_N_PAST		(16)
#define PVT_PROCESS_OFFSET		(0x40U)

/* Common */
#define PVT_IS_VALID_INSTANCE(_instance)	\
				((0 <= (_instance)) && ((_instance) < PVT_N_INSTANCE))
	/* Common Macros for overall PVT operations */
#define PVT_DISABLE		(0U)
#define PVT_ENABLE		(1U)
#define PVT_CLEAR		(1U)

	/* TRIMINFO_CONTROL */
#define PVT_REGISTERING		(0U)
#define PVT_BYPASS			(1U)

	/* ADC_CONTROL */
	/* TODO: How to use & What's for? */
#define PVT_DIGITAL_MONITORING	(0U)
#define PVT_ANALOG_MONITORING	(1U)

	/* PVT_CONTROL */
#define PVT_NONE_AVERAGE		(0b00U)	/* Normal Mode */
#define PVT_TWO_AVERAGE			(0b01U)
#define PVT_FOUR_AVERAGE		(0b10U)
#define PVT_EIGHT_AVERAGE		(0b11U)

#define PVT_EXCEED_ONLY_CURRENT		(0b000U)
#define PVT_EXCEED_TWO_PAST			(0b010U)
#define PVT_EXCEED_FOUR_PAST		(0b100U)
#define PVT_EXCEED_EIGHT_PAST		(0b101U)
#define PVT_EXCEED_TWELVE_PAST		(0b110U)
#define PVT_EXCEED_ALL_PAST			(0b111U)

#define PVT_TEMPERATURE_MODE	(0U)
#define PVT_VOLTAGE_MODE		(1U)

	/* SAMPLING_INTERVAL */
	/* TODO: Add oscillator frequency */
#define PVT_SAMPLING_INTERVAL_5MS	(0x000F4240U)	/* 0x000F_4240 = 1,000,000 */
#define PVT_SAMPLING_INTERVAL_10MS	(0x001E8480U)	/* 0x001E_8480 = 2,000,000 */

	/* SETUP_TIME_CNT */

	/* HANDSHAE_ON_EXP_CNT */

	/* PVT_CON_STATUS */

	/* EMUL_CON */

	/* HANDSHAKE_OFF_EXP_CNT */

	/* SOC_WAIT_INTERVAL */

/* Voltage */
	/* Macros for PVT voltage  reigsters */
#define PVT_VOLTAGE_IS_VALID_SENSOR_ID(_sensor_id)	\
				((0 <= (_sensor_id)) && ((_sensor_id) < PVT_VOLTAGE_N_SENSOR))
#define PVT_VOLTAGE_IS_VALID_PAST_INDEX(_idx)		\
				((0 <= (_idx)) && ((_idx) < PVT_VOLTAGE_N_PAST))

	/* Vr_TRIMINFO */

	/* Vr_PROBE_EN_VS */
#define PVT_VOLTAGE_RANGE_045V_090V	(0b0)	/* 0.45V - 0.90V (Default) */
#define PVT_VOLTAGE_RANGE_025V_050V	(0b1)	/* 0.25V - 0.50V */

	/* Vr_CURRENT_VOL */

	/* Vr_VS_STATUS */

	/* Vr_PAST_VOL */

/* Temperature */
	/* Macros for PVT temperature registers */
#define PVT_TEMPERATURE_IS_VALID_SENSOR_ID(_sensor_id)	\
				((0 <= (_sensor_id)) && ((_sensor_id) < PVT_TEMPERATURE_N_SENSOR))
#define PVT_TEMPERATURE_IS_VALID_RISE_FALL(_idx)		\
				((0 <= (_idx)) && ((_idx) < PVT_TEMPERATURE_N_RISE_FALL))
#define PVT_TEMPERATURE_IS_VALID_FALL_INDEX(_idx)		\
				((0 <= (_idx)) && ((_idx) < PVT_TEMPERATURE_N_FALL))
#define PVT_TEMPERATURE_IS_VALID_RISE_INDEX(_idx)		\
				((0 <= (_idx)) && ((_idx) < PVT_TEMPERATURE_N_RISE))
#define PVT_TEMPERATURE_CALLBACK_INDEX(_instance, _sensor_id, _rise_fall)	\
				(((((_instance) * PVT_TEMPERATURE_N_SENSOR) + \
					(_sensor_id)) * PVT_TEMPERATURE_N_RISE_FALL) + \
					(_rise_fall))
#define PVT_TEMPERATURE_IS_VALID_CALLBACK_INDEX(_callback_index)	\
				((0 <= (_callback_index)) && ((_callback_index) < PVT_TEMPERATURE_N_CALLBACKS))

	/* PVT_CONTROL */
#define PVT_TEMPERATURE_ONLY_CURRENT_TEMP		(0b000)
#define PVT_TEMPREATURE_4_PAST_TEMP				(0b100)
#define PVT_TEMPERATURE_8_PAST_TEMP				(0b101)
#define PVT_TEMPERATURE_12_PAST_TEMP			(0b110)
#define PVT_TEMPERATURE_16_PAST_TEMP			(0b111)

	/* Tr_TRIMINFO1 */

	/* Tr_TRIMINFO2 */

	/* Tr_PROBE_EN_TS */

	/* Tr_INTEN */

	/* Tr_INTPEND */

	/* Tr_INTSTAT */

	/* Tr_THRESHOLD_TEMP_RISE */

	/* Tr_THRESHOLD_TEMP_FALL */

	/* Tr_CURRENT_TEMP */

	/* Tr_TS_STATUS */

	/* Tr_PAST_TEMP */

/* Process */
	/* Macros for PVT process registers */
#define PVT_PROCESS_IS_VALID_SENSOR_ID(_sensor_id)	\
				((0 <= (_sensor_id)) && ((_sensor_id) < PVT_PROCESS_N_SENSOR))
#define PVT_PROCESS_IS_VALID_INDEX(_idx)			\
				((0 <= (_idx)) && ((_idx) < PVT_PROCESS_N_PAST))

	/* Pr_TRIMINFO */

	/* Pr_PROBE_EN_PS */
#define PVT_PROCESS_NORMAL_OUTPUT	(0U)	/* Default */
#define PVT_PROCESS_HALF_OUTPUT		(1U)

	/* Pr_CURRENT_PROC */

	/* Pr_PS_STATUS */

	/* Pr_PAST_PROC */
