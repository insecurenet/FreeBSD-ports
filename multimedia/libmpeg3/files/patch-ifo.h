--- ./ifo.h.orig	Thu Apr 21 07:59:43 2005
+++ ./ifo.h	Sat Jul 22 18:02:04 2006
@@ -15,6 +15,8 @@
 #define IFO_OFFSET_SUBPIC	0x0250
 
 
+typedef off_t __off64_t;
+
 // for debug and error output
 
 /**
