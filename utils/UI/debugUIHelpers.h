#ifndef DEBUG_UI_HELPERS
#define DEBUG_UI_HELPERS

#include <string>

struct Color;

struct DebugUIHelpers
{
   enum class TextType
   {
      NONE,
      TEXT_ERROR
   };

   static void displayText(const char* text, float x, float y, TextType textType = TextType::NONE);
   static void displayText(const char* text, const Color& color, float x, float y, TextType textType = TextType::NONE);
   static std::string getUIDotsFromTime(int millisecondsSinceGameStart);
};

#endif


