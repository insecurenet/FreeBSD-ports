--- ./memdump.c.orig	2005-08-30 23:04:18.000000000 +0000
+++ ./memdump.c	2007-11-30 18:54:11.000000000 +0000
@@ -107,8 +107,7 @@
 #define SUPPORTED
 #endif
 
-#if defined(FREEBSD2) || defined(FREEBSD3) || defined(FREEBSD4) \
-	|| defined(FREEBSD5) || defined(FREEBSD6) || defined(FREEBSD7) \
+#if defined(FREEBSD) \
 	|| defined(OPENBSD2) || defined(OPENBSD3) \
 	|| defined(BSDI2) || defined(BSDI3) || defined(BSDI4)
 #include <sys/param.h>
