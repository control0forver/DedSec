#!/bin/bash
cd $(realpath $(dirname $0))
cd kernel

i686-linux-gnu-gcc -m32 -c kernel_entry.cpp\
 -I .\
 -o $1'/obj/kernel.o'\
 -Wall\
 -ffreestanding\
 -fno-exceptions\
 -fno-rtti
 
