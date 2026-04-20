add_library(backtrace
	OBJECT
	backtrace.c
)

target_include_directories(backtrace
	PUBLIC
	../../include/
	${CMAKE_ROOT_DIR}/drivers/intc
	${FREERTOS_COMMON_INCLUDES}
)
