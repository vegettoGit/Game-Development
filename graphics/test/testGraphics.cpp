#include "test.h"
#include <memory>
#include <utility>

#ifdef TEST_GRAPHICS

#include "graphics.h"
#include "graphicsGame.h"
#include "vector3.h"

struct TestGraphicsGame : IGraphicsGame
{
   void render() const override
   {
      Graphics::getInstance().drawAxis(50.0f, Color(0.0f, 1.0f, 0.0f));
   }
};

void main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> testGraphicsGame = std::make_unique<TestGraphicsGame>();

   Graphics::getInstance().init(argc, argv, "Graphics example", std::move(testGraphicsGame));
}

#endif
