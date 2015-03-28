#include "test.h"

#ifdef TEST_LINK_CONFIGURATION

#include "linkConfiguration.h"
#include "Vector3.h"

void solveAndExamineResult(const Vector3& startP1, const Vector3& endP2, float lengthP1, float lengthP2)
{
   Vector3 result;
   float verifiedLengthLink1 = 0.0f;
   float verifiedLengthLink2 = 0.0f;
   LinkConfiguration::JointSolution returnResult = LinkConfiguration::GetInstance().Solve(startP1, endP2, lengthP1, lengthP2, result);
   if (returnResult == LinkConfiguration::JointSolution::FOUND)
   {
      verifiedLengthLink1 = (result - startP1).length();
      verifiedLengthLink2 = (endP2 - result).length();
   }
   return;
}

void main()
{
   solveAndExamineResult(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 7.0f, 0.0f), 3.0f, 4.0f);
   solveAndExamineResult(Vector3(1.0f, 0.0f, 0.0f), Vector3(4.0f, 0.0f, 0.0f), 1.0f, 2.0f);
   solveAndExamineResult(Vector3(1.0f, 0.0f, 0.0f), Vector3(4.0f, 0.0f, 0.0f), 1.0f, 3.0f);
   solveAndExamineResult(Vector3(1.0f, 0.0f, 0.0f), Vector3(4.0f, 0.0f, 0.0f), 1.0f, 13.0f);
   solveAndExamineResult(Vector3(1.0f, 0.0f, 0.0f), Vector3(4.0f, 0.0f, 0.0f), -1.0f, 13.0f);
}

#endif
