add_library(terminal_service
	STATIC
	console_uart.c
	console.c
	terminal_task.c
)

target_link_libraries(terminal_service
	PUBLIC
	$<$<STREQUAL:${ARCH},CA73>:intc>
	uart
)

target_include_directories(terminal_service
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${SVC_COMMON_INCLUDES}
)
