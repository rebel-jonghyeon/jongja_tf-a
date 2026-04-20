add_library(common
	STATIC
	printf.c
	system_api.c
)

if (NOT BUILD_TARGET STREQUAL cp1)
	target_link_libraries(common
		PUBLIC
		uart
	)
endif()

target_include_directories(common
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${FREERTOS_COMMON_INCLUDES}
	../../drivers/intc
)
