--- include/libiberty.h 2017-09-14 09:28:17 UTC
+++ include/libiberty.h
@@ -109,7 +109,7 @@
  || defined (__FreeBSD__) || defined (__OpenBSD__) || defined (__NetBSD__) \
  || defined (__CYGWIN__) || defined (__CYGWIN32__) || defined (__MINGW32__) \
  || defined (__DragonFly__) || defined (HAVE_DECL_BASENAME) 
-extern char *basename (const char *) ATTRIBUTE_RETURNS_NONNULL ATTRIBUTE_NONNULL(1);
+#include <libgen.h>
 #else
 /* Do not allow basename to be used if there is no prototype seen.  We
    either need to use the above prototype or have one from
