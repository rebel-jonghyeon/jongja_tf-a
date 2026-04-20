add_library(psci
	STATIC
	psci.c
)

target_link_libraries(psci
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
	smccc #psci.c using 'qrm_smccc_cmc'
)

target_include_directories(psci
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
