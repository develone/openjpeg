#!/bin/bash
rm -f *.o
rm -f libopenjp2.a

 

arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c bio.c -o bio.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c cidx_manager.c -o cidx_manager.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c cio.c -o cio.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c dwt.c -o dwt.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c event.c -o event.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c function_list.c -o function_list.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c image.c -o image.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c invert.c -o invert.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c j2k.c -o j2k.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c jp2.c -o jp2.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c mct.c -o mct.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c mqc.c -o mqc.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c openjpegcc -o openjpeg.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c opj_clock.c -o opj_clock.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c opj_malloc.c -o opj_malloc.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c phix_manager.c -o phix_manager.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c pi.c -o pi.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c ppix_manager.c -o ppix_manager.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c raw.c -o raw.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c t1.c -o t1.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c t1_generate_luts.c -o t1_generate_luts.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c t2.c -o t2.o 
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c tcd.c -o tcd.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c tgt.c -o tgt.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c thix_manager.c -o thix_manager.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c thread.c -o thread.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c tpix_manager.c -o tpix_manager.o
arm-none-eabi-gcc  -O3 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c openjpeg.c -o openjpeg.o
 
arm-none-eabi-ar rcs libopenjp2.a *.o
arm-none-eabi-ar t libopenjp2.a > libopenjp2_obj.txt
echo "The word count here should be 20"
echo "the word count in jpeg-2000-test/bare=metal/dwt"
echo "when ./compile.sh is executed should be 21"
echo "Word cpunt libopenjp2_obj.txt in src/lib/openjp2"
wc libopenjp2_obj.txt 
