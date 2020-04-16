--- src/xmalloc.h.orig	Sun Feb  6 10:50:42 2000
+++ src/xmalloc.h	Sun Feb  6 10:51:14 2000
@@ -1,7 +1,9 @@
 #ifndef __XMALLOC_H
 #define __XMALLOC_H
 
+#if !defined(__FreeBSD__)
 void *xmalloc(size_t size);
+#endif
 void xfree(void *ptr);
 
 #endif
