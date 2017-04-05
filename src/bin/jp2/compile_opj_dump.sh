#!/bin/bash
rm -f *.o opj_dump
#several headers are needed to create and obj file.
cp ../../../opj_config.h .
cp ../../../src/lib/openjp2/openjpeg.h .
cp ../../../src/lib/openjp2/opj_stdint.h .
cp ../common/opj_getopt.h .
cp ../common/format_defs.h .
cp ../common/opj_string.h .
cp ../../../build/src/bin/common/opj_apps_config.h .
cp ../../../opj_config_private.h .
cp ../../../src/lib/openjp2/opj_inttypes.h .

gcc -O3  -c opj_dump.c -o opj_dump.o
gcc -O3  -c convert.c -o convert.o
gcc -O3  -c index.c -o index.o
gcc -O3  -c opj_getopt.c -o opj_getopt.o
gcc opj_dump.o convert.o index.o opj_getopt.o -L ../../../build/bin -lopenjp2 -lm -lpthread -o opj_dump
