# Source this script in GDB and run "show mpu-registers".

define _print-mpu-register
	if $argc != 2
		echo "usage: _print-mpu-register <n> <address>"
		return
	end

	set $_i = $arg0
	set $_value = $arg1
	set $_addr = (($_value & 0xFFFFFF) << 2) - 1
	set $_perm = ($_value >> 24) & 0x3
	# M/S/U
	set $_perm = $_perm == 3 ? 77 : ($_perm == 1 ? 83 : 85)
	set $_w = ($_value  >> 26) & 1 ? 87 : 46
	set $_r = ($_value  >> 27) & 1 ? 82 : 46
	set $_x = ($_value  >> 28) & 1 ? 88 : 46
	set $_start = ($_value  >> 29) & 1 ? 83 : 32
	if $_start == 83
		set $_last = 0
	end
	set $_lock =($_value  >> 31) & 1 ? 76 : 32

	printf "MPRR%02d:  | 0x%08X | 0x%08X - 0x%08X | %c    | %c%c%c  | %c     | %c      |", $_i, $_value, $_last, $_addr, $_perm, $_w, $_r, $_x, $_start, $_lock

	set $_last = $_addr + 1
end

define show mpu-registers
	set $_mpu_base = 0x70300
	set $_j = 0
	set $_last = 0


	echo Register | RAW        | Address Range           | Mode | PERM | Start | Locked |
	echo --------------------------------------------------------------------------------
	while $_j < 24
		set $_reg = $_mpu_base + (4 * $_j)
		_print-mpu-register $_j *$_reg
		set $_j = $_j + 1
		printf "\n"
	end
end


document show mpu-registers
Display and decode CMRT MPU registers
end
