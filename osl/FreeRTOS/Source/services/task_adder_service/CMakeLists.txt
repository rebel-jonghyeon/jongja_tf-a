add_library(task_adder_service
	STATIC
	task_adder.c
)

target_link_libraries(task_adder_service
	PUBLIC
	freertos_kernel # it need event_group.o of freertos_kernel lib
)

target_include_directories(task_adder_service
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${SVC_COMMON_INCLUDES}
)
