#!/usr/bin/perl -w
# ---------------------------------------------------------------------------
# File Name     : rebel_make_dat.pl
# Title         :
# Project       : Rebel
# Description   : Splitting dram data into each physical dram array
# Notes         :
# ---------------------------------------------------------------------------
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
# ---------------------------------------------------------------------------

use IO::File;

#$BASE_ADDRESS = 80080000;
$BASE_ADDRESS = $ARGV[1];
$PREP = "../../scripts/prep_dram_data_rebel_ch0.pl";

$FILE_NAME = $ARGV[0];

print "Rebel...";

system("$PREP -s $FILE_NAME -b $BASE_ADDRESS -hash 1");

print "DONE\n";

