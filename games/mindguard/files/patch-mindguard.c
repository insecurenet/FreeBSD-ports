--- mindguard.c.orig	Fri Feb  7 20:53:53 2003
+++ mindguard.c	Wed Sep  7 23:27:25 2005
@@ -1381,7 +1381,7 @@
 					sprintf(car_path, "%s/MindGuard/carriers/", getenv("HOME"));
 					break;
 				case 2:
-					strcpy(car_path, "/usr/local/share/MindGuard/carriers/");
+					strcpy(car_path, LOCALBASE "/share/mindguard/");
 					break;
 				default:
 					break;
@@ -2799,4 +2799,4 @@
 }
 
 
-/* ...And your mind lived happily ever after.  The End */
\ No newline at end of file
+/* ...And your mind lived happily ever after.  The End */
