#include "test.h"

#ifdef TEST_GRAPHICS

#include "graphics.h"
#include "vector3.h"

void main(int argc, char* argv[])
{
   Graphics::GetInstance().init(argc, argv);

   return;
}

#endif
