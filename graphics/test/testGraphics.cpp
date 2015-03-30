#include "test.h"

#ifdef TEST_GRAPHICS

#include "graphics.h"
#include "vector3.h"

static void myGame()
{
   Graphics::GetInstance().drawAxis(50.0f, Color(0.0f, 1.0f, 0.0f));
}

void main(int argc, char* argv[])
{
   Graphics::GetInstance().init(argc, argv, "Graphics example");

   // TODO: We will be passing to Graphics a reference to a class which will handle our game loop render logic
}

#endif
