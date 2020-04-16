--- make_freebsd.mak.orig	2009-06-11 16:10:54.000000000 -0500
+++ make_freebsd.mak	2009-07-11 08:37:19.000000000 -0500
@@ -1,5 +1,5 @@
 #*******************************************************************************
-# Copyright (c) 2000, 2007 IBM Corporation and others.
+# Copyright (c) 2000, 2009 IBM Corporation and others.
 # All rights reserved. This program and the accompanying materials
 # are made available under the terms of the Eclipse Public License v1.0
 # which accompanies this distribution, and is available at
@@ -9,7 +9,7 @@
 #     IBM Corporation - initial API and implementation
 #*******************************************************************************
 
-# Makefile for creating SWT libraries for Linux GTK
+# Makefile for creating SWT libraries for FreeBSD GTK
 
 include make_common.mak
 
@@ -46,7 +46,7 @@
 
 # Do not use pkg-config to get libs because it includes unnecessary dependencies (i.e. pangoxft-1.0)
 GTKCFLAGS = `pkg-config --cflags gtk+-2.0`
-GTKLIBS = `pkg-config --libs-only-L gtk+-2.0 gthread-2.0` -lgtk-x11-2.0 -lgthread-2.0 -L/usr/X11R6/lib $(XLIB64) -lXtst
+GTKLIBS = `pkg-config --libs-only-L gtk+-2.0 gthread-2.0` -lgtk-x11-2.0 -lgthread-2.0 -L$(LOCALBASE)/lib $(XLIB64) -lXtst
 
 CDE_LIBS = -L$(CDE_HOME)/lib -R$(CDE_HOME)/lib -lXt -lX11 -lDtSvc
 
@@ -58,8 +58,8 @@
 GNOMECFLAGS = `pkg-config --cflags gnome-vfs-module-2.0 libgnome-2.0 libgnomeui-2.0`
 GNOMELIBS = `pkg-config --libs-only-L gnome-vfs-module-2.0 libgnome-2.0 libgnomeui-2.0` -lgnomevfs-2 -lgnome-2 -lgnomeui-2
 
-GLXCFLAGS = 
-GLXLIBS = -shared -fPIC -L/usr/X11R6/lib -lGL -lGLU -lm
+GLXCFLAGS = -I$(LOCALBASE)/include
+GLXLIBS = -shared -fPIC -L$(LOCALBASE)/lib -lGL -lGLU -lm
 
 # Uncomment for Native Stats tool
 #NATIVE_STATS = -DNATIVE_STATS
@@ -78,7 +78,17 @@
 	-I$(JAVA_HOME)/include/freebsd \
 	${SWT_PTR_CFLAGS}
 MOZILLALIBS = -shared -Wl,--version-script=mozilla_exports -Bsymbolic
-	
+MOZILLAEXCLUDES = -DNO__1XPCOMGlueShutdown \
+	-DNO__1XPCOMGlueStartup \
+	-DNO__1XPCOMGlueLoadXULFunctions \
+	-DNO_memmove__ILorg_eclipse_swt_internal_mozilla_nsDynamicFunctionLoad_2I \
+	-DNO_memmove__JLorg_eclipse_swt_internal_mozilla_nsDynamicFunctionLoad_2J \
+	-DNO_nsDynamicFunctionLoad_1sizeof \
+	-DNO__1Call__IIIIII \
+	-DNO__1Call__JJJJJI \
+	-DNO_nsDynamicFunctionLoad
+XULRUNNEREXCLUDES = -DNO__1NS_1InitXPCOM2
+
 SWT_OBJECTS = swt.o c.o c_stats.o callback.o
 CDE_OBJECTS = swt.o cde.o cde_structs.o cde_stats.o
 AWT_OBJECTS = swt_awt.o
@@ -87,7 +97,7 @@
 ATK_OBJECTS = swt.o atk.o atk_structs.o atk_custom.o atk_stats.o
 GNOME_OBJECTS = swt.o gnome.o gnome_structs.o gnome_stats.o
 MOZILLA_OBJECTS = swt.o xpcom.o xpcom_custom.o xpcom_structs.o xpcom_stats.o
-XULRUNNER_OBJECTS = swt.o xpcomxul.o xpcomxul_custom.o xpcomxul_structs.o xpcomxul_stats.o xpcomxulglue.o xpcomxulglue_stats.o
+XULRUNNER_OBJECTS = swt.o xpcomxul.o xpcomxul_custom.o xpcomxul_structs.o xpcomxul_stats.o
 XPCOMINIT_OBJECTS = swt.o xpcominit.o xpcominit_structs.o xpcominit_stats.o
 GLX_OBJECTS = swt.o glx.o glx_structs.o glx_stats.o
 
@@ -95,19 +105,20 @@
 		-DSWT_VERSION=$(SWT_VERSION) \
 		$(NATIVE_STATS) \
 		-DFREEBSD -DGTK \
+		-I$(LOCALBASE)/include \
 		-I$(JAVA_HOME)/include \
 		-I$(JAVA_HOME)/include/freebsd \
 		-fPIC \
 		${SWT_PTR_CFLAGS}
 LIBS = -shared -fPIC
 
-ifndef NO_STRIP
-	AWT_LIBS := $(AWT_LIBS) -s
-	MOZILLALIBS := $(MOZILLALIBS) -s
-	LIBS := $(LIBS) -s
-endif
+.ifndef NO_STRIP
+AWT_LIBS := $(AWT_LIBS) -s
+MOZILLALIBS := $(MOZILLALIBS) -s
+LIBS := $(LIBS) -s
+.endif
 
-all: make_swt make_atk make_gnome make_glx
+all: make_swt make_atk make_glx
 
 #
 # SWT libs
@@ -209,16 +220,16 @@
 	$(CXX) -o $(MOZILLA_LIB) $(MOZILLA_OBJECTS) $(MOZILLALIBS) ${MOZILLA_LIBS}
 
 xpcom.o: xpcom.cpp
-	$(CXX) $(MOZILLACFLAGS) ${MOZILLA_INCLUDES} -c xpcom.cpp
+	$(CXX) $(MOZILLACFLAGS) $(MOZILLAEXCLUDES) ${MOZILLA_INCLUDES} -c xpcom.cpp
 
 xpcom_structs.o: xpcom_structs.cpp
-	$(CXX) $(MOZILLACFLAGS) ${MOZILLA_INCLUDES} -c xpcom_structs.cpp
+	$(CXX) $(MOZILLACFLAGS) $(MOZILLAEXCLUDES) ${MOZILLA_INCLUDES} -c xpcom_structs.cpp
 	
 xpcom_custom.o: xpcom_custom.cpp
-	$(CXX) $(MOZILLACFLAGS) ${MOZILLA_INCLUDES} -c xpcom_custom.cpp
+	$(CXX) $(MOZILLACFLAGS) $(MOZILLAEXCLUDES) ${MOZILLA_INCLUDES} -c xpcom_custom.cpp
 
 xpcom_stats.o: xpcom_stats.cpp
-	$(CXX) $(MOZILLACFLAGS) ${MOZILLA_INCLUDES} -c xpcom_stats.cpp
+	$(CXX) $(MOZILLACFLAGS) $(MOZILLAEXCLUDES) ${MOZILLA_INCLUDES} -c xpcom_stats.cpp
 
 #
 # XULRunner lib
@@ -229,22 +240,16 @@
 	$(CXX) -o $(XULRUNNER_LIB) $(XULRUNNER_OBJECTS) $(MOZILLALIBS) ${XULRUNNER_LIBS}
 
 xpcomxul.o: xpcom.cpp
-	$(CXX) -o xpcomxul.o $(MOZILLACFLAGS) ${XULRUNNER_INCLUDES} -c xpcom.cpp
+	$(CXX) -o xpcomxul.o $(MOZILLACFLAGS) $(XULRUNNEREXCLUDES) ${XULRUNNER_INCLUDES} -c xpcom.cpp
 
 xpcomxul_structs.o: xpcom_structs.cpp
-	$(CXX) -o xpcomxul_structs.o $(MOZILLACFLAGS) ${XULRUNNER_INCLUDES} -c xpcom_structs.cpp
+	$(CXX) -o xpcomxul_structs.o $(MOZILLACFLAGS) $(XULRUNNEREXCLUDES) ${XULRUNNER_INCLUDES} -c xpcom_structs.cpp
 	
 xpcomxul_custom.o: xpcom_custom.cpp
-	$(CXX) -o xpcomxul_custom.o $(MOZILLACFLAGS) ${XULRUNNER_INCLUDES} -c xpcom_custom.cpp
+	$(CXX) -o xpcomxul_custom.o $(MOZILLACFLAGS) $(XULRUNNEREXCLUDES) ${XULRUNNER_INCLUDES} -c xpcom_custom.cpp
 
 xpcomxul_stats.o: xpcom_stats.cpp
-	$(CXX) -o xpcomxul_stats.o $(MOZILLACFLAGS) ${XULRUNNER_INCLUDES} -c xpcom_stats.cpp
-
-xpcomxulglue.o: xpcomglue.cpp
-	$(CXX) -o xpcomxulglue.o $(MOZILLACFLAGS) ${XULRUNNER_INCLUDES} -c xpcomglue.cpp
-
-xpcomxulglue_stats.o: xpcomglue_stats.cpp
-	$(CXX) -o xpcomxulglue_stats.o $(MOZILLACFLAGS) ${XULRUNNER_INCLUDES} -c xpcomglue_stats.cpp
+	$(CXX) -o xpcomxul_stats.o $(MOZILLACFLAGS) $(XULRUNNEREXCLUDES) ${XULRUNNER_INCLUDES} -c xpcom_stats.cpp
 
 #
 # XPCOMInit lib
