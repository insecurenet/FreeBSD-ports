--- src/gldit/cairo-dock-file-manager.c.orig	2014-10-15 14:16:34 UTC
+++ src/gldit/cairo-dock-file-manager.c
@@ -21,7 +21,11 @@
 #include <string.h>      // memset
 #include <sys/stat.h>    // stat
 #include <fcntl.h>  // open
+#if defined (__FreeBSD__) || defined (__DragonFly__)
+#include <sys/socket.h>
+#else
 #include <sys/sendfile.h>  // sendfile
+#endif
 #include <errno.h>  // errno
 
 #include "gldi-config.h"
@@ -500,7 +504,7 @@ gboolean cairo_dock_copy_file (const gch
 	{
 		// perform in-kernel transfer (zero copy to user space)
 		int size;
-		#ifdef __FreeBSD__
+		#if defined (__FreeBSD__) || defined (__DragonFly__)
 		size = sendfile (src_fd, dest_fd, 0, stat.st_size, NULL, NULL, 0);
 		#else  // Linux >= 2.6.33 for being able to have a regular file as the output socket
 		size = sendfile (dest_fd, src_fd, NULL, stat.st_size);  // note the inversion between both calls ^_^;
