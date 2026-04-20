/*
<<<<<<< HEAD
 * Copyright (c) 2023, STMicroelectronics - All Rights Reserved
=======
 * Copyright (c) 2023-2025, STMicroelectronics - All Rights Reserved
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

<<<<<<< HEAD
.section .bl2_image
.incbin BL2_BIN_PATH

.section .dtb_image
=======
.section .bl2_image, "a"
.incbin BL2_BIN_PATH

.section .dtb_image, "a"
>>>>>>> upstream_import/upstream_v2_14_1
.incbin DTB_BIN_PATH
