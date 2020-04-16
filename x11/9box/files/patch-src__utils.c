--- src/utils.c.orig	2002-10-30 19:30:09.000000000 +0800
+++ src/utils.c	2011-09-08 14:27:51.000000000 +0800
@@ -89,8 +89,8 @@ resize_box_for_client(Box * box, int cli
 
   XGetGeometry(box->dpy, box->boxed_windows[client]->client,
 	       &root_return, &x_return, &y_return, 
-	       &width_return, &height_return,
-	       &border_width_return, &depth_return);
+	       (unsigned int *)&width_return, (unsigned int*)&height_return,
+	       (unsigned int *)&border_width_return, (unsigned int *)&depth_return);
 
   XResizeWindow(box->dpy, box->win, width_return, height_return+button_height());
   box->box_width = width_return;
