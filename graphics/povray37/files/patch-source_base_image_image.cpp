--- source/base/image/image.cpp.orig	2012-06-19 02:57:32.000000000 +0200
+++ source/base/image/image.cpp	2012-09-22 23:19:44.000000000 +0200
@@ -2884,7 +2884,7 @@
 			meta[0] = sizeof(pixel_type);
 			meta[1] = m_Width;
 			meta[2] = m_Height;
-			if (lseek64(m_File, pos, SEEK_SET) != pos)
+			if (lseek(m_File, pos, SEEK_SET) != pos)
 				throw POV_EXCEPTION(kFileDataErr, "Intermediate image storage backing file write/seek failed at creation.");
 			if (write(m_File, &meta[0], (int) sizeof(size_type)*3) != (sizeof(size_type)*3))
 				throw POV_EXCEPTION(kFileDataErr, "Intermediate image storage backing file write failed at creation.");
@@ -3055,7 +3055,7 @@
 #endif
 				pos = block * sizeof(pixel_type) * m_Blocksize;
 				int chunk = sizeof(pixel_type) * m_Blocksize;
-				if (lseek64(m_File, pos, SEEK_SET) != pos)
+				if (lseek(m_File, pos, SEEK_SET) != pos)
 					throw POV_EXCEPTION(kFileDataErr, "Intermediate image storage backing file read/seek failed.");
 				int bytes = read(m_File, &m_Buffer[0], chunk);
 				if (bytes != (sizeof(pixel_type) * m_Blocksize))
@@ -3078,7 +3078,7 @@
 
 			if (m_Dirty) {
 				pos = m_CurrentBlock * sizeof(pixel_type) * m_Blocksize;
-				if (lseek64(m_File, pos, SEEK_SET) != pos)
+				if (lseek(m_File, pos, SEEK_SET) != pos)
 					throw POV_EXCEPTION(kFileDataErr, "Intermediate image storage backing file write/seek failed.");
 				if (write(m_File, &m_Buffer[0], (int) sizeof(pixel_type) * m_Blocksize) != (sizeof(pixel_type) * m_Blocksize))
 					throw POV_EXCEPTION(kFileDataErr, "Intermediate image storage backing file write failed.");
