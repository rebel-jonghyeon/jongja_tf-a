add_library(dma	OBJECT pl330.c)

target_link_libraries(dma
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(dma
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
