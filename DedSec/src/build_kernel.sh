#!/bin/bash
cd $(realpath $(dirname $0))
cd kernel

i686-linux-gnu-gcc -m32 -c kernel_entry.cpp\
 -o $1'/obj/kernel.o'\
 -ffreestanding\
 -fno-exceptions\
 -fno-rtti
