add_library(chiplet
	OBJECT
	chiplet.c
)

target_include_directories(chiplet
	PUBLIC
	${DD_COMMON_INCLUDES}
	${CMAKE_CURRENT_LIST_DIR}
)

add_library(driver
	STATIC
	driver.c
)

target_include_directories(driver
	PUBLIC
	${DD_COMMON_INCLUDES}
	${CMAKE_CURRENT_LIST_DIR}
)

add_library(assert
	STATIC
	assert.c
)
target_include_directories(assert
	PUBLIC
	${DD_COMMON_INCLUDES}
	${CMAKE_CURRENT_LIST_DIR}
)

add_library(interrupt
	STATIC
	interrupt.c
)
target_include_directories(interrupt
	PUBLIC
	${DD_COMMON_INCLUDES}
	${CMAKE_CURRENT_LIST_DIR}
	$<$<STREQUAL:${ARCH},CA73>:${CMAKE_CURRENT_LIST_DIR}/../intc>
	#gic.h<=portmacro.h<=FreeRTOS.h<=interrupt.h<=interrupt.c
)
