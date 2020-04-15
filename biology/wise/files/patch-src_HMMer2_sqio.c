--- src/HMMer2/sqio.c.orig	2001-06-18 13:59:51 UTC
+++ src/HMMer2/sqio.c
@@ -213,7 +213,7 @@ readline(FILE *f, char *s)
     }
 }
 
-/* Function: getline()
+/* Function: get_line()
  * Date:     SRE, Tue Mar  3 08:30:01 1998 [St. Louis]
  *
  * Purpose:  read a line from a sequence file into V->sbuffer.
@@ -229,7 +229,7 @@ readline(FILE *f, char *s)
  * Returns:  (void)
  */
 static void 
-getline(struct ReadSeqVars *V)
+get_line(struct ReadSeqVars *V)
 {
   char *cp;
   
@@ -299,7 +299,7 @@ readLoop(int addfirst, int (*endTest)(ch
   V->seqlen = 0;
   if (addfirst) addseq(V->sbuffer, V);
   do {
-    getline(V);
+    get_line(V);
 	/* feof() alone is a bug; files not necessarily \n terminated */
     if (*(V->sbuffer) == '\0' && feof(V->f))
       done = TRUE;
@@ -327,7 +327,7 @@ readPIR(struct ReadSeqVars *V)
   char *sptr;
 				/* load first line of entry  */
   while (!feof(V->f) && strncmp(V->sbuffer, "ENTRY", 5) != 0)
-    getline(V);
+    get_line(V);
   if (feof(V->f)) return;
 
   if ((sptr = strtok(V->sbuffer + 15, "\n\t ")) != NULL)
@@ -336,7 +336,7 @@ readPIR(struct ReadSeqVars *V)
       SetSeqinfoString(V->sqinfo, sptr, SQINFO_ID);
     }
   do {
-    getline(V);
+    get_line(V);
     if (!feof(V->f) && strncmp(V->sbuffer, "TITLE", 5) == 0)
       SetSeqinfoString(V->sqinfo, V->sbuffer+15, SQINFO_DESC);
     else if (!feof(V->f) && strncmp(V->sbuffer, "ACCESSION", 9) == 0)
@@ -345,7 +345,7 @@ readPIR(struct ReadSeqVars *V)
 	  SetSeqinfoString(V->sqinfo, sptr, SQINFO_ACC);
       }
   } while (! feof(V->f) && (strncmp(V->sbuffer,"SEQUENCE", 8) != 0));
-  getline(V);			/* skip next line, coords */
+  get_line(V);			/* skip next line, coords */
 
   readLoop(0, endPIR, V);
 
@@ -359,7 +359,7 @@ readPIR(struct ReadSeqVars *V)
   /* get next line
    */
   while (!feof(V->f) && strncmp(V->sbuffer, "ENTRY", 5) != 0)
-    getline(V);
+    get_line(V);
 }
 
 
@@ -377,7 +377,7 @@ readIG(struct ReadSeqVars *V)
   char *nm;
 				/* position past ';' comments */
   do {
-    getline(V);
+    get_line(V);
   } while (! (feof(V->f) || ((*V->sbuffer != 0) && (*V->sbuffer != ';')) ));
 
   if (!feof(V->f))
@@ -389,7 +389,7 @@ readIG(struct ReadSeqVars *V)
     }
   
   while (!(feof(V->f) || ((*V->sbuffer != '\0') && (*V->sbuffer == ';'))))
-    getline(V);
+    get_line(V);
 }
 
 static int 
@@ -411,7 +411,7 @@ readStrider(struct ReadSeqVars *V)
 	  if ((nm = strtok(V->sbuffer+16, ",\n\t ")) != NULL)
 	    SetSeqinfoString(V->sqinfo, nm, SQINFO_NAME);
 	}
-      getline(V);
+      get_line(V);
     }
 
   if (! feof(V->f))
@@ -420,7 +420,7 @@ readStrider(struct ReadSeqVars *V)
   /* load next line
    */
   while ((!feof(V->f)) && (*V->sbuffer != ';')) 
-    getline(V);
+    get_line(V);
 }
 
 
@@ -438,7 +438,7 @@ readGenBank(struct ReadSeqVars *V)
   int   in_definition;
 
   while (strncmp(V->sbuffer, "LOCUS", 5) != 0)
-    getline(V);
+    get_line(V);
 
   if ((sptr = strtok(V->sbuffer+12, "\n\t ")) != NULL)
     {
@@ -449,7 +449,7 @@ readGenBank(struct ReadSeqVars *V)
   in_definition = FALSE;
   while (! feof(V->f))
     {
-      getline(V);
+      get_line(V);
       if (! feof(V->f) && strstr(V->sbuffer, "DEFINITION") == V->sbuffer)
 	{
 	  if ((sptr = strtok(V->sbuffer+12, "\n")) != NULL)
@@ -482,11 +482,11 @@ readGenBank(struct ReadSeqVars *V)
 
 
   while (!(feof(V->f) || ((*V->sbuffer!=0) && (strstr(V->sbuffer,"LOCUS") == V->sbuffer))))
-    getline(V);
+    get_line(V);
 				/* SRE: V->s now holds "//", so sequential
 				   reads are wedged: fixed Tue Jul 13 1993 */
   while (!feof(V->f) && strstr(V->sbuffer, "LOCUS  ") != V->sbuffer)
-    getline(V);
+    get_line(V);
 }
 
 static int
@@ -515,7 +515,7 @@ readGCGdata(struct ReadSeqVars *V)
     Die("bogus GCGdata format? %s", V->sbuffer);
 
 				/* second line contains free text description */
-  getline(V);
+  get_line(V);
   SetSeqinfoString(V->sqinfo, V->sbuffer, SQINFO_DESC);
 
   if (binary) {
@@ -535,7 +535,7 @@ readGCGdata(struct ReadSeqVars *V)
   else readLoop(0, endGCGdata, V);
   
   while (!(feof(V->f) || ((*V->sbuffer != 0) && (*V->sbuffer == '>'))))
-    getline(V);
+    get_line(V);
 }
 
 static int
@@ -555,12 +555,12 @@ readPearson(struct ReadSeqVars *V)
   if ((sptr = strtok(NULL, "\n")) != NULL)
     SetSeqinfoString(V->sqinfo, sptr, SQINFO_DESC);
 				/* workaround for long NCBI NR lines */
-  while (V->longline && ! feof(V->f)) getline(V);
+  while (V->longline && ! feof(V->f)) get_line(V);
 
   readLoop(0, endPearson, V);
 
   while (!(feof(V->f) || ((*V->sbuffer != 0) && (*V->sbuffer == '>'))))
-    getline(V);
+    get_line(V);
 }
 
 
@@ -587,7 +587,7 @@ readEMBL(struct ReadSeqVars *V)
 
 				/* make sure we have first line */
   while (!feof(V->f) && strncmp(V->sbuffer, "ID  ", 4) != 0)
-    getline(V);
+    get_line(V);
 
   if ((sptr = strtok(V->sbuffer+5, "\n\t ")) != NULL)
     {
@@ -596,7 +596,7 @@ readEMBL(struct ReadSeqVars *V)
     }
 
   do {
-    getline(V);
+    get_line(V);
     if (!feof(V->f) && strstr(V->sbuffer, "AC  ") == V->sbuffer)
       {
 	if ((sptr = strtok(V->sbuffer+5, ";  \t\n")) != NULL)
@@ -620,7 +620,7 @@ readEMBL(struct ReadSeqVars *V)
 
 				/* load next record's ID line */
   while (!feof(V->f) && strncmp(V->sbuffer, "ID  ", 4) != 0)
-    getline(V);
+    get_line(V);
 }
 
 
@@ -636,7 +636,7 @@ readZuker(struct ReadSeqVars *V)
 {
   char *sptr;
 
-  getline(V);  /*s == "seqLen seqid string..."*/
+  get_line(V);  /*s == "seqLen seqid string..."*/
 
   if ((sptr = strtok(V->sbuffer+6, " \t\n")) != NULL)
     SetSeqinfoString(V->sqinfo, sptr, SQINFO_NAME);
@@ -647,7 +647,7 @@ readZuker(struct ReadSeqVars *V)
   readLoop(0, endZuker, V);
 
   while (!(feof(V->f) | ((*V->sbuffer != '\0') & (*V->sbuffer == '('))))
-    getline(V);
+    get_line(V);
 }
 
 static void 
@@ -669,7 +669,7 @@ readUWGCG(struct ReadSeqVars *V)
 
   do {
     done = feof(V->f);
-    getline(V);
+    get_line(V);
     if (! done) addseq(V->sbuffer, V);
   } while (!done);
 }
@@ -681,7 +681,7 @@ readSquid(struct ReadSeqVars *V)
   char *sptr;
   int   dostruc = FALSE;
 
-  while (strncmp(V->sbuffer, "NAM ", 4) != 0) getline(V);
+  while (strncmp(V->sbuffer, "NAM ", 4) != 0) get_line(V);
 
   if ((sptr = strtok(V->sbuffer+4, "\n\t ")) != NULL)
     SetSeqinfoString(V->sqinfo, sptr, SQINFO_NAME);
@@ -689,7 +689,7 @@ readSquid(struct ReadSeqVars *V)
   /*CONSTCOND*/
   while (1)
     {
-      getline(V);
+      get_line(V);
       if (feof(V->f)) {squid_errno = SQERR_FORMAT; return; }
 
       if (strncmp(V->sbuffer, "SRC ", 4) == 0)
@@ -721,14 +721,14 @@ readSquid(struct ReadSeqVars *V)
   while (1)
     {
 				/* sequence line */
-      getline(V);
+      get_line(V);
       if (feof(V->f) || strncmp(V->sbuffer, "++", 2) == 0) 
 	break;
       addseq(V->sbuffer, V);
 				/* structure line */
       if (dostruc)
 	{
-	  getline(V);
+	  get_line(V);
 	  if (feof(V->f)) { squid_errno = SQERR_FORMAT; return; }
 	  addstruc(V->sbuffer, V);
 	}
@@ -736,7 +736,7 @@ readSquid(struct ReadSeqVars *V)
 
 
   while (!feof(V->f) && strncmp(V->sbuffer, "NAM ", 4) != 0)
-    getline(V);
+    get_line(V);
 }
 
 
@@ -816,7 +816,7 @@ SeqfileOpen(char *filename, int format, 
 
   /* Load the first line.
    */
-  getline(dbfp);
+  get_line(dbfp);
 
   return dbfp;
 }
@@ -833,7 +833,7 @@ SeqfilePosition(SQFILE *sqfp, long offse
     Die("SeqfilePosition() failed: in a nonrewindable data file or stream");
 
   fseek(sqfp->f, offset, SEEK_SET);
-  getline(sqfp);
+  get_line(sqfp);
 }
 
 
@@ -853,7 +853,7 @@ SeqfileRewind(SQFILE *sqfp)
   if (sqfp->ali_aseqs != NULL) sqfp->ali_curridx = 0;
   else {
     rewind(sqfp->f);
-    getline(sqfp);
+    get_line(sqfp);
   }
 }
 
@@ -949,7 +949,7 @@ ReadSeq(SQFILE *V, int format, char **re
       do {			/* skip leading comments on GCG file */
 	gotuw = (strstr(V->sbuffer,"..") != NULL);
 	if (gotuw) readUWGCG(V);
-	getline(V);
+	get_line(V);
       } while (! feof(V->f));
       break;
 
