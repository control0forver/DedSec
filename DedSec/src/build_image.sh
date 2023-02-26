#!/bin/bash
cd $(realpath $(dirname $0))

# link system file
echo 'linking system'
i686-linux-gnu-gcc -m32 $1'/obj/boot.o' $1'/obj/kernel.o' -T 'linker.ld' -o $1'/obj/system.bin' -nostdlib -nodefaultlibs -lgcc
echo 'OK'

# make iso dir
mkdir -p $1'/obj/grub_boot/iso'
mkdir -p $1'/obj/grub_boot/iso/boot' $1'/obj/grub_boot/iso/boot/grub'

echo 'downloading system image files'
# copy configs&system files
cp $1'/obj/system.bin' $1'/obj/grub_boot/iso/boot/'
cp 'grub/grub.cfg' $1'/obj/grub_boot/iso/boot/grub/'
echo 'OK'

echo 'start making image'
# making
grub-mkrescue $1'/obj/grub_boot/iso' --output=$1'/obj/grub_boot/system.iso'
echo 'OK'

#dd if=$1'/obj/boot.o' of=$1'/image/system.img' bs=512 count=1 conv=notrunc
#dd if=$1'/obj/kernel.o' of=$1'/image/system.img' bs=512 seek=1 conv=notrunc
