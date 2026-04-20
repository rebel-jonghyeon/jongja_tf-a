/*
 * Middleware protocol definitions.
 *
 * Copyright (c) 2017-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef MW_PROTOCOL_H
#define MW_PROTOCOL_H

#include <stdint.h>
#include <rebel_h_gpt.h>
#include "../../../../common/rebel_h_sic.h"
/**
 * @struct cmrt_mw_request_t
 * CMRT MW command format. CMRT MW listens for commands from HLOS at
 * flow ID 100. Command should be sent using this struct. For select commands an
 * optional payload may follow this struct. MW responds to commands with
 * cmrt_mw_response_t.
 */
typedef struct {
	/**
	 * Command ID.
	 *
	 * @ref CMRT_MW_COMMANDS
	 */
	uint32_t cmd;

	/**
	 * Flow ID of the container. It is use by only those commands that operate
	 * on containers directly.
	 */
	uint32_t flowid;

	/**
	 * Container priority. It is used by load container only and indicate the
	 * container priority.
	 */
	uint32_t container_priority;

	/**
	 * Bytes. Used by #CMRT_MW_CHECK_CONTAINER and #CMRT_MW_LOAD_CONTAINER
	 * commands.
	 */
	uint32_t length;
} cmrt_mw_request_t;

/**
 * @struct cmrt_mw_response_t
 * CMRT MW response format. CMRT responds to HLOS command using this struct.
 */
typedef struct {
	/**
	 * If command execution results in an error, "errno" is returned in this
	 * field, it is 0 otherwise.
	 */
	uint32_t error;

	/**
	 * Container status. This field is set if cmd is #CMRT_MW_PROBE_CONTAINER
	 *
	 * @ref CRI_CONTAINER_STATE
	 */
	uint32_t status; /* container status, see below */
} cmrt_mw_response_t;

/**
 * MW responds to command #CMRT_MW_READ_LOGS with this struct. It is followed by
 * content of the ring buffer.
 */
typedef struct {
	uint32_t size; /**< Size of the log buffer, which follows this struct */

	/**
	 * Offset to the oldest log message. Message may be partial, due to wrap
	 * around in ring buffer.
	 */
	uint32_t head;
} cmrt_log_header_t;

typedef struct cmrt_mw_command_response_header cmrt_mw_command_response_header_t;
struct cmrt_mw_command_response_header {
	uint32_t command;
	uint32_t version;
	uint32_t size;
};

#define CMRT_MW_COMMAND_PS 1

typedef struct cmrt_mw_command_ps_response cmrt_mw_command_ps_response_t;
struct cmrt_mw_command_ps_response {
	uint32_t flowid;
	int32_t container_priority;
	uint32_t state;
};

typedef struct cmrt_mw_command_ps_containers_response cmrt_mw_command_ps_containers_response_t;
struct cmrt_mw_command_ps_containers_response {
	cmrt_mw_response_t mw_response;
	cmrt_mw_command_response_header_t cmd_header;
	cmrt_mw_command_ps_response_t cmd_response[2];
};

/**
 * @name CMRT_MW_COMMANDS
 * Commands accepted by CMRT MW in cmrt_mw_request_t.cmd.
 * @anchor CMRT_MW_COMMANDS
 * @{
 */

/**
 * Check container command is used for checking if a container can be loaded.
 * Check must be done before #CMRT_MW_LOAD_CONTAINER command is issued.
 * cmrt_mw_request_t.length must be set to size of image of container to be
 * loaded.
 * @deprecated
 */
#define CMRT_MW_CHECK_CONTAINER   0x01

/**
 * Command to load container. cmrt_mw_request_t.length must be set to
 * size of container image.
 * cmrt_mw_request_t.flowid must be set to flow ID that will be used to
 * interact or control this container. Container body must be appended
 * after cmrt_mw_request_t.
 *
 * The request can be accompanied by CMRT_MW_START_CONTAINER set in
 * the same request, which will automatically start container
 * execution once it's been successfully loaded.
 */
#define CMRT_MW_LOAD_CONTAINER    0x02

/**
 * Unload command, unloads a container. Container must be identified by its
 * flowid in cmrt_mw_request_t.flowid.
 */
#define CMRT_MW_UNLOAD_CONTAINER  0x04

/**
 * @cond INCLUDE_CRI_INTERNAL
 */
#define CMRT_MW_START_CONTAINER   0x08
#define CMRT_MW_STOP_CONTAINER    0x10

/**
 * @endcond
 * Probe command, checks container status. Container can be in one of the
 * @ref CRI_CONTAINER_STATE. If container has been unloaded or it has crashed
 * then ENOENT is returned in cmrt_mw_response_t.error.
 */
#define CMRT_MW_PROBE_CONTAINER   0x20

/*!
 * Query container information.  Returns information structure according to
 * passed in buffer size information.
 */
#define CMRT_MW_QUERY_CONTAINER   0x21

/**
 * Command returns log messages. This command is not supported for QEMU target.
 * Unlike any other command, response is in cmrt_log_header_t format.
 */
#define CMRT_MW_READ_LOGS         0x40

/**
 * Perform soft reset. MW thread is terminated and executed again.
 */
#define CMRT_MW_SOFT_RESET        0x41

#define CMRT_MW_PS_CONTAINERS     0x50

/**
 * Command from 0x60 reserved for load images (refer to common/rebel_h_sic.h)
 */

/**
 * @}
 * @name CRI_CONTAINER_STATE
 * Container status returned in cmrt_mw_response_t.status.
 * @anchor CRI_CONTAINER_STATE
 * @{
 */
#define CRI_CONTAINER_IDLE 0
#define CRI_CONTAINER_STARTING 1
#define CRI_CONTAINER_RUNNING 2
#define CRI_CONTAINER_EXIT_REQUESTED 3
#define CRI_CONTAINER_EXITING 4
#define CRI_CONTAINER_MALFUNCT 5

/*
 * ERROR CODES FROM MW.
 */
#define CMRT_MW_COMMAND_NOT_FOUND           1
#define CMRT_MW_COMMAND_NOT_SUPPORTED       2
#define CMRT_MW_CONTAINER_NOT_FOUND         3
#define CMRT_MW_CONTAINER_ALREADY_EXISTS    4
#define CMRT_MW_CONTAINER_NOT_AVAILABLE     5
#define CMRT_MW_CONTAINER_NO_MEM_AVAILABLE  6

#define CMRT_MW_DO_NOT_RESPOND 254

/**
 * @struct cmrt_mw_service_t
 * Structure used for SIC2 communications.
 */
typedef struct cmrt_mw_service cmrt_mw_service_t;
struct cmrt_mw_service {
	/* SIC context */
	cmrt_sic_t sic;
	/* Container Flow id. The flow id for MW is set via main call. */
	uint32_t flowid;
	/* Initially it takes the maximum value allowed for the container, but once
	 * a SIC read takes place, its value equals the size of the container loaded
	 * into SRAM (for the case of load operations)
	 */
	size_t buflen;
	uint32_t peerid;
	/* Before the container is loaded from SIC we only know the maximum available
	 * size, therefore we store it to calculate the offset on right aligned write
	 * operations.
	 */
	uint32_t max_buflen;
	/* It indicates whether SIC will perform an aligned to the right operation. */
	uint32_t mem_dir;
	uint8_t *buffer;
};

extern cmrt_mw_service_t srv;

/**
 * @}
 */
#endif
