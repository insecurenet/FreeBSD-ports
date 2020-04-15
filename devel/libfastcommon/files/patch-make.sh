--- make.sh.orig	2016-09-08 07:44:31 UTC
+++ make.sh
@@ -1,55 +1,15 @@
-tmp_src_filename=fast_check_bits.c
-cat <<EOF > $tmp_src_filename
-#include <stdio.h>
-#include <unistd.h>
-#include <fcntl.h>
-int main()
-{
-	printf("%d\n", (int)sizeof(void*));
-	printf("%d\n", (int)sizeof(off_t));
-	return 0;
-}
-EOF
-
-gcc -D_FILE_OFFSET_BITS=64 -o a.out $tmp_src_filename
-output=`./a.out`
-
-if [ -f /bin/expr ]; then
-  EXPR=/bin/expr
-else
-  EXPR=/usr/bin/expr
-fi
-
-count=0
-int_bytes=4
-off_bytes=8
-LIB_VERSION=lib64
-
-for col in $output; do
-    if [ $count -eq 0 ]; then
-        int_bytes=$col
-    else
-        off_bytes=$col
-    fi
-
-    count=`$EXPR $count + 1`
-done
+unamep=$(/usr/bin/uname -p)
 
-/bin/rm -f a.out $tmp_src_filename
-if [ "$int_bytes" -eq 8 ]; then
+if [ "$unamep" = "amd64" -o "$unamep" = "x86_64" ]; then
  OS_BITS=64
- LIB_VERSION=lib64
-else
- OS_BITS=32
- LIB_VERSION=lib
-fi
-
-if [ "$off_bytes" -eq 8 ]; then
  OFF_BITS=64
 else
+ OS_BITS=32
  OFF_BITS=32
 fi
 
+LIB_VERSION=lib
+
 DEBUG_FLAG=0
 
 CFLAGS='-Wall -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE'
@@ -67,12 +27,9 @@ HAVE_USER_H=0
 if [ "$uname" = "Linux" ]; then
   OS_NAME=OS_LINUX
   IOEVENT_USE=IOEVENT_USE_EPOLL
-elif [ "$uname" = "FreeBSD" ] || [ "$uname" = "Darwin" ]; then
+elif [ "$uname" = "FreeBSD" -o "$uname" = "DragonFly" ]; then
   OS_NAME=OS_FREEBSD 
   IOEVENT_USE=IOEVENT_USE_KQUEUE
-  if [ "$uname" = "Darwin" ]; then
-    CFLAGS="$CFLAGS -DDARWIN"
-  fi
 
   if [ -f /usr/include/sys/vmmeter.h ]; then
      HAVE_VMMETER_H=1
@@ -138,7 +95,7 @@ sed_replace()
 {
     sed_cmd=$1
     filename=$2
-    if [ "$uname" = "FreeBSD" ] || [ "$uname" = "Darwin" ]; then
+    if [ "$uname" = "FreeBSD" -o "$uname" = "DragonFly" ]; then
        sed -i "" "$sed_cmd" $filename
     else
        sed -i "$sed_cmd" $filename
