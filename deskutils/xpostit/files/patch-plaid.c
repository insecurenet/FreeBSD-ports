--- plaid.c.orig	Thu Dec 10 17:40:26 1992
+++ plaid.c	Mon May  6 13:23:17 1996
@@ -60,6 +60,7 @@
 {
 	Arg args[4];
 	register int nargs;
+	Dimension width, height;
 
 	/*
 	 * Create the plaid widget.
@@ -78,20 +79,22 @@
 	 * Get the width and height of the widget.
 	 */
 	nargs = 0;
-	SetArg(XtNwidth, NULL);
-	SetArg(XtNheight, NULL);
+	SetArg(XtNwidth, &width);
+	SetArg(XtNheight, &height);
 	XtGetValues(plaidwidget, args, nargs);
 
 	/*
 	 * If the user didn't set them, then we
 	 * should set them to the defaults.
 	 */
-	if ((args[0].value == 0) || (args[1].value == 0)) {
-		if (args[0].value == 0)
-			XtSetArg(args[0], XtNwidth, DefaultPlaidWidth);
+	if (width == 0 || height == 0) {
+		nargs = 0;
 
-		if (args[1].value == 0)
-			XtSetArg(args[1], XtNheight, DefaultPlaidHeight);
+		if (width == 0)
+			SetArg(XtNwidth, DefaultPlaidWidth);
+
+		if (height == 0)
+			SetArg(XtNheight, DefaultPlaidHeight);
 
 		XtSetValues(plaidwidget, args, nargs);
 	}
