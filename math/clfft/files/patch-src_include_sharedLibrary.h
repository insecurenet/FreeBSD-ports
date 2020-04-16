--- src/include/sharedLibrary.h.orig	2016-08-31 21:46:51 UTC
+++ src/include/sharedLibrary.h
@@ -52,7 +52,7 @@ inline void* LoadSharedLibrary( std::str
   {
           std::cerr << ::dlerror( ) << std::endl;
   }
-#elif defined(__FreeBSD_kernel__)
+#elif defined(__FreeBSD_kernel__) || defined (__FreeBSD__)
         tstring freebsdName = unixPrefix;
         freebsdName += libraryName += ".so";
         void* fileHandle = ::dlopen( freebsdName.c_str( ), RTLD_NOW );
