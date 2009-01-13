dnl @synopsis AC_PROG_GREP
dnl
dnl This macro find a grep application and set the variable
dnl grep to the name of the application or to no if not found if
dnl ACTION-IF-NOT-FOUND is not specified, configure fail when then
dnl application is not found.
dnl
dnl @category general
dnl @author Markus Kohm <mjk at users.berlios.de>
dnl @version 2009-01-20
dnl @license LGPL

AC_DEFUN([AC_PROG_GREP],[
AC_CHECK_PROGS(grep,[grep],no)
if test $grep = "no" ;
then
	ifelse($#,0,[AC_MSG_ERROR([Unable to find the grep application])],
        $1)
fi
])
