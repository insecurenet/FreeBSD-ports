--- tools/qslim/qvis.cxx.orig	2011-09-06 14:13:35.000000000 +0200
+++ tools/qslim/qvis.cxx	2011-09-06 14:14:02.000000000 +0200
@@ -14,7 +14,7 @@
 #include <MxStdGUI.h>
 #include <stdio.h>
 
-#include <FL/fl_file_chooser.H>
+#include <FL/Fl_File_Chooser.H>
 #include <FL/filename.H>
 #include <FL/filename.H>
 #include <FL/Fl_Slider.H>
@@ -228,7 +228,7 @@
 // Main application routine
 //
 
-main(int argc, char **argv)
+int main(int argc, char **argv)
 {
     // Change default values for application variables in GUI version
     will_record_history = true;
