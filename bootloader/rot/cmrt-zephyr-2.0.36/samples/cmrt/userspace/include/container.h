/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CONTAINER_H
#define CONTAINER_H


#ifdef __cplusplus
extern "C" {
#endif


typedef int cmrt_container_t;


/*!
 * Get the current container ID.
 * @return container ID (main
 */
cmrt_container_t cmrt_container_id(void);

/**
 * @brief User container main function.
 *
 * Entry point to the container, which can be defined in the container code.
 * The three parameters for user_main can be given in k_thread_create
 * by the supervisor application.
 *
 * @param p1 First parameter for the container thread (container load id)
 * @param p2 Second parameter for the container thread
 * @param p3 Third parameter for the container thread
 */
void container(void *p1, void *p2, void *p3);


#ifdef __cplusplus
}
#endif


#endif
