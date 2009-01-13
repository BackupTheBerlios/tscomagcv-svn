dnl @synopsis ACLTX_KOMA_SCRIPT([ACTION-IF-NOT-FOUND])
dnl
dnl This macro test if KOMA-Script is installed and fail (default)
dnl with a error message if not
dnl
dnl @category LaTeX
dnl @author Markus Kohm <mjk at users.berlios.de>
dnl @version 2000-01-13
dnl @license LGPL

AC_DEFUN([ACLTX_KOMA_SCRIPT],[
ACLTX_CLASS(scrartcl,komascript,[],[m4_ifval([$1],[$1],AC_MSG_ERROR([Unable to find the KOMA-Script class scrartcl]))])
])
