dnl @synopsis ACLTX_PROG_HTLATEX
dnl
dnl This macro find a htlatex application and set the variable
dnl htlatex to the name of the application or to no if not found if
dnl ACTION-IF-NOT-FOUND is not specified, configure fail when then
dnl application is not found.
dnl
dnl @category LaTeX
dnl @author Markus Kohm <mjk at users.berlios.de>
dnl @version 2009-01-19
dnl @license LGPL

AC_DEFUN([ACLTX_PROG_HTLATEX],[
AC_CHECK_PROGS(htlatex,[htlatex],no)
if test $htlatex = "no" ;
then
	ifelse($#,0,[AC_MSG_ERROR([Unable to find the htlatex application])],
        $1)
fi
])
