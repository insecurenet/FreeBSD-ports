--- src/mkreleasehdr.sh.orig	2013-08-13 15:39:40.000000000 +0400
+++ src/mkreleasehdr.sh	2013-08-13 15:39:55.000000000 +0400
@@ -1,6 +1,6 @@
 #!/bin/sh
-GIT_SHA1=`(git show-ref --head --hash=8 2> /dev/null || echo 00000000) | head -n1`
-GIT_DIRTY=`git diff --no-ext-diff 2> /dev/null | wc -l`
+GIT_SHA1="00000000"
+GIT_DIRTY="0"
 BUILD_ID=`uname -n`"-"`date +%s`
 test -f release.h || touch release.h
 (cat release.h | grep SHA1 | grep $GIT_SHA1) && \
