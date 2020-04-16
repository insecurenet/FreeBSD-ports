--- src/tools/enumpoly/pelqhull.cc.orig	2014-05-27 12:07:04.000000000 +0400
+++ src/tools/enumpoly/pelqhull.cc	2015-04-13 20:35:03.596285000 +0300
@@ -2792,7 +2792,7 @@
   
    /* zdef_(type,name,doc,average) */
   zzdef_(zdoc, Zdoc2, "precision statistics", -1);
-  zdef_(zinc, Znewvertex, reinterpret_cast<const char *>(NULL), -1);
+  zdef_(zinc, Znewvertex, static_cast<const char *>(NULL), -1);
   zdef_(wadd, Wnewvertex, "ave. distance of a new vertex to a facet (not 0s)", Znewvertex);
   zdef_(wmax, Wnewvertexmax, "max. distance of a new vertex to a facet", -1);
   zdef_(wmax, Wvertexmax, "max. distance of an output vertex to a facet", -1);
@@ -2831,7 +2831,7 @@
   zzdef_(zinc, Zsetplane, "facets created altogether", -1);
   zdef_(zinc, Ztotridges, "ridges created altogether", -1);
   zdef_(zinc, Zpostfacets, "facets before post merge", -1);
-  zdef_(zinc, Zangle, reinterpret_cast<const char *>(NULL), -1);
+  zdef_(zinc, Zangle, static_cast<const char *>(NULL), -1);
   zdef_(wadd, Wangle, "average angle (cosine) for all ridges", Zangle);
   zdef_(wmax, Wanglemax, "maximum angle (cosine) of a ridge", -1);
   zdef_(wmin, Wanglemin, "minimum angle (cosine) of a ridge", -1);
@@ -2946,7 +2946,7 @@
   zdef_(zinc, Zintersect, "intersections found redundant vertices", -1);
   zdef_(zadd, Zintersecttot, "   ave. number found per vertex", Zintersect);
   zdef_(zmax, Zintersectmax, "   max. found for a vertex", -1);
-  zdef_(zinc, Zvertexridge, reinterpret_cast<const char *>(NULL), -1);
+  zdef_(zinc, Zvertexridge, static_cast<const char *>(NULL), -1);
   zdef_(zadd, Zvertexridgetot, "  ave. number of ridges per tested vertex", Zvertexridge);
   zdef_(zmax, Zvertexridgemax, "  max. number of ridges per tested vertex", -1);
 
