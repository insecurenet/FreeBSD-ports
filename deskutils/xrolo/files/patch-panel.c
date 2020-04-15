*** panel.c.orig	Wed Dec  4 01:38:09 1991
--- panel.c	Sat Oct  1 20:05:54 2005
***************
*** 35,40 ****
--- 35,48 ----
   */
  
  
+ #if (defined(__unix__) || defined(unix)) && !defined(USG)
+ #include <sys/param.h>
+ #endif
+ 
+ #if (defined(BSD) && (BSD >= 199306))
+ #include <stdlib.h>
+ #endif
+ 
  #include <stdio.h>
  #include <strings.h>
  #include <xview/xview.h>
***************
*** 46,52 ****
  #include <xview/svrimage.h>
  #include <sys/param.h>
  #include <ctype.h>
! #if !defined (sgi)
  #include <alloca.h>
  #endif
  #include <string.h>
--- 54,60 ----
  #include <xview/svrimage.h>
  #include <sys/param.h>
  #include <ctype.h>
! #if !defined (sgi) && !(defined(BSD) && (BSD >= 199306))
  #include <alloca.h>
  #endif
  #include <string.h>
***************
*** 2462,2465 ****
  	  return(--s1);
  	return( NULL );
  }
- 
--- 2470,2472 ----
