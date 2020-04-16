--- ./src/gm_ntfs.h.orig	2001-01-29 21:33:58.000000000 +0100
+++ ./src/gm_ntfs.h	2011-03-17 01:15:54.000000000 +0100
@@ -29,17 +29,16 @@
 /* 'NTFS' in little endian */
 #define NTFS_SUPER_MAGIC	0x5346544E
 
-#if defined(i386) || defined(__i386__) || defined(__alpha__)
+#include <stdint.h>
 
 /* unsigned integral types */
 #ifndef NTFS_INTEGRAL_TYPES
 #define NTFS_INTEGRAL_TYPES
-typedef unsigned char		ntfs_u8;
-typedef unsigned short		ntfs_u16;
-typedef unsigned int		ntfs_u32;
-typedef s64_t			ntfs_u64;
+typedef uint8_t		ntfs_u8;
+typedef uint16_t	ntfs_u16;
+typedef uint32_t	ntfs_u32;
+typedef uint64_t	ntfs_u64;
 #endif /* NTFS_INTEGRAL_TYPES */
-#endif /* defined(i386) || defined(__i386__) || defined(__alpha__) */
 
 
 /* Macros reading unsigned integers from a byte pointer */
@@ -53,8 +52,5 @@
 /* Macros reading signed integers, returning int */
 #define NTFS_GETS8(p)		((int)(*(char*)(p)))
 #define NTFS_GETS16(p)		((int)(*(short*)(p)))
-#define NTFS_GETS24(p)		(NTFS_GETU24(p) < 0x800000 ? (int)NTFS_GETU24(p) :
-
-
 
 #endif /* _GM_NTFS_H */
