--- initmenu.c.orig	2005-11-08 05:40:38.000000000 +0900
+++ initmenu.c	2009-03-17 00:01:26.000000000 +0900
@@ -408,37 +408,34 @@
   XCharStruct overall_return ;
 
   m->xfont = XLoadQueryFont( x->display , opt->thefont ) ;
-  m->font = XLoadFont( x->display , opt->thefont ) ;
   if ( opt->verbose )
     {
       fprintf(stderr,"font=%s\n", opt->thefont) ;
     }
-  if ( m->font==BadAlloc || m->font==BadName || m->xfont==0 )
+  if ( m->xfont==0 )
     {
       fprintf(stderr,"Some problems when loading a font... trying others\n") ;
       m->xfont = XLoadQueryFont( x->display , 
-				 "-*-*-*-*-*-*-*-*-*-*-*-*-*-*" ) ;
-      m->font = XLoadFont( x->display , 
-			   "-*-*-*-*-*-*-*-*-*-*-*-*-*-*" ) ;
-      if ( m->font==BadAlloc || m->font==BadName || m->xfont==0 )
+				 "fixed" ) ;
+      if ( m->xfont==0 )
 	{
-	  fprintf(stderr,"You haven't -*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
+	  fprintf(stderr,"You haven't \"fixed\"\n");
 	  fprintf(stderr,"Have you A font?\n");
 	  fprintf(stderr,"Retry with -font option\n");
 	  exit(1) ;
 	}
     }
+  m->font = m->xfont->fid;
   m->xfont2 = XLoadQueryFont( x->display , opt->thefont2 ) ;
-  m->font2 = XLoadFont( x->display , opt->thefont2 ) ;
   if ( opt->verbose )
     {
       fprintf(stderr,"font2=%s\n", opt->thefont2) ;
     }
-  if ( m->font2==BadAlloc || m->font2==BadName || m->xfont2==0 )
+  if ( m->xfont2==0 )
     {
-      m->font2 = m->font ;
       m->xfont2 = m->xfont ;
     }
+  m->font2 = m->xfont2->fid;
 
   xgc.background = x->back_pixel ;
   xgc.foreground = opt->backcolor!=7 ? x->white_pixel : x->black_pixel;
