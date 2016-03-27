#ifndef DEBUG_UI_HELPERS
#define DEBUG_UI_HELPERS

#include <string>

struct DebugUIHelpers
{
   enum class TextType
   {
      NONE,
      TEXT_ERROR
   };

   static void displayText(const char* text, TextType textType = TextType::NONE);
   static std::string getUIDotsFromTime(int millisecondsSinceGameStart);
};

#endif


