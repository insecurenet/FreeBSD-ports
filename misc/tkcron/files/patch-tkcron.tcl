--- tkcron.tcl.orig	2013-09-25 00:48:19.068508511 -0700
+++ tkcron.tcl	2013-09-25 06:10:06.670101791 -0700
@@ -1,4 +1,6 @@
-#!/usr/local/bin/wish
+#! /bin/sh
+# the next line restarts using wish \
+exec %%WISH%% $0 ${1+"$@"}
 
 # A simple interface to ease the creation of crontab jobs
 # Cedric BEUST (beust@sophia.inria.fr)
@@ -281,6 +283,7 @@
 
 # Return the crontab string as a list
 proc parseCrontabFile {str} {
+    set result ""
     set crontablist [split $str \n]
     set listlength [llength $crontablist]
     for {set i 0} {$i < $listlength} {incr i 1} {
