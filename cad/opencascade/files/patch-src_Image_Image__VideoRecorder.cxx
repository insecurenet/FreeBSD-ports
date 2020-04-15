src/Image/Image_VideoRecorder.cxx:279:25: error: use of undeclared identifier 'CODEC_FLAG_GLOBAL_HEADER'
    aCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
                        ^
src/Image/Image_VideoRecorder.cxx:452:38: error: use of undeclared identifier 'AVFMT_RAWPICTURE'
  if ((myAVContext->oformat->flags & AVFMT_RAWPICTURE) != 0
                                     ^

--- src/Image/Image_VideoRecorder.cxx.orig	2017-08-30 13:28:21 UTC
+++ src/Image/Image_VideoRecorder.cxx
@@ -276,7 +276,7 @@ Standard_Boolean Image_VideoRecorder::addVideoStream (
   // some formats want stream headers to be separate
   if (myAVContext->oformat->flags & AVFMT_GLOBALHEADER)
   {
-    aCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
+    aCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
   }
   return Standard_True;
 #else
@@ -449,6 +449,7 @@ Standard_Boolean Image_VideoRecorder::writeVideoFrame 
   AVPacket aPacket;
   memset (&aPacket, 0, sizeof(aPacket));
   av_init_packet (&aPacket);
+#ifdef AVFMT_RAWPICTURE
   if ((myAVContext->oformat->flags & AVFMT_RAWPICTURE) != 0
    && !theToFlush)
   {
@@ -461,6 +462,7 @@ Standard_Boolean Image_VideoRecorder::writeVideoFrame 
     aResAv = av_interleaved_write_frame (myAVContext, &aPacket);
   }
   else
+#endif
   {
     // encode the image
     myFrame->pts = myFrameCount;
