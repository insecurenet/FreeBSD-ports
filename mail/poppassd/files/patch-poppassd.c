--- poppassd.c.orig	Thu Jan  4 23:19:36 2007
+++ poppassd.c	Thu Jan  4 23:24:26 2007
@@ -13,11 +13,11 @@
  * 
  * Doesn't actually change any passwords itself.  It simply listens for
  * incoming requests, gathers the required information (user name, old
- * password, new password) and executes /bin/passwd, talking to it over
+ * password, new password) and executes /usr/bin/passwd, talking to it over
  * a pseudo-terminal pair.  The advantage of this is that we don't need
  * to have any knowledge of either the password file format (which may
  * include dbx files that need to be rebuilt) or of any file locking
- * protocol /bin/passwd and cohorts may use (and which isn't documented).
+ * protocol /usr/bin/passwd and cohorts may use (and which isn't documented).
  *
  * The current version has been tested at NU under SunOS release 4.1.2 
  * and 4.1.3, and under HP-UX 8.02 and 9.01. We have tested the server 
@@ -29,7 +29,7 @@
  * Note that unencrypted passwords are transmitted over the network.  If
  * this bothers you, think hard about whether you want to implement the
  * password changing feature.  On the other hand, it's no worse than what
- * happens when you run /bin/passwd while connected via telnet or rlogin.
+ * happens when you run /usr/bin/passwd while connected via telnet or rlogin.
  * Well, maybe it is, since the use of a dedicated port makes it slightly
  * easier for a network snooper to snarf passwords off the wire.
  *
@@ -44,10 +44,10 @@
  *
  * The front-end code (which talks to the client) is directly 
  * descended from Leavitt's original version.  The back-end pseudo-tty stuff 
- * (which talks to /bin/password) is directly descended from Smith's
+ * (which talks to /usr/bin/password) is directly descended from Smith's
  * version, with changes for SunOS and HP-UX by Norstad (with help from
  * sample code in "Advanced Programming in the UNIX Environment"
- * by W. Richard Stevens). The code to report /bin/passwd error messages
+ * by W. Richard Stevens). The code to report /usr/bin/passwd error messages
  * back to the client in the final 500 response, and a new version of the
  * code to find the next free pty, is by Norstad.
  *        
@@ -112,7 +112,7 @@
 
 #define SUCCESS 1
 #define FAILURE 0
-#define BUFSIZE 512
+#define BUFSIZE 768
 
 #include <sys/types.h>
 #include <sys/stat.h>
@@ -125,12 +125,23 @@
 #include <ctype.h>
 #include <strings.h>
 #include <errno.h>
-#include <varargs.h>
+#include <stdarg.h>
 #include <pwd.h>
 #include <string.h>
 #include <termios.h>
 #include <dirent.h>
+#include <libutil.h>
 
+/* prototypes to keep modern compilers happy */
+void ReadFromClient (char *line);
+void WriteToClient (char *fmt, ...);
+int chkPass (char *user, char *pass, struct passwd *pw);
+int dochild (int master, char *slavedev, char *user);
+int expect (int master, char **expected, char *buf);
+void getemess (int master, char **expected, char *buf);
+int match (char *str, char *pat);
+int talktochild (int master, char *user, char *oldpass, char *newpass, char *emess);
+void writestring (int fd, char *s);
 
 /* Prompt strings expected from the "passwd" command. If you want
  * to port this program to yet another flavor of UNIX, you may need to add
@@ -145,19 +156,24 @@
 static char *P1[] =
    {"Old password:",
     "Changing password for *.\nOld password:",
+    "Changing local password for *.\nOld password:",
+    "Changing local password for *\nOld Password:",
     "Changing password for * on *.\nOld password:",
     "Changing NIS password for * on *.\nOld password:",
+    "Changing NIS password for *\nOld Password:",
     "Changing password for *\n*'s Old password:",
     ""};
 
 static char *P2[] =
    {"\nNew password:",
+    "\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\n*\nEnter new password: ",
     "\n*'s New password:",
     ""};
 
 static char *P3[] =
    {"\nRe-enter new password:",
     "\nRetype new password:",
+    "\nRe-type new password: ",
     "\nEnter the new password again:",
     "\n*Re-enter *'s new password:",
     "\nVerify:",
@@ -165,13 +181,14 @@
     
 static char *P4[] =
    {"\n",
+    "\npasswd: rebuilding the database...\npasswd: done\n",
+    "\npasswd: updating the database...\npasswd: done\n",
     "NIS entry changed on *\n",
+    "\n\nNIS password has been changed on *.\n",
     ""};
 
 
-main (argc, argv)
-int argc;
-char *argv[];
+int main (int argc, char *argv[])
 {
      char line[BUFSIZE];
      char user[BUFSIZE];
@@ -180,17 +197,14 @@
      char emess[BUFSIZE];
      char *slavedev;
      struct passwd *pw, *getpwnam();
+     struct termios stermios;
      int c, master;
      pid_t pid, wpid;
      int wstat;
      
      *user = *oldpass = *newpass = 0;
      
-     if (openlog ("poppassd", LOG_PID, LOG_LOCAL2) < 0)
-     {
-	  WriteToClient ("500 Can't open syslog.");
-	       exit (1);
-     }
+     openlog ("poppassd", LOG_PID, LOG_LOCAL2);
      
      WriteToClient ("200 poppassd v%s hello, who are you?", VERSION);
      ReadFromClient (line);
@@ -212,12 +226,16 @@
      
      if ((pw = getpwnam (user)) == NULL)
      {
-	  WriteToClient ("500 Unknown user, %s.", user);
+	  syslog (LOG_ERR, "Unknown user, %s", user);
+	  sleep (5);
+	  WriteToClient ("500 Old password is incorrect.");
 	  exit(1);
      }
 
      if (chkPass (user, oldpass, pw) == FAILURE)
      {
+	  syslog (LOG_ERR, "Incorrect password from %s", user);
+	  sleep (5);
 	  WriteToClient ("500 Old password is incorrect.");
 	  exit(1);
      }
@@ -232,215 +250,118 @@
 	  WriteToClient ("500 New password required.");
 	  exit(1);
      }
-     /* get pty to talk to password program */
-     if ((master = findpty (&slavedev)) < 0)
-     {
-	  syslog (LOG_ERR, "can't find pty");
-          WriteToClient("500 Server busy - try again later.");
-	  exit (1);
-     }
-	 
-     /* fork child process to talk to password program */
-     if ((pid = fork()) < 0)     /* Error, can't fork */
-     {
-	  syslog (LOG_ERR, "can't fork for passwd: %m");
-	  WriteToClient ("500 Server error (can't fork passwd), get help!");
-	  exit (1);
-     }
 
-     if (pid)   /* Parent */
-     {
-	  sleep (1);    /* Make sure child is ready.  Is this really needed? */
-	  if (talktochild (master, user, oldpass, newpass, emess) == FAILURE)
-	  {
-	       syslog (LOG_ERR, "failed attempt by %s", user);
-	       if (*emess == '\0') {
-	          WriteToClient ("500 Unable to change password." );
-               } else {
-		  WriteToClient ("500 %s", emess);
-               }
-	       exit(1);
-	  }
-
-	  if ((wpid = waitpid (pid, &wstat, 0)) < 0)
-	  {
-	       syslog (LOG_ERR, "wait for /bin/passwd child failed: %m");
-	       WriteToClient ("500 Server error (wait failed), get help!");
-	       exit (1);
-	  }
-
-	  if (pid != wpid)
-	  {
-	       syslog (LOG_ERR, "wrong child (/bin/passwd waited for!");
-	       WriteToClient ("500 Server error (wrong child), get help!");
-	       exit (1);
-	  }
-
-	  if (WIFEXITED (wstat) == 0)
-	  {
-	       syslog (LOG_ERR, "child (/bin/passwd) killed?");
-	       WriteToClient ("500 Server error (funny wstat), get help!");
-	       exit (1);
-	  }
-
-	  if (WEXITSTATUS (wstat) != 0)
-	  {
-	       syslog (LOG_ERR, "child (/bin/passwd) exited abnormally");
-	       WriteToClient ("500 Server error (abnormal exit), get help!");
-	       exit (1);
-	  }
-
-	  syslog (LOG_ERR, "password changed for %s", user);
-	  WriteToClient ("200 Password changed, thank-you.");
-
-          ReadFromClient (line);
-	  if (strncmp(line, "quit", 4) != 0) {
-	  	WriteToClient("500 Quit required.");
+	/* we need a pty to run passwd on but we have to make sure it is set up
+	   as we like it - no echo, canonical input processing, no map NL to CR/NL
+	   on outputs - otherwise our expect function will be confused */
+	(void)memset((void *)&stermios, 0, sizeof(stermios));
+	stermios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
+	stermios.c_lflag |= ICANON;
+	stermios.c_oflag &= ~(ONLCR);
+
+	/* get a pty and fork */
+	switch(pid = forkpty(&master, NULL, &stermios, NULL)) {
+	case -1:
+		/* failure - can't get pty, can't fork etc */
+		WriteToClient("500 Server Error - Contact Your Administrator");
+		exit(1);
+		break;
+	case 0:
+		/* slave/child */
+		/* Set login name */
+		if (setlogin(user) < 0) {
+			syslog(LOG_ERR, "setlogin failed: %m");
+			WriteToClient("500 Server Error - Contact Your Administrator");
+			return(0);
+		}
+		setuid (pw->pw_uid);
+		setgid (pw->pw_gid);
+		dochild (master, NULL, user);
+		break;
+	default:
+		/* master/parent */
+		sleep (1);    /* Make sure child is ready.  Is this really needed? */
+		if (talktochild (master, user, oldpass, newpass, emess) == FAILURE)
+		{
+			syslog (LOG_ERR, "failed attempt by %s", user);
+			if (*emess == '\0') {
+                                WriteToClient ("500 Password change unsuccessful, try a different password." );
+			} else {
+				WriteToClient ("500 %s", emess);
+			}
+			exit(1);
+		}
+		
+		break;
+	}
+
+	if ((wpid = waitpid (pid, &wstat, 0)) < 0)
+	{
+		syslog (LOG_ERR, "wait for /usr/bin/passwd child failed: %m");
+		WriteToClient ("500 Server error (wait failed), get help!");
+		exit (1);
+	}
+
+	if (pid != wpid)
+	{
+	     syslog (LOG_ERR, "wrong child (/usr/bin/passwd) waited for!");
+	     WriteToClient ("500 Server error (wrong child), get help!");
+	     exit (1);
+	}
+
+	if (WIFEXITED (wstat) == 0)
+	{
+	     syslog (LOG_ERR, "child (/usr/bin/passwd) killed?");
+	     WriteToClient ("500 Server error (funny wstat), get help!");
+	     exit (1);
+	}
+
+	if (WEXITSTATUS (wstat) != 0)
+	{
+	     syslog (LOG_ERR, "child (/usr/bin/passwd) exited abnormally");
+	     WriteToClient ("500 Server error (abnormal exit), get help!");
+	     exit (1);
+	}
+
+	syslog (LOG_ERR, "password changed for %s", user);
+	WriteToClient ("200 Password changed, thank-you.");
+
+    ReadFromClient (line);
+	if (strncmp(line, "quit", 4) != 0) {
+		WriteToClient("500 Quit required.");
 		exit (1);
-	  }
+	}
 	  
-	  WriteToClient("200 Bye.");
-	  exit (0);
-     }
-     else      /* Child */
-     {
-	  /*
-	   * Become the user trying who's password is being changed.  We're
-	   * about to exec /bin/passwd with is setuid root anyway, but this
-	   * way it looks to the child completely like it's being run by
-	   * the normal user, which makes it do its own password verification
-	   * before doing any thing.  In theory, we've already verified the
-	   * password, but this extra level of checking doesn't hurt.  Besides,
-	   * the way I do it here, if somebody manages to change somebody
-	   * else's password, you can complain to your vendor about security
-	   * holes, not to me!
-	   */
-	  setuid (pw->pw_uid);
-	  setgid (pw->pw_gid);
-	  dochild (master, slavedev, user);
-     }
+	WriteToClient("200 Bye.");
+	exit (0);
 }
 
 /*
  * dochild
  *
- * Do child stuff - set up slave pty and execl /bin/passwd.
+ * Do child stuff - set up slave pty and execl /usr/bin/passwd.
  *
  * Code adapted from "Advanced Programming in the UNIX Environment"
  * by W. Richard Stevens.
  *
  */
 
-dochild (master, slavedev, user)
-int master;
-char *slavedev, *user;
+int dochild (int master, char *slavedev, char *user)
 {
-   int slave;
-   struct termios stermios;
+   /* Fork /usr/bin/passwd. */
 
-   /* Start new session - gets rid of controlling terminal. */
-   
-   if (setsid() < 0) {
-      syslog(LOG_ERR, "setsid failed: %m");
-      return(0);
-   }
-
-   /* Open slave pty and acquire as new controlling terminal. */
-
-   if ((slave = open(slavedev, O_RDWR)) < 0) {
-      syslog(LOG_ERR, "can't open slave pty: %m");
-      return(0);
-   }
-
-   /* Close master. */
-
-   close(master);
-
-   /* Make slave stdin/out/err of child. */
-
-   if (dup2(slave, STDIN_FILENO) != STDIN_FILENO) {
-      syslog(LOG_ERR, "dup2 error to stdin: %m");
-      return(0);
-   }
-   if (dup2(slave, STDOUT_FILENO) != STDOUT_FILENO) {
-      syslog(LOG_ERR, "dup2 error to stdout: %m");
-      return(0);
-   }
-   if (dup2(slave, STDERR_FILENO) != STDERR_FILENO) {
-      syslog(LOG_ERR, "dup2 error to stderr: %m");
-      return(0);
-   }
-   if (slave > 2) close(slave);
-
-   /* Set proper terminal attributes - no echo, canonical input processing,
-      no map NL to CR/NL on output. */
-
-   if (tcgetattr(0, &stermios) < 0) {
-      syslog(LOG_ERR, "tcgetattr error: %m");
-      return(0);
-   }
-   stermios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
-   stermios.c_lflag |= ICANON;
-   stermios.c_oflag &= ~(ONLCR);
-   if (tcsetattr(0, TCSANOW, &stermios) < 0) {
-      syslog(LOG_ERR, "tcsetattr error: %m");
-      return(0);
-   }
-
-   /* Fork /bin/passwd. */
-
-   if (execl("/bin/passwd", "passwd", user, (char*)0) < 0) {
-      syslog(LOG_ERR, "can't exec /bin/passwd: %m");
+   if (execl("/usr/bin/passwd", "passwd", user, (char*)0) < 0) {
+      syslog(LOG_ERR, "can't exec /usr/bin/passwd: %m");
       return(0);
    }
 }
 
-
-/*
- * findpty()
- *
- * Finds the first available pseudo-terminal master/slave pair.  The master
- * side is opened and a fd returned as the function value.  A pointer to the
- * name of the slave side (i.e. "/dev/ttyp0") is returned in the argument,
- * which should be a char**.  The name itself is stored in a static buffer.
- *
- * A negative value is returned on any sort of error.
- *
- * Modified by Norstad to remove assumptions about number of pty's allocated
- * on this UNIX box.
- */
-findpty (slave)
-char **slave;
-{
-   int master;
-   static char *line = "/dev/ptyXX";
-   DIR *dirp;
-   struct dirent *dp;
-
-   dirp = opendir("/dev");
-   while ((dp = readdir(dirp)) != NULL) {
-      if (strncmp(dp->d_name, "pty", 3) == 0 && strlen(dp->d_name) == 5) {
-         line[8] = dp->d_name[3];
-         line[9] = dp->d_name[4];
-         if ((master = open(line, O_RDWR)) >= 0) {
-            line[5] = 't';
-            *slave = line;
-            closedir(dirp);
-            return (master);
-         }
-      }
-   }
-   closedir(dirp);
-   return (-1);
-}
-
 /*
  * writestring()
  *
  * Write a string in a single write() system call.
  */
-writestring (fd, s)
-char *s;
+void writestring (int fd, char *s)
 {
      int l;
 
@@ -458,9 +379,7 @@
  * FAILURE if any errors are encountered (in which case, it can be assumed
  * that the password wasn't changed).
  */
-talktochild (master, user, oldpass, newpass, emess)
-int master;
-char *user, *oldpass, *newpass, *emess;
+int talktochild (int master, char *user, char *oldpass, char *newpass, char *emess)
 {
      char buf[BUFSIZE];
      char pswd[BUFSIZE+1];
@@ -485,9 +404,11 @@
      }
 
      writestring(master, pswd);
-
+     sleep(2);
      if (!expect(master, P4, buf)) return FAILURE;
 
+     close(master);
+
      return SUCCESS;
 }
 
@@ -507,9 +428,7 @@
  *		  the pattern.
  *		2 if the string matches the full pattern.
  */
-match (str, pat)
-char *str;
-char *pat;
+int match (char *str, char *pat)
 {
    int result;
    
@@ -542,10 +461,7 @@
  * is not an initial segment of or exact match for at least one of 
  * the expected strings, the function returns FAILURE.
  */
-expect (master, expected, buf)
-int master;
-char **expected;
-char *buf;
+int expect (int master, char **expected, char *buf)
 {
      int n, m;
      char **s;
@@ -596,10 +512,7 @@
  * returning just the error message text. Newlines in the error message
  * text are replaced by spaces.
  */
-getemess (master, expected, buf)
-int master;
-char **expected;
-char *buf;
+void getemess (int master, char **expected, char *buf)
 {
    int n, m;
    char **s;
@@ -630,21 +543,18 @@
    }
 }
 
-WriteToClient (fmt, va_alist)
-char *fmt;
-va_dcl
+void WriteToClient (char *fmt, ...)
 {
 	va_list ap;
 	
-	va_start (ap);
+	va_start (ap, fmt);
 	vfprintf (stdout, fmt, ap);
 	fputs ("\r\n", stdout );
 	fflush (stdout);
 	va_end (ap);
 }
 
-ReadFromClient (line)
-char *line;
+void ReadFromClient (char *line)
 {
 	char *sp;
 	int i;
@@ -659,10 +569,7 @@
 	for (sp = line; isalpha(*sp); sp++) *sp = tolower(*sp);
 }
 
-int chkPass (user, pass, pw)
-char *user;
-char *pass;
-struct passwd *pw;
+int chkPass (char *user, char *pass, struct passwd *pw)
 {
      /*  Compare the supplied password with the password file entry */
      if (strcmp (crypt (pass, pw->pw_passwd), pw->pw_passwd) != 0)
