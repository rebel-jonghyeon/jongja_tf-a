add_library(uart
	OBJECT
	$<IF:$<STREQUAL:${BSP},rl-rebel-vp>, pl011/uart.c, uart.c>
)

target_link_libraries(uart
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(uart
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
