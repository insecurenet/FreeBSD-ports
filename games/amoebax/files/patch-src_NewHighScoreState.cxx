--- src/NewHighScoreState.cxx.orig	2007-07-29 16:48:20 UTC
+++ src/NewHighScoreState.cxx
@@ -396,7 +396,7 @@ NewHighScoreState::unicodeCharacterPress
     // FIXME: We are only interessted with ASCII values.
     if ( 0 == (code & 0xff80) )
     {
-        char character[2] = {toupper (static_cast<char>(code & 0x7f)), '\0'};
+        char character[2] = {static_cast<char>(toupper (static_cast<char>(code & 0x7f)), '\0')};
         std::string::size_type characterPos =
             m_CursorValues.find (std::string (character));
         if ( std::string::npos != characterPos )
