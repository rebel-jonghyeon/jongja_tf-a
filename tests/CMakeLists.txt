if ("${TEST}" STREQUAL "all")
	set(TEST_COMMON_INCLUDES
		${CMAKE_CURRENT_LIST_DIR}/common
		${DD_COMMON_INCLUDES}
	)

	add_subdirectory(common)
	add_subdirectory(interrupt_test_helper_example)
	list (APPEND TEST_LIST test_common interrupt_test_helper_example)

	add_subdirectory(arch)
	list (APPEND TEST_LIST test_arch)

	if ("${FREERTOS_PORT}" STREQUAL "GCC_ARM_CA73")
		add_subdirectory(arch/arm64)
		add_subdirectory(gpio)
		add_subdirectory(dma)
		add_subdirectory(mailbox)
		add_subdirectory(pvt_con)
		add_subdirectory(timer/dw_apb_timer)
		add_subdirectory(cmu)
		add_subdirectory(smmu)
		add_subdirectory(log)
		add_subdirectory(rbc)
		add_subdirectory(rbcm)
		add_subdirectory(i2c)
		add_subdirectory(hbm3)
		add_subdirectory(system_test)
		add_subdirectory(dvfs)
		add_subdirectory(pmic)
		add_subdirectory(sic)
		add_subdirectory(chipid)
		add_subdirectory(flash)
		add_subdirectory(qspi)
		add_subdirectory(rbdma)
		list (APPEND TEST_LIST test_gpio test_dma mailbox_test test_pvt_con test_arm64
			  test_dw_apb_timer test_cmu test_mmu show_log test_rbc test_rbcm test_i2c hbm3_test
			  system_test test_dvfs test_pmic pvt_cli test_sic test_chipid test_flash test_qspiapb
			  test_rbdma)
	elseif ("${FREERTOS_PORT}" STREQUAL "GCC_ARM_CM7")
		add_subdirectory(arch/arm)
		if ("${USE_PCIE}" STREQUAL "1")
			add_subdirectory(pcie)
		endif()
		add_subdirectory(mailbox)
		add_subdirectory(log)
		add_subdirectory(interrupt_test)
		add_subdirectory(pvt_con)
		if ("${USE_PCIE}" STREQUAL "1")
			list (APPEND TEST_LIST pcie_test mailbox_test test_arm show_log test_irq pvt_cli)
		elseif ("${USE_PCIE}" STREQUAL "0")
			list (APPEND TEST_LIST mailbox_test test_arm show_log test_irq pvt_cli)
		endif()
	endif()

	set(TEST_LISTS ${TEST_LIST} PARENT_SCOPE)
endif()

