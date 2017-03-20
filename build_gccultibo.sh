#!/bin/bash
rm -f *.o *.a
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c bio.c -o bio.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c cidx_manager.c -o cidx_manager.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c cio.c -o cio.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c dwt.c -o dwt.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c event.c -o event.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c function_list.c -o function_list.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c image.c -o image.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c invert.c -o invert.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c j2k.c -o j2k.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c jp2.c -o jp2.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c mct.c -o mct.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c mqc.c -o mqc.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c openjpegcc -o openjpeg.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c opj_clock.c -o opj_clock.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c opj_malloc.c -o opj_malloc.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c phix_manager.c -o phix_manager.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c pi.c -o pi.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c ppix_manager.c -o ppix_manager.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c raw.c -o raw.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c t1.c -o t1.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c t1_generate_luts.c -o t1_generate_luts.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c t2.c -o t2.o 
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c tcd.c -o tcd.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c tgt.c -o tgt.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c thix_manager.c -o thix_manager.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c thread.c -o thread.o
arm-none-eabi-gcc -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c tpix_manager.c -o tpix_manager.o
arm-none-eabi-ar rcs libopenjp2.a *.o
arm-none-eabi-ar t libopenjp2.a > libopenjp2_obj.txt
cp libopenjp2.a ~/jpeg-2000-test/bare-metal/dwt
echo "The word count here should be 20"
echo "the word count in jpeg-2000-test/bare=metal/dwt"
echo "when ./compile.sh is executed should be 21"
echo "Word cpunt libopenjp2_obj.txt in src/lib/openjp2"
wc libopenjp2_obj.txt 
#The steps below are from the file jpeg-2000-test/zip/uart_test_code/Makefile 
#20 of the 29 files that compile with arm-none-eabi-gcc compiler
#two of files dwt.c & opj_malloc.c are copies from 
#jpeg-2000-test/bare=metal/dwt
#opj_includes.h requires memory.h commented out 
#These files when compiled create the libopenjp2.a
#The libopenjp2.a plus the dwtlift.o created in the jpeg-2000-test/bare=metal/dwt
#are used to create kernel7.img which runs on Ultibo

#CROSS   := arm-none-eabi-
#CC      := $(CROSS)gcc
#OBJECTS := $(addprefix $(OBJDIR)/,$(subst .c,.o,$(SOURCES)))
#SOURCES := bio.c dwt.c event.c function_list.c image.c invert.c j2k.c jp2.c mct.c \
#mqc.c opj_clock.c opj_malloc.c pi.c raw.c t1_generate_luts.c t1.c t2.c tcd.c \
#tgt.c thread.c
#CFLAGS  :=  -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c

