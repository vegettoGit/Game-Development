#include "math.h"
#include <cmath>

/*

 - Floating point comparison:

   How we choose an epsilon depends on the problem we want to solve.
   The following functions currently serve our game environment.

   Reference for floating point calculations:
   . The Art of Computer Programming Volumen 2 (Knuth)

*/

const float Math::c_epsilon = 0.00001f;
const float Math::c_pi      = 3.14159265359f;

float Math::epsilon(float a, float b)
{
   return ( std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a) ) * c_epsilon;
}

bool Math::equal(float a, float b)
{
   return fabs(a - b) <= epsilon(a, b);
}

bool Math::lessThan(float a, float b)
{
   return (b - a) > epsilon(a, b);
}

bool Math::greaterThan(float a, float b)
{
   return lessThan(b, a);
}

float Math::radiansToDegrees(float radians)
{
   return radians * 180.0f / c_pi;
}