--- ipv6mon.c.orig	2012-09-20 13:02:24.000000000 +0900
+++ ipv6mon.c	2012-09-20 13:02:26.000000000 +0900
@@ -277,7 +277,7 @@
 	}
 
 	if(!configfile_f){
-		configfile="/etc/ipv6mon.conf";
+		configfile=IPV6MON_CONF;
 	}
 
 	if(process_config_file(configfile) == -1)
@@ -888,7 +888,8 @@
 	usage();
     
 	puts("\nOPTIONS:\n"
-	     "  --config-file, -c    Configuration file pathname (defaults to '/etc/ipv6mon.conf')\n"
+	     "  --config-file, -c    Configuration file pathname (defaults to '"
+ IPV6MON_CONF "')\n"
 		 "  --show-config, -q    Shows configuration values and quits\n"
 	     "  --help, -h           Print help for the scan6 tool\n"
 	     "  --verbose, -v        Be verbose\n"
