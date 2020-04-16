*** include/config.h.orig	Fri Jul 15 06:02:52 1994
--- include/config.h	Sun Dec 31 18:56:20 1989
***************
*** 17,23 ****
   ***	file that corresponds with your operating system.
   ***/
  
! #include "../configs/conf-svr4.h"
  
  #ifdef TW_TYPE32
  typedef TW_TYPE32 int32;
--- 17,23 ----
   ***	file that corresponds with your operating system.
   ***/
  
! #include "../configs/conf-freebsd2.h"
  
  #ifdef TW_TYPE32
  typedef TW_TYPE32 int32;
***************
*** 103,110 ****
  #endif
  */
  
! #define CONFIG_PATH     "/usr/local/bin/tw"
! #define DATABASE_PATH   "/var/tripwire"
  
  /******* name of Tripwire files **************************************
   *
--- 103,110 ----
  #endif
  */
  
! # define CONFIG_PATH     "/var/adm/tcheck"
! # define DATABASE_PATH   "/var/adm/tcheck/databases"
  
  /******* name of Tripwire files **************************************
   *
