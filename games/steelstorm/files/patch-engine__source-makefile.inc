--- engine_source/makefile.inc.orig	2010-09-08 08:57:48.000000000 +0400
+++ engine_source/makefile.inc	2010-09-10 21:44:31.000000000 +0400
@@ -188,7 +188,7 @@
 
 
 # Compilation
-CFLAGS_COMMON=$(CFLAGS_MAKEDEP) $(CFLAGS_PRELOAD) $(CFLAGS_FS) $(CFLAGS_CG) $(CFLAGS_WARNINGS) $(CFLAGS_LIBJPEG) $(CFLAGS_D3D) $(CFLAGS_CRYPTO)
+CFLAGS_COMMON=$(CFLAGS) $(CFLAGS_MAKEDEP) $(CFLAGS_PRELOAD) $(CFLAGS_FS) $(CFLAGS_CG) $(CFLAGS_WARNINGS) $(CFLAGS_LIBJPEG) $(CFLAGS_D3D) $(CFLAGS_CRYPTO)
 CFLAGS_DEBUG=-ggdb
 CFLAGS_PROFILE=-g -pg -ggdb -fprofile-arcs
 CFLAGS_RELEASE=