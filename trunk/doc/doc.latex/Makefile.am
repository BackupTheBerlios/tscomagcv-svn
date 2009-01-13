## Process this file with automake to produce Makefile.in
#
# Makefile for the latex documentation
# Copyright (c) Markus Kohm, 2009
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License.
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

LATEXMD5SUFFIXES = .aux .idx .ind
LATEXTMPSUFFIXES = .log .aux .toc .lot .lof .idx .ind .ilg .bbl .blg

pdfdir     = $(docdir)/pdf
pdf_DATA   = data.pdf

tex_SOURCE = $(foreach pdffile,$(pdf_DATA),\
                       $(addsuffix .tex,$(basename $(pdffile))))

CLEANFILES = $(foreach suffix,$(LATEXTMPSUFFIXES)\
                             ,$(foreach pdffile,$(pdf_DATA),\
                                        $(addsuffix $(suffix),\
                                                    $(basename $(pdffile)))))

include $(top_srcdir)/Makefile.rules/Makefile.latex-rules

all:	$(pdf_DATA)

data.pdf: data.tex
	$(run_pdflatex)