--- lineakd/lineakd_core_functions.cpp.orig	Fri May 26 14:49:04 2006
+++ lineakd/lineakd_core_functions.cpp	Fri May 26 14:51:07 2006
@@ -261,7 +261,7 @@
   	sigprocmask(SIG_SETMASK, &mask_set, &old_set);
 
    	/* now do some cleaning... */
-  	msg("Cleaning up xkb mappings");
+  	lineak_core_functions::msg("Cleaning up xkb mappings");
    	/* Clean up X */
         if (X != 0) {
   		X->cleanup(myKbd);
@@ -275,12 +275,12 @@
         if (!plugincleanup) {
            plugincleanup = true;
            if ( plugins != NULL) {
-              msg("Unloading All Plugins!");
+              lineak_core_functions::msg("Unloading All Plugins!");
               plugins->unloadAllPlugins();
-              msg("Unloading All Plugins DONE!");
+              lineak_core_functions::msg("Unloading All Plugins DONE!");
               delete(plugins);
               plugins = NULL;
-              msg("Plugins all taken care of!");
+              lineak_core_functions::msg("Plugins all taken care of!");
            }
         }
 
@@ -288,13 +288,13 @@
   	//sigprocmask(SIG_SETMASK, &old_set, NULL);
 
         /* Remove the message queue */
-  	msg("Removing message queue");
+  	lineak_core_functions::msg("Removing message queue");
 	msgPasser myMsg;
 	if (!myMsg.start()) error("do_exit(): Cannot establish message queue to shutdown the queue.!");
         myMsg.quit();
 
         /** Remove the lock */
-        msg("Removing lock");
+        lineak_core_functions::msg("Removing lock");
         lockCtrl lock("lineakd");
         lock.unlock();
 //      exit(true);
@@ -326,16 +326,16 @@
   		sigprocmask(SIG_SETMASK, &mask_set, &old_set);
    		//bool verbose = cmdprefs.getVerbose();
 
-   		msg("Recieved a message to load a new configuration");
-                msg("Unmapping keys");
+   		lineak_core_functions::msg("Recieved a message to load a new configuration");
+                lineak_core_functions::msg("Unmapping keys");
                 X->cleanup(myKbd);
 
-                msg("Unloading all plugins");
+                lineak_core_functions::msg("Unloading all plugins");
                 plugins->unloadAllPlugins();
 
                 /** Get a list of the potential plugins in the plugin directory */
                 vector<string> pluginlist = plugins->scanForPlugins();
-                msg("Scaning for and loading plugins");
+                lineak_core_functions::msg("Scaning for and loading plugins");
                 /** Load the plugins */
                 plugins->loadPlugins(pluginlist);
                 /** Define the list of macros we support */
@@ -375,37 +375,37 @@
                 cmdprefs.setDefaults(dnd);
 
   		/* reload .conf and .def file */
-  		msg("*** reloading config file " + myConfig.getFilename());
+  		lineak_core_functions::msg("*** reloading config file " + myConfig.getFilename());
                 cout << "Config file to load is: " << myConfig.getFilename() << endl;
                 ConfigLoader ldr(myConfig.getFilename(),dnd);
 		myConfig.clear();
                 myConfig = ldr.loadConfig();
                 myConfig.print(cout);
   		//parseConfigs(dnd, myConfig);
-		msg("*** setting config file options " + myConfig.getFilename());
+		lineak_core_functions::msg("*** setting config file options " + myConfig.getFilename());
                 cmdprefs.setOpts(myConfig);
-  		msg("*** reloading definition file " + myDef.getFilename());
+  		lineak_core_functions::msg("*** reloading definition file " + myDef.getFilename());
   		parseDefinitions(cmdprefs, myDef);
 
   		/* re-init the EAKeyboard */
-  		msg("*** re-initializing the keyboard");
+  		lineak_core_functions::msg("*** re-initializing the keyboard");
     	        myKbd = myDef.getKeyboard(myConfig[_CD_KEYBOARD_TYPE]);
 		/** Update our keyboard with our configured commands */
 		myKbd.setCommands(myConfig);
 
   		/* re-init X/Xkb with our EAK keycodes/keysyms */
-  		msg("*** reconfiguring Xkb keymap with new keys and buttons");
+  		lineak_core_functions::msg("*** reconfiguring Xkb keymap with new keys and buttons");
 		X->initialize(myKbd);
 
   		/* .. restore the old signal mask .. */
-  		msg("*** rehash done");
+  		lineak_core_functions::msg("*** rehash done");
   		sigprocmask(SIG_SETMASK, &old_set, NULL);
 		plugins->initializePlugins(myKbd, myConfig,plugins);
 
-  		msg("*** Restarting On Screen Display...");
+  		lineak_core_functions::msg("*** Restarting On Screen Display...");
 		myDisplay = plugins->getDisplay(myConfig);
   		//myDisplay->init(myConfig);
-		msg("*** InitializePluginsDisplay...");
+		lineak_core_functions::msg("*** InitializePluginsDisplay...");
                 plugins->initializePluginsDisplay(*myDisplay);
 
     	donehup=false;
