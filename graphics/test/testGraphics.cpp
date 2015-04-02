#include "test.h"

#ifdef TEST_GRAPHICS

#include "graphics.h"
#include "graphicsGame.h"
#include "vector3.h"

struct TestGraphicsGame : IGraphicsGame
{
   TestGraphicsGame(int width, int height)
   {
      m_properties.m_windowWidth  = width;
      m_properties.m_windowHeight = height;
   }

   TestGraphicsGame(int width, int height, float FOVAngleY, float aspectRatio, float zNear, float zFar)
   {
      m_properties.m_windowWidth = width;
      m_properties.m_windowHeight = height;
      m_properties.m_fieldOfViewAngle = FOVAngleY;
      m_properties.m_aspectRatio = aspectRatio;
      m_properties.m_nearClippingPlane = zNear;
      m_properties.m_farClippingPlane = zFar;
   }

   void render() const override
   {
      Graphics::getInstance().drawAxis(52.0f, Color(0.0f, 1.0f, 0.0f));
      Graphics::getInstance().drawVector3(Vector3(7.0f, 0.0f, 0.0f), Vector3(13.0f, 27.0f, 0.0f), Color(1.0f, 1.0f, 0.0f));
      Graphics::getInstance().drawVector3(Vector3(26.0f, 0.0f, 33.0f), Vector3(13.0f, 40.0f, 33.0f), Color(0.0f, 0.0f, 1.0f));

      // Test drawing a couple of vectors
   }
};

void main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> testGraphicsGame = std::make_unique<TestGraphicsGame>(1024, 768, 1.0f, 1.33f, 1.0f, 10000.0f);
   Graphics::getInstance().init(argc, argv, "Graphics example", std::move(testGraphicsGame));
}

#endif
