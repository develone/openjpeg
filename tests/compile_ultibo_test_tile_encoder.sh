#!/bin/bash
rm -f test_tile_encoder.o
arm-none-eabi-gcc -L../src/lib/openjp2 -lopenjp2 -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c test_tile_encoder.c
arm-none-eabi-objdump -d test_tile_encoder.o > dis_test_tile_encoder.txt
arm-none-eabi-objdump -d ../src/lib/openjp2/libopenjp2.a > dis_libopenjp2.txt
