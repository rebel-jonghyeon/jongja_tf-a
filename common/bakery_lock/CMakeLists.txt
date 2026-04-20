add_library(bakery_lock
	OBJECT
	bakery_lock.c
)

target_link_libraries(bakery_lock
	PUBLIC
)

target_include_directories(bakery_lock
	PUBLIC
	${FREERTOS_COMMON_INCLUDES}
	${CMAKE_CURRENT_LIST_DIR}
)
