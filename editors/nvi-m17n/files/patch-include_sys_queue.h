--- ../include/sys/queue.h.old	Wed Jan 10 07:16:01 2001
+++ ../include/sys/queue.h	Wed Jan 10 07:17:02 2001
@@ -33,8 +33,10 @@
  *	@(#)queue.h	8.5 (Berkeley) 8/20/94
  */
 
-#ifndef	_SYS_QUEUE_H_
-#define	_SYS_QUEUE_H_
+#ifndef	_SYS_QUEUE_HACK_H_
+#define	_SYS_QUEUE_HACK_H_
+
+#include <sys/queue_dist.h>
 
 /*
  * This file defines three types of data structures: lists, tail queues,
@@ -65,6 +67,7 @@
  * For details on the use of these macros, see the queue(3) manual page.
  */
 
+#ifndef LIST_HEAD
 /*
  * List definitions.
  */
@@ -114,7 +117,9 @@
 		    (elm)->field.le_prev;				\
 	*(elm)->field.le_prev = (elm)->field.le_next;			\
 }
+#endif /* LIST_HEAD */
 
+#ifndef TAILQ_HEAD
 /*
  * Tail queue definitions.
  */
@@ -180,7 +185,9 @@
 		(head)->tqh_last = (elm)->field.tqe_prev;		\
 	*(elm)->field.tqe_prev = (elm)->field.tqe_next;			\
 }
+#endif /* TAILQ_HEAD */
 
+#ifndef CIRCLEQ_HEAD
 /*
  * Circular queue definitions.
  */
@@ -256,4 +263,6 @@
 		(elm)->field.cqe_prev->field.cqe_next =			\
 		    (elm)->field.cqe_next;				\
 }
-#endif	/* !_SYS_QUEUE_H_ */
+#endif /* CIRCLEQ_HEAD */
+
+#endif	/* !_SYS_QUEUE_HACK_H_ */
