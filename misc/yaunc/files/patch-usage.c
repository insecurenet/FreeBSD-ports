--- usage.c.orig	Sun Apr 27 19:11:03 2003
+++ usage.c	Sun Apr 27 19:11:26 2003
@@ -10,7 +10,7 @@
 	fprintf(stderr, "\n");
 	fprintf(stderr, "Options:\n");
 	fprintf(stderr, "\t-f <config file> - use the specified config file instead of \n");
-	fprintf(stderr, "\t                   of /etc/yaunc.conf\n");
+	fprintf(stderr, "\t                   of ${PREFIX}/CONFFILE \n");
 	fprintf(stderr, "\t-h               - display this help\n");
 	fprintf(stderr, "\n");
 	exit(0);
