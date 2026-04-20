#!/usr/bin/perl -w
# ---------------------------------------------------------------------------
# File Name     : make_dat.pl
# Title         :
# Project       : Island
# Description   : Splitting dram data into each physical dram array
# Notes         :
# ---------------------------------------------------------------------------
# Copyright 2014(c) Samsung Electronics
# ---------------------------------------------------------------------------

use IO::File;

#$BASE_ADDRESS = 80080000;
$BASE_ADDRESS = $ARGV[1];
$PREP = "../../scripts/prep_dram_data_rebel_ch16.pl";

$FILE_NAME = $ARGV[0];

print "Rebel...";

system("$PREP -s $FILE_NAME -b $BASE_ADDRESS -hash 1");

print "DONE\n";

