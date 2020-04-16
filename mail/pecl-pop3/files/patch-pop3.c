--- pop3.c.orig	2005-07-26 05:47:03.000000000 +0800
+++ pop3.c	2012-05-20 05:24:07.000000000 +0800
@@ -172,8 +172,12 @@
 
 	intern = emalloc(sizeof(pop3_object));
 	intern->zo.ce = class_type;
+#if ZEND_MODULE_API_NO >= 20050922
+	intern->zo.guards = NULL;
+#else
 	intern->zo.in_get = 0;
 	intern->zo.in_set = 0;
+#endif
 	intern->zo.properties = NULL;
 	intern->ptr = NULL;
 
@@ -200,7 +204,7 @@
  *
  * Every user visible function must have an entry in pop3_functions[].
  */
-function_entry pop3_functions[] = {
+zend_function_entry pop3_functions[] = {
 	PHP_FE(pop3_open,	NULL)
 	PHP_FE(pop3_close, NULL)
 	PHP_FE(pop3_get_message_count, NULL)
@@ -221,7 +225,7 @@
 
 /* {{{ pop3_class_functions
  */
-function_entry pop3_class_functions[] = {
+zend_function_entry pop3_class_functions[] = {
 	POP3_ME_MAPPING(pop3, pop3_open, NULL)
 	POP3_ME_MAPPING(get_message_count, pop3_get_message_count, NULL)
 	POP3_ME_MAPPING(get_account_size, pop3_get_account_size, NULL)
