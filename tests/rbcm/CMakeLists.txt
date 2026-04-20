add_library(test_rbcm OBJECT
    rbcm_test.c
    rbcm_reg_access_test.c
)

target_include_directories(test_rbcm PUBLIC
    ${TEST_COMMON_INCLUDES}
)

target_link_libraries(test_rbcm PUBLIC
    cli_service
	rbcm
)