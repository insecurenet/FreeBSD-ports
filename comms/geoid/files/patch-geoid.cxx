--- geoid.cxx.orig	Mon Dec 18 13:53:07 2006
+++ geoid.cxx	Tue Mar 20 22:02:44 2007
@@ -28,10 +28,8 @@
 	strFname.append("/.geoid/country.pos");
   
  	if (ReadGeoFile((char *)strFname.c_str()) == -1) {
- 		strFname = szHomedir;
- 		strFname.append("/country.pos");
- 		if (ReadGeoFile((char *)strFname.c_str()) == -1) {
-	  		fl_message("Cannot open %s", (char *)strFname.c_str());
+ 		if (ReadGeoFile("%%LOCALBASE%%/share/geoid/country.pos") == -1) {
+	  		fl_message("Cannot open country.pos");
   			exit(0);
  		}
 	}
