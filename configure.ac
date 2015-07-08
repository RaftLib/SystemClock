#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([SystemClock], [1.2], [jonathan.c.beard@gmail.com])
AC_CONFIG_SRCDIR([src/Clock.cpp])
#AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
# Checks for programs.
AC_PROG_CXX
LT_INIT
# Checks for libraries.

case $host_os in 
   darwin*)
      os_bsd=no
      os_darwin=yes
      os_linux=no
   ;;
   linux*)
      os_bsd=no
      os_darwin=no
      os_linux=yes
   ;;
   bsd*)
      os_bsd=yes
      os_darwin=no
      os_linux=no
   ;;
esac

AM_CONDITIONAL([DARWIN], [test x$os_darwin = xyes]) 
AM_CONDITIONAL([LINUX],  [test x$os_linux = xyes]) 

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile testsuite/Makefile src/Makefile])
AC_OUTPUT
