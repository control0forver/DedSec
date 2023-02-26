#!/bin/bash
cd $(realpath $(dirname $0))

#globs
export OUTPUT_DIR='out'
export SOURCE_DIR='src'

checkPkg() {
    echo -en "\033[0m"
    echo "Package Checking for \"$1\""
    if ! type $1 >/dev/null 2>&1;then
        echo -en "\033[31;1m"
        echo "Package \"$1\" Uninstalled"
        echo -en "\033[0m\n"
    else
        echo -en "\033[32m"
        echo "Package \"$1\" Installed"
        echo -en "\033[0m\n"
    fi
}

setPermis() {
    echo 'Setting Permission'
    sudo chmod 777 -R $OUTPUT_DIR
    sudo chmod 777 $SOURCE_DIR
}

#checking out dir
echo -e '\n\033[33mStart Output Dir Checking\033[0m'

echo 'Checking Output Dir'
mkdir -p $OUTPUT_DIR $OUTPUT_DIR'/image/' $OUTPUT_DIR'/obj'
mkdir -p $SOURCE_DIR

setPermis
echo 'OK'

# clear files
echo 'cleaning build obj files'
rm -rf $OUTPUT_DIR'/obj/*'
echo 'OK'

#checking tools
echo -e '\n\033[33mStart Tools Checking\033[0m'
checkPkg nasm
checkPkg gcc
checkPkg g++
checkPkg i686-linux-gnu-gcc
checkPkg grub-mkrescue
echo 'OK'


#building
echo -e '\n\033[33mStart Building\033[0m'

echo 'Building Bootloader'
$SOURCE_DIR'/build_bootloader.sh' $(realpath $OUTPUT_DIR)
echo 'OK'

echo 'Building Kernel'
$SOURCE_DIR'/build_kernel.sh' $(realpath $OUTPUT_DIR)
echo 'OK'

echo 'Building Image'
$SOURCE_DIR'/build_image.sh' $(realpath $OUTPUT_DIR)
echo 'OK'
