#include "input.h"

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
}