--- panomatic/PanoDetector.h.orig	2008-03-10 20:17:33.000000000 +0000
+++ panomatic/PanoDetector.h	2012-09-24 12:02:46.529117189 +0000
@@ -84,8 +84,8 @@
 	inline bool getLinearMatch() const { return _linearMatch; }
 	inline int  getLinearMatchLen() const { return _linearMatchLen; }
 
-	inline bool	getDownscale() const { return _downscale; }
-    inline void setDownscale(bool iDown) { _downscale = iDown; }
+	inline float	getScale() const { return _scale; }
+    inline void setScale(float iScale) { _scale = iScale; }
 
 	
 	inline void addFile(const std::string& iFile) { _files.push_back(iFile); }
@@ -126,7 +126,7 @@
 
 	bool					_test;
 	int						_cores;
-    bool                    _downscale;
+    float                    _scale;
 	
 	// list of files
 	FileNameList_t			_files;
