--- configure.h.orig	Fri Dec 18 21:55:05 1998
+++ configure.h	Thu Feb 25 10:31:24 1999
@@ -11,10 +11,10 @@
  */
 
 /* ���󥹥ȡ���ǥ��쥯�ȥ� */
-#define INSTALLDIR ${HOME}/bin
+#define INSTALLDIR ${PREFIX}/bin
 
 /* �ǥե���ȥǡ����򥤥󥹥ȡ��뤹���� */
-#define DATADIR ${HOME}/share/mindfocus
+#define DATADIR ${PREFIX}/share/examples/mindfocus
 
 /* �ĿʹĶ���¸�ե�����(����ե�����)��̾�� */
 #define DOTFILENAME ".mindfocus"
@@ -32,7 +32,7 @@
 
 /* XPM�ե����ޥåȤ��б�������Ȥ���������롣���ΤȤ�����¾�ɬ�ܡ� */
 #define XPM
-#define XPMLIBRARY -L/usr/local/X11R6/lib -lXpm
+#define XPMLIBRARY -L${PREFIX}/lib -lXpm
 
 
 /*
