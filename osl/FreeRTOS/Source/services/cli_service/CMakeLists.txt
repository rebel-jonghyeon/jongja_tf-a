add_library(cli_service
	STATIC
	cli_task.c
	sys_command_line.c
)

target_link_libraries(cli_service
	PUBLIC
	freertos_kernel # it need event_group.o of freertos_kernel lib
)

target_include_directories(cli_service
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${SVC_COMMON_INCLUDES}
)
