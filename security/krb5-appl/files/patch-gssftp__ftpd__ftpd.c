--- gssftp/ftpd/ftpd.c.orig	Wed Jan  9 14:26:51 2002
+++ gssftp/ftpd/ftpd.c	Thu Jan 10 19:00:13 2002
@@ -487,7 +487,13 @@
 #ifndef LOG_DAEMON
 #define LOG_DAEMON 0
 #endif
-	openlog("ftpd", LOG_PID | LOG_NDELAY, LOG_DAEMON);
+
+#ifndef LOG_FTP
+#define FACILITY	LOG_DAEMON
+#else
+#define FACILITY	LOG_FTP
+#endif
+	openlog("ftpd", LOG_PID | LOG_NDELAY, FACILITY);
 
 	addrlen = sizeof (his_addr);
 	if (getpeername(0, (struct sockaddr *)&his_addr, &addrlen) < 0) {
