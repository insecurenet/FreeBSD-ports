Fixed a bug that caused configure to disobey the enable/disable debug flag.  The debug flag will default to disabled if not specified.
--- m4/ax_debug.m4.orig	2014-02-09 11:52:42 UTC
+++ m4/ax_debug.m4
@@ -49,16 +49,18 @@ AC_DEFUN([AX_DEBUG],
     [AC_PREREQ([2.63])dnl
     AC_ARG_ENABLE([debug],
       [AS_HELP_STRING([--enable-debug],
-        [Add debug code/turns off optimizations (yes|no) @<:@default=no@:>@])],
-      [ax_enable_debug=yes
+        [Add debug code/turns off optimizations (yes|no) @<:@default=no@:>@])])
+    AS_IF([test "x$enable_debug" = "xyes"], [
+      ax_enable_debug=yes
       AC_DEFINE([DEBUG],[1],[Define to 1 to enable debugging code.])
       AX_CHECK_LIBRARY([MCHECK],[mcheck.h],[mcheck],[AX_APPEND_LINK_FLAGS([-lmcheck])])
       AX_ADD_AM_MACRO([--debug],[AM_YFLAGS])
-      AX_ADD_AM_MACRO([-D_GLIBCXX_DEBUG],[AM_CPPFLAGS])],
-      [ax_enable_debug=no
+      AX_ADD_AM_MACRO([-D_GLIBCXX_DEBUG],[AM_CPPFLAGS])
+    ], [
+      ax_enable_debug=no
       AC_SUBST([MCHECK])
-      AC_DEFINE([DEBUG],[0],[Define to 1 to enable debugging code.])])
-
+      AC_DEFINE([DEBUG],[0],[Define to 1 to enable debugging code.])
+    ])
     AC_MSG_CHECKING([for debug])
     AC_MSG_RESULT([$ax_enable_debug])
     AM_CONDITIONAL([DEBUG],[test "x${ax_enable_debug}" = "xyes"])])
