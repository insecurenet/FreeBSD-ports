--- file.c.orig	2011-07-05 06:22:52.572441868 -0700
+++ file.c	2011-07-05 06:25:04.233646750 -0700
@@ -82,7 +82,7 @@
 
 static void	 setup_tty __P((int));
 static void	 back_to_col_1 __P((void));
-static void	 pushback __P((Char *));
+static void	 pushback __P((Char *, int));
 static void	 catn __P((Char *, Char *, int));
 static void	 copyn __P((Char *, Char *, int));
 static Char	 filetype __P((Char *, Char *));
@@ -156,8 +156,9 @@
  * Push string contents back into tty queue
  */
 static void
-pushback(string)
+pushback(string, list)
     Char   *string;
+    int    list;
 {
     Char *p;
     struct termios tty, tty_normal;
@@ -168,6 +169,10 @@
     (void) tcgetattr(SHOUT, &tty);
     tty_normal = tty;
     tty.c_lflag &= ~(ECHOKE | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOCTL);
+#if __FreeBSD_version >= 800000
+    if (list == LIST)
+    	tty.c_lflag |= ECHO;
+#endif
     (void) tcsetattr(SHOUT, TCSANOW, &tty);
 
     for (p = string; (c = *p) != '\0'; p++)
@@ -660,7 +665,7 @@
 	    should_retype = TRUE;
 	if (should_retype)
 	    printprompt();
-	pushback(inputline);
+	pushback(inputline, command);
 	if (should_retype)
 	    retype();
     }
