--- libicq2000/libicq2000/sigslot.h.orig	2010-10-26 17:19:06.000000000 +0000
+++ libicq2000/libicq2000/sigslot.h
@@ -84,6 +84,7 @@
 
 #include <set>
 #include <list>
+#include <cstddef>
 
 #if defined(SIGSLOT_PURE_ISO) || (!defined(WIN32) && !defined(SIGSLOT_USE_POSIX_THREADS))
 #       define _SIGSLOT_SINGLE_THREADED
