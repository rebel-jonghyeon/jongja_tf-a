#!/usr/bin/tclsh
# ---------------------------------------------------------------------------
# File Name     : convert.tcl
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

if {$argc && $argc < 4} {
	set core [lindex $argv 0]
	set bitwidth [lindex $argv 1]
	set offset [lindex $argv 2]

	set Image "${core}.bin"
	set ifile1 [open $Image rb]

	fconfigure $ifile1 -translation binary
	set readSize 1
	set cnt 0
	set line 0
	set temp ""
	set readByte [expr $bitwidth / 8]

	if {$offset != 0} {
		set offset [format %x [expr [format "%d" $offset] / $readByte]]
	}

	switch -exact -- $core {
		fboot_n {
			set out1 "${core}.hex"
			set ofile1 [open $out1 w]
			set ofile $ofile1
			puts $ofile "@${offset}"

			while {1} {
				set data [read $ifile1 $readSize]
				binary scan $data H* var
				set temp [linsert $temp 0 $var]

				if {[eof $ifile1]} {
					close $ifile1
					if {$temp != ""} {
						set temp [join [string trim $temp " "] ""]
							puts $ofile $temp
					}
					break
				}
				if {$cnt == [expr $readByte - 1]} {
					set cnt 0
					set temp [join [string trim $temp " "] ""]
					puts $ofile $temp
					set temp ""

				} else {
					incr cnt
				}
			}
			close $ofile1
		}
		bl1 -
		bl2 -
		freertos_kernel {
			set idx 0
			set out "${core}_${idx}.hex"
			incr idx
#			puts "${out} file created"

			set ofile [open $out w]
			puts $ofile "@${offset}"

			while {1} {
				set data [read $ifile1 $readSize]
				binary scan $data H* var
				set temp [linsert $temp 0 $var]

				if {[eof $ifile1]} {
					close $ifile1
					if {$temp != ""} {
						set temp [join [string trim $temp " "] ""]
						puts $ofile $temp
					}
					break
				}
				if {$cnt == [expr $readByte - 1]} {
					set cnt 0
					set temp [join [string trim $temp " "] ""]
					puts $ofile $temp
					set temp ""
					incr line

					if {$line == 8192 || $line == 16384 || $line == 24576} {
						close $ofile
						set out "${core}_${idx}.hex"
						incr idx
#						puts "${out} file created"

						set ofile [open $out w]
						puts $ofile "@${offset}"
					}
				} else {
					incr cnt
				}
			}
			close $ofile
		}
		default {
			puts "Not support : $arg"
		}
	}
} elseif {$argc >= 4} {
	puts "Too many arguments"
} else {
	puts "Wrong arguments"
}
