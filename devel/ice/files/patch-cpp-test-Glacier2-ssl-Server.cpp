--- cpp.orig/test/Glacier2/ssl/Server.cpp	2011-06-15 21:43:59.000000000 +0200
+++ cpp/test/Glacier2/ssl/Server.cpp	2012-03-04 20:14:53.000000000 +0100
@@ -31,9 +31,15 @@
         test(ctx["_con.type"] == "ssl");
         test(ctx["_con.localPort"] == "12348");
     }
-    test(ctx["_con.localAddress"] == "127.0.0.1");
+    if (!inFreeBSDJail())
+    {
+        test(ctx["_con.localAddress"] == "127.0.0.1");
+    }
     test(ctx["_con.remotePort"] != "");
-    test(ctx["_con.remoteAddress"] == "127.0.0.1");
+    if (!inFreeBSDJail())
+    {
+        test(ctx["_con.remoteAddress"] == "127.0.0.1");
+    }
 }
 
 }
@@ -133,8 +139,11 @@
     {
         testContext(true, current.ctx);
 
-        test(info.remoteHost == "127.0.0.1");
-        test(info.localHost == "127.0.0.1");
+        if (!inFreeBSDJail())
+        {
+            test(info.remoteHost == "127.0.0.1");
+            test(info.localHost == "127.0.0.1");
+        }
         test(info.localPort == 12348);
 
         try
