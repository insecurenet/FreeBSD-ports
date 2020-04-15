--- serialoverip.c.orig	2002-03-08 22:37:09 UTC
+++ serialoverip.c
@@ -34,6 +34,7 @@
 #include <fcntl.h>
 #include <termios.h>
 #include <signal.h>
+#include <strings.h>
 
 #define MAXMESG 2048
 
@@ -42,20 +43,19 @@ char*pname;
 int s[2],st[2];
 
 void help(){
-	fprintf(stderr,"\
-SerialOverIP version 1.0, Copyright (C) 2002 Stefan-Florin Nicola <sten@fx.ro>
-SerialOverIP comes with ABSOLUTELY NO WARRANTY. This is free software, and you
-are welcome to redistribute it under GNU General Public License.
- Usage: %s <source1> <source2>
-  where <source1> and <source2> are one of the folowing:
-    -s <IP> <port>                 UDP server on IP:port
-    -c <IP> <port>                 UDP client for server IP:port
-    -d <device> sss-dps            local serial device
-       sss is speed (50,..,230400)
-       d is data bits (5,6,7,8)
-       p is parity type (N,E,O)
-       s is stop bits (1,2)
-",pname);
+	fprintf(stderr,
+"SerialOverIP version 1.0, Copyright (C) 2002 Stefan-Florin Nicola <sten@fx.ro>\n"\
+"SerialOverIP comes with ABSOLUTELY NO WARRANTY. This is free software, and you\n"\
+"are welcome to redistribute it under GNU General Public License.\n"\
+" Usage: %s <source1> <source2>\n"\
+" where <source1> and <source2> are one of the folowing:\n"\
+"    -s <IP> <port>                 UDP server on IP:port\n"\
+"    -c <IP> <port>                 UDP client for server IP:port\n"\
+"    -d <device> sss-dps            local serial device\n"\
+"       sss is speed (50,..,230400)\n"\
+"       d is data bits (5,6,7,8)\n"\
+"       p is parity type (N,E,O)\n"\
+"       s is stop bits (1,2)\n",pname);
 	return;
 }
 
