--- gdk-pixbuf/io-png.c.orig	2001-01-24 21:59:23.000000000 +0100
+++ gdk-pixbuf/io-png.c	2012-04-24 22:50:30.000000000 +0200
@@ -175,7 +175,7 @@
 		return NULL;
 	}
 
-	if (setjmp (png_ptr->jmpbuf)) {
+	if (setjmp (png_jmpbuf(png_ptr))) {
 		png_destroy_read_struct (&png_ptr, &info_ptr, &end_info);
 		return NULL;
 	}
@@ -311,7 +311,7 @@
                 return NULL;
         }
 
-	if (setjmp (lc->png_read_ptr->jmpbuf)) {
+	if (setjmp (png_jmpbuf(lc->png_read_ptr))) {
 		if (lc->png_info_ptr)
 			png_destroy_read_struct(&lc->png_read_ptr, NULL, NULL);
                 g_free(lc);
@@ -366,7 +366,7 @@
         lc->max_row_seen_in_chunk = -1;
         
         /* Invokes our callbacks as needed */
-	if (setjmp (lc->png_read_ptr->jmpbuf)) {
+	if (setjmp (png_jmpbuf(lc->png_read_ptr))) {
 		return FALSE;
 	} else {
 		png_process_data(lc->png_read_ptr, lc->png_info_ptr, buf, size);
