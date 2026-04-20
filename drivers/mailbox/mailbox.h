#pragma once
#include "ipm_samsung.h"

/* Mailbox Channel number */
#define DEFAULT_M_CHANNEL			(1)
#define DRAM_INIT_DONE_CHANNEL		(11)
#ifdef __TEST
#ifdef __TARGET_PCIE
#define PCIE_IDE_FROM_ROT_CHANNEL	(21)
#define PCIE_IDE_FROM_CM7_CHANNEL	(22)
#else /* __TARGET_PCIE */
#define SYSTEM_TEST_CHANNEL			(23)
#define IMG_UPDATE_CHANNEL			(24)
#endif /* __TARGET_CP */
#define TEST_CHANNEL				(31)
#endif /* __TEST */

#define RBLN_CHANNEL	(16)

/* Mailbox index number */
#define DEFAULT_M_INDEX				(1)

/* Default mailbox data size */
#define SIZEOF_M_DATA				(4)

enum _MAILBOX_ID {
	IDX_MAILBOX_START,
#if defined __TARGET_PCIE
	IDX_MAILBOX_M2 = IDX_MAILBOX_START,
	IDX_MAILBOX_CP0_M4,
	IDX_MAILBOX_CP1_M4,
	IDX_MAILBOX_CP0_M4_C3,

	IDX_MAILBOX_PCIE_START,
	IDX_MAILBOX_PCIE_VF0 = IDX_MAILBOX_PCIE_START,
	IDX_MAILBOX_PCIE_VF1,
	IDX_MAILBOX_PCIE_VF2,
	IDX_MAILBOX_PCIE_VF3,
	IDX_MAILBOX_PCIE_VF4,
	IDX_MAILBOX_PCIE_VF5,
	IDX_MAILBOX_PCIE_VF6,
	IDX_MAILBOX_PCIE_VF7,
	IDX_MAILBOX_PCIE_VF8,
	IDX_MAILBOX_PCIE_VF9,
	IDX_MAILBOX_PCIE_VF10,
	IDX_MAILBOX_PCIE_VF11,
	IDX_MAILBOX_PCIE_VF12,
	IDX_MAILBOX_PCIE_VF13,
	IDX_MAILBOX_PCIE_VF14,
	IDX_MAILBOX_PCIE_VF15,
	IDX_MAILBOX_PCIE_PF,
#elif (__TARGET_CP == 0)
	IDX_MAILBOX_M0 = IDX_MAILBOX_START,
	IDX_MAILBOX_CP0_M3,
	IDX_MAILBOX_CP0_M4,
	IDX_MAILBOX_CP1_M3,
	IDX_MAILBOX_CP1_M4,

	IDX_MAILBOX_PERI0_START,
	IDX_MAILBOX_PERI0_M5 = IDX_MAILBOX_PERI0_START,
	IDX_MAILBOX_PERI0_M7_CPU0,
	IDX_MAILBOX_PERI0_M7_CPU1,
	IDX_MAILBOX_PERI0_M8_CPU0,
	IDX_MAILBOX_PERI0_M8_CPU1,
	IDX_MAILBOX_PERI0_M9_CPU0,
	IDX_MAILBOX_PERI0_M9_CPU1,
	IDX_MAILBOX_PERI0_M10_CPU0,
	IDX_MAILBOX_PERI0_M10_CPU1,
	IDX_MAILBOX_PERI0_M11_CPU0,
	IDX_MAILBOX_PERI0_M11_CPU1,
	IDX_MAILBOX_PERI0_M12_CPU0,
	IDX_MAILBOX_PERI0_M12_CPU1,

	IDX_MAILBOX_PERI1_START,
	IDX_MAILBOX_PERI1_M7_CPU0 = IDX_MAILBOX_PERI1_START,
	IDX_MAILBOX_PERI1_M7_CPU1,
	IDX_MAILBOX_PERI1_M8_CPU0,
	IDX_MAILBOX_PERI1_M8_CPU1,
	IDX_MAILBOX_PERI1_M9_CPU0,
	IDX_MAILBOX_PERI1_M9_CPU1,
	IDX_MAILBOX_PERI1_M10_CPU0,
	IDX_MAILBOX_PERI1_M10_CPU1,
	IDX_MAILBOX_PERI1_M11_CPU0,
	IDX_MAILBOX_PERI1_M11_CPU1,
	IDX_MAILBOX_PERI1_M12_CPU0,
	IDX_MAILBOX_PERI1_M12_CPU1,

	IDX_MAILBOX_PCIE_START,
	IDX_MAILBOX_PCIE_VF0 = IDX_MAILBOX_PCIE_START,
	IDX_MAILBOX_PCIE_VF1,
	IDX_MAILBOX_PCIE_VF2,
	IDX_MAILBOX_PCIE_VF3,
	IDX_MAILBOX_PCIE_VF4,
	IDX_MAILBOX_PCIE_VF5,
	IDX_MAILBOX_PCIE_VF6,
	IDX_MAILBOX_PCIE_VF7,
	IDX_MAILBOX_PCIE_VF8,
	IDX_MAILBOX_PCIE_VF9,
	IDX_MAILBOX_PCIE_VF10,
	IDX_MAILBOX_PCIE_VF11,
	IDX_MAILBOX_PCIE_VF12,
	IDX_MAILBOX_PCIE_VF13,
	IDX_MAILBOX_PCIE_VF14,
	IDX_MAILBOX_PCIE_VF15,
	IDX_MAILBOX_PCIE_PF,
#else
	IDX_MAILBOX_M1 = IDX_MAILBOX_START,
	IDX_MAILBOX_CP0_M3,
	IDX_MAILBOX_CP1_M3,

	IDX_MAILBOX_PERI0_START,
	IDX_MAILBOX_PERI0_M6 = IDX_MAILBOX_PERI0_START,
	IDX_MAILBOX_PERI0_M9_CPU0,
	IDX_MAILBOX_PERI0_M9_CPU1,
	IDX_MAILBOX_PERI0_M10_CPU0,
	IDX_MAILBOX_PERI0_M10_CPU1,
	IDX_MAILBOX_PERI0_M11_CPU0,
	IDX_MAILBOX_PERI0_M11_CPU1,
	IDX_MAILBOX_PERI0_M12_CPU0,
	IDX_MAILBOX_PERI0_M12_CPU1,
	IDX_MAILBOX_PERI0_M13_CPU0,
	IDX_MAILBOX_PERI0_M13_CPU1,
	IDX_MAILBOX_PERI0_M14_CPU0,
	IDX_MAILBOX_PERI0_M14_CPU1,

	IDX_MAILBOX_PERI1_START,
	IDX_MAILBOX_PERI1_M9_CPU0 = IDX_MAILBOX_PERI1_START,
	IDX_MAILBOX_PERI1_M9_CPU1,
	IDX_MAILBOX_PERI1_M10_CPU0,
	IDX_MAILBOX_PERI1_M10_CPU1,
	IDX_MAILBOX_PERI1_M11_CPU0,
	IDX_MAILBOX_PERI1_M11_CPU1,
	IDX_MAILBOX_PERI1_M12_CPU0,
	IDX_MAILBOX_PERI1_M12_CPU1,
	IDX_MAILBOX_PERI1_M13_CPU0,
	IDX_MAILBOX_PERI1_M13_CPU1,
	IDX_MAILBOX_PERI1_M14_CPU0,
	IDX_MAILBOX_PERI1_M14_CPU1,
#endif
	IDX_MAILBOX_END
};

enum _CPU_ID {
	CPU0,
	CPU1
};

enum _IRQ_HIGH {
	LOW,
	HIGH
};

/**
 * @fn		void ipm_samsung_register_callback(int inst, void (*cb)(int , int ))
 * @brief	Register a callback function that will be called when an interrupt
 *			is received for the specified instance number.
 * @param   inst: mailbox instance number
 * @param   cb: A callback function that takes two integer values as input.
 * @return  None
 */
void ipm_samsung_register_callback(const int inst, void (*cb)(const int, const int));

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

/**
 * @fn		void default_cb(int inst, int channel);
 * @brief	Generate the interrupt specified by the channel
 * @param   inst: mailbox instance number
 * @param   channel: specifies which logical channel to send the message on
 */
void default_cb(const int inst, const int channel);

/**
 * @fn		int ipm_samsung_read(int inst, const uint32_t target_id, const void *data, int size, int issr_index)
 * @brief	Read data from the samsung mailbox
 * @param   inst: mailbox instance number
 * @param   target_id: The ID of the chiplet that wants to read messages through the mailbox.
 * @param   data: pointer to outgoing data
 * @param   size: length of outgoing data
 * @param   issr_index: index of the ISSR register associated with this message
 * @return  The size of the data receivced
 */
int ipm_samsung_read(const int inst, const uint32_t target_id, void *data, const int size, const int issr_index);

/* rbln */
typedef void (*mailbox_rbln_callback_t)(int inst, int channel);
void mailbox_register_callback(mailbox_rbln_callback_t cb);