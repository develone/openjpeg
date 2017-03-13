################################################################################
##
## Filename: 	Makefile
##
## Project:	tttt, a simple 4x4x4 Tic-Tac-Toe Program
##
## Purpose:	To coordinate the build of the 4x4x4 Tic-Tac-Toe program of
##		course!
##
##	This build is customized to work with cross compilers by two environment
##	variables:
##
##	$(ARCH)	Specifies the name of your architecture.  All object files
##		will be placed into a directory with $(ARCH) as its suffix,
##		or obj-pc if none is given.
##
##	$(CROSS) specifies the prefix of the cross-compiler.  For the ZipCPU,
##		this is currently "zip-".  For other machines, other prefixes
##		may be appropriate.  If no prefix is given, the Makefile will
##		assume that the compiler is given by "gcc".
##
## Targets:
##
##	all	Builds the program for the current architecture
##
##	depends	Rebuilds the dependency list for the current architecture
##
##	clean	Remove all build products for the current architecture
##
##	pc	Builds the program for the host architecture, ARCH=pc and
##		CROSS= (nothing).  This is the build you will get from using
##		gcc.
##
##	tags	Build a tags file, suitable for searching through the source
##		code to look for definitions of things.
##
##	zip	Build this program for the ZipCPU.
##
##
##
## Creator:	Dan Gisselquist, Ph.D.
##		Gisselquist Technology, LLC
##
################################################################################
##
## Copyright (C) 2017, Gisselquist Technology, LLC
##
## This program is free software (firmware): you can redistribute it and/or
## modify it under the terms of  the GNU General Public License as published
## by the Free Software Foundation, either version 3 of the License, or (at
## your option) any later version.
##
## This program is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
## FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
## for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program.  (It's in the $(ROOT)/doc directory, run make with no
## target there if the PDF file isn't present.)  If not, see
## <http://www.gnu.org/licenses/> for a copy.
##
## License:	GPL, v3, as defined and found on www.gnu.org,
##		http://www.gnu.org/licenses/gpl.html
##
##
################################################################################
##
##

LFLAGS := rcs

MKLIB := arm-none-eabi-ar
CROSS   := arm-none-eabi-
CC      := $(CROSS)gcc
#LIBOPENJP := 
#OBJECTS := $(addprefix $(OBJDIR)/,$(subst .c,.o,$(SOURCES)))
OBJDIR  := obj-libopenj2
SOURCES := bio.c dwt.c event.c function_list.c image.c invert.c j2k.c jp2.c mct.c mqc.c opj_clock.c opj_malloc.c pi.c raw.c t1_generate_luts.c t1.c t2.c tcd.c tgt.c thread.c
CFLAGS  :=  -O2 -mabi=aapcs -marm -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=hard -c

#all: $(OBJDIR)/ libopenjp2
all: $(OBJDIR)/ 

$(OBJDIR)/:
	@bash -c "if [ ! -e $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi"

%.o: $(OBJDIR)/%.o
	$(CC) $(CFLAGS) -c $< -o $@

*.o: $(OBJDIR)/%.o
	$(CC) $(CFLAGS) -c $< -o $@




LIBOBJ :
	bio.o dwt.o event.o function_list.o image.o invert.o j2k.o jp2.o mct.o mqc.o opj_clock.o opj_malloc.o pi.o raw.o t1_generate_luts.o t1.o t2.o tcd.o tgt.o thread.o

LIBRARY :
	$(MKLIB) $(LFLAGS) libopenjp2.a $(OBJDIR)/*.o

.PHONY: clean
clean:
	rm -rf $(OBJDIR)/ libopenjp2.a
	
#arm-none-eabi-ar rcs libopenjp2.a obj-libopenj2/*.o
