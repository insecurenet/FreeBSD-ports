*** src/docmd.c	1995/07/21 09:53:30	1.1.1.1
--- src/docmd.c	1995/07/21 10:07:14	1.2
***************
*** 251,259 ****
  	char *cmd;
  {
  	int desc;
- #if	defined(DIRECT_RCMD)
  	static int port = -1;
- #endif	/* DIRECT_RCMD */
  
  	debugmsg(DM_MISC, "local user = %s remote user = %s\n", luser, ruser);
  	debugmsg(DM_MISC, "Remote command = '%s'\n", cmd);
--- 251,257 ----
***************
*** 280,290 ****
  	if (becomeuser() != 0)
  		exit(1);
  #else	/* !DIRECT_RCMD */
! 	debugmsg(DM_MISC, "Remote shell command = '%s'\n", path_remsh);
! 	(void) signal(SIGPIPE, SIG_IGN);
! 	desc = rshrcmd(&rhost, -1, luser, ruser, cmd, 0);
! 	if (desc > 0)
  		(void) signal(SIGPIPE, sighandler);
  #endif	/* DIRECT_RCMD */
  
  	(void) alarm(0);
--- 278,303 ----
  	if (becomeuser() != 0)
  		exit(1);
  #else	/* !DIRECT_RCMD */
! 	if (geteuid() == 0 && strcmp(path_remsh, "/usr/bin/rsh") == 0) {
! 		debugmsg(DM_MISC, "I am root, using rsh, therefore direct rcmd\n");
  		(void) signal(SIGPIPE, sighandler);
+ 
+ 		if (port < 0) {
+ 			struct servent *sp;
+ 		
+ 			if ((sp = getservbyname("shell", "tcp")) == NULL)
+ 				fatalerr("shell/tcp: unknown service");
+ 			port = sp->s_port;
+ 		}
+ 
+ 		desc = rcmd(&rhost, port, luser, ruser, cmd, 0);
+ 	} else {
+ 		debugmsg(DM_MISC, "Remote shell command = '%s'\n", path_remsh);
+ 		(void) signal(SIGPIPE, SIG_IGN);
+ 		desc = rshrcmd(&rhost, -1, luser, ruser, cmd, 0);
+ 		if (desc > 0)
+ 			(void) signal(SIGPIPE, sighandler);
+ 	}
  #endif	/* DIRECT_RCMD */
  
  	(void) alarm(0);
