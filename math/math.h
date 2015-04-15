/*
   Helper Math functions
*/

struct Math
{
   static const float c_epsilon;

   static bool equal        (float a, float b);
   static bool lessThan     (float a, float b);
   static bool greaterThan  (float a, float b);

private:

   static float epsilon     (float a, float b);
};



