--- modules/shellcode-signatures/sch_namespace_bindfiletransfer.cpp.orig
+++ modules/shellcode-signatures/sch_namespace_bindfiletransfer.cpp
@@ -27,6 +27,7 @@
 
 /* $Id: sch_namespace_bindfiletransfer.cpp 499 2006-04-08 18:40:14Z common $ */
 
+#include <cstdio>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
