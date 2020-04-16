diff --git src/hotkeys.c src/hotkeys.c
index b3ac52a..9a7cc82 100644
--- src/hotkeys.c
+++ src/hotkeys.c
@@ -54,7 +54,7 @@ extern char *getenv();
 #include <fcntl.h>
 #include <sys/ioctl.h>
 #if defined (__FreeBSD__)
-#include <machine/soundcard.h>
+#include <sys/soundcard.h>
 #else
 #       if defined (__NetBSD__) || defined (__OpenBSD__)
 #       include <soundcard.h>          /* OSS emulation */
@@ -66,9 +66,9 @@ extern char *getenv();
 #endif                          /* __FreeBSD__ */
 
 /* CDROM related */
-#include <linux/cdrom.h>        /* FIXME: linux specific! */
+//#include <linux/cdrom.h>        /* FIXME: linux specific! */
 /* APM (suspend/standby) support */
-#include "apm.h"
+//#include "apm.h"
 #if HAVE_GTK
   #include "splash.h"
 #endif
@@ -585,7 +585,7 @@ adjustVol(int adj)
 {
     int         mixer_fd = -1, cdrom_fd = -1;
     int         master_vol, cd_vol;
-    struct cdrom_volctrl cdrom_vol;
+//    struct cdrom_volctrl cdrom_vol;
     int         left, right;
     static struct timeval last_time;
     struct timeval this_time;
@@ -595,7 +595,7 @@ adjustVol(int adj)
     int sign = adj > 0 ? 1 : -1;
 
     if ( adj == 0 )
-        return;
+        return 0;
 
     if ( multiplier == 0 )
     {
@@ -683,6 +683,7 @@ adjustVol(int adj)
     }
 
     /* open the cdrom/dvdrom drive device */
+/***** ANDY: No CD support yet
     if ( cdromDevice != NULL )
     {
         if ( (cdrom_fd = open( cdromDevice, O_RDONLY|O_NONBLOCK )) == -1 )
@@ -691,7 +692,7 @@ adjustVol(int adj)
         }
         else
         {
-            /* read the cdrom volume */
+            || read the cdrom volume ||
             if ( ioctl(cdrom_fd, CDROMVOLREAD, &cdrom_vol) == -1 )
             {
                 uError("Unable to read the CDROM volume of `%s'", cdromDevice);
@@ -699,7 +700,7 @@ adjustVol(int adj)
             }
             else
             {
-                /* Set the CDROM volume */
+                || Set the CDROM volume ||
                 int     t;
                 float   myAdj;
                 myAdj = 0xFF / 100.0 * adj;
@@ -721,9 +722,10 @@ adjustVol(int adj)
             }
         }
     }
+END Andy *****/
 
     if (mixer_fd != -1)     close(mixer_fd);
-    if (cdrom_fd != -1)     close(cdrom_fd);
+//Andy    if (cdrom_fd != -1)     close(cdrom_fd);
 
     return ret;
 }
@@ -737,10 +739,10 @@ doMute(void)
 {
     static Bool             muted = False;
     static int              last_mixer_vol, last_cd_vol;
-    static struct cdrom_volctrl last_cdrom_vol;
+//Andy    static struct cdrom_volctrl last_cdrom_vol;
 
     int                     vol, cd_vol;
-    struct cdrom_volctrl    cdrom_vol;
+//Andy    struct cdrom_volctrl    cdrom_vol;
     int                     mixer_fd = -1, cdrom_fd = -1;
 
     short ret = 0;      /* return value */
@@ -751,6 +753,7 @@ doMute(void)
         uError("Unable to open `%s'", MIXER_DEV);
     }
     /* open the cdrom/dvdrom drive device */
+/***** Andy: No CD support
     if ( cdromDevice != NULL )
     {
         if ( (cdrom_fd = open( cdromDevice, O_RDONLY|O_NONBLOCK )) == -1 )
@@ -758,6 +761,7 @@ doMute(void)
             uError("Unable to open `%s'", cdromDevice);
         }
     }
+END Andy *****/
 
     if ( muted )
     {
@@ -783,6 +787,7 @@ doMute(void)
 #endif
             }
         }
+/***** Andy: No CD support
 #if 0
         if (SOUND_IOCTL(mixer_fd, SOUND_MIXER_WRITE_CD, &last_cd_vol) == -1)
         {
@@ -800,6 +805,7 @@ doMute(void)
             } else
                 muted = False;
         }
+End Andy *****/
     }
     else    /* ! muted */
     {
@@ -837,6 +843,7 @@ doMute(void)
                 }
             }
         }
+/***** Andy: No CD support
 #if 0
         if ( SOUND_IOCTL(mixer_fd, SOUND_MIXER_READ_CD, &last_cd_vol) == -1)
         {
@@ -853,7 +860,9 @@ doMute(void)
                 muted = True;
         }
 #endif
+End Andy *****/
         /* read and store the cdrom volume */
+/***** Andy: No CD support
         if (cdrom_fd != -1)
         {
             if ( ioctl(cdrom_fd, CDROMVOLREAD, &last_cdrom_vol) == -1 )
@@ -863,8 +872,8 @@ doMute(void)
             }
             else
             {
-                /* Set the volume to 0. FIXME: is this linux specific? Do
-                 * other platforms also have 4 channels? */
+                || Set the volume to 0. FIXME: is this linux specific? Do
+                 * other platforms also have 4 channels? ||
                 cdrom_vol.channel0 = cdrom_vol.channel1 = cdrom_vol.channel2 =
                     cdrom_vol.channel3 = 0;
                 if ( ioctl(cdrom_fd, CDROMVOLCTRL, &cdrom_vol) == -1 )
@@ -875,10 +884,11 @@ doMute(void)
                     muted = True;
             }
         }
+End Andy *****/
     }
 
     if (mixer_fd != -1)   close(mixer_fd);
-    if (cdrom_fd != -1)   close(cdrom_fd);
+//Andy    if (cdrom_fd != -1)   close(cdrom_fd);
 
     return ret;
 }
@@ -886,19 +896,20 @@ doMute(void)
 static int 
 ejectDisc(void)
 {
+/***** Andy: No CD support
     int fd, status;
 
     if ( cdromDevice == NULL )
         return 0;
 
-    /* the idea of this code is from xine's vcd plugin, mostly linux
-       specific FIXME */
+    || the idea of this code is from xine's vcd plugin, mostly linux
+       specific FIXME ||
     if ( (fd = open( cdromDevice, O_RDONLY | O_NONBLOCK)) > -1 ) {
         status = ioctl(fd, CDROM_DRIVE_STATUS, CDSL_CURRENT);
         switch (status)
         {
-            /* Looks like ATAPI drives doesn't return CDS_TRAY_OPEN,
-             * at least it's the case on my ASUS DVD drive... */
+            || Looks like ATAPI drives doesn't return CDS_TRAY_OPEN,
+             * at least it's the case on my ASUS DVD drive... ||
             case CDS_TRAY_OPEN:
 #ifdef HAVE_LIBXOSD
                 if ( osd )
@@ -929,7 +940,7 @@ ejectDisc(void)
             case CDS_NO_INFO:
             case CDS_DRIVE_NOT_READY:
             default:
-                /* Ignore */
+                || Ignore ||
                 break;
         }
         close(fd);
@@ -940,6 +951,7 @@ ejectDisc(void)
         SYSLOG(LOG_NOTICE, "CDROM_DRIVE_STATUS failed: %s\n", strerror(errno));
         return -1;
     }
+End Andy *****/
 }
 
 
@@ -1002,8 +1014,8 @@ launchApp(int keycode)
 #ifdef HAVE_LIBXOSD
         if ( osd )
         {
-            xosd_display(osd, 0, XOSD_string, "Launching:");
-            xosd_display(osd, 1, XOSD_string, getConfig(type));
+            xosd_display(osd, 0, XOSD_string, type);
+            xosd_display(osd, 1, XOSD_string, "");
         }
 #endif
     }
@@ -1015,13 +1027,14 @@ launchApp(int keycode)
 int
 sleepState(int mode)
 {
+/***** Andy: No APM support
 #ifdef USE_APMD
     switch (mode)
     {
-      case SUSPEND:
+    //  case SUSPEND:
         error = system("apm -s");
         break;
-      case STANDBY:
+    //  case STANDBY:
         error = system("apm -S");
         break;
       default:
@@ -1039,10 +1052,10 @@ sleepState(int mode)
     }
     switch (mode)
     {
-      case SUSPEND:
+     // case SUSPEND:
         error = apm_suspend(fd);
         break;
-      case STANDBY:
+     // case STANDBY:
         error = apm_standby(fd);
         break;
       default:
@@ -1050,7 +1063,9 @@ sleepState(int mode)
         break;
     }
     apm_close(fd);
-#endif /* USE_APMD */
+#endif 
+End Andy *****/
+/* USE_APMD */
 }
 
 
@@ -1105,8 +1120,8 @@ lookupUserCmd(const int keycode)
 #ifdef HAVE_LIBXOSD
                 if ( osd )
                 {
-                    xosd_display(osd, 0, XOSD_string, "Launching:");
-                    xosd_display(osd, 1, XOSD_string, kbd.customCmds[i].desc);
+                    xosd_display(osd, 0, XOSD_string, kbd.customCmds[i].desc);
+                    xosd_display(osd, 1, XOSD_string, "");
                 }
 #endif
                 break;  /* break the for loop */
@@ -1435,15 +1450,16 @@ initXOSD(void)
 #ifdef HAVE_LIBXOSD
     if ( osd )
     {
-        osd = xosd_init(xstrdup(getConfig("osd_font")),
-                        /* I dunno why, but you must call strdup here... */
-                        xstrdup(getConfig("osd_color")),
-                        atoi(getConfig("osd_timeout")),
-                        strncmp(getConfig("osd_position"),"top",3)?XOSD_bottom:XOSD_top,
-                        atoi(getConfig("osd_offset")), 
-                        3       /* shadow offset */,
-                        3       /* number_lines */ 
-                        );
+	osd = xosd_create(3);
+	xosd_set_pos(osd, strncmp(getConfig("osd_position"),"top",3)?XOSD_bottom:XOSD_top);
+	xosd_set_bar_length(osd, atoi(getConfig("osd_bar_length")));
+	xosd_set_colour(osd, xstrdup(getConfig("osd_color")));
+	xosd_set_shadow_colour(osd, xstrdup(getConfig("osd_shadow_color")));
+	xosd_set_shadow_offset(osd, atoi(getConfig("osd_shadow_offset")));
+	xosd_set_horizontal_offset(osd, atoi(getConfig("osd_hoffset")));
+	xosd_set_vertical_offset(osd, atoi(getConfig("osd_voffset")));
+	xosd_set_font(osd, xstrdup(getConfig("osd_font")));
+        xosd_set_align(osd, strncmp(getConfig("osd_align"),"left",4)?((!strncmp(getConfig("osd_align"),"center",6))?XOSD_center:XOSD_right):XOSD_left);
     }
 #endif
 }
@@ -1592,6 +1608,7 @@ main(int argc, char *argv[])
                 doMute();
             } else
             /* APM stuffs */
+/**** Andy: No APM support
             if ( ev.message.keycode == (kbd.defCmds)[sleepKey].key ||
                  ev.message.keycode == (kbd.defCmds)[wakeupKey].key ) {
                 sleepState(STANDBY);
@@ -1601,14 +1618,15 @@ main(int argc, char *argv[])
             }
             else
             {
+End Andy *****/
                 lookupUserCmd(ev.message.keycode);  /* User-defined stuffs */
-            }
+//Andy            }
         }
     }
 
 #ifdef HAVE_LIBXOSD
     if (osd)
-        xosd_uninit(osd);
+        xosd_destroy(osd);
 #endif
     XCloseDisplay(dpy);
     closelog();
