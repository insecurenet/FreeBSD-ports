--- cmake/UnixBuildTarget.cmake.orig	2017-08-29 07:50:23 UTC
+++ cmake/UnixBuildTarget.cmake
@@ -80,7 +80,7 @@ install(FILES ${NOMACS_QM} DESTINATION share/nomacs/tr
 #  manpage
 install(FILES Readme/nomacs.1 DESTINATION share/man/man1)
 #  appdata
-install(FILES nomacs.appdata.xml DESTINATION /usr/share/appdata/)
+install(FILES nomacs.appdata.xml DESTINATION share/appdata/)
 
 # "make dist" target
 string(TOLOWER ${PROJECT_NAME} CPACK_PACKAGE_NAME)
