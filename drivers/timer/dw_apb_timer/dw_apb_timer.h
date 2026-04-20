
#pragma once

#include <stdint.h>
#include <string.h>
#include <FreeRTOS.h>
#include <semphr.h>



/* Timer Global Parameters */
#define TIMER_FREQUENCY			(250000000)	/* 250MHz */
#define MAX_NUM_TIMERS			(8)
#define NUM_TIMERS				(4)
#define APB_DATA_WIDTH			(32)		/* 8, 16, 32 */
#if (APB_DATA_WIDTH == 32)
	#define TIM_NEWMODE				(1)			/* 0 = false, 1 = true */
#endif
#if (TIM_NEWMODE == 1)
	#define INTR_SYNC2PCLK		(0)	/* 0 = Timer clock (timer_clk), 1 = System clock (pclk) */
#endif

/* Configurations of each timers */
#define TIMER_WIDTH_1			(32)		/* 8 ~ 32 */
#define TIMER_WIDTH_2			(32)		/* 8 ~ 32 */
#define TIMER_WIDTH_3			(32)		/* 8 ~ 32 */
#define TIMER_WIDTH_4			(32)		/* 8 ~ 32 */
#define TIMER_HAS_TOGGLE_1		(1)			/* 0 = false, 1 = true */
#define TIMER_HAS_TOGGLE_2		(1)			/* 0 = false, 1 = true */
#define TIMER_HAS_TOGGLE_3		(1)			/* 0 = false, 1 = true */
#define TIMER_HAS_TOGGLE_4		(1)			/* 0 = false, 1 = true */
#if (TIM_NEWMODE == 0)
	#define TIM_METASTABLE_1		(1)			/* 0 = absent, 1 = present */
	#define TIM_METASTABLE_2		(1)			/* 0 = absent, 1 = present */
	#define TIM_METASTABLE_3		(1)			/* 0 = absent, 1 = present */
	#define TIM_METASTABLE_4		(1)			/* 0 = absent, 1 = present */
	#define TIM_PULSE_EXTD_1		(0)			/* 0 = [R <= 1], 1 = [1 < R <= 2], 2 = [2 < R <= 3], 3 = [3 < R <= 4], Not Valid = [4 < R] */
	#define TIM_PULSE_EXTD_2		(0)			/* 0 = [R <= 1], 1 = [1 < R <= 2], 2 = [2 < R <= 3], 3 = [3 < R <= 4], Not Valid = [4 < R] */
	#define TIM_PULSE_EXTD_3		(0)			/* 0 = [R <= 1], 1 = [1 < R <= 2], 2 = [2 < R <= 3], 3 = [3 < R <= 4], Not Valid = [4 < R] */
	#define TIM_PULSE_EXTD_4		(0)			/* 0 = [R <= 1], 1 = [1 < R <= 2], 2 = [2 < R <= 3], 3 = [3 < R <= 4], Not Valid = [4 < R] */
#endif
/* The number of synchronization stages to be placed on clock domain */
#if (TIM_METASTABLE_1 == 1)
	#define TIM_SYNC_DEPTH_1		(2)		/* 2 = 2-stage, 3 = 3-stage, 4 = 4-stage */
#endif
#if (TIM_METASTABLE_2 == 1)
	#define TIM_SYNC_DEPTH_2		(2)		/* 2 = 2-stage, 3 = 3-stage, 4 = 4-stage */
#endif
#if (TIM_METASTABLE_3 == 1)
	#define TIM_SYNC_DEPTH_3		(2)		/* 2 = 2-stage, 3 = 3-stage, 4 = 4-stage */
#endif
#if (TIM_METASTABLE_4 == 1)
	#define TIM_SYNC_DEPTH_4		(2)		/* 2 = 2-stage, 3 = 3-stage, 4 = 4-stage */
#endif
#if (APB_DATA_WIDTH < TIMER_WIDTH_1)
	#define TIM_COHERENCY_1			(0)		/* 0 = false, 1 = true */
#endif
#if (APB_DATA_WIDTH < TIMER_WIDTH_2)
	#define TIM_COHERENCY_2			(0)		/* 0 = false, 1 = true */
#endif
#if (APB_DATA_WIDTH < TIMER_WIDTH_3)
	#define TIM_COHERENCY_3			(0)		/* 0 = false, 1 = true */
#endif
#if (APB_DATA_WIDTH < TIMER_WIDTH_4)
	#define TIM_COHERENCY_4			(0)		/* 0 = false, 1 = true */
#endif

/* Timer Global Parameters (Continued.) */
#if ((TIMER_HAS_TOGGLE_1 == 1) && (TIMER_HAS_TOGGLE_2 == 1) && (TIMER_HAS_TOGGLE_3 == 1) && (TIMER_HAS_TOGGLE_4 == 1))
	#define TIM_0N100_PWM_MODE		(1)			/* 0 = false, 1 = true */
#endif

#if (TIM_0N100_PWM_MODE == 1)
	#define TIMER_0N100_PWM_HC_EN	(0)			/* 0 = false, 1 = true */
#endif

#define SLAVE_INTERFACE_TYPE	(1)			/* 0 = APB2, 1 = APB3, 2 = APB4 */



/* DW apb timer load count (TimerNLoadCount) */
#define TIMER_MAX_LOAD_COUNT				(0xFFFFFFFFU)
#define TIMER_FREE_RUNNING_MODE_LOAD_VALUE	(0xFFFFFFFFU)
#define TIMER_SET_LOAD_COUNT(load_count)	(load_count & TIMER_MAX_LOAD_COUNT)

/* DW apb timer control (TimerNControlReg) */
#define TIMER_ENABLED				(0x01U)		/* <-> TIMER_DISABLED			*/
#define TIMER_USER_DEFINED			(0x02U)		/* <-> TIMER_FREE_RUNNING		*/
#define TIMER_INTERRUPT_MASKED		(0x04U)		/* <-> TIMER_INTERRUPT_UNMASKED	*/
#define TIMER_PWM_ENABLED			(0x08U)		/* <-> TIMER_PWM_DISABLED		*/
#define TIMER_0N100PWM_ENABLED		(0x10U)		/* <-> TIMER_0N100PWM_DISABLED	*/

/* DW apb timer protection level (TIMER_N_PROT_LEVEL) */
#define TIMER_BASE_PROT_LEVEL		(0x2U)
#define TIMER_MAX_PROT_LEVEL		(0x7U)



#define TIMER_CONTROL_ENABLE_BIT    0
#define TIMER_MODE_BIT              1
#define TIMER_INTR_MASK_BIT         2



struct dw_apb_timer_reg {
	volatile uint32_t timer_n_load_count;
	volatile uint32_t timer_n_current_value;
	volatile uint32_t timer_n_control_reg;
	volatile uint32_t timer_n_eoi;
	volatile uint32_t timer_n_int_status;
};
struct dw_apb_timers_reg {
	volatile struct dw_apb_timer_reg timer_n_reg[MAX_NUM_TIMERS];
	volatile uint32_t timers_int_status;
	volatile uint32_t timers_eoi;
	volatile uint32_t timers_raw_int_status;
	volatile uint32_t timers_comp_version;
	volatile uint32_t timer_n_load_count2[MAX_NUM_TIMERS];
	volatile uint32_t timer_n_prot_level[MAX_NUM_TIMERS];
};

struct dw_apb_timer_config {
	/* Maximum number of timers = 8, Current number of timers = 4 */
	uint32_t timer_id;
	/* Maximal (default) count on which timer is reset */
	uint32_t load_count;
	/* Base address of timer */
	uintptr_t reg_base;

	/* Semaphore to protect user data */
	SemaphoreHandle_t lock;
	/* Clock frequency of timer */
	uint32_t freq;

	/* Default callback function */
	void (*default_callback)(const struct dw_apb_timer_config *timer_config);
	/* User registered alarm callback function */
	void (*alarm_callback)(const struct dw_apb_timer_config *timer_config);
	/* User registered alarm data */
	void *alarm_data;
};

/**
 * @brief This function handles the interrupt of the DW APB timer.
 *
 * @param[in] cb_ref Pointer to the callback reference structure.
 *
 * @return None
 */
void dw_apb_timer_irq_handler(void *cb_ref);

/**
 * @brief This function starts the DW APB timer in free-running mode.
 *
 * @param[in] timer_config Pointer to the timer configuration structure.
 *
 * @return Zero on success, negative error code on failure.
 */
int dw_apb_timer_start(const struct dw_apb_timer_config *timer_config);

/**
 * @brief This function disables the DW APB timer.
 *
 * @param[in] timer_config Pointer to the timer configuration structure.
 *
 * @return Zero on success, negative error code on failure.
 */
int dw_apb_timer_disable(const struct dw_apb_timer_config *timer_config);

/**
 * @brief This function reads the load count value of the DW APB timer.
 *
 * @param[in] timer_config Pointer to the timer configuration structure.
 *
 * @return The load count value of the timer.
 */
uint32_t dw_apb_timer_get_load_count(const struct dw_apb_timer_config *timer_config);

/**
 * @brief This function reads the current value of the DW APB timer.
 *
 * @param[in] timer_config Pointer to the timer configuration structure.
 *
 * @return The current value of the timer.
 */
uint32_t dw_apb_timer_get_value(const struct dw_apb_timer_config *timer_config);

/**
 * @brief This function sets the load count value of the DW APB timer.
 *
 * @param[in] timer_config Pointer to the timer configuration structure.
 *
 * @return Zero on success, negative error code on failure.
 */
int dw_apb_timer_set_load_count(struct dw_apb_timer_config *timer_config);

/**
 * @brief This function sets the alarm callback function and the load count value of the DW APB timer.
 *
 * @param[in] timer_config Pointer to the timer configuration structure.
 * @param[in] load_count The load count value for the alarm.
 * @param[in] alarm_callback The callback function to be called when the alarm is triggered.
 * @param[in] alarm_data The data to be passed to the callback function.
 *
 * @return Zero on success, negative error code on failure.
 */
int dw_apb_timer_set_alarm_callback(struct dw_apb_timer_config *timer_config, const uint32_t load_count,
									const void (*alarm_callback)(const struct dw_apb_timer_config *), void *alarm_data);

/**
 * @brief This function cancels the alarm callback function of the DW APB timer.
 *
 * @param[in] timer_config Pointer to the timer configuration structure.
 *
 * @return Zero on success, negative error code on failure.
 */
int dw_apb_timer_cancel_alarm_callback(struct dw_apb_timer_config *timer_config);

/**
 * @brief This function returns the frequency of the DW APB timer.
 *
 * @param[in] timer_config Pointer to the timer configuration structure.
 *
 * @return The frequency of the timer in Hz.
 */
uint32_t dw_apb_timer_get_freq(const struct dw_apb_timer_config *timer_config);

/**
 * @brief This function initializes the DW APB timer driver.
 *
 * @return Zero on success, negative error code on failure.
 */
int dw_apb_timer_init(void);
