#include "test.h"

#ifdef TEST_LINK_CONFIGURATION

#include "linkConfiguration.h"
#include "graphics.h"
#include "graphicsGame.h"
#include "color.h"

void solveAndExamineResult(const Vector3& startP1, const Vector3& endP2, float lengthP1, float lengthP2, const Color& color)
{
   Vector3 result;
   float verifiedLengthLink1 = 0.0f;
   float verifiedLengthLink2 = 0.0f;
   LinkConfiguration::JointSolution returnResult = LinkConfiguration::getInstance().solve(startP1, endP2, lengthP1, lengthP2, result);
   if (returnResult == LinkConfiguration::JointSolution::FOUND)
   {
      verifiedLengthLink1 = (result - startP1).length();
      verifiedLengthLink2 = (endP2 - result).length();

      Graphics::getInstance().drawVector3(startP1, result, color);
      Graphics::getInstance().drawVector3(result, endP2, color);
   }
   return;
}

struct TestLinkConfigurationGame : IGraphicsGame
{
   TestLinkConfigurationGame(int width, int height)
      : IGraphicsGame(GraphicsGameProperties(width, height))
   {
   }

   TestLinkConfigurationGame(const Vector3& eye, const Vector3& center, const Vector3& up, int width, int height, float FOVAngleY, float aspectRatio, float zNear, float zFar, GraphicsGameProperties::BufferMode bufferMode)
      : IGraphicsGame(GraphicsGameProperties(eye, center, up, width, height, FOVAngleY, aspectRatio, zNear, zFar, bufferMode))
   {
   }

   void gameUpdate(int millisecondsSinceGameStart) override
   {
      Graphics::getInstance().drawAxis(13.0f, Color(0.0f, 1.0f, 0.0f));

      solveAndExamineResult(Vector3(0.0f, 0.0f, 0.0f),  Vector3(0.0f, 7.0f, 0.0f),  3.0f, 4.0f,  Color(0.0f, 1.0f, 1.0f));
      solveAndExamineResult(Vector3(1.0f, 0.0f, 0.0f),  Vector3(4.0f, 0.0f, 0.0f),  1.0f, 2.0f,  Color(0.0f, 0.0f, 1.0f));
      solveAndExamineResult(Vector3(1.0f, 0.0f, 0.0f),  Vector3(4.0f, 0.0f, 0.0f),  1.0f, 3.0f,  Color(1.0f, 1.0f, 0.0f));
      solveAndExamineResult(Vector3(1.0f, 0.0f, 0.0f),  Vector3(4.0f, 0.0f, 0.0f),  1.0f, 13.0f, Color(0.0f, 1.0f, 1.0f)); // No solution
      solveAndExamineResult(Vector3(1.0f, 0.0f, 0.0f),  Vector3(4.0f, 0.0f, 0.0f), -1.0f, 13.0f, Color(0.0f, 1.0f, 1.0f)); // No solution
      solveAndExamineResult(Vector3(10.0f, 5.0f, 7.0f), Vector3(5.0f, 15.0f, 7.0f), 5.0f, 10.0f, Color(1.0f, 0.0f, 0.0f));

      // Enable if we want to update every frame even if things don't change
      // Graphics::getInstance().update();
   }
};

void main(int argc, char* argv[])
{
   std::unique_ptr<IGraphicsGame> linkConfigurationGame = std::make_unique<TestLinkConfigurationGame>(Vector3(20.0f, 20.0f, 20.0f),
                                                                                                      Vector3(), 
                                                                                                      Vector3(0.0f, 1.0f, 0.0f), 
                                                                                                      1024, 768, 
                                                                                                      45.0f, 
                                                                                                      1.33f, 
                                                                                                      1.0f, 1000.0f, 
                                                                                                      GraphicsGameProperties::BufferMode::SINGLE);

   Graphics::GraphicsResult result = Graphics::getInstance().init(argc, argv, "Link configuration example", std::move(linkConfigurationGame));
}

#endif
