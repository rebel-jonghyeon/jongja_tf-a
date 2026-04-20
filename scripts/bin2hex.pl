#!/usr/bin/perl
# ---------------------------------------------------------------------------
# File Name     : bin2hex.pl
# Title         :
# Project       : Rebel
# Description   : Converting script for binary to hex
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

use strict;

my $input_file;
my $output_file;
my $base_addr;
my $buf;
my ($byte0, $byte1, $byte2, $byte3);
my $alignedHex;

open(INFILE, $ARGV[0]);
binmode INFILE;
$input_file = $ARGV[0];
$output_file = $ARGV[1];
$base_addr = $ARGV[2];

open(OUTFILE, ">${output_file}");
if(${base_addr} ne "") {
	print(OUTFILE "${base_addr}\n");
}

while(sysread(INFILE, $buf, 4)) {
	my $buf2hex;
	$buf2hex = unpack("H*", $buf);
	$byte0 = substr($buf2hex, 0, 2);
	$byte1 = substr($buf2hex, 2, 2);
	$byte2 = substr($buf2hex, 4, 2);
	$byte3 = substr($buf2hex, 6, 2);
	$alignedHex = $byte3.$byte2.$byte1.$byte0;
	print(OUTFILE "${alignedHex}\n");
}

close(INFILE);
close(OUTFILE);
