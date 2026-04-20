#!/bin/bash

if [ $1 = "boot" ]; then
	echo "BootLoader_CP boot"
	cd binaries/BootLoader_CP
	if [ -e "fboot_n.bin" ]; then
		../../scripts/convert.tcl fboot_n 64 0
	fi
	cd - > /dev/null
fi

if [ $1 = "tf-a" ]; then
	echo "BootLoader_CP tf-a"
	cd binaries/BootLoader_CP
	if [ -e "bl1.bin" ]; then
		../../scripts/convert.tcl bl1 64 0
	fi
	if [ -e "bl2.bin" ]; then
		../../scripts/convert.tcl bl2 64 0
	fi
	if [ -e "bl31.bin" ]; then
		if [ $2 = "ch1" ]; then
			echo "HBM 1 channel"
			perl ../../scripts/bin2hex.pl bl31.bin bl31.hex
			perl ../../scripts/rebel_make_dat.pl bl31.hex 0x00000000
		elif [ $2 = "ch16" ]; then
			echo "HBM 16 channel"
			perl ../../scripts/bin2hex.pl bl31.bin bl31.hex
			perl ../../scripts/rebel_make_dat_ch16.pl bl31.hex 0x00000000
			mv Rebel_ch0_pch0.dat bl31_ch0_pch0.dat
			mv Rebel_ch0_pch1.dat bl31_ch0_pch1.dat

			mv Rebel_ch1_pch0.dat bl31_ch1_pch0.dat
			mv Rebel_ch1_pch1.dat bl31_ch1_pch1.dat

			mv Rebel_ch2_pch0.dat bl31_ch2_pch0.dat
			mv Rebel_ch2_pch1.dat bl31_ch2_pch1.dat

			mv Rebel_ch3_pch0.dat bl31_ch3_pch0.dat
			mv Rebel_ch3_pch1.dat bl31_ch3_pch1.dat

			mv Rebel_ch4_pch0.dat bl31_ch4_pch0.dat
			mv Rebel_ch4_pch1.dat bl31_ch4_pch1.dat

			mv Rebel_ch5_pch0.dat bl31_ch5_pch0.dat
			mv Rebel_ch5_pch1.dat bl31_ch5_pch1.dat

			mv Rebel_ch6_pch0.dat bl31_ch6_pch0.dat
			mv Rebel_ch6_pch1.dat bl31_ch6_pch1.dat

			mv Rebel_ch7_pch0.dat bl31_ch7_pch0.dat
			mv Rebel_ch7_pch1.dat bl31_ch7_pch1.dat

			mv Rebel_ch8_pch0.dat bl31_ch8_pch0.dat
			mv Rebel_ch8_pch1.dat bl31_ch8_pch1.dat

			mv Rebel_ch9_pch0.dat bl31_ch9_pch0.dat
			mv Rebel_ch9_pch1.dat bl31_ch9_pch1.dat

			mv Rebel_ch10_pch0.dat bl31_ch10_pch0.dat
			mv Rebel_ch10_pch1.dat bl31_ch10_pch1.dat

			mv Rebel_ch11_pch0.dat bl31_ch11_pch0.dat
			mv Rebel_ch11_pch1.dat bl31_ch11_pch1.dat

			mv Rebel_ch12_pch0.dat bl31_ch12_pch0.dat
			mv Rebel_ch12_pch1.dat bl31_ch12_pch1.dat

			mv Rebel_ch13_pch0.dat bl31_ch13_pch0.dat
			mv Rebel_ch13_pch1.dat bl31_ch13_pch1.dat

			mv Rebel_ch14_pch0.dat bl31_ch14_pch0.dat
			mv Rebel_ch14_pch1.dat bl31_ch14_pch1.dat

			mv Rebel_ch15_pch0.dat bl31_ch15_pch0.dat
			mv Rebel_ch15_pch1.dat bl31_ch15_pch1.dat
		fi
		printf "bl31 Done\n"
	fi
	if [ -e "p1.part" ]; then
		perl ../../scripts/bin2hex.pl p1.part p1.hex
		perl ../../scripts/rebel_make_dat.pl p1.hex 0x00000000
	fi
	cd - > /dev/null
fi

if [ $1 = "cm" ]; then
	echo "FreeRTOS_PCIE"
	cd binaries/FreeRTOS_PCIE
	if [ -e "freertos_kernel.bin" ]; then
		../../scripts/convert.tcl freertos_kernel 64 0
	fi
	cd - > /dev/null
fi

if [ $1 = "cp1" ]; then
	echo "Bootloader_CP1 BL31"
	cd binaries/FreeRTOS_CP1
	if [ -e "bl31.bin" ]; then
		if [ $2 = "ch1" ]; then
			echo "HBM 1 channel"
			perl ../../scripts/bin2hex.pl bl31.bin cp1_bl31.hex
			perl ../../scripts/rebel_make_dat.pl cp1_bl31.hex 0x14100000
		elif [ $2 = "ch16" ]; then
			echo "HBM 16 channel"
			perl ../../scripts/bin2hex.pl bl31.bin bl31.hex
			perl ../../scripts/rebel_make_dat_ch16.pl bl31.hex 0x14100000

			mv Rebel_ch0_pch0.dat cp1_bl31_ch0_pch0.dat
			mv Rebel_ch0_pch1.dat cp1_bl31_ch0_pch1.dat

			mv Rebel_ch1_pch0.dat cp1_bl31_ch1_pch0.dat
			mv Rebel_ch1_pch1.dat cp1_bl31_ch1_pch1.dat

			mv Rebel_ch2_pch0.dat cp1_bl31_ch2_pch0.dat
			mv Rebel_ch2_pch1.dat cp1_bl31_ch2_pch1.dat

			mv Rebel_ch3_pch0.dat cp1_bl31_ch3_pch0.dat
			mv Rebel_ch3_pch1.dat cp1_bl31_ch3_pch1.dat

			mv Rebel_ch4_pch0.dat cp1_bl31_ch4_pch0.dat
			mv Rebel_ch4_pch1.dat cp1_bl31_ch4_pch1.dat

			mv Rebel_ch5_pch0.dat cp1_bl31_ch5_pch0.dat
			mv Rebel_ch5_pch1.dat cp1_bl31_ch5_pch1.dat

			mv Rebel_ch6_pch0.dat cp1_bl31_ch6_pch0.dat
			mv Rebel_ch6_pch1.dat cp1_bl31_ch6_pch1.dat

			mv Rebel_ch7_pch0.dat cp1_bl31_ch7_pch0.dat
			mv Rebel_ch7_pch1.dat cp1_bl31_ch7_pch1.dat

			mv Rebel_ch8_pch0.dat cp1_bl31_ch8_pch0.dat
			mv Rebel_ch8_pch1.dat cp1_bl31_ch8_pch1.dat

			mv Rebel_ch9_pch0.dat cp1_bl31_ch9_pch0.dat
			mv Rebel_ch9_pch1.dat cp1_bl31_ch9_pch1.dat

			mv Rebel_ch10_pch0.dat cp1_bl31_ch10_pch0.dat
			mv Rebel_ch10_pch1.dat cp1_bl31_ch10_pch1.dat

			mv Rebel_ch11_pch0.dat cp1_bl31_ch11_pch0.dat
			mv Rebel_ch11_pch1.dat cp1_bl31_ch11_pch1.dat

			mv Rebel_ch12_pch0.dat cp1_bl31_ch12_pch0.dat
			mv Rebel_ch12_pch1.dat cp1_bl31_ch12_pch1.dat

			mv Rebel_ch13_pch0.dat cp1_bl31_ch13_pch0.dat
			mv Rebel_ch13_pch1.dat cp1_bl31_ch13_pch1.dat

			mv Rebel_ch14_pch0.dat cp1_bl31_ch14_pch0.dat
			mv Rebel_ch14_pch1.dat cp1_bl31_ch14_pch1.dat

			mv Rebel_ch15_pch0.dat cp1_bl31_ch15_pch0.dat
			mv Rebel_ch15_pch1.dat cp1_bl31_ch15_pch1.dat
		fi
		printf "BL31 CP1 .bin -> .hex convert DONE\n"
	fi
	cd - > /dev/null

	echo "FreeRTOS_CP1"
	cd binaries/FreeRTOS_CP1
	if [ -e "freertos_kernel.bin" ]; then
		if [ $2 = "ch1" ]; then
			echo "HBM 1 channel"
			perl ../../scripts/bin2hex.pl freertos_kernel.bin cp1_freertos.hex
			perl ../../scripts/rebel_make_dat.pl cp1_freertos.hex 0x14200000
		elif [ $2 = "ch16" ]; then
			echo "HBM 16 channel"
			perl ../../scripts/bin2hex.pl freertos_kernel.bin freertos_kernel.hex
			perl ../../scripts/rebel_make_dat_ch16.pl freertos_kernel.hex 0x14200000

			mv Rebel_ch0_pch0.dat cp1_freertos_kernel_ch0_pch0.dat
			mv Rebel_ch0_pch1.dat cp1_freertos_kernel_ch0_pch1.dat

			mv Rebel_ch1_pch0.dat cp1_freertos_kernel_ch1_pch0.dat
			mv Rebel_ch1_pch1.dat cp1_freertos_kernel_ch1_pch1.dat

			mv Rebel_ch2_pch0.dat cp1_freertos_kernel_ch2_pch0.dat
			mv Rebel_ch2_pch1.dat cp1_freertos_kernel_ch2_pch1.dat

			mv Rebel_ch3_pch0.dat cp1_freertos_kernel_ch3_pch0.dat
			mv Rebel_ch3_pch1.dat cp1_freertos_kernel_ch3_pch1.dat

			mv Rebel_ch4_pch0.dat cp1_freertos_kernel_ch4_pch0.dat
			mv Rebel_ch4_pch1.dat cp1_freertos_kernel_ch4_pch1.dat

			mv Rebel_ch5_pch0.dat cp1_freertos_kernel_ch5_pch0.dat
			mv Rebel_ch5_pch1.dat cp1_freertos_kernel_ch5_pch1.dat

			mv Rebel_ch6_pch0.dat cp1_freertos_kernel_ch6_pch0.dat
			mv Rebel_ch6_pch1.dat cp1_freertos_kernel_ch6_pch1.dat

			mv Rebel_ch7_pch0.dat cp1_freertos_kernel_ch7_pch0.dat
			mv Rebel_ch7_pch1.dat cp1_freertos_kernel_ch7_pch1.dat

			mv Rebel_ch8_pch0.dat cp1_freertos_kernel_ch8_pch0.dat
			mv Rebel_ch8_pch1.dat cp1_freertos_kernel_ch8_pch1.dat

			mv Rebel_ch9_pch0.dat cp1_freertos_kernel_ch9_pch0.dat
			mv Rebel_ch9_pch1.dat cp1_freertos_kernel_ch9_pch1.dat

			mv Rebel_ch10_pch0.dat cp1_freertos_kernel_ch10_pch0.dat
			mv Rebel_ch10_pch1.dat cp1_freertos_kernel_ch10_pch1.dat

			mv Rebel_ch11_pch0.dat cp1_freertos_kernel_ch11_pch0.dat
			mv Rebel_ch11_pch1.dat cp1_freertos_kernel_ch11_pch1.dat

			mv Rebel_ch12_pch0.dat cp1_freertos_kernel_ch12_pch0.dat
			mv Rebel_ch12_pch1.dat cp1_freertos_kernel_ch12_pch1.dat

			mv Rebel_ch13_pch0.dat cp1_freertos_kernel_ch13_pch0.dat
			mv Rebel_ch13_pch1.dat cp1_freertos_kernel_ch13_pch1.dat

			mv Rebel_ch14_pch0.dat cp1_freertos_kernel_ch14_pch0.dat
			mv Rebel_ch14_pch1.dat cp1_freertos_kernel_ch14_pch1.dat

			mv Rebel_ch15_pch0.dat cp1_freertos_kernel_ch15_pch0.dat
			mv Rebel_ch15_pch1.dat cp1_freertos_kernel_ch15_pch1.dat
		fi
		printf "FreeRTOS CP1 .bin -> .hex convert DONE\n"
	fi
	cd - > /dev/null
fi

if [ $1 = "cp0" ]; then
	echo "FreeRTOS_CP"
	cd binaries/FreeRTOS_CP
	if [ -e "freertos_kernel.bin" ]; then
		if [ $2 = "ch1" ]; then
			echo "HBM 1 channel"
			perl ../../scripts/bin2hex.pl freertos_kernel.bin freertos.hex
			perl ../../scripts/rebel_make_dat.pl freertos.hex 0x00200000
		elif [ $2 = "ch16" ]; then
			echo "HBM 16 channel"
			perl ../../scripts/bin2hex.pl freertos_kernel.bin freertos_kernel.hex
			perl ../../scripts/rebel_make_dat_ch16.pl freertos_kernel.hex 0x00200000
			mv Rebel_ch0_pch0.dat freertos_kernel_ch0_pch0.dat
			mv Rebel_ch0_pch1.dat freertos_kernel_ch0_pch1.dat

			mv Rebel_ch1_pch0.dat freertos_kernel_ch1_pch0.dat
			mv Rebel_ch1_pch1.dat freertos_kernel_ch1_pch1.dat

			mv Rebel_ch2_pch0.dat freertos_kernel_ch2_pch0.dat
			mv Rebel_ch2_pch1.dat freertos_kernel_ch2_pch1.dat

			mv Rebel_ch3_pch0.dat freertos_kernel_ch3_pch0.dat
			mv Rebel_ch3_pch1.dat freertos_kernel_ch3_pch1.dat

			mv Rebel_ch4_pch0.dat freertos_kernel_ch4_pch0.dat
			mv Rebel_ch4_pch1.dat freertos_kernel_ch4_pch1.dat

			mv Rebel_ch5_pch0.dat freertos_kernel_ch5_pch0.dat
			mv Rebel_ch5_pch1.dat freertos_kernel_ch5_pch1.dat

			mv Rebel_ch6_pch0.dat freertos_kernel_ch6_pch0.dat
			mv Rebel_ch6_pch1.dat freertos_kernel_ch6_pch1.dat

			mv Rebel_ch7_pch0.dat freertos_kernel_ch7_pch0.dat
			mv Rebel_ch7_pch1.dat freertos_kernel_ch7_pch1.dat

			mv Rebel_ch8_pch0.dat freertos_kernel_ch8_pch0.dat
			mv Rebel_ch8_pch1.dat freertos_kernel_ch8_pch1.dat

			mv Rebel_ch9_pch0.dat freertos_kernel_ch9_pch0.dat
			mv Rebel_ch9_pch1.dat freertos_kernel_ch9_pch1.dat

			mv Rebel_ch10_pch0.dat freertos_kernel_ch10_pch0.dat
			mv Rebel_ch10_pch1.dat freertos_kernel_ch10_pch1.dat

			mv Rebel_ch11_pch0.dat freertos_kernel_ch11_pch0.dat
			mv Rebel_ch11_pch1.dat freertos_kernel_ch11_pch1.dat

			mv Rebel_ch12_pch0.dat freertos_kernel_ch12_pch0.dat
			mv Rebel_ch12_pch1.dat freertos_kernel_ch12_pch1.dat

			mv Rebel_ch13_pch0.dat freertos_kernel_ch13_pch0.dat
			mv Rebel_ch13_pch1.dat freertos_kernel_ch13_pch1.dat

			mv Rebel_ch14_pch0.dat freertos_kernel_ch14_pch0.dat
			mv Rebel_ch14_pch1.dat freertos_kernel_ch14_pch1.dat

			mv Rebel_ch15_pch0.dat freertos_kernel_ch15_pch0.dat
			mv Rebel_ch15_pch1.dat freertos_kernel_ch15_pch1.dat
		fi

		printf "freeRTOS kernel DONE\n"
	fi
	cd - > /dev/null
fi
