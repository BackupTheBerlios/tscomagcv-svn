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

AC_INIT([comag], [0.1], [mjk at users.berlios.de])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_LIBTOOL
AC_PROG_CXX
AC_PATH_PROG(doxygen,[doxygen],[],[${PATH}])

AC_ENABLE_SHARED([no])

AC_ARG_ENABLE(devel,
[  --enable-devel          Turn on developer parts],
[case "${enableval}" in
  yes) devel=true ;;
  no)  devel=false ;;
  *) AC_MSG_ERROR(bad value ${enableval} for --enable-devel) ;;
esac],[devel=false])
AM_CONDITIONAL(DEVEL, test x$devel = xtrue)

AC_CONFIG_FILES([
	Makefile
	source/Makefile
])

if test "x$package_kfile_enabled" == "xyes"; then
   AC_CONFIG_SUBDIRS([kde3/kfile_metadat])
fi

AC_OUTPUT
