--- ./tty.c.orig	1990-02-06 05:47:47.000000000 +0100
+++ ./tty.c	2012-08-24 12:55:15.782915559 +0200
@@ -18,6 +18,7 @@
 #include <stdio.h>
 #include <strings.h>
 #include <signal.h>
+#include <termios.h>
 #include <sys/types.h>
 #include <sys/ioctl.h>
 #include <sys/time.h>
@@ -30,7 +31,7 @@
 char *getenv(), *tgetstr(), *tgoto() ;
 int destroy_frame(), outc() ;
 
-struct sgttyb in_new, in_old ;
+struct termios in_new, in_old ;
 
 
 SIGRET
@@ -90,7 +91,7 @@
     }
   do_move(0, 0) ;
   SIGNAL(SIGINT, SIG_IGN) ;
-  IOCTL(0, TIOCSETP, &in_old) ;
+  tcsetattr(0, TCSANOW, &in_old) ;
   exit(0) ;
 }
 
@@ -128,6 +129,7 @@
 }
 
 
+void
 drawline(x1, y1, x2, y2)
 int x1, y1, x2, y2 ;
 {
@@ -315,11 +317,14 @@
 
   SIGNAL(SIGINT, cleanup) ;
 
-  IOCTL(0, TIOCGETP, &in_old) ;        /* Setup standard input. */
+  tcgetattr(0, &in_old) ;	/* Setup standard input. */
   in_new = in_old ;
-  in_new.sg_flags |= RAW ;
-  in_new.sg_flags &= ~(ECHO | CRMOD) ;
-  IOCTL(0, TIOCSETP, &in_new) ;
+  in_new.c_iflag |= IGNBRK;
+  in_new.c_iflag &= ~ICRNL;
+  in_new.c_lflag &= ~(ECHOCTL|ISIG|ICANON|IEXTEN);
+  in_new.c_oflag &= ~ONLCR;
+  in_new.c_lflag &= ~ECHO;
+  tcsetattr(0, TCSANOW, &in_new) ;
 
   setbuf(stdout, (char *) NULL) ;
 
