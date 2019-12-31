#!/bin/bash
# My first script

#HOME_PATH=$HOME
PIN_PATH=$HOME"/NVCT/pin-2.14-71313-gcc.4.4.7-linux/"
NVCT_PATH=$HOME"/NVCT/tests/"

for k in $( seq 1 50 )
do
  screen_name="my_screen"
  screen -dmS $screen_name${k}

  cmd=$"time "$PIN_PATH"intel64/bin/pinbin -p32 "$PIN_PATH"ia32/bin/pinbin -t "$NVCT_PATH"obj-intel64/dcache.so -- /home/cc/NVCT/Benchmarks/CrashTests/NPB3.3-OMP-C/bin/cg.C.x";

  screen -x -S $screen_name${k} -p 0 -X stuff "$cmd"
  screen -x -S $screen_name${k} -p 0 -X stuff $'\n'

done
