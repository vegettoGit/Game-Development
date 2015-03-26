#include "linkConfiguration.h"
#include "Vector3.h"
#include <math.h>

LinkConfiguration::LinkConfiguration()
{
}

LinkConfiguration::~LinkConfiguration()
{
}

LinkConfiguration& LinkConfiguration::GetInstance()
{
   static LinkConfiguration s_instance;
   return s_instance;
}

Vector3 LinkConfiguration::Solve(const Vector3& link1StartPoint, const Vector3& link2EndPoint, float link1Length, float link2Length)
{
   /*

     Here is the math involved in solving the problem :)
     The plane P is defined by the following 2 vectors:
   
     V1 = Link2EndPoint - Link1StartPoint
     V2 = A Vector orthogonal to V1
   
     Let's solve the problem on the plane P as a first step.
     From there we will be able to create unlimited solutions at a later point, by rotating the result joint point around V1.
   
     In order to solve the problem on the plane P, we can easily solve the problem using the plane XY first.
     This allows us to greatly simplify the problem by using the equations mentioned below.
     Unit directions for XY are (1, 0, 0) and (0, 1, 0)
     End point          = (c, 0, 0)
     Result joint point = (a, b, 0)
   
     |result joint point - (0, 0, 0)| = L1
     |end point - result joint point| = L2
   
     a^2 + b^2 = L1^2                  
     (c - a)^2 + b^2 = L2^2   ;  c^2 - 2ca + a^2 + b^2 = L2^2            
    
     Substract both equations
   
     c^2 - 2ca = L2^2 - L1^2  ;  c - 2a = (L2^2 - L1^2) / c
     a - c / 2 = (L1^2 - L2^2) / c / 2
     a = c / 2 + (L1^2 - L2^2) / c / 2
     2a = c +  (L1^2 - L2^2) / c

     The final computed values are the following (later we have to translate them back to the plane P):
     a = (c + (L1^2 - L2^2) / c)) / 2
     b = sqrt(L1^2 - a^2)

   */

   // Since the start point in our local coordinates is at (0, 0, 0), c = Length (V1)
   Vector3 v1 = link2EndPoint - link1StartPoint;
   float c = v1.length();

   v1.normalize();

   Vector3 v2;
   if (v1.m_x == 0 && v1.m_y == 0)
   {
      v2 = Vector3(1.0f, 0.0f, 0.0f);
   }
   else
   {
      v2 = Vector3(-v1.m_y, v1.m_x, 0.0f);
   }

   // Solution on plane XY
   float l1Square = link1Length * link1Length;
   float a = (c + (l1Square - link2Length * link2Length) / c) / 2.0f;
   float b = sqrt(l1Square - a * a);

   // Translate into P coordinates
   Vector3 result;
   
   result = v1 * a;
   result += (v2 * b);

   // Translate into world coordinates
   result += link1StartPoint;

   return result;
}