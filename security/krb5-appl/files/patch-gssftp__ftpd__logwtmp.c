*** gssftp/ftpd/logwtmp.c.ORIG	Fri Feb  6 19:41:25 1998
--- gssftp/ftpd/logwtmp.c	Tue Jun 30 19:46:01 1998
***************
*** 66,72 ****
  	struct stat buf;
  	time_t time();
  
! 	if (fd < 0 && (fd = open(WTMPFILE, O_WRONLY|O_APPEND, 0)) < 0)
  		return;
  	if (fstat(fd, &buf) == 0) {
  		(void)strncpy(ut.ut_line, line, sizeof(ut.ut_line));
--- 66,72 ----
  	struct stat buf;
  	time_t time();
  
! 	if (fd < 0 && (fd = open(WTMP_FILE, O_WRONLY|O_APPEND, 0)) < 0)
  		return;
  	if (fstat(fd, &buf) == 0) {
  		(void)strncpy(ut.ut_line, line, sizeof(ut.ut_line));
