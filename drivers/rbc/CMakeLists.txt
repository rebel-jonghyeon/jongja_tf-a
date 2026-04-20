add_library(rbc
	OBJECT
	aw_ucie.c
	rbc_driver.c
	rbc_cmd.c
)

add_definitions(
	-DWA_SKIP_CHECK_LINK_STAT_ERROR=1
	-DWA_SKIP_RETRAIN_FOR_HANDLING_ERR=1
	-DWA_SKIP_UCIE_INIT_COND=1
	)

target_link_libraries(rbc
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
	intc
	PRIVATE
	cmu
	pmu
)

target_include_directories(rbc
	PUBLIC
	${${DD_COMMON_INCLUDES}}
	${CMAKE_CURRENT_LIST_DIR}
	PRIVATE
	registers
)