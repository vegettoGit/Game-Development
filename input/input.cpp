#include "input.h"

bool Input::m_availableKey = false;
unsigned char Input::m_key = '0';

Input::Input()
{
}

Input::~Input()
{
}

Input& Input::getInstance()
{
   static Input s_instance;
   return s_instance;
}

void Input::onKeyPressed(unsigned char charASCII, int mouseX, int mouseY)
{
   m_availableKey = true;
   m_key          = charASCII;
}

bool Input::extractKey(unsigned char& charASCII)
{
   bool result = false;

   if (m_availableKey)
   {
      result = true;
      m_availableKey = false;
      charASCII = m_key;
   }

   return result;
}