#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([getkey], [0.1], [getkey.amjith@gmail.com])
AM_INIT_AUTOMAKE([getkey], [0.1])
AC_CONFIG_SRCDIR([list.h])
#AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lX11':
AC_CHECK_LIB([X11], [XOpenDisplay], [],[
			  echo "X11 library is required for this program" 
			  exit -1])
# FIXME: Replace `main' with a function in `-lXtst':
AC_CHECK_LIB([Xtst], [XRecordCreateContext], [],[
			  echo "Xtst devel library is missing. Xtst is required for this program" 
			  exit -1])
# FIXME: Replace `main' with a function in `-lxosd':
AC_CHECK_LIB([xosd], [xosd_create], [],[
			  echo "xosd devel library is missing. xosd is required for this program"
			  exit -1])

# Checks for header files.
AC_PATH_X
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
