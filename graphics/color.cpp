#include "color.h"
#include <utility>

Color::Color()
   : m_red(0.0f),
     m_green(0.0f),
     m_blue(0.0f)
{
}

Color::Color(float red, float green, float blue)
   : m_red(red),
     m_green(green),
     m_blue(blue)
{
}

Color::Color(const Color& color)
{
   *this = color;
}

Color& Color::operator = (const Color& color)
{
   m_red   = color.m_red;
   m_green = color.m_green;
   m_blue  = color.m_blue;

   return *this;
}

Color::Color(Color&& color)
{
   *this = std::move(color);
}

Color& Color::operator = (Color&& color)
{
   m_red   = color.m_red;
   m_green = color.m_green;
   m_blue  = color.m_blue;

   color.m_red   = 0.0f;
   color.m_green = 0.0f;
   color.m_blue  = 0.0f;
    
   return *this;
}

Color::~Color()
{
}

