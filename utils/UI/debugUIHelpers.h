#ifndef DEBUG_UI_HELPERS
#define DEBUG_UI_HELPERS

#include <string>

struct Color;

struct DebugUIHelpers
{
   enum class TextType
   {
      NORMAL,
      TEXT_ERROR
   };

   static void displayText(const char* text, float x, float y, TextType textType = TextType::NORMAL);
   static void displayText(const char* text, const Color& color, float x, float y, TextType textType = TextType::NORMAL);
   static std::string getUIDotsFromTime(int millisecondsSinceGameStart);
};

#endif


