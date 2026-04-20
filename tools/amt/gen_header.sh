#!/bin/bash
export DEST_LOC="../../bootloader/cp/tf-a/include/drivers/hbm3"

if [ -n "$1" ]; then

	python2.7 useq_asm.py -i $1.asm -o $1.memh

	python2.7 useq_emu.py -i $1.memh

	if [ $? != 0 ]; then
		echo "Error happen in $1.memh"
		exit 1
	fi

	echo "generate header: $1"
	python2.7 gen_amt_header.py $1

	cp -f ${1}.h $DEST_LOC

else

	for file in *.asm
	do

		filename=$(basename "$file")
		name="${filename%.*}"

		python2.7 useq_asm.py -i $name.asm -o $name.memh

		python2.7 useq_emu.py -i $name.memh

		if [ $? != 0 ]; then
			echo "Error happen in $name.memh"
			exit 1
		fi

		echo "generate header: $name"
		python2.7 gen_amt_header.py $name

		cp -f ${name}.h $DEST_LOC

	done

fi


