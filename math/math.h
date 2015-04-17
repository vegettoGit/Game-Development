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

private:

   static float epsilon          (float a, float b);
};



