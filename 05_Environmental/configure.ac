#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([TEST-WINDOW], [0.1], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([Window.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([ncursesw], [initscr])
AC_CHECK_LIB([pcre2-8], [pcre2_match_8])
             
# Checks for header files.
AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([ncurses.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_ARG_ENABLE([utf], AS_HELP_STRING([--disable-utf], [Flag PCRE2_UCP will not be used]))
AS_IF([test "x$enable_utf" = "xno"], [
    AC_DEFINE(DISABLE_UTF, [], [Flag PCRE2_UCP will be used])
])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
