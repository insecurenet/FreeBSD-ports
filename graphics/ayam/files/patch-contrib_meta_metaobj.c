--- contrib/meta/metaobj.c.orig	2016-01-13 20:09:57 UTC
+++ contrib/meta/metaobj.c
@@ -859,7 +859,7 @@ metaobj_notifycb (ay_object *o)
  meta_world *w;
  meta_blob *b;
  ay_object *down;
- char *adapt;
+ const char *adapt;
  char vname[] = "ay";
  char vname1[] = "action";
  double euler[3] = {0};
