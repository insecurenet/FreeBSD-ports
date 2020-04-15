--- uigtk.c.orig	2002-09-14 15:45:45 UTC
+++ uigtk.c
@@ -14,11 +14,13 @@
 #include "ui.h"
 
 /* button pixmaps */
+#ifndef GTK2_6
 #include "button1.xpm"
 #include "button2.xpm"
 #include "button3.xpm"
 #include "button4.xpm"
 #include "button5.xpm"
+#endif
 
 
 static GtkWidget *window,*vbox,*detailstbl,*detaillabel[5];
@@ -107,6 +109,11 @@ GtkWidget *pixmap;
 GdkBitmap *bitmap,*mask;
 int tbl_row,width;
 
+#ifdef GTK2
+#define gtk_accel_group_get_default() accel
+  GtkAccelGroup *accel;
+#endif
+
 window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
 gtk_signal_connect(GTK_OBJECT(window),"destroy",
                    GTK_SIGNAL_FUNC(cb_doquit),NULL);
@@ -116,6 +123,11 @@ gtk_widget_set_events(window,GDK_KEY_PRE
 gtk_window_set_title(GTK_WINDOW(window),"xaylet");
 gtk_window_set_policy(GTK_WINDOW(window),FALSE,TRUE,FALSE);	/* XXX? */
 
+#ifdef GTK2
+  accel = gtk_accel_group_new ();
+  gtk_window_add_accel_group (GTK_WINDOW (window), accel);
+#endif
+
 /* main vbox */
 vbox=gtk_vbox_new(FALSE,0);
 gtk_container_add(GTK_CONTAINER(window),vbox);
@@ -194,7 +206,11 @@ DO_TBL_LEFT(statustbl,1, 0,"Time:");
 DO_TBL_RIGHT(statustbl,1, 1,2,"");
 label_for_time=label;
 
+#ifdef GTK2
+  highspeed_widget = gtk_check_button_new_with_mnemonic ("_High speed");
+#else
 highspeed_widget=gtk_check_button_new_with_label("High-speed");
+#endif
 /* don't allow focus, looks too weird and we have shortcut */
 GTK_WIDGET_UNSET_FLAGS(highspeed_widget,GTK_CAN_FOCUS);
 gtk_table_attach_defaults(GTK_TABLE(statustbl),highspeed_widget, 2,4, 0,2);
@@ -227,6 +243,21 @@ gtk_table_set_row_spacings(GTK_TABLE(but
 gtk_container_set_border_width(GTK_CONTAINER(buttontbl),5);
 gtk_widget_show(buttontbl);
 
+#ifdef GTK2_6 /* >= GTK+ 2.6 */
+#define ADD_PIXMAP_TO_BUTTON(button,xpm,stock) \
+  pixmap = gtk_image_new_from_stock (GTK_STOCK_MEDIA_##stock, \
+				     GTK_ICON_SIZE_BUTTON); \
+  gtk_container_add (GTK_CONTAINER ((button)), pixmap); \
+  gtk_widget_show (pixmap)
+#else /* < GTK+ 2.6 */
+#define ADD_PIXMAP_TO_BUTTON(button,xpm,stock) \
+  bitmap=gdk_pixmap_create_from_xpm_d(window->window,&mask,	\
+                                      &(window->style->black),	\
+                                      (xpm));			\
+  pixmap=gtk_pixmap_new(bitmap,mask);				\
+  gtk_container_add(GTK_CONTAINER(button),pixmap);		\
+  gtk_widget_show(pixmap)
+#endif
 
 hbox=gtk_hbox_new(TRUE,5);
 gtk_table_attach_defaults(GTK_TABLE(buttontbl),hbox, 0,4, 0,1);
@@ -236,16 +267,8 @@ gtk_widget_show(hbox);
 /* XXX this seems to be needed here, but is it ok? */
 gtk_widget_realize(window);
 
-#define ADD_PIXMAP_TO_BUTTON(button,xpm) \
-  bitmap=gdk_pixmap_create_from_xpm_d(window->window,&mask,	\
-                                      &(window->style->black),	\
-                                      (xpm));			\
-  pixmap=gtk_pixmap_new(bitmap,mask);				\
-  gtk_container_add(GTK_CONTAINER(button),pixmap);		\
-  gtk_widget_show(pixmap)
-
 button=gtk_button_new();
-ADD_PIXMAP_TO_BUTTON(button,button1);
+ADD_PIXMAP_TO_BUTTON(button,button1,PREVIOUS);
 gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,0);
 gtk_signal_connect(GTK_OBJECT(button),"clicked",
                    GTK_SIGNAL_FUNC(cb_button_prev_track),NULL);
@@ -256,7 +279,7 @@ GTK_WIDGET_UNSET_FLAGS(button,GTK_CAN_FO
 gtk_widget_show(button);
 
 button=gtk_button_new();
-ADD_PIXMAP_TO_BUTTON(button,button2);
+ADD_PIXMAP_TO_BUTTON(button,button2,PLAY);
 gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,0);
 gtk_signal_connect(GTK_OBJECT(button),"clicked",
                    GTK_SIGNAL_FUNC(cb_button_play),NULL);
@@ -266,7 +289,7 @@ GTK_WIDGET_UNSET_FLAGS(button,GTK_CAN_FO
 gtk_widget_show(button);
 
 button=gtk_button_new();
-ADD_PIXMAP_TO_BUTTON(button,button3);
+ADD_PIXMAP_TO_BUTTON(button,button3,PAUSE);
 gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,0);
 gtk_signal_connect(GTK_OBJECT(button),"clicked",
                    GTK_SIGNAL_FUNC(cb_button_pause),NULL);
@@ -276,7 +299,7 @@ GTK_WIDGET_UNSET_FLAGS(button,GTK_CAN_FO
 gtk_widget_show(button);
 
 button=gtk_button_new();
-ADD_PIXMAP_TO_BUTTON(button,button4);
+ADD_PIXMAP_TO_BUTTON(button,button4,STOP);
 gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,0);
 gtk_signal_connect(GTK_OBJECT(button),"clicked",
                    GTK_SIGNAL_FUNC(cb_button_stop),NULL);
@@ -286,7 +309,7 @@ GTK_WIDGET_UNSET_FLAGS(button,GTK_CAN_FO
 gtk_widget_show(button);
 
 button=gtk_button_new();
-ADD_PIXMAP_TO_BUTTON(button,button5);
+ADD_PIXMAP_TO_BUTTON(button,button5,NEXT);
 gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,0);
 gtk_signal_connect(GTK_OBJECT(button),"clicked",
                    GTK_SIGNAL_FUNC(cb_button_next_track),NULL);
@@ -295,7 +318,11 @@ gtk_widget_add_accelerator(button,"click
 GTK_WIDGET_UNSET_FLAGS(button,GTK_CAN_FOCUS);
 gtk_widget_show(button);
 
+#ifdef GTK2
+  button = gtk_button_new_with_mnemonic ("_Restart");
+#else
 button=gtk_button_new_with_label("Restart");
+#endif
 gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,0);
 gtk_signal_connect(GTK_OBJECT(button),"clicked",
                    GTK_SIGNAL_FUNC(cb_button_restart),NULL);
@@ -304,17 +331,24 @@ gtk_widget_add_accelerator(button,"click
 GTK_WIDGET_UNSET_FLAGS(button,GTK_CAN_FOCUS);
 gtk_widget_show(button);
 
-
 /* second row, these go straight on the table */
 /* backspace/delete/space are dealt with by keypress() */
+#ifdef GTK2
+  button = gtk_button_new_with_mnemonic ("_Previous file");
+#else
 button=gtk_button_new_with_label("Prev File");
+#endif
 gtk_table_attach_defaults(GTK_TABLE(buttontbl),button, 1,2, 1,2);
 gtk_signal_connect(GTK_OBJECT(button),"clicked",
                    GTK_SIGNAL_FUNC(cb_button_prev_file),NULL);
 GTK_WIDGET_UNSET_FLAGS(button,GTK_CAN_FOCUS);
 gtk_widget_show(button);
 
+#ifdef GTK2
+  button = gtk_button_new_with_mnemonic("_Next file");
+#else
 button=gtk_button_new_with_label("Next File");
+#endif
 gtk_table_attach_defaults(GTK_TABLE(buttontbl),button, 2,3, 1,2);
 gtk_signal_connect(GTK_OBJECT(button),"clicked",
                    GTK_SIGNAL_FUNC(cb_button_next_file),NULL);
@@ -386,8 +420,8 @@ retval=1;
 if(need_update)
   {
   need_update=0;
-  ui_draw_status(ay_filenames[ay_file],aydata.miscstr,aydata.authorstr,
-                 ay_track+1,aydata.tracks[ay_track].namestr);
+  ui_draw_status(ay_filenames[ay_file], (char *)aydata.miscstr, (char *)aydata.authorstr,
+                 ay_track+1, (char *)aydata.tracks[ay_track].namestr);
   }
 
 /* update time display */
