--- storage/myisam/mi_dynrec.c.orig	2018-03-16 23:50:04.334166000 +0300
+++ storage/myisam/mi_dynrec.c	2018-03-16 23:50:29.996533000 +0300
@@ -65,18 +65,13 @@
     DBUG_RETURN(1);
   }
   /*
-    I wonder if it is good to use MAP_NORESERVE. From the Linux man page:
-    MAP_NORESERVE
-      Do not reserve swap space for this mapping. When swap space is
-      reserved, one has the guarantee that it is possible to modify the
-      mapping. When swap space is not reserved one might get SIGSEGV
-      upon a write if no physical memory is available.
+      MAP_NORESERVE is unimplemented in FreeBSD
   */
   info->s->file_map= (uchar*)
                   my_mmap(0, (size_t) size,
                           info->s->mode==O_RDONLY ? PROT_READ :
                           PROT_READ | PROT_WRITE,
-                          MAP_SHARED | MAP_NORESERVE,
+                          MAP_SHARED,
                           info->dfile, 0L);
   if (info->s->file_map == (uchar*) MAP_FAILED)
   {
