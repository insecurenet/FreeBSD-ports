--- src/Mk-fbx86.mk.DIST  Sat Jan 12 15:40:10 2002
+++ src/Mk-fbx86.mk       Sat Jan 12 15:40:55 2002
@@ -21,7 +21,7 @@
 
 # Build definitions
 SRC = ../../src
-CFLAGS = -c -g3 -O -I. -I$(SRC)
+CFLAGS += -c -I. -I$(SRC)
 CFLAGS_LINT = -ansi -pedantic -Wall -Wshadow \
                -Wstrict-prototypes -Wmissing-prototypes \
                -Wmissing-declarations -Wredundant-decls

