--- sql/sql_view.cc.orig	2016-03-28 18:06:12 UTC
+++ sql/sql_view.cc
@@ -773,46 +773,46 @@ static const int required_view_parameter
 */
 static File_option view_parameters[]=
 {{{ C_STRING_WITH_LEN("query")},
-  my_offsetof(TABLE_LIST, select_stmt),
+  static_cast<int>(my_offsetof(TABLE_LIST, select_stmt)),
   FILE_OPTIONS_ESTRING},
  {{ C_STRING_WITH_LEN("md5")},
-  my_offsetof(TABLE_LIST, md5),
+  static_cast<int>(my_offsetof(TABLE_LIST, md5)),
   FILE_OPTIONS_STRING},
  {{ C_STRING_WITH_LEN("updatable")},
-  my_offsetof(TABLE_LIST, updatable_view),
+  static_cast<int>(my_offsetof(TABLE_LIST, updatable_view)),
   FILE_OPTIONS_ULONGLONG},
  {{ C_STRING_WITH_LEN("algorithm")},
-  my_offsetof(TABLE_LIST, algorithm),
+  static_cast<int>(my_offsetof(TABLE_LIST, algorithm)),
   FILE_OPTIONS_ULONGLONG},
  {{ C_STRING_WITH_LEN("definer_user")},
-  my_offsetof(TABLE_LIST, definer.user),
+  static_cast<int>(my_offsetof(TABLE_LIST, definer.user)),
   FILE_OPTIONS_STRING},
  {{ C_STRING_WITH_LEN("definer_host")},
-  my_offsetof(TABLE_LIST, definer.host),
+  static_cast<int>(my_offsetof(TABLE_LIST, definer.host)),
   FILE_OPTIONS_STRING},
  {{ C_STRING_WITH_LEN("suid")},
-  my_offsetof(TABLE_LIST, view_suid),
+  static_cast<int>(my_offsetof(TABLE_LIST, view_suid)),
   FILE_OPTIONS_ULONGLONG},
  {{ C_STRING_WITH_LEN("with_check_option")},
-  my_offsetof(TABLE_LIST, with_check),
+  static_cast<int>(my_offsetof(TABLE_LIST, with_check)),
   FILE_OPTIONS_ULONGLONG},
  {{ C_STRING_WITH_LEN("timestamp")},
-  my_offsetof(TABLE_LIST, timestamp),
+  static_cast<int>(my_offsetof(TABLE_LIST, timestamp)),
   FILE_OPTIONS_TIMESTAMP},
  {{ C_STRING_WITH_LEN("create-version")},
-  my_offsetof(TABLE_LIST, file_version),
+  static_cast<int>(my_offsetof(TABLE_LIST, file_version)),
   FILE_OPTIONS_ULONGLONG},
  {{ C_STRING_WITH_LEN("source")},
-  my_offsetof(TABLE_LIST, source),
+  static_cast<int>(my_offsetof(TABLE_LIST, source)),
   FILE_OPTIONS_ESTRING},
  {{(char*) STRING_WITH_LEN("client_cs_name")},
-  my_offsetof(TABLE_LIST, view_client_cs_name),
+  static_cast<int>(my_offsetof(TABLE_LIST, view_client_cs_name)),
   FILE_OPTIONS_STRING},
  {{(char*) STRING_WITH_LEN("connection_cl_name")},
-  my_offsetof(TABLE_LIST, view_connection_cl_name),
+  static_cast<int>(my_offsetof(TABLE_LIST, view_connection_cl_name)),
   FILE_OPTIONS_STRING},
  {{(char*) STRING_WITH_LEN("view_body_utf8")},
-  my_offsetof(TABLE_LIST, view_body_utf8),
+  static_cast<int>(my_offsetof(TABLE_LIST, view_body_utf8)),
   FILE_OPTIONS_ESTRING},
  {{NullS, 0},			0,
   FILE_OPTIONS_STRING}
