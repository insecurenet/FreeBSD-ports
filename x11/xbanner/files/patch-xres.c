*** xres.c.org	Tue May 18 20:07:11 1999
--- xres.c	Tue May 18 20:30:50 1999
***************
*** 8,13 ****
--- 8,14 ----
  #include <string.h>
  #include <stdlib.h>
  #include <ctype.h>
+ #include <sys/param.h>
  
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
***************
*** 1196,1202 ****
    /* get the app-defaults */
  
  #ifndef vms
!   strcpy(line,"/usr/lib/X11/app-defaults/");
    strcat(line,PRGCLASS);
    appdefDB = XrmGetFileDatabase(line);
    if(appdefDB==NULL && getenv("XAPPLRESDIR")!=NULL)
--- 1197,1207 ----
    /* get the app-defaults */
  
  #ifndef vms
! #  if (defined(BSD) && (BSD >= 199306))
!      strcpy(line,"%%LOCALBASE%%/lib/X11/app-defaults/");
! #  else
!      strcpy(line,"/usr/lib/X11/app-defaults/");
! #  endif
    strcat(line,PRGCLASS);
    appdefDB = XrmGetFileDatabase(line);
    if(appdefDB==NULL && getenv("XAPPLRESDIR")!=NULL)
