--- src/vc.c.orig	1997-01-25 00:06:23.000000000 +0900
+++ src/vc.c	2012-05-10 00:14:28.968550436 +0900
@@ -40,7 +40,13 @@
 #include	<termio.h>
 #elif defined(__FreeBSD__)
 #include	<termios.h>
-#include	<machine/console.h>
+#include        <osreldate.h>
+#if __FreeBSD_version >= 410000
+#  include      <sys/consio.h>
+#  include      <sys/kbio.h>
+#else
+#  include      <machine/console.h>
+#endif
 #endif
 #include	<sys/ioctl.h>
 #ifdef linux
@@ -94,29 +100,22 @@
 static
 inline	void	blatch(void *head, int n)
 {
-
-    __asm__("\t clc\n"
-	    "1:\n"
-	    "\t andb %%bl, (%%eax)\n"
-	    "\t incl %%eax\n"
-	    "\t loop 1b\n"
-	    :
-	    : "eax" ((long)head), "bl" (0x7F), "c" (n)
-	    : "bl", "cx" );
+    char *tmp = (char *)head;
+    do {
+	*tmp &= 0x7f;
+	tmp++;
+    }  while(  --n  );
 }
 
 static
 inline	void	llatch(void *head, int n)
 {
-
-    __asm__("\t clc\n"
-	    "1:\n"
-	    "\t andl %%ebx, (%%eax)\n"
-	    "\t addl $4, %%eax\n"
-	    "\t loop 1b\n"
-	    :
-	    : "eax" ((long)head), "ebx" (0x7F7F7F7F), "c" (n>>2)
-	    : "ebx", "cx" );
+    int *tmp = (int *)head;
+    n /= 4;
+    do {
+	*tmp &= 0x7f7f7f7f;
+	tmp++;
+    }  while(  --n  );
 }
 
 static inline u_int	TextAddress(u_int x, u_int y)
@@ -266,12 +265,23 @@
 {
     struct vt_mode vtm;
 
+#if defined(__FreeBSD__)
+    signal(SIGUSR1, SIG_IGN);
+    signal(SIGUSR2, SIG_IGN);
+#else   /* linux */
     signal(SIGUSR1, SIG_DFL);
     signal(SIGUSR2, SIG_DFL);
+#endif
     vtm.mode = VT_AUTO;
     vtm.waitv = 0;
+#if defined(__FreeBSD__)
+    vtm.relsig = SIGUSR1;
+    vtm.acqsig = SIGUSR2;
+    vtm.frsig = SIGUSR1;
+#else   /* linux */
     vtm.relsig = 0;
     vtm.acqsig = 0;
+#endif
     ioctl(0, VT_SETMODE, &vtm);
 #if defined(__FreeBSD__)
     ioctl(0, VT_RELDISP, 1);
@@ -297,6 +307,9 @@
     vtm.waitv = 0;
     vtm.relsig = SIGUSR1;
     vtm.acqsig = SIGUSR2;
+#if defined(__FreeBSD__)
+    vtm.frsig = SIGUSR1;
+#endif
     ioctl(0, VT_SETMODE, &vtm);
     vInfo.graph_mode();
     if (useHardScroll)
@@ -779,22 +792,21 @@
     return SUCCESS;
 }
 
-static	char	*videoName;
+static	char	*videoName = NULL;
 
 static int	ConfigDisplay(const char *config)
 {
     struct videoconf *v;
-    char name[MAX_COLS];
-    
-    sscanf(config, "%s", name);
+    char *name, *last, *sep = " \t\r\n";
+
+    name = strtok_r((char *)config, sep, &last);
+    if (name == NULL) {
+	error("invalid entry for %s\r\n", videoName);
+	return FAILURE;
+    } 
     for (v = videos; v->name != NULL; v++) {
 	if (strcasecmp(name, v->name) == 0) {
-	    config = strchr(config, '\n');
-	    if (config == NULL) {
-		error("invalid entry for %s\r\n", videoName);
-		return FAILURE;
-	    }
-	    if (v->set(&vInfo, config) == FAILURE)
+	    if (v->set(&vInfo, last) == FAILURE)
 		return FAILURE;
 	    message("video type `%s' selected\r\n", name);
 	    if (vInfo.has_hard_scroll) {
@@ -816,22 +828,32 @@
 
 static int	ConfigBeep(const char *confstr)
 {
-    beepCount = atoi(confstr) * 10000;
 #if defined(linux)
+    beepCount = atoi(confstr) * 10000;
     if (beepCount > 0)
 	ioperm(COUNTER_ADDR, 1, TRUE);
 #endif
+#if defined(__FreeBSD__)
+    beepCount = atoi(confstr) * 10;
+#endif
     return SUCCESS;
 }
 
+#define BELL_PITCH	800
+
 void	Beep(void)
 {
-    if (!con.active || beepCount <= 0) return;
 #if defined(linux)
+    if (!con.active || beepCount <= 0) return;
     PortOutb(PortInb(COUNTER_ADDR)|3, COUNTER_ADDR);
     usleep(beepCount);
     PortOutb(PortInb(COUNTER_ADDR)&0xFC, COUNTER_ADDR);
 #endif
+#if defined(__FreeBSD__)
+    if(beepCount <= 0) return;
+    ioctl(fileno(stdout), KDMKTONE, (BELL_PITCH & 0xffff) | 
+          ((beepCount & 0xffff) << 16)); 
+#endif
 }
 
 static int	ConfigInterval(const char *confstr)
@@ -850,6 +872,7 @@
 
 void	ConsoleInit(const char *video)
 {
+    SafeFree(videoName);
     videoName = strdup(video);
     DefineCap(videoName, ConfigDisplay, NULL);
     DefineCap("BeepCounter", ConfigBeep, "5");
@@ -877,12 +900,12 @@
 {
     scrollLine = textHead = 0;
     vInfo.detatch();
-    SafeFree((void **)&textBuff);
-    SafeFree((void **)&attrBuff);
-    SafeFree((void **)&flagBuff);
+    SafeFree(textBuff);
+    SafeFree(attrBuff);
+    SafeFree(flagBuff);
 #ifdef linux
     ioperm(COUNTER_ADDR, 1, FALSE);
 #endif
     
-    SafeFree((void **)&videoName);
+    SafeFree(videoName);
 }
