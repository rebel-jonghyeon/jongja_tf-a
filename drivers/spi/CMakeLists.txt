add_library(dwc_ssi
	STATIC
	dwc_ssi.c
)

target_link_libraries(dwc_ssi
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(dwc_ssi
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${BOOTLOADER_COMMON_INCLUDES}
)
