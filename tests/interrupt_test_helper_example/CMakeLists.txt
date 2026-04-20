#
# Copyright 2024 Samsung Electronics Co, Ltd. All Rights Reserved.
#
# PROPRIETARY/CONFIDENTIAL
#
# This software is the confidential and proprietary information of
# Samsung Electronics Co., Ltd. ("Confidential Information").
# You shall not disclose such Confidential Information and shall use it only
# in accordance with the terms of the license agreement you entered into with
# Samsung Electronics Co., Ltd. ("SAMSUNG").
#
# SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
# THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
# NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
# LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
# ITS DERIVATIVES.
#

add_library(interrupt_test_helper_example
	OBJECT
	example_test.c
	example_driver.c
)

target_compile_definitions(interrupt_test_helper_example
	PRIVATE
	UNITY_FIXTURE_NO_EXTRAS
)

target_link_libraries(interrupt_test_helper_example
	PRIVATE
	interrupt_test_helper
	unity
	cli_service
	$<$<STREQUAL:${FREERTOS_PORT},GCC_ARM_CA73>:intc>
)

target_include_directories(interrupt_test_helper_example
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${TEST_COMMON_INCLUDES}
)