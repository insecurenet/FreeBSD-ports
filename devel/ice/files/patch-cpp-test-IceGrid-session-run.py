--- cpp/test/IceGrid/session/run.py.orig	2015-07-03 19:05:11.680636978 +0200
+++ cpp/test/IceGrid/session/run.py	2015-07-03 19:18:59.590608978 +0200
@@ -20,11 +20,14 @@
 sys.path.append(os.path.join(path[0], "scripts"))
 import TestUtil, IceGridAdmin
 
+dbdir = os.path.join(os.getcwd(), "db")
+
 if not TestUtil.isWin32() and os.getuid() == 0:
-    sys.stdout.write("\n")
-    sys.stdout.write("*** can't run test as root ***\n")
-    sys.stdout.write("\n")
-    sys.exit(0)
+    for root, dirs, files in os.walk(dbdir):
+        os.chown(os.path.join(dbdir, root), 65534, 65534)
+        for f in files:
+            os.chown(os.path.join(dbdir, root, f), 65534, 65534)
+    os.setuid(65534)
 
 name = os.path.join("IceGrid", "session")
 
