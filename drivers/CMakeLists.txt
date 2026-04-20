set(DD_COMMON_INCLUDES
	${BOOTLOADER_COMMON_INCLUDES}
	${FREERTOS_COMMON_INCLUDES}
	${CMAKE_CURRENT_LIST_DIR}/include
)

if (${CMAKE_PROJECT_NAME} STREQUAL "CP_Bootloader")
	add_subdirectory(spi)
	list(APPEND DD_COMMON_INCLUDES
		${CMAKE_CURRENT_LIST_DIR}/../bootloader/cp/fboot/include
		${CMAKE_CURRENT_LIST_DIR}/../bootloader/cp/fboot/include/arm64
	)
endif()

add_subdirectory(common)
set(DEVICE_DRIVER_COMMON_LIBS
	driver
	assert
	interrupt
)
list(APPEND DEVICE_DRIVERS_LIST ${DEVICE_DRIVER_COMMON_LIBS})

if (FREERTOS_PORT STREQUAL "GCC_ARM_CM7")
	if (${USE_PCIE} STREQUAL "1")
		list (APPEND DD uart bat pcie mailbox pmu pvt_con watchdog)
	elseif (${USE_PCIE} STREQUAL "0")
		list (APPEND DD uart bat mailbox pmu pvt_con watchdog)
	endif()
	foreach(DRIVER ${DD})
		add_subdirectory(${DRIVER})
	endforeach()
	list (APPEND DEVICE_DRIVERS_LIST ${DD})
elseif (FREERTOS_PORT STREQUAL "GCC_ARM_CA73")
	list (APPEND DD intc psci mailbox pmu)
	if (NOT BUILD_TARGET STREQUAL cp1)
		list (APPEND DD uart dma gpio smmu pvt_con cmu watchdog rbc rbcm i2c noc_logger hbm3
			  pmic dvfs sic)
	endif()
	foreach(DRIVER ${DD})
		add_subdirectory(${DRIVER})
	endforeach()
	add_subdirectory(timer/generic_timer)
	add_subdirectory(timer/dw_apb_timer)
	add_subdirectory(qspi/qspi_apb)
	add_subdirectory(flash)
	list (APPEND DEVICE_DRIVERS_LIST ${DD} generic_timer dw_apb_timer qspi_apb flash)
else()
	# For fboot_n
	add_subdirectory(uart)
	list(APPEND DEVICE_DRIVERS_LIST uart)
endif()

set(DD_LISTS ${DEVICE_DRIVERS_LIST} PARENT_SCOPE)
