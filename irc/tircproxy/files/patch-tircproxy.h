--- tircproxy.h	Sat Oct 15 06:49:51 2005
+++ tircproxy.h	Sat Oct 15 06:50:00 2005
@@ -34,8 +34,8 @@
 /* Set the location of the broadcast & MOTD files.  Undef these to disable
 ** the broadcasting feature.
 */
-#define BROADCAST_FILE		"/tmp/ircbroadcast"
-#define IRC_MOTD_FILE		"/etc/motd.irc"
+#define BROADCAST_FILE		"/usr/local/etc/tircproxy/ircbroadcast"
+#define IRC_MOTD_FILE		"/usr/local/etc/tircproxy/motd.irc"
 
 /* Enable this if you want to use the IPF code for tranparency.
 */
@@ -43,7 +43,7 @@
 
 /* Enable this if you want to use the Linux code for tranparency.
 */
-#define LINUX 1
+#define LINUX 0
 
 /* Enable this if you want to ask proxy users for passwords.
 */
@@ -117,11 +117,11 @@
 **
 ** This means the proxy does NOT need to run as root for ident responses to
 ** be correct.  This method is now obsolete - use UDB if at all possible!
-*/
+
 #define CDIR        "/var/oidentd/"
 #define CDIR_IDENT  "ident"
 #define CDIR_MAP    "user"
-
+*/
 
 /* The following table defines a list of filenames that are not
 ** to be handled transparently by the DCC code.. if replace points to
