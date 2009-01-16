## Process this file with automake to produce Makefile.in
#
# Makefile to produce meta++
# Copyright (c) Markus Kohm, 2009
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

lib_LTLIBRARIES = libcomag_meta.la
libcomag_meta_la_SOURCES = comag_meta.cpp
libcomag_meta_la_LDFLAGS = -module -release $(VERSION) -export-dynamic $(LDFLAGS)
if DEVEL
include_HEADERS = comag_meta.h
endif

bin_PROGRAMS = meta
meta_SOURCES = meta_main.cpp comag_meta.h
meta_LDADD = $(lib_LTLIBRARIES)
