#include "test.h"

#ifdef TEST_GRAPHICS

#include "graphics.h"
#include "graphicsGame.h"
#include "color.h"

struct TestGraphicsGame : IGraphicsGame
{
   TestGraphicsGame(int width, int height)
      : IGraphicsGame(GraphicsGameProperties(width, height))
   {
   }

   TestGraphicsGame(const Vector3& eye, const Vector3& center, const Vector3& up, int width, int height, float FOVAngleY, float aspectRatio, float zNear, float zFar, GraphicsGameProperties::BufferMode bufferMode)
      : IGraphicsGame(GraphicsGameProperties(eye, center, up, width, height, FOVAngleY, aspectRatio, zNear, zFar, bufferMode))
   {
   }

   void update() const override
   {
      Graphics::getInstance().drawAxis(30.0f, Color(0.0f, 1.0f, 0.0f));

      // Test drawing a couple of vectors
      Graphics::getInstance().drawVector3(Vector3(7.0f, 0.0f, 0.0f), Vector3(13.0f, 27.0f, 0.0f), Color(1.0f, 1.0f, 0.0f));
      Graphics::getInstance().drawVector3(Vector3(26.0f, 0.0f, 33.0f), Vector3(13.0f, 40.0f, 33.0f), Color(0.0f, 0.0f, 1.0f));
   }
};

void main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> testGraphicsGame = std::make_unique<TestGraphicsGame>(Vector3(40.0f, 40.0f, 40.0f), Vector3(), Vector3(0.0f, 1.0f, 0.0f), 1024, 768, 45.0f, 1.33f, 1.0f, 1000.0f, GraphicsGameProperties::BufferMode::DOUBLE);
   Graphics::getInstance().init(argc, argv, "Graphics example", std::move(testGraphicsGame));
}

#endif
