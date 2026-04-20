add_library(dw_apb_timer
	OBJECT
	dw_apb_timer.c
)

target_link_libraries(dw_apb_timer
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(dw_apb_timer
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
