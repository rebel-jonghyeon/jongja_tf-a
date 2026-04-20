add_library(watchdog
	OBJECT
	dw_apb_wdt.c
)

target_link_libraries(watchdog
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(watchdog
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
