--- lib/RK/ncache.c.orig	2003-09-17 17:50:52.000000000 +0900
+++ lib/RK/ncache.c	2008-09-20 01:46:07.000000000 +0900
@@ -27,7 +27,7 @@
 #include	"RKintern.h"
 
 #define	NCHASH		101
-#define	hash(x)		((int)((x)%NCHASH))
+#define	hash(x)		((int)(((unsigned long)(x))%NCHASH))
 
 static struct ncache	Nchash[NCHASH];
 static struct ncache	Ncfree;
