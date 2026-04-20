#pragma once
#include "ipm_samsung.h"

/* Mailbox Channel number */
#define DRAM_INIT_DONE_CHANNEL (11)

enum _MAILBOX_ID {
	IDX_MAILBOX_START,
	IDX_MAILBOX_M0 = IDX_MAILBOX_START,
	IDX_MAILBOX_CP0_M3,
	IDX_MAILBOX_CP0_M4,
	IDX_MAILBOX_CP1_M3,
	IDX_MAILBOX_CP1_M4,
	IDX_MAILBOX_CP0_M4_C3,
	IDX_MAILBOX_END,
};

enum _CPU_ID {
	M_CPU0,
	M_CPU1
};

/**
 * @fn		int ipm_samsung_receive(int inst, void *data, int size, int issr_index)
 * @brief	Read data from the samsung mailbox
 * @param   inst: mailbox instance number
 * @param   data: pointer to buffer where incoming data should be stored
 * @param   size: maximum amount of data to receive
 * @param   issr_index: index of the ISSR register associated with this message
 * @return  The size of the received data
 */
int ipm_samsung_receive(const int inst, void *data, const int size, const int issr_index);

/**
 * @fn		int ipm_samsung_write(int inst, const void *data, int size, int issr_index)
 * @brief	Write data to the samsung mailbox
 * @param   inst: mailbox instance number
 * @param   target_id: The ID of the chiplet that wants to receive messages through the mailbox.
 * @param   data: pointer to outgoing data
 * @param   size: length of outgoing data
 * @param   issr_index: index of the ISSR register associated with this message
 * @return  The size of the data transmitted
 */
int ipm_samsung_write(const int inst, const uint32_t target_id, const void *data, const int size,
					  const int issr_index);

/**
 * @fn		int ipm_samsung_send(int inst, int channel, uint32_t cpu_id)
 * @brief	Generate the interrupt specified by the channel with the inputted cpu
 * @param   inst: mailbox instance number
 * @param   target_id: The ID of the chiplet that wants to receive messages through the mailbox.
 * @param   channel: specifies which logical channel to send the message on
 * @param   cpu_id: ID of the CPU to send the message to
 * @return  0 on success
 */
int ipm_samsung_send(const int inst, const uint32_t target_id, const int channel,
					 const uint32_t cpu_id);
