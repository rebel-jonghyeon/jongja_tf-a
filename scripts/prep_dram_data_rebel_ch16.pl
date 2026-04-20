#!/usr/bin/perl
# ---------------------------------------------------------------------------
# File Name     : prep_dram_data_rebel_ch16.pl
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
my $pch_hash_bit;
my $sid;

my @oF;
my @pch0_oF;
my @pch1_oF;
my @oF_sid;
my $current_oF;
my $mem_idx;
my $pch_idx;
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

my $cnt;


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

my @pch0_ofilenames = ("Rebel_ch0_pch0.dat", "Rebel_ch1_pch0.dat", "Rebel_ch2_pch0.dat", "Rebel_ch3_pch0.dat", "Rebel_ch4_pch0.dat", "Rebel_ch5_pch0.dat", "Rebel_ch6_pch0.dat", "Rebel_ch7_pch0.dat",
		  "Rebel_ch8_pch0.dat", "Rebel_ch9_pch0.dat", "Rebel_ch10_pch0.dat", "Rebel_ch11_pch0.dat", "Rebel_ch12_pch0.dat", "Rebel_ch13_pch0.dat", "Rebel_ch14_pch0.dat", "Rebel_ch15_pch0.dat");

my @pch1_ofilenames = ("Rebel_ch0_pch1.dat", "Rebel_ch1_pch1.dat", "Rebel_ch2_pch1.dat", "Rebel_ch3_pch1.dat", "Rebel_ch4_pch1.dat", "Rebel_ch5_pch1.dat", "Rebel_ch6_pch1.dat", "Rebel_ch7_pch1.dat",
		  "Rebel_ch8_pch1.dat", "Rebel_ch9_pch1.dat", "Rebel_ch10_pch1.dat", "Rebel_ch11_pch1.dat", "Rebel_ch12_pch1.dat", "Rebel_ch13_pch1.dat", "Rebel_ch14_pch1.dat", "Rebel_ch15_pch1.dat");


@pch0_oF = map {IO::File->new($_, 'w')} @pch0_ofilenames;
@pch1_oF = map {IO::File->new($_, 'w')} @pch1_ofilenames;


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
			# printf "addr_in = 0x%x\n\n", $addr_in;

			if( $hash == 1 ){

				$hash_bits = 0;
				for my $id (0..4) {
					my $masked_value = (($addr_in >> 14) & 0x3FFFFF) & $cfg_CustomHash_bitmask[$id];
					my $result = 0;

					for my $i (0..21) {
						$result ^= ($masked_value & 0x1);
						$masked_value = ($masked_value >> 1);
					}
					$hash_bits = (($hash_bits << 1) | ($result & 0x1));
				}
				# printf "hash_bits = 0x%x\n", $hash_bits;

				# $addr_in = ($addr_in & 0xFFFE0FFFF) | (($hash_bits << 16) & 0x1F0000);
				$addr_in = (((($addr_in >> 16) & 0xFFFE0) | ($hash_bits & 0x1F)) << 16) | ($addr_in & 0xFFFF);

				# printf "addr_hash = 0x%x\n", $addr_in;
			}

			$LA_22 = ($addr_in >> 32) & 0x1;
			$LA_23 = ($addr_in >> 33) & 0x1;
			$LA_24 = ($addr_in >> 34) & 0x1;
			$LA_25 = ($addr_in >> 35) & 0x1;
			$LA_9 = ($addr_in >> 19) & 0x1;

			# printf "LA_22 = 0x%x\n", $LA_22;
			# printf "LA_23 = 0x%x\n", $LA_23;
			# printf "LA_24 = 0x%x\n", $LA_24;
			# printf "LA_25 = 0x%x\n", $LA_25;
			# printf "LA_9 = 0x%x\n", $LA_9;

			$RA_14 = (($LA_24 & $LA_23 | $LA_25) & 0x1 );
			$RA_13 = (~($LA_24) & ~($LA_25) & (~($LA_23) | ~($LA_9)) & 0x1);
			$RA_12 = (($LA_25) ? ($LA_9) : ($LA_22) & 0x1);

			# printf "RA_14 = 0x%x\n", $RA_14;
			# printf "RA_13 = 0x%x\n", $RA_13;
			# printf "RA_12 = 0x%x\n", $RA_12;


			$SID_1 = (~($LA_9) & ~($LA_25) & (($LA_23) | ($LA_24)) & 0x1);
			$SID_0 = (~($LA_23) & ($LA_9) | ($LA_25) & 0x1 );

			#$laddr = ($addr_in >> 6) & 0x3ffffff;
			$laddr = ( ((($addr_in >> 14 ) & 0x3fffff) << 4) | (($addr_in >> 6) & 0xf ) ) & 0x3ffffff;	# 26bit

			$row_addr = ( ($RA_14 << 14) | ($RA_13 << 13) | ($RA_12 << 12) | (($laddr >> 10) & 0xfff) ); #  15bit width
			# printf "row_addr = 0x%x\n", $row_addr;

			#$col_addr = ((($laddr) & 0x1F)); # Not use BA interleaving
			$col_addr = (((($laddr >> 3 ) & 0x7 ) << 2 ) | (($laddr & 0x3)) << 0); # shkim : BA Interleaving -default : 5bit width
			# printf "col_addr = 0x%x\n", $col_addr;

			$bank_addr = ((($laddr >> 8) & 0x1) << 3) | ((($laddr >> 2) & 0x1) << 2) | ((($laddr >> 6) & 0x3) << 0); # BA Interleaving
			#$bank_addr = ((($laddr >> 5 ) & 0xf) << 0); # Not use BA Interleaving
			# printf "bank_addr = 0x%x\n", $bank_addr;

			$sid_addr = ( ($SID_1 << 1) | $SID_0);

			$addr = ($sid_addr <<($row_addr_width + $col_addr_width + $bank_addr_width)) | ($bank_addr <<($row_addr_width+$col_addr_width)) | ($row_addr << ($col_addr_width)) | $col_addr;
			# printf "addr = 0x%x\n", $addr;

			$addr_7 = ($addr << 3) & 0xffffffff; # for zebu memory model addressing
			$addr_p1 = $addr +1;

			# 1K - channel interleaving for Rebel H
			$hash_bit = (((($addr_in >> 13)&0x1 ) << 3) | ((($addr_in >> 12)&0x1) <<2 ) | ((($addr_in >> 11)&0x1) <<1) | (($addr_in >> 10)& 0x1) );
			# printf "hash bit = 0x%x\n", $hash_bit;
			# zebu specific : if use only channel 0, 32K interleaving between PCh0 and PCh1.
			$pch_hash_bit = (($addr_in >> 5)& 0x1);

			$mem_idx = $hash_bit;

			$data_in_l = $data_in_hex & 0xffff;
			$data_in_h = ($data_in_hex >> 16) & 0xffff;

			$addr_hex = sprintf("%x", $addr_7);
			$addr_p1_hex = sprintf("07%x", $addr_p1);
			$data_in_l_hex = sprintf("%04x",$data_in_l);
			$data_in_h_hex = sprintf("%04x",$data_in_h);
			#if($pch_idx == 0x1) { # for pch1
			if(($pch_hash_bit) == 0x1) { # for pch1

				if( ($line_num %8 ) == 0 ){
					$pch1_oF[$mem_idx]->print("\@$addr_hex\n");
				}
				$pch1_oF[$mem_idx]->print("$data_in_h_hex");
				$pch1_oF[$mem_idx]->print("$data_in_l_hex\n");
			}
			else { # for pch0
				if( ($line_num %8 ) == 0 ){
					$pch0_oF[$mem_idx]->print("\@$addr_hex\n");

				}
				$pch0_oF[$mem_idx]->print("$data_in_h_hex");
				$pch0_oF[$mem_idx]->print("$data_in_l_hex\n");
			}

			$offset = $offset + 4;
			$addr_in_origin = $addr_in_origin + 4;
			$line_num++;
			$addr_in_hex = sprintf("%x", $addr_in_origin);

		}
	}
}

close iF;
foreach (@pch0_oF) {
	close $_;
}
foreach (@pch1_oF) {
	close $_;
}

