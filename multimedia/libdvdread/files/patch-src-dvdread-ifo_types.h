--- src/dvdread/ifo_types.h.orig	2015-06-27 19:35:59.043370000 +0200
+++ src/dvdread/ifo_types.h	2015-06-27 19:37:10.885577000 +0200
@@ -32,7 +32,7 @@
 
 #if defined(__GNUC__)
 #if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
-#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
+#if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)) && !defined(__clang__)
 #define ATTRIBUTE_PACKED __attribute__ ((packed,gcc_struct))
 #else
 #define ATTRIBUTE_PACKED __attribute__ ((packed))
