dnl @synopsis AC_PROG_MD5SUM
dnl
dnl This macro find a md5sum application and set the variable
dnl md5sum to the name of the application or to no if not found if
dnl ACTION-IF-NOT-FOUND is not specified, configure fail when then
dnl application is not found.
dnl
dnl @category general
dnl @author Markus Kohm <mjk at users.berlios.de>
dnl @version 2009-01-20
dnl @license LGPL

AC_DEFUN([AC_PROG_MD5SUM],[
AC_CHECK_PROGS(md5sum,[md5sum],no)
if test $md5sum = "no" ;
then
	ifelse($#,0,[AC_MSG_ERROR([Unable to find the md5sum application])],
        $1)
fi
])
