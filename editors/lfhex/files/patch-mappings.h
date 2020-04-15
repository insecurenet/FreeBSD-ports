--- mappings.h.orig	2008-09-19 00:36:49 UTC
+++ mappings.h
@@ -19,7 +19,7 @@
 /* automatically generated mappings from gen*To*Map.pl scripts          */
 
 namespace TranslationTables {
-  char * byteToBinaryMap[256] = {
+  const char * byteToBinaryMap[256] = {
     "00000000", "00000001", "00000010", "00000011", "00000100", "00000101", 
     "00000110", "00000111", "00001000", "00001001", "00001010", "00001011", 
     "00001100", "00001101", "00001110", "00001111", "00010000", "00010001", 
@@ -92,7 +92,7 @@ namespace TranslationTables {
     '.','.','.','.','.','.','.','.','.','.',
     '.','.','.','.','.','.',
   };
-  char * byteToHexMap[256] = {
+  const char * byteToHexMap[256] = {
     "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", 
     "0a", "0b", "0c", "0d", "0e", "0f", "10", "11", "12", "13", 
     "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", 
@@ -120,7 +120,7 @@ namespace TranslationTables {
     "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", 
     "fa", "fb", "fc", "fd", "fe", "ff", 
   };
-  char * byteToOctalMap[256] = {
+  const char * byteToOctalMap[256] = {
     "000", "001", "002", "003", "004", "005", "006", "007", "010", "011", 
     "012", "013", "014", "015", "016", "017", "020", "021", "022", "023", 
     "024", "025", "026", "027", "030", "031", "032", "033", "034", "035", 
