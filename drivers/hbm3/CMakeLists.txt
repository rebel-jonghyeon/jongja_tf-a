add_library(hbm3
	OBJECT
	hbm3.c
	tmrs.c
	icon.c
	hbm3_irq.c
	hbm3_am.c
)

target_link_libraries(hbm3
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(hbm3
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/../../bootloader/cp/tf-a/include/drivers/hbm3
)
