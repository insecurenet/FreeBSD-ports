--- ./radiant/mainframe.cpp.orig	Thu Mar 16 16:09:46 2006
+++ ./radiant/mainframe.cpp	Thu Mar 16 16:09:46 2006
@@ -510,7 +510,7 @@
 const char* const c_library_extension =
 #if defined(WIN32)
 "dll"
-#elif defined(__linux__)
+#elif defined(__linux__) || defined(__FreeBSD__)
 "so"
 #elif defined (__APPLE__)
 "dylib"
@@ -2849,7 +2849,7 @@
 
 #if !defined(WIN32)
   {
-    GdkPixbuf* pixbuf = pixbuf_new_from_file_with_mask("icon.bmp");
+    GdkPixbuf* pixbuf = pixbuf_new_from_file_with_mask("bitmaps/icon.bmp");
     if(pixbuf != 0)
     {
       gtk_window_set_icon(window, pixbuf);
@@ -3479,7 +3479,7 @@
     const char* ENGINEPATH_ATTRIBUTE =
 #if defined(WIN32)
       "enginepath_win32"
-#elif defined(__linux__)
+#elif defined(__linux__) || defined(__FreeBSD__)
       "enginepath_linux"
 #elif defined(__APPLE__)
       "enginepath_macos"
