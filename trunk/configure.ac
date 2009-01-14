#
# configure.ac
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

AC_INIT([tscomagcv], [0.1], [mjk at users.berlios.de])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_MD5SUM
AC_PROG_GREP
ACLTX_PROG_PDFLATEX
ACLTX_PROG_MAKEINDEX
ACLTX_PROG_BIBTEX
ACLTX_KOMA_SCRIPT
# Note: We don't test for LaTeX packages from base, tools and required,
#       because they have to be at every valid LaTeX installation.
ACLTX_PACKAGE(lmodern,scrartcl,ltx_pkg_lmodern,[],
	      [AC_MSG_ERROR([Unable to find the font package lmodern])])
ACLTX_PACKAGE(xspace,scrartcl,ltx_pkg_xspace,[],
	      [AC_MSG_ERROR([Unable to find the xspace package])])
ACLTX_PACKAGE(svn,scrartcl,ltx_pkg_svn,[],
	      [AC_MSG_ERROR([Unable to find the svn package])])
ACLTX_PACKAGE(booktabs,scrartcl,ltx_pkg_booktabs,[],
	      [AC_MSG_ERROR([Unable to find the booktabs package])])
ACLTX_PACKAGE(tabularx,scrartcl,ltx_pkg_tabularx,[],
	      [AC_MSG_ERROR([Unable to find the tabularx package])])
ACLTX_PACKAGE(hyperref,scrartcl,ltx_pkg_hyperref,[],
	      [AC_MSG_ERROR([Unable to find the hyperref package])])
ACLTX_PACKAGE(xcolor,scrartcl,ltx_pkg_xcolor,[],
	      [AC_MSG_ERROR([Unable to find the xcolor package])])
ACLTX_PACKAGE(colortbl,scrartcl,ltx_pkg_colortbl,[],
	      [AC_MSG_ERROR([Unable to find the colortbl package])])
ACLTX_PACKAGE(amsmath,scrartcl,ltx_pkg_amsmath,[],
	      [AC_MSG_ERROR([Unable to find the amsmath package])])
AC_CONFIG_FILES([
	Makefile
	doc/Makefile
	doc/doc.latex/Makefile
])
AC_OUTPUT
