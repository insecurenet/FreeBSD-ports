--- build.sh.orig	2010-02-12 17:49:56 UTC
+++ build.sh
@@ -41,9 +41,19 @@ case $OS in
 			MAKE_TYPE=gmake
 		fi
 		;;
+	"DragonFly")
+		SWT_OS=dragonfly
+		MAKEFILE=make_dragonfly.mak
+		if uname -p > /dev/null 2>&1; then
+			MODEL=`uname -p`
+		fi
+		;;
 	"FreeBSD")
 		SWT_OS=freebsd
 		MAKEFILE=make_freebsd.mak
+		if uname -p > /dev/null 2>&1; then
+			MODEL=`uname -p`
+		fi
 		;;
 	*)
 		SWT_OS=`uname -s | tr -s '[:upper:]' '[:lower:]'`
@@ -75,15 +85,16 @@ case $MODEL in
 esac
 
 # For 64-bit CPUs, we have a switch
-if [ ${MODEL} = 'x86_64' -o ${MODEL} = 'ppc64' -o ${MODEL} = 'ia64' -o ${MODEL} = 's390x' ]; then
+if [ ${MODEL} = 'x86_64' -o ${MODEL} = 'ppc64' -o ${MODEL} = 'ia64' -o ${MODEL} = 's390x' -o ${MODEL} = 'amd64' ]; then
 	SWT_PTR_CFLAGS=-DJNI64
 	export SWT_PTR_CFLAGS
 	if [ -d /lib64 ]; then
-		XLIB64=-L/usr/X11R6/lib64
+		XLIB64=-L${LOCALBASE}/lib64
 		export XLIB64
 	fi
 fi
 
+if [ x${MAKE_GNOME} = "xmake_gnome" ]; then
 if [ x`pkg-config --exists gnome-vfs-module-2.0 libgnome-2.0 libgnomeui-2.0 && echo YES` = "xYES" ]; then
 	echo "libgnomeui-2.0 found, compiling SWT program support using GNOME"
 	MAKE_GNOME=make_gnome
@@ -91,7 +102,9 @@ else
 	echo "libgnome-2.0 and libgnomeui-2.0 not found:"
 	echo "    *** SWT Program support for GNOME will not be compiled."
 fi
+fi
 
+if [ x${MAKE_CAIRO} = "xmake_cairo" ]; then
 if [ x`pkg-config --exists cairo && echo YES` = "xYES" ]; then
 	echo "Cairo found, compiling SWT support for the cairo graphics library."
 	MAKE_CAIRO=make_cairo
@@ -99,30 +112,17 @@ else
 	echo "Cairo not found:"
 	echo "    *** Advanced graphics support using cairo will not be compiled."
 fi
+fi
 
-if [ -z "${MOZILLA_INCLUDES}" -a -z "${MOZILLA_LIBS}" ]; then
-	if [ x`pkg-config --exists mozilla-xpcom && echo YES` = "xYES" ]; then
-		MOZILLA_INCLUDES=`pkg-config --cflags mozilla-xpcom`
-		MOZILLA_LIBS=`pkg-config --libs mozilla-xpcom`
-		export MOZILLA_INCLUDES
-		export MOZILLA_LIBS
-		MAKE_MOZILLA=make_mozilla
-	elif [ x`pkg-config --exists firefox-xpcom && echo YES` = "xYES" ]; then
-		MOZILLA_INCLUDES=`pkg-config --cflags firefox-xpcom`
-		MOZILLA_LIBS=`pkg-config --libs firefox-xpcom`
-		export MOZILLA_INCLUDES
-		export MOZILLA_LIBS
-		MAKE_MOZILLA=make_mozilla
-	elif [ x`pkg-config --exists libxul && echo YES` = "xYES" ]; then
-		XULRUNNER_INCLUDES=`pkg-config --cflags libxul`
-		XULRUNNER_LIBS=`pkg-config --libs libxul`
-		export XULRUNNER_INCLUDES
-		export XULRUNNER_LIBS
-		MAKE_MOZILLA=make_xulrunner
-	else
-		echo "None of the following libraries were found:  Mozilla/XPCOM, Firefox/XPCOM, or XULRunner/XPCOM"
-		echo "    *** Mozilla embedding support will not be compiled."
-	fi
+if [ x${MAKE_MOZILLA} = "xmake_xulrunner" ]; then
+	echo "Using libxul for gecko support"
+	XULRUNNER_INCLUDES=`pkg-config --cflags libxul libxul-embedding`
+	XULRUNNER_LIBS=`pkg-config --libs libxul libxul-embedding`
+	export XULRUNNER_INCLUDES
+	export XULRUNNER_LIBS
+else
+	echo "None of the following libraries were found:  XULRunner/XPCOM"
+	echo "    *** Mozilla embedding support will not be compiled."
 fi
 
 # Find AWT if available
