/*
   Helper Math functions
*/

struct Math
{
   static const float c_epsilon;

   bool equal        (float a, float b);
   bool lessThan     (float a, float b);
   bool greaterThan  (float a, float b);

private:

   float epsilon     (float a, float b);
};



