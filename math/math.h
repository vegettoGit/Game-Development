/*
   Helper Math functions
*/

struct Math
{
   static const float c_epsilon;
   static const float c_pi;

   static bool  equal            (float a, float b);
   static bool  lessThan         (float a, float b);
   static bool  greaterThan      (float a, float b);

   static float radiansToDegrees (float radians);
   static float degreesToRadians (float radians);

   static float mix              (float a, float b, float weightB);
   static float crossfade        (float a, float b, float t);

   // Bounces off the bottom of the [0, 1] range. Any negative values are now positive
   static float bounceClampBottom   (float t);

   // Bounces off the top of the [0, 1] range. Any values over 1 become inverted below 1.
   static float bounceClampTop      (float t);
   static float bounceClampBottomTop(float t);

   // Cubic (3rd) Bezier through A, B, C, D where A (start) and D (end) are assumed to be 0 and 1
   static float normalizedBezier3(float b, float c, float t);

private:

   static float epsilon          (float a, float b);
};



