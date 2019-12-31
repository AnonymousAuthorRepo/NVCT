#!/bin/bash

#HOME_PATH=$HOME
PIN_PATH=$HOME"/NVCT/pin-2.14-71313-gcc.4.4.7-linux/"
NVCT_PATH=$HOME"/NVCT/tests/"
echo $PIN_PATH

cmd="time "$PIN_PATH"intel64/bin/pinbin -p32 "$PIN_PATH"ia32/bin/pinbin -t "$NVCT_PATH"obj-intel64/dcache.so -- "$1
#echo $cmd

if [ "$1" != "" ]; then
    echo "Crash Test"
    $cmd
else
    echo "Enter the path to application you want to do crash test!"
fi

