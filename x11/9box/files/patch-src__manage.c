--- src/manage.c.orig	2002-12-05 05:44:23.000000000 +0800
+++ src/manage.c	2011-09-08 14:33:13.000000000 +0800
@@ -21,6 +21,8 @@
 
 #include "dat.h"
 #include "fns.h"
+#include <stdio.h>
+#include <stdlib.h>
 
 void
 resize_window(BoxedWindow * window)
@@ -30,8 +32,8 @@ resize_window(BoxedWindow * window)
   
   XGetGeometry(window->box->dpy, window->box->win,
 	       &root_return, &x_return, &y_return, 
-	       &width_return, &height_return,
-	       &border_width_return, &depth_return);
+	       (unsigned int *)&width_return, (unsigned int *)&height_return,
+	       (unsigned int *)&border_width_return, (unsigned int *)&depth_return);
   XMoveWindow(window->box->dpy, window->button,
 	      window->number * BUTTON_DEFAULT_WIDTH, height_return - button_height());
   printf(">> %d; %d\n", width_return, height_return);
@@ -144,8 +146,8 @@ update_buttons_position(Box * box)
   
   XGetGeometry(box->dpy, box->win,
 	       &root_return, &x_return, &y_return, 
-	       &width_return, &height_return,
-	       &border_width_return, &depth_return);
+	       (unsigned int *)&width_return, (unsigned int *)&height_return,
+	       (unsigned int *)&border_width_return, (unsigned int *)&depth_return);
 
   for (i=0; i<MAX_BOXED_WINDOWS && box->boxed_windows[i]; i++)
     {
