#!/bin/bash
cd $(realpath $(dirname $0))
cd bootloader

nasm -f elf32\
 boot.asm\
 -o $1'/obj/boot.o'
