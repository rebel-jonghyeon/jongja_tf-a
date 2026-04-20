#!/bin/bash

GPTfile="$PWD/scripts/p1.part"

if [ ! -f $GPTfile ]; then
    echo "$GPTfile doesn't exist, Create new image"

    truncate -s 7680KiB $GPTfile
fi

if [ ! $# -eq 4 ]; then
    echo "Usage : fuse_gpt_partition.sh id, name, image, size"
    exit 1
fi

id=$1
name=$2
image=$3
size=$4
echo "id : ${id}, name : ${name}, image : ${image}, size : +${size}KiB"

if [ ! -f $image ]; then
    echo "!!! $image doesn't exist !!!"
    exit 1
fi

## partition
sgdisk -a 128 -n 0:0:+${size}KiB -c 0:${name} -p $GPTfile

## image fusing
file=$image
size=`wc -c < $file`
start_sector=$(sgdisk -i ${id} $GPTfile | grep "First sector" | awk '{print $3}')
start=$((start_sector*512))
echo "$file : $start : $size"
dd if=$file of=$GPTfile bs=1 seek=$start count=$size conv=notrunc

sgdisk -i ${id} $GPTfile
