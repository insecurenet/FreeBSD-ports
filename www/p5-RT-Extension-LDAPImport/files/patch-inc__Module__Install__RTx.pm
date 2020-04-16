--- inc/Module/Install/RTx.pm.orig	2014-09-22 20:18:51 UTC
+++ inc/Module/Install/RTx.pm
@@ -85,7 +85,7 @@
     my %index = map { $_ => 1 } @INDEX_DIRS;
     $self->no_index( directory => $_ ) foreach grep !$index{$_}, @DIRS;
 
-    my $args = join ', ', map "q($_)", map { ($_, $path{$_}) }
+    my $args = join ', ', map "q($_)", map { ($_, "\${DESTDIR}$path{$_}") }
         sort keys %path;
 
     printf "%-10s => %s\n", $_, $path{$_} for sort keys %path;
