--- src/main.c.orig
+++ src/main.c
@@ -341,6 +341,24 @@
 }
 
 
+/*--Rafraichir l'�cran (� chaque frame), suivant le mode--*/
+void rafraichit(void)
+ {
+  if (dblebuf) {
+    SDL_Flip(ecran);
+    nrsrect=0;
+    nrs=!nrs;
+  }
+  else {
+    SDL_UpdateRects(ecran, nrsrect, rsrect);
+    nrsrect=0;
+    nrs=0;
+  }
+
+  return;
+}
+
+
 /*--Affiche des informations, pose une question--*/
 void dialogue(char * texte, int estunequestion)
 {
@@ -1176,24 +1194,6 @@
 }
 
 
-/*--Rafraichir l'�cran (� chaque frame), suivant le mode--*/
-int rafraichit(void)
-{
-  if (dblebuf) {
-    SDL_Flip(ecran);
-    nrsrect=0;
-    nrs=!nrs;
-  }
-  else {
-    SDL_UpdateRects(ecran, nrsrect, rsrect);
-    nrsrect=0;
-    nrs=0;
-  }
-
-  return;
-}
-
-
 /*--Dessine la jauge d'�nergie du joueur n � droite de l'�cran--*/
 void jauge(int n)
 {
