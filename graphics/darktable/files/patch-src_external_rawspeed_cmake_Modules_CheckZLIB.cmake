--- src/external/rawspeed/cmake/Modules/CheckZLIB.cmake.orig	2018-01-18 18:05:10 UTC
+++ src/external/rawspeed/cmake/Modules/CheckZLIB.cmake
@@ -38,7 +38,7 @@ endif()
 CHECK_PROTOTYPE_DEFINITION(zError
  "const char* zError(int zErrorCode)"
  "NULL"
- "zlib.h"
+ "stddef.h;zlib.h"
  HAVE_ZLIB_ZERROR_PROTOTYPE)
 if(NOT HAVE_ZLIB_ZERROR_PROTOTYPE)
   message(SEND_ERROR "Found unexpected prototype for zError() in <zlib.h>")
