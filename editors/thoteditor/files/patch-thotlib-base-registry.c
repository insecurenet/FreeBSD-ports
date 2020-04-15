--- ../thotlib/base/registry.c.orig	Mon Sep 27 00:32:18 1999
+++ ../thotlib/base/registry.c	Mon Sep 27 00:34:52 1999
@@ -833,6 +833,7 @@
    PathBuffer          path;
    char               *home_dir;
    char                filename[MAX_PATH];
+   char                homecmd[MAX_PATH];
    char               *my_path;
    char               *dir_end = NULL;
    char               *appName;
@@ -1084,13 +1085,22 @@
        dir_end -= 3;
      }
    else
-     fprintf (stderr, "System wide %s not found at %s\n", THOT_INI_FILENAME, &filename[0]);
+     fprintf (stderr, " ");
+/*     fprintf (stderr, "System wide %s not found at %s\n", THOT_INI_FILENAME, &filename[0]); */
 
    if (home_dir != NULL)
      {
 	strcpy (filename, home_dir);
 	strcat (filename, DIR_STR);
 	strcat (filename, THOT_RC_FILENAME);
+	if (!TtaFileExist (&filename[0]))
+	{
+		sprintf(homecmd,"/bin/cp %%PREFIX%%/share/thot/config/thot.ini %s%s.thotrc\n",home_dir,DIR_STR);
+		fprintf(stderr,"Copying system thot.ini into ~/.thotrc.\n");
+		system(homecmd);
+		sprintf(homecmd,"/bin/chmod u+w %s%s.thotrc\n",home_dir,DIR_STR);
+		system(homecmd);
+	}
 	if (TtaFileExist (&filename[0]))
 	  {
 #ifdef DEBUG_REGISTRY
