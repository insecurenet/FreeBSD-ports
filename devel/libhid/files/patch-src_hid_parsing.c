--- src/hid_parsing.c.orig	2009-03-07 20:29:35.000000000 +0300
+++ src/hid_parsing.c	2009-03-07 20:29:43.000000000 +0300
@@ -1,5 +1,6 @@
 #define HID_INTERNAL
 
+#include <stdlib.h>
 #include <hid.h>
 #include <hid_helpers.h>
 
