set(SVC_COMMON_INCLUDES
	${CMAKE_CURRENT_LIST_DIR}/cli_service
	${CMAKE_CURRENT_LIST_DIR}/terminal_service
	${CMAKE_CURRENT_LIST_DIR}/task_adder_service
	${FREERTOS_COMMON_INCLUDES}
)

add_subdirectory(cli_service)
list(APPEND SERVICE_LIST cli_service)

add_subdirectory(terminal_service)
list(APPEND SERVICE_LIST terminal_service)


if(${FREERTOS_PORT} STREQUAL "GCC_ARM_CA73")
add_subdirectory(replay_service)
list(APPEND SERVICE_LIST replay_service)
add_subdirectory(task_adder_service)
list(APPEND SERVICE_LIST task_adder_service)
endif()

set(SVC_LIST ${SERVICE_LIST} PARENT_SCOPE)
