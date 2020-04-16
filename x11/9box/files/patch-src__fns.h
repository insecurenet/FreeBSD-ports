--- src/fns.h.orig	2003-01-06 18:23:16.000000000 +0800
+++ src/fns.h	2011-09-08 14:36:30.000000000 +0800
@@ -7,7 +7,8 @@
 Window selectwin(Box *);
 Window dump_tree(Box *, Window, int);
 char * getprop(Box *, Window, Atom);
-Window reparent_window(Box *);
+void reparent_window(Box *);
+int nobuttons(XButtonEvent *);
 
 
 /* grab.c */
@@ -21,9 +22,14 @@ void select_window(BoxedWindow *);
 void remove_window(BoxedWindow *);
 void release_window(BoxedWindow *);
 void update_buttons_position(Box *);
+void destroy_window(BoxedWindow *);
 
+/* menu.c */
+int menu(Box *, char **, int);
+void b2menu(Box *);
 
 /* buttons.c */
+void move_button(Box *);
 void draw_button(BoxedWindow *);
 int button_height();
 void move_button_to(Box *, int);
@@ -32,6 +38,7 @@ void move_button_to(Box *, int);
 BoxedWindow * search_boxedwindow(Box *, Window);
 BoxedWindow * search_boxedwindow_client(Box *, Window);
 BoxedWindow * search_boxedwindow_button(Box *, Window);
+void resize_box_for_client(Box *, int);
 
 /* wm.c */
 void set_title(Box *, char *);
