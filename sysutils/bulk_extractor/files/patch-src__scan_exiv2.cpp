--- ./src/scan_exiv2.cpp.orig	2013-08-18 16:39:17.000000000 +0000
+++ ./src/scan_exiv2.cpp	2013-10-19 13:09:32.000000000 +0000
@@ -68,7 +68,7 @@
  * Used for helping to convert libexiv2's GPS format to decimal lat/long
  */
 
-static double stod(string s)
+static double be13stod(string s)
 {
     double d=0;
     sscanf(s.c_str(),"%lf",&d);
@@ -78,9 +78,9 @@
 static double rational(string s)
 {
     std::vector<std::string> parts = split(s,'/');
-    if(parts.size()!=2) return stod(s);	// no slash, so return without
-    double top = stod(parts[0]);
-    double bot = stod(parts[1]);
+    if(parts.size()!=2) return be13stod(s);	// no slash, so return without
+    double top = be13stod(parts[0]);
+    double bot = be13stod(parts[1]);
     return bot>0 ? top / bot : top;
 }
 
