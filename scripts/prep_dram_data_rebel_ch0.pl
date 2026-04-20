#!/usr/bin/perl
# ---------------------------------------------------------------------------
# File Name     : prep_dram_data_rebel_ch0.pl
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

use strict;
use warnings;

use IO::File;
use Getopt::Long;

my $help;
my $num_argv = $#ARGV;

#################################################################
# this fileds are differ from Project.
# LPDDR4 8Gb x16
my $rank_addr_width = 1;      # this is not used
my $chip_stacK_id_width = 0;  # this is not used
my $bank_group_width = 0;     # this is not used

my $bank_addr_width = 4;
my $row_addr_width = 15;
my $col_addr_width = 5;
my $sid_addr_width = 2;
#################################################################

my $src_file;
my $base_addr;
my $base_addr_hex;
my $hash = 0;

my $addr;
my $addr_7;
my $addr_p1;
my $addr_p1_hex;

my $addr_hex;
my $addr_in;
my $addr_in_origin;
my $laddr;
my $offset;
my $print_addr_flag = 1;


my $line_num=0;

my $col_addr;
my $row_addr;
my $bank_addr;
my $rank_addr;
my $sid_addr;
my @bank_addr_prev = (-1,-1,-1,-1);
my $col_addr_hex;
my $row_addr_hex;
my $bank_addr_hex;
my $sid_addr_hex;

# hash interleaving
my $hash_bits1;
my $hash_bits0;
my $hash_bits;
my $hash_bits_hex;
my $DestSel;
my @cfg_CustomHash_bitmask = (0x084210, 0x042108, 0x021084, 0x210842, 0x108421);

my $upper_addr;
my $upper_addr_hex;
my $addr_in_hex;
my $data_in_str;
my $data_in_hex;
my $data_in_h;
my $data_in_h_hex;
my $data_in_l;
my $data_in_l_hex;
my $swap_data_in_h;
my $swap_data_in_h_hex;
my $swap_data_in_l;
my $swap_data_in_l_hex;
my $hash_bit;
my $sid;

#my @ofilenames = ("$src_file.0","$src_file.1","$src_file.2","$src_file.3","$src_file.4","$src_file.5","$src_file.6","$src_file.7");
my @oF;
my @oF_sid;
my $current_oF;
my $mem_idx;
my @field;
my @field_addr;

# shkim for Rebel H 24Gb 12H
my  $RA_14;
my  $RA_13;
my  $RA_12;
my  $SID_0;
my  $SID_1;
my  $LA_9;
my  $LA_22;
my  $LA_23;
my  $LA_24;
my  $LA_25;


GetOptions(
	"s=s"  => \$src_file,
	"b=s"  => \$base_addr,
	"hash=i" => \$hash,
	#"rank=i" => \$rank,
	#"red_page=i" => \$red_page,
	"h" => \$help
	);

if( defined($help) || ($num_argv< 0)) {
	print("Usage:\n");
	print("		prep_dram_data.pl [Options] \n\n");
	print("Options:\n");
	print("		-s		: src file \n");
	print("		-b		: base address(offset from dram base address, if dram area starts from 0x4000_0000,  \n");
	print("		-hash	: hash [1|0] Bank hash address map mode\n");
	#print("		-rank	: rank [1|0] Rank Interleaving\n");
	#print("		-red_page	: red_page [1|0] \n");
	print("		-h(elp)	: print this message \n");
	print("		input file should be 32 bit-width hex format and base address should be word-aligned \n");
	exit 0;
}


$base_addr_hex = hex $base_addr;


open(iF, "<$src_file") || die "Can't open $src_file";

#my @ofilenames = ("Rebel_test0.dat", "Rebel_test1.dat", "Rebel_test2.dat","Rebel_test3.dat","Rebel_test4.dat","Rebel_test5.dat","Rebel_test6.dat","Rebel_test7.dat","Rebel_test8.dat","Rebel_test9.dat",
#                  "Rebel_test10.dat", "Rebel_test11.dat", "Rebel_test12.dat", "Rebel_test13.dat", "Rebel_test14.dat", "Rebel_test15.dat");

my ($basename) = split(/\./, $src_file);
my @ofilenames = ("$basename\_channel0_pch0.dat", "$basename\_channel0_pch1.dat");  # use channel 0 only

@oF = map {IO::File->new($_, 'w')} @ofilenames;


$offset = 0;
$addr_in_origin = $base_addr_hex;


while(<iF>) {
	@field = split ( /\s+/, $_);
	foreach ( @field ) {
		if ($_ =~ /^\@/) {
			@field_addr = split ( /\@/, $_);
			$addr_in_origin =  hex $field_addr[1];
			$addr_in_hex = sprintf("%x", $addr_in_origin);
			$print_addr_flag =1;
		}
		else {
			$data_in_hex = hex $_;

			$addr_in = $addr_in_origin;
			# printf "addr_in = 0x%x\n", $addr_in;

			if( $hash == 1 ){

				$hash_bits = 0;
				for my $id (0..4) {
					my $masked_value = (($addr_in >> 10) & 0x3FFFFF) & $cfg_CustomHash_bitmask[$id];
					my $result = 0;

					for my $i (0..21) {
						$result ^= ($masked_value & 0x1);
						$masked_value = ($masked_value >> 1);
					}
					$hash_bits = (($hash_bits << 1) | ($result & 0x1));
				}
				# printf "hash_bits = 0x%x\n", $hash_bits;

				# $addr_in = ($addr_in & 0xFFFE0FFF) | (($hash_bits << 12) & 0x1F000);
				$addr_in = (((($addr_in >> 12) & 0xFFFE0) | ($hash_bits & 0x1F)) << 12) | ($addr_in & 0xFFF);
			}

			# printf "addr_hash = 0x%x\n", $addr_in;

			$LA_22 = ($addr_in >> 28) & 0x1;
			$LA_23 = ($addr_in >> 29) & 0x1;
			$LA_24 = ($addr_in >> 30) & 0x1;
			$LA_25 = ($addr_in >> 31) & 0x1;
			$LA_9 = ($addr_in >> 15) & 0x1;

			$RA_14 = (($LA_24 & $LA_23 | $LA_25) & 0x1 );
			$RA_13 = (~($LA_24) & ~($LA_25) & (~($LA_23) | ~($LA_9)) & 0x1);
			$RA_12 = (($LA_25) ? ($LA_9) : ($LA_22) & 0x1);

			$SID_1 = (~($LA_9) & ~($LA_25) & (($LA_23) | ($LA_24)) & 0x1);
			$SID_0 = (~($LA_23) & ($LA_9) | ($LA_25) & 0x1 );

			$laddr = ($addr_in >> 6) & 0x3fffffff;

			$row_addr = ( ($RA_14 << 14) | ($RA_13 << 13) | ($RA_12 << 12) | (($laddr >> 10) & 0xfff) ); #  15bit width

			#$col_addr = ((($laddr) & 0x1F)); # Not use BA interleaving
			$col_addr = (((($laddr >> 3 ) & 0x7 ) << 2 ) | (($laddr & 0x3)) << 0); # shkim : BA Interleaving -default : 5bit width
			#printf("[DBG]col_addr : 0x%x\n", $col_addr);

			$bank_addr = ((($laddr >> 8) & 0x1) << 3) | ((($laddr >> 2) & 0x1) << 2) | ((($laddr >> 6) & 0x3) << 0); # BA Interleaving
			#$bank_addr = ((($laddr >> 5 ) & 0xf) << 0); # Not use BA Interleaving
			#printf("[DBG]bank_addr : 0x%x\n", $bank_addr);

			$sid_addr = ( ($SID_1 << 1) | $SID_0);

			$addr = ($sid_addr <<($row_addr_width + $col_addr_width + $bank_addr_width)) | ($bank_addr <<($row_addr_width+$col_addr_width)) | ($row_addr << ($col_addr_width)) | $col_addr;
			#printf("[DBG] phsical addr: 0x%x\n", $addr);

			$addr_7 = ($addr << 3) & 0xffffffff; # for zebu memory model addressing
			$addr_p1 = $addr +1;

			# 1K - channel interleaving for Rebel H
			#$hash_bit = (((($addr_in >> 13)&0x1 ) << 3) | ((($addr_in >> 12)&0x1) <<2 ) | ((($addr_in >> 11)&0x1) <<1) | (($addr_in >> 10)& 0x1) )

			# zebu specific : if use only channel 0, 32K interleaving between PCh0 and PCh1.
			$hash_bit = (($addr_in >> 5)& 0x1);

			$mem_idx = $hash_bit;

			$data_in_l = $data_in_hex & 0xffff;
			$data_in_h = ($data_in_hex >> 16) & 0xffff;

			$addr_hex = sprintf("%x", $addr_7);
			$addr_p1_hex = sprintf("07%x", $addr_p1);
			$data_in_l_hex = sprintf("%04x",$data_in_l);
			$data_in_h_hex = sprintf("%04x",$data_in_h);

			if( ($line_num %8 ) == 0 ){
				$oF[$mem_idx]->print("\@$addr_hex\n");

			}
			$oF[$mem_idx]->print("$data_in_h_hex");
			$oF[$mem_idx]->print("$data_in_l_hex\n");

			$offset = $offset + 4;
			$addr_in_origin = $addr_in_origin + 4;
			$bank_addr_prev[$mem_idx] = $bank_addr;
			$line_num++;
			$addr_in_hex = sprintf("%x", $addr_in_origin);

		}
	}
}

close iF;
foreach (@oF) {
	close $_;
}

