#include "test.h"

#ifdef TEST_LINK_CONFIGURATION

#include "linkConfiguration.h"
#include "Vector3.h"

void main()
{
   Vector3 startP1(0.0f, 0.0f, 0.0f);
   float lengthP1 = 3;
   Vector3 endP2(0.0f, 7.0f, 0.0f);
   float lengthP2 = 4;

   Vector3 result = LinkConfiguration::GetInstance().Solve(startP1, endP2, lengthP1, lengthP2);

   return;
}

#endif