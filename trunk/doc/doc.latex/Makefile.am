## Process this file with automake to produce Makefile.in
#
# Makefile for the latex documentation
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

LATEXMD5SUFFIXES = .aux .idx .ind .bbl
LATEXTMPSUFFIXES = .log .aux .toc .lot .lof .idx .ind .ilg .bbl .blg .out \
                   .lg .dvi .md5 *.html .css .4ct .4tc .idv .xref .tmp

pdfdir      = $(docdir)/doc.pdf
pdf_name    = data.pdf
pdf_DATA    = ../doc.pdf/$(pdf_name)

htmldir     = $(docdir)/doc.html
html_DATA   = ../doc.html/data*.html ../doc.html/data.css

tex_SOURCE  = $(foreach pdffile,$(pdf_name),\
                        $(addsuffix .tex,$(basename $(pdffile)))) \
              data.bib

CLEANFILES = $(foreach suffix,$(LATEXTMPSUFFIXES)\
                             ,$(foreach pdffile,$(pdf_name),\
                                        $(addsuffix $(suffix),\
                                                    $(basename $(pdffile)))))
SOURCE_EXTRA = $(tex_SOURCE)

-include $(top_srcdir)/Makefile.rules/Makefile.latex-rules

../doc.pdf/data.pdf: data.pdf
	cp data.pdf ../doc.pdf/data.pdf

data.pdf: data.tex data.bib
	$(run_pdflatex)

../doc.html/data*.html ../doc.html/data.css: data.tex data.bib
	$(run_htlatex)

.PHONY: upload

upload:
	cd ../doc.html && \
	scp *.html *.css *.png shell.berlios.de:/home/groups/tscomagcv/htdocs/
