/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_CONTAINER_H
#define CMRT_CONTAINER_H

#include <kernel_structs.h>
#include <stdalign.h>
#include <zephyr.h>
#include <device.h>
#include <string.h>
#include <sys/util.h>

#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/util.h>
#include <cmrt/fboot/fboot_config.h>

// Maximum limitation for static management of containers.
// WARNING: Increasing beyond 2 requires containers memory management.
#define CMRT_CONTAINERS_MAX_NUM           2
// Containers thread stack size.
#define CMRT_CONTAINERS_THREAD_STACK_SIZE 12288

/*
 *
 * CONTAINER STATE FLOW:
 *
 * ===================== LEGEND ==========================
 * capital case: mw commands.
 * lowercase: cmrt_container function calls.
 *
 *
 *                     +-----------+
 *                     |    INIT   |
 *                     +-----------+
 *                           |
 *                           | cmrt_container_initialize_all()
 *                           |
 *                           v          cmrt_container_unload()                       cmrt_container_stop()
 *                      +--------+      UNLOAD                      +---------+       STOP                        +----------------+
 *                      |  IDLE  | <------------------------------- | EXITING | <-------------------------------- | MALFUNCTIONING |
 *                      +--------+                                  +---------+                                   +----------------+
 *                       |      ^                                        ^
 * cmrt_container_load() |      | cmrt_container_unload()                |
 *                  LOAD |      | UNLOAD                                 |
 *                       v      |                                        |
 *                     +----------+                                      |
 *                     |          |                                      |
 *                     | STARTING |                                      | cmrt_container_stop()
 *                     |          |                                      | 2nd STOP
 *                     +----------+                                      |
 *                          |                                            |
 *                          | cmrt_container_run()                       |
 *                          | START                                      |
 *                          |                                            |
 *                          v                                            |
 *                     +---------+     cmrt_container_resume()     +-----------+
 *                     |         |     START                       |           |
 *                     | RUNNING | <------------------------------ | SUSPENDED |
 *                     |         | ------------------------------> |           |
 *                     +---------+     cmrt_container_suspend()    +-----------+
 */

/*
 * CONTAINER A or B SIC BUFFER:
 * ----------------------------
 * To reduce the memory footprint, the SIC buffer for reception will be switched between containers
 * A and B. Its lengths it is limited by the available memory for the containers
 * Once both containers are full, all LOAD operations will be ignored, and SIC buffer will
 * default to the SIC buffer under Container A.
 *
 * | Start Container A or B.
 * v
 * +------------+---------------------------+
 * | SIC BUFFER | BEGINNING OF IMAGE LOADED |
 * +------------+                           |
 * |                                        |
 * |                                        |
 * |                                        |
 * +----------------------------------------+
 *                                          ^
 *                  End of Container A or B |
 */


// Container created without threads.
// All containers exists in IDLE state once the program start execution.
#define CMRT_CONTAINER_IDLE 0
// Container thread created but not yet running.
#define CMRT_CONTAINER_STARTING 1
// Container thread running.
#define CMRT_CONTAINER_RUNNING 2
//
#define CMRT_CONTAINER_EXIT_REQUESTED 3
// Container thread has been aborted.
#define CMRT_CONTAINER_EXITING 4
//
#define CMRT_CONTAINER_MALFUNCT 5
// Container thread suspended.
#define CMRT_CONTAINER_SUSPENDED 6

/**
 * @struct cmrt_container_t
 * @brief This structure controls the containers internal state and other
 * parameters of interest.
 */
/**
 * @var cmrt_container_t::id
 * Identification number used internally for the only purpose of memory allocation.
 */
/**
 * @var cmrt_container_t::*ptr_img
 * Pointer to the memory address where the container image starts.
 */
/**
 * @var cmrt_container_t::img_size
 * Contains the container image size.
 */
/**
 * @var cmrt_container_t::state
 * Stores the intenal state of the container. These states are defined as IDLE,
 * STARTING, RUNNING, EXITING, SUSPENDED, MALFUNCTIONING, AND EXIT_REQUESTED.
 */
/**
 * @var cmrt_container_t::flowid
 * Indicates the flowid used by the container when using the SIC interface.
 */
/**
 * @var cmrt_container_t::*ptr_thread_data
 * Pointer to Zephyr's thread data.
 */
/**
 * @var cmrt_container_t::*ptr_thread_stack
 * Pointer to Zephyr's thread stack.
 */
/**
  * @var cmrt_container_t::thread_stack_size
  * Zephyr's thread stack size.
  */
/**
 * @var cmrt_container_t::thread_id
 * Zephyr's thread id.
 */
/**
 * @var cmrt_container_t::thread_priority
 * Zephyr's thread priority.
 */
typedef struct cmrt_container cmrt_container_t;
struct cmrt_container {

	/* CONTAINER RELATED PROPERTIES */
	/* Container id. */
	unsigned int id;
	/* Container image memory location. */
	void *ptr_img;
	/* Container write direction */
	int img_write_direction;
	/* Container image size. */
	size_t img_size;
	/* Container internal State. */
	int state;
	/* Container flowid. */
	int flowid;

	/* ZEPHYR THREADS RELATED PROPERTIES */
	/* Thread data. */
	struct k_thread *ptr_thread_data;
	/* Thread stack. */
	k_thread_stack_t *ptr_thread_stack;
	/* Thread stack size. */
	size_t thread_stack_size;
	/* Thread id returned upon thread creation.
	 * Note: typedef struct k_thread * k_tid_t */
	k_tid_t thread_id;
	/* Thread priority */
	int8_t thread_priority;
};

typedef struct cmrt_container_status cmrt_container_status_t;
struct cmrt_container_status {
	int flowid;
	int thread_priority;
	int state;
};


/* CONTAINER ACTIONS */
/**
 * @brief Allocates container into memory and creates thread.
 *
 * @param flowid Indicates the flowid used by the container for SIC communication.
 * @param img Pointer to image to load into container.
 * @param img_size Container image size.
 *
 * @return Zero on success or negative value on error.
 */
int cmrt_container_load(int flowid, int8_t thread_priority, void *img, size_t img_size);

/**
 * @brief Deallocates container from memory.
 *
 * @param ptr_container Pointer to the container to unload.
 *
 * @return Zero on success or negative value on error.
 */
int cmrt_container_unload(cmrt_container_t *ptr_container);

/**
 * @brief Runs or resumes container (in function of its state when the call takes effect).
 *
 * @param ptr_container Pointer to the container to unload.
 *
 * @return Zero on success or negative value on error.
 */
int cmrt_container_run_resume(cmrt_container_t *ptr_container);

/**
 * @brief Stops container execution (Thread abortion).
 *
 * @param ptr_container Pointer to the container to unload.
 *
 * @return Zero on success or negative value on error.
 */
int cmrt_container_stop(cmrt_container_t *ptr_container);

/**
 * @brief Suspends container executtion (Thread suspension).
 *
 * @param ptr_container Pointer to the container to unload.
 *
 * @return Zero on success or negative value on error.
 */
int cmrt_container_suspend(cmrt_container_t *ptr_container);


int cmrt_container_number_of_containers(void);
/* Returns an array with the status for each container. */
void *cmrt_container_statuses(cmrt_container_status_t *ptr_statuses, int *ptr_size);

/********************************************************************************
// CONTAINERS INTERNAL MANAGEMENT
********************************************************************************/

/**
 * @brief Initilizes all global variables to predefined values.
 *
 */
void cmrt_container_initialize(void);

/**
 * @brief Initializes one single container to predefined values.
 *
 * @param ptr_container Pointer to the container to unload.
 */
void cmrt_container_initialize_one(cmrt_container_t *ptr_container);

/**
 * @brief Initilizes all containers to predefined values.
 *
 */
void cmrt_container_initialize_all(void);

/**
 * @brief Searchs container per flow id.
 *
 * @param flowid Flow id container to be search.
 *
 * @return Pointer to container found, otherwise NULL.
 */
cmrt_container_t *cmrt_container_search_per_flowid(int flowid);

/**
 * @brief Retrieves next available empty container based in flowid value.
 *
 * @return Pointer to container found, otherwise NULL.
 */
void cmrt_container_get_next_empty(cmrt_container_t **ptr_container, size_t *container_size);

void cmrt_container_update_malfunctioning(void);

int cmrt_container_is_there_one_running(void);

/******************************************************************************
     CONTAINERS INTERNAL MEMORY MANAGEMENT (Maximum 2 containers only)

     All functions below this point are non-generic, meaning there are
     written with a maximum number of containers (2) in mind. To increase
     the number of containers a different approach should be followed.
*******************************************************************************/
/*

| <-- Container A Start                 Container B End --> |
|                                                           |
|                     Container B Start                     |
|                             |-->                          |
├─────────────────────────────┼─────────────────────────────┤
|      MEMORY CONTAINER A     |      MEMORY CONTAINER B     |
├─────────────────────────────┴─────────────────────────────┤
|                        TOTAL MEMORY                       |
└───────────────────────────────────────────────────────────┘

 */

/*!
 * Pointer to RAM end (immediately past the end of the
 * container-available total RAM.
 */

#define CONTAINER_RAM_END     ((char *) RISCV_RAM_BASE + RISCV_RAM_SIZE)

#define CONTAINER_RAM_START   ((char *)(ROUND_UP(_image_ram_end, 4)))
#define CONTAINER_RAM_TOTAL   ((size_t)(CONTAINER_RAM_END - CONTAINER_RAM_START))
#define CONTAINER_RAM_GUARD   (16)

/* Array of containers. */
extern cmrt_container_t cmrt_containers[CMRT_CONTAINERS_MAX_NUM];

#define CONTAINER_A cmrt_containers[0]
#define CONTAINER_B cmrt_containers[1]


#endif // CMRT_CONTAINER_H
