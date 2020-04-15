--- qsstv/config/directoriesconfig.cpp.orig	2017-11-16 17:14:48 UTC
+++ qsstv/config/directoriesconfig.cpp
@@ -43,7 +43,11 @@ void directoriesConfig::readSettings()
   txStockImagesPath=qSettings.value("txStockImagesPath",QString(getenv("HOME"))+"/tx_stock/").toString();
   templatesPath=qSettings.value("templatesPath",QString(getenv("HOME"))+"/templates/").toString();
   audioPath=qSettings.value("audioPath",QString(getenv("HOME"))+"/audio/").toString();
+#ifdef WITH_DOCS
+  docURL=qSettings.value("docURL","file:///usr/local/share/doc/qsstv/manual").toString();
+#else
   docURL=qSettings.value("docURL","http://users.telenet.be/on4qz/qsstv/manual").toString();
+#endif
   saveTXimages=qSettings.value("saveTXimages",false).toBool();
   qSettings.endGroup();
   setParams();
