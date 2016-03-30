#include "debugUIHelpers.h"
#include "graphics.h"
#include "color.h"

void DebugUIHelpers::displayText(const char* text, float x, float y, TextType textType)
{
   Color color = (textType == TextType::TEXT_ERROR) ? Color(1.0f, 0.0f, 0.0f) : Color(1.0f, 1.0f, 1.0f);
   Graphics::getInstance().drawText(x, y, color, text);
}

void DebugUIHelpers::displayText(const char* text, const Color& color, float x, float y, TextType textType)
{
   Graphics::getInstance().drawText(x, y, color, text);
}

std::string DebugUIHelpers::getUIDotsFromTime(int millisecondsSinceGameStart)
{
   // Display one dot every quarter of a second, with a maximum of 3 dots
   unsigned int numberDots = (millisecondsSinceGameStart / 250) % 3;

   std::string dotsText = ".";

   for (unsigned int i = 0; i < numberDots; ++i)
   {
      dotsText += ".";
   }

   return dotsText;
}
