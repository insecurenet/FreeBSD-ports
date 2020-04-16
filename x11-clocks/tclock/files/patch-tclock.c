--- tclock.c.orig	1992-12-21 19:56:29.000000000 +0000
+++ tclock.c	2011-06-20 18:42:37.000000000 +0100
@@ -22,7 +22,10 @@
  */ 
 
 #include <stdio.h>
+#include <stdlib.h>
+#include <unistd.h>
 #include <math.h>
+#include <time.h>
 #include <X11/Xlib.h>
 #include <X11/Xutil.h>
 #include <X11/Xos.h>
@@ -51,7 +54,7 @@
 int     screen_number;
 Window  rootWindow, mainWindow;
 int     ShapeEventNumber, ShapeErrorNumber;
-long    clock;
+time_t  lclock;
 struct tm lastTimes, times;
 Pixmap  border, clip;
 GC      clearGC, drawGC;
@@ -212,7 +215,7 @@
   XShapeCombineMask(display, mainWindow, ShapeBounding, 0, 0, border, ShapeSet);
   XShapeCombineMask(display, mainWindow, ShapeClip, 0, 0, clip, ShapeSet);
 
-  XFlush(display, 1);
+  XFlush(display);
 
   /* This call to XPending ensures that if the window gets closed, we die */
   XPending(display);
@@ -222,8 +225,6 @@
 strToTP(s)
   char *s;
 {
-  extern
-  char *malloc();
 
   XTextProperty *tp = (XTextProperty *)malloc(sizeof *tp);
   XStringListToTextProperty(&s, 1, tp);
@@ -233,11 +234,11 @@
 int
 sigalrm()
 {
-  clock = time(0);
-  times = *localtime(&clock);
+  lclock = time(0);
+  times = *localtime(&lclock);
   times.tm_hour = times.tm_hour * 5 + times.tm_min / 12;
   reshape();
-  signal(SIGALRM, sigalrm);		/* For SysV lusers */
+  signal(SIGALRM, (void *)sigalrm);		/* For SysV lusers */
 }
 
 unsigned long
@@ -294,7 +295,7 @@
   strcpy(appClass, "Tclock");
 }
 
-void
+int
 main(ac, av)
   int ac;
   char **av;
@@ -309,6 +310,7 @@
   extern
   char		*getenv();
   char		*displayName, fn[1000];
+  char		*sdb;
   int		parseReturn, rc;
 
   XrmParseCommand(&db, option, numOptions, "tclock", &ac, av);
@@ -330,7 +332,7 @@
   display = XOpenDisplay(displayName);
   if(display == 0)
   {
-    fprintf("Couldn't open display %s\n", displayName);
+    fprintf(stderr, "Couldn't open display %s\n", displayName);
     exit(-1);
   }
 
@@ -341,13 +343,14 @@
     exit(1);
 
   db = XrmGetStringDatabase(tclockDefaults);
-  XrmMergeDatabases(XrmGetStringDatabase(XResourceManagerString(display)), &db);
+  if(sdb = XResourceManagerString(display))
+    XrmMergeDatabases(XrmGetStringDatabase(sdb), &db);
   
   sprintf(fn, "%s/.Xdefaults", getenv("HOME"));
   if(access(fn, R_OK) == 0)
     XrmMergeDatabases(XrmGetFileDatabase(fn), &db);
 
-  if(getenv("XENVIRONMENT") && access(getenv("XENVIRONMENT")) == 0)
+  if(getenv("XENVIRONMENT") && access(getenv("XENVIRONMENT"), R_OK) == 0)
     XrmMergeDatabases(XrmGetFileDatabase(getenv("XENVIRONMENT")), &db);
 
   XrmMergeDatabases(cmdDB, &db);
@@ -410,7 +413,7 @@
   XMapRaised(display, mainWindow);
   XFlush(display);
 
-  signal(SIGALRM, sigalrm);
+  signal(SIGALRM, (void *)sigalrm);
   new.it_interval.tv_sec = 1;
   new.it_value.tv_sec = 1;
   new.it_interval.tv_usec = 0;
@@ -420,4 +423,3 @@
   for(;;)
     sigpause(0);
 }
-
