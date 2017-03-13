#/*
# * The copyright in this software is being made available under the 2-clauses 
# * BSD License, included below. This software may be subject to other third 
# * party and contributor rights, including patent rights, and no such rights
# * are granted under this license.
# *
# * Copyright (c) 2002-2014, Universite catholique de Louvain (UCL), Belgium
# * Copyright (c) 2002-2014, Professor Benoit Macq
# * Copyright (c) 2003-2014, Antonin Descampe
# * Copyright (c) 2003-2009, Francois-Olivier Devaux
# * Copyright (c) 2005, Herve Drolon, FreeImage Team
# * Copyright (c) 2002-2003, Yannick Verschueren
# * Copyright (c) 2001-2003, David Janssens
# * Copyright (c) 2011-2012, Centre National d'Etudes Spatiales (CNES), France 
# * Copyright (c) 2012, CS Systemes d'Information, France
# *
# * All rights reserved.
# *
# * Redistribution and use in source and binary forms, with or without
# * modification, are permitted provided that the following conditions
# * are met:
# * 1. Redistributions of source code must retain the above copyright
# *    notice, this list of conditions and the following disclaimer.
# * 2. Redistributions in binary form must reproduce the above copyright
# *    notice, this list of conditions and the following disclaimer in the
# *    documentation and/or other materials provided with the distribution.
# *
# * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
# * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# * POSSIBILITY OF SUCH DAMAGE.
# */


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

