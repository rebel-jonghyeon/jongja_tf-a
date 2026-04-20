#
# Copyright 2025 Samsung Electronics Co, Ltd. All Rights Reserved.
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

add_library(noc_logger
	OBJECT
	noc_logger.c
)

target_link_libraries(noc_logger
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(noc_logger
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
