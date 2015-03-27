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

bool Math::lessThan(float a, float b)
{
   return (b - a) > ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * c_epsilon );
}