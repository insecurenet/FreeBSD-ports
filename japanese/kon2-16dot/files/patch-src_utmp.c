--- src/utmp.c.orig	1997-01-24 09:37:28.000000000 +0900
+++ src/utmp.c	2012-05-10 04:09:42.294562501 +0900
@@ -41,20 +41,39 @@
 #include	<utmp.h>
 #include	<grp.h>
 #include	<sys/stat.h>
+#if defined(__FreeBSD__)
+#include	<ttyent.h>
+#endif
 
+#if !defined(__FreeBSD__)
 static int ttyGid;
+#else
+static gid_t ttyGid;
+static int ts;
+#endif
+static int unuse_utmp = 0;
+
+void	UnUseUtmp(int flg)
+{
+	unuse_utmp = flg;
+}
 
 void	SetUtmp(char *tty)
 {
-#ifdef linux
 	struct utmp	utmp;
 	struct passwd	*pw;
 	struct group	*ttygrp;
 	char	*tn;
-
+#if defined(__FreeBSD__)
+	struct ttyent	*ttyp;
+	int fd, i;
+#endif
+	if (unuse_utmp)
+		return;
 	pw = getpwuid(getuid());
 	tn = rindex(tty, '/') + 1;
 	memset((char *)&utmp, 0, sizeof(utmp));
+#if !defined(__FreeBSD__)
 	strncpy(utmp.ut_id, tn + 3, sizeof(utmp.ut_id));
 	utmp.ut_type = DEAD_PROCESS;
 	setutent();
@@ -66,21 +85,45 @@
 	time(&(utmp.ut_time));
 	pututline(&utmp);
 	endutent();
+#else
+	time(&(utmp.ut_time));
+	strncpy(utmp.ut_name, pw->pw_name, sizeof(utmp.ut_name));
+	strncpy(utmp.ut_line, tn, sizeof(utmp.ut_line));
+	setttyent();
+	ts = 0;
+	for (i = 1; (ttyp = getttyent()); ++i)
+	    if (!strcmp(ttyp->ty_name,tn)) {
+		ts = i;
+		break;
+	    }
+	endttyent();
+	if (ts > 0 && (fd = open(_PATH_UTMP, O_WRONLY|O_CREAT, 0644)) >= 0) {
+	    lseek(fd, (ts*sizeof(struct utmp)), L_SET);
+	    write(fd, &utmp, sizeof(struct utmp));
+	    close(fd);
+	}
+#endif
 	if ((ttygrp = getgrnam("tty")) != NULL)
 		ttyGid = ttygrp->gr_gid;
 	else
 		ttyGid = -1;
 	chmod(tty, 0622);
 	chown(tty, getuid(), ttyGid);
-#endif
 }
 
 void	ResetUtmp(char *tty)
 {
-#ifdef linux
+#if !defined(__FreeBSD__)
 	struct utmp	utmp, *utp;
 	char	*tn;
+#else
+	struct utmp	utmp;
+	int fd;
+#endif
+	if (unuse_utmp)
+		return;
 
+#if !defined(__FreeBSD__)
 	tn = rindex(tty, '/') + 4;
 	memset((char *)&utmp, 0, sizeof(utmp));
 	strncpy(utmp.ut_id, tn, sizeof(utmp.ut_id));
@@ -93,7 +136,19 @@
 	time(&(utp->ut_time));
 	pututline(utp);
 	endutent();
+#else
+	if (ts > 0 && (fd = open(_PATH_UTMP, O_RDWR, 0)) >= 0) {
+	    lseek(fd, (ts*sizeof(struct utmp)), L_SET);
+	    if (read(fd, &utmp, sizeof(struct utmp)) == sizeof(struct utmp)) {
+		bzero(utmp.ut_name, sizeof(utmp.ut_name));
+		bzero(utmp.ut_host, sizeof(utmp.ut_host));
+		time(&utmp.ut_time);
+		lseek(fd, (ts*sizeof(struct utmp)), L_SET);
+		write(fd, &utmp, sizeof(struct utmp));
+	    }
+	    close(fd);
+	}
+#endif
 	chmod(tty, 0600);
 	chown(tty, 0, ttyGid);
-#endif
 }
