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

float Math::degreesToRadians(float degrees)
{
   return degrees * c_pi / 180.0f;
}

float Math::mix(float a, float b, float weightB)
{
	return (1 - weightB) * a + weightB * b;
}

float Math::crossfade(float a, float b, float t)
{
	return mix(a, b, t);
}

float Math::bounceClampBottom(float t)
{
	return std::fabs(t);
}

float Math::bounceClampTop(float t)
{
	return 1.0f - std::fabs(1.0f - t);
}

float Math::bounceClampBottomTop(float t)
{
	return bounceClampTop(bounceClampBottom(t));
}

float Math::normalizedBezier3(float b, float c, float t)
{
	float s = 1.0f - t;
	float t2 = t * t;
	float s2 = s * s;
	float t3 = t2 * t;

	return (3.0f * b * s2 * t) + (3.0f * c * s * t2) + t3;
}