#!/bin/bash

awk '
NR > 1 { printf "\n" }
{
    printf "%s", substr($0,7,2) substr($0,5,2) substr($0,3,2) substr($0,1,2)
}' "${1:-dev/stdin}"
