################################################################################
##
## Filename: 	Makefile
##
## Project:	tttt, a simple 4x4x4 Tic-Tac-Toe Program
##
## Purpose:	A master make file to coordinate the build of all of the various
##		subdirectories of this project.
##
## Targets:
##
##	doc	Build any documentation
##
##	tttt	Just build the main program for the host computer
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
all:	libopenjp2.a

#doc:
#	$(MAKE) -C doc

libopenjp2.a:
	$(MAKE) -C src/lib/openjp2 LIBRARY

