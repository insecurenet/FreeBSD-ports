$NetBSD: patch-ah,v 1.1 2000/05/05 20:54:57 hubertf Exp $

--- festival/config/modules/nas_audio.mak.orig	Fri May  5 21:07:15 2000
+++ festival/config/modules/nas_audio.mak	Fri May  5 21:07:29 2000
@@ -44,6 +44,6 @@
 
 AUDIO_DEFINES += -DSUPPORT_NAS
 AUDIO_INCLUDES += -I$(NAS_INCLUDE)
-MODULE_LIBS += -L$(NAS_LIB) -laudio -L$(X11_LIB) -lX11 -lXt
+MODULE_LIBS += -L$(NAS_LIB) -laudio -L$(X11_LIB) -Wl,-R$(X11_LIB) -lX11 -lXt
 
 
