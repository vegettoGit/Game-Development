#include "test.h"

#ifdef TEST_VECTOR3

#include "vector3.h"

// Intentionally created to test move constructor
Vector3 PassAndReturn(Vector3 test)
{
   return test;
}

void main()
{
   // Constructor
   Vector3 test1(1.0f, 2.0f, 3.0f);
   
   // Copy constructor
   Vector3 test2(test1);

   // Constructor
   // We would then expect move constructor (rvalue), but might not happen (copy elision) depending on compiler settings
   Vector3 test3(Vector3(4.0f, 5.0f, 6.0f));

   // Constructor of temporary (rvalue)
   // Move constructor of temporary directly into test4 (return value optimization happens)
   // Destructor of temporary
   Vector3 test4(PassAndReturn(Vector3(7.0f, 8.0f, 9.0f)));

   test1.normalize();
   float length = test1.length();

   // Constructs a temporary, adds the values and calls the move constructor to steal the resources from the temporary
   Vector3 test5 = test3 + test4;
   Vector3 test6 = test4 - test3;

   // test6 destructor
   // test5 destructor
   // test4 destructor
   // test3 destructor
   // test2 destructor
   // test1 destructor

   Vector3 test7(2.0f, 3.0f, 4.0f);
   Vector3 test8(5.0f, 6.0f, 7.0f);

   bool isPerpendicular1 = test7.isPerpendicular(test8);

   Vector3 test9 = test7.cross(test8);

   bool isPerpendicular2 = test7.isPerpendicular(test9);
   bool isPerpendicular3 = test8.isPerpendicular(test9);

   // Get angle between orthogonal vectors, should be PI/2
   float angle = test9.getAngle(test7);

   return;
}

#endif
