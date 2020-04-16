--- main.c.orig	2008-07-14 11:41:51.368157158 -0400
+++ main.c	2008-07-14 12:07:36.524646879 -0400
@@ -126,12 +126,14 @@
 static int cleanup(void) {
   int gsstatus, status = 0;
   pstotextExit(instance);
-  if (gs!=NULL) {
 #ifdef VMS
+  if (gs!=NULL) {
     gsstatus = fclose(gs);
+  }
 #else
-    gsstatus = pclose(gs);
+  waitpid(-1, &gsstatus, 0);
 #endif
+  if (gsstatus) {
     if (WIFEXITED(gsstatus)) {
       if (WEXITSTATUS(gsstatus)!=0) status = 3;
       else if (WIFSIGNALED(gsstatus)) status = 4;
@@ -166,8 +168,13 @@
 
 static int do_it(char *path) {
   /* If "path" is NULL, then "stdin" should be processed. */
-  char *gs_cmdline;
-  char *input;
+  char *gs_argv[32];
+  int gs_argc=0;
+#ifdef DEBUG
+  int i;
+#endif
+  int fd[2];
+  pid_t p;
   int status;
   char norotate[] = "";
   FILE *fileout;
@@ -201,47 +208,31 @@
     exit(1);
   }
 
-  if (path==NULL) {
-    input = (char*)malloc(2);
-    if (input == NULL) {
-      fprintf(stderr,"No memory available\n");
-      cleanup();
-      exit(1);
-    }
-    strcpy(input, "-");
-  } else {
-    input = (char*)malloc(strlen(path) + 6);
-    if (input == NULL) {
-      fprintf(stderr,"No memory available\n");
-      cleanup();
-      exit(1);
-    }
-    strcpy(input, "-- '"); strcat(input, path); strcat(input, "'");
+  gs_argv[gs_argc++] = "gs";
+  gs_argv[gs_argc++] = "-r72";
+  gs_argv[gs_argc++] = "-dNODISPLAY";
+  gs_argv[gs_argc++] = "-dFIXEDMEDIA";
+  gs_argv[gs_argc++] = "-dDELAYBIND";
+  gs_argv[gs_argc++] = "-dWRITESYSTEMDICT";
+  if (!debug) {
+    gs_argv[gs_argc++] = "-q";
+  }
+  gs_argv[gs_argc++] = "-dNOPAUSE";
+  gs_argv[gs_argc++] = "-dSAFER";
+  if (rotate_path && strcmp(rotate_path, "")) {
+    gs_argv[gs_argc++] = rotate_path;
+  }
+  if (ocr_path && strcmp(ocr_path, "")) {
+    gs_argv[gs_argc++] = ocr_path;
+  }
+  if (path == NULL ) {
+    gs_argv[gs_argc++] = "-";
+  }
+  else {
+    gs_argv[gs_argc++] = "--";
+    gs_argv[gs_argc++] = path;
   }
-
-  gs_cmdline = (char*)malloc(strlen(gs_cmd)+strlen(rotate_path)+
-	strlen(ocr_path) + strlen(input) + 128);
-
-  if (gs_cmdline == NULL) {
-    fprintf(stderr, "No memory available\n");
-    cleanup();
-    exit(1);
-  }
-
-  sprintf(
-    gs_cmdline,
-#ifdef VMS
-    "%s -r72 \"-dNODISPLAY\" \"-dFIXEDMEDIA\" \"-dDELAYBIND\" \"-dWRITESYSTEMDICT\" %s \"-dNOPAUSE\" %s %s %s",
-#else
-    "%s -r72 -dNODISPLAY -dFIXEDMEDIA -dDELAYBIND -dWRITESYSTEMDICT %s -dNOPAUSE %s %s %s",
-#endif
-    gs_cmd,
-    (debug ? "" : "-q"),
-    rotate_path,
-    ocr_path,
-    input
-    );
-  if (debug) fprintf(stderr, "%s\n", gs_cmdline);
+  gs_argv[gs_argc++] = NULL;
 #ifdef VMS
   cmdfile = tempnam("SYS$SCRATCH:","PS2TGS");
   gsoutfile = tempnam("SYS$SCRATCH:","GSRES");
@@ -259,8 +250,25 @@
 	exit(1);
   }
 #else
-  gs = popen(gs_cmdline, "r");
-  if (gs==0) {perror(cmd); exit(1);}
+  if (pipe(fd)) {
+	perror("pipe failed: "); exit(1);
+  };
+  p = fork();
+  if (p == -1) {
+	perror("fork failed: "); exit(1);
+  }
+  if (p == 0) { /* child */
+    close(fd[0]);
+    dup2(fd[1], 1); /* Redirect stdout into pipe to parent */
+    execvp("%%LOCALBASE%%/bin/gs", gs_argv);
+    perror("execvp: "); status=cleanup(); exit(1);
+  } else { /* parent */
+    close(fd[1]);
+    gs = fdopen(fd[0], "r");
+    if (gs == NULL) {
+      perror("fdopen: "); status=cleanup(); exit(1);
+    }
+  }
 #endif
   status = pstotextInit(&instance);
   if (status!=0) {
