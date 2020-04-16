--- routers2.cgi.pl.orig	2008-11-06 11:17:27.000000000 +0100
+++ routers2.cgi.pl	2008-11-06 11:19:06.000000000 +0100
@@ -1,9 +1,9 @@
-#!/usr/bin/perl 
+#!%%LOCALBASE%%/bin/perl
 # DONT FORGET TO CHANGE THE ABOVE PATH TO MATCH YOUR PERL LOCATION! 
 #vim:ts=4
 ##############################################################################
 # To use Speedycgi, you need to change the first line to this:
-##!/usr/bin/speedy -- -M20 -t3600 -gnone -r500
+###!%%LOCALBASE%%/bin/speedy -- -M20 -t3600 -gnone -r500
 # and then set the CACHE global variable (below) to 1.
 # To use mod_perl, you should be able to put the script directly into the
 # mod_perl directory and it will work.  This is not very thoroughly tested 
@@ -35,7 +35,7 @@
 #use Data::Dumper;     # For persistent caching
 ##CONFIG#START################################################################
 # You MUST set this to the location of the configuration file!
-my ($conffile) = '/u01/etc/routers2.conf';
+my ($conffile) = '%%LOCALBASE%%/etc/routers2.conf';
 ##############################################################################
 # Are we running in speedycgi or mod_perl mode?  Can we cache configs?
 # If you set this to 1 when you dont have speedycgi or mod_perl, it will
