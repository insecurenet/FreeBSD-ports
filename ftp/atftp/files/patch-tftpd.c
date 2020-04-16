--- tftpd.c.orig	2004-02-27 10:05:26.000000000 +0800
+++ tftpd.c	2011-02-09 14:18:04.000000000 +0800
@@ -60,6 +60,9 @@
 char directory[MAXLEN] = "/tftpboot/";
 int retry_timeout = S_TIMEOUT;
 
+int on = 1;
+int listen_local = 0;
+
 int tftpd_daemon = 0;           /* By default we are started by inetd */
 int tftpd_daemon_no_fork = 0;   /* For who want a false daemon mode */
 short tftpd_port = 0;           /* Port atftpd listen to */
@@ -157,6 +160,7 @@
      struct servent *serv;
      struct passwd *user;
      struct group *group;
+     pthread_t tid;
 
 #ifdef HAVE_MTFTP
      pthread_t mtftp_thread;
@@ -253,7 +257,7 @@
           else
                sa.sin_addr.s_addr = htonl(INADDR_ANY);
           /* open the socket */
-          if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == 0)
+          if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
           {
                logger(LOG_ERR, "atftpd: can't open socket");
                exit(1);
@@ -301,7 +305,7 @@
      }
 
      /* We need to retieve some information from incomming packets */
-     if (setsockopt(0, SOL_IP, IP_PKTINFO, &one, sizeof(one)) != 0)
+     if (setsockopt(0, IPPROTO_IP, IP_RECVDSTADDR, &one, sizeof(one)) != 0)
      {
           logger(LOG_WARNING, "Failed to set socket option: %s", strerror(errno));
      }
@@ -387,10 +391,21 @@
              packets */
           if (!tftpd_cancel)
           {
+               int rv;
+
                if ((tftpd_timeout == 0) || (tftpd_daemon))
-                    select(FD_SETSIZE, &rfds, NULL, NULL, NULL);
+                    rv = select(FD_SETSIZE, &rfds, NULL, NULL, NULL);
                else
-                    select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
+                    rv = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
+               if (rv < 0) {
+                    if (errno == EINTR)
+                        continue;
+                    logger(LOG_ERR, "%s: %d: select: %s",
+                           __FILE__, __LINE__, strerror(errno));
+
+                    /* Clear the bits, they are undefined! */
+                    FD_ZERO(&rfds);
+	       }
           }
 
 #ifdef RATE_CONTROL
@@ -463,10 +478,12 @@
                     exit(1);
                }
                new->client_info->done = 0;
+               new->client_info->bytes_sent = 0;
                new->client_info->next = NULL;
+               new->client_info->last_ack = -1;
                
                /* Start a new server thread. */
-               if (pthread_create(&new->tid, NULL, tftpd_receive_request,
+               if (pthread_create(&tid, NULL, tftpd_receive_request,
                                   (void *)new) != 0)
                {
                     logger(LOG_ERR, "Failed to start new thread");
@@ -567,7 +584,8 @@
 
      /* Detach ourself. That way the main thread does not have to
       * wait for us with pthread_join. */
-     pthread_detach(pthread_self());
+     data->tid = pthread_self();
+     pthread_detach(data->tid);
 
      /* Read the first packet from stdin. */
      data_size = data->data_buffer_size;     
@@ -615,7 +633,25 @@
           data->sockfd = socket(PF_INET, SOCK_DGRAM, 0);
           to.sin_family = AF_INET;
           to.sin_port = 0;
-          if (data->sockfd > 0)
+          /* Force socket to listen on local address. Do not listen on broadcast address 255.255.255.255. 
+             If the socket listens on the broadcast address, Linux tells the remote client the port
+             is unreachable. This happens even if SO_BROADCAST is set in setsockopt for this socket.
+             I was unable to find a kernel option or /proc/sys flag to make the kernel pay attention to 
+             these requests, so the workaround is to force listening on the local address. */
+          if (listen_local == 1)
+          { 
+               to.sin_addr.s_addr = INADDR_ANY;
+               logger(LOG_INFO, "forcing socket to listen on local address");
+               if (setsockopt(data->sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) != 0) {
+                  logger(LOG_ERR, "setsockopt: %s", strerror(errno));
+               }
+          }
+          else
+          {
+               logger(LOG_INFO, "socket may listen on any address, including broadcast");
+          }
+
+          if (data->sockfd >= 0)
           {
                /* bind the socket to the interface */
                if (bind(data->sockfd, (struct sockaddr *)&to, len) == -1)
@@ -630,17 +666,14 @@
                     logger(LOG_ERR, "getsockname: %s", strerror(errno));
                     retval = ABORT;
                }
-               /* connect the socket, faster for kernel operation */
-               if (connect(data->sockfd,
-                           (struct sockaddr *)&data->client_info->client,
-                           sizeof(data->client_info->client)) == -1)
-               {
-                    logger(LOG_ERR, "connect: %s", strerror(errno));
-                    retval = ABORT;
-               }
                logger(LOG_DEBUG, "Creating new socket: %s:%d",
                       inet_ntoa(to.sin_addr), ntohs(to.sin_port));
                
+	       /* save the dest ip address to bind multicast to correct 
+		* interface
+		*/
+               data->mcastaddr.imr_interface.s_addr = to.sin_addr.s_addr;
+
                /* read options from request */
                opt_parse_request(data->data_buffer, data_size,
                                  data->tftp_options);
@@ -732,8 +765,8 @@
      tftpd_clientlist_free(data);
 
      /* free the thread structure */
-     free(data);
-     
+     free(data);    
+
      logger(LOG_INFO, "Server thread exiting");
      pthread_exit(NULL);
 }
@@ -811,6 +844,7 @@
           { "no-multicast", 0, NULL, 'M' },
           { "logfile", 1, NULL, 'L' },
           { "pidfile", 1, NULL, 'I'},
+          { "listen-local", 0, NULL, 'F'},
           { "daemon", 0, NULL, 'D' },
           { "no-fork", 0, NULL, 'N'},
           { "user", 1, NULL, 'U'},
@@ -888,6 +922,9 @@
           case 'I':
                pidfile = strdup(optarg);
                break;
+          case 'F':
+               listen_local = 1;
+               break;
           case 'D':
                tftpd_daemon = 1;
                break;
@@ -1015,6 +1052,10 @@
      logger(LOG_INFO, "  log file: %s", (log_file==NULL) ? "syslog":log_file);
      if (pidfile)
           logger(LOG_INFO, "  pid file: %s", pidfile);
+     if (listen_local == 1)
+          logger(LOG_INFO, "  forcing to listen on local interfaces: on.");
+     else
+          logger(LOG_INFO, "  not forcing to listen on local interfaces.");
      if (tftpd_daemon == 1)
           logger(LOG_INFO, "  server timeout: Not used");
      else
@@ -1085,8 +1126,7 @@
      else
      {
           /* unlink the pid file */
-          if (unlink(file) == -1)
-               logger(LOG_ERR, "unlink: %s", strerror(errno));
+          unlink(file);
           return OK;
      }
 }
@@ -1111,11 +1151,12 @@
             " output messages\n"
             "  --trace                    : log all sent and received packets\n"
             "  --no-timeout               : disable 'timeout' from RFC2349\n"
-            "  --no-tisize                : disable 'tsize' from RFC2349\n"
+            "  --no-tsize                 : disable 'tsize' from RFC2349\n"
             "  --no-blksize               : disable 'blksize' from RFC2348\n"
             "  --no-multicast             : disable 'multicast' from RFC2090\n"
             "  --logfile <file>           : logfile to log logs to ;-)\n"
             "  --pidfile <file>           : write PID to this file\n"
+            "  --listen-local             : force listen on local network address\n"
             "  --daemon                   : run atftpd standalone (no inetd)\n"
             "  --no-fork                  : run as a daemon, don't fork\n"
             "  --user <user[.group]>      : default is nobody\n"
