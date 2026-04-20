/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include "cmrt_container.h"
#include <linker/linker-defs.h>
#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt_container, CONFIG_CMRT_LOG_LEVEL);
#include <assert.h>

/* Array of containers. */
cmrt_container_t cmrt_containers[CONFIG_CMRT_NUM_CONTAINERS];

/* Defines array of data threads. */
struct k_thread cmrt_containers_threads[CONFIG_CMRT_NUM_CONTAINERS];

/* Defines array of thread stacks. */
K_THREAD_STACK_ARRAY_DEFINE(cmrt_containers_thread_stacks,
	CONFIG_CMRT_NUM_CONTAINERS, CONFIG_CMRT_CONTAINER_STACK_SIZE);

#define CMRT_MAX_CONTAINER_FLOW_ID 0x7FF

int cmrt_container_load(int flowid, int8_t thread_priority, void *img, size_t img_size)
{
	/* Check input parameters. */
	if (flowid <= 0 || flowid > CMRT_MAX_CONTAINER_FLOW_ID ||
	    img == NULL || img_size <= 0) {
		LOG_INF("MW %s(): Invalid parameters", __func__);
		return -EINVAL;
	}

	if (!(thread_priority > 0 && thread_priority <= (CONFIG_NUM_PREEMPT_PRIORITIES - 1))) {
		LOG_INF("MW %s(): Invalid parameter priority %d",
			__func__, thread_priority);
		return -EINVAL;
	}

	cmrt_container_t *ptr_container = NULL;
	uint32_t container_size = 0;
	cmrt_container_get_next_empty(&ptr_container, &container_size);
	if (container_size == 0) {
		/* This code should never execute even with a dedicated test case. */
		LOG_INF("MW %s(): Invalid container found", __func__);
		return -EINVAL;
	}

	ptr_container->flowid = flowid;
	ptr_container->thread_priority = thread_priority;
	ptr_container->img_size = img_size;

	/* Creating container thread. */
	ptr_container->thread_id = k_thread_create(ptr_container->ptr_thread_data,
						   ptr_container->ptr_thread_stack,
						   ptr_container->thread_stack_size,
						   (k_thread_entry_t)img, (void *)
						   ptr_container->flowid, NULL, NULL,
						   ptr_container->thread_priority,
						   K_USER | K_CONTAINER, K_FOREVER);

	/* Documentation does not indicate which is the value returned when
	 * functions fails to create thread. Assuming NULL. */
	if (ptr_container->thread_id == NULL) {
		LOG_INF("MW %s(): Failure creating thread for flowid %d",
			__func__, ptr_container->flowid);
		return -EINVAL;
	}

	/* At this stage we could have a dead thread, meaning the image
	 * loading operation failed. We simply inform the user and leave
	 * the image in memory. The user should proceed to stop and unload
	 * the image from memory to free the container. */
	if (ptr_container->thread_id->base.thread_state == _THREAD_DEAD) {
		ptr_container->state = CMRT_CONTAINER_MALFUNCT;
		LOG_INF("Container FAILED to load");
	} else {
		/* Assign container state and return. */
		ptr_container->state = CMRT_CONTAINER_STARTING;
		LOG_INF("Container LOADED");
	}

	return 0;
}

int cmrt_container_unload(cmrt_container_t *ptr_container)
{
	if (ptr_container == NULL) {
		return -EINVAL;
	}

	int rval = 0;
	switch (ptr_container->state) {
		case CMRT_CONTAINER_MALFUNCT:
		case CMRT_CONTAINER_RUNNING:
		case CMRT_CONTAINER_SUSPENDED:
		case CMRT_CONTAINER_STARTING:
			LOG_INF("MW %s(): Aborting Thread %p",
				__func__, ptr_container->thread_id);
			k_thread_abort(ptr_container->thread_id);
			if (ptr_container->state != CMRT_CONTAINER_STARTING) {
				LOG_INF("Closing contexts for Thread %p", ptr_container->thread_id);
				cmrt_dd_free(ptr_container->thread_id);
			}
			/* [[fall-through]]; */
		case CMRT_CONTAINER_EXITING:
			LOG_INF("MW %s(): Unloading Thread %p",
				__func__, ptr_container->thread_id);
			cmrt_container_initialize_one(ptr_container);
			rval = 1;
			break;
		default:
			rval = -EBADF;
			break;
	}
	return rval;
}

int cmrt_container_run_resume(cmrt_container_t *ptr_container)
{
	if (ptr_container == NULL) {
		return -EINVAL;
	}

	int rval = 0;
	switch (ptr_container->state) {
	case CMRT_CONTAINER_RUNNING:
		/* Container thread is already running. */
		rval = 0;
		break;
	case CMRT_CONTAINER_STARTING:
		LOG_INF("MW %s(): Started Thread %p", __func__,
			ptr_container->thread_id);
		k_thread_start(ptr_container->thread_id);
		ptr_container->state = CMRT_CONTAINER_RUNNING;
		rval = 1;
		break;
	case CMRT_CONTAINER_SUSPENDED:
		LOG_INF("MW %s(): Resuming Thread %p", __func__,
			ptr_container->thread_id);
		k_thread_resume(ptr_container->thread_id);
		ptr_container->state = CMRT_CONTAINER_RUNNING;
		rval = 1;
		break;
	default:
		rval = -EBADF;
		break;
	}

	return rval;
}

int cmrt_container_stop(cmrt_container_t *ptr_container)
{
	if (ptr_container == NULL) {
		return -EINVAL;
	}

	int rval = 0;
	switch (ptr_container->state) {
	case CMRT_CONTAINER_MALFUNCT:
	case CMRT_CONTAINER_RUNNING:
	case CMRT_CONTAINER_STARTING:
	case CMRT_CONTAINER_SUSPENDED:
		LOG_INF("MW %s(): Aborting Thread %p", __func__,
			ptr_container->thread_id);
		k_thread_abort(ptr_container->thread_id);
		LOG_INF("Closing contexts for Thread %p",
			ptr_container->thread_id);
		cmrt_dd_free(ptr_container->thread_id);
		ptr_container->state = CMRT_CONTAINER_EXITING;
		rval = 1;
		break;
	default:
		rval = -EBADF;
		break;
	}
	return rval;
}

int cmrt_container_suspend(cmrt_container_t *ptr_container)
{
	if (ptr_container == NULL) {
		return -EINVAL;
	}

	int rval = 0;
	switch (ptr_container->state) {
	case CMRT_CONTAINER_RUNNING:
		LOG_INF("MW() %s: Suspending Thread %p", __func__,
			ptr_container->thread_id);
		k_thread_suspend(ptr_container->thread_id);
		ptr_container->state = CMRT_CONTAINER_SUSPENDED;
		rval = 1;
		break;
	case CMRT_CONTAINER_STARTING:
	case CMRT_CONTAINER_SUSPENDED:
		/* Container thread is already suspended/inactive. */
		rval = 0;
		break;
	default:
		rval = -EBADF;
		break;
	}
	return rval;
}

void cmrt_container_initialize(void)
{
	LOG_INF("User container max size: %d bytes", CONTAINER_RAM_TOTAL);
	LOG_INF("Max concurrent user containers: %d", CONFIG_CMRT_NUM_CONTAINERS);
	cmrt_container_initialize_all();
}

int cmrt_container_number_of_containers(void)
{
	return CONFIG_CMRT_NUM_CONTAINERS;
}

/* Returns an array with the status for each container. */
void *cmrt_container_statuses(cmrt_container_status_t *ptr_statuses, int *ptr_size)
{
	if (ptr_statuses == NULL || ptr_size == NULL) {
		return NULL;
	}

	cmrt_container_status_t aux[CONFIG_CMRT_NUM_CONTAINERS];
	for (int i = 0; i < CONFIG_CMRT_NUM_CONTAINERS; i++) {
		aux[i].flowid = cmrt_containers[i].flowid;
		aux[i].thread_priority = cmrt_containers[i].thread_priority;
		aux[i].state = cmrt_containers[i].state;
	}
	*ptr_size = CONFIG_CMRT_NUM_CONTAINERS;
	return memcpy((void *)ptr_statuses, (void *)aux,
		      CONFIG_CMRT_NUM_CONTAINERS * sizeof(cmrt_container_status_t));
}

/*******************************************************************************
 * CONTAINERS INTERNAL MANAGEMENT
*******************************************************************************/

/* Sets container to initial values. */
void cmrt_container_initialize_one(cmrt_container_t *ptr_container)
{
	if (ptr_container == NULL) {
		return;
	}

	ptr_container->state = CMRT_CONTAINER_IDLE;
	ptr_container->flowid = -1;
	ptr_container->thread_priority = -1;

	/* Delete memory image. */
	(void)memset(ptr_container->ptr_img, 0, ptr_container->img_size);
	ptr_container->img_size = 0;

	/* Delete stack memory: Security concern. */
	(void)memset(ptr_container->ptr_thread_stack, 0, ptr_container->thread_stack_size);

	/* Point thread id to null. */
	ptr_container->thread_id = NULL;
}

/* Sets all the containers to initial values. */
void cmrt_container_initialize_all(void)
{
	for (unsigned int i = 0; i < CONFIG_CMRT_NUM_CONTAINERS; i++) {
		cmrt_containers[i].id = i;
		cmrt_containers[i].state = CMRT_CONTAINER_IDLE;
		cmrt_containers[i].flowid = -1;
		cmrt_containers[i].img_size = 0;
		cmrt_containers[i].ptr_thread_data = &cmrt_containers_threads[i];
		cmrt_containers[i].ptr_thread_stack = cmrt_containers_thread_stacks[i];
		cmrt_containers[i].thread_stack_size = CMRT_CONTAINERS_THREAD_STACK_SIZE;
		cmrt_containers[i].thread_priority = -1;
	}

	static_assert(CONFIG_CMRT_NUM_CONTAINERS <= 2, "only 2 containers work");
	CONTAINER_A.ptr_img = CONTAINER_RAM_START;
	CONTAINER_A.img_write_direction = 0;
#if CMRT_CONTAINER_MAX_NUM > 1
	CONTAINER_B.ptr_img = CONTAINER_RAM_END;
	CONTAINER_B.img_write_direction = CMRT_SIC_ALIGN_RIGHT;
#endif
}

/* Search for container based in flow id number.
 */
cmrt_container_t *cmrt_container_search_per_flowid(int flowid)
{
	for (int i = 0; i < CONFIG_CMRT_NUM_CONTAINERS; i++) {
		if (cmrt_containers[i].flowid == flowid) {
			return &cmrt_containers[i];
		}
	}
	return NULL;
}


/* Maximum size of a container to load.  "Using guard to compensate
 * for all the alignments" (?)
 */
static size_t cmrt_container_max_size(void)
{
	size_t n = CONTAINER_RAM_TOTAL - CONTAINER_RAM_GUARD;
	for (unsigned i = 0; i < CONFIG_CMRT_NUM_CONTAINERS; ++i) {
		n -= cmrt_containers[i].img_size;
	}
	return n;
}

/*
  Returns the next empty container based in flow id.
  also changes it start address based in the container size.
 */
void cmrt_container_get_next_empty(cmrt_container_t **ptr_container, size_t *container_size)
{
	cmrt_container_t *container = &cmrt_containers[0];
	size_t size = 0;
	char *pimg = CONTAINER_RAM_START;
	for (int i = 0; i < CONFIG_CMRT_NUM_CONTAINERS; i++) {
		if (cmrt_containers[i].flowid == -1) {
			container = &cmrt_containers[i];
			container->ptr_img = pimg;
			size = cmrt_container_max_size();
			break;
		}
		pimg += ROUND_UP(cmrt_containers[i].img_size, 4);
	}
	*ptr_container = container;
	*container_size = size;
}

/* Sets dead container to malfunctioning. */
/* Transition to other state shall be initiated by user. */
void cmrt_container_update_malfunctioning(void)
{
	for (int i = 0; i < CONFIG_CMRT_NUM_CONTAINERS; i++) {
		if ((cmrt_containers_threads[i].base.thread_state == _THREAD_DEAD) &&
		    (cmrt_containers[i].state <= CMRT_CONTAINER_RUNNING) &&
		    (cmrt_containers[i].state > CMRT_CONTAINER_IDLE)) {
			LOG_INF("Detected container %d malfunctioning", cmrt_containers[i].flowid);
			cmrt_containers[i].state = CMRT_CONTAINER_MALFUNCT;
		}
	}
}

/* Indicates if there is at least one container running */
int cmrt_container_is_there_one_running(void)
{
	for (int i = 0; i < CONFIG_CMRT_NUM_CONTAINERS; ++i) {
		if (cmrt_containers[i].state == CMRT_CONTAINER_RUNNING) {
			return true;
		}
	}
	return false;
}
