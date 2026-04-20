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

#include "FreeRTOS.h"
#include <stdlib.h>
#include <string.h>
#include "smmu_pmu.h"
#include "cpu.h"
#include "rl_errors.h"

uint32_t used_counter;
uint32_t smmu_pmu_events[SMMU_PMCG_MAX_COUNTERS];
static int smmu_pmcg_nctr;

/**
 * @brief Starts monitoring a specific counter.
 *
 * This function enables the specified counter by writing to the SMMU_PMCG_CNTENSET0 register.
 *
 * @param count_id Counter ID to start monitoring.
 * @return None
 */
static void smmu_pmu_counter_start(int idx)
{
	uint32_t counter_mask = 0x1 << idx;

	sys_write32(counter_mask, TCU + SMMU_PMCG_CNTENSET0);
}

/**
 * @brief Stops the specified PMCG counter.
 *
 * This function disables a PMU for the given index
 * by clearing the corresponding bit in the `SMMU_PMCG_CNTENCLR0` register.
 *
 * @param[in] idx The index of the counter to stop. This must be a valid counter index.
 * @return None
 */
static void smmu_pmu_counter_stop(int idx)
{
	sys_write32(0x1 << idx, TCU + SMMU_PMCG_CNTENCLR0);
}

/**
 * @brief Triggers a capture operation for all event counters in the PMCG.
 *
 * This function writes a capture command to the `SMMU_PMCG_CAPR` register,
 * causing all event counters in the SMMU Performance Monitoring Counter Group (PMCG)
 * to capture their current values.
 *
 * @param None
 *
 * @return None
 */
static void smmu_pmu_capture_evcntr(void)
{
	sys_write32(SMMU_PMCG_CAPTURE, TCU + SMMU_PMCG_CAPR);
}

/**
 * @brief Resets the performance monitoring counter (PMCG) at the specified index.
 *
 * This function writes a value of `0x0`(reset) to the PMCG event counter register
 * corresponding to the provided index.
 *
 * @param idx The index of the counter to reset.
 *
 */
static void smmu_pmu_reset_counter(int idx)
{
	sys_write32(0x0, TCU + SMMU_PMCG_EVCNTR(idx, 4));
}

/**
 * @brief Captures the counter value for a specific event.
 *
 * This function triggers a capture operation and retrieves the counter value
 * associated with the specified event ID.
 *
 * @param[in] evt_id The event ID for which the counter value should be captured.
 *                   This ID must correspond to an event previously configured.
 *
 * @return The captured counter value as an integer if successful.
 *         If the event ID is not found, it returns `RL_ERROR`.
 */
int smmu_pmu_capture_counter(uint32_t evt_id)
{
	smmu_pmu_capture_evcntr();

	int idx = rl_find_index(smmu_pmu_events, smmu_pmcg_nctr, evt_id);

	if (idx < 0) {
		printf("The event cannot be found\n");
		return RL_ERROR;
	}

	int cnt_val = (int)sys_read32(TCU + SMMU_PMCG_SVR(idx));

	return cnt_val;
}

/**
 * @brief Prints the counts of all enabled PMCG counters.
 *
 * This function captures and prints the current counter values and associated event IDs
 * for all enabled counters in the SMMU Performance Monitoring Counter Group (PMCG).
 *
 * @param None
 *
 * @return None
 */
void smmu_pmu_print_enabled_cnt(void)
{
	smmu_pmu_capture_evcntr();

	for (int i = 0; i < smmu_pmcg_nctr; i++) {
		if (used_counter & (0x1 << i)) {
			uint32_t cnt = sys_read32(TCU + SMMU_PMCG_SVR(i));
			uint32_t evt_id = sys_read32(TCU + SMMU_PMCG_EVTYPER(i)) & RL_GENMASK(15, 0);

			printf("\n0x%02x event: count %d\n", evt_id, cnt);
		}
	}
}

/**
 * @brief Resets the performance monitoring unit (PMU) counter corresponding
 *        to the specified event ID.
 *
 * This function locates the index of the specified event ID in the
 * `smmu_pmu_events` array. If the event ID is not found, it logs a message
 * indicating that the event has not been registered and returns an error code.
 * Otherwise, it resets the counter associated with the event ID.
 *
 * @param evt_id The event ID to reset the counter for.
 * @return RL_OK on success, RL_ERROR if the event ID is not found.
 */
int smmu_pmu_reset_counter_by_evt(uint32_t evt_id)
{
	int idx = rl_find_index(smmu_pmu_events, smmu_pmcg_nctr, evt_id);

	if (idx < 0) {
		printf("%x event has not been registered\n");
		return RL_ERROR;
	}

	smmu_pmu_reset_counter(idx);

	return RL_OK;
}

/**
 * @brief Sets the event type and span for a specified PMCG counter.
 *
 * This function configures the event type and the SID span
 * for the Performance Monitoring Counter Group (PMCG) at the specified counter index.
 *
 * @param[in] evt_id The event ID to set. This specifies the type of event to monitor.
 * @param[in] idx The index of the counter to configure.
 * @param[in] span The span value to configure the SID span for filtering.
 */
static void smmu_pmu_set_evtyper(uint32_t evt_id, uint32_t idx, uint32_t span)
{
	uint32_t val = evt_id | (span << SMMU_PMCG_SID_SPAN_SHIFT);

	sys_write32(val, TCU + SMMU_PMCG_EVTYPER(idx));
}

/**
 * @brief Clears the event type register for a specified PMCG counter index.
 *
 * This function writes a value of `0x0`(reset) to the `SMMU_PMCG_EVTYPER` register
 * for the provided index. This effectively clears the event type associated
 * with the performance monitoring counter.
 *
 * @param idx The index of the PMCG event type register to clear.
 *
 */
static void smmu_pmu_clr_evtyper(uint32_t idx)
{
	sys_write32(0x0, TCU + SMMU_PMCG_EVTYPER(idx));
}

/**
 * @brief Set StreamID to SMR
 *
 * This function sets up an StreamID
 *
 * @param sid The StreamID to monitor
 * @return None
 */
static void smmu_pmu_set_smr(uint32_t sid)
{
	sys_write32(sid, TCU + SMMU_PMCG_SMR0);
}

/**
 * @brief Adds an event to the SMMU PMU.
 *
 * This function sets up an event type and
 * starts monitoring for the specified counter ID.
 *
 * @param evt_id The type of event to monitor.
 * @return 0 on success, or a negative error code on failure.
 */
int smmu_pmu_add_evt(uint32_t evt_id)
{
	int idx = rl_find_index(smmu_pmu_events, smmu_pmcg_nctr, evt_id);

	if (idx >= 0) {
		printf("%x event has already been registered\n", evt_id);
		return RL_ERROR;
	}

	idx = rl_find_first_zero_bit(used_counter);

	if (idx < 0 || idx >= smmu_pmcg_nctr) {
		printf("All counters are in use.\n");
		return RL_ERROR;
	}

	smmu_pmu_set_evtyper(evt_id, idx, SMMU_PMCG_FLT_SID_SPAN);

	smmu_pmu_set_smr(SMMU_PMCG_ALL_SID);

	smmu_pmu_counter_start(idx);

	rl_set_bit(&used_counter, idx);

	smmu_pmu_events[idx] = evt_id;

	return RL_OK;
}

/**
 * @brief Delete an SMMU PMU event
 *
 * This function finds the index of the event in the event array using the event ID
 * and stops the event counter at the specified index.
 *
 * @param evt_id The type of event to monitor
 * @return 0 on success, or a negative error code on failure.
 */
int smmu_pmu_del_evt(uint32_t evt_id)
{
	int idx = rl_find_index(smmu_pmu_events, smmu_pmcg_nctr, evt_id);

	if (idx < 0) {
		printf("The event cannot be found\n");
		return RL_ERROR;
	}

	smmu_pmu_counter_stop(idx);

	smmu_pmu_reset_counter(idx);

	smmu_pmu_events[idx] = SMMU_PMCG_EVENT_CLEAR;

	rl_clear_bit(&used_counter, idx);

	return 0;
}

/**
 * @brief Sets the SID filter for the SMMU PMU.
 *
 * This function configures the SID filter to monitor specific stream IDs.
 *
 * @param sid Stream ID to be filtered.
 * @return None
 */
void smmu_pmu_set_filter(uint32_t sid)
{
	/* Write the SID to the appropriate register */
	sys_write32(sid, TCU + SMMU_PMCG_SMR0);
}

/**
 * @brief Enables the SMMU PMU.
 *
 * This function enables the PMU by directly setting the enable bit in the
 * control register. Since only the 0th bit is writable, there is no need
 * to preserve the other bits in the register.
 *
 * @return None
 */
int smmu_pmu_enable(void)
{
	if (smmu_pmcg_nctr != 0) {
		printf("SMMU PMU has already been enabled.\n");
		return RL_ERROR;
	}

	uint32_t nctr = sys_read32(TCU + SMMU_PMCG_CFGR) & RL_GENMASK(5, 0);

	smmu_pmcg_nctr = (int)nctr + 1;

	for (int i = 0; i < smmu_pmcg_nctr; i++) {
		smmu_pmu_events[i] = SMMU_PMCG_EVENT_CLEAR;
	}

	sys_write32(SMMU_PMU_ENABLE, TCU + SMMU_PMCG_CR);

	return RL_OK;
}

/**
 * @brief Disables the SMMU PMU.
 *
 * This function disables the PMU by directly clearing the enable bit in the
 * control register. Since only the 0th bit is writable, there is no need
 * to preserve the other bits in the register.
 *
 * @return None
 */
void smmu_pmu_disable(void)
{
	sys_write32(SMMU_PMU_DISABLE, TCU + SMMU_PMCG_CR);

	smmu_pmcg_nctr = 0;
}

/**
 * @brief Disable the SMMU Performance Monitoring Unit Counters(PMU).
 *
 *
 * @return None
 */
void smmu_pmu_reset_all_counters(void)
{
	for (int idx = 0 ; idx <= smmu_pmcg_nctr; idx++) {
		smmu_pmu_reset_counter(idx);
	}
}
