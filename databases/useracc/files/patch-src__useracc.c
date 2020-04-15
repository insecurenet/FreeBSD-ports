--- src/useracc.c.orig	Sun Oct  5 18:05:29 2003
+++ src/useracc.c	Sun Oct  5 18:05:42 2003
@@ -92,7 +92,7 @@
 #include <sys/wait.h>
 #include <time.h>
 #include <unistd.h>
-#include <varargs.h>
+#include <stdarg.h>
 
 
 #define ACCFILE   "useracc.dat"	/* default user accounts file */
@@ -299,7 +299,7 @@
 {
   int                sockfd;
 #ifndef OSF1
-  unsigned long      inadd;
+  in_addr_t          inadd;
 #else
   in_addr_t          inadd;
 #endif  
