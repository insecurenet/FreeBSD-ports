--- code/qcommon/vm_x86_64.c.orig	2008-05-10 10:05:55.000000000 -0300
+++ code/qcommon/vm_x86_64.c	2010-10-10 20:41:15.000000000 -0300
@@ -246,7 +246,7 @@
 #else
 #define JMPIARG \
 	emit("movq $%lu, %%rax", vm->codeBase+vm->instructionPointers[iarg]); \
-	emit("jmpq *%rax");
+	emit("jmpq *%%rax");
 #endif
  
 // integer compare and jump
@@ -534,7 +534,7 @@
 	{
 		compiledOfs = assembler_get_code_size();
 		vm->codeLength = compiledOfs;
-		vm->codeBase = mmap(NULL, compiledOfs, PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
+		vm->codeBase = mmap(NULL, compiledOfs, PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
 		if(vm->codeBase == (void*)-1)
 			Com_Error(ERR_DROP, "VM_CompileX86: can't mmap memory");
 
