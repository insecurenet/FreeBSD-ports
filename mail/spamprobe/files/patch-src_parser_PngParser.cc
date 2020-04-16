--- src/parser/PngParser.cc.orig	2006-11-17 08:11:10.000000000 +0100
+++ src/parser/PngParser.cc	2010-03-29 17:15:51.000000000 +0200
@@ -53,9 +53,9 @@
 {
   if (m_initialized) {
     if (m_infoPtr) {
-      png_destroy_read_struct(&m_pngPtr, &m_infoPtr, png_infopp_NULL);
+      png_destroy_read_struct(&m_pngPtr, &m_infoPtr, NULL);
     } else {
-      png_destroy_read_struct(&m_pngPtr, png_infopp_NULL, png_infopp_NULL);
+      png_destroy_read_struct(&m_pngPtr, NULL, NULL);
     }
   }
 }
@@ -104,7 +104,7 @@
   int bit_depth, color_type, interlace_type;
 
   png_get_IHDR(m_pngPtr, m_infoPtr, &width, &height, &bit_depth, &color_type,
-               &interlace_type, int_p_NULL, int_p_NULL);
+               &interlace_type, NULL, NULL);
 
   string base_token("image_0");
   sendToken(base_token + "_height_" + num_to_string((int)width));
